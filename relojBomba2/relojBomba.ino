#define BTN_UP 0
#define BTN_DOWN 1
#define BTN_LEFT 2
#define BTN_RIGHT 3
#define BTN_SELECT 4
#define BTN_NONE 5
#define STATE_TIME 1
#define STATE_REGRE 2

#include <LiquidCrystal.h>
LiquidCrystal lcd(4,5,6,7,8,9); //FUNCIONA EN EL SIM
//LiquidCrystal lcd(8,9,4,5,6,7); //FUNCIONA EN EL DISP. REAL

int value = 0;
int minutos = 0;
int segundos = 0;
int estadoAnterior = BTN_NONE;
int estadoActual = BTN_NONE;
int estadoAnterior2 = 0;
int estadoActual2 = 5;
int posCursor = 5;
int aux1 = 0;
int aux2 = 0;
int aux3 = 0;
int aux4 = 0;
int state;
long tInicial = 0;
int tiempoBomba = 0;

int readButton(int value){
  if(value <70)
    return BTN_RIGHT;
  if(value <235)
    return BTN_UP;
  if(value <416)
    return BTN_DOWN;
  if(value <621)
    return BTN_LEFT;
  if(value <881)
    return BTN_SELECT;
  return BTN_NONE;
}

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.display();
  
  lcd.setCursor(5,0);
  lcd.print(aux1);
  lcd.print(aux2);
  lcd.print(":");
  lcd.print(aux3);
  lcd.print(aux4);
    
  lcd.setCursor(posCursor,1);
  lcd.print("^");
  state = STATE_TIME;
}

void stateTime(){
  value = analogRead(A0); 
  estadoActual = readButton(value);
  lcd.setCursor(5,0);
  if(estadoActual == BTN_NONE){
    estadoAnterior = BTN_NONE;
    estadoAnterior2 = 0;
  }
  if(estadoAnterior == BTN_NONE && estadoActual != BTN_NONE){
    switch(estadoActual){
      case BTN_RIGHT:
        if(estadoAnterior != BTN_RIGHT){
          if(posCursor == 5 || posCursor == 8){
            lcd.setCursor(posCursor,1);
            lcd.print(" ");
            posCursor++;
          }
          else if(posCursor == 6){
            lcd.setCursor(posCursor,1);
            lcd.print(" ");
            posCursor+=2;
          }
          estadoAnterior = BTN_RIGHT;
        }
        break;
      case BTN_LEFT:
        if(estadoAnterior != BTN_LEFT){
          if(posCursor == 6 || posCursor == 9){
            lcd.setCursor(posCursor,1);
            lcd.print(" ");
            posCursor--;
          }
          else if(posCursor == 8){
            lcd.setCursor(posCursor,1);
            lcd.print(" ");
            posCursor-=2;
          }
          estadoAnterior = BTN_LEFT;
        }
        break;
      case BTN_UP:
        if(estadoAnterior != BTN_UP){
          if(posCursor == 5){
            estadoActual2 = 5;
            if(estadoActual2 == 5 && estadoAnterior2 != 5){
              lcd.setCursor(posCursor,0);
              lcd.print(" ");
              aux1++;
            }
            estadoAnterior2 = 5;
          }
          if(posCursor == 6){
            estadoActual2 = 6;
            if(estadoActual2 == 6 && estadoAnterior2 != 6){
              lcd.setCursor(posCursor,0);
              lcd.print(" ");
              aux2++;
            }
            estadoAnterior2 = 6;
          }
          if(posCursor == 8){
            estadoActual2 = 8;
            if(estadoActual2 == 8 && estadoAnterior2 != 8){
              lcd.setCursor(posCursor,0);
              lcd.print(" ");
              aux3++;
            }
            estadoAnterior = 8;
          }
          if(posCursor == 9){
            estadoActual2 = 9;
            if(estadoActual2 == 9 && estadoAnterior2 != 9){
              lcd.setCursor(posCursor,0);
              lcd.print(" ");
              aux4++;
            }
            estadoAnterior2 = 9;
          }
          estadoAnterior == BTN_UP;
        }
        break;
      case BTN_DOWN:
        if(estadoAnterior != BTN_DOWN){
          if(posCursor == 5){
            estadoActual2 = 5;
            if(estadoActual2 == 5 && estadoAnterior2 != 5){
              lcd.setCursor(posCursor,0);
              lcd.print(" ");
              aux1--;
            }
            estadoAnterior2 = 5;
          }
          if(posCursor == 6){
            estadoActual2 = 6;
            if(estadoActual2 == 6 && estadoAnterior2 != 6){
              lcd.setCursor(posCursor,0);
              lcd.print(" ");
              aux2--;
            }
            estadoAnterior2 = 6;
          }
          if(posCursor == 8){
            estadoActual2 = 8;
            if(estadoActual2 == 8 && estadoAnterior2 != 8){
              lcd.setCursor(posCursor,0);
              lcd.print(" ");
              aux3--;
            }
            estadoAnterior = 8;
          }
          if(posCursor == 9){
            estadoActual2 = 9;
            if(estadoActual2 == 9 && estadoAnterior2 != 9){
              lcd.setCursor(posCursor,0);
              lcd.print(" ");
              aux4--;
            }
            estadoAnterior2 = 9;
          }
          estadoAnterior == BTN_DOWN;
        }
        break;
      case BTN_SELECT:
        state = STATE_REGRE;
		tInicial = millis();
		tiempoBomba = ((aux1*10+aux2)*60) + (aux3*10+aux4);
        break;
    }
  }
  
  lcd.setCursor(5,0);

  
  if(aux1 == 10 || aux1 <0){
    aux1 = 0;
  }
  if(aux2 == 10 || aux2 <0){
    aux2 = 0;
  }
  if(aux3 == 6 || aux3 <0){
    aux3 = 0;
  }
  if(aux4 == 10 || aux4 <0){
    aux4 = 0;
  }
  
  
  lcd.print(aux1);
  lcd.print(aux2);
  lcd.print(":");
  lcd.print(aux3);
  lcd.print(aux4);
    
  lcd.setCursor(posCursor,1);
  lcd.print("^");
}

void stateRegre(){
	nuevosMillis = millis();
	if(nuevosMillis-tInicial >= 1000){
		tiempoBomba--;
		tInicial = nuevosMillis;
		if(tiempoBomba==0){
			state = STATE_TIME;
			lcd.setCursor(5,0);
			lcd.print(aux1);
			lcd.print(aux2);
			lcd.print(":");
			lcd.print(aux3);
			lcd.print(aux4);
		}
	}
	lcd.setCursor(5,0);
	int minToPrint = tiempoBomba / 60;
	int secToPrint = tiempoBomba % 60;
	char s[5];
	sprintf(s, "%2d:%2d", minToPrint, secToPrint);
	lcd.print(s);
}

void loop() {
  switch(state){
    case STATE_TIME:
      stateTime();
      break;
    case STATE_REGRE:
      stateRegre();
      break; 
  }
}
