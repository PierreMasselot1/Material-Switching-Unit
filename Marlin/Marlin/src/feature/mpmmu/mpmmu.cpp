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


float idlerPosition;

float offsetEndstopTo1 = 0.3 * 4.16;          //space from the endstop to the first bearing position(Filament 1)
bool homingIdler=false;
float spaceBetweenBearings = 0.75 * 4.16;     //space in between each bearing
float parkedPosition = 0;
float absolutePosition;                       //position for the idler to be pressing on the correct filament
float MMUToNozzleLength = BOWDEN_TUBE_LENGTH; //length, for now the unit is arbitrary but will have to set correct step per mm to get it in mm or scale acordingly
float storeExtruderPosition;
xyz_pos_t position= xyz_pos_t(current_position);

void MPMMU::tool_change(uint8_t index)
{ position= xyz_pos_t(current_position);
  apply_motion_limits(position);
  storeExtruderPosition = planner.position.e;
  planner.position.resetExtruder(); //reset the extruder position to 0 to avoid problems with next move
  //unload filament slow
  planner.buffer_line(position, -10, 4, MMU_EXTRUDER_PIN);
#ifdef DIRECT_DRIVE
  planner.buffer_line(0, 0, 0, -10, 4, EXTRUDER_PIN);
#endif
  planner.buffer_line(position, -MMUToNozzleLength, 16, MMU_EXTRUDER_PIN);
#ifdef DIRECT_DRIVE
  planner.buffer_line(position , -MMUToNozzleLength + 10, 16, EXTRUDER_PIN);
#endif
  planner.synchronize();
  planner.position.resetExtruder();

  //idler select new filament
  absolutePosition = offsetEndstopTo1 + index * spaceBetweenBearings;
  planner.buffer_line(position, -(absolutePosition - idlerPosition), 2, MMU_IDLER_PIN);
  planner.synchronize();
  planner.position.resetExtruder();

  //reload the new filament slow
  planner.buffer_line(position, 10, 4, MMU_EXTRUDER_PIN);
#ifdef DIRECT_DRIVE
  planner.buffer_line(position, 10, 4, EXTRUDER_PIN);
#endif
  //reload the new filament fast
  planner.buffer_line(position, MMUToNozzleLength, 16, MMU_EXTRUDER_PIN);
#ifdef DIRECT_DRIVE
  planner.buffer_line(position, MMUToNozzleLength, 16, EXTRUDER_PIN);
#endif
  planner.synchronize();
  planner.position.resetExtruder();
  idlerPosition = absolutePosition;
  planner.position.e = storeExtruderPosition;
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
  homingIdler = true;
  endstops.enable(true);
  position= xyz_pos_t(current_position);
  apply_motion_limits(position);

  planner.buffer_line(position, current_position.e + 100, 1, MMU_IDLER_PIN); //move towards endstop until it's hit
  planner.synchronize();                                                    //wait for the move to finish
  endstops.validate_homing_move();
  homingIdler = false;              //homing completed
  idlerPosition = 0;                //new idler position
  planner.position.resetExtruder(); //reset the extruder position to 0 to avoid problems with next move
  endstops.not_homing();

  
}
bool MPMMU::idler_is_moving()
{
  return homingIdler;
}

#endif
