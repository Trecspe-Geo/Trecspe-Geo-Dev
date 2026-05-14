/********************************************************************************************************************
*
*
*
* Copyright (C) 2026 Trecspe.  All rights reserved.
*
********************************************************************************************************************/

/********************************************************************************************************************
* @file		common.h
* @company	Trecspe
* @author	Armel Kamdem
* @date		14.05.2026
*********************************************************************************************************************
* @brief	Global variable.
*
*		This file contain global definition
*
*********************************************************************************************************************
*@remarks
*
********************************************************************************************************************/

#ifndef _COMMON_H_
#define _COMMON_H_ 

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>
#include <ctype.h>
//#include "linked_list.h"

#define CLEARFLAG(reg, Flag)            ((reg) &= ~(1u << (Flag)));
                                                                        /*< Bit in RAM- Variable l schen >                            */
#define     SETFLAG( reg, Flag )        ( ( reg ) |= ( 1u << ( Flag ) ) )
                                                                        /*< Bit in RAM- Variable setzen >                             */
#define     TESTFLAG( reg, Flag )       ( ( reg ) & ( 1u << ( Flag ) ) )
                                                                        /*< Bit in RAM- Variable abfragen >                           */
#define     MSB_SET( reg )              ( ( reg ) & ( 1u << ( MSB ) ) )
#define READFLAGSTATE(u32Reg, bitPosition)\
  ((u32Reg & (1u << bitPosition)) >> bitPosition) 
#define SETMULTIPLEFLAG(u32Reg, bitPositionStart, val)\
        u32Reg |= (val << bitPositionStart)
#define   NULL_PTR                         (void*)0
#define   ON                               (uint8_t)1u
#define   OFF                              (uint8_t)0u
#define   ZERO                             (uint8_t)0u
#define   ONE                              (uint8_t)1U
#define   TWO                              (uint8_t)2U
#define   THREE                            (uint8_t)3U
#define   FOUR                             (uint8_t)4U
#define   FIVE                             (uint8_t)5U
#define   SIX                              (uint8_t)6U
#define   SEVEN                            (uint8_t)7U
#define   EIGHT                            (uint8_t)8U
#define   NINE                             (uint8_t)9U
#define   TENE                             (uint8_t)10U
#define   ELEVEN                           (uint8_t)11U
#define   TWELVE                           (uint8_t)12U
#define   THIRTEEN                         (uint8_t)13U
#define   FOURTEEN                         (uint8_t)14U
#define   FIVETEEN                         (uint8_t)15U 
#define   SIXTEEN                          (uint8_t)16U
#define   SEVENTEEN                        (uint8_t)17U
#define   EIGHTEEN                         (uint8_t)18U
#define   NINETEEN                         (uint8_t)19U
#define   TWENTY                           (uint8_t)20U
#define   TWENTY_ONE                       (uint8_t)21U
#define   TWENTY_TWO                       (uint8_t)22U

#define   TWENTY_THREE                     (uint8_t)23U
#define   TWENTY_FOUR                      (uint8_t)24U
#define   TWENTY_FIVE                      (uint8_t)25U

#define   TWENTY_SIX                       (uint8_t)26U
#define   TWENTY_SEVEN                     (uint8_t)27U
#define   TWENTY_EIGHT                     (uint8_t)28U


#define   TWENTY_NINE                      (uint8_t)29U
#define   THIRTY                           (uint8_t)30U
#define   THIRTY_ONE                       (uint8_t)31U
#define   THIRTY_TWO                       (uint8_t)32U
#define   THIRTY_THREE                     (uint8_t)33U
#define   THIRTY_FOUR                      (uint8_t)34U
#define   THIRTY_FIVE                      (uint8_t)35U
#define   THIRTY_SIX                       (uint8_t)36U
#define   THIRTY_SEVEN                     (uint8_t)37U
#define   THIRTY_EIGHT                     (uint8_t)38U
#define   THIRTY_NINE                      (uint8_t)39U
#define   FOURTY                           (uint8_t)40U
#define   FOURTYSIX                        (uint8_t)46U
#define  	EQ		                           ==					
#define  	NEQ  	                           !=										
#define  	AND  	                           &&										
#define  	OR		                           ||									
#define  	XOR  	                           ^										
#define  	NOT                              !							
#define  	MODU                       	     %									
#define  	BITOR	                           |										
#define  	BITAND	                         &								
#define  	BITXOR	                         ^									
#define  	BITCPL	                         ~			

