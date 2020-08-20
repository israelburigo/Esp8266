#ifndef WIFI_H
#define WIFI_H

#define NONE -1
#define GET 0
#define POST 1
#define PUT 2
#define DELETE 3

class Wifi {
  private:    
    String buffer;
    bool done;
    
    int ResolveVerb(String verb);
  public:
    String id;
    String route;
    int verb;

    void Send(String cmd, String resp, int timeOut);
    bool Done();
    void Reset();
    void Run();
    void Start(String ssid, String pass);
    
    Wifi();
    ~Wifi();
};

#endif
