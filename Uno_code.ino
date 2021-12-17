#include <LiquidCrystal.h>
#include "DHT.h"
#define DHTPIN A2     // what digital pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
#define FAN 2
#define R1 3
#define R2 10
#define R3 11
#define R4 13
#define SWU A4
#define SWD A5
#define SWE 12

unsigned long previousMillis=0;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(4, 5, 6, 7, 8, 9);
unsigned long valY = 0;   //
int analogTEMP = A0,ii; // Temperature Sensor
float temp=0, temp_max = 40;
unsigned int light, moisture, light_m = 90, moisture_min = 20, moisture_max = 80;
float h, humidity_max = 60;
int llight;
int moist;
DHT dht(DHTPIN, DHTTYPE);

// Pins for Buzzer and LED
// Pins for Motors
void setup () {
    Serial.begin(9600);
    lcd.begin(16, 2);
    lcd.print("PROJECT OK ...  ");
    delay(2000);
    pinMode(FAN, OUTPUT);    
    pinMode(R1, OUTPUT);    pinMode(R2, OUTPUT); 
    pinMode(R3, OUTPUT);    pinMode(R4, OUTPUT);
    pinMode(SWU, INPUT_PULLUP);
    pinMode(SWD, INPUT_PULLUP);
    pinMode(SWE, INPUT_PULLUP); 
    digitalWrite(FAN,LOW);
    digitalWrite(R1,LOW);    digitalWrite(R2,LOW);
    digitalWrite(R3,LOW);    digitalWrite(R4,LOW);   
    enter_values(); 
    
    lcd.clear();
    dht.begin();
    previousMillis = millis();
}

void enter_values()
{
  lcd.clear();
  lcd.print("Enter Max Temp. ");
  lcd.setCursor(0, 1);
  lcd.print(temp_max);
  while(digitalRead(SWE)==HIGH)
  {
    if(digitalRead(SWU)==LOW)
    {
      if(temp_max<80)                 //changed
      {
        temp_max++;
        lcd.setCursor(0, 1);
        lcd.print("    ");
        lcd.setCursor(0, 1);
        lcd.print(temp_max);
        delay(200);      
      }
    }
    if(digitalRead(SWD)==LOW)
    {
      if(temp_max>20)
      {
        temp_max--;
        lcd.setCursor(0, 1);
        lcd.print("    ");
        lcd.setCursor(0, 1);
        lcd.print(temp_max);
        delay(200);
      }
    }    
  }
  delay(500);
  lcd.clear();


  lcd.print("Enter Max Light ");
  lcd.setCursor(0, 1);
  lcd.print(light_m);
  while(digitalRead(SWE)==HIGH)
  {
    if(digitalRead(SWU)==LOW)
    {
      if(light_m<100)                 //changed
      {
        light_m++;
        lcd.setCursor(0, 1);
        lcd.print("    ");
        lcd.setCursor(0, 1);
        lcd.print(light_m);
        delay(200);      
      }
    }
    if(digitalRead(SWD)==LOW)
    {
      if(light_m>20)
      {
        light_m--;
        lcd.setCursor(0, 1);
        lcd.print("    ");
        lcd.setCursor(0, 1);
        lcd.print(light_m);
        delay(200);
      }
    }    
  }
  delay(500);
  lcd.clear();

  lcd.print("Enter Min Soi.M.");
  lcd.setCursor(0, 1);
  lcd.print(moisture_min);
  while(digitalRead(SWE)==HIGH)
  {
    if(digitalRead(SWU)==LOW)
    {
      if(moisture_min<100)                 //changed
      {
        moisture_min++;
        lcd.setCursor(0, 1);
        lcd.print("    ");
        lcd.setCursor(0, 1);
        lcd.print(moisture_min);
        delay(200);      
      }
    }
    if(digitalRead(SWD)==LOW)
    {
      if(moisture_min>10)
      {
        moisture_min--;
        lcd.setCursor(0, 1);
        lcd.print("    ");
        lcd.setCursor(0, 1);
        lcd.print(moisture_min);
        delay(200);
      }
    }    
  }
  delay(500);
  lcd.clear();


  lcd.print("Enter Max Soi.M.");
  lcd.setCursor(0, 1);
  lcd.print(moisture_max);
  while(digitalRead(SWE)==HIGH)
  {
    if(digitalRead(SWU)==LOW)
    {
      if(moisture_max<100)                 //changed
      {
        moisture_max++;
        lcd.setCursor(0, 1);
        lcd.print("    ");
        lcd.setCursor(0, 1);
        lcd.print(moisture_max);
        delay(200);      
      }
    }
    if(digitalRead(SWD)==LOW)
    {
      if(moisture_max>10)
      {
        moisture_max--;
        lcd.setCursor(0, 1);
        lcd.print("    ");
        lcd.setCursor(0, 1);
        lcd.print(moisture_max);
        delay(200);
      }
    }    
  }
  delay(500);
  lcd.clear();


  lcd.print("Enter Max R.H.%");
  lcd.setCursor(0, 1); 
  lcd.print(humidity_max);
  while(digitalRead(SWE)==HIGH)
  {
    if(digitalRead(SWU)==LOW)
    {
      if(humidity_max<100)                 //changed
      {
        humidity_max++;
        lcd.setCursor(0, 1);
        lcd.print("    ");
        lcd.setCursor(0, 1);
        lcd.print(humidity_max);
        delay(200);      
      }
    }
    if(digitalRead(SWD)==LOW)
    {
      if(humidity_max>10)
      {
        humidity_max--;
        lcd.setCursor(0, 1);
        lcd.print("    ");
        lcd.setCursor(0, 1);
        lcd.print(humidity_max);
        delay(200);
      }
    }    
  }
  delay(500);
  lcd.clear();
}

