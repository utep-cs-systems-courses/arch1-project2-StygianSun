#include <msp430.h>
#include "stateMachines.h"

void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static char blink_count = 0;
  if(state == 1){
    if (++blink_count == 125) {
      state_advance();
      blink_count = 0;
    }
  }else if(state == 2){

  }else if(state == 3){

  }else if(state == 4){

  }
}
