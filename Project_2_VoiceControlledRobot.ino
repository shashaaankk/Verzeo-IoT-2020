#include <AFMotor.h>
#include <SoftwareSerial.h>
SoftwareSerial Serial(11, 12); // RX, TX
String voice;
const byte MOTOR_A = 3; // Motor 2 Interrupt Pin - INT 1 - Right Motor
const byte MOTOR_B = 2; // Motor 1 Interrupt Pin - INT 0 - Left Motor

// Motor A
int enA = 10;
int in1 = 9;
int in2 = 8;

// Motor B
int enB = 5;
int in3 = 7;
int in4 = 6;

void ISR_countA()
{
    counter_A++; // increment Motor A counter value
}

// Motor B pulse count ISR
void ISR_countB()
{
    counter_B++; // increment Motor B counter value
}

void setup()
{
    // Attach the Interrupts to their ISR's
    attachInterrupt(digitalPinToInterrupt(MOTOR_A), ISR_countA, RISING); // Increase counter A when speed sensor pin goes High
    attachInterrupt(digitalPinToInterrupt(MOTOR_B), ISR_countB, RISING); // Increase counter B when speed sensor pin goes High
    Serial.begin(9600);
    
}
// Function to convert from centimeters to steps
int CMtoSteps(float cm)
{

    int result;                                        // Final calculation result
    float circumference = (wheeldiameter * 3.14) / 10; // Calculate wheel circumference in cm
    float cm_step = circumference / stepcount;         // CM per Step

    float f_result = cm / cm_step; // Calculate result as a float
    result = (int)f_result;        // Convert to an integer (note this is NOT rounded)

    return result; // End and return result
}

void loop()
{
    while (Serial.available())
    {
        delay(10);
        char c = Serial.read();
        if (c == '#')
        {
            break;
        }
        voice += c;
    }

    //splitting the voice input into 2 parts
    if (voice.length() > 0)
    {
        String xval = getValue(voice, ':', 0);
        String yval = getValue(voice, ':', 1);
        //converting the distance from string to int
        int xvalue = xvalue.toInt(xval);

        if (yval == "*Forward")
        {
            MoveForward(CMtoSteps(xvalue), 255);
        }
        else if (yval == "*Backward")
        {
            MoveReverse(CMtoSteps(xvalue), 255);
        }
        else if (yval == "*right")
        {
            SpinRight(CMtoSteps(xvalue), 255);
        }
        else if (yval == "*left")
        {
            SpinLeft(CMtoSteps(xvalue), 255);
        }
         voice = "";
    }
}

//function to move forward
void MoveForward(int steps, int mspeed);
{
    counter_A = 0; //  reset counter A to zero
    counter_B = 0; //  reset counter B to zero

    // Set Motor A forward
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);

    // Set Motor B forward
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

    // Go forward until step value is reached
    while (steps > counter_A && steps > counter_B)
    {

        if (steps > counter_A)
        {
            analogWrite(enA, mspeed);
        }
        else
        {
            analogWrite(enA, 0);
        }
        if (steps > counter_B)
        {
            analogWrite(enB, mspeed);
        }
        else
        {
            analogWrite(enB, 0);
        }
    }

    // Stop when done
    analogWrite(enA, 0);
    analogWrite(enB, 0);
    counter_A = 0; //  reset counter A to zero
    counter_B = 0; //  reset counter B to zero
}

// Function to Move in Reverse
void MoveReverse(int steps, int mspeed)
{
    counter_A = 0; //  reset counter A to zero
    counter_B = 0; //  reset counter B to zero

    // Set Motor A reverse
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);

    // Set Motor B reverse
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

    // Go in reverse until step value is reached
    while (steps > counter_A && steps > counter_B)
    {

        if (steps > counter_A)
        {
            analogWrite(enA, mspeed);
        }
        else
        {
            analogWrite(enA, 0);
        }
        if (steps > counter_B)
        {
            analogWrite(enB, mspeed);
        }
        else
        {
            analogWrite(enB, 0);
        }
    }

    // Stop when done
    analogWrite(enA, 0);
    analogWrite(enB, 0);
    counter_A = 0; //  reset counter A to zero
    counter_B = 0; //  reset counter B to zero
}

// Function to Spin Right
void SpinRight(int steps, int mspeed)
{
    counter_A = 0; //  reset counter A to zero
    counter_B = 0; //  reset counter B to zero

    // Set Motor A reverse
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);

    // Set Motor B forward
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);

    // Go until step value is reached
    while (steps > counter_A && steps > counter_B)
    {

        if (steps > counter_A)
        {
            analogWrite(enA, mspeed);
        }
        else
        {
            analogWrite(enA, 0);
        }
        if (steps > counter_B)
        {
            analogWrite(enB, mspeed);
        }
        else
        {
            analogWrite(enB, 0);
        }
    }

    // Stop when done
    analogWrite(enA, 0);
    analogWrite(enB, 0);
    counter_A = 0; //  reset counter A to zero
    counter_B = 0; //  reset counter B to zero
}

// Function to Spin Left
void SpinLeft(int steps, int mspeed)
{
    counter_A = 0; //  reset counter A to zero
    counter_B = 0; //  reset counter B to zero

    // Set Motor A forward
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);

    // Set Motor B reverse
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

    // Go until step value is reached
    while (steps > counter_A && steps > counter_B)
    {

        if (steps > counter_A)
        {
            analogWrite(enA, mspeed);
        }
        else
        {
            analogWrite(enA, 0);
        }
        if (steps > counter_B)
        {
            analogWrite(enB, mspeed);
        }
        else
        {
            analogWrite(enB, 0);
        }
    }

    // Stop when done
    analogWrite(enA, 0);
    analogWrite(enB, 0);
    counter_A = 0; //  reset counter A to zero
    counter_B = 0; //  reset counter B to zero
}
