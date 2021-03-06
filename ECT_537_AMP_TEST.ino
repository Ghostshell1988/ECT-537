/*This project is for the Terre Haute History Museum. As of now, it sets 3 ammeters 
 * to a randomized value, and then make one meter change based on time and a button press. 
  */

int amPin1 = 9;
int amPin2 = 5;
int amPin3 = 3;
int amPin4 = 10;
int buttonPin= 8;
int ledOn = 7;
int ledOff = 6;
int AMPout = 0;
int amPinvar1 = 0;
int amPinvar2 = random(14,60);
int amPinvar3 = random(14,60);
int amPinvar4 = random(14,60);
int state = 0;
int val = LOW;
int seconds = 0;
int sclock = 0;
void setup() {
  // put your setup code here, to run once:
pinMode(amPin1, OUTPUT);
pinMode(amPin2, OUTPUT);
pinMode(amPin3, OUTPUT);
pinMode(amPin4, OUTPUT);
pinMode(ledOn, OUTPUT);
pinMode(ledOff, OUTPUT);
pinMode(buttonPin, INPUT);

Serial.begin(9600);
}

void loop() {
  //The next three lines set ammeters 2,3 and 4 to a randomized value for forever
  analogWrite(amPin2,amPinvar2);
  analogWrite(amPin3,amPinvar3);
  analogWrite(amPin4,amPinvar4);
  //The next chunk checks to see if a button was pressed, and then changes the state. This essentially acts as a 
  //locking mechanism to turn some LEDs on/off and also controls one of the ammeters and causes it to run
  val=digitalRead(buttonPin);
     if(val == HIGH && state == 0){
        state = 1;
        }
     
     else if(val == HIGH && state== 1){
        state = 0;
     }
//this chunk prints the values being sent to each ammeter
    Serial.print("State:");
    Serial.print(state);
    Serial.print("  Value1 =");
    Serial.print(amPinvar1);
    Serial.print("      Value2 =");
    Serial.print(amPinvar2);
    Serial.print("  Value3 =");
    Serial.print(amPinvar3);
    Serial.print("      Value4 =");
    Serial.println(amPinvar4);
//From here to the end, it checks the state, which was changed by the button press, and then 
//goes through a couple of timed loops to create a system that changes ammeter 1 on a set
//interval, and then resets to 0 when the cycle is completed
   if(state == 1){  
    amPinvar1 = 14;          
        for(seconds=0;seconds <= 5;){
          for(sclock = 0;sclock <= 1000;sclock++)
          {
            delay(1);
            if(val == HIGH){
              sclock = 16000000;
          }
          }
          seconds++;
          Serial.print("Seconds = ");
          Serial.println(seconds);
         if(seconds == 5){
          amPinvar1+=5;
          seconds = 0;
         }
         if (val == HIGH && state == 1){
          break;
         }
                
          digitalWrite(ledOff, LOW);
          digitalWrite(ledOn, HIGH);
          Serial.print("Ameter Running.\n");
          analogWrite(amPin1,amPinvar1);        
          Serial.print("State:");
          Serial.print(state);
          Serial.print("  Value1 =");
          Serial.print(amPinvar1);
          Serial.print("  Value2 =");
          Serial.print(amPinvar2);
          Serial.print("  Value3 =");
          Serial.print(amPinvar3);
          Serial.print("  Value4 =");
          Serial.println(amPinvar4);
          sclock = 0;
        if(amPinvar1 >= 66){
        state = 0;
        break;
       }
       }     
       }
         

      if(state == 0){
       digitalWrite(ledOff, HIGH);
       digitalWrite(ledOn, LOW);
       Serial.print("Ameter off. \n");
       amPinvar1=0;
       analogWrite(amPin1,amPinvar1);
       }

}
 
