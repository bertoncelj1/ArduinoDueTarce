#include <DueTimer.h>
#include <knjiznica.h>

#include <LiquidCrystal.h>
#include <senzorjiDueTarce.h>
#include <tipkeDueTarce.h>
#include <DueFlashStorage.h>

asdasd
DueFlashStorage dueFlashStorage;

//#include <EEPROM.h>

s_parameter parametri[MAX_SPOMIN];

s_ekran mainMenu = //MENI_GLAVNI
{
  "Glavni meni",
  //tipke:
  //gor dol levo, desno, select
  0, FUN_TIPKE, DEC_IZBRAN, INC_IZBRAN, 0,
  3, 0,
  "igraj !",      MENI_IGRAJ,
  "nastavitve",   MENI_NASTAVITVE,
  "info",         MENI_INFO,
};

s_ekran infoMenu = //MENI_INFO
{
  "Verzija 1.02",
  //gor dol levo, desno, select
  MENI_GLAVNI, STEJ_PRITISKE, STEJ_PRITISKE, STEJ_PRITISKE, 0,
  1, 0,
  "10.feb.2015",       0,
};

s_ekran madeByMenu = //MENI_MADE_BY
{
  "SPROGRAMIRAL",
  //gor dol levo, desno, select
  MENI_INFO, 0, 0, 0, 0,
  1, 0,
  "Anze  Bertoncelj",       0,
};

s_ekran nastavitveMenu = //MENI_NASTAVITVE
{
  "Nastavitve",
  //gor dol levo, desno, select
  MENI_GLAVNI, FUN_TIPKE, DEC_IZBRAN, INC_IZBRAN, 0,
  2, 0,
  "senzorji",       NAST_SENZORJI,
  "st. tarc",       NAST_ST_TARC,
};

s_ekranNastavitve stTarcNast =  //NAST_ST_TARC
{
  "Nast. st. tarc",
  //gor dol levo, desno, select
  MENI_NASTAVITVE, NAST_EDIT, DEC_IZBRAN, INC_IZBRAN, 0,
  //st parametrov, trenutno izbran, focus
  1, 0, OFF,
  //index parametra ki je shranjen v arreju "parametri"
  MEM_ST_TARC
};

s_ekranNastavitve senzorjiNast =  //NAST_SENZORJI
{
  "Nast. senzorjev",
  //gor dol levo, desno, select
  MENI_NASTAVITVE, NAST_EDIT, DEC_IZBRAN, INC_IZBRAN, 0,
  //st parametrov, trenutno izbran, focus
  1, 0, OFF,
  //opis,    min   max,  def,  korak, index
  //index parametra ki je shranjen v arreju "parametri"
  MEM_ZAMIK,
};

s_ekranNastavitveEdit editNast =  //NAST_EDIT
{
  0,
  //gor dol levo, desno, select
  NAST_EDIT_FINISH, 0, NAST_EDIT_DEC, NAST_EDIT_INC, 0,
  //return state
  0
};

s_ekran igrajMenu = //MENI_IGRAJ
{
  "Izberi program:",
  //gor dol levo, desno, select
  MENI_GLAVNI, FUN_TIPKE, DEC_IZBRAN, INC_IZBRAN, 0,
  5, 0,
  "gorijo vse",        MENI_PROG1,
  "ena za drugo",        MENI_PROG2,
  "nakljucno",        MENI_PROG3,
  "zaporedje 10s",        MENI_PROG4,
  "prva in zadnja",        MENI_PROG5
};

s_ekran prog1Menu = //MENI_PROG1
{
  "Gorijo vse:",
  //gor dol levo, desno, select
  MENI_IGRAJ, FUN_TIPKE, DEC_IZBRAN, INC_IZBRAN, 0,
  2, 0,
  "zacni z igro",        PROGRAM_1,
  "nastavitve",        	 0,
};

s_ekranNastavitve prog1Nast =  //NAST_PROG1
{
  "prog1 nastavitve",
  //gor dol levo, desno, select
  MENI_PROG1, NAST_EDIT, NAST_DEC_IZBRAN, NAST_INC_IZBRAN, 0,
  //st parametrov, trenutno izbran, focus
  1, 0, OFF,
  //index parametra ki je shranjen v arreju "parametri"
  MEM_PROG1_CAS,
  //"hitrost:",  100,  1000, 500,  50

};

s_ekran prog2Menu = //MENI_PROG2
{
  "Ena za drugo:",
  //gor dol levo, desno, select
  MENI_IGRAJ, FUN_TIPKE, DEC_IZBRAN, INC_IZBRAN, 0,
  2, 0,
  "zacni z igro",        PROGRAM_2,
  "nastavitve",        	 0,
};

s_ekranNastavitve prog2Nast =  //NAST_PROG2
{
  "prog2 nastavitve",
  //gor dol levo, desno, select
  MENI_PROG2, NAST_EDIT, NAST_DEC_IZBRAN, NAST_INC_IZBRAN, 0,
  //st parametrov, trenutno izbran, focus
  2, 0, OFF,
  //index parametra ki je shranjen v arreju "parametri"
  MEM_PROG2_TEZ,
  MEM_PROG2_CAS,

};

s_ekran prog3Menu = //MENI_PROG3
{
  "Nakljucno:",
  //gor dol levo, desno, select
  MENI_IGRAJ, FUN_TIPKE, DEC_IZBRAN, INC_IZBRAN, 0,
  2, 0,
  "zacni z igro",        PROGRAM_3,
  "nastavitve",        	 0,
};

s_ekranNastavitve prog3Nast =  //NAST_PROG3
{
  "prog3 nastavitve",
  //gor dol levo, desno, select
  MENI_PROG3, NAST_EDIT, NAST_DEC_IZBRAN, NAST_INC_IZBRAN, 0,
  //st parametrov, trenutno izbran, focus
  2, 0, OFF,
  //index parametra ki je shranjen v arreju "parametri"
  MEM_PROG3_TEZ,
  MEM_PROG3_CAS,

};