#define MILLI_SECONDS                      *1UL
#define SECONDS                            *1000 MILLI_SECONDS
#define MINUTES                            *60UL SECONDS
#define HOURS                              *60UL MINUTES
#define DAYS                               *24UL HOURS

#define MILLISECONDS_TO_HOURS(ms)          (uint32_t)((ms) / (1000.0 * 60.0 * 60.0))

#define EXTERN_MEM_MANAGE_PIN              (uint8_t)1U // pin to enable write or read from the eeprom
#define GSM_POWER_MANAGE_PIN               (uint8_t)0U // pin to on or of the gsm module
#define UTIME_SIZE                         (uint8_t)12
#define FORMATED_VERSION_SIZE              (uint8_t)6
#define CHECK_PTR(x)                       if (x == NULL) while(1)
#define UNUSED_FUNCTION                    __attribute__((unused))
#define noinline                           __attribute__((noinline))
#define PLACE_IN_RAM(x)                    __attribute__((section(x))) __attribute__((__used__))

// Define the version of the firmware
extern const uint8_t __attribute__((section (".text"))) u8FirmVersion[];

#define UNUSED(x)                          (void)(x)

struct  buffer_tTag
{
  uint8_t  *u8Buffer;
  uint16_t u16Lenght;
};

typedef struct buffer_tTag buffer_t;

typedef  float	float32_t;									
typedef  double float64_t;		

/**
 * @brief The Enumeration used to define the True and False for the bool value 
 * 
 */
enum T_bool  								
{														
	FALSE = 0u,  							
	TRUE  = 1u								
} ;  												
typedef  enum T_bool bool_t ;		

typedef void (*cbkFunc_t) (void);

struct __attribute__((packed)) result_tTag 
{
  uint16_t u16NumExtractedDigits;
  uint16_t u16LastDigitIndex;
  bool     bIsDigit;
};

typedef struct result_tTag sResult_t;

/**
 * @brief Define a structure to hold the state of the extraction process
 * 
 */
struct __attribute__((packed)) extractState_tTag
{
  uint8_t  u8State;          // The current state of the state machine (0 or 1)
  uint8_t *u8Str1;           // The first string to search for in the input
  uint8_t *u8Str2;           // The second string to search for in the input
  uint16_t u16Str1Len;       // The length of the str1 string
  uint16_t u16Str2Len;       // The length of the str2 string
  uint16_t u16Match1;        // The number of characters of str1 that have been matched so far
  uint16_t u16Match2;        // The number of characters of str2 that have been matched so far
  uint8_t *u8Result;         // A pointer to the buffer where the resulting string will be stored
  uint16_t u16ResultSize;    // The size of u8Result array
  uint16_t u16ResultLen;     // The length of the resulting string
};

typedef struct extractState_tTag sExtractState_t;

/**
 * Kalman filter states
*/
struct __attribute__((packed)) kalmanFilterState_tTag
{
  float fNoiseCov;           // process noise covariance
  float fNoiseCovMeas;       // measurement noise covariance
  float fEstimatedErrorCov;  // estimation error covariance
  float fKalmanGain;         // kalman gain
  float fEstimatedValue;     // estimated value 
};

typedef struct kalmanFilterState_tTag sKalmanFilterState_t;


/********************************************************************************************************************
 *                                                                                                                  *
 *  P U B L I C    F U N C T I O N    I M P L E M E N T A T I O N S                                                 *
 *                                                                                                                  *
 *******************************************************************************************************************/

