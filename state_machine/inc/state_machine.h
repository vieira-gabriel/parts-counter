/** \file state_machine.h
 *  \brief State machine example header file.
 *
 *  This is the main source file of a fictitious firmware implementation as
 *  a state machine (automaton).
 *  \author Fernando C. Guimaraes
 *  \date 2020-12-11
 */

#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

#include <stdint.h>

#define STATE_FUNCTIONS_ARGS      int16_t *ex_data, int16_t *in_data
#define IN_BUFFER_SIZE            1
#define OUT_BUFFER_SIZE           2

typedef enum
{
   ST_NULL = 0,
   ST_LED_OFF,
   ST_LED_ON,
   ST_LED_PWM_SETUP,
   ST_LED_PWM_RUN,
   ST_EMERG_ON,
   ST_COUNT_0,
   ST_COUNT_1,
   ST_COUNT_2,
   ST_COUNT_3,
   ST_COUNT_4,
   ST_COUNT_5,
   ST_MOTOR_ON_HORARIO,
   ST_MOTOR_ON_ANTIHORARIO,
   ST_MOTOR_OFF,
   NUMBER_ST
} state_id;

typedef enum
{
   EV_NONE = 0,
   EV_LED_OFF,
   EV_LED_ON,
   EV_LED_PWM,
   EV_INTERNAL,
   EV_INTERNAL_LOCK,
   EV_NF_ON,
   EV_NF_OFF,
   EV_NA,
   EV_SENSOR_DETECT,
   EV_MOTOR_HORARIO,
   EV_MOTOR_ANTIHORARIO,
   NUMBER_EV
} event_id;

typedef struct
{
   state_id st_id;
   int (*state_exe)(STATE_FUNCTIONS_ARGS);
} state_handler;

// Public function used to tell the SM what the new incoming event is. It can be called by an interrupt
// function or a polling one responsible for inputs reading. External interrupts are triggered by
// rise or falling edges of GPIOs and other peripherals. The polling method only reads the GPIOs states
// at the reading moment.
int sm_set_event(event_id event);

// Public function used to setup whatever the SM needs (peripherals registers, memory allocation, etc.)
void sm_setup(void);

// Public function which executes the current state function.
int sm_run(void);

// Public function used to turn things off, to deallocate memory, etc.
void sm_close(void);


#endif /* STATE_MACHINE_H_ */
