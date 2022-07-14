/**
 * @file TFT_prog.cpp
 * @author Alaa Abdelrahman  (alaaawad17@gmail.com)
 * @brief include the implemntation of TFT interfaces
 * @version 0.1
 * @date 2022-04-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <Arduino.h>
#include "TFT_eSPI.h"
#include "FS.h"

#include "TFT_interface.h"

/********************************************************************************************************************
 * --------------------------------- HELPER FUNCTION ---------------------------------------------------------------
 *******************************************************************************************************************/

/**
 * @brief draw the button in specified screen through pass pionter to the screen and take the parametr for the button and draw it
 * 
 * @param tft screen object  
 * @param screen that you  want to draw the button in
 * 
 * @return error state 
 */
static errorState_t drawButtons(TFT_eSPI *tft,screen_t * screen)
{
    if(tft == NULL || screen == NULL)
    {
        return NULL_PTR;
    }
    uint8_t counter;
    for(counter = 0 ; counter < screen->numberOfButtons ; counter++)
    {  
        
        tft->fillRect(screen->drawnButton[counter]->button_x,screen->drawnButton[counter]->button_y,screen->drawnButton[counter]->button_w,screen->drawnButton[counter]->button_h,screen->drawnButton[counter]->button_color);

        tft->setTextColor(screen->drawnButton[counter]->button_txt_color);

        tft->loadFont("NotoSansBold15");

        tft->setTextSize(2);

        tft->setTextDatum(MC_DATUM);

        tft->drawString(screen->drawnButton[counter]->button_text, screen->drawnButton[counter]->button_x + (screen->drawnButton[counter]->button_w / 2),  screen->drawnButton[counter]->button_y + (screen->drawnButton[counter]->button_h / 2));

        screen->drawnButton[counter]->chosen = FALSE ;

    }

   return DONE;
  
}


// These read 16- and 32-bit types from the SD card file.
// BMP data is stored little-endian, Arduino is little-endian too.
// May need to reverse subscript order if porting elsewhere.

/**
 * @brief used to read file 
 * 
 * @param f want to read
 * @return uint16_t 
 */
static uint16_t read16(fs::File &f) {
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read(); // MSB
  return result;
}

/**
 * @brief used to read file 
 * 
 * @param f file that is want to read
 * @return uint16_t 
 */
static uint32_t read32(fs::File &f) {
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read(); // MSB
  return result;
}


/**
 * @brief draw Bmp picture on the specified screen
 * 
 * @param filename bmp picture that you want to draw
 * @param x        x origin point to draw the bmp picture
 * @param y        y origin point to draw the bmp picture
 * @param tft      pointer to the initailized hardware screen
 * @return errorState_t 
 */

errorState_t drawBmp(const char *filename, int16_t x, int16_t y, TFT_eSPI* tft) {

  if ((x >= tft->width()) || (y >= tft->height())) 
  {
      return OUT_SCOPE;
  }

  fs::File bmpFS;    // Create a file object. The File class belongs to the "fs" namespace
                     // This is declared in https://github.com/espressif/arduino-esp32/blob/master/libraries/FS/src/FS.h

  // Open requested file on SD card
  bmpFS = SPIFFS.open(filename, "r");

  if (!bmpFS)
  {
     return FILE_NOT_FOUND;
  }

  uint32_t seekOffset;
  uint16_t w, h, row, col;
  uint8_t  r, g, b;

  // uint32_t startTime = millis();

  if (read16(bmpFS) == 0x4D42)
  {
    read32(bmpFS);
    read32(bmpFS);
    seekOffset = read32(bmpFS);
    read32(bmpFS);
    w = read32(bmpFS);
    h = read32(bmpFS);

    if ((read16(bmpFS) == 1) && (read16(bmpFS) == 24) && (read32(bmpFS) == 0))
    {
      y += h - 1;

      tft->setSwapBytes(true);
      bmpFS.seek(seekOffset);

      uint16_t padding = (4 - ((w * 3) & 3)) & 3;
      uint8_t lineBuffer[w * 3 + padding];

      for (row = 0; row < h; row++) {
        
        bmpFS.read(lineBuffer, sizeof(lineBuffer));
        uint8_t*  bptr = lineBuffer;
        uint16_t* tptr = (uint16_t*)lineBuffer;
        // Convert 24 to 16 bit colours
        for (uint16_t col = 0; col < w; col++)
        {
          b = *bptr++;
          g = *bptr++;
          r = *bptr++;
          *tptr++ = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
        }

        // Push the pixel row to screen, pushImage will crop the line if needed
        // y is decremented as the BMP image is drawn bottom up
        tft->pushImage(x, y--, w, 1, (uint16_t*)lineBuffer);
      }
      /*
      DEBUGPRINT("Loaded in "); DEBUGPRINT(millis() - startTime);
      DEBUGPRINTLN(" ms");
      */
    }
    else 
    {
        DEBUGPRINTLN("BMP format not recognized.");
        return  BMP_FORMAT_ERROR;
    }

  }
  bmpFS.close();
  return DONE;
}