s_ekran prog4Menu = //MENI_PROG4
{
  "Zaporedje 10s:",
  //gor dol levo, desno, select
  MENI_IGRAJ, FUN_TIPKE, DEC_IZBRAN, INC_IZBRAN, 0,
  2, 0,
  "zacni z igro",        PROGRAM_4,
  "nastavitve",        	 NAST_PROG4,
};

s_ekranNastavitve prog4Nast =  //NAST_PROG4
{
  "prog4 nastavitve",
  //gor dol levo, desno, select
  MENI_PROG4, NAST_EDIT, NAST_DEC_IZBRAN, NAST_INC_IZBRAN, 0,
  //st parametrov, trenutno izbran, focus
  1, 0, OFF,
  //index parametra ki je shranjen v arreju "parametri"
  MEM_PROG4_CAS,
  //MEM_PROG4_TEZ,

};

s_ekran prog5Menu = //MENI_PROG5
{
  "Prva in zadnja:",
  //gor dol levo, desno, select
  MENI_IGRAJ, FUN_TIPKE, DEC_IZBRAN, INC_IZBRAN, 0,
  2, 0,
  "zacni z igro",        PROGRAM_5,
  "nastavitve",        	 0,
};

s_ekranNastavitve prog5Nast =  //NAST_PROG5
{
  "prog5 nastavitve",
  //gor dol levo, desno, select
  MENI_PROG5, NAST_EDIT, NAST_DEC_IZBRAN, NAST_INC_IZBRAN, 0,
  //st parametrov, trenutno izbran, focus
  2, 0, OFF,
  //index parametra ki je shranjen v arreju "parametri"
  MEM_PROG5_TEZ,
  MEM_PROG5_CAS,

};


s_ekranProgram program1 =          // PROGRAM_1
{
  0,
  //gor dol levo, desno, select
  MENI_PROG1, 0, PROG1_TOCKE_DEC, PROG1_TOCKE_INC, 0,
};

s_ekranProgram program2 =         // PROGRAM_2
{
  0,
  //gor dol levo, desno, select
  MENI_PROG2, 0, 0, 0, 0,
};

s_ekranProgram program3 =         // PROGRAM_3
{
  0,
  //gor dol levo, desno, select
  MENI_PROG3, 0, 0, 0, 0,
};

s_ekranProgram program4 =        // PROGRAM_4
{
  0,
  //gor dol levo, desno, select
  MENI_PROG4, 0, 0, 0, 0,
};

s_ekranProgram program5 =        // PROGRAM_5
{
  0,
  //gor dol levo, desno, select
  MENI_PROG5, 0, 0, 0, 0,
};

s_ekranOdstevaj odstavajOkno =        // OSDSTEVAJ
{
  0,
  //gor dol levo, desno, select
  //tuki se poj notr shran tipke ki jih lahko uporabnik
  //uporablja med odstevanjem
  0, 0, 0, 0, 0,
  
};




// def vrednosti odstevalnika
s_odstevajInit odstevalnik = {
  //state, millis, stOdstevanj, returnState
  0, 0, 5, 255
};

s_drawTockeInit risalnikTock = {
  //nacin, cas, hitrostScrolla
  DRAW_TOCKE_KLIK, 0, 100, 0
};



//TODO naredi ta te prasa predn gres s programa vn
//TODO dodaj zvok ko je tarca zadeta
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int i;
int stoparica = OFF;
int stevec = 0;

int gumbi[5];
int adc_key_in;
int funInt = 1;
uint8_t state;
uint8_t puscice = 0; // ali so narisane puščice ?
uint32_t vsiEkrani[MAX_EKRANOV];
uint32_t spomin[MAX_SPOMIN];
long zacetniCas = 0;
long zacetniCas2 = 0;
char *(besedila)[3] = {
  "Igra", "Start ", "Info"
};
char izpis[16] = {ZNAK_LEVO, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ZNAK_DESNO};
int8_t programState = -1;

void setup() {
    
  Serial.begin(9600);
  Serial.println("Program Start");
  lcd.begin(16, 2);
  getSpomin();
  initTipke();
  initPiskac();
  initSenzorji(spomin[MEM_ST_TARC],10,spomin[MEM_ZAMIK]);//spomin[MEM_ST_TARC], spomin[MEM_ZAMIK]);
  initEkrane();
  sPrint("stTarc",stTarc);
  
  state = MENI_GLAVNI;
}

void drawTocke() {
  char outStr[16];
  //outStr more bit dolg vsaj 16 znakov
  char cifra[3];
  switch (risalnikTock.nacin) {
    case DRAW_TOCKE_SCROLL:

      break;

    case DRAW_TOCKE_KLIK:
      int i = 0;
      
      if(stTarc > 2){
        outStr[i++] = ZNAK_LEVO;
        outStr[i++] = ' ';
        outStr[14] = ' ';
        outStr[15] = ZNAK_DESNO;
      }else{
        i = 3;
      }

      int krog = 0;
      int trenutnaTarca;
      while (krog < 2) { // to je glih tok da se ustav pred koncem
        //izracuna trenutno tarco
        trenutnaTarca = ((risalnikTock.pozicija + krog) % stTarc);
        //tukaj spodaj izpise tocke
        outStr[i++] = 't';
        outStr[i++] = trenutnaTarca + 0x30;
        outStr[i++] = ':';

        itoa(tocke[trenutnaTarca], cifra, 10);
        int j;
        for(j=0;j<getDecLength(tocke[trenutnaTarca]);j++){
          outStr[i++] = cifra[j];
        }
        while(j<3){
          outStr[i++] = ' ';
          j++;
        }

        //outStr[i++] = '_';
        
        krog ++;
      }


      //outStr[16] = 0;



      break;
  }
  
  
  /*for (i = 0; i < 16; i++) {
    Serial.write(outStr[i]);
  }*/
  
  lcd.print(outStr);
  //return &outStr[0];
}
/*
char* drawTocke(char* out)  {
  int i;
  for(i=0;i<16;i++){
    out[i] = i + 0x30;
  }
  out[i] = 0;
  
  return &out[0];
}
*/
void check(int st) {
  Serial.print(((s_ekran*)vsiEkrani[st])->tipke[btnRIGHT]);
  Serial.print(" ");
  Serial.print(((s_ekran*)vsiEkrani[st])->tipke[btnUP]);
  Serial.print(" ");
  Serial.print(((s_ekran*)vsiEkrani[st])->tipke[btnDOWN]);
  Serial.print(" ");
  Serial.print(((s_ekran*)vsiEkrani[st])->tipke[btnLEFT]);
  Serial.print(" ");
  Serial.println(((s_ekran*)vsiEkrani[st])->tipke[btnSELECT]);
}

