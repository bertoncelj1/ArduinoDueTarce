#include "senzorjiDueTarce.h"


struct s_senzor{
  int pinLuc;
  int pinSenzor;
};

s_senzor senzorji[10] = {
  30,31,
  32,33,
  34,35,
  36,37,
  38,39,
  40,41,
  42,43,
  44,45,
  46,47,
  48,49,
};


unsigned long zadnjicPrebrano[10];

uint16_t tocke[10];
uint16_t tockeSkupaj;
uint16_t staraTockeSkupaj;
uint16_t noReadTime = 100;
uint8_t tarceStanje[10]; //pove stanje o tarci on/off
uint8_t stTarc;
uint8_t stTarcMax;
int j;

/*
uint16_t getScoreTarce(uint8_t tarca){
	return tocke[tarca];
}

uint16_t[] getScore(){
	return tocke;
}
*/
void resetScore(){
	j=10;
	while(j--)tocke[j] = 0;
	tockeSkupaj = 0;
	staraTockeSkupaj = 0;
}

void deaktivirajVse(){
	j=stTarcMax;
	while(j--)deaktivirajTarco(j);
}

void deaktivirajTarco(int tarca){
	tarceStanje[tarca] = TARCA_OFF;
	digitalWrite(senzorji[tarca].pinLuc, LOW);
}

void aktivirajVse(){
	j=stTarcMax;
	while(j--)aktivirajTarco(j);
}

void aktivirajVseIzbrane(){
	j=stTarc;
	while(j--)aktivirajTarco(j);
}

void aktivirajTarco(int tarca){
	tarceStanje[tarca] = TARCA_ON;
	digitalWrite(senzorji[tarca].pinLuc, HIGH);
}

void setNoReadTime(uint16_t a){
	noReadTime = a;
}

void setStTarc(uint8_t st){
	Serial.print("SPREMEMBA TARC!");
	stTarc = st;
}


void initSenzorji(uint8_t st, uint8_t maxSt, uint16_t tarceNoRead){
  stTarcMax = maxSt;
  setStTarc(st);
  Serial.println(stTarc);
  setNoReadTime(tarceNoRead);

  //Serial.begin(9600);
  
  for(j=0;j<maxSt;j++){
    //attachInterrupt(senzorji[j].pinSenzor, sensorInterrupt, RISING);
    pinMode(senzorji[j].pinLuc, OUTPUT);
  }
  
  deaktivirajVse();
  
  //nastavi interrupte za lucke
  attachInterrupt(senzorji[0].pinSenzor, int0, RISING);
  attachInterrupt(senzorji[1].pinSenzor, int1, RISING);
  attachInterrupt(senzorji[2].pinSenzor, int2, RISING);
  attachInterrupt(senzorji[3].pinSenzor, int3, RISING);
  attachInterrupt(senzorji[4].pinSenzor, int4, RISING);
  attachInterrupt(senzorji[5].pinSenzor, int5, RISING);
  attachInterrupt(senzorji[6].pinSenzor, int6, RISING);
  attachInterrupt(senzorji[7].pinSenzor, int7, RISING);
  attachInterrupt(senzorji[8].pinSenzor, int8, RISING);
  attachInterrupt(senzorji[9].pinSenzor, int9, RISING);
  
}  

/*void loop() {
  for(i=0;i<10;i++){
    if(tocke[i] % 2 == 0){
      digitalWrite(senzorji[i].pinLuc, HIGH);
    }else{
      digitalWrite(senzorji[i].pinLuc, LOW);
    }
    Serial.print(tocke[i]);
    Serial.print(' ');
  }
  Serial.println();
  delay(500);
}
*/
/*
void sensorInterrupt(){
  for(i=0;i<10;i++){
    tocke[i]++;
    if(digitalRead(senzorji[i].pinSenzor) == HIGH){
      long mil = millis();
      tocke[i]++;
      if(mil - zadnjicPrebrano[i] > noReadTime){
        zadnjicPrebrano[i] = mil;
        tocke[i]++;
      }
    }
  }
}
*/

void obdelajInt(uint8_t t){
  if(tarceStanje[t] == TARCA_ON && millis() - zadnjicPrebrano[t] > noReadTime){
    zadnjicPrebrano[t] = millis();
    tocke[t]++;
    tockeSkupaj ++;
  }
}

void int0(){
	obdelajInt(0);
}

void int1(){
	obdelajInt(1);
}

void int2(){
	obdelajInt(2);
}

void int3(){
	obdelajInt(3);
}

void int4(){
	obdelajInt(4);
}

void int5(){
	obdelajInt(5);
}

void int6(){
	obdelajInt(6);
}

void int7(){
	obdelajInt(7);
}

void int8(){
	obdelajInt(8);
}

void int9(){
	obdelajInt(9);
}

