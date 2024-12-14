#include <Arduino.h>
#include <stdint.h>
#include <stdio.h>

const int ledPin = 10; // GPIO10 (D10)

//#define PRINTF_DEBUG_OUTPUT_ENABLED
static uint8_t disableCycles = 0;

void ALIVE_init(void)
{
  pinMode(ledPin, OUTPUT);
}

void ALIVE_Disable(uint8_t cycles)
{
  disableCycles = cycles;
}

void ALIVE_CyclicTask(void)
{
  static uint8_t cnt_cycle = 0;
  if (! disableCycles)
  {
    cnt_cycle++;
    if (cnt_cycle & 1)
    {
      digitalWrite(ledPin, HIGH);
  #ifdef PRINTF_DEBUG_OUTPUT_ENABLED
      printf("LED HIGH \n");
  #endif
    }
    else
    {
      digitalWrite(ledPin, LOW);
  #ifdef PRINTF_DEBUG_OUTPUT_ENABLED    
      printf("LED LOW \n");
  #endif    
    }
  }
  else
  {
    disableCycles--;
  }
}