int nonStop = 0; //uporabla se da skoz krozi skoz glavno State Masino 0-OFF, 1-ON
int preverjajSprememboTarc = 0; //ce je to na 1 bo tud su preverjat tarce ce so se kej spremenile
int prevState;

void loop() {

  //Serial.println(state);
  //sPrint("nS", nonStop);
  //sPrint("tarc", preverjajSprememboTarc);
  switch (state) {
    
    case MENI_GLAVNI:
    case MENI_IGRAJ:
    case MENI_NASTAVITVE:
    case MENI_INFO:
    case MENI_MADE_BY:
      drawScreen();
      break;

    case MENI_PROG1:
    case MENI_PROG2:
    case MENI_PROG3:
    case MENI_PROG4:
    case MENI_PROG5:
      deaktivirajVse();
      drawScreen();
      nonStop = 0;
      preverjajSprememboTarc = 0;
      break;

    case NAST_PROG1:
    case NAST_PROG2:
    case NAST_PROG3:
    case NAST_PROG4:
    case NAST_PROG5:
    case NAST_ST_TARC:
    case NAST_SENZORJI:
      drawScreenNast();
      break;

    case NAST_EDIT:
      drawScreenEdit();
      break;

    case PROGRAM_1:
      programFSM1();
      break;
      
    case PROGRAM_2:
      programFSM2();
    break;
    
    case PROGRAM_3:
      programFSM3();
    break;
    
    case PROGRAM_4:
      programFSM4();
    break;
    
    case PROGRAM_5:
      programFSM5();
    break;

    case ODSTEVAJ:
      odstevaj();
      break;

    default:
      //ce ne dobi nc pametnga se vrne na prvotno stanje
      Serial.println("def");
      state = prevState;
      break;

  }

  prevState = state;
  while (!preveriTipke() && !nonStop && !preveriTarce());
  //TODO nared da gre tud takrt naprej ko se spremenijo tocke

}


uint8_t preveriTarce(){
  if(preverjajSprememboTarc == 1){
    if(staraTockeSkupaj != tockeSkupaj){
      staraTockeSkupaj = tockeSkupaj;
      return 1;
    }
  }
  return 0;
}

void confOdstevalnik(){
    //skonfigurira odstevalnik
    odstevalnik.state = 1;
    odstevalnik.stOdstevanj = 5;
    odstevalnik.mills = 0;
    odstevalnik.returnState  = state;
    // nastavi vrednost tipke da ko uporabnik pritisne GOR bo su nazanj na meni
    ((s_ekranOdstevaj*)vsiEkrani[ODSTEVAJ])->tipke[btnUP] = ((s_ekranProgram*)vsiEkrani[state])->tipke[btnUP];
    state = ODSTEVAJ;
    nonStop = 1;
}


//TODO dej te spremenljivke vse v skupno strukturo za vsak program
int treOsvetljena;
int pauza;  //pauza preden przge nasledno tarco
long treMill;//trenutne millisekunde
int stara = 0;
long mil;

void programFSM1() { //prog 1 final state mašina
  char  izpisTocke[16];
  char  tockeSkupajArr[3];
  
  switch (programState) {
    case -1:
      //skonfigurira odstevalnik
      confOdstevalnik();
      programState = 0;
      //odstevalnik premakne programState naprej na 1
      break;

    case 1:
      programState = 2;

      //resetira vse tocke in pokaze vse tarce
      resetScore();
      aktivirajVseIzbrane();

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Preostalih: X");
      
      //izpise prvo vrednost na mesto X
      itoa(stTarc, tockeSkupajArr, 10);
      lcd.setCursor(12, 0);
      lcd.print(tockeSkupajArr);
      
      
      lcd.setCursor(0, 1);
      lcd.print("Cas: ");
      
      treMill = millis();
      stara = tockeSkupaj;
      nonStop = 1;
      preverjajSprememboTarc = 1;

   break;
      
   case 2:
      if(stara != tockeSkupaj){
        stara = tockeSkupaj;
        int stevec = 0;
        for(i=0;i<stTarc;i++){
          if(tocke[i] > 0){ //ce je bla ze kdaj zadeta
            deaktivirajTarco(i);
            stevec ++;
          }
          
        }
        if(stevec == stTarc){
          programState = 3;
          break;
        }
        
      //izpise skupne tocke
      //pobrise prejsno cifro
      lcd.setCursor(12, 0);
      lcd.print("    ");
      
      itoa(stTarc - tockeSkupaj, tockeSkupajArr, 10);
      lcd.setCursor(12, 0);
      lcd.print(tockeSkupajArr);
       
        
      }
      //pobrise screen
      //lcd.setCursor(7, 0);
      //lcd.print("    ");
      

      //izrise uro v spodnji vrstici
      lcd.setCursor(5, 1);
      izpisiCas((millis() - treMill)/100);
   break;

  case 3:
    piskacOn(3);
    nonStop = 0;
    preverjajSprememboTarc = 0;
    
    lcd.setCursor(0, 0);
    lcd.print("   Konec igre   ");
  
  
  break;
  }
}


