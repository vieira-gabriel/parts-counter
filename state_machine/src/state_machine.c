/** \file state_machine.c
 *  \brief State machine example source file.
 *
 *  This is the main source file of a fictitious firmware implementation as
 *  a state machine (automaton).
 *  \author Fernando C. Guimaraes
 *  \date 2020-12-11
 */
#include <dev_helper.h>
#include <state_machine.h>

/********************* Declaration of function headers ****************************/

// Private LED_OFF state function declaration.
static int st_led_off(STATE_FUNCTIONS_ARGS);

// Private LED_ON state function declaration.
static int st_led_on(STATE_FUNCTIONS_ARGS);

// Private LED_PWM_SETUP (internal) state function declaration.
static int st_led_pwm_setup(STATE_FUNCTIONS_ARGS);

// Private LED_PWM_RUN (internal) state function declaration.
static int st_led_pwm_run(STATE_FUNCTIONS_ARGS);

static int st_count_0(STATE_FUNCTIONS_ARGS);

static int st_count_1(STATE_FUNCTIONS_ARGS);

static int st_count_2(STATE_FUNCTIONS_ARGS);

static int st_count_3(STATE_FUNCTIONS_ARGS);

static int st_count_4(STATE_FUNCTIONS_ARGS);

static int st_count_5(STATE_FUNCTIONS_ARGS);

static int st_count_stop(STATE_FUNCTIONS_ARGS);

static int st_motor_on_horario(STATE_FUNCTIONS_ARGS);

static int st_motor_on_antiorario(STATE_FUNCTIONS_ARGS);

static int st_motor_off(STATE_FUNCTIONS_ARGS);

static int st_emerg_on(STATE_FUNCTIONS_ARGS);

// Declaration of a private 'get' function used to return the last event.
static event_id sm_private_get_event(void);

// Declaration of a private 'set' function used by internal states to allow
// external events recognition.
static void sm_private_set_event(event_id event);

/********************* Global variables *******************************************/

static event_id _event = EV_NONE; // current event
static state_id _led_state = ST_LED_OFF; // initial state of led (it could be declared inside sm_run)
static state_id _motor_state = ST_MOTOR_ON_HORARIO; // initial state of motor (it could be declared inside sm_run)
static state_id _count_state = ST_COUNT_0; // initial state of count (it could be declared inside sm_run)

// Function pointers array
// ----> Change this array accordingly to your automaton model
const static state_handler state_handler_container[NUMBER_ST] =
{
   [ST_LED_OFF] = {ST_LED_OFF, st_led_off},
   [ST_LED_ON]  = {ST_LED_ON, st_led_on},
   [ST_LED_PWM_SETUP] = {ST_LED_PWM_SETUP, st_led_pwm_setup},
   [ST_LED_PWM_RUN] = {ST_LED_PWM_RUN, st_led_pwm_run},
   [ST_COUNT_0] = {ST_COUNT_0, st_count_0},
   [ST_COUNT_1] = {ST_COUNT_1, st_count_1},
   [ST_COUNT_2] = {ST_COUNT_2, st_count_2},
   [ST_COUNT_3] = {ST_COUNT_3, st_count_3},
   [ST_COUNT_4] = {ST_COUNT_4, st_count_4},
   [ST_COUNT_5] = {ST_COUNT_5, st_count_5},
   [ST_COUNT_STOP] = {ST_COUNT_STOP, st_count_stop},
   [ST_MOTOR_ON_HORARIO] = {ST_MOTOR_ON_HORARIO, st_motor_on_horario},
   [ST_MOTOR_ON_ANTIHORARIO] = {ST_MOTOR_ON_ANTIHORARIO, st_motor_on_antiorario},
   [ST_MOTOR_OFF] = {ST_MOTOR_OFF, st_motor_off},
   [ST_EMERG_ON] = {ST_EMERG_ON, st_emerg_on}
};


/********************* Implementation of functions *************************************/

/********************* State functions *************************************************/

// ----> Implement your own state functions

// Private LED_OFF state function implementation.
static int st_led_off(STATE_FUNCTIONS_ARGS)
{
   PDEBUGY("sm_led_off execution\n");

   // Configure GPIO and set its output to 0.
   // Return -1 if something goes wrong.

   return 0;
}


