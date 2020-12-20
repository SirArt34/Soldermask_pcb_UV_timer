#include <Wire.h>   // standardowa biblioteka Arduino
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

#define OK 4    //przycisk zatwierdzania czasu
#define UV 10
#define START 11 //przycisk START

    //zmienne przedstawiające menu i dzialanie uv 
    int ustCzasu=0;  //0 - ustawienie MIN, 1 - potwierdzenie startu, 2 - odliczanie, 
    #define USTAWIENIA_MIN 0 
    #define USTAWIENIA_SEC 1 
    #define START 2 
    #define ODLICZANIE  3 

        // Wartosci potrzebne do enkoderow
        int encoder0PinA = 2;
        int encoder0PinB = 3;
        int encoder0PinA2 = 2;
        int encoder0PinB2 = 3;
        word encoder0Pos = 0;
        word encoder0Pos2 = 0;
        int encoder0PinALast = LOW;
        int encoder0PinALast2 = LOW;
        int n = LOW;
        int n2 = LOW;
        int a = 0;

//zmienne zawierające czas 
unsigned long time_on = 0;       //czas włączenia pompy 
unsigned long aktualny_czas=0;   //aktualny czas 
int odliczanie=0;

void setup() 
  { 
  Serial.begin(9600); 
  lcd.begin(16,2);
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("Utwardzacz");
    delay(400);
  lcd.setCursor(1,1);
  lcd.print("do Soldermaski");
    delay(400);  
  lcd.clear();
   lcd.setCursor(1,0);
  lcd.print("Utwardzacz UV");
    delay(400);
  lcd.setCursor(0,1);
  lcd.print("ver 1.0");
    delay(400);
  lcd.setCursor(10,1);
  lcd.print("2019r");
    delay(400);
  lcd.clear();

  pinMode(UV, OUTPUT);            // Przekznik UV
  pinMode(OK, INPUT_PULLUP);      // Zatwierdzanie czasu
  pinMode(START, INPUT_PULLUP);   // START
  pinMode (encoder0PinA, INPUT);
  pinMode (encoder0PinB, INPUT);

  
  time_on = 0; 
  ustCzasu = 0; 
    } 
      
    void loop() 
    { 
      //Pobierz liczbe milisekund od startu 
      aktualny_czas = millis(); 



 //w pętli switch sterujemy ledami  
      switch(ustCzasu) 
      { 
        //---------------------------------------------------------------------------- 
        case USTAWIENIA_MIN: 

             lcd.setCursor(2,0);
             lcd.print("USTAWIENIA:");
             lcd.setCursor(0,1);
             lcd.print("MIN:");                                                                                         
             if (encoder0Pos < 10) lcd.print(" ");                  
             lcd.print(encoder0Pos, DEC);
             lcd.setCursor(7,1);
             lcd.print("min");
             lcd.setCursor(11,1);
             lcd.print(encoder0Pos2);
             lcd.setCursor(13,1);
             lcd.print("sec");
                        
n = digitalRead(encoder0PinA);
  encoder0Pos = constrain(encoder0Pos, 1, 59);
  if ((encoder0PinALast == LOW) && (n == HIGH)) {
    if (digitalRead(encoder0PinB) == LOW) {
      encoder0Pos--;
    } else {
      encoder0Pos++;
    }

  }
  encoder0PinALast = n;
              //---------------------------------LCD-------------------------//

              if (digitalRead(OK) == LOW){
                delay(200);
                lcd.clear();
                ustCzasu=USTAWIENIA_SEC; 
                } //wyjście z if'a 
                
         break;    //wyjście ze switch 
  //--------------------------------------------------------------------------//       
        case USTAWIENIA_SEC: 
             
             lcd.setCursor(2,0);
             lcd.print("USTAWIENIA:");
             lcd.setCursor(0,1);
             lcd.print("SEC:");                                                                                         
             if (encoder0Pos < 10) lcd.print(" ");                  
             lcd.print(encoder0Pos, DEC);
             lcd.setCursor(7,1);
             lcd.print("min");
             lcd.setCursor(11,1);
             lcd.print(encoder0Pos2);
             lcd.setCursor(13,1);
             lcd.print("sec");
             
n2 = digitalRead(encoder0PinA2);
  encoder0Pos2 = constrain(encoder0Pos2, 1, 59);
  if ((encoder0PinALast2 == LOW) && (n2 == HIGH)) {
    if (digitalRead(encoder0PinB2) == LOW) {
      encoder0Pos2--;
    } else {
      encoder0Pos2++;
    }

  }
  encoder0PinALast2 = n2;
                if (digitalRead(OK) == LOW){
                delay(200);
                lcd.clear();
                ustCzasu=START; 

          break;    //wyjście ze switch 
        //---------------------------------------------------------------------------- 
                case START: 
 //----------------------------------LCD----------------------------------------------//

      odliczanie=encoder0Pos*60+encoder0Pos2;
      for (int a=odliczanie; a>=0; a--)
{
      lcd.setCursor(0, 0);
      lcd.print("Start");
      lcd.setCursor(0, 1);
      lcd.print("Pozostalo: ");
      lcd.print(a);
      if (a < 10) lcd.print("  ");  
delay(1000);
}


                      
                if (digitalRead(OK) == LOW){
                delay(200);
                lcd.clear();
                ustCzasu=USTAWIENIA_MIN; 
                } 
          break;    //wyjście ze switch 
        //---------------------------------------------------------------------------- 
        
         case ODLICZANIE: 
           
 //----------------------------------LCD----------------------------------------------//
             lcd.setCursor(2,0);
             lcd.print("ODLICZANIE");
             lcd.setCursor(0,1);
             lcd.print(encoder0Pos);           
             lcd.setCursor(6,1);
             lcd.print(encoder0Pos2);  
                if (digitalRead(OK) == LOW){
                delay(200);
                lcd.clear();
                ustCzasu=USTAWIENIA_MIN; 
                } 
   //wyjście ze switch 
      default:
      break;
      }       //koniec switch 
}}
      
