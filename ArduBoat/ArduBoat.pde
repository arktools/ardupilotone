// Libraries
#include <FastSerial.h>
#include <DataFlash.h>
#include <SPI.h>
#include <AP_Math.h>
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
#include <Arduino_Mega_ISR_Registry.h>
#include <AP_PeriodicProcess.h>

// Vehicle Configuration
//#include "BoatGeneric.h"
#include "SailboatLaser.h"

// ArduPilotOne Default Setup
#include "APO_DefaultSetup.h"
