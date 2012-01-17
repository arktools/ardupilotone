/*
 * AP_Board.cpp
 *
 *  Created on: Apr 4, 2011
 *
 */

#include <GCS_MAVLink.h>
#include "AP_CommLink.h"
#include "AP_Board.h"

#define LED_ON HIGH
#define LED_OFF LOW

namespace apo {

void AP_Board::delayWithCommUpdate(uint32_t t)
{
    uint32_t tstart;
    static uint32_t last_1hz, last_50hz;

    if (_inDelayWithCommUpdate) {
        // this should never happen, but let's not tempt fate by
        // letting the stack grow too much
        delay(t);
        return;
    }

    _inDelayWithCommUpdate = true;

    tstart = millis();
    do {
        uint32_t tnow = millis();
        if (tnow - last_1hz > 1000) {
            last_1hz = tnow;
            getGcs()->sendMessage(MAVLINK_MSG_ID_HEARTBEAT);
            getGcs()->sendMessage(MAVLINK_MSG_ID_SYS_STATUS);
        }
        if (tnow - last_50hz > 20) {
            last_50hz = tnow;
            getGcs()->requestCmds();
            getGcs()->sendParameters();
            getGcs()->receive();
        }
        delay(1);
        checkUsbConnection();
    } while (millis() - tstart < t);

    _inDelayWithCommUpdate = false;
}

void AP_Board::checkUsbConnection()
{
    if (_usbMuxPin == 0) return;
    bool _usbCheck = !digitalRead(_usbMuxPin);
    if (_usbCheck == _usbConnected) {
        return;
    }

    // the user has switched to/from the telemetry port
    _usbConnected = _usbCheck;
    // TODO get this working
    //if (_usbConnected) {
        //Serial.begin(_parameters.serial0Baud, 128, 128);
    //} else {
        //Serial.begin(map_baudrate(g.serial3_baud, SERIAL3_BAUD), 128, 128);
    //}
}


void AP_Board::flashLeds(bool on)
{
    digitalWrite(_aLedPin, on?LED_OFF:LED_ON);
    digitalWrite(_cLedPin, on?LED_ON:LED_OFF);
}

} // namespace apo

// vim:ts=4:sw=4:expandtab
