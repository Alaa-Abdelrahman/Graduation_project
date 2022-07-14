/**
 * @file FlEX_interface.h
 * @author Alaa Abdelrahman  (alaaawad17@gmail.com)
 * @brief  include the interfaces  and type declarations of FLEX sensors
 * @version 0.1
 * @date 2022-07-014
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef FLEX_INTERFACE_H
#define FLEX_INTERFACE_H

#define FLEX_NUMBER_OF_SENSORS 5            // number of flex sensors
#define CLIBRATE_MODE          1            // clibrate mode for FLEX_read function
#define NORMAL_MODE            2            // normal mode for FLEX_read function

#define NO_READS              200          // number of reads to average the resistance of the flex sensor

#define FLEX_LITTLE_FINGER_PIN   39       // Pin connected to Flex sensor of the little finger 
#define FLEX_RING_FINGER_PIN     34       // Pin connected to Flex sensor of the ring finger 
#define FLEX_MIDDLE_FINGER_PIN   35       // Pin connected to Flex sensor of the middle finger 
#define FLEX_INDEX_FINGER_PIN    32       // Pin connected to Flex sensor of the index finger 
#define FLEX_THUMB_FINGER_PIN    33       // Pin connected to Flex sensor of the thumb finger 

#define VCC                 ((float)3.3)                   // voltage at Ardunio 3.3V line
#define R_DIV               ((float)56000.0)               // resistor used to create a voltage divider at the little finger


/************************************************************************************************************************
 * ------------------------------------------------ type declration-------------------------------------------------
 ************************************************************************************************************************/

/**
 * @brief enum define types of error in our software component 
 * 
 */
enum errorState_t{
    NULL_PTR,
    SPIFFS_ERROR_INIT,
    OUT_SCOPE,
    FILE_NOT_FOUND,
    INVALID_MODE,
     DONE
};


/************************************************************************************************************************
 * ------------------------------------------------ Function interfaces-------------------------------------------------
 ************************************************************************************************************************/

/**
 * @brief  configure the flex sensors and initialize the pins connected to the flex sensors
 * 
 * @param void
 * 
 * @return errorState_t to check the function did well 
 */
errorState_t FLEX_config(void);

/**
 * @brief claibrate the readings of the flex sensors, through average filter
 *         used in the case of calculating the bend and flat resistance each  flex sensor 
 *
 * @param (out) parrFlexValue pointer to array of float to store the bend and flat resistance of each flex sensor 
 * 
 * @return errorState_t to check the function did well 
 */

errorState_t FLEX_calibrate(float * parrFlexValue);



/**
 * @brief read the flex sensors anagles and store the readings in the array of uint8_t
 *
 * @param (in) parrRFlexFlatValue pointer to array of float to store the bend and flat resistance of each flex sensor
 * @param (out) parrFlexValue pointer to array of float to store the reading of each flex sensor
 * 
 * @return errorState_t to check the function did well 
 */

errorState_t FLEX_getReads(uint8_t * parrFlexValue,float * parrRFlexFlatValue,float * parrRFlexBendValue);


#endif // FLEX_INTERFACE_H