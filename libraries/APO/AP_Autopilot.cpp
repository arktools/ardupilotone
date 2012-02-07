/*
 * AP_Autopilot.cpp
 *
 *  Created on: Apr 30, 2011
 *      Author: jgoppert
 */

#include "../FastSerial/FastSerial.h"
#include "AP_Autopilot.h"
#include "../AP_GPS/AP_GPS.h"
#include "../APM_RC/APM_RC.h"
#include "AP_Board.h"
#include "AP_CommLink.h"
#include "AP_MavlinkCommand.h"
#include "AP_Navigator.h"
#include "AP_Controller.h"
#include "AP_Guide.h"
#include "AP_Process.h"
#include "AP_BatteryMonitor.h"

namespace apo {

    class AP_Board;

    AP_Autopilot::AP_Autopilot(AP_Navigator * navigator, AP_Guide * guide,
            AP_Controller * controller, AP_Board * board) :
        //Loop(board->getParameters().loopRate, callback, this), _navigator(navigator), _guide(guide),
        //_controller(controller), _board(board),
        callbackCalls(0) {

            // allow hardware to call autopilot public routines
            board->setAutopilot(this);

            board->getDebug()->printf_P(PSTR("initializing autopilot\n"));
            board->getDebug()->printf_P(PSTR("free ram: %d bytes\n"),freeMemory());

            /*
             * Comm links
             */
            board->setGcs(new MavlinkComm(board->getGcsPort(), navigator, guide, controller, board, 3));
            if (board->getParameters().mode != AP_Board::MODE_LIVE) {
                board->setHil(new MavlinkComm(board->getHilPort(), navigator, guide, controller, board, 3));
            }
            board->getGcs()->sendMessage(MAVLINK_MSG_ID_HEARTBEAT);
            board->getGcs()->sendMessage(MAVLINK_MSG_ID_SYS_STATUS);

            /*
             * Calibration
             */
            controller->setState(MAV_STATE_CALIBRATING);
            board->getGcs()->sendMessage(MAVLINK_MSG_ID_HEARTBEAT);
            board->getGcs()->sendMessage(MAVLINK_MSG_ID_SYS_STATUS);

            if (navigator) navigator->calibrate();

            /*
             * Look for valid initial state
             */
            while (_navigator) {

                // letc gcs known we are alive
                board->getGcs()->sendMessage(MAVLINK_MSG_ID_HEARTBEAT);
                board->getGcs()->sendMessage(MAVLINK_MSG_ID_SYS_STATUS);
                if (board->getParameters().mode == AP_Board::MODE_LIVE) {
                    _navigator->updateSlow(0);
                    if (board->getGps()) {
                        if (board->getGps()->fix) {
                            break;
                        } else {
                            board->getGps()->update();
                            board->getGcs()->sendText(SEVERITY_LOW,
                                    PSTR("waiting for gps lock\n"));
                            board->getDebug()->printf_P(PSTR("waiting for gps lock\n"));
                        }
                    } else { // no gps, can skip
                        break;
                    }
                } else if (board->getParameters().mode == AP_Board::MODE_HIL_CNTL) { // hil
                    board->getHil()->sendMessage(MAVLINK_MSG_ID_HEARTBEAT);
                    board->getHil()->receive();
                    if (_navigator->getTimeStamp() != 0) {
                        // give hil a chance to send some packets
                        for (int i = 0; i < 5; i++) {
                            board->getDebug()->println_P(PSTR("reading initial hil packets"));
                            board->getGcs()->sendText(SEVERITY_LOW, PSTR("reading initial hil packets"));
                            delay(1000);
                        }
                        break;
                    }
                    board->getDebug()->println_P(PSTR("waiting for hil packet"));
                    board->getGcs()->sendText(SEVERITY_LOW, PSTR("waiting for hil packets"));
                }
                delay(500);
            }

            AP_MavlinkCommand::home.setAlt(_navigator->getAlt());
            AP_MavlinkCommand::home.setLat(_navigator->getLat());
            AP_MavlinkCommand::home.setLon(_navigator->getLon());
            AP_MavlinkCommand::home.setCommand(MAV_CMD_NAV_WAYPOINT);
            AP_MavlinkCommand::home.save();
            board->getDebug()->printf_P(PSTR("\nhome before load lat: %f deg, lon: %f deg, cmd: %d\n"),
                    AP_MavlinkCommand::home.getLat()*rad2Deg,
                    AP_MavlinkCommand::home.getLon()*rad2Deg,
                    AP_MavlinkCommand::home.getCommand());
            AP_MavlinkCommand::home.load();
            board->getDebug()->printf_P(PSTR("\nhome after load lat: %f deg, lon: %f deg, cmd: %d\n"),
                    AP_MavlinkCommand::home.getLat()*rad2Deg,
                    AP_MavlinkCommand::home.getLon()*rad2Deg,
                    AP_MavlinkCommand::home.getCommand());

            guide->setCurrentIndex(0);
            controller->setMode(MAV_MODE_LOCKED);
            controller->setState(MAV_STATE_STANDBY);

            /*
             * Set up the processes.
             */

            proc_forbid();
//            navigator->createProcess(navigationTask, this);
            proc_permit();



            /*
             * Attach loops, stacking for priority
             */
            /*
            board->getDebug()->println_P(PSTR("attaching loops"));
            subLoops().push_back(new Loop(board->getParameters().loop0Rate, callback0, this));
            subLoops().push_back(new Loop(board->getParameters().loop1Rate, callback1, this));
            subLoops().push_back(new Loop(board->getParameters().loop2Rate, callback2, this));
            subLoops().push_back(new Loop(board->getParameters().loop3Rate, callback3, this));
            */

            board->getDebug()->println_P(PSTR("running"));
            //board->getGcs()->sendText(SEVERITY_LOW, PSTR("running"));
        }

