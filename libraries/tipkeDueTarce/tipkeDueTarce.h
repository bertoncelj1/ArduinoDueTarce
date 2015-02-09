
#ifndef tipkeDueTarce_h
#define tipkeDueTarce_h

#import <Arduino.h>


extern int tipke[5];          //kolikokrat je bila tipka pritisnjena
void initTipke();
int get_LCD_button(int tipka);//prebere tipko



void initPiskac();		
void piskacOn(int cas); //nastavi pisakc za doloceno stevilo ms*100 (npr. 10 pomeni 1s)
void piskacOFF();



#else
	#error Oops! Trying to include tipkeDueTarce.h on another device?
#endif
