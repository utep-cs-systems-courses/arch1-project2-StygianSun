#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"

int substate = 0;
int state = 1;

char toggle_red()		/* always toggle! */
{
  red_on ^= 1;
  return 1;			/* always changes an led */
}

char toggle_green()	/* only toggle green if red is on!  */
{
  green_on ^= 1;
  return 1;
}

void state_advance()		/* alternate between toggling red & green */
{
  char changed = 0;
  
  switch (state) {
  case 1:
    switch(substate){ //will use assembly function
    case 0: changed = 1; red_on = 1; green_on = 0; substate = 1; buzzer_set_period(0); break;
    case 1: changed = toggle_green(); substate = 2; break;
    case 2: changed = toggle_red(); substate = 3; break;
    case 3: changed = toggle_green(); substate = 0; break;
    }
    break;
  case 2:
    switch(substate){
    case 0: changed = 1; red_on = 0; green_on = 1; substate = 1; break;
    case 1: changed = toggle_green(); substate = 2; break;
    case 2: changed = toggle_red(); toggle_green(); substate = 3; break;
    case 3: changed = toggle_green(); substate = 0; break;
    }
    break;
  case 3: littleLambAdvance(); break;
  case 4:
    switch(substate){
    case 0: changed = 1; red_on = 1; green_on = 1; substate = 1; buzzer_set_period(5000); break;
    case 1: changed = toggle_red(); substate = 2; buzzer_set_period(6000); break;
    case 2: changed = toggle_red(); toggle_green(); substate = 3; buzzer_set_period(7000); break;
    case 3: changed = toggle_red(); substate = 0; buzzer_set_period(8000); break;
    }
    break;
  }

  led_changed = 1;
  led_update();
}
