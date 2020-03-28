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
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);  /* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES); /* if switch down, sense up */
  return p2val;
}

void switch_init()                 /* setup switch */
{
  P2REN |= SWITCHES;               /* enables resistors for switches */
  P2IE = SWITCHES;                 /* enable interrupts from switches */
  P2OUT |= SWITCHES;               /* pull-ups for switches */
  P2DIR &= ~SWITCHES;              /* set switches' bits for input */
  switch_update_interrupt_sense();
  led_update();
}

void switch_interrupt_handler()
{
  char p2val = switch_update_interrupt_sense();
  switch_state_down1 = (p2val & SW1) ? 0 : 1; /* 0 when SW1 is up */
  switch_state_down2 = (p2val & SW2) ? 0 : 1; /* 0 when SW2 is up */
  switch_state_down3 = (p2val & SW3) ? 0 : 1; /* 0 when SW3 is up */
  switch_state_down4 = (p2val & SW4) ? 0 : 1; /* 0 when SW4 is up */

  /* State switching implemented here so that when a button is pressed, the state immediatelly changes rather than waiting for a state_advance call. */
  if(switch_state_down1){ //Dim state
    state = 1;
    substate = 0;
    buzzer_set_period(0);
  }else if(switch_state_down2){ //Starts halt state
    state = 2;
  }else if(switch_state_down3){ //Mary Had a Little Lamb, clears buzzer and leds and resets to play song from the beginning
    buzzer_set_period(0);
    red_on = 0;
    green_on = 0;
    state = 3;
    substate = 0;
    ll_cur_note = 0;
    llbeat = 1;
    llmeasure = 1;
  }else if(switch_state_down4){ // LED & Buzzer cycle state
    state = 4;
    substate = 0;
  }
  
  switch_state_changed = 1;
}
