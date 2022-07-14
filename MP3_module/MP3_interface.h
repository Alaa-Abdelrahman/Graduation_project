/**
 * @file MP3_interface.h
 * @author Alaa Abdelrahman  (alaaawad17@gmail.com)
 * @brief  include the interfaces  and type declarations of MP3 sensors
 * @version 0.1
 * @date 2022-07-014
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef MP3_INTERFACE_H
#define MP3_INTERFACE_H

#define BAUD_RATE 9600

/**
 * @brief  set equalizer mode to:
*                   -DFPLAYER_EQ_NORMAL
*                   -DFPLAYER_EQ_POP
*                   -DFPLAYER_EQ_ROCK
*                   -DFPLAYER_EQ_JAZZ
*                   -DFPLAYER_EQ_CLASSIC
*                   -DFPLAYER_EQ_BASS
*  
 */

#define EQ_MODE  DFPLAYER_EQ_NORMAL

typedef DFRobotDFPlayerMini myDFPlayer_t;


/**
 * @brief enum define types of error in our software component 
 * 
 */
enum errorState_t{
    NULL_PTR,
    MP3_UANBLE_TO_INITIALIZE,
    SPIFFS_ERROR_INIT,
    OUT_SCOPE,
    FILE_NOT_FOUND,
    INVALID_MODE,
    INVALID_VOLUME,
     DONE
};

/************************************************************************************************************************
 * ------------------------------------------------ Function interfaces-------------------------------------------------
 ************************************************************************************************************************/

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
errorState_t MP3_config(myDFPlayer_t *myDFPlayer, uint8_t u8Volume);

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
errorState_t MP3_play(uint8_t u8FileNO, uint8_t u8Folder,myDFPlayer_t *myDFPlayer);

/**
 * @brief  puase MP3 player
 * 
 * 
 * @param IN:myDFPlayer pionter to mp3 player
 
 * @return errorState_t to check the function did well 
 */  
errorState_t MP3_pause(myDFPlayer_t *myDFPlayer);

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

#endif