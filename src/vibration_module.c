/*
 * vibration_module.c
 *
 *  Created on: May 31, 2019
 *      Author: noblesse3539
 */

#include "vibration_module.h"

#include <feedback.h>
#include <device/haptic.h>


// msec values
static haptic_device_h handle;

void vibration_module_init_haptic()
{
	device_haptic_open(0, &handle);
}

void vibration_module_release_haptic()
{
	device_haptic_close(handle);
}

void vibration_module_vibro(int duration)
{
	int error;
	haptic_effect_h effect_handle;
	error = device_haptic_vibrate(handle, duration, 50, &effect_handle);

}
