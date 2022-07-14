/**
 * @file MPU_interface.h
 * @author Alaa Abdelrahman  (alaaawad17@gmail.com)
 * @brief  include the interfaces  and type declarations of FLEX sensors
 * @version 0.1
 * @date 2022-07-014
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef MPU_INTERFACE_H
#define MPU_INTERFACE_H


#define NO_SENSOR_READS        6          // number of sensor reads 

#define CLIBRATE_MODE          1            // clibrate mode for FLEX_read function
#define READ_MODE              2            // normal mode for FLEX_read function

#define CALIBRATE_COUNTER     200         // number of samples for calibration

/*<
*@brief Accelerometer ranges:
*               1-MPU6050_RANGE_2_G
*               2-MPU6050_RANGE_4_G
*               3-MPU6050_RANGE_8_G
*               4-MPU6050_RANGE_16_G
*/


#define ACCEL_RANGE   MPU6050_RANGE_8_G

/*<
*@brief Gyroscope ranges:
*               1-MPU6050_RANGE_250_DEG
*               2-MPU6050_RANGE_500_DEG
*               3-MPU6050_RANGE_1000_DEG
*               4-MPU6050_RANGE_2000_DEG
*/

#define GYRO_RANGE    MPU6050_RANGE_250_DEG

/*<
*@brief bandwidth filter:
*               1-MPU6050_BAND_21_HZ
*               2-MPU6050_BAND_44_HZ
*               3-MPU6050_BAND_94_HZ
*               4-MPU6050_BAND_184_HZ
*               5-MPU6050_BAND_260_HZ

*/

#define BANDWIDTH     MPU6050_BAND_44_HZ

typedef Adafruit_MPU6050 mpu_t;

enum errorState_t{
    NULL_PTR,
    SPIFFS_ERROR_INIT,
    OUT_SCOPE,
    FILE_NOT_FOUND,
    INVALID_MODE,
    MPU_NOT_CONNECTED,
     DONE
};


/************************************************************************************************************************
 * ------------------------------------------------ Function interfaces-------------------------------------------------
 ************************************************************************************************************************/

/**
 * @brief  configure the MPU and initialize the pins connected to MPU
 * 
 * @param void
 * 
 * @return errorState_t to check the function did well 
 */
errorState_t MPU_config(void);

/**
 * @brief claibrate the readings of MPU, through average filter
 *         to set the offest of reading of mpu
 *
 * @param (out) parrMPUValue pointer to array of to store the reading of MPU offset
 * 
 * @return errorState_t to check the function did well 
 */

errorState_t MPU_calibrate(uint16_t * parrMPUValue);



/**
 * @brief read the MPU and store the readings in the array of uint16_t
 *       operates on two mode : calibrate and normal mode
 *
 * @param out parrMPUValue pointer to array of uint16_t to store the reading of MPU
 * 
 * @param in parrMPUoffsetValues pointer to array that stores the offset of MPU
 * 
 * @param in u8Mode to check if the readings are for calibration or for normal operation
 * 
 * @return errorState_t to check the function did well 
 */
errorState_t MPU_getReads(uint16_t * parrMPUValue, uint16_t * parrMPUoffsetValues);




#endif