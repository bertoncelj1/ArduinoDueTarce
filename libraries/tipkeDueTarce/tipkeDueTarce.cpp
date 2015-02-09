#include "tipkeDueTarce.h"
#include <DueTimer.h>
#include <knjiznica.h>

int tipke[5];
void checkTipke();


void initTipke() {
  Timer3.attachInterrupt(checkTipke).start(10000); // Every 10ms //za tipke
  pinMode(GUMBI_PIN, INPUT);
}

long tipkeDebounceTimer[5];
//vrednosti ko so pritisnjene posamezne tipke
//1023, 990, 958, 872, 757
int tipkeVrednost[] = {1024, 1002, 970, 903, 800, 700};
int debounceDelay = 10;

#define TIPKA_DOWN     -2
#define TIPKA_UP       -3

void checkTipke() {
  int i;

  //prebere vrednost na pinu
  int reading = analogRead(GUMBI_PIN);

  //glede na to vrednost se odloči katera tipka je bila pritisnjena
  //nemogoce neakj je narobe
  if (reading > 1024)return;
  //sprehodi se skozi vse tipke
  for (i = 0; i < 5; i++) {
    //ce reading pade pod podane vrednosti in ce je tipka gor si zapovni cas
    if (tipkeVrednost[i] > reading && reading > tipkeVrednost[i + 1]) {
      if (tipkeDebounceTimer[i] ==  TIPKA_UP) {
        tipkeDebounceTimer[i] = millis();
      }
      //ce je tipka ze dol ne naredi nicesar
      if (tipkeDebounceTimer[i] ==  TIPKA_DOWN) continue;
      
      // ce je bila tipka dol dosti casa zabelezi pritisk tipke
      if (millis() - tipkeDebounceTimer[i] > debounceDelay) {
        tipke[i]++;
        tipkeDebounceTimer[i] = TIPKA_DOWN;
      }
    } else {
      tipkeDebounceTimer[i] = TIPKA_UP;
    }
  }
}

//prebere tipko
int get_LCD_button(int tipka) {
  if (tipke[tipka]) {
    //Serial.println(tipkeArr[tipka]);
    tipke[tipka]--;
    return 1;
  }
  return 0;
}



//piskac ˇˇˇ

int piskacCnt = 0;
int piskac = OFF;

void piskacCount();


void initPiskac() {
  Timer4.attachInterrupt(piskacCount).start(100000); // Every 100ms //za piskac
  pinMode(PISKAC_PIN, OUTPUT);
  digitalWrite(PISKAC_PIN, LOW);
}

void piskacOn(int cas) {
  if (piskac == OFF) {
    piskacCnt = cas;
    digitalWrite(PISKAC_PIN, HIGH);
  }
  piskac = ON;
}

void piskacOFF(){
	//TODO: ugasni interrupt ko ga ne rabi vec
    //Timer1.detachInterrupt();
	piskac = OFF;
	digitalWrite(PISKAC_PIN, LOW);
}

void piskacCount() {
  if (piskac == ON) {
    if (piskacCnt == 0) {
		piskacOFF();
    }
    else piskacCnt --;
  }
}

