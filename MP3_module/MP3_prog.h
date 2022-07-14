

/**
 * @file MP3_prog.c
 * @author Alaa Abdelrahman  (alaaawad17@gmail.com)
 * @brief  include implementation  of MP3 player
 * @version 0.1
 * @date 2022-07-014
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include "DFRobotDFPlayerMini.h"

#include "MP3_interface.h"

/*<
*@brief  use UART1 of esp32 to communicate with MP3 player
 */

HardwareSerial mySoftwareSerial(1);

/**
 * @brief  configure MP3 player paramters such as 
 *        -baud rate
 *        -equalizer mode
 *        -volume
 *        -enable DAC
 *        -specify SD card as output 
 * 
 * 
 * @param IN:myDFPlayer pionter to mp3 player
 * @param IN:VOlume to set the volume of the mp3 player
 * 
 * @return errorState_t to check the function did well 
 */
errorState_t MP3_config(myDFPlayer_t *myDFPlayer, uint8_t u8Volume)
{
    errorState_t errorState = DONE;
    if (myDFPlayer == NULL)
    {
        errorState = NULL_PTR;

        return errorState;
    }
    
     mySoftwareSerial.begin(BAUD_RATE, SERIAL_8N1, 16, 17);
    
    if (!myDFPlayer->begin(&mySoftwareSerial))
        {
            errorState = MP3_UANBLE_TO_INITIALIZE;

        }
        else
        { 
            //Set serial communictaion time out 500ms
            myDFPlayer.setTimeOut(500);
            // Set volume 0~30
            myDFPlayer->setVolume(u8Volume);

            // set equalizer mode 
            myDFPlayer->EQ(EQ_MODE);

            //----Set device we use SD as default----
            myDFPlayer->setDevice(DFPLAYER_DEVICE_SD);

            //Enable On-chip DAC
            myDFPlayer.enableDAC();  




        }
    return errorState;
      
}
  

 /**
 * @brief  play from specific file number and folder 
 * 
 * 
 * @param IN:myDFPlayer pionter to mp3 player
 * @param IN:u8FileNO file number to play
 * @param IN:u8FolderNO folder number to play
 * 
 * @return errorState_t to check the function did well 
 */   
errorState_t MP3_play(uint8_t u8FileNO, uint8_t u8Folder,myDFPlayer_t *myDFPlayer)
{
    errorState_t errorState = DONE;
    if (myDFPlayer == NULL)
    {
        errorState = NULL_PTR;

        return errorState;
    }
    if (myDFPlayer->play(u8Folder, u8FileNO))
    {
        errorState = DONE;
    }
    else
    {
        errorState = FILE_NOT_FOUND;
    }
    return errorState;
}


/**
 * @brief  puase MP3 player
 * 
 * 
 * @param IN:myDFPlayer pionter to mp3 player
 
 * @return errorState_t to check the function did well 
 */

errorState_t MP3_pause(myDFPlayer_t *myDFPlayer)
{
    errorState_t errorState = DONE;
    if (myDFPlayer == NULL)
    {
        errorState = NULL_PTR;

        return errorState;
    }

    myDFPlayer->pause();

    return errorState;
}

/**
 * @brief  set the volume of the mp3 player in range 0~30 
 * 
 * 
 * @param IN:myDFPlayer pionter to mp3 player
 * @param IN:u8Volume volume to set the mp3 player
 * 
 * @return errorState_t to check the function did well 
 */ 
errorState_t MP3_setVolume(uint8_t u8Volume,myDFPlayer_t *myDFPlayer)
{
    errorState_t errorState = DONE;

    if (myDFPlayer == NULL)
    {
        errorState = NULL_PTR;

        return errorState;
    }

 // check if the volume is in range 0~30
    if (u8Volume < 31 && u8Volume > 0)
    {
        myDFPlayer->setVolume(u8Volume);
        
    }
    else
    {
        errorState = INVALID_VOLUME;
    }
    
    return errorState;
}

