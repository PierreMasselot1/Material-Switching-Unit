#include "../../inc/MarlinConfig.h"
#if ENABLED(MMU_CLONE)

#include "mpmmu.h"
#include "../../MarlinCore.h"
#include "../../gcode/gcode.h"
#include "../../module/planner.h"
#include "../../module/motion.h"
#include "../../module/stepper.h"
#include "../../gcode/parser.h"
#include "../../module/endstops.h"

bool idlerHomed = false;  //idler status
bool homingidler = false; //idler currently homing
float idlerPosition;
float parkedPosition=0;
float offsetEndstopTo1 = 0.3;      //space from the endstop to the first bearing position(Filament 1)
float spaceBetweenBearings = 0.75; //space in between each bearing
float absolutePosition;            //position for the idler to be pressing on the correct filament
float MMUToNozzleLength = BOWDEN_TUBE_LENGTH;      //length, for now the unit is arbitrary but will have to set correct step per mm to get it in mm or scale acordingly

void MPMMU::tool_change(uint8_t index)
{
  if (idlerHomed == false)
  {
    homingidler = true;
    endstops.enable(true);

    planner.buffer_line(0, 0, 0, current_position.e + 1000, 1, MMU_IDLER_PIN); //move towards endstop until it's hit
    planner.synchronize();                                         //wait for the move to finish
    endstops.validate_homing_move();
    homingidler = false;              //homing completed
    idlerPosition = 0;                //new idler position
    planner.position.resetExtruder(); //reset the extruder position to 0 to avoid problems with next move
    endstops.not_homing();

    idlerHomed = true;
  }

  switch (index)
  {
  case 0:
    SERIAL_ECHOPGM("change to filament #1");
    SERIAL_ECHOLNPAIR("change to filament #1");

    //unload filament
    planner.buffer_line(0, 0, 0, -MMUToNozzleLength, 4, MMU_EXTRUDER_PIN);
    #ifdef DIRECT_DRIVE
    planner. buffer_line(0, 0, 0, -MMUToNozzleLength, 4, EXTRUDER_PIN);
    #endif
    planner.synchronize();
    planner.position.resetExtruder();

    //idler select new filament
    absolutePosition = offsetEndstopTo1;
    planner.buffer_line(0, 0, 0, -(absolutePosition - idlerPosition), 2, MMU_IDLER_PIN);
    planner.synchronize();
    planner.position.resetExtruder();

    //reload the new filament
    planner.buffer_line(0, 0, 0, MMUToNozzleLength, 4, MMU_EXTRUDER_PIN);
    #ifdef DIRECT_DRIVE
    planner. buffer_line(0, 0, 0, MMUToNozzleLength, 4, EXTRUDER_PIN);
    #endif
    planner.synchronize();
    planner.position.resetExtruder();
    idlerPosition = absolutePosition;

    //if direct drive is enabled park the idler leting the filament move freely through the MMU
    #ifdef DIRECT_DRIVE
      absolutePosition = parkedPosition;
      planner.buffer_line(0, 0, 0, -(absolutePosition - idlerPosition), 2, MMU_IDLER_PIN);
      planner.synchronize();
      planner.position.resetExtruder();
    #endif

    break;
  case 1:
    SERIAL_ECHOPGM("change to filament #2");
    SERIAL_ECHOLNPAIR("change to filament #2");

    //unload filament
    planner.buffer_line(0, 0, 0, -MMUToNozzleLength, 4, MMU_EXTRUDER_PIN);
    #ifdef DIRECT_DRIVE
    planner. buffer_line(0, 0, 0, -MMUToNozzleLength, 4, EXTRUDER_PIN);
    #endif
    planner.synchronize();
    planner.position.resetExtruder();

    //idler select new filament
    absolutePosition = offsetEndstopTo1 + 1 * spaceBetweenBearings;
    planner.buffer_line(0, 0, 0, -(absolutePosition - idlerPosition), 2, MMU_IDLER_PIN);
    planner.synchronize();
    planner.position.resetExtruder();

    //reload the new filament
    planner.buffer_line(0, 0, 0, MMUToNozzleLength, 4, MMU_EXTRUDER_PIN);
    #ifdef DIRECT_DRIVE
    planner. buffer_line(0, 0, 0, MMUToNozzleLength, 4, EXTRUDER_PIN);
    #endif
    planner.synchronize();
    planner.position.resetExtruder();
    idlerPosition = absolutePosition;

    //if direct drive is enabled park the idler leting the filament move freely through the MMU
    #ifdef DIRECT_DRIVE
      absolutePosition = parkedPosition;
      planner.buffer_line(0, 0, 0, -(absolutePosition - idlerPosition), 2, MMU_IDLER_PIN);
      planner.synchronize();
      planner.position.resetExtruder();
    #endif
    break;
  case 2:
    SERIAL_ECHOPGM("change to filament #3");
    SERIAL_ECHOLNPAIR("change to filament #3");

    //unload filament
    planner.buffer_line(0, 0, 0, -MMUToNozzleLength, 4, MMU_EXTRUDER_PIN);
    #ifdef DIRECT_DRIVE
    planner. buffer_line(0, 0, 0, -MMUToNozzleLength, 4, EXTRUDER_PIN);
    #endif
    planner.synchronize();
    planner.position.resetExtruder();

    //idler select new filament
    absolutePosition = offsetEndstopTo1 + 2 * spaceBetweenBearings;
    planner.buffer_line(0, 0, 0, -(absolutePosition - idlerPosition), 2, MMU_IDLER_PIN);
    planner.synchronize();
    planner.position.resetExtruder();

    //reload the new filament
    planner.buffer_line(0, 0, 0, MMUToNozzleLength, 4, MMU_EXTRUDER_PIN);
    #ifdef DIRECT_DRIVE
    planner. buffer_line(0, 0, 0, MMUToNozzleLength, 4, EXTRUDER_PIN);
    #endif
    planner.synchronize();
    planner.position.resetExtruder();
    idlerPosition = absolutePosition;

    //if direct drive is enabled park the idler leting the filament move freely through the MMU
    #ifdef DIRECT_DRIVE
      absolutePosition = parkedPosition;
      planner.buffer_line(0, 0, 0, -(absolutePosition - idlerPosition), 2, MMU_IDLER_PIN);
      planner.synchronize();
      planner.position.resetExtruder();
    #endif
    break;
  case 3:
    SERIAL_ECHOPGM("change to filament #4");
    SERIAL_ECHOLNPAIR("change to filament #4");

    //unload filament
    planner.buffer_line(0, 0, 0, -MMUToNozzleLength, 4, MMU_EXTRUDER_PIN);
    #ifdef DIRECT_DRIVE
    planner. buffer_line(0, 0, 0, -MMUToNozzleLength, 4, EXTRUDER_PIN);
    #endif
    planner.synchronize();
    planner.position.resetExtruder();

    //idler select new filament
    absolutePosition = offsetEndstopTo1 + 3 * spaceBetweenBearings;
    planner.buffer_line(0, 0, 0, -(absolutePosition - idlerPosition), 2, MMU_IDLER_PIN);
    planner.synchronize();
    planner.position.resetExtruder();

    //reload the new filament
    planner.buffer_line(0, 0, 0, MMUToNozzleLength, 4, MMU_EXTRUDER_PIN);
    #ifdef DIRECT_DRIVE
    planner. buffer_line(0, 0, 0, MMUToNozzleLength, 4, EXTRUDER_PIN);
    #endif
    planner.synchronize();
    planner.position.resetExtruder();
    idlerPosition = absolutePosition;

    //if direct drive is enabled park the idler leting the filament move freely through the MMU
    #ifdef DIRECT_DRIVE
      absolutePosition = parkedPosition;
      planner.buffer_line(0, 0, 0, -(absolutePosition - idlerPosition), 2, MMU_IDLER_PIN);
      planner.synchronize();
      planner.position.resetExtruder();
    #endif
    break;
  case 4:
    SERIAL_ECHOPGM("change to filament #5");
    SERIAL_ECHOLNPAIR("change to filament #5");

    //unload filament
    planner.buffer_line(0, 0, 0, -MMUToNozzleLength, 4, MMU_EXTRUDER_PIN);
    #ifdef DIRECT_DRIVE
    planner. buffer_line(0, 0, 0, -MMUToNozzleLength, 4, EXTRUDER_PIN);
    #endif
    planner.synchronize();
    planner.position.resetExtruder();

    //idler select new filament
    absolutePosition = offsetEndstopTo1 + 4 * spaceBetweenBearings;
    planner.buffer_line(0, 0, 0, -(absolutePosition - idlerPosition), 2, MMU_IDLER_PIN);
    planner.synchronize();
    planner.position.resetExtruder();

    //reload the new filament
    planner.buffer_line(0, 0, 0, MMUToNozzleLength, 4, MMU_EXTRUDER_PIN);
    #ifdef DIRECT_DRIVE
    planner. buffer_line(0, 0, 0, MMUToNozzleLength, 4, EXTRUDER_PIN);
    #endif
    planner.synchronize();
    planner.position.resetExtruder();
    idlerPosition = absolutePosition;

    //if direct drive is enabled park the idler leting the filament move freely through the MMU
    #ifdef DIRECT_DRIVE
      absolutePosition = parkedPosition;
      planner.buffer_line(0, 0, 0, -(absolutePosition - idlerPosition), 2, MMU_IDLER_PIN);
      planner.synchronize();
      planner.position.resetExtruder();
    #endif
    break;
  }
}
bool MPMMU::idler_is_moving()
{
  return homingidler;
}

#endif
