/*
*
*   L'esp doit être sur qu'il est subscribe au LoPy sur lequel
*   il est connecté.
*   Pour cela on requete le LoPy en http;
*
*
*
*/
#include <ESP8266HTTPClient.h>


#define SUBSCRIBE_LOG "trying to subscribe"

unsigned long subscribe_debounce = 15000;
boolean is_subscribed;
String espid;

// String getEspId()
// {
//   String espId = WiFi.macAddress();
//   espId.replace(":", "");
//   return espId;
// }
void SubscribeInit(void) {

    is_subscribed = false;
    espid = WiFi.macAddress();
    espid.replace(":","");
    AddLog_P(LOG_LEVEL_INFO, PSTR(D_LOG_APPLICATION "Subscribe init"));


}


void subscribe(void) {
    HTTPClient http;
    String route = "http://10.42.31.2/subscribe?espid="+ espid;
    //WebSend(route.c_str());
    http.begin(route);
    http.POST("");
    http.end();
}

void subscribed()
{
    HTTPClient http;
    String route = "http://10.42.31.2/subscribed/" + espid;
    http.begin(route);
    int httpCode = http.GET();  
    is_subscribed = (httpCode == 200);
    http.end();
  
}

void SubscribeLoop(void) {

    if (TimeReached(subscribe_debounce)) {
        SetNextTimeInterval(subscribe_debounce, 10000);  
        if((WiFi.status() != WL_CONNECTED)){
            is_subscribed = false;
        }
        else if( (WiFi.status() == WL_CONNECTED) && (!is_subscribed))
        {
            AddLog_P(LOG_LEVEL_INFO, PSTR(D_LOG_APPLICATION "Trying to subscribe"));

            subscribe();
            subscribed();
        }
    }

}
