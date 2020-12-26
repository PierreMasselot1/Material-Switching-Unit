/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include "rotary_encoder.h"
#include "../MarlinCore.h"
#if ENABLED(ROTARY_ENCODER)
bool enabled;
float distance=0;
int Pin1State=0;
int Pin2State=0;
int Pin1PrevState=0;
int Pin2PrevState=0;

RotaryEncoder rotaryencoder;
void RotaryEncoder::init(){
    SET_INPUT(ROTARY_ENCODER_PIN1);
    SET_INPUT(ROTARY_ENCODER_PIN2);
    Pin1PrevState=READ(ROTARY_ENCODER_PIN1);
    Pin2PrevState=READ(ROTARY_ENCODER_PIN2);
}
void RotaryEncoder::enable(const bool onoff){
 enabled=onoff;
}
void RotaryEncoder::poll(){
 Pin1State=READ(ROTARY_ENCODER_PIN1);
 if(Pin1State!=Pin1PrevState){
     //pulse occured
     
 }
}
#endif