// Private LED_ON state function implementation.
static int st_led_on(STATE_FUNCTIONS_ARGS)
{
   PDEBUGY("sm_led_on execution\n");

   // Configure GPIO and set its output to 1.
   // Return -1 if something goes wrong.

   return 0;
}

// Private LED_PWM_SETUP (internal) state function implementation.
static int st_led_pwm_setup(STATE_FUNCTIONS_ARGS)
{
   PDEBUGY("st_led_pwm_setup execution\n");

   // Get PWM period and duty cycle from ext_data buffer
   // Configure GPIO, set the initial values of variables (and put them into in_data buffer), etc.
   // Return -1 if something goes wrong.

   // 'lock' the SM in order to execute the next internal state (ST_LED_PWM_RUN) independently of
   // new incoming events from 'outside' (which are all discarded).
   sm_private_set_event(EV_INTERNAL_LOCK);
   if(sm_run() < 0) {
      printf("\nFatal error!\n");
      return -1;
   }

   return 0;
}

// Private LED_PWM_RUN (internal) state function implementation.
static int st_led_pwm_run(STATE_FUNCTIONS_ARGS)
{
   PDEBUGY("sm_led_pwm_run execution\n");

   // Count the number of delay intervals and toggle the GPIO accordingly (also setting the counter to 0).
   // The value of the delays counter is shared across multiple executions by saving it in_data buffer.
   // Return -1 if something goes wrong.

   // 'unlock' the SM. If no external event occurs, it keeps executing this state, in order to periodically
   // toggle the GPIO.
   sm_private_set_event(EV_INTERNAL);

   return 0;
}

static int st_count_0(STATE_FUNCTIONS_ARGS)
{
   PDEBUGY("st_count_0 execution\n");
   return 0;
}

static int st_count_1(STATE_FUNCTIONS_ARGS)
{
   PDEBUGY("st_count_1 execution\n");
   return 0;
}

static int st_count_2(STATE_FUNCTIONS_ARGS)
{
   PDEBUGY("st_count_2 execution\n");
   return 0;
}

static int st_count_3(STATE_FUNCTIONS_ARGS)
{
   PDEBUGY("st_count_3 execution\n");
   return 0;
}

static int st_count_4(STATE_FUNCTIONS_ARGS)
{
   PDEBUGY("st_count_4 execution\n");
   return 0;
}

static int st_count_5(STATE_FUNCTIONS_ARGS)
{
   PDEBUGY("st_count_5 execution\n");
   sm_private_set_event(EV_LED_PWM);
   if(sm_run() < 0) {
      printf("\nFatal error!\n");
      return -1;
   }
   else{
      sm_private_set_event(EV_NONE);
      if(sm_run() < 0) {
         printf("\nFatal error!\n");
         return -1;
      }
   }
   return 0;
}


static int st_count_stop(STATE_FUNCTIONS_ARGS)
{
   PDEBUGY("st_count_stop execution\n");
   return 0;
}

static int st_motor_on_horario(STATE_FUNCTIONS_ARGS)
{
   PDEBUGY("st_motor_on_horario execution\n");
   return 0;
}

static int st_motor_on_antihorario(STATE_FUNCTIONS_ARGS)
{
   PDEBUGY("st_motor_on_antihorario execution\n");
   return 0;
}

static int st_motor_off(STATE_FUNCTIONS_ARGS)
{
   PDEBUGY("st_motor_off execution\n");
   return 0;
}

static int st_emerg_on(STATE_FUNCTIONS_ARGS)
{
   PDEBUGY("st_emerg_on execution\n");
   return 0;
}

/********************* 'get' and 'set' functions *********************************************/

// sm_private_get_event implementation.
static event_id sm_private_get_event(void)
{
   event_id new_event;

   PDEBUG("sm_private_get_event execution\n");

   // Read the current event and reset it.
   new_event = _event;
   _event = EV_NONE;

   return new_event;
}

// sm_private_set_event implementation.
static void sm_private_set_event(event_id event)
{
   PDEBUG("sm_private_set_event execution\n");

   // The value of event is not checked in this private 'set' function. The SM programmers should know what
   // they're doing.
   _event = event;
}

