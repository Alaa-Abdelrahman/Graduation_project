/**
 * @file MPU_prog.cpp
 * @author Alaa Abdelrahman  (alaaawad17@gmail.com)
 * @brief include the implemntation of MPU functions
 * @version 0.1
 * @date 2022-07-014
 * 
 * @copyright Copyright (c) 2022
 * 
 */



#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#include "MPU_interface.h"


// initalize the accelemeter and gyroscope objects
sensors_event_t a, g, temp;


/**
 * @brief  configure the MPU parameters and initialize the MPU6050
 *            -inatilize the MPU6050 I2C bus
 *            -Inatilize the MPU6050 sensor
 *            -configure Accelerometer range
 *            -configure Gyroscope range
 *            -define bandwidth of Low pass filter
 * 
 * @param in mpu pointer to the MPU6050 object
 * 
 * @return errorState_t to check the function did well 
 */
errorState_t MPU_config(mpu_t * mpu)
{
    // initialize the error state to no error
    errorState_t errorState = DONE;

    if (mpu == NULL)
    {
        errorState = NULL_PTR;
        return errorState;

    }

    // initialize the i2C bus
    Wire.begin();
    delay(10);

    // check if the MPU is connected to the I2C bus
    if (!mpu->begin()) {
    
        errorState = MPU_NOT_CONNECTED;
        return errorState;
    }

    // set accelerometer range 
     mpu->setAccelerometerRange(ACCEL_RANGE);

    // set gyroscope range
    mpu->setGyroRange(GYRO_RANGE);

    // bandwidth of filter
    mpu->setFilterBandwidth(BANDWIDTH); 


    return errorState;
    }

/**
 * @brief read the MPU and store the readings in the array of uint16_t
 *       operates on two mode : calibrate and normal mode
 *
 * @param out parrMPUValue pointer to array of uint16_t to store the reading of MPU
 * 
 * @param in u8Mode to check if the readings are for calibration or for normal operation
 * 
 * @return errorState_t to check the function did well 
 */

errorState_t MPU_getReads(uint16_t * parrMPUValue,uint16_t * parrMPUoffsetValues, uint8_t u8Mode)
{
    // initialize the error state to no error
    errorState_t errorState = DONE;
    if (parrMPUValue == NULL)
    {
        errorState = NULL_PTR;
        return errorState;
    }
    // read the MPU
    mpu->getEvent(&a, &g, &temp);
    // store the readings in the array of uint16_t
    if (u8Mode == CALIBRATE_MODE)
    {
        parrMPUValue[0] += a.acceleration.x;
        parrMPUValue[1] += a.acceleration.y;
        parrMPUValue[2] += a.acceleration.z;
        parrMPUValue[3] += g.gyro.x;
        parrMPUValue[4] += g.gyro.y;
        parrMPUValue[5] += g.gyro.z;
    }
    else if (u8Mode == READ_MODE)
    {
        parrMPUValue[0] = a.acceleration.x - parrMPUoffsetValues[0];
        parrMPUValue[1] = a.acceleration.y - parrMPUoffsetValues[1];
        parrMPUValue[2] = a.acceleration.z - parrMPUoffsetValues[2];
        parrMPUValue[3] = g.gyro.x - parrMPUoffsetValues[3];
        parrMPUValue[4] = g.gyro.y - parrMPUoffsetValues[4];
        parrMPUValue[5] = g.gyro.z - parrMPUoffsetValues[5];
    }
    else
    {
        errorState = INVALID_MODE;
        return errorState;
    }
    return errorState;
}



/**
 * @brief claibrate the readings of MPU, through average filter
 *         used in the case of calculating the bend and flat resistance each  flex sensor 
 *
 * @param (out) parrMPUValue pointer to array of to store the reading of MPU offset
 * 
 * @return errorState_t to check the function did well 
 */

errorState_t MPU_calibrate(uint16_t * parrMPUoffsetValues)
{
    // initialize the error state to no error
    errorState_t errorState = DONE;
    if (parrMPUoffsetValues == NULL)
    {
        errorState = NULL_PTR;
        return errorState;
    }
    // initialize the array of uint16_t to store the readings of MPU
    uint16_t arrMPUValue[NO_SENSOR_READS] = {0};

    // initalize the counter to zero
    uint8_t u8Counter = 0;

    // apply the average filter to the readings of MPU
    for(u8Counter = 0; u8Counter < CALIBRATE_COUNTER; u8Counter++)
    {
        MPU_getReads(arrMPUValue, parrMPUoffsetValues, CALIBRATE_MODE);
    }
    // divide the readings by the number of readings to get the average
    for(u8Counter = 0; u8Counter < NO_SENSOR_READS; u8Counter++)
    {
        parrMPUoffsetValues[u8Counter] = arrMPUValue[u8Counter] / CALIBRATE_COUNTER;
    }
}
