#include <msp430.h>
#include "switches.h"
#include "lcddraw.h"
#include "lcdutils.h"
#include "led.h"
#include "buzzer.h"
#include "stateMachine.h"


// next two methods are from the assembly file
void turnOff();
void check_State();
u_char c,r = 11;
int state;
int cplace=0;
u_int colorR[] = {COLOR_YELLOW, COLOR_GREEN,COLOR_BLACK,COLOR_PINK};
char switch_state_down, switch_state_changed, s1, s2, s3, s4; /* effectively boolean */
int beat = 600; // used to change the beat of the tune



// used some of the methods provided by the demo labs to complete this lab

static char
switch_update_interrupt_sense() {
  char p1val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p1val & SWITCHES);/* if switch up, sense down */
  P2IES &= (p1val | ~SWITCHES);/* if switch down, sense up */
  return p1val;
}
void
switch_init()/* setup switch */
{
  P2REN |= SWITCHES;/* enables resistors for switches */
  P2IE |= SWITCHES;/* enable interrupts from switches */
  P2OUT |= SWITCHES;/* pull-ups for switches */
  P2DIR &= ~SWITCHES;/* set switches' bits for input */
  switch_update_interrupt_sense();
  led_update();
}

void
switch_interrupt_handler()
{
  char p1val = switch_update_interrupt_sense();
  // sets up values for the state var too know what button is being pressed and therfore carry out the correct actions more on what bottons do in the README.md
  s1 = (p1val & SW1) ? 0 : 1;
  s2 = (p1val & SW2) ? 0 : 1;
  s3 = (p1val & SW3) ? 0 : 1;
  s4 = (p1val & SW4) ? 0 : 1;

  if (s1){
    
    drawMe(colorR[cplace]);
    switch_state_down = s1;
    switch_state_changed = 1;
    buzzer_set_period(1000);
    dim1 = 1;
    
  }
  else if(s2){
    
    switch_state_down = s2;
    switch_state_changed = 1;
    buzzer_set_period(1200);
    dim1 = 0;
    drawPixel(3,4,COLOR_GREEN);
    drawJelly(c,r,colorR[cplace]);
    cplace++;
    if(cplace == 3){
      cplace = 0;
    }
    c+=15;
    r+=2;
   
    
  }
  else if(s3){
    
    clearScreen(COLOR_BLUE);
    clearScreen(COLOR_BLUE);
    switch_state_down = s3;
    switch_state_changed = 1;
    turnOff();
    turnOff();
    dim1 =0;
    c,r=11;
    
 }
  else if(s4){
    
    switch_state_down = s4;
    switch_state_changed = 1;
    dim1 =0;
    
  }
}
