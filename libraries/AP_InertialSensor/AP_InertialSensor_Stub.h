/// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-

#ifndef __AP_INERTIAL_SENSOR_STUB_H__
#define __AP_INERTIAL_SENSOR_STUB_H__

#include <string.h>
#include <stdint.h>

#include "../AP_PeriodicProcess/AP_PeriodicProcess.h"
#include "AP_InertialSensor.h"

class AP_InertialSensor_Stub : public AP_InertialSensor
{
  public:

  AP_InertialSensor_Stub(AP_PeriodicProcess * scheduler) : AP_InertialSensor(scheduler) {}

  /* Concrete implementation of AP_InertialSensor functions: */
  bool update();
  bool new_data_available();
  float gx();
  float gy();
  float gz();
  void get_gyros( float * );
  float ax();
  float ay();
  float az();
  void get_accels( float * );
  void get_sensors( float * );
  float temperature();
  uint32_t sample_time();
  void reset_sample_time();
<<<<<<< HEAD
  float get_gyro_drift_rate();
  };
=======
};
>>>>>>> 855e82a7f010266ec705e471f1847240f27d2615

#endif // __AP_INERTIAL_SENSOR_STUB_H__
