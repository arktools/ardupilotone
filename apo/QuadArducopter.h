/*
 * QuadArducopter.h
 *
 *  Created on: May 1, 2011
 *      Author: jgoppert
 */

#ifndef QUADARDUCOPTER_H_
#define QUADARDUCOPTER_H_

using namespace apo;

// algorithm selection
#define CONTROLLER_CLASS ControllerQuad
#define GUIDE_CLASS MavlinkGuide
#define NAVIGATOR_CLASS Navigator_Dcm

// hardware selection
//#define BOARD_TYPE Board_APM1
//#define BOARD_TYPE Board_APM1_2560
#define BOARD_TYPE Board_APM2

static const struct AP_Board::parameters_t parameters = 
{
    // vehicle type
    MAV_QUADROTOR,

    // mode
    AP_Board::MODE_LIVE,
    //AP_Board::MODE_HIL_CNTRL,

    // options
    AP_Board::opt_gps | 
    //AP_Board::opt_baro | 
    //AP_Board::opt_compass |
    //AP_Board::opt_batteryMonitor |
    //AP_Board::opt_rangeFinderFront |
    //AP_Board::opt_rangeFinderBack |
    //AP_Board::opt_rangeFinderLeft |
    //AP_Board::opt_rangeFinderRight |
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

// position control loop
static const float PID_TILT_P = 0.1;
static const float PID_TILT_I = 0;
static const float PID_TILT_D = 0.1;
static const float PID_TILT_LIM = 0.04; // about 2 deg
static const float PID_TILT_AWU = 0.02; // about 1 deg
static const float PID_TILT_DFCUT = 10; // cut derivative feedback at 10 hz

static const float PID_SPD_P = 1;
static const float PID_SPD_I = 0;
static const float PID_SPD_D = 0.1;
static const float PID_SPD_LIM = 0.04; // about 2 deg
static const float PID_SPD_AWU = 0.02; // about 1 deg
static const float PID_SPD_DFCUT = 10; // cut derivative feedback at 10 hz

static const float PID_POS_Z_P = 0.1;
static const float PID_POS_Z_I = 0;
static const float PID_POS_Z_D = 0.2;
static const float PID_POS_Z_LIM = 0.1;
static const float PID_POS_Z_AWU = 0;
static const float PID_POS_Z_DFCUT = 10; // cut derivative feedback at 10 hz

// attitude control loop
static const float PID_ATT_P = 0.17;
static const float PID_ATT_I = 0.5;
static const float PID_ATT_D = 0.06;
static const float PID_ATT_LIM = 0.05; // 5 % motors
static const float PID_ATT_AWU = 0.005; // 0.5 %
static const float PID_ATT_DFCUT = 25; // cut derivative feedback at 25 hz
static const float PID_YAWPOS_P = 1;
static const float PID_YAWPOS_I = 0;
static const float PID_YAWPOS_D = 0.1;
static const float PID_YAWPOS_LIM = 1; // 1 rad/s
static const float PID_YAWPOS_AWU = 0; // 1 rad/s
static const float PID_YAWSPEED_P = 0.5;
static const float PID_YAWSPEED_I = 0;
static const float PID_YAWSPEED_D = 0;
static const float PID_YAWSPEED_LIM = .05; // 5 % motors
static const float PID_YAWSPEED_AWU = 0.0;
static const float PID_YAWSPEED_DFCUT = 3.0; // 3 Radians, about 1 Hz
static const float THRUST_HOVER_OFFSET = 0.475;

// guidance
static const float velCmd = 0.3; // m/s
static const float xt = 10; // cross track gain
static const float xtLim = 90; // cross track angle limit, deg

#include "ControllerQuad.h"

#endif /* QUADARDUCOPTER_H_ */
// vim:ts=4:sw=4:expandtab
