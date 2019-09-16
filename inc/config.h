/*
 * config.h
 *
 *  Created on: Jun 3, 2019
 *      Author: noblesse3539
 */

#ifndef CONFIG_H_
#define CONFIG_H_

typedef enum {
	TUTORIAL = 0,
	EGG,
	HATCHING,
	HAPPY,
	HUNGRY,
	DEAD,
} creature_state;

#define POST_PONE_TIME 			10000  	// 	12h == 43200sec
#define DEAD_TIME_AFTER_HUNGRY 	100000 	// 	72h == 259200sec
#define MAX_HAPPY_TIME			3600 	// 	30h == 108000sec
#define EXCHANGE_RATE			20   	// 	4000step == 1 fruit
#define HATCH_STEPS				5	//	hatching! on 5000step

#endif /* CONFIG_H_ */
