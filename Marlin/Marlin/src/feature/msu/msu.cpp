#include "../../inc/MarlinConfig.h"

#if ENABLED(MSU)

#include "msu.h"
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

float idlerPosition; //stores the idler position in mm
float offsetEndstopTo1 = 1.248;//space from the endstop to the first bearing position(Filament 1)
float spaceBetweenBearings = 3.12;//space in between each bearing
float servopos1=20;//first bearing position
float servobearingangle=25;//space between each bearings
float parkedPosition = 0; //this is the parked position. when using the servo it will be the parked position in degree
float absolutePosition;  //used to represent the position in mm where the idler aligns with the correct filament
float storeExtruderPosition; //used to store the extruder position before the tool change so that we are able to reset everything.

bool homingIdler=false;//homing status used in the homing sequence, but will also be useful in order to disable the bug where the idler won't move if the nozzle is cold(prevent cold extrusion feature)
xyze_pos_t position;//we have to create a fake destination(x,y,z) when doing our MSU moves in order to be able to apply motion limits. We then apply the extruder movement we want to that

#if ENABLED(SERVO_IDLER)
  Servo servoidler;//if using a servo, create an instance of the class that will be the used to control the servo
  bool servoinit=false; // boolean to check whether the servo has already been initiated.
#endif



void MSUMPMP::tool_change(uint8_t index)
{
  #if ENABLED(SERVO_IDLER)
    //if the servo hasn't been initiated before the tool change make sure to initiate it and update the init state of the servo
    if(!servoinit)
    idler_servo_init();
    servoinit=true;
  #endif

  position= current_position;//get the current position of the nozzle, this will be used so that we don't move the axis when performing any moves at the MSU level
  storeExtruderPosition = planner.position.e;//get the extruder position to be able to revert it once the tool change is done
  apply_motion_limits(position);//apply the motion limits (this is what is used when you create an offset for the bed in the X and Y axis to get proper alignement),
  // if not used the nozzle will move to the wrong position at every tool change
  planner.position.resetExtruder(); //reset the extruder position to 0 to avoid problems with next move
  
  //unload filament slow
  position.e= -10;
  planner.buffer_line(position, 4, MSU_EXTRUDER_PIN);
#ifdef DIRECT_DRIVE
  planner.position.resetExtruder();
  position.e= -10;
  planner.buffer_line(position, 4, EXTRUDER_PIN);
#endif
  //unload filament fast
  position.e= -BOWDEN_TUBE_LENGTH;
  planner.buffer_line(position,  16, MSU_EXTRUDER_PIN);
  planner.position.resetExtruder();
  
#ifdef DIRECT_DRIVE
  position.e= -BOWDEN_TUBE_LENGTH;
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
  planner.buffer_line(position,  2, MSU_IDLER_PIN);
  planner.synchronize();
  planner.position.resetExtruder();
  #endif

  //reload the new filament slow
  position.e=10;
  planner.buffer_line(position, 4, MSU_EXTRUDER_PIN);
  planner.position.resetExtruder();
#ifdef DIRECT_DRIVE
  position.e=10;
  planner.buffer_line(position, 10, 4, EXTRUDER_PIN);
  planner.position.resetExtruder();
#endif
  //reload the new filament fast
  position.e=BOWDEN_TUBE_LENGTH;
  planner.buffer_line(position, 16, MSU_EXTRUDER_PIN);
  planner.position.resetExtruder();
#ifdef DIRECT_DRIVE
  position.e=BOWDEN_TUBE_LENGTH;
  planner.buffer_line(position, 16, EXTRUDER_PIN);
  planner.position.resetExtruder();
#endif
//reset all the positions to their original state
  planner.synchronize();//wait for all the moves to finish
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
  planner.buffer_line(position,  2, MSU_IDLER_PIN);
  planner.synchronize();
  planner.position.resetExtruder();
#endif

#endif
}

//homing sequence of the idler. If this is called when using the servo motor it will initiate it
void MSU::idler_home()
{
#if ENABLED(SERVO_IDLER)
  msu.idler_servo_init();
#else
  homingIdler = true;
  endstops.enable(true);
  position= current_position;
  //apply_motion_limits(position);
  planner.position.resetExtruder();
  position.e= 100;
  planner.buffer_line(position, 1, MSU_IDLER_PIN); //move towards endstop until it's hit
  planner.synchronize();                                                    //wait for the move to finish
  endstops.validate_homing_move();
  homingIdler = false;              //homing completed
  idlerPosition = 0;                //new idler position
  planner.position.resetExtruder(); //reset the extruder position to 0 to avoid problems with next move
  endstops.not_homing();
#endif
  
}
#if ENABLED(SERVO_IDLER)

//servo initiation sequence
void MSU::idler_servo_init(){
  servoidler.attach(SERVO_IDLER_PIN);
  servoidler.write(parkedPosition);
}
#endif

//used in the homing process. Will be used to fix the cold extrusion related bug when moving the idler
bool MSU::idler_is_moving()
{
  return homingIdler;
}

#endif