// sm_set_event implementation.
int sm_set_event(event_id event)
{
   int ret = -1; // return -1 if event is ignored.

   PDEBUG("sm_set_event_event execution\n");

   // First check if event value is valid. Obs.: EV_NONE is not recognized because it would be useless.
   if((event > 0) && (event < NUMBER_EV)) {
      // 1st condition: if current event is internal and 'locking', ignore the external event.
      // 2nd condition: block an external attempt to 'lock' the SM.
      if((_event != EV_INTERNAL_LOCK) && (event != EV_INTERNAL_LOCK)) {
         _event = event;
         ret = 0;
      }
   }
   // Of course, all conditions can be put in one single 'if'.

   return ret;
}

/********************* Public SM functions *********************************************/

// sm_setup implementation.
void sm_setup(void)
{
   // Nothing to do in this fictitious firmware, just print a msg.
   PDEBUG("sm_setup execution\n");
}

// sm_run implementation
int sm_run(void)
{
   int ret = 0;
   event_id event = EV_NONE;
   state_id next_led_state = _led_state; // Current state for LED
   state_id next_motor_state = _motor_state; // Current state for motor
   state_id next_count_state = _count_state; // Current state for count

   // Dynamic memory allocation could be used (in setup function), but for microcontrollers with
   // bare-metal, monolithic firmware, this is usually better.
   static int16_t ex_data[OUT_BUFFER_SIZE];
   static int16_t in_data[IN_BUFFER_SIZE];

   // Transition function array: given a state and an event, it returns the next state.
   // Be careful! The events ordering defined in 'typedef enum event_id' must be obeyed.
   // ----> Change this transition function accordingly to your automaton model!
   const static state_id f[NUMBER_ST][NUMBER_EV] =
   {
      [ST_LED_OFF]       = {ST_NULL, ST_LED_OFF, ST_LED_ON, ST_LED_PWM_SETUP, ST_NULL, ST_NULL, ST_EMERG_ON, ST_LED_OFF, ST_LED_ON, ST_NULL, ST_NULL, ST_NULL},
      [ST_LED_ON]        = {ST_NULL, ST_LED_OFF, ST_LED_ON, ST_LED_PWM_SETUP, ST_NULL, ST_NULL, ST_EMERG_ON, ST_LED_OFF, ST_LED_ON, ST_NULL, ST_NULL, ST_NULL},
      [ST_LED_PWM_SETUP] = {ST_NULL, ST_NULL, ST_NULL, ST_NULL, ST_NULL, ST_LED_PWM_RUN, ST_EMERG_ON, ST_LED_OFF, ST_NULL, ST_NULL, ST_NULL, ST_NULL},
      [ST_LED_PWM_RUN]   = {ST_NULL, ST_LED_OFF, ST_NULL, ST_LED_PWM_RUN, ST_LED_PWM_RUN, ST_NULL, ST_EMERG_ON, ST_LED_OFF, ST_LED_PWM_RUN, ST_NULL, ST_NULL, ST_NULL},
      [ST_EMERG_ON]      = {ST_NULL, ST_EMERG_ON, ST_EMERG_ON, ST_EMERG_ON, ST_EMERG_ON, ST_EMERG_ON, ST_EMERG_ON, ST_LED_OFF, ST_EMERG_ON, ST_EMERG_ON, ST_EMERG_ON, ST_EMERG_ON},
      [ST_COUNT_0]       = {ST_NULL, ST_NULL, ST_NULL, ST_NULL, ST_NULL, ST_NULL, ST_COUNT_STOP, ST_COUNT_0, ST_COUNT_0, ST_COUNT_1, ST_NULL, ST_NULL},
      [ST_COUNT_1]       = {ST_NULL, ST_NULL, ST_NULL, ST_NULL, ST_NULL, ST_NULL, ST_COUNT_STOP, ST_COUNT_1, ST_COUNT_1, ST_COUNT_2, ST_NULL, ST_NULL},
      [ST_COUNT_2]       = {ST_NULL, ST_NULL, ST_NULL, ST_NULL, ST_NULL, ST_NULL, ST_COUNT_STOP, ST_COUNT_2, ST_COUNT_2, ST_COUNT_3, ST_NULL, ST_NULL},
      [ST_COUNT_3]       = {ST_NULL, ST_NULL, ST_NULL, ST_NULL, ST_NULL, ST_NULL, ST_COUNT_STOP, ST_COUNT_3, ST_COUNT_3, ST_COUNT_4, ST_NULL, ST_NULL},
      [ST_COUNT_4]       = {ST_NULL, ST_NULL, ST_NULL, ST_NULL, ST_NULL, ST_NULL, ST_COUNT_STOP, ST_COUNT_4, ST_COUNT_4, ST_COUNT_5, ST_NULL, ST_NULL},
      [ST_COUNT_5]       = {ST_NULL, ST_NULL, ST_NULL, ST_NULL, ST_NULL, ST_NULL, ST_COUNT_STOP, ST_COUNT_5, ST_COUNT_0, ST_COUNT_5, ST_NULL, ST_NULL},
      [ST_COUNT_STOP]    = {ST_NULL, ST_NULL, ST_NULL, ST_NULL, ST_NULL, ST_NULL, ST_COUNT_STOP, ST_COUNT_STOP, ST_COUNT_0, ST_NULL, ST_NULL, ST_NULL},
      [ST_MOTOR_ON_HORARIO]    = {ST_NULL, ST_NULL, ST_NULL, ST_NULL, ST_NULL, ST_NULL, ST_MOTOR_OFF, ST_MOTOR_OFF, ST_MOTOR_ON_HORARIO, ST_NULL, ST_MOTOR_ON_HORARIO, ST_MOTOR_ON_ANTIHORARIO},
      [ST_MOTOR_ON_ANTIHORARIO]    = {ST_NULL, ST_NULL, ST_NULL, ST_NULL, ST_NULL, ST_NULL, ST_MOTOR_OFF, ST_MOTOR_OFF, ST_MOTOR_ON_ANTIHORARIO, ST_NULL, ST_MOTOR_ON_HORARIO, ST_MOTOR_ON_ANTIHORARIO},
      [ST_MOTOR_OFF]     = {ST_NULL, ST_NULL, ST_NULL, ST_NULL, ST_NULL, ST_NULL, ST_MOTOR_OFF, ST_MOTOR_OFF,  ST_MOTOR_ON_HORARIO, ST_NULL, ST_MOTOR_OFF, ST_MOTOR_OFF}
   };

   PDEBUG("sm_run execution\n");

   // At each cycle, get the new event, which was set by 'external world' or by a SM internal state
   event = sm_private_get_event();

   // In order to save power, do something if there is a new event only.
   if(event == EV_NONE){}

   else{
      // Changes led state
      if(event <= EV_NA) {
         // Get the next state to be executed
         next_led_state = f[_led_state][event];

         if(next_led_state != ST_NULL) {
            // Update the current state variable
            _led_state = next_led_state;

            // Execute next state function, return 0 if everything went OK or -1 otherwise
            ret = state_handler_container[_led_state].state_exe(ex_data, in_data);
         }
         else if(event == EV_NA){
            
         }
         else {
            // If the new event is not recognized in current state, f returns a 'NULL' state, and the function
            // returns an error code.
            return -1;
         }
      }


      // Changes motor and sensor states
      if(event >= EV_NF_ON) {
         if(event != EV_SENSOR_DETECT){
         // Get the next state to be executed
            next_motor_state = f[_motor_state][event];

            if(next_motor_state != ST_NULL) {
               // Update the current state variable
               _motor_state = next_motor_state;

               // Execute next state function, return 0 if everything went OK or -1 otherwise
               ret = state_handler_container[_motor_state].state_exe(ex_data, in_data);
            }
            else {
               // If the new event is not recognized in current state, f returns a 'NULL' state, and the function
               // returns an error code.
               return -1;
            } 
         }

         if(event < EV_MOTOR_R){
            // Get the next state to be executed
            next_count_state = f[_count_state][event];

            if(next_count_state != ST_NULL) {
               // Update the current state variable
               _count_state = next_count_state;

               // Execute next state function, return 0 if everything went OK or -1 otherwise
               ret = state_handler_container[_count_state].state_exe(ex_data, in_data);
            }
            else {
               // If the new event is not recognized in current state, f returns a 'NULL' state, and the function
               // returns an error code.
               return -1;
            }
         }
      }
   }

   return ret;
}

// sm_close implementation.
void sm_close(void)
{
   // Nothing to do in this fictitious firmware, just print a msg.
   PDEBUG("sm_close execution\n");
}



