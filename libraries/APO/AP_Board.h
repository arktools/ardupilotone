/*
 * AP_Board.h
 *
 *  Created on: Apr 4, 2011
 *
 */

#ifndef AP_BOARD_H_
#define AP_BOARD_H_

#include "../AP_Common/AP_Vector.h"
#include "../GCS_MAVLink/GCS_MAVLink.h"
#include <AP_Math.h>

class AP_ADC;
class IMU;
class GPS;
class AP_Baro;
class Compass;
class BetterStream;
class RangeFinder;
class FastSerial;
class AP_IMU_INS;
class AP_InertialSensor;
class APM_RC_Class;
class AP_TimerProcess;
class Arduino_Mega_ISR_Registry;
class DataFlash_Class;

namespace apo {

class AP_RcChannel;
class AP_CommLink;
class AP_BatteryMonitor;
class AP_Autopilot;

class AP_Board {

public:

    // enumerations
    enum mode_e {
        MODE_LIVE, 
        MODE_HIL_CNTL,
        /*MODE_HIL_NAV*/
    };

    enum port_e {
        PORT_DEBUG,
        PORT_GCS,
        PORT_HIL,
        PORT_GPS,
    };

    // parameters
    typedef uint32_t options_t;
    enum options_e {
        opt_gps                 = 0<<1,
        opt_baro                = 1<<1,
        opt_compass             = 2<<1,
        opt_batteryMonitor      = 3<<1,
        opt_rangeFinderFront    = 4<<1,
        opt_rangeFinderBack     = 5<<1,
        opt_rangeFinderLeft     = 6<<1,
        opt_rangeFinderRight    = 7<<1,
        opt_rangeFinderUp       = 8<<1,
        opt_rangeFinderDown     = 9<<1,
    };

    struct parameters_t {
        // vehicle type
        MAV_TYPE vehicle;

        //mode
        mode_e mode;

        //options
        options_t options;

        // baud rates
        uint32_t debugBaud;
        uint32_t gcsBaud;
        uint32_t gpsBaud;
        uint32_t hilBaud;

        // battery sensor
        uint8_t batteryPin;
        float batteryVoltageDivRatio;
        float batteryMinVolt;
        float batteryMaxVolt;

        // compass sensor
        Matrix3f compassOrientation;

        // loop rates
        float loopRate;
        float loop0Rate;
        float loop1Rate;
        float loop2Rate;
        float loop3Rate;

        // misc
        uint8_t heartBeatTimeout;
    };

    // default ctors on pointers called on pointers here, this
    // allows NULL to be used as a boolean for if the device was
    // initialized
    AP_Board(const parameters_t &parameters): 
        _parameters(parameters) {
    }

    // get routines
    AP_ADC * getAdc() { return _adc; }
    GPS * getGps() { return _gps; }
    AP_Baro * getBaro() { return _baro; }
    Compass * getCompass() { return _compass; }
    Vector<RangeFinder *> getRangeFinders() { return _rangeFinders; }
    AP_BatteryMonitor * getBatteryMonitor() {  return _batteryMonitor; }
    AP_IMU_INS * getImu() { return _imu; }
    AP_InertialSensor * getIns() { return _ins; }
    AP_TimerProcess * getScheduler() { return _scheduler; }
    Arduino_Mega_ISR_Registry * getIsrRegistry() { return _isr_registry; }
    APM_RC_Class * getRadio() { return _radio; } 
    Vector<AP_RcChannel *> & getRadioChannels() { return _radioChannels; };
    FastSerial * getPort(port_e port);

    // TODO move these to AP_Autopilot?
    FastSerial * getDebug() { return getPort(PORT_DEBUG); }
    AP_CommLink * getGcs() { return _gcs; }
    AP_CommLink * getHil() { return _hil; }

    DataFlash_Class * getDataFlash() { return _dataFlash; }
    uint8_t getLoad() { return _load; }
    uint8_t getSlideSwitchPin() { return _slideSwitchPin; }
    uint8_t getPushButtonPin() { return _pushButtonPin; }
    uint8_t getALedPin() { return _aLedPin; }
    uint8_t getBLedPin() { return _bLedPin; }
    uint8_t getCLedPin() { return _cLedPin; }
    uint16_t getEEPROMMaxAddr() { return _eepromMaxAddr; }
    const parameters_t & getParameters() { return _parameters; }

    // set routines
    void setGcs(AP_CommLink * gcs) { _gcs = gcs; }
    void setHil(AP_CommLink * hil) { _hil = hil; }
    void setLoad(uint8_t load) { _load = load; }

    /**
     * delay while updating comms
     */
    void delayWithCommUpdate(uint32_t t);

    /**
     * called by gyro/accel init to flash LEDs so user
     * has some mesmerising lights to watch while waiting
     */
    void flashLeds(bool on);

    /**
     * check if usb is connected
     */
    void checkUsbConnection();

    void startPort(port_e port);
    void setPort(port_e port, uint8_t portNumber);
    uint8_t getPortNumber(port_e port);


protected:

    // sensors
    AP_ADC * _adc;
    GPS * _gps;
    AP_Baro * _baro;
    Compass * _compass;
    Vector<RangeFinder *> _rangeFinders;
    AP_BatteryMonitor * _batteryMonitor;
    AP_IMU_INS * _imu;
    AP_InertialSensor * _ins;

    // timing
    AP_TimerProcess * _scheduler;
    Arduino_Mega_ISR_Registry * _isr_registry;

    // radio
    APM_RC_Class * _radio;
    Vector<AP_RcChannel *> _radioChannels;

    // communications
    uint8_t _portNumber[4];
    FastSerial * _ports[4];
    AP_CommLink * _gcs;
    AP_CommLink * _hil;

    // data flash
    DataFlash_Class * _dataFlash;
    uint8_t _load;

    // settings
    uint8_t _slideSwitchPin;
    uint8_t _pushButtonPin;
    uint8_t _aLedPin;
    uint8_t _bLedPin;
    uint8_t _cLedPin;
    uint16_t _eepromMaxAddr;
    uint8_t _usbMuxPin;

    // parameters structure
    const parameters_t _parameters;

    bool _inDelayWithCommUpdate;
    bool _usbConnected;
};

} // namespace apo

#endif /* AP_HARDWAREABSTRACTIONLAYER_H_ */
// vim:ts=4:sw=4:expandtab