int stZadetih;
void programFSM2( ) { 
  char  izpisTocke[16];
  char  tockeSkupajArr[3];
  
    
  switch (programState) {
    case -1:
      //skonfigurira odstevalnik
      confOdstevalnik();
      
      pauza = 100; // 10 s;
      programState = 0;
      //odstevalnik premakne programState naprej na 1
      break;

    case 1:
      programState = 2;

      //resetira vse tocke in pokaze vse tarce
      resetScore();


      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Preostalih: X");
      
      //izpise prvo vrednost na mesto X
      itoa(stTarc, tockeSkupajArr, 10);
      lcd.setCursor(12, 0);
      lcd.print(tockeSkupajArr);
      
      lcd.setCursor(0, 1);
      lcd.print("Cas: ");
      
      treMill = millis();
      stara = tockeSkupaj;
      nonStop = 1;
      preverjajSprememboTarc = 1;
      stZadetih = 0;
      treOsvetljena = 0;
      stara = tockeSkupaj;
      aktivirajTarco(treOsvetljena);
   break;

      
   case 2:
     //ko je tarca zadeta se zaporedno prižga nasledna
     
     if(stara != tockeSkupaj){
      deaktivirajTarco(treOsvetljena);
      
      treOsvetljena ++;
      if(treOsvetljena > stTarc - 1){
        programState = 3;
        break;
      } 
      aktivirajTarco(treOsvetljena);
      
      Serial.print(treOsvetljena);
      stara = tockeSkupaj;
      
      //izpise skupne tocke
      //pobrise prejsno cifro
      lcd.setCursor(12, 0);
      lcd.print("    ");
      
      itoa(stTarc - tockeSkupaj, tockeSkupajArr, 10);
      lcd.setCursor(12, 0);
      lcd.print(tockeSkupajArr);
      
     }
      

      
      //izrise uro v spodnji vrstici
      lcd.setCursor(5, 1);
      izpisiCas((millis() - treMill)/100);
   break;
   
   case 3:
    piskacOn(3);
    nonStop = 0;
    preverjajSprememboTarc = 0;
    
    lcd.setCursor(0, 0);
    lcd.print("   Konec igre   ");
  
  
    break;


  }
}
int spisekPreostalih[10]; // TODO dodej max st tarc
int stPreostalih;

void programFSM3( ) { 
  char  izpisTocke[16];
  char  tockeSkupajArr[3];//arraj ki se uporablja za izpisovanje int-ov
  
  switch (programState) {
    case -1:
      //skonfigurira odstevalnik
      confOdstevalnik();
      
      programState = 0;
      //odstevalnik premakne programState naprej na 1
      break;

    case 1:
      programState = 2;
      
      //resetira vse tocke in pokaze vse tarce
      resetScore();
      //deaktivirajVse();
      //mislm da ni treba
      
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Preostalih: 0");
    
      //izpise st preostalih
      itoa(stTarc, tockeSkupajArr, 10);
      lcd.setCursor(12, 0);
      lcd.print(tockeSkupajArr);
      
      
      lcd.setCursor(0, 1);
      lcd.print("Cas: ");

      
      nonStop = 1;
      preverjajSprememboTarc = 0;
      stara = tockeSkupaj;
      treMill = millis();
      
      stPreostalih = stTarc;
      for(i=0;i<stTarc;i++){
        spisekPreostalih[i] = i;
      }
      
      treOsvetljena = random(stPreostalih-1);
      aktivirajTarco(spisekPreostalih[treOsvetljena]);
   break;

      
   case 2:
      if(stara != tockeSkupaj){
        //na radnom przge tarco ko je bila prejsna zadeta
        deaktivirajTarco(spisekPreostalih[treOsvetljena]);
        
        stPreostalih --;
        if(stPreostalih == 0){
          programState = 3;
          break;
        }
        for(i=treOsvetljena; i<stPreostalih; i++){
          
          spisekPreostalih[i] =  spisekPreostalih[i+1];
        }
        
        treOsvetljena = random(stPreostalih-1);
        aktivirajTarco(spisekPreostalih[treOsvetljena]);
        stara = tockeSkupaj;
        Serial.print(treOsvetljena);
        
        //pobrise prejsno cifro in izpise novo
        lcd.setCursor(12, 0);
        lcd.print("    ");
        
        itoa(stPreostalih, tockeSkupajArr, 10);
        lcd.setCursor(12, 0);
        lcd.print(tockeSkupajArr);
      }
      

      
      //izrise uro v spodnji vrstici
      lcd.setCursor(5, 1);
      izpisiCas((millis() - treMill)/100);
   break;
   
    case 3:
    piskacOn(3);
    nonStop = 0;
    preverjajSprememboTarc = 0;
    
    lcd.setCursor(0, 0);
    lcd.print("   Konec igre   ");
  
  
    break;


  }
}



