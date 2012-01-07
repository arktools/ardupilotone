/*
 * Board_APM1.cpp
 *
 *  Created on: Dec 7, 2011
 *
 */

#include <FastSerial.h>
#include <I2C.h>
#include <AP_Common.h>
#include <APM_RC.h>
#include <AP_RangeFinder.h>
#include <GCS_MAVLink.h>
#include <AP_ADC.h>
#include <AP_DCM.h>
#include <AP_Compass.h>
#include <AP_GPS.h>
#include <AP_IMU.h>
#include <AP_Baro.h>
#include <ModeFilter.h>
#include <APO.h>
#include <AP_AnalogSource.h>
#include <AP_InertialSensor.h>
#include <DataFlash.h>
#include <SPI.h>

#include "Board_APM1.h"

namespace apo {

Board_APM1::Board_APM1(const parameters_t & parameters) : 
    AP_Board(parameters) {

    AP_Var::load_all();

    // start I2C
    I2c.begin();
    I2c.timeOut(20);

    //start SPI
    SPI.begin();
    SPI.setClockDivider(SPI_CLOCK_DIV16); // 1MHZ SPI rate

    // ports
    _ports[0]=&Serial;
    _ports[1]=&Serial1;
    _ports[2]=&Serial3;
    _ports[3]=NULL;

    setPort(PORT_DEBUG,0);
    setPort(PORT_HIL,1);
    setPort(PORT_GCS,2);

    // start debug
    getDebug()->println_P(PSTR("initialized getDebug() port"));

    // button and switch locations
    _slideSwitchPin = 40;
    _pushButtonPin = 41;
    _aLedPin = 37;
    _bLedPin = 36;
    _cLedPin = 35;

    // eeprom memory
    _eepromMaxAddr = 1024;

    // pin modes
    pinMode(_aLedPin, OUTPUT); //  extra led
    pinMode(_bLedPin, OUTPUT); //  imu ledclass AP_CommLink;
    pinMode(_cLedPin, OUTPUT); //  gps led
    pinMode(_slideSwitchPin, INPUT);
    pinMode(_pushButtonPin, INPUT);
    DDRL |= B00000100; // set port L, pint 2 to output for the relay

    // components
    _isr_registry = new Arduino_Mega_ISR_Registry;
    _radio = new APM_RC_APM1;
    _radio->Init(_isr_registry);
    _dataFlash = new DataFlash_APM1;
    _scheduler = new AP_TimerProcess(_isr_registry);
    _adc = new AP_ADC_ADS7844(_scheduler);

    // live mode devices
    if (_parameters.mode == MODE_LIVE) {

        if (_parameters.options & opt_batteryMonitor) {
            _batteryMonitor = new AP_BatteryMonitor(
                    _parameters.batteryPin,
                    _parameters.batteryVoltageDivRatio,
                    _parameters.batteryMinVolt,
                    _parameters.batteryMaxVolt);
        }

        if (_parameters.options & opt_gps) {
            setPort(PORT_GPS,1);
            getDebug()->println_P(PSTR("initializing gps"));
            AP_GPS_Auto gpsDriver(getPort(PORT_GPS), &(_gps));
            _gps = &gpsDriver;
            _gps->callback = delay;
            _gps->init();
        }

        if (_parameters.options & opt_baro) {
            getDebug()->println_P(PSTR("initializing baro"));
            _baro = new AP_Baro_BMP085(false);
            _baro->init(_scheduler);
        }

        if (_parameters.options & opt_compass) {
            getDebug()->println_P(PSTR("initializing compass"));
            _compass = new AP_Compass_HMC5843;
            _compass->set_orientation(_parameters.compassOrientation);
            _compass->set_offsets(0,0,0);
            _compass->set_declination(0.0);
            _compass->init();
        }
    }

    /**
     * Initialize ultrasonic sensors. If sensors are not plugged in, the navigator will not
     * initialize them and NULL will be assigned to those corresponding pointers.
     * On detecting NU/LL assigned to any ultrasonic sensor, its corresponding block of code
     * will not be executed by the navigator.
     * The coordinate system is assigned by the right hand rule with the thumb pointing down.
     * In set_orientation, it is defined as (front/back,left/right,down,up)
     */

    // XXX this isn't really that general, should be a better way

    if (_parameters.options & opt_rangeFinderFront) {
        getDebug()->println_P(PSTR("initializing front range finder"));
        RangeFinder * rangeFinder = 
            new AP_RangeFinder_MaxsonarXL(new AP_AnalogSource_Arduino(1),new ModeFilter);
        rangeFinder->set_orientation(1, 0, 0);
        _rangeFinders.push_back(rangeFinder);
    }

    if (_parameters.options & opt_rangeFinderBack) {
        getDebug()->println_P(PSTR("initializing back range finder"));
        RangeFinder * rangeFinder = 
            new AP_RangeFinder_MaxsonarXL(new AP_AnalogSource_Arduino(2),new ModeFilter);
        rangeFinder->set_orientation(-1, 0, 0);
        _rangeFinders.push_back(rangeFinder);
    }

    if (_parameters.options & opt_rangeFinderLeft) {
        getDebug()->println_P(PSTR("initializing left range finder"));
        RangeFinder * rangeFinder = 
            new AP_RangeFinder_MaxsonarXL(new AP_AnalogSource_Arduino(3),new ModeFilter);
        rangeFinder->set_orientation(0, -1, 0);
        _rangeFinders.push_back(rangeFinder);
    }

    if (_parameters.options & opt_rangeFinderRight) {
        getDebug()->println_P(PSTR("initializing right range finder"));
        RangeFinder * rangeFinder = 
            new AP_RangeFinder_MaxsonarXL(new AP_AnalogSource_Arduino(4),new ModeFilter);
        rangeFinder->set_orientation(0, 1, 0);
        _rangeFinders.push_back(rangeFinder);
    }

    if (_parameters.options & opt_rangeFinderUp) {
        getDebug()->println_P(PSTR("initializing up range finder"));
        RangeFinder * rangeFinder = 
            new AP_RangeFinder_MaxsonarXL(new AP_AnalogSource_Arduino(5),new ModeFilter);
        rangeFinder->set_orientation(0, 0, -1);
        _rangeFinders.push_back(rangeFinder);
    }

    if (_parameters.options & opt_rangeFinderDown) {
        getDebug()->println_P(PSTR("initializing down range finder"));
        RangeFinder * rangeFinder = 
            new AP_RangeFinder_MaxsonarXL(new AP_AnalogSource_Arduino(6),new ModeFilter);
        rangeFinder->set_orientation(0, 0, 1);
        _rangeFinders.push_back(rangeFinder);
    }

    // navigation sensors
    getDebug()->println_P(PSTR("initializing imu"));
    _ins = new AP_InertialSensor_Oilpan(_adc,_scheduler);
    getDebug()->println_P(PSTR("initializing ins"));
    _imu = new AP_IMU_INS(_ins, k_sensorCalib,_scheduler);
    getDebug()->println_P(PSTR("setup completed"));
}

} // namespace apo

// vim:ts=4:sw=4:expandtab
