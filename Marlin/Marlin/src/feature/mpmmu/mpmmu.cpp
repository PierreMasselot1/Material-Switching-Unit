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
float parkedPosition = 0;
float offsetEndstopTo1 = 1.250;                 //space from the endstop to the first bearing position(Filament 1)
float spaceBetweenBearings =3.12;            //space in between each bearing
float absolutePosition;                       //position for the idler to be pressing on the correct filament
float MMUToNozzleLength = BOWDEN_TUBE_LENGTH; //length, for now the unit is arbitrary but will have to set correct step per mm to get it in mm or scale acordingly
float storeExtruderPosition;
void MPMMU::tool_change(uint8_t index)
{ storeExtruderPosition=planner.position.e;
  if (idlerHomed == false)
  {
    idler_home();
  }
  planner.position.resetExtruder(); //reset the extruder position to 0 to avoid problems with next move
  //unload filament slow
  planner.buffer_line(planner.get_axis_position_mm(X_AXIS), planner.get_axis_position_mm(Y_AXIS), planner.get_axis_position_mm(Z_AXIS), -10, 4, MMU_EXTRUDER_PIN);
#ifdef DIRECT_DRIVE
  planner.buffer_line(0, 0, 0, -10, 4, EXTRUDER_PIN);
#endif
planner.buffer_line(planner.get_axis_position_mm(X_AXIS), planner.get_axis_position_mm(Y_AXIS), planner.get_axis_position_mm(Z_AXIS), -MMUToNozzleLength, 16, MMU_EXTRUDER_PIN);
#ifdef DIRECT_DRIVE
  planner.buffer_line(planner.get_axis_position_mm(X_AXIS), planner.get_axis_position_mm(Y_AXIS), planner.get_axis_position_mm(Z_AXIS),, -MMUToNozzleLength+10, 16, EXTRUDER_PIN);
#endif
  planner.synchronize();
  planner.position.resetExtruder();

  //idler select new filament
  absolutePosition = offsetEndstopTo1 + index * spaceBetweenBearings;
  planner.buffer_line(planner.get_axis_position_mm(X_AXIS), planner.get_axis_position_mm(Y_AXIS), planner.get_axis_position_mm(Z_AXIS), -(absolutePosition - idlerPosition), 2, MMU_IDLER_PIN);
  planner.synchronize();
  planner.position.resetExtruder();

  //reload the new filament slow
  planner.buffer_line(planner.get_axis_position_mm(X_AXIS), planner.get_axis_position_mm(Y_AXIS), planner.get_axis_position_mm(Z_AXIS), 10, 4, MMU_EXTRUDER_PIN);
#ifdef DIRECT_DRIVE
  planner.buffer_line(planner.get_axis_position_mm(X_AXIS), planner.get_axis_position_mm(Y_AXIS), planner.get_axis_position_mm(Z_AXIS), 10, 4, EXTRUDER_PIN);
#endif
//reload the new filament fast
  planner.buffer_line(planner.get_axis_position_mm(X_AXIS), planner.get_axis_position_mm(Y_AXIS), planner.get_axis_position_mm(Z_AXIS), MMUToNozzleLength, 16, MMU_EXTRUDER_PIN);
#ifdef DIRECT_DRIVE
  planner.buffer_line(planner.get_axis_position_mm(X_AXIS), planner.get_axis_position_mm(Y_AXIS), planner.get_axis_position_mm(Z_AXIS), MMUToNozzleLength, 16, EXTRUDER_PIN);
#endif
  planner.synchronize();
  planner.position.resetExtruder();
  idlerPosition = absolutePosition;
  planner.position.e=storeExtruderPosition;
//if direct drive is enabled park the idler leting the filament move freely through the MMU
#ifdef DIRECT_DRIVE
  absolutePosition = parkedPosition;
  planner.buffer_line(0, 0, 0, -(absolutePosition - idlerPosition), 2, MMU_IDLER_PIN);
  planner.synchronize();
  planner.position.resetExtruder();
#endif
}
void MPMMU::idler_home()
{
  homingidler = true;
  endstops.enable(true);

  planner.buffer_line(0, 0, 0, current_position.e + 100, 1, MMU_IDLER_PIN); //move towards endstop until it's hit
  planner.synchronize();                                                     //wait for the move to finish
  endstops.validate_homing_move();
  homingidler = false;              //homing completed
  idlerPosition = 0;                //new idler position
  planner.position.resetExtruder(); //reset the extruder position to 0 to avoid problems with next move
  endstops.not_homing();

  idlerHomed = true;
}
bool MPMMU::idler_is_moving()
{
  return homingidler;
}

#endif