void programFSM4() { //prog 4 final state mašina
  char  izpisTocke[16];
  char  tockeSkupajArr[3];
  
  switch (programState) {
    case -1:
      //skonfigurira odstevalnik
      confOdstevalnik();
      
      programState = 0;

      pauza = spomin[MEM_PROG4_CAS] * 1000;
      sPrint("pauza:",pauza);
      treMill = 0;
      //odstevalnik premakne programState naprej na 1
      break;

    case 1:
      programState = 2;

      //resetira vse tocke in pokaze vse tarce"tarc
      resetScore();
      //deaktivirajVse();
      //mislm da ni treba
      
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("zadetkov:  0/   ");
      
      itoa(stTarc, tockeSkupajArr, 10);
      lcd.setCursor(13, 0);
      lcd.print(tockeSkupajArr);
      
      itoa(tockeSkupaj, tockeSkupajArr, 10);
      lcd.setCursor(11, 0);
      lcd.print(tockeSkupajArr);
      
      //itoa(stTarc, tockeSkupajArr, 10);
      //lcd.setCursor(12, 0);
      //lcd.print(tockeSkupajArr);
      
      lcd.setCursor(0, 1);
      lcd.print("Cas:");
      


      //init risalnik tock struct
      risalnikTock.nacin = DRAW_TOCKE_KLIK;
      risalnikTock.pozicija = 16;
      
      nonStop = 1;
      preverjajSprememboTarc = 0;
      treOsvetljena = 0;      //to je tarca ki jo najprej przge
      stara = tockeSkupaj;
      treMill = millis();
      aktivirajTarco(treOsvetljena);
   break;

      
   case 2:
      //postavitev tarc
      //priziga tarce eno za drugo
      //prizge nasledno ce je cas > pauze ali ce je tarca zadeta
      mil = millis();
      if(mil - treMill > pauza || stara != tockeSkupaj){
        stara = tockeSkupaj;
        treMill = mil;
       
        deaktivirajTarco(treOsvetljena);
        
        treOsvetljena ++;
        //ce so bile ze zadete vse
        if(treOsvetljena > stTarc-1){
          programState = 3;
          nonStop = 1;
        }else{
          aktivirajTarco(treOsvetljena);
        }
      }
      
      //izris na ekran
      //izpise skupne tocke
      itoa(tockeSkupaj, tockeSkupajArr, 10);
      if(tockeSkupaj > 9) lcd.setCursor(10, 0);
      else lcd.setCursor(11, 0);
      lcd.print(tockeSkupajArr);
    
      //izrise uro v spodnji vrstici
      lcd.setCursor(5, 1);
      izpisiCas((pauza - mil + treMill)/100);
      
      lcd.setCursor(5, 1);

   break;
   
  case 3:
  
    piskacOn(3);
    nonStop = 0;
    preverjajSprememboTarc = 0;
    
    lcd.setCursor(0, 0);
    lcd.print("  Konec igre   ");
    
    
    lcd.setCursor(0, 1);
    lcd.print("zadetkov:  0/   ");
    
    itoa(stTarc, tockeSkupajArr, 10);
    lcd.setCursor(13, 1);
    lcd.print(tockeSkupajArr);
    
  
    itoa(tockeSkupaj, tockeSkupajArr, 10);
    if(tockeSkupaj > 9) lcd.setCursor(10, 1);
    else lcd.setCursor(11, 1);
    lcd.print(tockeSkupajArr);
    
  
  
  break;

  }
}

//izpise long z zadnjo številko kot decimalko ("xx.x")
//ostala mesta zafila s presledki
void izpisiCas(long cas){
    char casArrOut[7];
    int  casArrOutIndex = 0;
    

    
    //pretvori cas v int
    itoa(cas, casArrOut, 10);
    
    //najde zadnjo cifro
    int index = getDecLength(cas)-1;
    
    
    char stack = casArrOut[index];
    if(cas < 10)casArrOut[index++] = '0';
    
    casArrOut[index++] = '.';
    casArrOut[index++] = stack;
    casArrOut[index++] = 's';
    
    while(index < 7){
      casArrOut[index++] = ' ';
    }
    
    casArrOut[index++] = 0;
    
    
    lcd.print(casArrOut);
}
void programFSM5() { //prog 5 final state mašina
  char  izpisTocke[16];
  char  arr[3];
  
  switch (programState) {
    case -1:
      resetScore();
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("  Zadeni prvo");
      
      lcd.setCursor(0, 1);
      lcd.print(" tarco in zacni");
      
      nonStop = 0;
      preverjajSprememboTarc = 1;
      
      treOsvetljena = 0;      
      aktivirajTarco(treOsvetljena);
      
      programState = 1;
      Serial.print("fsm5 -1");

    break;
    
    case 1:
      Serial.print("fsm5 1");
      //tarca je bila prvic zadeta
      piskacOn(3);
      treMill = millis();
      
      deaktivirajTarco(treOsvetljena);
      treOsvetljena ++;
      aktivirajTarco(treOsvetljena);
      stara = tockeSkupaj;
      
      lcd.setCursor(0, 0);
      lcd.print("Preostale:      ");
      
      
      lcd.setCursor(0, 1);
      lcd.print("Cas: 0.0s       ");
      

     
     nonStop = 1; 
     programState = 2; 
    
    break;
    
    case 2:
      //drugi pogoj se izvede samo v primeru ko je bila izbrana samo ena tarca
      if(stara != tockeSkupaj || treOsvetljena > stTarc-1){
       
        deaktivirajTarco(treOsvetljena);
        
        treOsvetljena ++;
        if(treOsvetljena > stTarc-1){
          
          programState = 3;
          break;
        } 
        aktivirajTarco(treOsvetljena);
        stara = tockeSkupaj;
      }
      
      //izrise uro v spodnji vrstici
      lcd.setCursor(5, 1);
      izpisiCas((millis() - treMill)/100);
      
      lcd.setCursor(11, 0);
      itoa(stTarc-treOsvetljena, arr,10);
      lcd.print(arr);
    break;
    
    case 3:
    
      piskacOn(3);
      nonStop = 0;
      preverjajSprememboTarc = 0;
            
      lcd.setCursor(0, 0);
      lcd.print("   Konec igre   ");
      

    break;

  }
}

void odstevaj() {
  //sPrint("ost State:", odstevalnik.state);
  switch (odstevalnik.state) {
    case 1:
      char outStr[16];
      lcd.setCursor(0, 0);
      lcd.print("Igra se zacne v");
      char cifra[2];
      odstevalnik.state = 2;
      odstevalnik.mills = 0;

    case 2:
      if (millis() - odstevalnik.mills > 960) {
        odstevalnik.mills = millis();
        if (odstevalnik.stOdstevanj-- == 0) {
          odstevalnik.state = 3;
          break;
        }
        lcd.setCursor(0, 1);
        itoa(odstevalnik.stOdstevanj + 1, cifra, 10);
        lcd.print(pretvoriBesedilo(outStr, cifra, NASLOV));
        piskacOn(3);
      }
      break;

    case 3:
      //lcd.setCursor(0, 1);
      //lcd.print(pretvoriBesedilo(outStr, "! GO !", NASLOV));
      piskacOn(10);
      if (millis() - odstevalnik.mills > 100) {
        state = odstevalnik.returnState;
        sPrint("ret State:", state);
        programState = 1;
      }
      break;
  }
}

