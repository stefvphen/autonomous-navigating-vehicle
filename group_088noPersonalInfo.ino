//We can work on this here then copy and paste into Arduino IDE        
  
/*         
  
  ELEC1100 Your Lab#06 & Project Template         
  
    
  
    
  
  To program the car tracking the white line on a dark mat         
  
    
  
         
  
    
  
  Group No. (number of your project box): group_088         
  
    
  
  Group Member 1 (name & SID):        
  
    
  
  Group Member 2 (name & SID):        
  
    
  
           
  
    
  
*/         
  
    
  
         
  
    
  
// assign meaningful names to those pins that will be used         
  
    
  
         
  
    
  
const int pinL_Sensor = A5;      //pin A5: left sensor          
  
    
  
const int pinB_Sensor = A4;      //pin A4: bumper sensor         
  
    
  
const int pinR_Sensor = A3;      //pin A3: right sensor          
  
    
  
         
  
    
  
const int pinL_PWM = 9;          //pin D9: left motor speed         
  
    
  
const int pinL_DIR = 10;         //pin D10: left motor direction         
  
    
  
         
  
    
  
const int pinR_PWM = 11;         //pin D11: right motor speed         
  
    
  
const int pinR_DIR = 12;         //pin D12: right motor direction         
  
    
  
         
  
    
  
//define variables to be used in script         
  
    
  
         
  
    
  
int bumperSensor = 1;  // not sensing white         
  
    
  
int leftSensor = 1;    // not sensing white         
  
    
  
int rightSensor = 1;   // not sensing white         
  
    
  
         
  
    
  
int countBumper = 0;   // bumper sensor not triggered yet         
  
    
  
int countTurn = 1; //count which turn the car is done       
  
    
  
      
  
    
  
int baseSpeed = 100;     
  
    
  
int turnSpeed = 200;    
  
    
  
     
  
    
  
unsigned long straightOnly = 0;    
  
    
  
unsigned long theTime = 0;    
  
    
  
unsigned long speedUp = 0;    
  
unsigned long turn6resetTime = 0; 
unsigned long turn8resetTime = 0;
    
  
     
  
    
  
bool turn8Speed = true;    
  
    
  
         
  
    
  
// the setup function runs once when you press reset or power the board         
  
    
  
         
  
    
  
void setup ()         
  
    
  
{         
  
    
  
  // define pins as input and output         
  
    
  
  pinMode(pinB_Sensor, INPUT);         
  
    
  
  pinMode(pinL_Sensor, INPUT);         
  
    
  
  pinMode(pinR_Sensor, INPUT);         
  
    
  
           
  
    
  
  pinMode(pinL_DIR, OUTPUT);         
  
    
  
  pinMode(pinR_DIR, OUTPUT);         
  
    
  
           
  
    
  
  pinMode(pinL_PWM, OUTPUT);         
  
    
  
  pinMode(pinR_PWM, OUTPUT);         
  
    
  
           
  
    
  
  // initialize output pins         
  
    
  
  digitalWrite(pinL_DIR, HIGH);   //forward direction             
  
    
  
  digitalWrite(pinR_DIR, HIGH);   //forward direction         
  
    
  
  analogWrite(pinL_PWM, 0);       //stop at the start position          
  
    
  
  analogWrite(pinR_PWM, 0);       //stop at the start position     
  
    
  
}         
  
    
  
         
  
    
  
// the loop function runs over and over again forever         
  
    
  
         
  
    
  
void loop() {     
  
    
  
  bumperSensor = digitalRead(pinB_Sensor);           
  
  leftSensor = digitalRead(pinL_Sensor);         
  
  rightSensor = digitalRead(pinR_Sensor);     
  
  theTime = millis();        
  
   // car stops at the start position when bumper sensor no trigger    
  
   if(bumperSensor && countBumper == 0 ){    
  
    analogWrite(pinL_PWM, 0);         
  
    analogWrite(pinR_PWM, 0);     
  
    countTurn = 1;  
  
   }    
  
    
  
   else{    
  
    
  
     if(countTurn < 9){ Stage1();}    
  
    
  
     else{Stage2();}    
  
    
  
   }    
  
    
  
     
  
    
  
}     
  
    
  
     
  
    
  
