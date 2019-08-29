
/*********************************************************************************************\
 * WiFi config Button support
\*********************************************************************************************/

unsigned long wifibutton_debounce = 10000;          // Button debounce timer
uint8_t wifibutton_present = 0;
char cmnd[255];
int hold_counter = 0;
int selection_counter = 0;
uint8_t last_read= 0;
int ssid_n       = 0;
int ssid_index   = 0;
bool scan_flag = false;
uint8_t button;
uint8_t state = 0;
int * lopy_ssid_index;
const char * prefix = "Lopy";
int not_removed_size;
int lopy_found = 0;



void WiFiButtonInit(void)
{
    wifibutton_present = 0;
    if (pin[GPIO_WIFI_KEY] < 99) {

        //AddLog_P2(LOG_LEVEL_INFO, PSTR(D_LOG_APPLICATION D_BUTTON " %" PRIu8 ), pin[GPIO_WIFI_KEY]);
        wifibutton_present++;
        pinMode(pin[GPIO_WIFI_KEY], INPUT);

    }

    AddLog_P(LOG_LEVEL_INFO, PSTR(D_LOG_APPLICATION "WiFi Button init"));
    state = 0;

}

bool starts_with(const char * string, const char * prefix)
{
    while(*prefix)
    {
        if(*prefix++ != *string++)
            return 0;
    }

    return 1;
}

int *remove(int *first, int *last, int val)
{
  int *result = first;
  while (first!=last) {
    if (!(*first == val)) {
      *result = *first;
      ++result;
    }
    ++first;
  }
  return result;
}

void WiFiScan(void){
  snprintf(cmnd, sizeof(cmnd), PSTR("DISPLAYTEXT [zs2]Scannning\nWiFi..."));
  ExecuteCommand(cmnd, SRC_BUTTON); 
  //SetNextTimeInterval(wifibutton_debounce, 3000);
  free(lopy_ssid_index);
  ssid_n = WiFi.scanNetworks();
  lopy_ssid_index = (int*) malloc(ssid_n * sizeof(int));
  
  for(int i = 0; i < ssid_n; i++){
    if(starts_with(WiFi.SSID(i).c_str(),prefix) == 0){
      lopy_ssid_index[i] = -1;
    }else{
      lopy_ssid_index[i] = i;
      AddLog_P2(LOG_LEVEL_INFO, PSTR(D_LOG_APPLICATION "match ssid %s"),WiFi.SSID(i).c_str());
      lopy_found++;
    }
  }

  int *end = remove(lopy_ssid_index, lopy_ssid_index + ssid_n, -1);
  not_removed_size = end - lopy_ssid_index;
  ssid_index = 0;

}

void WiFiScanDone(void){
  snprintf_P(cmnd, sizeof(cmnd), PSTR("DISPLAYTEXT [zs2]%d AP\nfound."),lopy_found);
  ExecuteCommand(cmnd, SRC_BUTTON);
  scan_flag = false;
}


void WiFiButtonHandler(){

  if(state == 1){

    button = (digitalRead(pin[GPIO_WIFI_KEY]));
    //AddLog_P2(LOG_LEVEL_INFO, PSTR(D_LOG_APPLICATION D_BUTTON " state %d - %d"),button,last_read);

    if(hold_counter > 15){
      state = 0;
      WifiDisconnect();


    }else if(button == 1 && last_read == 0){
      hold_counter++;
      last_read = 1;

    }else if(button == 1 && last_read == 1){
      hold_counter++;

    }else if(button == 0 && last_read == 1){
       if(ssid_index >= not_removed_size) { ssid_index = 0; }
      snprintf_P(cmnd, sizeof(cmnd), PSTR("DISPLAYTEXT [zs2]%s %d/%d"), WiFi.SSID(lopy_ssid_index[ssid_index]).c_str(), ssid_index, not_removed_size-1);
      ExecuteCommand(cmnd, SRC_BUTTON);
      ssid_index ++;
      last_read = 0;
      hold_counter = 0;
      selection_counter = 0;
      state = 2;

    }
  }else if(state == 2){

    button = (digitalRead(pin[GPIO_WIFI_KEY]));


    if(hold_counter > 15){
      state = 0;
      WifiDisconnect();

    }else if(button == 1 && last_read == 0){
      hold_counter++;
      last_read = 1;
      selection_counter = 0;

    }else if(button == 1 && last_read == 1){
      hold_counter++;
      selection_counter = 0;

    }else if(button == 0 && last_read == 1){
      if(ssid_index >= not_removed_size) { ssid_index = 0; }
      snprintf_P(cmnd, sizeof(cmnd), PSTR("DISPLAYTEXT [zs2]%s %d/%d"), WiFi.SSID(lopy_ssid_index[ssid_index]).c_str(), ssid_index, not_removed_size-1);
      ExecuteCommand(cmnd, SRC_BUTTON);
      ssid_index++;
      last_read = 0;
      hold_counter = 0;
      selection_counter = 0;

    }else if(button == 0 && last_read == 0){
      //AddLog_P2(LOG_LEVEL_INFO, PSTR(D_LOG_APPLICATION D_BUTTON " selection %d"),selection_counter);

      selection_counter++;
      if(selection_counter > 30){
        hold_counter = 0;
        last_read = 0;
        state = 3;
      }
    }
  }else if(state == 4){
    button = (digitalRead(pin[GPIO_WIFI_KEY]));
    //AddLog_P2(LOG_LEVEL_INFO, PSTR(D_LOG_APPLICATION D_BUTTON " state %d - %d"),button,hold_counter);

    if(hold_counter > 15){
      state = 5;
      WifiDisconnect();
      

    }else if(button == 1 && last_read == 0){
      hold_counter++;
      last_read = 1;

    }else if(button == 1 && last_read == 1){
      hold_counter++;

    }else{
      hold_counter = 0;

    }
  }
}

