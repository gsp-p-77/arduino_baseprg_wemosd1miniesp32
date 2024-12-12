/*
* Minimal operating system to schedule cyclic tasks and a background task
* for Arduino projects
* The 1000 ms TASK prints a heartbeat message to the serial output

* 
*/
#include <Arduino.h>
#include <stdint.h>
#include <stdio.h>
#include "./alive/alive.h"

/*
  Init system timer variable for task scheduler
*/
uint64_t gSystemTimer1msLastSnapshot = millis();



void setup() {
  Serial.begin(115200);
  while(!Serial)
  {
  //wait
  }
  
  Serial.println("Starting ESP32...");

  
  ALIVE_init();

}

void TASK_10ms_idx0(void)
{

}

void TASK_100ms_idx1(void)
{
  static uint8_t cnt_cycle = 0;

  printf("TASK_100ms: Count %d\n",cnt_cycle);
  cnt_cycle++;

  ALIVE_10msTask();

}

typedef struct 
{
  uint32_t start_micros;
  uint32_t end_micros;
  uint32_t task_time_current_micros;
  uint32_t task_time_max_micros;
  uint32_t task_time_avg_micros;
}TASK_profile_data_t;

void TASK_profile_start_hook(TASK_profile_data_t * pProfileData)
{
  pProfileData->start_micros = micros();
}

void TASK_profile_end_hook(TASK_profile_data_t * pProfileData)
{
  pProfileData->end_micros = micros();
  pProfileData->task_time_current_micros = pProfileData->end_micros - pProfileData->start_micros;
  if (pProfileData->task_time_max_micros < pProfileData->task_time_current_micros)
  {
    pProfileData->task_time_max_micros = pProfileData->task_time_current_micros;    
  }

  pProfileData->task_time_avg_micros = (pProfileData->task_time_avg_micros + pProfileData->task_time_current_micros) / 2;
}




void TASK_1000ms_idx2(void)
{
  static uint8_t cnt_cycle = 0;
  
  printf("TASK_1000ms: Count %d\n",cnt_cycle);
  cnt_cycle++;
}


void TASK_Background_idx3(void)
{

}


void loop() {
  static uint16_t cnt1ms = 0;
  
  static TASK_profile_data_t task_profile_data;
  
  TASK_profile_start_hook(&task_profile_data);

  while (! (millis() - gSystemTimer1msLastSnapshot))
  {
    //Wait until 1 ms over (could be used for background tasks)
    TASK_Background_idx3();
  }
  cnt1ms++;
  gSystemTimer1msLastSnapshot = millis();

  if (!((cnt1ms + 1) % 100) )
  {
    TASK_10ms_idx0();
  } 

  if (!((cnt1ms + 2) % 100) )
  {
    TASK_100ms_idx1();
  } 

  if (!((cnt1ms + 7) % 1000) )
  {
    TASK_1000ms_idx2();

    printf("All task max time took %lu microseconds\n", task_profile_data.task_time_max_micros);
    printf("All task avg time took %lu microseconds\n", task_profile_data.task_time_avg_micros);    
  }
  
  TASK_profile_end_hook(&task_profile_data);

}

