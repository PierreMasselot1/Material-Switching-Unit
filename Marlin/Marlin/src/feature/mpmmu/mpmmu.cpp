#include "../../inc/MarlinConfig.h"
#if ENABLED(MMU_CLONE)

#include"mpmmu.h"
#include "../../MarlinCore.h"
#include "../../gcode/gcode.h"
#include "../../module/planner.h"
#include "../../module/motion.h"
#include "../../module/stepper.h"
#include "../../gcode/parser.h"
#include "../../module/endstops.h"

boolean idlerHomed=false;//idler status
boolean homingidler=false;//idler currently homing
float idlerPosition;
float offsetEndstopTo1=0.3;//space from the endstop to the first bearing position(Filament 1)
float spaceBetweenBearings=0.65;//space in between each bearing
float absolutePosition;

void MPMMU::tool_change(uint8_t index){
  if(idlerHomed==false){
    homingidler=true;
    endstops.enable(true);
    
    planner.buffer_line(0,0,0,current_position.e+1000,1,1);//move towards endstop until it's hit
    planner.synchronize();//wait for the move to finish
    endstops.validate_homing_move();
    homingidler=false;//homing completed
    idlerPosition=0;//new idler position
    planner.position.resetExtruder();//reset the extruder position to 0 to avoid problems with next move
    endstops.not_homing();
    
    idlerHomed=true;
  }

  switch(index){
    case 0:
       SERIAL_ECHOPGM("change to filament #1" );
       SERIAL_ECHOLNPAIR("change to filament #1" );
       absolutePosition=offsetEndstopTo1;
       planner.buffer_line(0,0,0,-(absolutePosition-idlerPosition),2,1);
       planner.synchronize();
       planner.position.resetExtruder();
       idlerPosition= absolutePosition;
       
       break;
    case 1:
       SERIAL_ECHOPGM("change to filament #2" );
       SERIAL_ECHOLNPAIR("change to filament #2" );
       absolutePosition=offsetEndstopTo1+1*spaceBetweenBearings;
       planner.buffer_line(0,0,0,-(absolutePosition-idlerPosition),2,1);
       planner.synchronize();
       planner.position.resetExtruder();
       idlerPosition= absolutePosition;
       break;
    case 2:
      SERIAL_ECHOPGM("change to filament #3" );
      SERIAL_ECHOLNPAIR("change to filament #3" );
      absolutePosition=offsetEndstopTo1+2*spaceBetweenBearings;
       planner.buffer_line(0,0,0,-(absolutePosition-idlerPosition),2,1);
       planner.synchronize();
       planner.position.resetExtruder();
       idlerPosition= absolutePosition;
      break;
    case 3:
      SERIAL_ECHOPGM("change to filament #4" );
      SERIAL_ECHOLNPAIR("change to filament #4" );
      absolutePosition=3*spaceBetweenBearings;
       planner.buffer_line(0,0,0,-(absolutePosition-idlerPosition),2,1);
       planner.synchronize();
       planner.position.resetExtruder();
       idlerPosition= absolutePosition;
      break;
    case 4:
       SERIAL_ECHOPGM("change to filament #5" );
       SERIAL_ECHOLNPAIR("change to filament #5" );
       absolutePosition=offsetEndstopTo1+4*spaceBetweenBearings;
       planner.buffer_line(0,0,0,-(absolutePosition-idlerPosition),2,1);
       planner.synchronize();
       planner.position.resetExtruder();
       idlerPosition= absolutePosition;
       break;

  }
  
 
}
boolean MPMMU::idler_is_moving(){
  return homingidler;
}

#endif
