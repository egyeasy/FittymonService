/*
 * data_storage.c
 *
 *  Created on: Jun 3, 2019
 *      Author: noblesse3539
 */


#include "data_storage.h"

#include "config.h"
#include <app_preference.h>
#include <time.h>

#define KEY_TUTORIAL_TIME 		"key.tutorial.time"
#define KEY_HUNGRY_TIME 		"key.hungry.time"
#define KEY_DEATH_TIME 			"key.death_time"


#define KEY_CREATURE_STATE 		"key.creature.state"
#define KEY_TOTAL_STEPS 		"key.total.steps"
#define KEY_DAILY_STEPS 		"key.daily.steps"
#define KEY_CURRENCY_STEPS 		"key.currency.steps"
#define KEY_NUM_OF_FRUITS 		"key.num.of.fruits"

#define KEY_FLAG_TUTORIAL 		"key.flag.tutorial"
#define KEY_FLAG_NOTI_HUNGRY 	"key.flag.noti.hungry"
#define KEY_FLAG_NOTI_DYING 	"key.flag.noti.dying"
#define KEY_FLAG_NOTI_DEAD 		"key.flag.noti.dead"
#define KEY_FLAG_NOTI_HATCHING 	"key.flag.noti.hatching"

#define KEY_HATCHED_DATE		"key.hatched.date"

void data_storage_reset()
{
	preference_remove_all();
}

void data_storage_save_tutorial_start_time(long int tutorial_time)
{
	preference_set_double(KEY_TUTORIAL_TIME, tutorial_time);
}

long int data_storage_get_tutorial_start_time()
{
	double tutorial_time = -1;
	bool is_existing = false;

	preference_is_existing(KEY_TUTORIAL_TIME, &is_existing);
	if (is_existing)
		preference_get_double(KEY_TUTORIAL_TIME, &tutorial_time);

	return tutorial_time;
}

void data_storage_save_hungry_time(long int hungry_time)
{
	preference_set_double(KEY_HUNGRY_TIME, hungry_time);
}

long int data_storage_get_hungry_time()
{
	double hungry_time = -1;
	bool is_existing = false;

	preference_is_existing(KEY_HUNGRY_TIME, &is_existing);
	if (is_existing)
		preference_get_double(KEY_HUNGRY_TIME, &hungry_time);

	return hungry_time;
}

void data_storage_save_death_time(long int death_time)
{
	preference_set_double(KEY_DEATH_TIME, death_time);
}

long int data_storage_get_death_time()
{
	double death_time = -1;
	bool is_existing = false;

	preference_is_existing(KEY_DEATH_TIME, &is_existing);
	if (is_existing)
		preference_get_double(KEY_DEATH_TIME, &death_time);

	return death_time;
}

void data_storage_save_creature_state(int creature_state)
{
	preference_set_int(KEY_CREATURE_STATE, creature_state);
}

int data_storage_get_creature_state()
{
	int creature_state = TUTORIAL;
	bool is_existing = false;

	preference_is_existing(KEY_CREATURE_STATE, &is_existing);
	if (is_existing)
		preference_get_int(KEY_CREATURE_STATE, &creature_state);

	return creature_state;
}

void data_storage_save_total_steps(int total_steps)
{
	preference_set_int(KEY_TOTAL_STEPS, total_steps);
}

int data_storage_get_total_steps()
{
	int total_steps = 0;
	bool is_existing = false;

	preference_is_existing(KEY_TOTAL_STEPS, &is_existing);
	if (is_existing)
		preference_get_int(KEY_TOTAL_STEPS, &total_steps);

	return total_steps;
}

void data_storage_save_daily_steps(int daily_steps)
{
	preference_set_int(KEY_DAILY_STEPS, daily_steps);
}

int data_storage_get_daily_steps()
{
	int daily_steps = 0;
	bool is_existing = false;

	preference_is_existing(KEY_DAILY_STEPS, &is_existing);
	if (is_existing)
		preference_get_int(KEY_DAILY_STEPS, &daily_steps);

	return daily_steps;
}

