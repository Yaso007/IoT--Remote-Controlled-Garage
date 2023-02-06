#include <Servo.h>
#include <IRremote.h>
#define trigPin 2
#define echoPin 3
#define servoPin 9

int buz =12;
int led=8;
int light=0;

long duration;
int distance;
int ultra=0;
const int RECV_PIN = 7;

IRrecv irrecv(RECV_PIN);
decode_results results;
Servo myservo;


void setup() {
  myservo.attach(servoPin);
  Serial.begin(9600);  
  pinMode(led,OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 
  pinMode(buz,OUTPUT);
  irrecv.enableIRIn(); 
}

void loop() {
  digitalWrite(buz,LOW);

  if (irrecv.decode(&results)){
        Serial.println(results.value);
        irrecv.resume();
  }
  
 if(light == 1){
     Serial.println("Light");
     digitalWrite(led,HIGH);
   }  else digitalWrite(led,LOW);
   
  if(ultra==1){
   digitalWrite(trigPin, HIGH);
    delay(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2;
    Serial.print("Distance = ");
     Serial.print(distance);
    Serial.println(" cm");
    if(distance<5){Serial.println("Too close");
        digitalWrite(buz,HIGH);
        delay(1000);
    }

   delay(50);    
  }
  else digitalWrite(trigPin,LOW);
  
 switch (results.value){
    case  33472575:
        Serial.println("Servo up");  
        myservo.write(180);
         delay(15);
        
        break;
    case 33439935:  Serial.println("Servo down");
            myservo.write(0);
            delay(15);
            break;
    case 33448095 :  Serial.println("lights on");
            light=1;
                                  
            break;
    case 33464415:  Serial.println("lights off");
            light=0;
            break;
    case 33460335:Serial.println("UltraON");
            ultra=1;break;
    case 33427695: Serial.println("UltraOFF");
            ultra =0;
            break;   
    case  10368:
        Serial.println("Servo up");  
        
        myservo.write(180);
         delay(15);
        
        break;
    case 14467:  Serial.println("Servo down");
            myservo.write(0);
            delay(15);
            break;
    case 10421 :  Serial.println("lights on");
            light=1;
                                  
            break;
    case 10388:  Serial.println("lights off");
            light=0;
            break;
    case 10373:Serial.println("UltraON");
            ultra=1;break;
    case 14470: Serial.println("UltraOFF");
            ultra =0;
            break;                                    
    default:Serial.println("Error");
 }    

  delay(1000);
}