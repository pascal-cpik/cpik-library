/// @file myhardware.h
/// @brief Define global settings
///
/// This file should be included by all hardware-specific source files.
/// The idea is that the individual files remain unchanged ("libraries")
/// while the project-specific tuning is done here.
///
/// @author Pascal Niklaus

#ifndef __MYHARDWARE_H
#define __MYHARDWARE_H

#include <p18f2680.h>
#include <sys/types.h>

/// @name Byte Access
/// @{
///
/// @brief Method to access e.g. low/high byte of a word.
/// I am still searching for the optimal solution
/// @see my_uint16_t
/// @see my_uint32_t



/// @brief Access low byte of a word using pointer casts
/// This creates ok code but is not ideal.
#define LOWBYTE(x) *((uint8_t *)&x)

/// @brief Access high byte of a word using pointer casts
/// This creates ok code but is not ideal.
#define HIGHBYTE(x) *(((uint8_t *)&x)+1)

/// @brief Access low and high byte of a word using a union
/// This creates ideal code but is a bit awkward since it 
/// involves a special type.
/// @see LOWBYTE()
/// @see HIGHBYTE()
typedef union {
  uint16_t word;
  struct {
    uint8_t low;
    uint8_t high;
  };
  struct {
    uint8_t byte0;
    uint8_t byte1;
  };
} my_uint16_t;



/// @brief Access low and high word of a double word using a union.
/// Alternatively, also the individual bytes can be accessed.
/// This creates ideal code but is a bit awkward since it 
/// involves a special type.
typedef union {
  uint32_t dword;
  struct {
    uint16_t word0;
    uint16_t word1;
  };
  struct {
    uint8_t byte0;
    uint8_t byte1;
    uint8_t byte2;
    uint8_t byte3;
  };
} my_uint32_t;


/// @}

/// @brief Define the CPU frequency in MHz
///
/// This define is used to calculate baud rates, delay counters
/// etc in the other modules.
#define CPUFREQ 16

/// @brief Select whether an external crystal is present
///
/// 1=yes, 0=use internal oscillator
#define CRYSTAL 1


//----------------------- LCD -------------------------

/// @name LCD
/// @brief LCD-related defines for Hitachi-like controllers
/// These defines are used in lcd.c
/// @{

/// @brief Set TRIS bit for RW line
#define LCD_RW_SET_TRIS TRISCbits.TRISC1=0

/// @brief Set RW line low (write operation) and at the same
/// time set the TRIS bits for the data lines to output
#define LCD_WRITE { PORTCbits.RC1=0; TRISA &= 0b11000011; }  

/// @brief Set RW line high (read operation) and at the same
/// time set the TRIS bits for the data lines to input
#define LCD_READ  { TRISA |= 0b00111100; PORTCbits.RC1=1;  }  

// RS is on RC1

/// @brief Set TRIS bit for RS (register select) line
#define LCD_RS_SET_TRIS TRISCbits.TRISC3=0

/// @brief Set RS low 
#define LCD_RS0   PORTCbits.RC3=0

/// @brief Set RS high 
#define LCD_RS1   PORTCbits.RC3=1

/// @brief Set TRIS bit for E 
#define LCD_E_SET_TRIS TRISCbits.TRISC0=0
/// @brief Set E low 
#define LCD_E0    PORTCbits.RC0=0
/// @brief Set E high
#define LCD_E1    PORTCbits.RC0=1

/// @brief set data byte @p x (for writing)
#define LCD_SETDATA(x) { PORTA = (PORTA&0b11000011) | ((x&0x0f)*4u); }

/// @brief read data byte 
#define LCD_GETDATA    ((PORTA & 0b00111100)>>2u)

/// @}

#endif