/**
 * @brief 
 * 
 * @param pu8InputBuff Buff that you want to extract sub string
 * @param pu8OuputBuff Buff that receive the sub string
 * @param u8Start      Start Index
 * @param u8End        End characher
 * @return uint8_t     the index of end position
 */
uint8_t u8StrSub (const uint8_t* pu8InputBuff, uint8_t*   pu8OuputBuff,
                 uint8_t        u8Start,        uint8_t       u8End);

/**
 * @brief    Take the string and retrun the double value
 * 
 * @param pu8InputBuff  String input 
 * @return double       the convert the String input en return double value
 * 
 * @example pu8InputBuff = "32.1254" \n
 *          double val = 32.1254
 */
double dStrToFloat(const uint8_t* pu8InputBuff);


uint16_t u16ArrayToInt(uint8_t pArray[], uint8_t n);
/**
 * @brief this function 
 * 
 * @param str      input string 
 * @param pos      start position to extract 
 * @param len      len of the string to extract 
 * @param result   output string 
 */
void vExtractsubstring(uint8_t *str, int pos, int len, uint8_t *result);
/* @brief Count the numbe of digit of a given number
 * @brief Count the number of digit of a given number
 * 
 * @param str1 destination string
 * @param str2 Income string
 * @param pos  Position to start to add
 */


/**
 * @brief this function is use to insert a string into another string
 * 
 * @param u8Str1 destination string
 * @param u8Str2 Income string
 * @param u8Pos  Position to start to add
 */
void vInString(uint8_t *u8Str1, uint8_t *u8Str2, uint8_t u8Pos);


/**
 * @brief Inserts elements into a uint8_t array at a specified position.
 *
 * @param u8Array      The array to insert elements into.
 * @param u8ArrayLen    The length of the array.
 * @param u8Elements    The elements to insert.
 * @param u8ElementsLen The number of elements to insert.
 * @param u8Pos         The position to insert the elements at.
 */
void vInsertElements(uint8_t *u8Array, uint8_t u8ArrayLen, uint8_t *u8Elements, uint8_t u8ElementsLen, uint8_t u8Pos); 

/**
 * @brief Convert a floating-point number to a string.
 *
 * This function converts a floating-point number `num` to a string and stores it in the output string `str`.
 * The `precision` parameter specifies the number of digits after the decimal point to include in the output string.
 *
 * @param fNum         The floating-point number to convert.
 * @param u8Str        The output string where the converted number will be stored.
 * @param u8Precision The number of digits after the decimal point to include in the output string.
 */
