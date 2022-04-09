/**
 * @file Button_interface.h
 * @author Alaa Abdelrahman  (alaaawad17@gmail.com)
 * @brief this file include interface for button
 * @version 0.1
 * @date 2022-04-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef BUTTON_INTERFACE_H
#define BUTTON_INTERFACE_H

/*********************************************************************************
 * --------------------------- type decleration ----------------------------------
 *********************************************************************************/

/**
 * @brief enum define the modes of connection of button 
 * 
 */

typedef enum {
    INPUT_MODE,
    OUTPUT_MODE,
    INPUT_PULLDOWN_MODE,
    INPUT_PULLUP_MODE
    } buttonMode_t;

/**
 * @brief enum define the state of button
 * 
 */
typedef enum {
    PRESSED,
    NOT_PRESSD
    }buttonState_t;

/**
 * @brief  struct that contains the attributes of button
 *          such as pin , mode and state 
 */
typedef struct{
    uint8_t pin ;
    buttonMode_t mode;
    buttonState_t state;
    }button_t;

/**
 * @brief enum define types of error in our software component 
 * 
 */

typedef enum{
    NULL_PTR,
    MODE_ERROR,
    PIN_NOT_FOUND,
    DONE
    }errorState_t;


/************************************************************************************************************************
 * ------------------------------------------------ functions interface-------------------------------------------------
 ************************************************************************************************************************/

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
errorState_t Button_Config( uint8_t pin ,buttonMode_t mode ,button_t *button);

/**
 * @brief function is used to get the state of the button 
 * 
 * @param button is the input to he function that pionter to the button used to get the state 
 *  
 * @param state   is the output of function and pointer to the state
 * 
 * @return errorState_t to check the function do well or not 
 */
errorState_t Button_getState(button_t *button, buttonState_t * state);

#endif