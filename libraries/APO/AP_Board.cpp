/*
 * AP_Board.cpp
 *
 *  Created on: Apr 4, 2011
 *
 */

#include <FastSerial.h>
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
    // XXX this needs to be tested
    static uint8_t portNumberDebug = 0;
    static uint8_t portNumberGcs = 0;

    if (_usbMuxPin == 0) return;
    bool _usbCheck = !digitalRead(_usbMuxPin);
    if (_usbConnected == _usbCheck) {
        return;
    } else{
        _usbConnected = _usbCheck;
        if (_usbConnected) {
            portNumberDebug = getPortNumber(PORT_DEBUG);
            portNumberGcs = getPortNumber(PORT_GCS);
            setPort(PORT_DEBUG,portNumberGcs);
            setPort(PORT_GCS,portNumberDebug);
            getGcs()->initialize();
        } else {
            setPort(PORT_DEBUG,portNumberDebug);
            setPort(PORT_GCS,portNumberGcs);
            getGcs()->initialize();
        }
    }
}


void AP_Board::flashLeds(bool on)
{
    digitalWrite(_aLedPin, on?LED_OFF:LED_ON);
    digitalWrite(_cLedPin, on?LED_ON:LED_OFF);
}

FastSerial * AP_Board::getPort(port_e port) {
    return _ports[_portNumber[port]];
}

void AP_Board::startPort(port_e port) {
    switch(port) {
        case PORT_DEBUG:
            getPort(PORT_DEBUG)->begin(_parameters.debugBaud, 128, 128);
            break;
        case PORT_GCS:
            getPort(PORT_GCS)->begin(_parameters.gcsBaud, 128, 128);
            break;
        case PORT_HIL:
            getPort(PORT_HIL)->begin(_parameters.hilBaud, 128, 128);
            break;
        case PORT_GPS:
            getPort(PORT_GPS)->begin(_parameters.gpsBaud, 128, 16);
            break;
        default: 
            break;
    }
}

void AP_Board::setPort(port_e port, uint8_t portNumber) {
    _portNumber[port] = portNumber;
    startPort(port);
}

uint8_t AP_Board::getPortNumber(port_e port) {
    return _portNumber[port];
}

} // namespace apo

// vim:ts=4:sw=4:expandtab