void drawScreen() {
  char outStr[16];

  // izpiše naslov
  lcd.setCursor(0, 0); // postav ga na sredino //TODO: IZRUSI SAMO TAKRAT KO GA se spremeni !!
  lcd.print(pretvoriBesedilo(&outStr[0], ((s_ekran*)vsiEkrani[state])->naslov, NASLOV));

  //ne izrse puscic ce je samo 1 izbor
  int tipIzrisa = BESEDILO;
  if(((s_ekran*)vsiEkrani[state])->st_elementov < 2)tipIzrisa = NASLOV;
  
  //izpiše spodnje besedilo
  lcd.setCursor(0, 1);
  lcd.print(pretvoriBesedilo(&outStr[0], ((s_ekran*)vsiEkrani[state])->elementi[((s_ekran*)vsiEkrani[state])->trenutnoIzbran].besedilo, tipIzrisa));
  programState = -1; //TODO premakn to na bolsi mest
}

void drawScreenNast() {
  char outStr[16];
  char vrednostStr[4];

  // izpiše naslov
  lcd.setCursor(0, 0); // postav ga na sredino //TODO: IZRUSI SAMO TAKRAT KO GA se spremeni !!
  lcd.print(pretvoriBesedilo(&outStr[0], ((s_ekranNastavitve*)vsiEkrani[state])->naslov, NASLOV));

  //izpiše spodnje besedilo
  lcd.setCursor(0, 1);
  //if(((s_ekranNastavitve*)vsiEkrani[state])->focus == OFF){
  uint8_t treIzbran = ((s_ekranNastavitve*)vsiEkrani[state])->trenutnoIzbran;
  uint8_t indexParametra = ((s_ekranNastavitve*)vsiEkrani[state])->indexi[treIzbran];
  char *opis = parametri[indexParametra].opis;
  uint32_t vrednost = parametri[indexParametra].vrednost;//((s_ekranNastavitve*)vsiEkrani[state])->parameter[treIzbran].vrednost;
  int b = 0; //<-- stevec ki se premika po poljih
  sPrint("Vrednost: ", vrednost);
  /*
  Serial.println(d_retState);
  Serial.println(d_tretIzbran);
  Serial.println(d_indexParametra);
  Serial.println(opis);
  */

  //postavi puscice ce je elementov vec kot 2
  if(((s_ekranNastavitve*)vsiEkrani[state])->stParametrov > 2){
    outStr[b++] = ZNAK_LEVO;
    outStr[15] = ZNAK_DESNO;
  }else{
    outStr[b++] = ' ';
    outStr[15] = ' '; 
  }
  uint8_t dolzina = (getDecLength(vrednost) + getLngth(opis) + 1);
  while (b < 8 - (dolzina - dolzina / 2)) {
    outStr[b++] = ' ';
  }


  //zapise opis parametra

  // postavi na sredino
  while (*opis != 0) {
    outStr[b++] = *opis;
    opis ++;
  }
  outStr[b++] = ' ';
  //zapise vrednost
  itoa(vrednost, vrednostStr, 10);
  //itoa(get_free_memory(),vrednostStr,10);
  for (i = 0; i < getDecLength(vrednost); b++, i++) {
    outStr[b] = vrednostStr[i];
  }
  //zapise presledke do konca
  while (b < 15) {
    outStr[b++] = ' ';
  }

  lcd.print(outStr);
  //}else{
  //}
}


void drawScreenEdit() {
  char outStr[16];
  
  //naslovne vrstico pustimo pri miru
  //ampak temu ocitno ne bo tako ker zaradi ene cudne napake ki je v zgornjo vrstico zapisala
  //en smorn jo ne morm pustiti pri miru FUACK
  //TODO odkrij to mistririjozno napako !
  lcd.setCursor(0, 0);
  lcd.print(pretvoriBesedilo(&outStr[0], ((s_ekranNastavitve*)vsiEkrani[d_retState])->naslov, NASLOV));
  
  //spreminjamo samo ta drugo
  char vrednostStr[4]; // charr arr v katerga zapisemo vrednost
  int b = 0;               // stevec ki se premika po poljih naprej

  
  char *opis = d_parameter.opis;

  uint8_t dolzina = (getDecLength(d_parameter.vrednost) + getLngth(opis) + 5);
  //zapise opis
  while (b < 8 - (dolzina - dolzina / 2)) {
    outStr[b++] = ' ';
  }

  while (*opis != 0) {
    outStr[b++] = *opis;
    opis ++;
  }

  //postavi puscico levo
  outStr[b++] = ' ';
  outStr[b++] = ZNAK_LEVO;
  outStr[b++] = ' ';


  //zapise vrednost
  itoa(d_parameter.vrednost, vrednostStr, 10);
  for (i = 0; i < getDecLength(d_parameter.vrednost); b++, i++) {
    outStr[b] = vrednostStr[i];
  }

  outStr[b++] = ' ';
  outStr[b++] = ZNAK_DESNO;
  outStr[b++] = ' ';

  //zapise presledke do konca
  while (b < 16) {
    outStr[b++] = ' ';
  }

  lcd.setCursor(0, 1);
  lcd.print(outStr);
}

uint8_t preveriTipke() {
  if (get_LCD_button(btnUP)) {
    //Serial.println(((s_ekran*)vsiEkrani[state])->tipke[btnUP]);
    return izvediUkaz(((s_ekran*)vsiEkrani[state])->tipke[btnUP]);
  }
  else if (get_LCD_button(btnDOWN)) {
    //Serial.println(((s_ekran*)vsiEkrani[state])->tipke[btnDOWN]);
    return izvediUkaz(((s_ekran*)vsiEkrani[state])->tipke[btnDOWN]);
  }
  else if (get_LCD_button(btnRIGHT)) {
    //Serial.println("RIGHT");
    return izvediUkaz(((s_ekran*)vsiEkrani[state])->tipke[btnRIGHT]);
  }
  else if (get_LCD_button(btnLEFT)) {
    //Serial.println("LEFT");
    return izvediUkaz(((s_ekran*)vsiEkrani[state])->tipke[btnLEFT]);
  } else if (get_LCD_button(btnSELECT)) {
    //Serial.println("SELECT");
    return izvediUkaz(((s_ekran*)vsiEkrani[state])->tipke[btnSELECT]);
  }
  //else if(get_LCD_button(btnUP));
  return 0;
}

