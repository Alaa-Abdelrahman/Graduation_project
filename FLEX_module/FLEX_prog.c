
/**
 * @file Flex_prog.cpp
 * @author Alaa Abdelrahman  (alaaawad17@gmail.com)
 * @brief include the implemntation of FLEX functions
 * @version 0.1
 * @date 2022-07-014
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <Arduino.h>

#include "Flex_interface.h"





/**
 * @brief  used to read the resistance of the flex sensor and operate in two mode 
 *                                                                                  1) CLIBRATE_MODE 
 *                                                                                  2) NORMAL_MODE
 * 
 * @param(OUT) parrfRFlexValue pointer to array to store the resistance of the flex sensor
 *  
 * @param(IN) u8Mode determines the mode of function opartaion that is either CLIBRATE_MODE or NORMAL_MODE
 * 
 * @return errorState_t to check the function did well 
 */


errorState_t FLEX_read(float * parrfRFlexValue,uint8_t u8Mode)
{
    
    // initialize the error state to no error
    errorState_t errorState = DONE;

    if (parrfRFlexValue == NULL)
    {
        errorState = NULL_PTR;
        return errorState;

    }

     // initialize the array of float to store the bend or flat resistance of each flex sensor
    float arrfVFlexValue[FLEX_NUMBER_OF_SENSORS] = {0};

    parrfVFlexValue[0]= ( analogRead( FLEX_LITTLE_FINGER_PIN )* VCC) / 4095.0;
    parrfVFlexValue[1]= ( analogRead( FLEX_RING_FINGER_PIN )  * VCC) / 4095.0 ; 
    parrfVFlexValue[2]= ( analogRead( FLEX_MIDDLE_FINGER_PIN )* VCC) / 4095.0 ; 
    parrfVFlexValue[3]= ( analogRead( FLEX_INDEX_FINGER_PIN ) * VCC) / 4095.0 ; 
    parrfVFlexValue[4]= ( analogRead( FLEX_THUMB_FINGER_PIN ) * VCC) / 4095.0 ;
    
    if(u8Mode == NORMAL_MODE)
    {
    // calculate the bend or flat resistance of each flex sensor
    parrfRFlexValue[0]=R_DIV* (VCC/parrfVFlexValue[0]-1.0);
    parrfRFlexValue[1]=R_DIV* (VCC/parrfVFlexValue[1]-1.0);
    parrfRFlexValue[2]=R_DIV* (VCC/parrfVFlexValue[2]-1.0);
    parrfRFlexValue[3]=R_DIV* (VCC/parrfVFlexValue[3]-1.0);
    parrfRFlexValue[4]=R_DIV* (VCC/parrfVFlexValue[4]-1.0);
    }
    else if(u8Mode == CLIBRATE_MODE)
    {
    {
        // calculate the bend or flat resistance of each flex sensor
        parrfRFlexValue[0]+=R_DIV* (VCC/parrfVFlexValue[0]-1.0);
        parrfRFlexValue[1]+=R_DIV* (VCC/parrfVFlexValue[1]-1.0);
        parrfRFlexValue[2]+=R_DIV* (VCC/parrfVFlexValue[2]-1.0);
        parrfRFlexValue[3]+=R_DIV* (VCC/parrfVFlexValue[3]-1.0);
        parrfRFlexValue[4]+=R_DIV* (VCC/parrfVFlexValue[4]-1.0);
    }
    else
    {
        errorState = INVALID_MODE;
        return errorState;
    }

    return errorState;


}

errorState_t FLEX_getAvg(float * parrfRFlexValue)
{
    // inintalize the error state to no error
    errorState_t errorState = DONE;
    if(parrfRFlexValue == NULL)
    {
        errorState = NULL_PTR;
        return errorState;
    }
    
    uint8_t u8Counter = 0;

    for(u8Counter = 0; u8Counter < FLEX_NUMBER_OF_SENSORS; u8Counter++)
    {
        parrfRFlexValue[u8Counter] = parrfRFlexValue[u8Counter]/NO_READS;
    }

    return errorState;
}


/********************************************************************************************************************
 * --------------------------------- INTERFACES  FUNCTION ---------------------------------------------------------------
 *******************************************************************************************************************/

/**
 * @brief  configure the flex sensors and initialize the pins connected to the flex sensors
 * 
 * @param void
 * 
 * @return errorState_t to check the function did well 
 */
errorState_t FLEX_config(void)
{
    // configure the pins connected to the flex sensors
    pinMode(FLEX_LITTLE_FINGER_PIN, INPUT);
    pinMode(FLEX_RING_FINGER_PIN  , INPUT);
    pinMode(FLEX_MIDDLE_FINGER_PIN, INPUT);
    pinMode(FLEX_INDEX_FINGER_PIN , INPUT);
    pinMode(FLEX_THUMB_FINGER_PIN , INPUT);
} 

/**
 * @brief claibrate the readings of the flex sensors, through average filter
 *         used in the case of calculating the bend and flat resistance each  flex sensor 
 *
 * @param (out) parrFlexValue pointer to array of float to store the bend and flat resistance of each flex sensor 
 * 
 * @return errorState_t to check the function did well 
 */
errorState_t FLEX_calibrate(float * pfarrRFlexValue)
{
    // initialize the error state to no error
    errorState_t errorState = DONE;
    if(pfarrFlexValue == NULL)
    {
        errorState = NULL_PTR;
        return errorState;
    }
    // initialize the counter to count the number of times the average filter is applied
    uint8_t u8Counter = 0;

      for(:u8Counter<NO_READS:u8Counter++)
      {
        // read the flex sensors
        FLEX_read(pfarrRFlexValue,CLIBRATE_MODE);
     }

    // get the average of the readings of the flex sensors
    FLEX_getAvg(pfarrRFlexValue);
      return errorState;
}

/**
 * @brief read the flex sensors anagles and store the readings in the array of uint8_t
 *
 * @param (in) parrRFlexFlatValue pointer to array of float to store the bend and flat resistance of each flex sensor
 * @param (out) parrFlexValue pointer to array of float to store the reading of each flex sensor
 * 
 * @return errorState_t to check the function did well 
 */

errorState_t FLEX_getReads(uint8_t * parrFlexValue,float * parrRFlexFlatValue,float * parrRFlexBendValue)
{
    // initalize the error state to no error
    errorState_t errorState = DONE;
    if(parrFlexValue == NULL)
    {
        errorState = NULL_PTR;
        return errorState;
    }

    //intialize array of float to store the reading of each flex sensor
    float arrfRFlexValue[FLEX_NUMBER_OF_SENSORS] = {0};
    // read the flex sensors
    FLEX_read(arrfRFlexValue,NORMAL_MODE);

    // convert the readings of the flex sensors to angle in degrees
    uint8_t u8Counter = 0;
    for(u8Counter = 0; u8Counter < FLEX_NUMBER_OF_SENSORS; u8Counter++)
    {
        parrFlexValue[u8Counter] = map(arrfRFlexValue[u8Counter],parrRFlexFlatValue[u8Counter],parrRFlexBendValue[u8Counter],0, 90);
    }


}
