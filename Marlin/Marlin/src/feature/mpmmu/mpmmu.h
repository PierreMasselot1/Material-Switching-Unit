#pragma once

#include "../../inc/MarlinConfig.h"

class MPMMU{
public:
    MPMMU();
    //add init later
    //add reset later
    //add loop for error manadgment later

    static void tool_change(uint8_t index);
    static void idler_home();
    static bool idler_is_moving();




};
extern MPMMU mpmmu;
