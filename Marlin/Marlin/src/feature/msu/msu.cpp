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
float offsetEndstopTo1 = 3.9;//space from the endstop to the first bearing position(Filament 1)
float spaceBetweenBearings = 3;//space in between each bearing
float servopos1=20;//first bearing position
float servobearingangle=25;//space between each bearings
float parkedPosition = 0; //this is the parked position. when using the servo it will be the parked position in degree
float absolutePosition;  //used to represent the position in mm where the idler aligns with the correct filament
float storeExtruderPosition; //used to store the extruder position before the tool change so that we are able to reset everything.
float bowdenTubeLength = BOWDEN_TUBE_LENGTH;
float nozzleExtruderGearLength = NOZZLE_EXTRUDER_GEAR_LENGTH;

int SelectedFilamentNbr = 0;

bool idlerEngaged = true;//idler engaged or not, this is used in direct drive setup with the MSU disengaging and letting the extruder do everything
bool idlerHomed=false;

bool homingIdler=false;//homing status used in the homing sequence, but will also be useful in order to disable the bug where the idler won't move if the nozzle is cold(prevent cold extrusion feature)
xyze_pos_t position;//we have to create a fake destination(x,y,z) when doing our MSU moves in order to be able to apply motion limits. We then apply the extruder movement we want to that

#if ENABLED(SERVO_IDLER)
  Servo servoidler;//if using a servo, create an instance of the class that will be the used to control the servo
#endif



