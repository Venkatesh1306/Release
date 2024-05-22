    /*******************************************************************

                  Generic Type Definitions

********************************************************************
 FileName:        GenericTypeDefs.h
 Dependencies:    None
 Processor:       PIC10, PIC12, PIC16, PIC18, PIC24, dsPIC, PIC32
 Compiler:        MPLAB C Compilers for PIC18, PIC24, dsPIC, & PIC32
                  Hi-Tech PICC PRO, Hi-Tech PICC18 PRO
 Company:         Microchip Technology Inc.

 Software License Agreement

 The software supplied herewith by Microchip Technology Incorporated
 (the "Company") is intended and supplied to you, the Company's
 customer, for use solely and exclusively with products manufactured
 by the Company.

 The software is owned by the Company and/or its supplier, and is
 protected under applicable copyright laws. All rights are reserved.
 Any use in violation of the foregoing restrictions may subject the
 user to criminal sanctions under applicable laws, as well as to
 civil liability for the breach of the terms and conditions of this
 license.

 THIS SOFTWARE IS PROVIDED IN AN "AS IS" CONDITION. NO WARRANTIES,
 WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

********************************************************************
 File Description:

 Change History:
  Rev   Date         Description
  1.1   09/11/06     Add base signed types
  1.2   02/28/07     Add uint64_t, LONGLONG, uint64_t_VAL
  1.3   02/06/08     Add def's for PIC32
  1.4   08/08/08     Remove LSB/MSB Macros, adopted by Peripheral lib
  1.5   08/14/08     Simplify file header
  2.0   07/13/09     Updated for new release of coding standards
*******************************************************************/

#ifndef __MODHEAD_H_
#define __MODHEAD_H_

/* Specify an extension for GCC based compilers */
#if defined(__GNUC__)
#define __EXTENSION __extension__
#else
#define __EXTENSION
#endif

#if !defined(__PACKED)
    #define __PACKED
#endif


/***********************************************************************************/

/* Alternate definitions */
typedef void                    VOID;

typedef char                    char8_t;
typedef unsigned char           uchar8_t;

typedef unsigned char           uint8_t;                           /* 8-bit unsigned  */
typedef unsigned short int      uint16_t;                           /* 16-bit unsigned */
typedef unsigned long           uint32_t;                          /* 32-bit unsigned */
/* MPLAB C Compiler for PIC18 does not support 64-bit integers */
__EXTENSION
typedef unsigned long long      uint64_t;                          /* 64-bit unsigned */
typedef signed char             char_t;                           /* 8-bit signed    */
typedef signed short int        short_t;                          /* 16-bit signed   */
typedef signed long             long_t;                           /* 32-bit signed   */
/* MPLAB C Compiler for PIC18 does not support 64-bit integers */
__EXTENSION
typedef signed long long        long_long_t;                       /* 64-bit signed   */
typedef union
{
    uint8_t Val;
    struct __PACKED
    {
        __EXTENSION uint8_t b0:1;
        __EXTENSION uint8_t b1:1;
        __EXTENSION uint8_t b2:1;
        __EXTENSION uint8_t b3:1;
        __EXTENSION uint8_t b4:1;
        __EXTENSION uint8_t b5:1;
        __EXTENSION uint8_t b6:1;
        __EXTENSION uint8_t b7:1;
    } bits;
} uint8_t_VAL, uint8_t_BITS;

typedef union
{
    uint16_t Val;
    uint8_t v[2] __PACKED;
    struct __PACKED
    {
        uint8_t LB;
        uint8_t HB;
    } bytes;
    struct __PACKED
    {
        __EXTENSION uint8_t b0:1;
        __EXTENSION uint8_t b1:1;
        __EXTENSION uint8_t b2:1;
        __EXTENSION uint8_t b3:1;
        __EXTENSION uint8_t b4:1;
        __EXTENSION uint8_t b5:1;
        __EXTENSION uint8_t b6:1;
        __EXTENSION uint8_t b7:1;
        __EXTENSION uint8_t b8:1;
        __EXTENSION uint8_t b9:1;
        __EXTENSION uint8_t b10:1;
        __EXTENSION uint8_t b11:1;
        __EXTENSION uint8_t b12:1;
        __EXTENSION uint8_t b13:1;
        __EXTENSION uint8_t b14:1;
        __EXTENSION uint8_t b15:1;
    } bits;
} uint16_t_VAL, uint16_t_BITS;

