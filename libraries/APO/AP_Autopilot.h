/*
 * AP_Autopilot.h
 *
 *  Created on: Apr 30, 2011
 *      Author: jgoppert
 */

#ifndef AP_AUTOPILOT_H_
#define AP_AUTOPILOT_H_

#include "../AP_Common/AP_Loop.h"

/**
 * ArduPilotOne namespace to protect variables
 * from overlap with avr and libraries etc.
 * ArduPilotOne does not use any global
 * variables.
 */

namespace apo {

// enumerations
// forward declarations
class AP_Navigator;
class AP_Guide;
class AP_Controller;
class AP_Board;
class AP_CommLink;

/**
 * This class encapsulates the entire autopilot system
 * The constructor takes guide, navigator, and controller
 * as well as the hardware abstraction layer.
 *
 * It inherits from loop to manage
 * the sub-loops and sets the overall
 * frequency for the autopilot.
 *

 */
class AP_Autopilot: public Loop {
public:
    /**
     * Default constructor
     */
    AP_Autopilot(AP_Navigator * navigator, AP_Guide * guide,
                 AP_Controller * controller, AP_Board * board,
                 AP_CommLink * gcs, AP_CommLink * hil);

    /**
     * Accessors
     */
    AP_Navigator * getNavigator() {
        return _navigator;
    }
    AP_Guide * getGuide() {
        return _guide;
    }
    AP_Controller * getController() {
        return _controller;
    }
    AP_Board * getBoard() {
        return _board;
    }

    AP_CommLink * getGcs() { 
        return _gcs; 
    }
    
    AP_CommLink * getHil() {
        return _hil;
    }

    /**
     * Loop Monitoring
     */
    uint32_t callbackCalls;

    /**
     * Misc Callback Functions
     */
    void cycleLeds() {}
    void mavlinkDelay(uint32_t millis) {}

private:

    /**
     * Loop Callbacks (fastest)
     * - inertial navigation
     * @param data A void pointer used to pass the apo class
     *  so that the apo public interface may be accessed.
     */
    static void callback(void * data);

    /**
     * Loop 0 Callbacks
     * - control
     * - compass reading
     * @see callback
     */
    static void callback0(void * data);

    /**
     * Loop 1 Callbacks
     * - gps sensor fusion
     * - compass sensor fusion
     * @see callback
     */
    static void callback1(void * data);

    /**
     * Loop 2 Callbacks
     * - slow messages
     * @see callback
     */
    static void callback2(void * data);

    /**
     * Loop 3 Callbacks
     * - super slow messages
     * - log writing
     * @see callback
     */
    static void callback3(void * data);

    /**
     * Components
     */
    AP_Navigator * _navigator;
    AP_Guide * _guide;
    AP_Controller * _controller;
    AP_Board * _board;

    // communications
    AP_CommLink * _gcs;
    AP_CommLink * _hil;
};

} // namespace apo

#endif /* AP_AUTOPILOT_H_ */
// vim:ts=4:sw=4:expandtab