    void AP_Autopilot::navigationTask(void * data) {
        AP_Autopilot * apo = (AP_Autopilot *) data;
        AP_Navigator * nav = apo->getNavigator();
        //apo->getBoard()->getDebug()->println_P(PSTR("callback"));

        nav->setupTimer();
        while(1) {

            apo->callbackCalls++;
            // Get the navigator if it hasn't already been
            if(!nav) {
                nav = apo->getNavigator();
            } 

            if(nav) {
                nav->updateFast(nav->proc_dt());
            }
            nav->waitOnTimer();
           }
        }


        void AP_Autopilot::controllerTask(void * data) {
            AP_Autopilot * apo = (AP_Autopilot *) data;
            AP_CommLink * hil = apo->getBoard()->getHil();
            AP_Controller * ctrl = apo->getController();
            //parameters_t parameters = apo->getBoard()->getParameters();
            //apo->getBoard()->getDebug()->println_P(PSTR("callback 0"));

            while(1) {
                /*
                 * hardware in the loop
                 */
                if(!hil) {
                    hil = apo->getBoard()->getHil();
                }

                if(hil && apo->getBoard()->getParameters().mode != AP_Board::MODE_LIVE) {
                    hil->receive();
                    hil->sendMessage(MAVLINK_MSG_ID_RC_CHANNELS_SCALED);
                }

                /*
                 * update control laws
                 */
                if(!ctrl) {
                    ctrl = apo->getController();
                }
                if(ctrl) {
                    ctrl->update(ctrl->proc_dt());
                }
                /*
                   char msg[50];
                   sprintf(msg, "c_hdg: %f, c_thr: %f", apo->guide()->headingCommand, apo->guide()->groundSpeedCommand);
                   apo->board()->gcs->sendText(AP_CommLink::SEVERITY_LOW, msg);
                   */

                // Set Signal Blocking
            }
        }

