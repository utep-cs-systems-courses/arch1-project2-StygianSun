#include <msp430.h>
#include "buzzer.h"
#include "led.h"

//Song notes
#define G 3135.96
#define A 3520
#define B 3951.06

extern int ll_cur_note, llbeat, llmeasure;

void littleLambAdvance();
