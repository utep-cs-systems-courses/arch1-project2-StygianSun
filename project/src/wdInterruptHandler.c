#include <msp430.h>
#include "stateMachines.h"
#include "littleLamb.h"

void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static char blink_count = 0;
  if(state == 1){ //Blink count changed to 1 to allow for LED to look dimmed
    if (++blink_count == 1) {
      state_advance();
      blink_count = 0;
    }
  }else if(state == 2){
    //Intentionally left blank.
  }else if(state == 3){
    if (++blink_count == 125) {
      state_advance();
      blink_count = 0;
    }else if(blink_count < 125 && blink_count > 110){ //Cuts off the note so that they don't blend
      switch(llmeasure){ //Switch state determines when buzzer should shut off, allowing notes                                longer than one beat. Also determines when green LED turns off
      case 1:
      case 5:
      case 6:
      case 7:
	green_on = 0; buzzer_set_period(0); break;
      case 2:
      case 3:
      case 4:
	if(llbeat != 4){
	  green_on = 0; buzzer_set_period(0);
	}
	break;
      case 8:
	if(llbeat == 1){
	  green_on = 0; buzzer_set_period(0);
	}
	break;
      }
    }else if(blink_count > 25){ //Only flashes the red LED at the beginning of the beat
      red_on = 0;
    }else if(blink_count <= 25){ //Turns on LEDs at the beginning of the beat
      red_on = 1;
      green_on = 1;
    }
    led_changed = 1;
    led_update();
  }else if(state == 4){
    if(++blink_count == 125){
      state_advance();
      blink_count == 0;
    }
  }
}