uint32_t zadnjiPritisk;
uint8_t stPritiskov = 0;

int defVrednost;
uint8_t izvediUkaz(uint8_t ukaz) {
  if (ukaz == 0)return 0;
  if (ukaz < MAX_EKRANOV) {
    state = ukaz;
    return 1;
  }
  switch (ukaz) {
    case FUN_TIPKE:
      //Serial.println(((s_ekran*)vsiEkrani[state])->elementi[((s_ekran*)vsiEkrani[state])->trenutnoIzbran].funkcija);
      return izvediUkaz(((s_ekran*)vsiEkrani[state])->elementi[((s_ekran*)vsiEkrani[state])->trenutnoIzbran].funkcija);

    case INC_IZBRAN:
      if (((s_ekran*)vsiEkrani[state])->trenutnoIzbran < ((s_ekran*)vsiEkrani[state])->st_elementov - 1) {
        ((s_ekran*)vsiEkrani[state])->trenutnoIzbran ++;
      } else {
        ((s_ekran*)vsiEkrani[state])->trenutnoIzbran = 0;
      }
      return 1;

    case DEC_IZBRAN:
      if (((s_ekran*)vsiEkrani[state])->trenutnoIzbran > 0) {
        ((s_ekran*)vsiEkrani[state])->trenutnoIzbran --;
      } else {
        ((s_ekran*)vsiEkrani[state])->trenutnoIzbran = ((s_ekran*)vsiEkrani[state])->st_elementov - 1;
      }
      return 1;


    case NAST_INC_IZBRAN:
      if (((s_ekranNastavitve*)vsiEkrani[state])->trenutnoIzbran < ((s_ekranNastavitve*)vsiEkrani[state])->stParametrov - 1) {
        ((s_ekranNastavitve*)vsiEkrani[state])->trenutnoIzbran ++;
      } else {
        ((s_ekranNastavitve*)vsiEkrani[state])->trenutnoIzbran = 0;
      }
      return 1;

    case NAST_DEC_IZBRAN:
      if (((s_ekranNastavitve*)vsiEkrani[state])->trenutnoIzbran > 0) {
        ((s_ekranNastavitve*)vsiEkrani[state])->trenutnoIzbran --;
      } else {
        ((s_ekranNastavitve*)vsiEkrani[state])->trenutnoIzbran = ((s_ekranNastavitve*)vsiEkrani[state])->stParametrov - 1;
      }
      return 1;


    case NAST_EDIT_DEC:
      d_parameter.vrednost -= d_parameter.korak;
      if (d_parameter.vrednost < d_parameter.min) {
        d_parameter.vrednost = d_parameter.min;
      }
      return 1;

    case NAST_EDIT_INC:

      d_parameter.vrednost += d_parameter.korak;
      if (d_parameter.vrednost > d_parameter.max) {
        d_parameter.vrednost = d_parameter.max;
      }

      return 1;

    case NAST_EDIT:
      //ko se poklice okno nastavitve
      
      // zapovne si state da ve kere podatke ureja
      d_retState = state;

      
      
      //prebere vresnost iz spomina
      defVrednost = d_parameter.vrednost;
      //sPrint("defV:", defVrednost);
      d_parameter.vrednost = spomin[d_indexParametra];
      Serial.println(d_indexParametra);
      sPrint("izSpomina:", spomin[d_indexParametra]);
      
      if ( d_parameter.max < d_parameter.vrednost || d_parameter.vrednost < d_parameter.min) {
        Serial.println("napacna");
        d_parameter.vrednost = defVrednost;
      }

      state = NAST_EDIT;
      Serial.println("We are in");
      return 1;

    case NAST_EDIT_FINISH:
      
      if(spomin[d_indexParametra] != d_parameter.vrednost){
        //zapise vrednost nazaj v spomin
        spomin[d_indexParametra] = d_parameter.vrednost;
        
        //EEPROM.write(d_parameter.index, d_parameter.vrednost); TODO: urihtej ta spomi!
        
        dueFlashStorage.write(d_indexParametra, d_parameter.vrednost / d_parameter.korak);
        sPrint("zapis v spomin:", dueFlashStorage.read(d_indexParametra) * d_parameter.korak);
        
      }else{
        Serial.println("Ni bilo spremembe!");
      }
      
      if(d_indexParametra == MEM_ST_TARC)stTarc = d_parameter.vrednost;
      else if (d_indexParametra == MEM_ZAMIK)setNoReadTime(d_parameter.vrednost);
      
      sPrint("koncna:", spomin[d_indexParametra]);
      state = d_retState;
      return 1;
      
    case PROG1_TOCKE_DEC:
      risalnikTock.pozicija --;
      
    return 1;
    
    case PROG1_TOCKE_INC:
      risalnikTock.pozicija ++;

    return 1;
    
    case STEJ_PRITISKE:
      if(millis() - zadnjiPritisk < 500){
        stPritiskov ++;
        if(stPritiskov > 10){
          state = MENI_MADE_BY;
        }
      }else{
        stPritiskov = 0;
      }
      zadnjiPritisk = millis();
    return 1;
    
    default:
      Serial.println("neznan ukaz");
    break;

  }

}

void sPrint(char* c, int a) {
  Serial.print(c);
  Serial.println(a);
}