typedef union
{
    uint32_t Val;
    uint16_t w[2] __PACKED;
    uint8_t v[4] __PACKED;
    struct __PACKED
    {
        uint16_t LW;
        uint16_t HW;
    } word;
    struct __PACKED
    {
        uint8_t LB;
        uint8_t HB;
        uint8_t UB;
        uint8_t MB;
    } bytes;
    struct __PACKED
    {
        uint16_t_VAL low;
        uint16_t_VAL high;
    }wordUnion;
    struct __PACKED
    {
        __EXTENSION uint8_t b0:1;
        __EXTENSION uint8_t b1:1;
        __EXTENSION uint8_t b2:1;
        __EXTENSION uint8_t b3:1;
        __EXTENSION uint8_t b4:1;
        __EXTENSION uint8_t b5:1;
        __EXTENSION uint8_t b6:1;
        __EXTENSION uint8_t b7:1;
        __EXTENSION uint8_t b8:1;
        __EXTENSION uint8_t b9:1;
        __EXTENSION uint8_t b10:1;
        __EXTENSION uint8_t b11:1;
        __EXTENSION uint8_t b12:1;
        __EXTENSION uint8_t b13:1;
        __EXTENSION uint8_t b14:1;
        __EXTENSION uint8_t b15:1;
        __EXTENSION uint8_t b16:1;
        __EXTENSION uint8_t b17:1;
        __EXTENSION uint8_t b18:1;
        __EXTENSION uint8_t b19:1;
        __EXTENSION uint8_t b20:1;
        __EXTENSION uint8_t b21:1;
        __EXTENSION uint8_t b22:1;
        __EXTENSION uint8_t b23:1;
        __EXTENSION uint8_t b24:1;
        __EXTENSION uint8_t b25:1;
        __EXTENSION uint8_t b26:1;
        __EXTENSION uint8_t b27:1;
        __EXTENSION uint8_t b28:1;
        __EXTENSION uint8_t b29:1;
        __EXTENSION uint8_t b30:1;
        __EXTENSION uint8_t b31:1;
    } bits;
} uint32_t_VAL;

/* MPLAB C Compiler for PIC18 does not support 64-bit integers */
typedef union
{
    uint64_t Val;
    uint32_t d[2] __PACKED;
    uint16_t w[4] __PACKED;
    uint8_t v[8] __PACKED;
    struct __PACKED
    {
        uint32_t LD;
        uint32_t HD;
    } dword;
    struct __PACKED
    {
        uint16_t LW;
        uint16_t HW;
        uint16_t UW;
        uint16_t MW;
    } word;
    struct __PACKED
    {
        __EXTENSION uint8_t b0:1;
        __EXTENSION uint8_t b1:1;
        __EXTENSION uint8_t b2:1;
        __EXTENSION uint8_t b3:1;
        __EXTENSION uint8_t b4:1;
        __EXTENSION uint8_t b5:1;
        __EXTENSION uint8_t b6:1;
        __EXTENSION uint8_t b7:1;
        __EXTENSION uint8_t b8:1;
        __EXTENSION uint8_t b9:1;
        __EXTENSION uint8_t b10:1;
        __EXTENSION uint8_t b11:1;
        __EXTENSION uint8_t b12:1;
        __EXTENSION uint8_t b13:1;
        __EXTENSION uint8_t b14:1;
        __EXTENSION uint8_t b15:1;
        __EXTENSION uint8_t b16:1;
        __EXTENSION uint8_t b17:1;
        __EXTENSION uint8_t b18:1;
        __EXTENSION uint8_t b19:1;
        __EXTENSION uint8_t b20:1;
        __EXTENSION uint8_t b21:1;
        __EXTENSION uint8_t b22:1;
        __EXTENSION uint8_t b23:1;
        __EXTENSION uint8_t b24:1;
        __EXTENSION uint8_t b25:1;
        __EXTENSION uint8_t b26:1;
        __EXTENSION uint8_t b27:1;
        __EXTENSION uint8_t b28:1;
        __EXTENSION uint8_t b29:1;
        __EXTENSION uint8_t b30:1;
        __EXTENSION uint8_t b31:1;
        __EXTENSION uint8_t b32:1;
        __EXTENSION uint8_t b33:1;
        __EXTENSION uint8_t b34:1;
        __EXTENSION uint8_t b35:1;
        __EXTENSION uint8_t b36:1;
        __EXTENSION uint8_t b37:1;
        __EXTENSION uint8_t b38:1;
        __EXTENSION uint8_t b39:1;
        __EXTENSION uint8_t b40:1;
        __EXTENSION uint8_t b41:1;
        __EXTENSION uint8_t b42:1;
        __EXTENSION uint8_t b43:1;
        __EXTENSION uint8_t b44:1;
        __EXTENSION uint8_t b45:1;
        __EXTENSION uint8_t b46:1;
        __EXTENSION uint8_t b47:1;
        __EXTENSION uint8_t b48:1;
        __EXTENSION uint8_t b49:1;
        __EXTENSION uint8_t b50:1;
        __EXTENSION uint8_t b51:1;
        __EXTENSION uint8_t b52:1;
        __EXTENSION uint8_t b53:1;
        __EXTENSION uint8_t b54:1;
        __EXTENSION uint8_t b55:1;
        __EXTENSION uint8_t b56:1;
        __EXTENSION uint8_t b57:1;
        __EXTENSION uint8_t b58:1;
        __EXTENSION uint8_t b59:1;
        __EXTENSION uint8_t b60:1;
        __EXTENSION uint8_t b61:1;
        __EXTENSION uint8_t b62:1;
        __EXTENSION uint8_t b63:1;
    } bits;
} uint64_t_VAL;

#undef __EXTENSION

#endif /* __MODHEAD_H_*/
