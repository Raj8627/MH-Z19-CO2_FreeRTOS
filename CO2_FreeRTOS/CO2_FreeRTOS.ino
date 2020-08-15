#include <Arduino_FreeRTOS.h>

int pin1 = 2;
int pin2 = 12;

unsigned long duration1;
unsigned long duration2;

float value1;
float value2;

// define two tasks for Blink & AnalogRead
void CO2_1( void *pvParameters );
void CO2_2( void *pvParameters );
void action( void *pvParameters );

// the setup function runs once when you press reset or power the board
void setup() {

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  delay(1000);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB, on LEONARDO, MICRO, YUN, and other 32u4 based boards.
  }

  // Now set up two tasks to run independently.
  xTaskCreate(
    CO2_1
    ,  "CO2 1"   // A name just for humans
    ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  NULL // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL );

  xTaskCreate(
    CO2_2
    ,  "CO2 2"
    ,  128  // Stack size
    ,  NULL
    ,  NULL  // Priority
    ,  NULL );

  xTaskCreate(
    action
    ,  "take action based on co2 level"
    ,  128  // Stack size
    ,  NULL
    ,  NULL  // Priority
    ,  NULL );


  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}

void loop()
{
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void CO2_1(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  pinMode(pin1, INPUT);

  while (1) // A Task shall never return or exit.
  {
    duration1 = pulseIn(pin1, HIGH);
    //  Serial.print("Duration 1 : "); Serial.println(duration1);
    duration1 = duration1 / 1000;
    //Checking to see if the Co2 value is in range
    if (duration1 > 2)
    {
      value1 = (5000 * (duration1 - 2)) / (duration1 + (1004 - duration1) - 4);
    }
    Serial.print("CO2 1 : "); Serial.println(value1);
    delay(2000);
  }
}

void CO2_2(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  // initialize digital LED_BUILTIN on pin 13 as an output.
  pinMode(pin2, INPUT);

  while (1)
  {
    duration2 = pulseIn(pin2, HIGH);
    //  Serial.print("Duration 1 : "); Serial.println(duration1);
    duration2 = duration2 / 1000;
    //Checking to see if the Co2 value is in range
    if (duration2 > 2)
    {
      value2 = (5000 * (duration2 - 2)) / (duration2 + (1004 - duration2) - 4);
    }
    Serial.print("CO2 2 : "); Serial.println(value2);
    delay(2000);
  }
}


void action(void *pvParameters)
{
  (void) pvParameters;

  while (1)
  {
    int difference = abs(value1 - value2);

    Serial.print("difference=");
    Serial.println(difference);
    delay(2000);

    if ( value1 < value2)
    {
      Serial.println("");

    }
    else

    {
      Serial.println("");

    }
  }
}
