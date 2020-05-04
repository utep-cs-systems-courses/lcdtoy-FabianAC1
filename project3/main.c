#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "stateMachine.h"
#include "switches.h"
#include "buzzer.h"



void main(void) {


  and_sr(~16);  
  configureClocks();
  lcd_init();
  switch_init();
  buzzer_init();
  led_init();
  enableWDTInterrupts();
  or_sr(0x18);
}