void measure_temperature()
{
  valY=0;
    for(ii=0;ii<50;ii++)
    {
      valY += analogRead(analogTEMP);
    }
     valY = valY/50;
    temp = (float)(((5.0*100)/1023.0)*valY);
    lcd.setCursor(0,0);
    lcd.print("T:");
    lcd.print(temp,1);
    lcd.print("*C ");
    Serial.print("<T");Serial.print((int)temp);Serial.println(">");
    delay(100);
}

void measure_light_intensity()
{
    valY=0;
    for(ii=0;ii<50;ii++)
    {
      valY += analogRead(A1);
    }
     valY = valY/50;
    light = (unsigned int)(valY);
    llight = map(light,  0, 1023, 100, 0); 
   
    lcd.setCursor(0,1);
    lcd.print("L:");
    lcd.print(llight);
    lcd.print("%   ");
    Serial.print("<L");Serial.print((int)llight);Serial.println(">");
    delay(100);
}

void measure_humidity()
{
   h = dht.readHumidity();
    
    if (isnan(h)) 
    {
      //Serial.println("Failed to read from DHT sensor!");
      lcd.print("H:");
      lcd.print("ERR");
      //lcd.print("%        ");
    }
    else
    {
      lcd.setCursor(9,0);
      lcd.print("H:");
      lcd.print(h,1);
      lcd.print("%        ");
    }
    Serial.print("<H");Serial.print((int)h);Serial.println(">");
    delay(100);
}

void measure_soil_moisture()
{
  valY=0;
    for(ii=0;ii<50;ii++)
    {
      valY += analogRead(A3);
    }
     valY = valY/50;
    moisture = (unsigned int)(valY);     

    moist = map(moisture,  0, 1023, 100, 0); 
   
    lcd.setCursor(9,1);
    lcd.print("M:");
    lcd.print(moist);
    lcd.print("%         "); 
    Serial.print("<M");Serial.print((int)moist);Serial.println(">");
    delay(100);
}

void sensor_check()
{
  if(temp>temp_max)
  {
    lcd.clear();
    lcd.print("TEMP. ALERT !!  ");
    digitalWrite(FAN,HIGH);    digitalWrite(R1,HIGH);
    Serial.println("<F1>");
    delay(1500);
  }
  else
  {
    digitalWrite(FAN,LOW);    digitalWrite(R1,LOW);
    Serial.println("<F0>");
    delay(100);
  }

  if(llight>light_m)
  {
    lcd.clear();
    lcd.print("LIGHT ALERT !!  ");
    digitalWrite(R2,HIGH);
    Serial.println("<B1>");
    delay(1500);
    
    
  }
  else
  {
    Serial.println("<B0>");
    digitalWrite(R2,LOW);
    delay(100);
  }

  if(h>humidity_max)
  {
    lcd.clear();
    lcd.print("R.H.  ALERT !!  ");
    digitalWrite(R3,HIGH);
    Serial.println("<E1>");
    delay(1500);
  }
  else
  {
    digitalWrite(R3,LOW);
    Serial.println("<E0>");
    delay(100);
  }

  if(moist<moisture_min)
  {
    lcd.clear();
    lcd.print("Soil Moist ALERT");
    digitalWrite(R4,HIGH);
    Serial.println("<S1>");
    delay(1500);
  }
  else if(moist>moisture_max)
  {
    digitalWrite(R4,LOW);
    Serial.println("<S0>");
    delay(100);
  }
}
void loop () 
{   
    measure_temperature(); 
    measure_light_intensity();  
    measure_humidity();
    measure_soil_moisture();
    sensor_check();
    delay(500);
    if(millis() - previousMillis > 25000)
    {
      delay(1000);
      Serial.println("Sending data");
      Serial.println("<U>");  
      delay(1000);
      previousMillis = millis();
    }
}
