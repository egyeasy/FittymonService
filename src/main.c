#include <tizen.h>
#include <service_app.h>
#include <dlog.h>
#include <display.h>
#include <app_alarm.h>
#include <unistd.h>
#include <Ecore.h>
#include <footcount_module.h>
#include <continuous_callback.h>
#include "vibration_module.h"
#include "config.h"
#include "data_storage.h"

static Ecore_Timer *timer;
static Ecore_Timer *displayOnTimer;
static int c_state;
static int alarm_id;

Eina_Bool displayOnCallback(void *Data)
{
	// FIXME: if certification will fail. remove highlight

	/* blink when creature state is EGG only. */
	c_state = data_storage_get_creature_state();
	if (c_state == EGG)
	{
		display_state_e state;
		device_display_get_state(&state);
		if (state == DISPLAY_STATE_SCREEN_OFF)
		{
			device_display_change_state(DISPLAY_STATE_NORMAL);
		}
		device_display_change_state(state);
	}

	return ECORE_CALLBACK_RENEW;
}

/*static void init_alarm()
{
    int ret;
    int DELAY = 10;

    dlog_print(DLOG_ERROR, "LIM_TAG", "ALARM_ERROR_NONE %d", ALARM_ERROR_NONE);
    dlog_print(DLOG_ERROR, "LIM_TAG", "ALARM_ERROR_INVALID_PARAMETER %d", ALARM_ERROR_INVALID_PARAMETER);
    dlog_print(DLOG_ERROR, "LIM_TAG", "ALARM_ERROR_INVALID_TIME %d", ALARM_ERROR_INVALID_TIME);
    dlog_print(DLOG_ERROR, "LIM_TAG", "ALARM_ERROR_CONNECTION_FAIL %d", ALARM_ERROR_CONNECTION_FAIL);
    dlog_print(DLOG_ERROR, "LIM_TAG", "ALARM_ERROR_NOT_PERMITTED_APP %d", ALARM_ERROR_NOT_PERMITTED_APP);
    dlog_print(DLOG_ERROR, "LIM_TAG", "ALARM_ERROR_PERMISSION_DENIED %d", ALARM_ERROR_PERMISSION_DENIED);

    app_control_h app_control = NULL;
    ret = app_control_create(&app_control);
	dlog_print(DLOG_INFO, "LIM_TAG", "app_control_create %d", ret);
    ret = app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	dlog_print(DLOG_INFO, "LIM_TAG", "app_control_set_operation %d", ret);
    ret = app_control_set_app_id(app_control, "org.geargotchi.game.ui");
	dlog_print(DLOG_INFO, "LIM_TAG", "app_control_set_app_id %d", ret);

	ret = alarm_schedule_once_after_delay(app_control, DELAY, &alarm_id);
	dlog_print(DLOG_INFO, "LIM_TAG", "alarm_schedule_after_delay %d", ret);
}*/

bool service_app_create(void *data)
{
	dlog_print(DLOG_INFO, "LIM_TAG", "Service app create callback");
//	dlog_print(DLOG_DEBUG, "LIM_TAG", "Start infinite routine, count calls: %d", countCalls);
	footcount_module_setting_recorder();
	vibration_module_init_haptic();
	//footcount_module_start();
	timerEventCallback(NULL);
	timer = ecore_timer_add(2, timerEventCallback, NULL);
	// TODO: set time to 10 minute when publish app to market
	displayOnTimer = ecore_timer_add(60 * 10, displayOnCallback, NULL);
//	ecore_timer_del(timer);

    return true;
}

void service_app_terminate(void *data)
{
	ecore_timer_del(timer);
	ecore_timer_del(displayOnTimer);
	vibration_module_release_haptic();
	dlog_print(DLOG_DEBUG, "LIM_TAG", "terminating service");
    return;
}

void service_app_control(app_control_h app_control, void *data)
{
	dlog_print(DLOG_INFO, "LIM_TAG", "Service app control callback");
	//init_alarm();
}

int main(int argc, char* argv[])
{
	service_app_lifecycle_callback_s event_callback;

	event_callback.create = service_app_create;
	event_callback.terminate = service_app_terminate;
	event_callback.app_control = service_app_control;

	return service_app_main(argc, argv, &event_callback, NULL);
}

/* instant logic */
//void data_storage_feeding()
//{
//	double hungry_time = data_storage_get_hungry_time();
//
//	if(hungry_time - time(NULL) >= (MAX_HAPPY_TIME - POST_PONE_TIME))
//		data_storage_save_hungry_time(time(NULL)+ MAX_HAPPY_TIME);
//	else
//		data_storage_save_hungry_time(hungry_time + POST_PONE_TIME);
//}
//
//void data_storage_reset() // at hatching!!
//{
//	time_t c_time = time(NULL);
//	data_storage_save_creature_state(HAPPY);
//	data_storage_save_hatched_date(c_time);
//	data_storage_save_hungry_time(c_time + POST_PONE_TIME);
//	data_storage_save_total_steps(0);
//	data_storage_save_currency_steps(0);
//	data_storage_save_daily_steps(0);
//	data_storage_save_death_time(data_storage_get_hungry_time() + DEAD_TIME_AFTER_HUNGRY);
//	data_storage_save_num_of_fruits(0);
//}
//
//bool data_storage_is_exchangable()
//{
//	return data_storage_get_currency_steps() >= EXCHANGE_RATE;
//}
//
//bool data_storage_buy_fruit()
//{
//	if (data_storage_is_exchangable())
//	{
//		data_storage_save_currency_steps(data_storage_get_currency_steps() - EXCHANGE_RATE);
//		data_storage_save_num_of_fruits(data_storage_get_num_of_fruits()+1);
//		return true;
//	}
//	return false;
//}
