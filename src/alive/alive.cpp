#include <Arduino.h>
#include <stdint.h>
#include <stdio.h>

const int ledPin = 10; // GPIO10 (D10)

//#define PRINTF_DEBUG_OUTPUT_ENABLED

void ALIVE_init(void)
{
  pinMode(ledPin, OUTPUT);
}

void ALIVE_10msTask(void)
{
  static uint8_t cnt_cycle = 0;
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
