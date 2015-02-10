
#ifndef senzorjiDueTarce_h
#define senzorjiDueTarce_h

#define TARCA_ON   1
#define TARCA_OFF  0
#import <Arduino.h>

extern uint16_t tocke[10];
extern uint16_t noReadTime; //100ms nc ne bere
extern uint8_t stTarc;
extern uint16_t tockeSkupaj;
extern uint16_t staraTockeSkupaj;

void resetScore();
void deaktivirajVse();
void deaktivirajTarco(int tarca);
void aktivirajVse();
void aktivirajVseIzbrane();
void aktivirajTarco(int tarca);
void setNoReadTime(uint16_t a);
void setStTarc(uint8_t st);

void initSenzorji(uint8_t st, uint8_t maxSt, uint16_t tarceNoRead);

void int0();
void int1();
void int2();
void int3();
void int4();
void int5();
void int6();
void int7();
void int8();
void int9();

#else
	#error Oops! Trying to include senzorjiDueTarce.h on another device?
#endif
