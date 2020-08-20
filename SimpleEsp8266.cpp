#include "wifi.h"

Wifi::~Wifi()
{
}

Wifi::Wifi()
{
}

bool Wifi::Done()
{
  return this->done;
}

void Wifi::Reset()
{
  this->id = "";
  this->route = "";
  this->verb = NONE;
  this->done = false;
}

int Wifi::ResolveVerb(String verb)
{
  if (verb == "GET") return GET;
  else if (verb == "POST") return POST;
  else if (verb == "PUT") return PUT;
  else if (verb == "DELETE") return DELETE;
  return NONE;
}

void Wifi::Run()
{
  if (!Serial.available())
    return;
  this->buffer += (char)Serial.read();
  if (this->buffer.length() > 200)
    this->buffer = "";

  if (this->buffer.endsWith("HTTP/1.1"))
  {
    this->buffer = this->buffer.substring(this->buffer.indexOf("+IPD"));
    this->buffer.replace("HTTP/1.1", "");
    this->id = this->buffer[5];
    String verb = this->buffer.substring(this->buffer.indexOf(':') + 1, this->buffer.indexOf(' '));
    this->verb = ResolveVerb(verb);
    this->route = this->buffer.substring(this->buffer.indexOf('/') + 1);
    this->route.trim();

    //String page = "HTTP/1.0 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE html>\r\n<META HTTP-EQUIV=\"REFRESH\" CONTENT=\"1\">\r\nApi rodando";

    this->Send("AT+CIPSEND=" + id + ",5", "OK", 1000);
    this->Send("API", "OK", 1000);
    this->buffer = "";
    this->done = true;
  }
}

void Wifi::Start(String ssid, String pass)
{
  Serial.begin(115200);
  this->Send("AT+RST", "WIFI GOT IP", 5000);
  this->Send("ATE0", "OK", 1000);
  this->Send("AT+CWJAP=\"" + ssid + "\",\"" + pass + "\"", "OK", 5000);
  this->Send("AT+CWMODE=1", "OK", 1000);
  this->Send("AT+CIPMUX=1", "OK", 1000);
  this->Send("AT+CIPSERVER=1", "OK", 1000);
}

void Wifi::Send(String cmd, String resp, int timeOut)
{
  this->buffer = "";
  Serial.print(cmd + "\r\n");
  long time = millis() + timeOut;
  while (millis() < time )
  {
    if (!Serial.available())
      continue;
    this->buffer += Serial.read();
    if (this->buffer.indexOf(resp) > -1)
      break;
  }
  this->buffer = "";
}
