#include <ESP8266WiFi.h>

#define wifi_ssid "twatia" //wifi name
#define wifi_password "siddharth" //wifi password
const char* host = "api.thingspeak.com"; //host
const char* writeAPIKey = "S7QMMQ1QRSWRY1VR"; //apikey

char cmd_arr1[100];
int cmd_count1;
int i;
int temp,sm,hum,light,fan_st,bulb_st,ex_st,sp_st;
//T,M,H,L,F,B,E,S
//*****************************************************************
void setup_wifi() 
{
  delay(10);
  // We start by connecting to our WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);

  WiFi.begin(wifi_ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  
  digitalWrite(4, HIGH);
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
//*****************************************************************
void serial_get_command()
{
  char inchar=0;
  if(Serial.available() > 0)
  {
    inchar = Serial.read();    
    if(inchar == '<')
    {
      cmd_count1=0;
      while(inchar != '>' && cmd_count1<15)
      {
        if(Serial.available() > 0)
        {
          inchar = Serial.read();
          cmd_arr1[cmd_count1++] = inchar;
        }        
      }
      if(inchar == '>')
      { 
        if(cmd_arr1[0]=='T')
        {cmd_arr1[0]='0';temp = atoi(cmd_arr1);Serial.print("Temp : ");Serial.println(temp);}
        else if(cmd_arr1[0]=='M')
        {cmd_arr1[0]='0';sm = atoi(cmd_arr1);Serial.print("Soil Moisture : ");Serial.println(sm);}
        else if(cmd_arr1[0]=='H')
        {cmd_arr1[0]='0';hum = atoi(cmd_arr1);Serial.print("Humidity : ");Serial.println(hum);}
        else if(cmd_arr1[0]=='L')
        {cmd_arr1[0]='0';light = atoi(cmd_arr1);Serial.print("Light : ");Serial.println(light);}
        else if(cmd_arr1[0]=='F')
        {cmd_arr1[0]='0';fan_st = atoi(cmd_arr1);Serial.print("Fan Status : ");Serial.println(fan_st);}
        else if(cmd_arr1[0]=='B')
        {cmd_arr1[0]='0';bulb_st = atoi(cmd_arr1);Serial.print("Bulb Status : ");Serial.println(bulb_st);}
        else if(cmd_arr1[0]=='E')
        {cmd_arr1[0]='0';ex_st = atoi(cmd_arr1);Serial.print("Exhaust Status : ");Serial.println(ex_st);}
        else if(cmd_arr1[0]=='S')
        {cmd_arr1[0]='0';sp_st = atoi(cmd_arr1);Serial.print("Sprinkler Status : ");Serial.println(sp_st);}
        else if(cmd_arr1[0]=='U')
        {upload_data();}
      }
    }
  }
}
//*****************************************************************
void upload_data()
{
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    return;
  }
  Serial.println("Client Connected");
  String url = "/update?key=";
  url+=writeAPIKey;
  url+="&field1=";
  url+=String(temp);
  url+="&field2=";
  url+=String(sm);
  url+="&field3=";
  url+=String(hum);
  url+="&field4=";
  url+=String(light);
  url+="&field5=";
  url+=String(fan_st);
  url+="&field6=";
  url+=String(bulb_st);
  url+="&field7=";
  url+=String(ex_st);
  url+="&field8=";
  url+=String(sp_st);
  url+="\r\n";
  
  // Request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");
               
  for(i=0;i<5;i++)
  {
    digitalWrite(4, LOW);delay(100);digitalWrite(4, HIGH);delay(100);
  }
}
//*****************************************************************
void setup() 
{
  Serial.begin(9600);
  Serial.println("Program Started");
  pinMode(4, OUTPUT);digitalWrite(4, LOW);
  setup_wifi();
}
//*****************************************************************
void loop()
{
  serial_get_command();
}
//*****************************************************************