void getSpomin() {
 
  //deklaracija parametrov	opis,	        min,	max,	def,	korak
  parametri[MEM_ST_TARC]=	{"st. tarc:",	1,	10,	10,	1	};
  parametri[MEM_ZAMIK]=		{"zamik:",	100,	1000,	100,	50	};
  
  parametri[MEM_PROG1_CAS]=	{"cas:",	10,	200,	60,	10	};
  //parametri[MEM_PROG1_TEZ]=	{"tezavnost:",	1,	5,	3,	1	};
  
  parametri[MEM_PROG2_TEZ]=	{"tezavnost:",	1,	5,	3,	1	};
  parametri[MEM_PROG2_CAS]=	{"cas:",	10,	200,	60,	10	};
  
  parametri[MEM_PROG3_TEZ]=	{"tezavnost:",	1,	5,	3,	1	};
  parametri[MEM_PROG3_CAS]=	{"cas:",	10,	200,	60,	10	};
  
  parametri[MEM_PROG4_TEZ]=	{"tezavnost:",	1,	5,	3,	1	};
  parametri[MEM_PROG4_CAS]=	{"cas:",	1,	30,	10,	1	};
  
  parametri[MEM_PROG5_TEZ]=	{"tezavnost:",	1,	5,	3,	1	};
  parametri[MEM_PROG5_CAS]=	{"cas:",	10,	200,	60,	10	};
  
  //nafila ceu spomin iz EEPROM-a
  for (i = 0; i < ST_SPOMINA; i++) {
    spomin[i] = dueFlashStorage.read(i) * parametri[i].korak;
    
     Serial.print(i);
     Serial.print(": ");
     
    //vrednost v spominu je izven meja
    if(spomin[i] > parametri[i].max || spomin[i]  < parametri[i].min){
      Serial.print("os:");
      Serial.print(spomin[i]);
      
      //na zacetku ko se ni nc spremenjen je v .vrednosti notr osnovna def vrednost
      spomin[i] = parametri[i].vrednost;
      
      Serial.print("  ");
      Serial.print("nova:");
    }
   
    parametri[i].vrednost = spomin[i];
    
    Serial.println(spomin[i]);
    
    
  }
}

void initEkrane() {
  vsiEkrani[NAST_EDIT] =         (uint32_t)(&editNast);

  vsiEkrani[MENI_GLAVNI] =       (uint32_t)(&mainMenu);
  vsiEkrani[MENI_IGRAJ] =        (uint32_t)(&igrajMenu);
  vsiEkrani[MENI_NASTAVITVE] =   (uint32_t)(&nastavitveMenu);
  vsiEkrani[MENI_INFO] =         (uint32_t)(&infoMenu);
  vsiEkrani[MENI_MADE_BY] =      (uint32_t)(&madeByMenu);

  vsiEkrani[NAST_ST_TARC] =      (uint32_t)(&stTarcNast);
  vsiEkrani[NAST_SENZORJI] =     (uint32_t)(&senzorjiNast);
  vsiEkrani[ODSTEVAJ] =          (uint32_t)(&odstavajOkno);

  vsiEkrani[MENI_PROG1] =   	 (uint32_t)(&prog1Menu);
  vsiEkrani[MENI_PROG2] =   	 (uint32_t)(&prog2Menu);
  vsiEkrani[MENI_PROG3] =   	 (uint32_t)(&prog3Menu);
  vsiEkrani[MENI_PROG4] =   	 (uint32_t)(&prog4Menu);
  vsiEkrani[MENI_PROG5] =   	 (uint32_t)(&prog5Menu);

  vsiEkrani[PROGRAM_1] =   	 (uint32_t)(&program1);
  vsiEkrani[PROGRAM_2] =   	 (uint32_t)(&program2);
  vsiEkrani[PROGRAM_3] =   	 (uint32_t)(&program3);
  vsiEkrani[PROGRAM_4] =   	 (uint32_t)(&program4);
  vsiEkrani[PROGRAM_5] =   	 (uint32_t)(&program5);

  vsiEkrani[NAST_PROG1] =   	 (uint32_t)(&prog1Nast);
  vsiEkrani[NAST_PROG2] =   	 (uint32_t)(&prog2Nast);
  vsiEkrani[NAST_PROG3] =   	 (uint32_t)(&prog3Nast);
  vsiEkrani[NAST_PROG4] =   	 (uint32_t)(&prog4Nast);
  vsiEkrani[NAST_PROG5] =   	 (uint32_t)(&prog5Nast);


}


//pretvori string v 16 dolg niz znakov ki je primeren za izpis
char* pretvoriBesedilo(char* out, char *str, int tip) {
  int dolzina = getLngth(str);
  int dolOuta = 16;                   // dolžina izhodnega stringa
  int i = 0;                          //števec
  if (tip == BESEDILO) {
    if (dolzina > 14)dolzina = 14;
    out[i++] = ZNAK_LEVO;                 // na provo mesto zališe puščico levo
    dolOuta = 15;                   // skrajša dolžino izhodnega striga da ne povoz desne puščice
    out[15] = ZNAK_DESNO;                  // na zadnje mesto zapie puščico desno
  } else {
    if (dolzina > 16)dolzina = 16;
  }

  int pozStr = 8 - dolzina / 2;    // pozicija stringa
  if (dolzina & 0x1)pozStr --;     // če ni deljiv z 2 ga premakne v levo

  while (i < pozStr) {
    out[i++] = ' ';             //zapiše presledke pred stringom
  }
  while (i < pozStr + dolzina) {
    out[i++] = str[i - pozStr - 1]; //zapiše string
  }
  while (i < dolOuta) {
    out[i++] = ' ';             //zapiše prtesledke po besedilu
  }
  out[16] = 0;                    // na konec stringa doda nulo
  return &out[0];
}

// vrne dolžino stringa če ima na koncu 0
int getLngth(char * c) {
  int dolzina = 0;
  while (*c++ != 0)dolzina ++;
  return dolzina;
}

int getDecLength(long n) {
  if (n < 100000)
  {
    // 5 or less
    if (n < 100)
    {
      // 1 or 2
      if (n < 10)
        return 1;
      else
        return 2;
    }
    else
    {
      // 3 or 4 or 5
      if (n < 1000)
        return 3;
      else
      {
        // 4 or 5
        if (n < 10000)
          return 4;
        else
          return 5;
      }
    }
  }
  else
  {
    // 6 or more
    if (n < 10000000)
    {
      // 6 or 7
      if (n < 1000000)
        return 6;
      else
        return 7;
    }
    else
    {
      // 8 to 10
      if (n < 100000000)
        return 8;
      else
      {
        // 9 or 10
        if (n < 1000000000)
          return 9;
        else
          return 10;
      }
    }
  }
}



