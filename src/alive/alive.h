#ifndef ALIVE_H
#define ALIVE_H

void ALIVE_init(void);
void ALIVE_CyclicTask(void);
void ALIVE_DisableCycles(uint8_t cycles);
void ALIVE_RequestActive(boolean state);

#endif

