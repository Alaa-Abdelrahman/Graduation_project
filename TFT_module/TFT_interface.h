/**
 * @file TFT_interface.h
 * @author Alaa Abdelrahman  (alaaawad17@gmail.com)
 * @brief  include the interfaces  and type declarations of tft screen 
 * @version 0.1
 * @date 2022-04-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef TFT_INTERFACE_H
#define TFT_INTERFACE_H

    #define DEBUGPRINT(x)       Serial.print (x)
    #define DEBUGPRINTDEC(x)    Serial.print (x, DEC)
    #define DEBUGPRINTLN(x)     Serial.println (x)


/***************************************************************************************
** Colour options

                    -TFT_BLACK      
                    -TFT_NAVY       
                    -TFT_DARKGREEN  
                    -TFT_DARKCYAN   
                    -TFT_MAROON     
                    -TFT_PURPLE     
                    -TFT_OLIVE      
                    -TFT_LIGHTGREY  
                    -TFT_DARKGREY   
                    -TFT_BLUE       
                    -TFT_GREEN      
                    -TFT_CYAN       
                    -TFT_RED        
                    -TFT_MAGENTA    
                    -TFT_YELLOW     
                    -TFT_WHITE      
                    - TFT_ORANGE     
                    - TFT_GREENYELLOW
                    - TFT_PINK           
                    - TFT_BROWN      
                    - TFT_GOLD       
                    - TFT_SILVER     
                    - TFT_SKYBLUE    
                    - TFT_VIOLET     
*/
#define BACKGROUND_COLOR        TFT_BLACK
#define TFT_TEXT                TFT_WHITE
#define FRAME_COLOR             TFT_RED

/************************************************************************************************************************
 * ------------------------------------------------ type declration-------------------------------------------------
 ************************************************************************************************************************/


/**
 * @brief define the mode of screen 
 * 
 */
typedef enum{
    WELCOME_SCREEN,
    CUSTOMIZE_SCREEN,
    OPEN_HAND_CAL,
    CLOSE_HAND_CAL,
    VERFIY_SCREEN_DONE,
    VERFIY_SCREEN_ERR,
    HOME_SCREEN
}screenMode_t;

/**
 * @brief define boolean types
 * 
 */
typedef enum {
    TRUE,
    FALSE
}bool_t;


typedef enum {
    READY,
    SPEAK_BT,
    MUTE_BT,
     NOT_FOUND

}nameButton_t;

/**
 * @brief defin specs of drawn button 
 * 
 */
 struct drawnButtonSpec_t{
    nameButton_t nameButton;
    uint8_t button_x;
    uint8_t button_y;
    uint8_t button_w;
    uint8_t button_h;
    uint16_t button_color;
    uint16_t button_txt_color;
    String button_text;
    bool_t chosen ;

};

/**
 * @brief enum define types of error in our software component 
 * 
 */
enum errorState_t{
    NULL_PTR,
    SPIFFS_ERROR_INIT,
    OUT_SCOPE,
    FILE_NOT_FOUND,
    BMP_FORMAT_ERROR,
    DONE
};

/**
 * @brief define the possiple orientation of screen 
 * 
 */
 enum  screenOrient_t{
    ORIENT_0,
    ORIENT_90,
    ORIENT_180,
    ORIENT_270,
    MIRROR
};

/**
 * @brief define the attribute of the screen
 * 
 */
struct screen_t{
    screenMode_t screenMode;
     uint8_t numberOfButtons ;
    drawnButtonSpec_t * drawnButton[3];
    uint16_t screenBgColor;
    uint16_t screenTxtColor;
    uint8_t screenTxtSize;
    drawnButtonSpec_t * active_button;
    String fontType;
    
};

enum screenState_t
{
    SET_BUTTON,
    MOVE,
};


/************************************************************************************************************************
 * ------------------------------------------------ functions interface-------------------------------------------------
 ************************************************************************************************************************/

/**
 * @brief  instantiate screen, set orientation and clear screen 
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
errorState_t  TFT_config(TFT_eSPI * tft ,screenOrient_t orient);

/**
 * @brief draw the required screen 
 * 
 * @param screenName input to the function define which screen will draw and must be one of 
 *                                                                                          - WELCOME_SCREEN,
 *                                                                                          - CUSTOMIZE_SCREEN,
 *                                                                                          - OPEN_HAND_CAL,
 *                                                                                          - CLOSE_HAND_CAL,
 *                                                                                          - VERFIY_SCREEN,
 *                                                                                          - HOME_SCREEN
 * @return errorState_t   check the function do well 
 */
errorState_t TFT_drawScreen(screen_t * screen,TFT_eSPI * tft);

/**
 * @brief define which screen is active and state of button
 * 
 * @param screen is output pramter that used o reurn the value of the active screen
 * 
 * @return errorState_t check the function do its job
 */
errorState_t TFT_getScreenState(screen_t * screen);
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
errorState_t TFT_setScreenState(screen_t * screen, screenState_t screenState);

/**
 * @brief draw Bmp picture on the specified screen
 * 
 * @param filename bmp picture that you want to draw
 * @param x        x origin point to draw the bmp picture
 * @param y        y origin point to draw the bmp picture
 * @param tft      pointer to the initailized hardware screen
 * @return errorState_t 
 */

errorState_t drawBmp(const char *filename, int16_t x, int16_t y, TFT_eSPI* tft) ;





#endif