void Stage1(){             
  
    
  
  
    
  
  // bumper sensor is triggered at the start position for the 1st time         
  
    
  
   if ( !bumperSensor && countBumper == 0) {         
  
    
  
    analogWrite(pinL_PWM, 100);         
  
    
  
    analogWrite(pinR_PWM, 100);         
  
    
  
    countBumper = countBumper + 1;         
  
    
  
    delay(350);     //to let the car leave the start position with no miscount         
  
    
  
  }        
  
    
  
      
  
    
  
          
  
    
  
  // car is tracking on the white line         
  
    
  
  //else if ( bumperSensor && countBumper == 1)       
  
    
  
  if(countTurn == 2){
    baseSpeed = 80;    
  }
  else if (countTurn == 3){
    baseSpeed = 100;
  }
  else if (countTurn == 5){
    baseSpeed = 80;
  }
  else if(countTurn == 7){
    baseSpeed = 110;
  }
  
  
    
  
  if((theTime >= speedUp) && turn8Speed){    
  
    
  
    baseSpeed = 100;    
  
    
  
  }    
  
    
  
  if ( !bumperSensor && countBumper == 1){  
  
        analogWrite(pinL_PWM, 250);         
  
    
  
        analogWrite(pinR_PWM, 250);         
  
    
  
        digitalWrite(pinL_DIR, HIGH);  
  
        digitalWrite(pinR_PWM, HIGH );  
  
        delay(250);        
  
    
  
  }  
  
    
  
  if ( bumperSensor && countBumper == 1)        
  
    
  
  {        
  
    
  
     
  
    
  
    if ( (!leftSensor && !rightSensor) ) {         
  
      if(countTurn == 7 && theTime < turn6resetTime){ 
        countTurn = 6; 
      } 
  
      if(countTurn == 3){        
  
    
  
        analogWrite(pinL_PWM, 250);         
  
    
  
        analogWrite(pinR_PWM, 250);         
  
    
  
        digitalWrite(pinL_DIR, LOW);         
  
    
  
        digitalWrite(pinR_DIR, HIGH);         
  
    
  
        countTurn++;          
  
    
  
        delay(410);  // 180 degree turn      
  
    
  
        }     
  
    
  
        else if (countTurn == 2){        
  
    
  
        analogWrite(pinL_PWM, 150);         
  
    
  
        analogWrite(pinR_PWM, turnSpeed);         
  
    
  
        digitalWrite(pinL_DIR, LOW);         
  
    
  
        digitalWrite(pinR_DIR, HIGH);         
  
    
  
        countTurn++;          
  
    
  
        delay(180);        
  
    
  
      }           
  
    
  
      else if (countTurn == 5){       
  
    
  
        analogWrite(pinL_PWM, turnSpeed);         
  
    
  
        analogWrite(pinR_PWM, 150);         
  
    
  
        digitalWrite(pinL_DIR, HIGH);         
  
    
  
        digitalWrite(pinR_DIR, LOW);         
  
    
  
        countTurn++;          
  
    
  
        delay(175);      
  
    
  
        baseSpeed = 250;     
  
    
  
        speedUp = theTime + 2100;     
  
    
  
      }       
  
      else if (countTurn == 6){        
  
    
  
        analogWrite(pinL_PWM, 150);         
  
    
  
        analogWrite(pinR_PWM, turnSpeed);         
  
    
  
        digitalWrite(pinL_DIR, LOW);         
  
    
  
        digitalWrite(pinR_DIR, HIGH);         
  
    
  
        countTurn++;          
  
        turn6resetTime = theTime + 1000; 
  
        delay(300);   
  
      }   
  
    
  
      else if (countTurn == 7){      
  
    
  
        analogWrite(pinL_PWM, baseSpeed);         
  
    
  
        analogWrite(pinR_PWM, baseSpeed);         
  
    
  
        digitalWrite(pinL_DIR, HIGH);         
  
    
  
        digitalWrite(pinR_DIR, HIGH);      
  
    
  
        countTurn++;    
  
    
  
        delay(100);     
  
    
  
        baseSpeed = 80;    
  
    
  
        turn8Speed = false;     
  
    
  
      }     
  
  
    
  
      else if (countTurn == 8){      
  
    
  
       /* analogWrite(pinL_PWM, turnSpeed);         
  
    
  
        analogWrite(pinR_PWM, 150);         
  
    
  
        digitalWrite(pinL_DIR, HIGH);         
  
    
  
        digitalWrite(pinR_DIR, LOW);      
  
    
  
        countTurn++;    
  
    
  
        delay(25); */  
  
    
  
        analogWrite(pinL_PWM, baseSpeed);         
  
    
  
        analogWrite(pinR_PWM, baseSpeed);         
  
    
  
        digitalWrite(pinL_DIR, HIGH);         
  
    
  
        digitalWrite(pinR_DIR, HIGH);     
  
    
  
        countTurn++;    
  
    
  
        delay(300);    
  
    
  
        theTime = millis();    
  
        turn8resetTime = theTime +500;
  
        straightOnly = theTime + 7000;     
  
        //straightOnly = theTime + 6000;       
  
    
  
      }     
  
    
  
      else if (countTurn == 1 || countTurn == 4){        
  
    
  
        analogWrite(pinL_PWM, 150);         
  
    
  
        analogWrite(pinR_PWM, turnSpeed);         
  
    
  
        digitalWrite(pinL_DIR, LOW);         
  
    
  
        digitalWrite(pinR_DIR, HIGH);         
  
    
  
        countTurn++;          
  
    
  
        delay(240);        
  
    
  
      }       
  
    
  
    }    
  
    
  
     
  
    
  
    /*if (countTurn == 8){    
  
    
  
        analogWrite(pinL_PWM, baseSpeed);         
  
    
  
        analogWrite(pinR_PWM, baseSpeed);         
  
    
  
        digitalWrite(pinL_DIR, HIGH);         
  
    
  
        digitalWrite(pinR_DIR, HIGH);     
  
    
  
        delay(800);    
  
    
  
        analogWrite(pinL_PWM, 150);         
  
    
  
        analogWrite(pinR_PWM, turnSpeed);         
  
    
  
        digitalWrite(pinL_DIR, LOW);         
  
    
  
        digitalWrite(pinR_DIR, HIGH);     
  
    
  
        delay(120);    
  
    
  
        analogWrite(pinL_PWM, baseSpeed);         
  
    
  
        analogWrite(pinR_PWM, baseSpeed);         
  
    
  
        digitalWrite(pinL_DIR, HIGH);         
  
    
  
        digitalWrite(pinR_DIR, HIGH);     
  
    
  
        delay(500);    
  
    
  
        countTurn++;    
  
    
  
        theTime = millis();    
  
    
  
        straightOnly = theTime + 7000;    
  
    
  
    }*/    
  
    
  
     
  
    
    if(( (!leftSensor && rightSensor && (countTurn == 2 || countTurn == 5))) ) {         
  
    
  
        analogWrite(pinL_PWM, 175);         
  
    
  
        analogWrite(pinR_PWM, turnSpeed);         
  
    
  
        digitalWrite(pinL_DIR, LOW);         
  
    
  
        digitalWrite(pinR_DIR, HIGH);       
  
    
  
        delay(1);    
    }
    else if ( (!leftSensor && rightSensor) ) {         
  
    
  
        analogWrite(pinL_PWM, 150);         
  
    
  
        analogWrite(pinR_PWM, turnSpeed);         
  
    
  
        digitalWrite(pinL_DIR, LOW);         
  
    
  
        digitalWrite(pinR_DIR, HIGH);       
  
    
  
        delay(1);         
  
    
  
      }     
  
    
  
           
  
    if(( (leftSensor && !rightSensor && (countTurn == 2 || countTurn == 5))) ) {         
  
    
        analogWrite(pinL_PWM, turnSpeed);         
  
    
  
        analogWrite(pinR_PWM, 175);         
  
    
  
        digitalWrite(pinL_DIR, HIGH);         
  
    
  
        digitalWrite(pinR_DIR, LOW);          
  
    
  
        delay(1);       
  
    
     
    }
  
    else if ( leftSensor && !rightSensor) {         
  
    
  
        analogWrite(pinL_PWM, turnSpeed);         
  
    
  
        analogWrite(pinR_PWM, 150);         
  
    
  
        digitalWrite(pinL_DIR, HIGH);         
  
    
  
        digitalWrite(pinR_DIR, LOW);          
  
    
  
        delay(1);       
  
    
  
      }     
  
    
  
        
  
    
  
    if(leftSensor && rightSensor && countTurn == 1){    
  
    
  
        analogWrite(pinL_PWM, 250);         
  
    
  
        analogWrite(pinR_PWM, 250);         
  
    
  
        digitalWrite(pinL_DIR, HIGH);         
  
    
  
        digitalWrite(pinR_DIR, HIGH);     
  
    
  
    }    
  
    else if  ( leftSensor && rightSensor && countTurn ==2){    
  
    
  
        analogWrite(pinL_PWM, baseSpeed);         
  
    
  
        analogWrite(pinR_PWM, baseSpeed +55 );         
  
    
  
        digitalWrite(pinL_DIR, HIGH);         
  
    
  
        digitalWrite(pinR_DIR, HIGH);     
  
    
  
    }    
    else if  ( leftSensor && rightSensor && countTurn ==5){    
  
    
  
        analogWrite(pinL_PWM, baseSpeed +55);         
  
    
  
        analogWrite(pinR_PWM, baseSpeed );         
  
    
  
        digitalWrite(pinL_DIR, HIGH);         
  
    
  
        digitalWrite(pinR_DIR, HIGH);  
    }   
  
    else if (leftSensor && rightSensor && countTurn == 6){   
  
         analogWrite(pinL_PWM, baseSpeed + 5);         
  
    
  
        analogWrite(pinR_PWM, baseSpeed - 20);         
  
    
  
        digitalWrite(pinL_DIR, HIGH);         
  
    
  
        digitalWrite(pinR_DIR, HIGH);    
  
    }  
  
    
  
    else if (leftSensor && rightSensor && countTurn == 8){    
  
    
  
           
  
        analogWrite(pinL_PWM, baseSpeed);         
  
    
  
        analogWrite(pinR_PWM, baseSpeed + 50);         
  
    
  
        digitalWrite(pinL_DIR, HIGH);         
  
    
  
        digitalWrite(pinR_DIR, HIGH);    
  
    
  
    }    
  
    
  
    else if (leftSensor && rightSensor && countTurn == 7){    
  
    
  
        analogWrite(pinL_PWM, baseSpeed);         
  
    
  
        analogWrite(pinR_PWM, baseSpeed + 100);         
  
    
  
        digitalWrite(pinL_DIR, HIGH);         
  
    
  
        digitalWrite(pinR_DIR, HIGH);     
  
    
  
    }    
  
    
  
    else if ( leftSensor && rightSensor ) {         
  
    
  
        analogWrite(pinL_PWM, baseSpeed);         
  
    
  
        analogWrite(pinR_PWM, baseSpeed);         
  
    
  
        digitalWrite(pinL_DIR, HIGH);         
  
    
  
        digitalWrite(pinR_DIR, HIGH);           
  
    
  
      }        
  
    
  
        
  
    
  
        
  
    
  
   
  
    
  
             
  
    
  
  }       
  
    
  
}       
  
    
  
     
  
    
  