        void AP_Autopilot::gpsFusion(void * data) {
            AP_Autopilot * apo = (AP_Autopilot *) data;
            AP_Navigator * nav = apo->getNavigator();
            AP_Guide * guide = apo->getGuide();
            AP_CommLink * gcs = apo->getBoard()->getGcs();
            //apo->getBoard()->getDebug()->println_P(PSTR("callback 1"));

            while(1) {
                /*
                 * update guidance laws
                 */
                if(!guide) {
                    guide = apo->getGuide();
                }
                if(guide) {
                    //apo->getBoard()->getDebug()->println_P(PSTR("updating guide"));
                    guide->update();
                }

                /*
                 * slow navigation loop update
                 */
                if(!nav) {
                    nav = apo->getNavigator();
                }
                if(nav) {
                    nav->updateSlow(nav->proc_dt());
                }

                /*
                 * send telemetry
                 */
                if(!gcs) {
                    gcs = apo->getBoard()->getGcs();
                }
                if(gcs) {
                    gcs->sendMessage(MAVLINK_MSG_ID_ATTITUDE);
                    gcs->sendMessage(MAVLINK_MSG_ID_GLOBAL_POSITION);

                    gcs->receive();
                }

                /*
                 * navigator debug
                 */
                /*
                   if (apo->navigator()) {
                   apo->getBoard()->getDebug()->printf_P(PSTR("roll: %f deg\tpitch: %f deg\tyaw: %f deg\n"),
                   apo->navigator()->getRoll()*rad2Deg,
                   apo->navigator()->getPitch()*rad2Deg,
                   apo->navigator()->getYaw()*rad2Deg);
                   apo->getBoard()->getDebug()->printf_P(PSTR("lat: %f deg\tlon: %f deg\talt: %f m\n"),
                   apo->navigator()->getLat()*rad2Deg,
                   apo->navigator()->getLon()*rad2Deg,
                   apo->navigator()->getAlt());
                   }
                   */

                // Set Signal Wait
            }
        }

        void AP_Autopilot::slowMessages(void * data) {
            AP_Autopilot * apo = (AP_Autopilot *) data;
            AP_Board * board = apo->getBoard();
            AP_CommLink * gcs = board->getGcs();
            AP_BatteryMonitor * batt = board->getBatteryMonitor();

            //apo->getBoard()->getDebug()->println_P(PSTR("callback 2"));

            /*
             * send telemetry
             */
            while(1) {
                if(!gcs) {
                    gcs = apo->getBoard()->getGcs();
                }
                if(gcs) {
                    gcs->sendMessage(MAVLINK_MSG_ID_RC_CHANNELS_SCALED);
                    gcs->sendMessage(MAVLINK_MSG_ID_RC_CHANNELS_RAW);
                    gcs->sendMessage(MAVLINK_MSG_ID_SCALED_IMU);                    
                }

                /*
                 * Update battery monitor
                 */
                if(!batt) {
                    batt = apo->getBoard()->getBatteryMonitor();
                }
                if(batt) {
                    batt->update();
                }

                /*
                 * Send heartbeat
                 */
                if(gcs){
                    gcs->sendMessage(MAVLINK_MSG_ID_HEARTBEAT);
                }


                /*
                 * load/loop rate/ram debug
                 */
                if(board) {
                    //board->setLoad(apo->load());
                    board->getDebug()->printf_P(PSTR("callback calls: %d\n"),apo->callbackCalls);
                    apo->callbackCalls = 0;
                    //board->getDebug()->printf_P(PSTR("load: %d%%\trate: %f Hz\tfree ram: %d bytes\n"),
                            //apo->load(),1.0/apo->dt(),freeMemory());
                    board->getGcs()->sendMessage(MAVLINK_MSG_ID_SYS_STATUS);
                }

                /*
                 * adc debug
                 */
                //apo->getDebug().printf_P(PSTR("adc: %d %d %d %d %d %d %d %d\n"),
                //apo->adc()->Ch(0), apo->adc()->Ch(1), apo->adc()->Ch(2),
                //apo->adc()->Ch(3), apo->adc()->Ch(4), apo->adc()->Ch(5),
                //apo->adc()->Ch(6), apo->adc()->Ch(7), apo->adc()->Ch(8));
                //

                // Set Signal Wait
            }
        }

        void AP_Autopilot::callback3(void * data) {
            AP_Autopilot * apo = (AP_Autopilot *) data;
            //apo->getBoard()->getDebug()->println_P(PSTR("callback 3"));
        }

    } // apo
    // vim:ts=4:sw=4:expandtab
