/*
 * CarStampede.h
 *
 *  Created on: May 1, 2011
 *      Author: jgoppert
 *
 */

#ifndef CARSTAMPEDE_H_
#define CARSTAMPEDE_H_

using namespace apo;

// algorithm selection
#define CONTROLLER_CLASS ControllerCar
#define GUIDE_CLASS MavlinkGuide
#define NAVIGATOR_CLASS Navigator_Dcm

// hardware selection
//#define BOARD_TYPE Board_APM1
//#define BOARD_TYPE Board_APM1_2560
#define BOARD_TYPE Board_APM2

static const struct AP_Board::parameters_t parameters = 
{
    // vehicle type
    UGV_GROUND_ROVER,

    // mode
    AP_Board::MODE_LIVE,
    //AP_Board::MODE_HIL_CNTRL,

    // options
    AP_Board::opt_gps | 
    AP_Board::opt_baro | 
    AP_Board::opt_compass |
    AP_Board::opt_batteryMonitor |
    //AP_Board::opt_rangeFinderFront |
    //AP_Board::opt_rangeFinderBack |
    //AP_Board::opt_rangeFinderLeft |
    AP_Board::opt_rangeFinderRight |
    0, // note: 0 here to allow | on last option

    // baud rates
    57600,  // debug baud rate
    57600,  // telem baud rate
    38400,  // gps baud rate
    57600,  // hil baud rate

    // battery sensor
    0,      // battery  pin
    6,      // battery voltage div ratio
    10.0,   // battery min volt
    12.4,   // battery max volt
    AP_COMPASS_COMPONENTS_UP_PINS_FORWARD, // compass orientation

    // loop rates
    150,    // attitude nav
    50,     // controller
    10,     // pos nav/ gcs fast
    1,      // gcs slow
    0.1,     // very slow loop

    // heartbeat timeout
    3
};


static const bool useForwardReverseSwitch = false;

// gains
static const float steeringP = 0.1;
static const float steeringI = 0.0;
static const float steeringD = 0.1;
static const float steeringIMax = 0.0;
static const float steeringYMax = 1;
static const float steeringDFCut = 25.0;

static const float throttleP = 0.1;
static const float throttleI = 0.0;
static const float throttleD = 0.0;
static const float throttleIMax = 0.0;
static const float throttleYMax = 1;
static const float throttleDFCut = 0.0;

// guidance
static const float velCmd = 5;
static const float xt = 10;
static const float xtLim = 90;

#include "ControllerCar.h"

#endif /* CARSTAMPEDE_H_ */
// vim:ts=4:sw=4:expandtab
