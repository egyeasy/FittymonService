/*
 * data_storage.h
 *
 *  Created on: Jun 3, 2019
 *      Author: noblesse3539
 */

#ifndef DATA_STORAGE_H_
#define DATA_STORAGE_H_

#include <system_settings.h>
#include <time.h>

void data_storage_reset();

void data_storage_save_tutorial_start_time(long int tutorial_time);
long int data_storage_get_tutorial_start_time();

void data_storage_save_hungry_time(long int hungry_time);
long int data_storage_get_hungry_time();

void data_storage_save_death_time(long int death_time);
long int data_storage_get_death_time();

void data_storage_save_creature_state(int creature_state);
int data_storage_get_creature_state();

void data_storage_save_total_steps(int total_steps);
int data_storage_get_total_steps();

void data_storage_save_currency_steps(int currency_step);
int data_storage_get_currency_steps();

void data_storage_save_daily_steps(int daily_steps);
int data_storage_get_daily_steps();

void data_storage_save_num_of_fruits(int num_of_fruits);
int data_storage_get_num_of_fruits();

void data_storage_save_flag_tutorial(bool flag_tutorial);
bool data_storage_get_flag_tutorial();

void data_storage_save_flag_noti_hungry(bool flag_noti_hungry);
bool data_storage_get_flag_noti_hungry();

void data_storage_save_flag_noti_dying(bool flag_noti_dying);
bool data_storage_get_flag_noti_dying();

void data_storage_save_flag_noti_dead(bool flag_noti_dead);
bool data_storage_get_flag_noti_dead();

void data_storage_save_flag_noti_hatching(bool flag_noti_hatching);
bool data_storage_get_flag_noti_hatching();

void data_storage_save_hatched_date(long int hatched_date);
long int data_storage_get_hatched_date();

#endif /* DATA_STORAGE_H_ */
