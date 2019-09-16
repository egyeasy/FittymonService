/*
 * notification_module.c
 *
 *  Created on: May 31, 2019
 *      Author: noblesse3539
 */

#include "notification_module.h"
#include <app_control.h>
#include <notification.h>


void notification_module_send_notification(char *title, char *body) {
	notification_h notification = NULL;
	app_control_h control = NULL;
	int noti_err = NOTIFICATION_ERROR_NONE;
	char *app_id = NULL;

	notification = notification_create(NOTIFICATION_TYPE_NOTI);
	if (notification == NULL) return;

	/* Notification was initialized successfully */
	noti_err = notification_set_text(notification, NOTIFICATION_TEXT_TYPE_TITLE, title, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	noti_err = notification_set_text(notification, NOTIFICATION_TEXT_TYPE_CONTENT, body, NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	noti_err = notification_set_vibration(notification, NOTIFICATION_VIBRATION_TYPE_DEFAULT, NULL);
	app_control_create(&control);

	app_control_set_app_id(control, "org.geargotchi.game.ui");
	noti_err = notification_set_launch_option(notification, NOTIFICATION_LAUNCH_OPTION_APP_CONTROL, control);

	if (noti_err == NOTIFICATION_ERROR_NONE)
		noti_err = notification_post(notification);

	app_control_destroy(control);
	notification_free(notification);
}

