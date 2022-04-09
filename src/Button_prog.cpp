/**
 * @file Button_prog.cpp
 * @author Alaa Abdelrahman  (alaaawad17@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */
 

/************************************************************************************************
 *------------------------- file inclusion------------------------------------------------------
 *************************************************************************************************/
#include <Arduino.h>
#include "Button_interface.h"



/************************************************************************************************
 *------------------------- function defintation ------------------------------------------------
 *************************************************************************************************/


/**
 * @brief function is used to configure the button pin, mode of connection 
 * 
 * @param pin  is the input to function that the button connect to  
 * @param mode is the input to function that is the mode of connection as   1-INPUT,
 *                                                                          2-OUTPUT,
 *                                                                          3-INPUT_PULLDOWN,
 *                                                                          4-INPUT_PULLUP
 * @param button is the pionter to the button need to configure 
 * 
 * @return errorState_t  to check the function do well or not 
 */
errorState_t Button_Config( uint8_t pin ,buttonMode_t mode ,button_t *button)
{
    
    if( button == NULL)
    {
        return NULL_PTR;
    }
    
    if(mode == OUTPUT_MODE || mode == INPUT_MODE || mode == INPUT_PULLDOWN_MODE || mode == INPUT_PULLUP_MODE)
    {
        button->mode = mode;
    }
    else
    {
        return MODE_ERROR;
    }

    pinMode(pin,mode);

    return DONE;
   
}

/**
 * @brief function is used to get the state of the button 
 * 
 * @param button is the input to he function that pionter to the button used to get the state 
 *  
 * @param state   is the output of function and pointer to the state
 * 
 * @return errorState_t to check the function do well or not 
 */
errorState_t Button_getState(button_t *button, buttonState_t * state)
{
    uint8_t local_read;
    if( button == NULL || state == NULL)
    {
        return NULL_PTR;
    }
    else
    {
        local_read = digitalRead(button->pin );
        if(button->mode ==  INPUT_PULLDOWN_MODE)
        {
            
            if(local_read == HIGH)
            {
                *state = PRESSED;
            }
            else
             {
                *state = NOT_PRESSD ;    
            }

        }
        else if(button->mode ==  INPUT_PULLUP_MODE)
        {
            
            if(local_read == LOW)
            {
                *state = PRESSED;
            }
            else
            {
                *state = NOT_PRESSD ;
            }

        }
        else
        {
            return NULL_PTR;
        }
    }
    return  DONE;

}

