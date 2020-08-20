# Esp8266
Simple connection with module ESP8266 for Arduino

Open the files on Arduino project, adding new tabs
and then includes the #include "wifi.h" instruction


using:

Wifi wifi;

void setup()
{
  wifi.Start("SSID", "PASS");
}

void loop()
{
  wifi.Run();
  if(wifi.Done()){
    // do stuff
    wifi.Reset();
  }
}
