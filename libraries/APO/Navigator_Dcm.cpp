/*
 * Navigator_Dcm.cpp
 *
 *  Created on: Dec 6, 2011
 *      Author: jgoppert/ wenyaoxie
 */

#include "../FastSerial/FastSerial.h"
#include "Navigator_Dcm.h"
#include "AP_CommLink.h"
#include "AP_Board.h"
#include "../AP_DCM/AP_DCM.h"
#include "../AP_Math/AP_Math.h"
#include "../AP_Compass/AP_Compass.h"
#include "AP_MavlinkCommand.h"
#include "AP_Var_keys.h"
#include "../AP_RangeFinder/RangeFinder.h"
#include "../AP_IMU/AP_IMU.h"
#include "../AP_InertialSensor/AP_InertialSensor.h"
#include "../AP_Baro/AP_Baro.h"

namespace apo {

Navigator_Dcm::Navigator_Dcm(AP_Board * board, const uint16_t key, const prog_char_t * name) :
    AP_Navigator(board), _imuOffsetAddress(0),
    _dcm(_board->getImu(), _board->getGps(), _board->getCompass()),
    _rangeFinderDown(),
    _group(key, name ? : PSTR("NAV_")),
    _baroLowPass(&_group,1,10,PSTR("BAROLP")),
    _groundTemperature(&_group,2, 25.0,PSTR("GNDT")), // TODO check temp
    _groundPressure(&_group,3,0.0,PSTR("GNDP")) {

    // if orientation equal to front, store as front
    /**
     * rangeFinder<direction> is assigned values based on orientation which
     * is specified in ArduPilotOne.pde.
     */
    for (uint8_t i = 0; i < _board->getRangeFinders().getSize(); i++) {
        if (_board->getRangeFinders()[i] == NULL)
            continue;
        if (_board->getRangeFinders()[i]->orientation_x == 0
                && _board->getRangeFinders()[i]->orientation_y == 0
                && _board->getRangeFinders()[i]->orientation_z == 1)
            _rangeFinderDown = _board->getRangeFinders()[i];
    }

    // tune down dcm
    _dcm.kp_roll_pitch(0.030000);
    _dcm.ki_roll_pitch(0.00001278),	// 50 hz I term

    // tune down compass in dcm
    _dcm.kp_yaw(0.08);
    _dcm.ki_yaw(0);

    if (_board->getCompass()) {
        _dcm.set_compass(_board->getCompass());
    }
}
void Navigator_Dcm::calibrate() {

    AP_Navigator::calibrate();

    // TODO: handle cold/warm restart
    if (_board->getImu()) {
        _board->getImu()->warmStart();
    }

    if (_board->getBaro()) {

        int flashcount = 0;

        while(_groundPressure == 0){
            _board->getBaro()->read(); 					// Get initial data from absolute pressure sensor
            _groundPressure = _board->getBaro()->get_pressure();
            _groundTemperature = _board->getBaro()->get_temperature()/10.0;
            delay(20);
        }

        for(int i = 0; i < 30; i++){		// We take some readings...

            // set using low pass filters
            _groundPressure = _groundPressure * 0.9   + _board->getBaro()->get_pressure() * 0.1;
            _groundTemperature = _groundTemperature * 0.9   + (_board->getBaro()->get_temperature()/10.0) * 0.1;

            //mavlink_delay(20);
            delay(20);
            if(flashcount == 5) {
                digitalWrite(_board->getCLedPin(), LOW);
                digitalWrite(_board->getALedPin(), HIGH);
                digitalWrite(_board->getBLedPin(), LOW);
            }

            if(flashcount >= 10) {
                flashcount = 0;
                digitalWrite(_board->getCLedPin(), LOW);
                digitalWrite(_board->getALedPin(), HIGH);
                digitalWrite(_board->getBLedPin(), LOW);
            }
            flashcount++;
        }
        
        _groundPressure.save();
        _groundTemperature.save();

        _board->getDebug()->printf_P(PSTR("ground pressure: %ld ground temperature: %d\n"),_groundPressure.get(), _groundTemperature.get());
        _board->getGcs()->sendText(SEVERITY_LOW, PSTR("barometer calibration complete\n"));
    }
}

void Navigator_Dcm::updateFast(float dt) {

    if (_board->getParameters().mode != AP_Board::MODE_LIVE)
        return;

    setTimeStamp(micros()); // if running in live mode, record new time stamp

    // use range finder if attached and close to the ground
    if (_rangeFinderDown != NULL && _rangeFinderDown->distance <= 695) {
        setAlt(_rangeFinderDown->distance);

    // otherwise if you have a baro attached, use it
    } else if (_board->getBaro()) {
        /**
         * The altitued is read off the barometer by implementing the following formula:
         * altitude (in m) = 44330*(1-(p/po)^(1/5.255)),
         * where, po is pressure in Pa at sea level (101325 Pa).
         * See http://www.sparkfun.com/tutorials/253 or type this formula
         * in a search engine for more information.
         * altInt contains the altitude in meters.
         *
         * pressure input is in pascals
         * temp input is in deg C *10
         */
        _board->getBaro()->read();		// Get new data from absolute pressure sensor
        float reference = 44330 * (1.0 - (pow(_groundPressure.get()/101325.0,0.190295)));
        setAlt(_baroLowPass.update((44330 * (1.0 - (pow((_board->getBaro()->get_pressure()/101325.0),0.190295)))) - reference,dt));
        //_board->getDebug->printf_P(PSTR("Ground Pressure %f\tAltitude = %f\tGround Temperature = %f\tPress = %ld\tTemp = %d\n"),_groundPressure.get(),getAlt(),_groundTemperature.get(),_board->baro->Press,_board->baro->Temp);
        
    // last resort, use gps altitude
    } else if (_board->getGps() && _board->getGps()->fix) {
        setAlt_intM(_board->getGps()->altitude * 10); // gps in cm, intM in mm
    }

    // update dcm calculations and navigator data
    //
    _dcm.update_DCM_fast();
    setRoll(_dcm.roll);
    setPitch(_dcm.pitch);
    setYaw(_dcm.yaw);
    setRollRate(_dcm.get_gyro().x);
    setPitchRate(_dcm.get_gyro().y);
    setYawRate(_dcm.get_gyro().z);
    setXAccel(_dcm.get_accel().x);
    setYAccel(_dcm.get_accel().y);
    setZAccel(_dcm.get_accel().z);

    /*
     * accel/gyro debug
     */
    /*
     Vector3f accel = _board->getImu()->get_accel();
     Vector3f gyro = _board->getImu()->get_gyro();
     Serial.printf_P(PSTR("accel: %f %f %f gyro: %f %f %f\n"),
     accel.x,accel.y,accel.z,gyro.x,gyro.y,gyro.z);
     */
}

void Navigator_Dcm::updateSlow(float dt) {
    if (_board->getParameters().mode != AP_Board::MODE_LIVE)
        return;

    setTimeStamp(micros()); // if running in live mode, record new time stamp

    if (_board->getGps()) {
        _board->getGps()->update();
        updateGpsLight();
        if (_board->getGps()->fix && _board->getGps()->new_data) {
            setLat_degInt(_board->getGps()->latitude);
            setLon_degInt(_board->getGps()->longitude);
            setGroundSpeed(_board->getGps()->ground_speed / 100.0); // gps is in cm/s
        }
    }

    if (_board->getCompass()) {
        _board->getCompass()->read();
        _board->getCompass()->calculate(_dcm.get_dcm_matrix());
        _board->getCompass()->null_offsets(_dcm.get_dcm_matrix());
        //_board->getDebug()->printf_P(PSTR("heading: %f"), _board->getCompass()->heading);
    }
}
void Navigator_Dcm::updateGpsLight(void) {
    // GPS LED on if we have a fix or Blink GPS LED if we are receiving data
    // ---------------------------------------------------------------------
    static bool GPS_light = false;
    switch (_board->getGps()->status()) {
    case (2):
        //digitalWrite(C_LED_PIN, HIGH); //Turn LED C on when gps has valid fix.
        break;

    case (1):
        if (_board->getGps()->valid_read == true) {
            GPS_light = !GPS_light; // Toggle light on and off to indicate gps messages being received, but no GPS fix lock
            if (GPS_light) {
                digitalWrite(_board->getCLedPin(), LOW);
            } else {
                digitalWrite(_board->getCLedPin(), HIGH);
            }
            _board->getGps()->valid_read = false;
        }
        break;

    default:
        digitalWrite(_board->getCLedPin(), LOW);
        break;
    }
}

} // namespace apo
// vim:ts=4:sw=4:expandtab
