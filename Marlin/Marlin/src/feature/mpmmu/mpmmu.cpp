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
#if ENABLED(SERVO_IDLER)
  #include "../../module/servo.h"
#endif

float idlerPosition;
float offsetEndstopTo1 = 0.3 * 4.16;          //space from the endstop to the first bearing position(Filament 1)
float servopos1=20;//first bearing position
float servobearingangle=25;//space between each bearings
bool homingIdler=false;
float spaceBetweenBearings = 0.75 * 4.16;     //space in between each bearing
float parkedPosition = 0; //this is the parked position. when using the servo it will be the parked position in degree
float absolutePosition;                       //position for the idler to be pressing on the correct filament
float MMUToNozzleLength = BOWDEN_TUBE_LENGTH; //length, for now the unit is arbitrary but will have to set correct step per mm to get it in mm or scale acordingly
float storeExtruderPosition;
xyze_pos_t position;
#if ENABLED(SERVO_IDLER)
  Servo servoidler;
#endif
bool servoinit=false;

void MPMMU::tool_change(uint8_t index)
{
  #if ENABLED(SERVO_IDLER)
  if(!servoinit)
  idler_servo_init();
  servoinit=true;
  #endif
  position= current_position;
  storeExtruderPosition = planner.position.e;
  apply_motion_limits(position);
  planner.position.resetExtruder(); //reset the extruder position to 0 to avoid problems with next move
  //unload filament slow
  position.e= -10;
  planner.buffer_line(position, 4, MMU_EXTRUDER_PIN);
#ifdef DIRECT_DRIVE
  planner.position.resetExtruder();
  position.e= -10;
  planner.buffer_line(position, 4, EXTRUDER_PIN);
#endif
 
  position.e= -MMUToNozzleLength;
  planner.buffer_line(position,  16, MMU_EXTRUDER_PIN);
  planner.position.resetExtruder();
  
#ifdef DIRECT_DRIVE
  position.e= -MMUToNozzleLength;
  planner.buffer_line(position , 16, EXTRUDER_PIN);
#endif
  planner.synchronize();
  planner.position.resetExtruder();

  //idler select new filament
  #if ENABLED(SERVO_IDLER)
  servoidler.write(servopos1+index*servobearingangle);
  #else
  absolutePosition = offsetEndstopTo1 + index * spaceBetweenBearings;
  position.e=-(absolutePosition - idlerPosition);
  planner.buffer_line(position,  2, MMU_IDLER_PIN);
  planner.synchronize();
  planner.position.resetExtruder();
  #endif

  //reload the new filament slow
  position.e=10;
  planner.buffer_line(position, 4, MMU_EXTRUDER_PIN);
  planner.position.resetExtruder();
#ifdef DIRECT_DRIVE
  position.e=10;
  planner.buffer_line(position, 10, 4, EXTRUDER_PIN);
  planner.position.resetExtruder();
#endif
  //reload the new filament fast
  position.e=MMUToNozzleLength;
  planner.buffer_line(position, 16, MMU_EXTRUDER_PIN);
  planner.position.resetExtruder();
#ifdef DIRECT_DRIVE
  position.e=MMUToNozzleLength;
  planner.buffer_line(position, 16, EXTRUDER_PIN);
  planner.position.resetExtruder();
#endif
  planner.synchronize();
  planner.position.resetExtruder();
  idlerPosition = absolutePosition;
  planner.position.e = storeExtruderPosition;
//if direct drive is enabled park the idler leting the filament move freely through the MMU
#ifdef DIRECT_DRIVE
#if ENABLED(SERVO_IDLER)
  servoidler.write(parkedPosition);
#else
  absolutePosition = parkedPosition;
  position.e=-(absolutePosition - idlerPosition);
  planner.buffer_line(position,  2, MMU_IDLER_PIN);
  planner.synchronize();
  planner.position.resetExtruder();
#endif
#endif
}

void MPMMU::idler_home()
{
#if ENABLED(SERVO_IDLER)
  mpmmu.idler_servo_init();
#else
  homingIdler = true;
  endstops.enable(true);
  position= current_position;
  //apply_motion_limits(position);
  planner.position.resetExtruder();
  position.e= 100;
  planner.buffer_line(position, 1, MMU_IDLER_PIN); //move towards endstop until it's hit
  planner.synchronize();                                                    //wait for the move to finish
  endstops.validate_homing_move();
  homingIdler = false;              //homing completed
  idlerPosition = 0;                //new idler position
  planner.position.resetExtruder(); //reset the extruder position to 0 to avoid problems with next move
  endstops.not_homing();
#endif
  
}
#if ENABLED(SERVO_IDLER)
void MPMMU::idler_servo_init(){
  servoidler.attach(SERVO_IDLER_PIN);
  servoidler.write(parkedPosition);
}
#endif
bool MPMMU::idler_is_moving()
{
  return homingIdler;
}

#endif
