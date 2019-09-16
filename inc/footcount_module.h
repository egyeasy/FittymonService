/*
 * footcount.h
 *
 *  Created on: May 29, 2019
 *      Author: wjtjdrb
 */

#include "sensor.h"

#ifndef FOOTCOUNT_H_
#define FOOTCOUNT_H_

sensor_h footcount_module_sensor;
sensor_listener_h footcount_module_listener;

// check ability of pedometer
bool footcount_module_is_supported();
bool footcount_module_is_recorder_supported();

void footcount_module_start();
void footcount_module_setting_recorder();
void footcount_module_making_query();

// callback functions for counting and recording foot steps.
void footcount_module_sensor_callback(sensor_h sensor, sensor_event_s *event, void *user_data);

int footcount_module_getStepsCount();


#endif /* FOOTCOUNT_H_ */
