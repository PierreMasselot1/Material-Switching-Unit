#pragma once

#include "../../inc/MarlinConfig.h"

class MSUMP{
public:
    MSUMP();
    //add init later
    //add reset later
    //add loop for error manadgment later
    static void idler_servo_init();
    static void tool_change(uint8_t index);
    static void idler_home();
    static bool idler_is_moving();




};
extern MSUMP msu;