void MSUMP::tool_change(uint8_t index)
{ 
  
  #ifdef DIRECT_DRIVE
    if(!idlerEngaged)
  {
    #if ENABLED(SERVO_IDLER)
      servoidler.write(servopos1+SelectedFilamentNbr*servobearingangle);
    #else
      absolutePosition = offsetEndstopTo1 + SelectedFilamentNbr * spaceBetweenBearings;
      position.e=-(absolutePosition - idlerPosition);
      planner.buffer_line(position,  5, MSU_IDLER_ENBR);
      planner.synchronize();
      planner.position.resetExtruder();
    #endif
  }
    

  #endif//DIRECT_DRIVE
  if(!idlerHomed)idler_home();
  
  position= current_position;//get the current position of the nozzle, this will be used so that we don't move the axis when performing any moves at the MSU level
  storeExtruderPosition = planner.position.e;//get the extruder position to be able to revert it once the tool change is done
  apply_motion_limits(position);//apply the motion limits (this is what is used when you create an offset for the bed in the X and Y axis to get proper alignement),
  // if not used the nozzle will move to the wrong position at every tool change
  planner.position.resetExtruder(); //reset the extruder position to 0 to avoid problems with next move
  
  //clear the extruder gears
  #ifdef DIRECT_DRIVE
    planner.position.resetExtruder();
    position.e= -nozzleExtruderGearLength-5;//go a bit further just to be sure, it doesn't change anything since the idler is not engaged
    planner.buffer_line(position, 10, ORIGINAL_EXTRUDER_ENBR);
    planner.position.resetExtruder();
    //also move with the MSU(with the idler putting pressure on the right filament) if the extruder and the MSU are controlled independantly since they have different steps per mm
    position.e=-nozzleExtruderGearLength;
    planner.buffer_line(position, 10, MSU_EXTRUDER_ENBR)//two extruder moves at the same time: needs testing
    
  #endif

  //disengage idler and clear the extruder with actual extruder
  #ifdef DIRECT_DRIVE_LINKED_EXTRUDER
    
  //disengage idler if it's engaged  
  if(idlerEngaged)
  {
    #if ENABLED(SERVO_IDLER)
      servoidler.write(parkedPosition);
    #else
      absolutePosition = parkedPosition;
      position.e=-(absolutePosition - idlerPosition);
      planner.buffer_line(position,  5, MSU_IDLER_ENBR);
      planner.synchronize();
      planner.position.resetExtruder();
    #endif
  }
  //clear the extruder gears
  planner.position.resetExtruder();
  position.e= -nozzleExtruderGearLength;
  planner.buffer_line(position, 10, MSU_EXTRUDER_ENBR);
  planner.position.resetExtruder();

  #endif //DIRECT_DRIVE_LINKED_EXTRUDER


  //unload filament until it clears the merger

  position.e= -bowdenTubeLength;
  planner.buffer_line(position,  20, MSU_EXTRUDER_ENBR);
  planner.position.resetExtruder();
  planner.synchronize();
  planner.position.resetExtruder();

  //idler select new filament
  #if ENABLED(SERVO_IDLER)
    servoidler.write(servopos1+index*servobearingangle);
  #else
    absolutePosition = offsetEndstopTo1 + index * spaceBetweenBearings;
    position.e=-(absolutePosition - idlerPosition);
    planner.buffer_line(position,  5, MSU_IDLER_ENBR);
    planner.synchronize();
    planner.position.resetExtruder();
  #endif
  SelectedFilamentNbr = index;

  //reload the new filament up to the nozzle/extruder gear if running a direct drive setup
  position.e=bowdenTubeLength;
  planner.buffer_line(position, 20, MSU_EXTRUDER_ENBR);
  planner.position.resetExtruder();

  #ifdef DIRECT_DRIVE
    //put extra pressure to help the extruder gears grab the filament
    position.e=1;
    planner.buffer_line(position, 10, MSU_EXTRUDER_ENBR)//two extruder moves at the same time: needs testing

    planner.position.resetExtruder();
    position.e= nozzleExtruderGearLength;
    planner.buffer_line(position, 10, ORIGINAL_EXTRUDER_ENBR);
    planner.position.resetExtruder();
    //also move with the MSU(with the idler putting pressure on the right filament) if the extruder and the MSU are controlled independantly since they have different steps per mm
    #ifndef DIRECT_DRIVE_LINKED_EXTRUDER
      position.e=nozzleExtruderGearLength;
      planner.buffer_line(position, 10, MSU_EXTRUDER_ENBR)//two extruder moves at the same time: needs testing
    #endif
  #endif

  #ifdef DIRECT_DRIVE_LINKED_EXTRUDER
    //put extra pressure to help the extruder gears grab the filament, this is a synched move with both the MSU and the actual extruder
    position.e=3;
    planner.buffer_line(position, 10, MSU_EXTRUDER_ENBR)
    planner.position.resetExtruder();
    //disengage idler
    #if ENABLED(SERVO_IDLER)
      servoidler.write(parkedPosition);
    #else
      absolutePosition = parkedPosition;
      position.e=-(absolutePosition - idlerPosition);
      planner.buffer_line(position,  5, MSU_IDLER_ENBR);
      planner.synchronize();
      planner.position.resetExtruder();
    #endif

    idlerEngaged=false;

    //finish loading

    position.e=nozzleExtruderGearLength;
    planner.buffer_line(position, 10, MSU_EXTRUDER_ENBR)//two extruder moves at the same time: needs testing
   
  #endif //DIRECT_DRIVE_LINKED_EXTRUDER
  

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
      planner.buffer_line(position,  5, MSU_IDLER_ENBR);
      planner.synchronize();
      planner.position.resetExtruder();
    #endif

    idlerEngaged=false;

  #endif//DIRECT_DRIVE
}

//homing sequence of the idler. If this is called when using the servo motor it will initiate it

void MSUMP::idler_home()
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
    planner.buffer_line(position, 4, MSU_IDLER_ENBR); //move towards endstop until it's hit
    planner.synchronize();                                                    //wait for the move to finish
    endstops.validate_homing_move();
    homingIdler = false;              //homing completed
    idlerPosition = 0;                //new idler position
    planner.position.resetExtruder(); //reset the extruder position to 0 to avoid problems with next move
    endstops.not_homing();
  #endif
  idlerHomed=true;
  
}

#if ENABLED(SERVO_IDLER)
//servo initiation sequence
void MSUMP::idler_servo_init(){
  servoidler.attach(SERVO_IDLER_PIN);
  servoidler.write(parkedPosition);
}
#endif

//used in the homing process. Used to fix the cold extrusion false trigger when performing idler moves
bool MSUMP::idler_is_homing()
{
  return homingIdler;
}

void MSUMP::edit_bowden_tube_length(const float diff){
  bowdenTubeLength+=diff;
}
void MSUMP::move_msu_extruder(const float diff){
  position.e= -diff;
  planner.buffer_line(position,  20, MSU_EXTRUDER_ENBR);
  planner.position.resetExtruder();
  
}
const float MSUMP::get_bowden_tube_length(){
  return bowdenTubeLength;
}


#endif