void  WiFiButtonLoop(void)
{
  // ajouter if(wifibutton_present) comme 
  if (TimeReached(wifibutton_debounce)) {

    if(state == 0){
      if(WiFi.status() != WL_CONNECTED && (strcmp(Settings.sta_ssid[1],"")!=1)){
        // AddLog_P(LOG_LEVEL_INFO, PSTR(D_LOG_APPLICATION D_BUTTON " state 0"));
        
        WiFiScan();
        WiFiScanDone();

        if(not_removed_size == 0){
          snprintf(cmnd, sizeof(cmnd), PSTR("DISPLAYTEXT [zs2]No AP hold\nto rescan."));
          ExecuteCommand(cmnd, SRC_BUTTON);
          state = 4;
        }else{
          state = 1;
        }
        

        ssid_index        = 0;
        hold_counter      = 0;
        selection_counter = 0;
        last_read         = 0;
        lopy_found        = 0;
        SetNextTimeInterval(wifibutton_debounce, 3000);
      }else{
        state = 4;
        SetNextTimeInterval(wifibutton_debounce, 300);
      }
      

    }else if(state == 1){
      // AddLog_P(LOG_LEVEL_INFO, PSTR(D_LOG_APPLICATION D_BUTTON " state 1"));

      WiFiButtonHandler();
      SetNextTimeInterval(wifibutton_debounce, 300);

    }else if(state == 2){
      // AddLog_P(LOG_LEVEL_INFO, PSTR(D_LOG_APPLICATION D_BUTTON " state 2"));

      //selection_counter = 0;
      //last_read         = 0;CONNECTION
      WiFiButtonHandler();
      SetNextTimeInterval(wifibutton_debounce, 300);
    }else if(state == 3){
      // AddLog_P(LOG_LEVEL_INFO, PSTR(D_LOG_APPLICATION D_BUTTON " state 3"));

      // connection a index_ssid--

      snprintf(cmnd, sizeof(cmnd), PSTR("DISPLAYTEXT [zs2]Connection..."));
      ExecuteCommand(cmnd, SRC_BUTTON);
      snprintf_P(cmnd, sizeof(cmnd), PSTR("DISPLAYTEXT [zs2]%s"),WiFi.SSID(lopy_ssid_index[ssid_index-1]).c_str());
      ExecuteCommand(cmnd, SRC_BUTTON);
      snprintf_P(cmnd, sizeof(cmnd), PSTR("SSID %s"),WiFi.SSID(lopy_ssid_index[ssid_index-1]).c_str());
      ExecuteCommand(cmnd, SRC_BUTTON);
      WifiConnect();
      state = 4;
      SetNextTimeInterval(wifibutton_debounce, 10000);
    }else if(state == 4){
      // AddLog_P(LOG_LEVEL_INFO, PSTR(D_LOG_APPLICATION D_BUTTON " state 4"));
      // snprintf(cmnd, sizeof(cmnd), PSTR("DISPLAYTEXT [zs2]CONNECTED!"));
      // ExecuteCommand(cmnd, SRC_BUTTON);
      WiFiButtonHandler();
      SetNextTimeInterval(wifibutton_debounce, 300);
    }else if(state == 5){
      hold_counter = 0;
      snprintf_P(cmnd, sizeof(cmnd), PSTR("SSID 1"));
      ExecuteCommand(cmnd, SRC_BUTTON);
      state = 4;
    }
    
  }
}

