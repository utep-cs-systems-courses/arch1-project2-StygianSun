#include <msp430.h>
#include "buzzer.h"
#include "led.h"
#include "littleLamb.h"

int ll_cur_note = 0;
int llbeat = 1;
int llmeasure = 1;

int verse[] = {B, A, G, A, B, A, B, A, G, A, B, A, B, A, G};

void littleLambAdvance(){
  switch(llmeasure){
  case 1:
  case 5:
    switch(llbeat){
    case 1:
    case 2:
    case 3:
      green_on = 1; red_on = 1;
      buzzer_set_period(verse[ll_cur_note]); ll_cur_note++; llbeat++; break;
    case 4: buzzer_set_period(verse[ll_cur_note]); ll_cur_note++; llbeat = 1; llmeasure++; break;
    }
    break;
  case 2:
  case 3:
  case 6:
    switch(llbeat){
    case 1:
    case 2:
    case 3:
      buzzer_set_period(verse[ll_cur_note]); llbeat++; break;
    case 4: buzzer_set_period(verse[ll_cur_note]); ll_cur_note++; llbeat = 1; llmeasure++; break;
    }
    break;
  case 4:
    switch(llbeat){
    case 1:
    case 2:
    case 3:
      buzzer_set_period(verse[ll_cur_note]); llbeat++; break;
    case 4:
      buzzer_set_period(verse[ll_cur_note]); llbeat = 1; llmeasure++; break;
    }
    break;
  case 7:
    switch(llbeat){
    case 1: buzzer_set_period(verse[ll_cur_note]); llbeat++; break;
    case 2:
    case 3:
      buzzer_set_period(verse[ll_cur_note]); ll_cur_note++; llbeat++; break;
    case 4:
      buzzer_set_period(verse[ll_cur_note]); ll_cur_note++; llbeat = 1; llmeasure++; break;
    }
    break;
  case 8:
    switch(llbeat){
    case 1:
    case 2:
    case 3:
      buzzer_set_period(verse[ll_cur_note]); llbeat++; break;
    case 4:
      buzzer_set_period(verse[ll_cur_note]); ll_cur_note = 0; llbeat = 1; llmeasure = 1; break;
    }
    break;
  }
}
