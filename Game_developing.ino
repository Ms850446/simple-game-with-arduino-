/* 
 * LCD RS pin to digital pin 2
 * LCD Enable pin to digital pin 3
 * LCD D4 pin to digital pin 4
 * LCD D5 pin to digital pin 5
 * LCD D6 pin to digital pin 6
 * LCD D7 pin to digital pin 7
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 */
#include<LiquidCrystal.h>
#define rs 2
#define en 3
#define d4 4
#define d5 5
#define d6 6
#define d7 7
#define right A0 //press of the right move
#define up A1 //press of the up move
#define left A2 //press of the left move
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
  bool Game=true;
  bool n;
  int x=0;
  int y=0;
  bool pressed=false;
  unsigned long pressedTime=millis();
  int blocks[30];
  int yblock[30];
  int index=0;
  unsigned long Time;
  unsigned long TimeMove;
// this block for shape of body and the block
//////////////////////////////////////////////////////////


byte body[8] = {
  B00000,
  B00000,
  B00100,
  B01110,
  B10101,
  B00100,
  B00100,
  B00100
  };
byte block[8] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
  };



////////////////////////////////////////////////////////




void setup() {
pinMode(A0,INPUT);
pinMode(A1,INPUT);  
pinMode(A2,INPUT);
  
  lcd.createChar(2,body);
  lcd.createChar(3,block);
  lcd.begin(16,2);
  lcd.setCursor(3,0);
  lcd.print("welcome to ");
  lcd.setCursor(3,1);
  lcd.print("the game");
  delay(5000);
  lcd.clear();
  lcd.home();   
  lcd.write(2);

  Time=millis();
  TimeMove=millis();
}



void loop() {
      if(Game)
      {
                  if(millis()-TimeMove>1000)
                  { for(int i=0; i<30;i++)
                    { if(blocks[i]==0&&blocks[i+1]==0)
                        break;
                        blockoff(i);
                        if(blocks[i]==0)
                       continue;
                        blocks[i]--;
                        lcd.setCursor(blocks[i],yblock[i]);
                        lcd.write(3); 
                                      }
                                           TimeMove=millis();  }
                         

                  
                  if(millis()-Time>2000){
                    int i =Check();

                      blocks[i]=15;
                   
                    lcd.setCursor(blocks[i],Y(i));
                    lcd.write(3);
                    
                    Time=millis();
                    }
        
              



 
if(millis()-pressedTime>200){
if(digitalRead(right)==HIGH&&!pressed){
  off();
  x++;
  lcd.setCursor(x,y);
  lcd.write(2);
  pressed=true;
  pressedTime=millis();
  }
if(digitalRead(up)==HIGH&&!pressed){
  off();
  switch(y){
  case 0: {y=1;break;}
  default: y=0; }

  lcd.setCursor(x,y);
  lcd.write(2);
  pressed=true;
pressedTime=millis();
  
  }
if(digitalRead(left)==HIGH&&!pressed){
  off();
  x--;
  lcd.setCursor(x,y);
  lcd.write(2);
  pressed=true; 
  pressedTime=millis();                      
  }

if(pressed&&digitalRead(left)==LOW&&digitalRead(up)==LOW&&digitalRead(right)==LOW)
pressed=false;

}

crash();
n=true;
}

else {
   
  if(n)
  lcd.clear();
        
  lcd.setCursor(3,0);
  lcd.print("Game over");
  if(n){
  delay(5000);
  n=false;}
  lcd.setCursor(0,1);
  lcd.print("press up to start");
  if(digitalRead(up)==HIGH)
    { for (int i=0;i<30;i++)
      blocks[i]=0;
      lcd.clear();
  {   lcd.setCursor(0,0); // the start of the block
      x=0;
      y=0;
      lcd.write(2);
      Time=millis();
      TimeMove=millis(); 
      pressed=true;   } // this block for restarting all first conditions of the game
      Game=true;
    }
  }


}

void off(){
  lcd.setCursor(x,y);
  lcd.print(" ");
  
  }
  
  void blockoff(int i){
    lcd.setCursor(blocks[i],yblock[i]);
    lcd.print(" ");
    
    }

  bool crash(){
    for(int i=0;i<30;i++){
             if(blocks[i]==0&&blocks[i+1]==0)
                        break;
      if(x==blocks[i]&&y==yblock[i])
     Game=false;

      }
       return Game; 
    }

    int Y(int i){
      randomSeed(analogRead(A5));
      yblock[i]=random(0,10);
      if(yblock[i]>5)
      {yblock[i]=1;
        return yblock[i];}
      yblock[i]=0;
      return yblock[i];
      
      }

int Check(){
  for(int i=0;i<30;i++){
   if( blocks[i]==0)
   {index=i;  break;}
    
    }
  return index;
  }