void vFlotStr(float fNum, uint8_t *u8Str, uint8_t u8Precision);

  /* @note  The sExtractState_t structure holds the current state of the extraction process. It has several fields:
  *        u8State: The current state of the state machine (0 or 1).
  *        u8Str1: The first string to search for in the input.
  *        u8Str2: The second string to search for in the input.
  *        u16Str1Len: The length of the str1 string.
  *        u16Str2Len: The length of the str2 string.
  *        u16Match1: The number of characters of str1 that have been matched so far.
  *        u16Match2: The number of characters of str2 that have been matched so far.
  *        u8Result: A pointer to the buffer where the resulting string will be stored.
  *        u16ResultLen: The length of the resulting string.
  *        The vExtractInit function initializes an extract_state structure with the provided arguments. It sets the initial state to 0, 
  *        copies the u8Str1, u8Str2, and result arguments to their respective fields, and computes the lengths of the str1 and str2 strings 
  *        using the strlen function from the C standard library. It also initializes the u16Match1, u16Match2, and u16ResultLen fields to 0.
  *
  *        The u8ExtractNext function processes a single character of input and updates the state machine accordingly. 
  *        It takes two arguments: a pointer to an extract_state structure and a character to process. 
  *        The function first checks which state the state machine is currently in by examining the value of the state->state field.
  *
  *        If the state machine is in state 0, it checks if the input character matches the next character of the u8Str1 string by 
  *        comparing it to state->u8Str1[state->u16Match1]. If there is a match, it increments the value of state->u16Match1. 
  *        If all characters of str1 have been matched (i.e., if state->u16Match1 == state->u16Str1Len), it transitions 
  *        to state 1 by setting state->state = 1. If there is no match, it resets the value of state->u16Match1 to 0.
  *
  *        If the state machine is in state 1, it checks if the input character matches the next character of the 
  *        u8Str2 string by comparing it to state->str2[state->u16Match2]. If there is a match, it increments the value 
  *        of state->u16Match2. If all characters of str2 have been matched (i.e., if state->u16Match2 == state->u16Str2Len), 
  *        it returns 1 to indicate that the extraction is complete. If there is no match, it appends the input character 
  *        to the result buffer by storing it at position state->u8Result[psState->u16ResultLen] in memory and incrementing state->u16ResultLen. 
  *        It also resets state->u16Match2 to 0.
  *
  *        The function returns 0 if more characters are needed to complete the extraction or 1 if the extraction is complete.

  *        The vExtractFinish function finalizes the extraction process after all characters have been processed. 
  *        It takes a single argument: a pointer to an extractState_t structure. If state->u8State is equal to 1 
  *        (i.e., if <IPAddress> was found in <IPAddress>), it null-terminates state->u8Result[0] by storing a null character 
  *        at position state->u16ResultLen in memory. Otherwise (i.e., if <IPAddress> was not found), it sets state->u8Result[0] 
  *        to ‘\0’ and sets state->u16ResultLen to -1.

  * @example 
  *    #include <stdio.h>
  *    int main() {
  *        sExtractState_t state;
  *        char result[1024];
  *        
  *        vExtractInit(&state, "start", "end", result);
  *        
  *        int c;
  *        while ((c = getchar()) != EOF) {
  *            if (u8ExtractNext(&state, c)) break;
  *        }
  *        
  *        vExtractFinish(&state);
  *        
  *        if (state.result_len >= 0) {
  *            printf("Extracted string: %s\n", result);
  *            printf("Length: %zu\n", state.result_len);
  *        } else {
  *            printf("Extraction failed\n");
  *        }
  *        
  *        return 0;
  *    }
 **/



/**
 * @brief Count the numbe of digit of a given number
 * 
 * @param u32Number The number we want to get the number of digit
 * @return uint32_t The number of digit of the number
 */
uint32_t u32CountDigit(uint32_t u32Number);

/**
 * @brief This function takes an input array of characters and an output array of characters as arguments.
 *        It extracts the first consecutive number from the input array and stores it in the output array.
 * 
 * @param u8Input            The input Array we want to get first consecutive digits from
 * @param u16InputLength     The length of Input array
 * @param u8Output           The array containing extracted number
 * 
 * @return                   The function returns a struct containing the number of extracted digits and
 *                           the index in the input array where the last digit was found.
 */
void vExtractFirstConsNumber(const uint8_t* u8Input, uint16_t u16InputLength, uint8_t* u8Output,  sResult_t* psResult);



/**
 * @brief This function takes a single character as input and an output array of characters as arguments.
 *        If the input character is a digit, it is added to the output array until a non digit character is found.
 * 
 * @param u8Input   The input character we want to see if it is a digit
 * @param u8Output  The array containing extracted digits
 * 
 * @return sResult_t The function returns a struct containing the number of extracted digits and
 *         a flag indicating whether the input character was a digit or not.
 */
void vExtractDigit(const uint8_t u8Input, uint8_t* u8Output, sResult_t* psResult);
/**
 * @brief Initialize an sExtractState_t structure with the provided arguments
 * 
 * @note This function must be first called before calling bExtractNext
 * @note Please see example above
 * 
 * @param psState Define a structure to hold the state of the extraction process
 * @param u8Str1  The first string to search for in the input
 * @param u8Str2  The second string to search for in the input
 * @param u8Result A pointer to the buffer where the resulting string will be stored
 * @param u16ResultSize The size of u8Result buffer
 */
