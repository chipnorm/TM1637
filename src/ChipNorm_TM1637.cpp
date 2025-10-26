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

extern "C" {
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
}

#include <ChipNorm_TM1637.h>
#include <Arduino.h>

#define TM1637_I2C_COMM1 0x40
#define TM1637_I2C_COMM2 0xC0
#define TM1637_I2C_COMM3 0x80
#define DEFAULT_BIT_DELAY 100


//
//      A
//     ---
//  F |   | B
//     -G-
//  E |   | C
//     ---
//      D


const uint8_t digitToSegment[] = {
0b00111111,    // 0
0b00000110,    // 1
0b01011011,    // 2
0b01001111,    // 3
0b01100110,    // 4
0b01101101,    // 5
0b01111101,    // 6
0b00000111,    // 7
0b01111111,    // 8
0b01101111,    // 9
};


static const uint8_t minusSegments = 0b01000000;



ChipNorm_TM1637::ChipNorm_TM1637(uint8_t pinClk, uint8_t pinDIO)
{
m_pinClk = pinClk;
m_pinDIO = pinDIO;

pinMode(m_pinClk, INPUT);
pinMode(m_pinDIO, INPUT);
digitalWrite(m_pinClk, LOW);
digitalWrite(m_pinDIO, LOW);

clear();
}



void ChipNorm_TM1637::setBrightness(uint8_t brightness, bool on)
{
m_brightness = (brightness & 0x7) | (on? 0x08 : 0x00);
}



void ChipNorm_TM1637::setSegments(const uint8_t segments[], uint8_t length, uint8_t pos)
{
start();
writeByte(TM1637_I2C_COMM1);
stop();

start();
writeByte(TM1637_I2C_COMM2 + 0x00);

for (uint8_t k = 0; k < 4; k++) {
if (k == 1 && m_dot_state) {
writeByte(m_segments[k] | 0x80);
} else {
writeByte(m_segments[k] & 0x7F);
}
}
stop();

start();
writeByte(TM1637_I2C_COMM3 + (m_brightness & 0x0f));
stop();
}



void ChipNorm_TM1637::clear()
{
memset(m_segments, 0, 4);
m_dot_state = false;
setSegments(m_segments, 4, 0);
}



uint8_t digitToSegmentCode(int8_t digit) {
	if (digit >= 0 && digit <= 9) {
		return digitToSegment[digit];
	} else {
		return 0x00;
	}
}



//#############################
// Direkte Hauptfunktionen
//#############################

void ChipNorm_TM1637::write_numbers(int8_t d1, int8_t d2, int8_t d3, int8_t d4)
{
m_segments[0] = digitToSegmentCode(d1);
m_segments[1] = digitToSegmentCode(d2);
m_segments[2] = digitToSegmentCode(d3);
m_segments[3] = digitToSegmentCode(d4);
setSegments(m_segments, 4, 0);
}


void ChipNorm_TM1637::dot(bool state)
{
m_dot_state = state;
setSegments(m_segments, 4, 0);
}


void ChipNorm_TM1637::write_text(uint8_t d1_code, uint8_t d2_code, uint8_t d3_code, uint8_t d4_code)
{
write_manuell(d1_code, d2_code, d3_code, d4_code);
}




void ChipNorm_TM1637::write_manuell(uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4)
{
m_segments[0] = d1;
m_segments[1] = d2;
m_segments[2] = d3;
m_segments[3] = d4;
setSegments(m_segments, 4, 0);
}




//#############################
//Hilfsfunktion
//#############################


void ChipNorm_TM1637::start()
{
pinMode(m_pinDIO, OUTPUT);
delayMicroseconds(100);
}


void ChipNorm_TM1637::stop()
{
pinMode(m_pinDIO, OUTPUT);
delayMicroseconds(100);
pinMode(m_pinClk, INPUT);
delayMicroseconds(100);
pinMode(m_pinDIO, INPUT);
delayMicroseconds(100);
}


bool ChipNorm_TM1637::writeByte(uint8_t b)

{
uint8_t data = b;
 for(uint8_t i = 0; i < 8; i++) {
    pinMode(m_pinClk, OUTPUT);
    delayMicroseconds(100);

    if (data & 0x01)
       pinMode(m_pinDIO, INPUT);
    else
       pinMode(m_pinDIO, OUTPUT);

    delayMicroseconds(100);


    pinMode(m_pinClk, INPUT);
    delayMicroseconds(100);
    data = data >> 1;
  }


pinMode(m_pinClk, OUTPUT);
pinMode(m_pinDIO, INPUT);
delayMicroseconds(100);

pinMode(m_pinClk, INPUT);
delayMicroseconds(100);
uint8_t ack = digitalRead(m_pinDIO);
if (ack == 0)
	pinMode(m_pinDIO, OUTPUT);
delayMicroseconds(100);
pinMode(m_pinClk, OUTPUT);
delayMicroseconds(100);
return ack;
}