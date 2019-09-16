/*
 * vibration_module.h
 *
 *  Created on: May 31, 2019
 *      Author: noblesse3539
 */

#ifndef VIBRATION_MODULE_H_
#define VIBRATION_MODULE_H_

#define SHORT 250
#define MEDIUM 500
#define LONG 1000

void vibration_module_init_haptic(); // use in resume
void vibration_module_release_haptic(); // use in pause
void vibration_module_vibro(int duration);

#endif /* VIBRATION_MODULE_H_ */
