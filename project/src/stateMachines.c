#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"
#include "littleLamb.h"
#include "statesAssembly.h"

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

void state_advance() /* Advances substate of the current state */
{
  char changed = 0;
  
  switch (state) { // Dim state
  case 1:
    switch(substate){
    case 0: changed = 1; red_on = 0; green_on = 0; substate++; break;
    case 1:
    case 2:
    case 3:
      changed = 0; substate++; break;
    case 4:
      changed = 1; red_on = 1; green_on = 1; substate = 0; break;
    }
    break;
  case 2: //Intentionally left blank. Is intended to act as a "halt" button
    break;
  case 3: littleLambAdvance(); break; //Advances through Mary Had a Little Lamb
  case 4: //LED and Buzzer cycle state
    assemblyState();
    break;
  }

  led_changed = 1;
  led_update();
}
