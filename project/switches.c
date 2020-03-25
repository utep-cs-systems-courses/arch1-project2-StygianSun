#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "buzzer.h"
#include "littleLamb.h"
#include "stateMachines.h"

char switch_state_down1, switch_state_down2, switch_state_down3,
  switch_state_down4, switch_state_changed;

static char
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  P2IES |= (p2val & SWITCHES);
  P2IES &= (p2val | ~SWITCHES);
  return p2val;
}

void switch_init()
{
  P2REN |= SWITCHES;
  P2IE = SWITCHES;
  P2OUT |= SWITCHES;
  P2DIR &= ~SWITCHES;
  switch_update_interrupt_sense();
  led_update();
}

void switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();
  switch_state_down1 = (p2val & SW1) ? 0 : 1;
  switch_state_down2 = (p2val & SW2) ? 0 : 1;
  switch_state_down3 = (p2val & SW3) ? 0 : 1;
  switch_state_down4 = (p2val & SW4) ? 0 : 1;

  if(switch_state_down1){
    state = 1;
    substate = 0;
    buzzer_set_period(0);
  }else if(switch_state_down2){
    state = 2;
    substate = 0;
    buzzer_set_period(0);
  }else if(switch_state_down3){
    buzzer_set_period(0);
    red_on = 0;
    green_on = 0;
    state = 3;
    substate = 0;
    ll_cur_note = 0;
    llbeat = 1;
    llmeasure = 1;
  }else if(switch_state_down4){
    state = 4;
    substate = 0;
    buzzer_set_period(0);
  }
  
  switch_state_changed = 1;
}