/********************************************************************************************************************
 * --------------------------------- INTERFACES  FUNCTION ---------------------------------------------------------------
 *******************************************************************************************************************/

/**
 * @brief  instantiate screen, SPIFFS and set orientation and clear screen 
 * 
 * @param tft pointer to tft screen as input to screen 
 * @param orient pass orientation of the screen and its value may be 
 *                                                                    - ORIENT_0
 *                                                                    - ORIENT_90
 *                                                                    - ORIENT_180
 *                                                                    - ORIENT_270
 *                                                                    - MIRROR
 * 
 * @return errorState_t to check the function did well 
 */
errorState_t  TFT_config( TFT_eSPI * tft ,screenOrient_t orient)
{
     if(tft ==  NULL)
     {
        return NULL_PTR; 
     }

     if (!SPIFFS.begin()) 
    {
        return SPIFFS_ERROR_INIT;
    }

    tft->init();

    tft->setRotation( orient);

   tft->fillScreen(BACKGROUND_COLOR );

   return DONE;


}

/**
 * @brief draw the required screen 
 * 
 * @param screen pointer to the screen and input to the function define 
 *              which screen name that you will draw and must be one of 
 * 
 *                                                              -WELCOME_SCREEN,
 *                                                              -CUSTOMIZE_SCREEN,
 *                                                              -OPEN_HAND_CAL,
 *                                                              -CLOSE_HAND_CAL,
 *                                                              - VERFIY_SCREEN_DONE,
 *                                                              - VERFIY_SCREEN_ERR
 *                                                              -HOME_SCREEN                                                                                        -
 * @return errorState_t   check the function do well 
 */
errorState_t TFT_drawScreen(screen_t * screen,TFT_eSPI * tft)
{
    if(screen == NULL)
    {
        return NULL_PTR;
    }
    switch(screen->screenMode){

        case WELCOME_SCREEN   :
        {
            tft->fillScreen(screen->screenBgColor);
            tft->setTextColor(screen->screenTxtColor);
            //tft->loadFont(screen->fontType);
            tft->setCursor(0, 0);
            tft->setTextSize(screen->screenTxtSize);
            tft->println("Hello!");
            tft->println("Best wishes with ");
            tft->println("Good experience ");
            // draw Logo
             drawBmp("/clap.bmp",0,20,  tft);
             delay(500);
             break;

        }
        case CUSTOMIZE_SCREEN :
        {
            tft->fillScreen(screen->screenBgColor);
            tft->setTextColor(screen->screenTxtColor);
            tft->loadFont(screen->fontType);
            tft->setCursor(0, 0);
            tft->setTextSize(screen->screenTxtSize);
            tft->println("Let's customize!");
            tft->println("Your device ");
            tft->println("Ready ....... ");
           // draw Logo
           // drawBmp()
             delay(500);
             break;
        }
        case OPEN_HAND_CAL    :
        {
            errorState_t localError;
            tft->fillScreen(screen->screenBgColor);
            tft->setTextColor(screen->screenTxtColor);
            tft->loadFont(screen->fontType);
            tft->setCursor(0, 0);
            tft->setTextSize(screen->screenTxtSize);
            tft->println("Open your Hand!");
            tft->println("AS in shape ");
            // draw ready button
            localError = drawButtons(tft ,screen);
            if(localError != DONE)
            {
                return localError;
            }
            break;
        }
        case CLOSE_HAND_CAL   :
        {
            errorState_t localError;
            tft->fillScreen(screen->screenBgColor);
            tft->setTextColor(screen->screenTxtColor);
            tft->loadFont(screen->fontType);
            tft->setCursor(0, 0);
            tft->setTextSize(screen->screenTxtSize);
            tft->println("close your Hand!");
            tft->println("AS in shape ");
            // draw ready button
            localError = drawButtons(tft ,screen);
            if(localError != DONE)
            {
                return localError;
            }
            break;
            }
        case VERFIY_SCREEN_DONE   :
        {
            tft->fillScreen(screen->screenBgColor);
            tft->setTextColor(screen->screenTxtColor);
            tft->loadFont(screen->fontType);
            tft->setCursor(0, 0);
            tft->setTextSize(screen->screenTxtSize);
            tft->println("HI");
            tft->println("Your device is ready ");
            break;
        }
        case VERFIY_SCREEN_ERR   :
        {
            tft->fillScreen(screen->screenBgColor);
            tft->setTextColor(screen->screenTxtColor);
            tft->loadFont(screen->fontType);
            tft->setCursor(0, 0);
            tft->setTextSize(screen->screenTxtSize);
            tft->println("OOPS");
            tft->println("You need to try Again ");
            tft->println("........... ");
            break;
        }
        case HOME_SCREEN      :
        {
            tft->fillScreen(screen->screenBgColor);
            tft->setTextColor(screen->screenTxtColor);
            tft->loadFont(screen->fontType);
            tft->setCursor(0, 0);
            tft->setTextSize(screen->screenTxtSize);
            tft->println("MODES");
           //tft->setCursor(80, 0);
            tft->println("ACTIVE MODE ");
            /* draw button SPEAK MODE*/
            drawButtons(tft,screen);
            break;
            }

    }

    return DONE;
}