void Stage2(){    
  
    
  
  if(bumperSensor == 0){    
  
    
  
          analogWrite(pinL_PWM, 255);         
  
    
  
          analogWrite(pinR_PWM, 255);         
  
    
  
          digitalWrite(pinL_DIR, LOW);         
  
    
  
          digitalWrite(pinR_DIR, LOW);     
  
    
  
          delay(270);    
  
    
  
          analogWrite(pinL_PWM, 0);         
  
    
  
          analogWrite(pinR_PWM, 0);     
  
    
  
          while(1){    
  
    
  
            delay(100);    
  
    
  
          }    
  
    
  
  }    
  
    
  if(theTime < straightOnly){
    
  baseSpeed = 80;   
  }
 
  if(!leftSensor && !rightSensor && theTime < turn8resetTime){
           analogWrite(pinL_PWM, turnSpeed);         
  
    
  
          analogWrite(pinR_PWM, 150);         
  
    
  
          digitalWrite(pinL_DIR, HIGH);         
  
    
  
          digitalWrite(pinR_DIR, LOW); 
          delay(100);        
  }
  
  if(!leftSensor && !rightSensor && theTime >= straightOnly){    
  
    
  
    if ((countTurn >= 9)){     
  
          //analogWrite(pinL_PWM, 0);         
  
    
  
          //analogWrite(pinR_PWM, 0);    
  
    
  
          analogWrite(pinL_PWM, 250);         
  
    
  
          analogWrite(pinR_PWM, 250);         
  
    
  
          digitalWrite(pinL_DIR, LOW);         
  
    
  
          digitalWrite(pinR_DIR, HIGH);         
  
    
  
          countTurn++;          
  
    
  
          delay(925);  // 360 degree turn    
  
    
  
          analogWrite(pinL_PWM, 200);         
  
    
  
          analogWrite(pinR_PWM, 200);         
  
    
  
          digitalWrite(pinL_DIR, HIGH);         
  
    
  
          digitalWrite(pinR_DIR, HIGH);     
  
    
  
          delay(175);   
          baseSpeed = 120; 
  
    
  
    }    
  
    
  
  }    
  
    
  
  else if (!leftSensor && !rightSensor && (theTime < straightOnly - 4000)){  //within 3sec after stage 2, should turn left  
  
    
  
             
  
          analogWrite(pinL_PWM, 150);         
  
    
  
          analogWrite(pinR_PWM, turnSpeed);         
  
    
  
          digitalWrite(pinL_DIR, LOW);         
  
    
  
          digitalWrite(pinR_DIR, HIGH);    
  
    
  
          delay(150);    
  
    
  
  }    
  
    
  
  else if(!leftSensor && !rightSensor && theTime < straightOnly -2000){   
  
    
  
          analogWrite(pinL_PWM, turnSpeed);         
  
    
  
          analogWrite(pinR_PWM, 150);         
  
    
  
          digitalWrite(pinL_DIR, HIGH);         
  
    
  
          digitalWrite(pinR_DIR, LOW);    
  
    
  
          delay(125);    
  
    
  
  }    
  
  else if (!leftSensor && !rightSensor && theTime >= straightOnly - 5000 && theTime < straightOnly - 3000){ 
          analogWrite(pinL_PWM, turnSpeed);         
  
  
          analogWrite(pinR_PWM, 150);         
   
  
          digitalWrite(pinL_DIR, HIGH);         
   
  
          digitalWrite(pinR_DIR, LOW);    
  
    
  
          delay(125);  
  } 
    
  
  else if(!leftSensor && !rightSensor && theTime >= straightOnly - 2000){    
  
    
  
          analogWrite(pinL_PWM, 150);         
  
    
  
          analogWrite(pinR_PWM, turnSpeed);         
  
    
  
          digitalWrite(pinL_DIR, LOW);         
  
    
  
          digitalWrite(pinR_DIR, HIGH);    
  
    
  
          delay(150);    
  
    
  
  }    
  
    
  
      
  
    
  
  if (leftSensor && !rightSensor && theTime >= straightOnly - 5000 && theTime < straightOnly - 3000){    
  
    
  
        //analogWrite(pinL_PWM, 0);         
  
    
  
        //analogWrite(pinR_PWM, 0);     
  
        analogWrite(pinL_PWM, turnSpeed);         
  
    
  
        analogWrite(pinR_PWM, 200);         
  
    
  
        digitalWrite(pinL_DIR, HIGH);         
  
    
  
        digitalWrite(pinR_DIR, LOW);       
  
    
  
        delay(1);    
  
    
  
  }    
  
    
  
  else if(leftSensor && !rightSensor){    
  
    
  
        analogWrite(pinL_PWM, turnSpeed);         
  
    
  
        analogWrite(pinR_PWM, 120);         
  
    
  
        digitalWrite(pinL_DIR, HIGH);         
  
    
  
        digitalWrite(pinR_DIR, LOW);       
  
    
  
        delay(1);     
  
    
  
   }     
  
    
  
      
  
    
  
  if(!leftSensor && rightSensor && theTime < straightOnly - 3700){    
  
    
  
        analogWrite(pinL_PWM, 200);         
  
    
  
        analogWrite(pinR_PWM, turnSpeed);         
  
    
  
        digitalWrite(pinL_DIR, LOW);         
  
    
  
        digitalWrite(pinR_DIR, HIGH);       
  
    
  
        delay(1);     
  
    
  
  }    
  
    
  
  else if(!leftSensor && rightSensor){    
  
    
  
        analogWrite(pinL_PWM, 120);         
  
    
  
        analogWrite(pinR_PWM, turnSpeed);         
  
    
  
        digitalWrite(pinL_DIR, LOW);         
  
    
  
        digitalWrite(pinR_DIR, HIGH);       
  
    
  
        delay(1);     
  
    
  
    }    
  
    
  
     
  
    
if(  leftSensor && rightSensor && theTime < straightOnly - 5000){
        analogWrite(pinL_PWM, baseSpeed);         
  
    
  
        analogWrite(pinR_PWM, baseSpeed + 60);         
  
    
  
        digitalWrite(pinL_DIR, HIGH);         
  
    
  
        digitalWrite(pinR_DIR, HIGH);     
}
else if(leftSensor && rightSensor && theTime >= straightOnly - 5000 && theTime < straightOnly - 3000){    
  
    
  
        analogWrite(pinL_PWM, baseSpeed + 50);         
  
    
  
        analogWrite(pinR_PWM, baseSpeed);         
  
    
  
        digitalWrite(pinL_DIR, HIGH);         
  
    
  
        digitalWrite(pinR_DIR, HIGH);     
  
    
  
  }    
  
    
  
  else if(leftSensor && rightSensor && theTime >= straightOnly -1000){    
  
    
  
        analogWrite(pinL_PWM, baseSpeed + 30);         
  
    
  
        analogWrite(pinR_PWM, baseSpeed);         
  
    
  
        digitalWrite(pinL_DIR, HIGH);         
  
    
  
        digitalWrite(pinR_DIR, HIGH);     
  
    
  
  }    
  
    
  
  else if ( leftSensor && rightSensor ) {         
  
    
  
        analogWrite(pinL_PWM, baseSpeed);         
  
    
  
        analogWrite(pinR_PWM, baseSpeed);         
  
    
  
        digitalWrite(pinL_DIR, HIGH);         
  
    
  
        digitalWrite(pinR_DIR, HIGH);           
  
    
  
      }     
  
    
  
         
  
    
  
}    
  
    
  
     
  
    
  
    
  
  
 
 
