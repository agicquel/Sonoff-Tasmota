
unsigned long statusbutton_debounce = 10000;          // Button debounce timer
int statusbutton;
int status_last_read;
char status_cmnd[255];
String status_espid;
int status_state = 0;



void StatusButtonInit(void)
{
    if (pin[GPIO_STATUS_KEY] < 99) {

        pinMode(pin[GPIO_STATUS_KEY], INPUT);

    }

    AddLog_P(LOG_LEVEL_INFO, PSTR(D_LOG_APPLICATION "Status Button init"));

    status_espid = WiFi.macAddress();
    status_espid.replace(":","");
    
}

void StatusButtonHandler(){

    statusbutton = (digitalRead(pin[GPIO_STATUS_KEY]));

    if (statusbutton == 1 && status_last_read == 0)
    {
        status_last_read = 1;
    }else if (statusbutton == 0 && status_last_read == 1)
    {   
        if (status_state > 2) { status_state = 0; }
        
        if(status_state == 0){
            snprintf_P(status_cmnd, sizeof(status_cmnd), PSTR("DISPLAYTEXT [zs2]%s "), status_espid.c_str());
            ExecuteCommand(status_cmnd, SRC_BUTTON);
        }else if (status_state == 1)
        {
            snprintf_P(status_cmnd, sizeof(status_cmnd), PSTR("DISPLAYTEXT [zs2]%s "), Settings.sta_ssid[0]);
            ExecuteCommand(status_cmnd, SRC_BUTTON);
        }
    
        status_last_read = 0;
        status_state++;
    }
    
    
}

void  StatusButtonLoop(void)
{
  // ajouter if(wifibutton_present) comme 
  if (TimeReached(statusbutton_debounce)) {
    SetNextTimeInterval(statusbutton_debounce, 300);
    StatusButtonHandler();
  }
}

