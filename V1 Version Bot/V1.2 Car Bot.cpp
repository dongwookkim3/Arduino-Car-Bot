#include <IRremote.h>

#define EA 3
#define EB 11
#define M_IN1 4
#define M_IN2 5
#define M_IN3 13
#define M_IN4 12

const int motorA_vector = 1;
const int motorB_vector = 1;
const int motor_speed = 255;
const int RECV_PIN = 6;

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
    Serial.begin(9600);
    irrecv.enableIRIn();
    pinMode(EA, OUTPUT);
    pinMode(EB, OUTPUT);
    pinMode(M_IN1, OUTPUT);
    pinMode(M_IN2, OUTPUT);
    pinMode(M_IN3, OUTPUT);
    pinMode(M_IN4, OUTPUT);
}

void loop(){

//숫자 16진수값
/*
0 : FD30CF
1 : FD08F7
2 : FD8877
3 : FD48B7
4 : FD28D7
5 : FDA857
6 : FD6897
7 : FD18E7
8 : FD9867
9 : FD58A7
*/
    if (irrecv.decode(&results)){
        Serial.print("0x");
        Serial.print(results.value, HEX);
        Serial.print(" : ");
        Serial.println(results.value);
        Serial.println();
        switch (results.value){
        case 16718055:
            motorA_con(motor_speed);
            motorB_con(motor_speed);
            break;
        case 16716015:
            motorA_con(motor_speed);
            motorB_con(0);
            break;
        case 16726215:
            motorA_con(0);
            motorB_con(0);
            break;
        case 16734885:
            motorA_con(0);
            motorB_con(motor_speed);
            break;
        case 16730805:
            motorA_con(-motor_speed);
            motorB_con(-motor_speed);
            break;
        default:
            break;
        }
        irrecv.resume();
    }
    delay(50);
}

void motorA_con(int M1){
    if (M1 > 0){
        digitalWrite(M_IN1, !motorA_vector);
        digitalWrite(M_IN2, motorA_vector);
    }
    else if (M1 < 0){
        digitalWrite(M_IN1, motorA_vector);
        digitalWrite(M_IN2, !motorA_vector);
    }
    else{
        digitalWrite(M_IN1, LOW);
        digitalWrite(M_IN2, LOW);
    }
    analogWrite(EA, abs(M1));
}

void motorB_con(int M2){
    if (M2 > 0){
        digitalWrite(M_IN3, motorB_vector);
        digitalWrite(M_IN4, !motorB_vector);
    }
    else if (M2 < 0){
        digitalWrite(M_IN3, !motorB_vector);
        digitalWrite(M_IN4, motorB_vector);
    }
    else{
        digitalWrite(M_IN3, LOW);
        digitalWrite(M_IN4, LOW);
    }
    analogWrite(EB, abs(M2));
}