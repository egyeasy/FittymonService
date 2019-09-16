/*
 * footcount.c
 *
 *  Created on: May 29, 2019
 *      Author: wjtjdrb
 */

#include <sensor.h>
#include <dlog.h>
#include <footcount_module.h>
#include "data_storage.h"
// STEPS means the values that will be used in getStepsCount(); tmpnum is just to use temporarily check and test.
int STEPS = -1;
sensor_recorder_option_h option;

// this function is callback function of footstep. if count of footstep is changed, you can see the count in log.
void
footcount_module_sensor_callback(sensor_h footcount_module_sensor, sensor_event_s *event, void *user_data)
{
	/*dlog_print(DLOG_DEBUG, "RACCOON", "START CALLBACK");
    sensor_type_e type;
    sensor_get_type(footcount_module_sensor, &type);
    if (type == SENSOR_HUMAN_PEDOMETER) {
        float x = event->values[0]; // numbers of steps
		dlog_print(DLOG_DEBUG, "RACCOON", "Steps %d", (int)x);
		STEPS = (int)x;

    }*/
}

// To check whether the pedometer is supported
bool
footcount_module_is_supported() {

	bool is_supported = false;
	sensor_is_supported(SENSOR_HUMAN_PEDOMETER, &is_supported);


   if (is_supported) {
	   dlog_print(DLOG_DEBUG, "RACCOON", "connection to pedometer is succeed");
   } else {
	   dlog_print(DLOG_DEBUG, "RACCOON", "connection to pedometer is failed");
   }

	return is_supported;
}


// this function is callback function of recorded footstep. so, when starting app, you can see the recorded count in log
int call = 0;
static bool
footcount_module_sensor_recorder_callback(sensor_type_e type, sensor_recorder_data_h data, int remains, sensor_error_e error, void *user_data)
{
	call++;
	int step;
	time_t start;
	time_t end;

	if (error != SENSOR_ERROR_NONE) return false;

	sensor_recorder_data_get_time(data, &start, &end);

	sensor_recorder_data_get_int(data, SENSOR_RECORDER_DATA_STEPS, &step);

	// TODO: comment below line to test without walking
	STEPS = step;
	dlog_print(DLOG_DEBUG, "RACCOON", "steps: %d. call: %d", step, call);

	return true;
}


// To check whether recording the pedometer is supported.
bool
footcount_module_is_recorder_supported() {
	bool supported = false;

	sensor_recorder_is_supported(SENSOR_HUMAN_PEDOMETER, &supported);
	if (supported) {
		dlog_print(DLOG_DEBUG, "RACCOON", "You can record pedometer");
	} else {
		dlog_print(DLOG_DEBUG, "RACCOON", "You can not record pedometer");
	}
	return supported;
}

// it will make sensor and listener of pedometer and start listening.
void
footcount_module_start() {
	if (footcount_module_is_supported()) {
		int result = sensor_get_default_sensor(SENSOR_HUMAN_PEDOMETER, &footcount_module_sensor);
		dlog_print(DLOG_DEBUG, "RACCOON", "SENSOR result = %d", result);
		result = sensor_create_listener(footcount_module_sensor, &footcount_module_listener);
		dlog_print(DLOG_DEBUG, "RACCOON", "LISTENER result = %d", result);

		result = sensor_listener_set_event_cb(footcount_module_listener, 1000, footcount_module_sensor_callback, NULL);
		dlog_print(DLOG_DEBUG, "RACCOON", "CALLBACK result = %d", result);
		result = sensor_listener_start(footcount_module_listener);
		dlog_print(DLOG_DEBUG, "RACCOON", "START result = %d", result);
	 }
}

// this function will set some option of recording the pedomenter
void
footcount_module_setting_recorder() {
   // set option of record
	if (footcount_module_is_recorder_supported()) {
		sensor_recorder_create_option(&option);
		// 30 * 24 -> the record will remain in a month(30 * 24 hour)
		sensor_recorder_option_set_int(option, SENSOR_RECORDER_OPTION_RETENTION_PERIOD, 30 * 24);
		sensor_recorder_start(SENSOR_HUMAN_PEDOMETER, option);
	}
}

// this function will make a query and read the record.
void
footcount_module_making_query() {
	call = 0;
	sensor_recorder_query_h query;
	sensor_recorder_create_query(&query);
	// start time is a days ago ( 3600 sec(1hour) * 24 == 1 day )
	dlog_print(DLOG_FATAL, "LIM_TAG", "Making steps querry from %d till %d", data_storage_get_tutorial_start_time(), time(NULL));
	sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_START_TIME, (time_t)data_storage_get_tutorial_start_time());
	sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_END_TIME, time(NULL));
	sensor_recorder_query_set_int(query, SENSOR_RECORDER_QUERY_TIME_INTERVAL, 24 * 60);
	// the time when a day starts is 4 AM ( 4 * 3600 sec ( 1hour ))
	sensor_recorder_query_set_time(query, SENSOR_RECORDER_QUERY_ANCHOR_TIME, (time_t)(4 * 3600));
	sensor_recorder_read(SENSOR_HUMAN_PEDOMETER, query, footcount_module_sensor_recorder_callback, NULL);
}
#include <stdlib.h>
int
footcount_module_getStepsCount() {
	// TODO: uncomment to test without walking
	//STEPS += (rand() % 15);
	return STEPS;
}
