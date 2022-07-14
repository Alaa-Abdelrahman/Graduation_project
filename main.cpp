#include <Arduino.h>

#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>

#include "TFT_interface.h"

TFT_eSPI tft = TFT_eSPI();       // Invoke custom library




void setup() {

  Serial.begin(9600);

  
/**
   * @brief Construct a new tft config object
   * 
   * @param orient define orientation of the screen
   * @param  tft pionter to the tft object
   */ 
   
 TFT_config(& tft ,ORIENT_90);
 
}

void loop() {
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/**
  * @brief dfine the attributes of READY_BUTTON 
  * 
  */
 drawnButtonSpec_t ready_button ;
ready_button.nameButton = READY;
ready_button.button_x = 50;
ready_button.button_y = 50;
ready_button.button_w= 20;  
ready_button.button_h= 20;
ready_button.button_color = TFT_BLUE;
ready_button.button_txt_color = TFT_CYAN;
ready_button.button_text = "READY";
ready_button.chosen = FALSE;


  /**
  * @brief dfine the attributes of MUTE_BUTTON 
  * 
  */
 drawnButtonSpec_t mute_button ;
mute_button.nameButton = MUTE_BT; 
mute_button.button_x = 50;
mute_button.button_y = 70;
mute_button.button_w= 20;
mute_button.button_h= 20;
mute_button.button_color = TFT_RED;
mute_button.button_txt_color = TFT_CYAN;
mute_button.button_text = "MUTE";
mute_button.chosen = FALSE;



 /**
  * @brief dfine the attributes of SPEAK_BUTTON 
  * 
  */
 drawnButtonSpec_t speak_button ;
speak_button.nameButton = SPEAK_BT;
speak_button.button_x = 50;
speak_button.button_y = 90;
speak_button.button_w= 20;
speak_button.button_h= 20;
speak_button.button_color = TFT_GREEN;
speak_button.button_txt_color = TFT_CYAN;
speak_button.button_text = "SPEAK";
speak_button.chosen = FALSE;



/**
 * @brief define the data structure of the screens 
 * 
 */
  screen_t welcome_screen;
 welcome_screen.screenMode = WELCOME_SCREEN;
 welcome_screen.drawnButton[0] = NULL;
 welcome_screen.numberOfButtons = 0;
 welcome_screen.screenBgColor = TFT_BLACK;
 welcome_screen.screenTxtColor = TFT_WHITE;
 welcome_screen.screenTxtSize = 2;
 welcome_screen.active_button = NULL;
 welcome_screen.fontType = "NotoSansBold15.vlw";
  
  screen_t customize_screen;
  customize_screen.screenMode = CUSTOMIZE_SCREEN;
  customize_screen.drawnButton[0] = &ready_button;
  customize_screen.numberOfButtons = 1;
  customize_screen.screenBgColor = TFT_BLACK;
  customize_screen.screenTxtColor = TFT_WHITE;
  customize_screen.screenTxtSize = 2;
  customize_screen.active_button = NULL;
  customize_screen.fontType = "SansSerif-36.vlw";
    
  screen_t open_hand_cal;
  open_hand_cal.screenMode = OPEN_HAND_CAL;
  open_hand_cal.drawnButton[0] = NULL;
  open_hand_cal.numberOfButtons = 0;
  open_hand_cal.screenBgColor = TFT_BLACK;
  open_hand_cal.screenTxtColor = TFT_WHITE;
  open_hand_cal.screenTxtSize = 2;
  open_hand_cal.active_button = NULL;
  open_hand_cal.fontType = "SansSerif-36.vlw";

  screen_t close_hand_cal;
  close_hand_cal.screenMode = CLOSE_HAND_CAL;
  close_hand_cal.drawnButton[0] = NULL;
  close_hand_cal.numberOfButtons = 0;
  close_hand_cal.screenBgColor = TFT_BLACK;
  close_hand_cal.screenTxtColor = TFT_WHITE;
  close_hand_cal.screenTxtSize = 2;
  close_hand_cal.active_button = NULL;
  close_hand_cal.fontType = "SansSerif-36.vlw";

  screen_t verify_screen_done;
  verify_screen_done.screenMode = VERFIY_SCREEN_DONE;
  verify_screen_done.drawnButton[0] = NULL;
  verify_screen_done.numberOfButtons = 0;
  verify_screen_done.screenBgColor = TFT_BLACK;
  verify_screen_done.screenTxtColor = TFT_WHITE;
  verify_screen_done.screenTxtSize = 2;
  verify_screen_done.active_button = NULL;
  verify_screen_done.fontType = "SansSerif-36.vlw";

  screen_t verify_screen_err;
  verify_screen_err.screenMode = VERFIY_SCREEN_ERR;
  verify_screen_err.drawnButton[0]= NULL;
  verify_screen_err.numberOfButtons = 0;
  verify_screen_err.screenBgColor = TFT_BLACK;
  verify_screen_err.screenTxtColor = TFT_WHITE;
  verify_screen_err.screenTxtSize = 2;
  verify_screen_err.active_button = NULL;
  verify_screen_err.fontType = "SansSerif-36.vlw";

  screen_t home_screen;
  home_screen.screenMode = HOME_SCREEN;
  home_screen.drawnButton[0] =&ready_button;
  home_screen.drawnButton[1] =&mute_button;
  home_screen.drawnButton[2] =&speak_button;
  home_screen.numberOfButtons = 3;
  home_screen.screenBgColor = TFT_BLACK;
  home_screen.screenTxtColor = TFT_WHITE;
  home_screen.screenTxtSize = 2;
  home_screen.active_button = NULL;
  home_screen.fontType = "NotoSansBold15";


  // put your main code here, to run repeatedly:
int flag = 1;
  while(1)
  {
    if(flag == 1)
    {
  errorState_t errorState =DONE;
    errorState= TFT_drawScreen(&welcome_screen,&tft);
    if(errorState != DONE)
    {
      Serial.println("error in draw screen");
    }
    else
    {
      Serial.println("draw screen done");
      flag = 2;
    }
    }

    delay(1000);

     if(flag == 2)
    {
  errorState_t errorState =DONE;
    errorState= TFT_drawScreen(&home_screen,&tft);
    if(errorState != DONE)
    {
      Serial.println("error in draw screen");
    }
    else
    {
      Serial.println("draw screen done");
      flag = 1;
    }
    }
    delay(1000);

  }
}


