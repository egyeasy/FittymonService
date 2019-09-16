#include <config.h>
#include <data_storage.h>
#include <footcount_module.h>
#include <system_settings.h>
#include <Ecore.h>
#include <time.h>
#include <dlog.h>
#include "vibration_module.h"
#include "notification_module.h"

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "Geargotchi.Service"

static int countCalls = 0;
static int lastSteps = -1;


void set_noti_flags(long int current_time);

Eina_Bool timerEventCallback(void *data)
{
	long int hungry_time = data_storage_get_hungry_time();
	long int death_time = data_storage_get_death_time();
	int creature_state = data_storage_get_creature_state();
	int total_steps = data_storage_get_total_steps();
	int currency_step = data_storage_get_currency_steps();
	int daily_steps = data_storage_get_daily_steps();
	int num_of_fruits = data_storage_get_num_of_fruits();
	bool flag_tutorial = data_storage_get_flag_tutorial();
	bool flag_noti_hungry = data_storage_get_flag_noti_hungry();
	bool flag_noti_dying = data_storage_get_flag_noti_dying();
	bool flag_noti_dead = data_storage_get_flag_noti_dead();
	bool flag_noti_hatching = data_storage_get_flag_noti_hatching();
	int hatched_date = data_storage_get_hatched_date();
	long int current_time = time(NULL);

	set_noti_flags(current_time);
	// not to count if it is in tutorial
	if (creature_state == TUTORIAL) {
		return ECORE_CALLBACK_RENEW;
	}

	// check steps
	dlog_print(DLOG_DEBUG, "LIM_TAG", "Start infinite routine, count calls: %d", countCalls++);
	footcount_module_making_query();
	int currentSteps = footcount_module_getStepsCount();
	dlog_print(DLOG_FATAL, "LIM_TAG", "current steps in footcount module: %d", currentSteps);

	/*if (lastSteps == -1)
	{
		// Init
		lastSteps = currentSteps;
		dlog_print(DLOG_DEBUG, "LIM_TAG", "INIT currentStep : %d", currentSteps);
	}
	else // if not tutorial*/
	{
		int difference = data_storage_get_total_steps() - data_storage_get_currency_steps();
		dlog_print(DLOG_DEBUG, "LIM_TAG", "difference in steps : %d", difference);
		//lastSteps = currentSteps;
		// TODO: dailysteps count(maybe it isn't necessary)
		data_storage_save_total_steps(currentSteps);
		data_storage_save_currency_steps(currentSteps - difference);
		//data_storage_save_currency_steps(data_storage_get_currency_steps() + difference);
		//data_storage_save_total_steps(data_storage_get_total_steps() + difference);
		dlog_print(DLOG_DEBUG, "LIM_TAG", "get currency step : %d", data_storage_get_currency_steps());
		dlog_print(DLOG_DEBUG, "LIM_TAG", "get total step : %d", data_storage_get_total_steps());
	}
	dlog_print(DLOG_DEBUG, "LIM_TAG", "currentSteps : %d", currentSteps);

	/* transition logic */
	// TODO: change to switch statement
	dlog_print(DLOG_DEBUG, "LIM_TAG", "currentState: %d, currentTime: %ld, hungrytime: %ld, deathtime: %ld", creature_state, current_time, hungry_time, death_time);
    // egg -> hatching logic
    time_t nowTime = time(NULL);
    if (creature_state == EGG && data_storage_get_total_steps() >= HATCH_STEPS && !data_storage_get_flag_noti_hatching())
    {
        vibration_module_vibro(LONG);
        notification_module_send_notification("Hurry up!", "Your Fittymon is Hatching!");
        data_storage_save_flag_noti_hatching(true);
//        creature_state = HATCHING;
        data_storage_save_creature_state(HATCHING);
    }
	// happy -> HUNGRY
	else if (creature_state == HAPPY && nowTime >= hungry_time && !data_storage_get_flag_noti_hungry())
	{
		creature_state = HUNGRY;
		data_storage_save_creature_state(creature_state);

        vibration_module_vibro(LONG);
        notification_module_send_notification( "I'm hungry!!", "Feed me, Plz!!" );
        data_storage_save_flag_noti_hungry(true);
	}
    // hungry & dying
	else if (creature_state == HUNGRY && !data_storage_get_flag_noti_dying() && current_time + POST_PONE_TIME > death_time)
	{
        vibration_module_vibro(LONG);
        notification_module_send_notification( "I'm starving....", "Feed me....." );
        data_storage_save_flag_noti_dying(true);
	}
	// HUNGRY -> dead
	else if (creature_state == HUNGRY && nowTime >= death_time)
	{
		creature_state = DEAD;
		data_storage_save_creature_state(creature_state);

        vibration_module_vibro(LONG);
        notification_module_send_notification( "Walky's left us..", "Press f to Pay Respects." );
        data_storage_save_flag_noti_hungry(true);
	}

    double leftToHungryModeTime = hungry_time - nowTime;
    double leftToDeathModeTime = death_time - nowTime;

    dlog_print(DLOG_DEBUG, LOG_TAG, "Left seconds to hungry mode: %.0f", leftToHungryModeTime);
    dlog_print(DLOG_DEBUG, LOG_TAG, "Left seconds to dead mode: %.0f", leftToDeathModeTime);

	return ECORE_CALLBACK_RENEW;

}

void set_noti_flags(long int current_time)
{
	if (current_time < data_storage_get_hungry_time())
	{
		data_storage_save_flag_noti_hungry(false);
		data_storage_save_flag_noti_dying(false);
	}
	else if (current_time + POST_PONE_TIME < data_storage_get_death_time())
	{
		data_storage_save_flag_noti_dying(false);
	}
}
