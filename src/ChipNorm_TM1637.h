// FILE: ChipNorm_TM1637.h
// VERSION: 1.0.0
//
// ChipNorm invests time and resources providing this open code,
// please support ChipNorm by purchasing products from ChipNorm.
//
// Written by Enrique Fernandez for ChipNorm by FMH.
//
// Copyright   Copyright (c) 2025 Enrique Fernandez - ChipNorm by FMH
// See the LICENSE file for details.

#ifndef CHIPNORM_TM1637_H
#define CHIPNORM_TM1637_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


#define A 0b01110111
#define B 0b01111100
#define C 0b00111001
#define D 0b01011110
#define E 0b01111001
#define F 0b01110001
#define G 0b00111101
#define H 0b01110110
#define I 0b00000110
#define J 0b00011110
#define K 0b01110000
#define L 0b00111000
#define M 0b01010100
#define N 0b01010100
#define O 0b00111111
#define P 0b01110011
#define Q 0b01100111
#define R 0b01010000
#define S 0b01101101
#define T 0b01111000
#define U 0b00111110
#define V 0b00011100
#define W 0b00111110
#define Y 0b01101110

#define MINUS 0b01000000
#define BLANK 0b00000000
#define DOT 0b10000000


class ChipNorm_TM1637 {

public:
ChipNorm_TM1637(uint8_t pinClk, uint8_t pinDIO);

void setBrightness(uint8_t brightness, bool on = true);

void clear();


void write_numbers(int8_t d1, int8_t d2, int8_t d3, int8_t d4);

void write_manuell(uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4);

void write_text(uint8_t d1_code, uint8_t d2_code, uint8_t d3_code, uint8_t d4_code);

void dot(bool state);


protected:
void start();
void stop();
bool writeByte(uint8_t b);

void setSegments(const uint8_t segments[], uint8_t length = 4, uint8_t pos = 0);



private:
uint8_t m_pinClk;
uint8_t m_pinDIO;
uint8_t m_brightness;
unsigned int m_bitDelay;
uint8_t m_segments[4] = {0, 0, 0, 0};
bool m_dot_state = false;
};

#endif // __TM1637DISPLAY__