void data_storage_save_currency_steps(int currency_steps)
{
	preference_set_int(KEY_CURRENCY_STEPS, currency_steps);
}

int data_storage_get_currency_steps()
{
	int currency_steps = 0;
	bool is_existing = false;

	preference_is_existing(KEY_CURRENCY_STEPS, &is_existing);
	if (is_existing)
		preference_get_int(KEY_CURRENCY_STEPS, &currency_steps);

	return currency_steps;
}

void data_storage_save_num_of_fruits(int num_of_fruits)
{
	preference_set_int(KEY_NUM_OF_FRUITS, num_of_fruits);
}

int data_storage_get_num_of_fruits()
{
	int num_of_fruits = 0;
	bool is_existing = false;

	preference_is_existing(KEY_NUM_OF_FRUITS, &is_existing);
	if (is_existing)
		preference_get_int(KEY_NUM_OF_FRUITS, &num_of_fruits);

	return num_of_fruits;
}

void data_storage_save_flag_tutorial(bool flag_tutorial)
{
	preference_set_int(KEY_FLAG_TUTORIAL, flag_tutorial);
}

bool data_storage_get_flag_tutorial()
{
	bool flag_tutorial = false;
	bool is_existing = false;

	preference_is_existing(KEY_FLAG_TUTORIAL, &is_existing);
	if (is_existing)
		preference_get_boolean(KEY_FLAG_TUTORIAL, &flag_tutorial);

	return flag_tutorial;
}

void data_storage_save_flag_noti_hungry(bool flag_noti_hungry)
{
	preference_set_boolean(KEY_FLAG_NOTI_HUNGRY, flag_noti_hungry);
}

bool data_storage_get_flag_noti_hungry()
{
	bool flag_noti_hungry = false;
	bool is_existing = false;

	preference_is_existing(KEY_FLAG_NOTI_HUNGRY, &is_existing);
	if (is_existing)
		preference_get_boolean(KEY_FLAG_NOTI_HUNGRY, &flag_noti_hungry);

	return flag_noti_hungry;
}

void data_storage_save_flag_noti_dying(bool flag_noti_dying)
{
	preference_set_boolean(KEY_FLAG_NOTI_DYING, flag_noti_dying);
}

bool data_storage_get_flag_noti_dying()
{
	bool flag_noti_dying = false;
	bool is_existing = false;

	preference_is_existing(KEY_FLAG_NOTI_DYING, &is_existing);
	if (is_existing)
		preference_get_boolean(KEY_FLAG_NOTI_DYING, &flag_noti_dying);

	return flag_noti_dying;
}

void data_storage_save_flag_noti_dead(bool flag_noti_dead)
{
	preference_set_boolean(KEY_FLAG_NOTI_DEAD, flag_noti_dead);
}

bool data_storage_get_flag_noti_dead()
{
	bool flag_noti_dead = false;
	bool is_existing = false;

	preference_is_existing(KEY_FLAG_NOTI_DEAD, &is_existing);
	if (is_existing)
		preference_get_boolean(KEY_FLAG_NOTI_DEAD, &flag_noti_dead);

	return flag_noti_dead;
}

void data_storage_save_flag_noti_hatching(bool flag_noti_hatching)
{
	preference_set_boolean(KEY_FLAG_NOTI_HATCHING, flag_noti_hatching);
}

bool data_storage_get_flag_noti_hatching()
{
	bool flag_noti_hatching = false;
	bool is_existing = false;

	preference_is_existing(KEY_FLAG_NOTI_HATCHING, &is_existing);
	if (is_existing)
		preference_get_boolean(KEY_FLAG_NOTI_HATCHING, &flag_noti_hatching);

	return flag_noti_hatching;
}

void data_storage_save_hatched_date(long int hatched_date)
{
	preference_set_double(KEY_HATCHED_DATE, hatched_date);
}

long int data_storage_get_hatched_date()
{
	double hatched_date = -1;
	bool is_existing = false;

	preference_is_existing(KEY_HATCHED_DATE, &is_existing);
	if (is_existing)
		preference_get_double(KEY_HATCHED_DATE, &hatched_date);

	return hatched_date;
}

/* business logic */
