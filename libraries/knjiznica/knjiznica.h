
#ifndef knjiznica_h
#define knjiznica_h

#define BESEDILO 0
#define NASLOV 1

#define ZNAK_DESNO  126
#define ZNAK_LEVO   127

#define ZVOK_OFF  0
#define ZVOK_LOW  100
#define ZVOK_MED  180
#define ZVOK_MAX  255

#define btnUP     0
#define btnDOWN   1
#define btnLEFT   2
#define btnRIGHT  3
#define btnSELECT 4

char tipkeArr[] = {'u','d','l','r','s'};


#define PISKAC_PIN	 10
#define GUMBI_PIN    A0


#define ON  1
#define OFF  0

#define MAX_EKRANOV	40
//ekrani in dejanska stanja
#define MENI_GLAVNI 	1
#define MENI_IGRAJ 	    2
#define MENI_NASTAVITVE 3
#define NAST_SENZORJI 	4
#define NAST_ST_TARC	5
#define MENI_PROG1 	6
#define MENI_PROG2 	7
#define MENI_PROG3 	8
#define MENI_PROG4 	9
#define MENI_PROG5 	10
#define PROGRAM_1	11
#define PROGRAM_2	12
#define PROGRAM_3	13
#define PROGRAM_4	14
#define PROGRAM_5	15
#define NAST_PROG1 	16
#define NAST_PROG2 	17
#define NAST_PROG3 	18
#define NAST_PROG4 	19
#define NAST_PROG5 	20
#define ODSTEVAJ	21



//ukazi
#define INC_IZBRAN        40
#define DEC_IZBRAN        41
#define NAST_INC_IZBRAN   42
#define NAST_DEC_IZBRAN   43
#define NAST_EDIT         44
#define NAST_EDIT_DEC     45
#define NAST_EDIT_INC     46
#define NAST_EDIT_FINISH  47 
#define PROG1_TOCKE_DEC   48 //za premikanje po tockah
#define PROG1_TOCKE_INC   49 

//nastavitve in splosen spomin -- indexi vseh spremenljivk v spominu
//mem -> memory
#define MAX_SPOMIN 		 50
#define ST_SPOMINA 		 12

#define MEM_ST_TARC		 0
#define MEM_OBCUT		 1
#define MEM_ZAMIK		 2
#define MEM_PROG1_CAS	 3
#define MEM_PROG2_TEZ	 4
#define MEM_PROG2_CAS	 5
#define MEM_PROG3_CAS	 6
#define MEM_PROG3_TEZ	 7
#define MEM_PROG4_CAS	 8
#define MEM_PROG4_TEZ	 9
#define MEM_PROG5_CAS	 10
#define MEM_PROG5_TEZ	 11


//risalnik tock tipi
#define DRAW_TOCKE_SCROLL    0
#define DRAW_TOCKE_KLIK		 1



#define FUN_TIPKE 200

#define MAX_PARAMETROV 2

#define d_retState   (((s_ekranNastavitveEdit*)vsiEkrani[NAST_EDIT])->returnState)
#define d_tretIzbran (((s_ekranNastavitve*)vsiEkrani[d_retState])->trenutnoIzbran)
#define d_parameter  (((s_ekranNastavitve*)vsiEkrani[d_retState])->parameter[d_tretIzbran])




typedef struct
{
char *besedilo;
uint8_t funkcija;
}s_izbirnaVrstica;



typedef struct 
{
char* naslov;
uint8_t tipke[5];
uint8_t st_elementov;
uint8_t trenutnoIzbran;
s_izbirnaVrstica elementi[5];
}s_ekran;

typedef struct 
{
char* opis;
uint16_t min;
uint16_t max;
int16_t vrednost;
uint8_t  korak;
uint8_t index; //st indexa v spominu
}s_parameter;


typedef struct 
{
char* naslov;
uint8_t tipke[5];
uint8_t stParametrov;
uint8_t trenutnoIzbran;
uint8_t focus;
s_parameter parameter[MAX_PARAMETROV];
}s_ekranNastavitve;

typedef struct 
{
char* naslov; //nima ga
uint8_t tipke[5];
uint16_t returnState;
}s_ekranNastavitveEdit;

typedef struct 
{
char* naslov;
uint8_t tipke[5];
}s_ekranProgram;

typedef struct 
{
uint8_t state;
uint32_t mills;
uint8_t stOdstevanj;
uint8_t returnState;

}s_odstevajInit;

typedef struct 
{
uint8_t nacin;
uint32_t cas;
uint8_t hitrostScroll;
uint8_t pozicija;

}s_drawTockeInit;


typedef struct 
{
uint8_t stanje;
uint8_t cnt;
uint8_t tocke;
}s_tarca;

struct koncniNapisi 
{
  char *besedilo;
  uint16_t zamik;
};

#else
	#error Oops! Trying to include knjiznica.h on another device?
#endif