void vExtractInit(sExtractState_t *psState, uint8_t *u8Str1, uint8_t *u8Str2, uint8_t *u8Result, uint16_t u16ResultSize);

/**
 * @brief Process a single character of input and update the state machine accordingly
 * 
 * @note please first call vExtractInit before to call this function
 * 
 * @param psState Define a structure to hold the state of the extraction process
 * @param u8Car     The character to process
 * @return   Return 1 when all the characters have been extracted beetween u8Str1 and u8Str2
 */
uint8_t u8ExtractNext(sExtractState_t *psState, uint8_t u8Car);

/**
 * @brief Finalize the extraction process after all characters have been processed
 * 
 * @param psState Define a structure to hold the state of the extraction process
 */
void vExtractFinish(sExtractState_t *psState);


/**
 * @brief Checks if a part of a character string contains only digits.
 *
 * This function takes a pointer to an array of uint8_t representing the string,
 * as well as two indices start and end to delimit the part of the string to be checked.
 * It checks if all characters in the string between the start and end indices (inclusive) are digits (0 to 9).
 *
 * @param u8Chaine A pointer to an array of uint8_t representing the string to be checked.
 * @param u8Start  The index of the first character to be checked.
 * @param u8End    The index of the last character to be checked.
 * @return         true if all characters in the string between the start and end indices (inclusive) are digits, false otherwise.
 */
bool bIsDigit(uint8_t *u8Chaine, size_t uStart, size_t uEnd) ;



/**
 * @brief Converts a string containing a number to a float.
 *
 * This function takes a string containing a number and extracts the float to convert it from string to float.
 * If the string contains characters other than digits, the function uses a loop to iterate through the string and extract only the characters that represent the float number.
 *
 * @param u8Str The string containing the number to convert.
 * @return The float number extracted from the string.
 */
float fStrToF(uint8_t *u8Str);

/**
 * @brief This function takes a uint8_t string and its length as input and returns a new uint8_t string
 * with colons ':' separating every pair of characters.
 * 
 * @param input     The input uint8_t string.
 * @param output    The output uint8_t string.
 * @param length    The length of the input uint8_t string.
 * @param separator To specify the char to use to separate
 * @return uint8_t* The output uint8_t string with colons separating every pair of characters.
 */
void vAddCol(uint8_t *input, size_t length, char separator, uint8_t *output);


/**
 * @brief 
 * 
 * @param u8Array 
 * @param u8ArrayLen 
 * @param u8Elements 
 * @param u8ElementsLen 
 */
void vReplaceElements(uint8_t *u8Array, uint8_t u8ArrayLen, uint8_t *u8Elements, uint8_t u8ElementsLen) ;

/**
 * @brief This function convert flaot value into uint16_t respecting arrondis rules
 * 
 * @param  fValue   the float input value
 * @return uint16_t 
 */
uint16_t u16Fot16(float fValue);

/**
 * @brief Converts GMT time to local time based on time zone.
 *
 * This function takes as input an array `u8Time` that contains the GMT time as a string,
 * an array `u8ZoneTime` that contains the time zone as a string and updates the array
 * `u8Time` with the local time.
 *
 * @param u8Time Array containing the GMT time as a string.
 * @param u8ZoneTime Array containing the time zone as a string.
 */
void vConvertToZoneTime(uint8_t u8Time[UTIME_SIZE], uint8_t u8ZoneTime[]);

/**
 * @brief Converts a longitude or latitude value from a UART buffer to decimal degrees.
 * 
 * @param u8LonBuffer The buffer containing the longitude/latitude value in the format "0509.1010000".
 * @return The decimal degree value of the longitude.
 */
float fConvertToDegree(uint8_t* u8LonBuffer);

#endif