/**
 * @brief define which screen is active and state of button
 * 
 * @param screen is input pramter that used to get it state and output parameter store the active element in it 
 *
 * @return errorState_t check the function do its job
 */
errorState_t TFT_getScreenButtonState(screen_t * screen )
{
    uint8_t counter;
    if(screen == NULL )
    {
        return NULL_PTR;
    }
    for(counter = 0 ; counter < screen->numberOfButtons ; counter++)
    {  
        if(screen->drawnButton[counter]->chosen == TRUE)
        {
              screen->active_button = screen->drawnButton[counter] ;
              return DONE;
        }
    
    }

     screen->active_button =NULL;

    return DONE;

}
/**
 * @brief control of the state of the screen if action is taken or not
 * 
 * @param screen  the input of function to navigate the state of screen
 * 
 * @param screenState  acton is required as
 *                                            -SET_BUTTON
 *                                            -MOVE
 * 
 * @return errorState_t 
 */
errorState_t TFT_setScreenButtonState(TFT_eSPI * tft ,screen_t * screen, screenState_t screenState)
{
    if(screen == NULL)
    {
        return NULL_PTR;
    }
    if(screenState == SET_BUTTON)
    {
        if(screen->active_button->nameButton == SPEAK_BT||screen->active_button->nameButton == MUTE_BT||screen->active_button->nameButton == READY)
        {
            tft->drawRect(screen->active_button->button_x,screen->active_button->button_y,screen->active_button->button_w,screen->active_button->button_h,FRAME_COLOR);
            screen->active_button->chosen == true;
        }
    }
    else if(screenState == MOVE)
    {
        /*screen->active_button->nameButton mean current button*/
        switch(screen->active_button->nameButton)
        {
            case SPEAK_BT:
            {
                ++screen->active_button; // move to next button
                
                tft->drawRect(screen->active_button->button_x,screen->active_button->button_y,screen->active_button->button_w,screen->active_button->button_h,FRAME_COLOR);
                
                 screen->active_button->chosen=TRUE;

                break;
            }
            case MUTE_BT:
            {
                --screen->active_button; // move to back button
                
                tft->drawRect(screen->active_button->button_x,screen->active_button->button_y,screen->active_button->button_w,screen->active_button->button_h,FRAME_COLOR);
                
                screen->active_button->chosen=TRUE;

                break;

            } 

            case READY:
            {    
                tft->drawRect(screen->active_button->button_x,screen->active_button->button_y,screen->active_button->button_w,screen->active_button->button_h,FRAME_COLOR);
                
                screen->active_button->chosen=TRUE;

                break;

            } 

            
            
        }

    }

    return DONE;


}

