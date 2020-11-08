  // PRUSA MMU2
// idler-body
// GNU GPL v3
// Josef Průša <iam@josefprusa.cz> and contributors
// http://www.reprap.org/wiki/Prusa_Mendel
// http://prusamendel.org

//modified by Pierre Masselot to accomodate for bigger endstops and slot added to fit an endstop for drivers with no sensorless homing.


module motor_screws()
{
    translate([-34,15.5,15.5+1.5-0.4]) rotate([0,90,0]) cylinder(r=1.65, h=10, $fn=50); 
    translate([-24.1,15.5,15.5+1.5-0.4]) rotate([0,90,0]) cylinder(r=3.2+0.8, h=15, $fn=50); 
    translate([-24.1,15.5-3.2-0.8,15.5+1.5-0.4]) cube([15,6.4+1.6,10]);
    translate([-10,15.5-2-2,15.5+1.5-0.4]) rotate([0,-30,0]) cube([20,4+4,10]);


    translate([-34,-15.5,15.5+1.5-0.4]) rotate([0,90,0]) cylinder(r=1.65, h=10, $fn=50); 

    translate([-24.1,-15.5,15.5+1.5-0.4]) rotate([0,90,0]) cylinder(r=3.2+0.8, h=15, $fn=50); 
    translate([-24.1,-15.5-3.2-0.8,15.5+1.5-0.4]) cube([15,6.4+1.6,10]);
    translate([-10,-15.5-2-2,15.5+1.5-0.4]) rotate([0,-30,0]) cube([20,4+4,10]);


    translate([-34,15.5,-15.5+1.5-0.4]) rotate([0,90,0]) cylinder(r=1.65, h=10, $fn=50); 
    translate([-24.1,15.5,-15.5+1.5-0.4]) rotate([0,90,0]) cylinder(r=3.2, h=15, $fn=50); 

    translate([-34,-15.5,-15.5+1.5-0.4]) rotate([0,90,0]) cylinder(r=1.65, h=10, $fn=50); 
    translate([-24.1,-15.5,-15.5+1.5-0.4]) rotate([0,90,0]) cylinder(r=3.2, h=15, $fn=50); 
}


module idler_spring_screws()
{
    
        
        translate([0,-27,-4]) rotate([0,0,0]) cylinder(r=1.7, h=30, $fn=50); 
        translate([0,-27.5,-4]) rotate([0,0,0]) cylinder(r=1.7, h=30, $fn=50); 
        translate([0,-26.5,-4]) rotate([0,0,0]) cylinder(r=1.7, h=30, $fn=50);
        
        translate([-1.7,-27.5,-4.2]) cube([1.7*2,1,10]);
        
        translate([0,-27,9]) rotate([-175,0,0]) cylinder(r=1.7, h=30, $fn=50); 
        translate([0,-27,9]) rotate([-185,0,0]) cylinder(r=1.7, h=30, $fn=50); 
    
        difference()
        {
            union()
            {
            translate([0,-27,5.5]) rotate([0,0,0]) cylinder(r=3.5, h=30, $fn=50); 
            translate([0,-27.5,5.5]) rotate([3,0,0]) cylinder(r=3.5, h=30, $fn=50); 
            translate([0,-26.5,5.5]) rotate([-3,0,0]) cylinder(r=3.5, h=30, $fn=50); 
            }
            translate([-5,-35,-4.5]) cube([10,20,10]);
            translate([-5,-33.6,-4.2]) cube([10,4.4,10]);
            translate([-5,-24.8,-4.2]) cube([10,4.4,10]);
        }
    }


    
module idler_body_base()
{

    difference()
    {
        // body
        union()
        {
            translate([-29,-25,0]) cube([125,50,23+1.5-0.4]);
            translate([-29,-25,-20+1.5-0.4]) cube([10,49,42]);
            translate([70.5,0,0+1.5-0.4]) rotate([0,90,0]) cylinder(r=15, h=10, $fn=50); 
            
            // spring screw mounts
            translate([86,-33,-2]) cube([10,57,25+1.5-0.4]);
            translate([-27,-33,-2]) cube([10,57,25+1.5-0.4]);
            translate([91,-33,-2]) rotate([0,0,0]) cylinder(r=5, h=25+1.5-0.4, $fn=6); 
            translate([-22,-33,-2]) rotate([0,0,0]) cylinder(r=5, h=25+1.5-0.4, $fn=6); 
            //translate([-27,-20,-8]) rotate([20,0,0]) cube([8,10,10]);
            
            // hold together shaft housing
            translate([81,30,-24]) rotate([0,90,0]) cylinder(r=11, h=10, $fn=50); 
            translate([-29,30,-24]) rotate([0,90,0]) cylinder(r=11, h=10, $fn=50); 
            translate([81,21,-24]) cube([10,20,46]); 
            translate([-29,21,-24]) cube([10,20,46]); 

        }

        // shaft
        translate([70,0,0+1.5-0.4]) rotate([0,90,0]) cylinder(r=11.1, h=12, $fn=50); 
        translate([80.5,0,0+1.5-0.4]) rotate([0,90,0]) cylinder(r=3, h=20, $fn=50); 
        translate([81,-3,-10+1.5-0.4]) cube([20,6,10]);
        translate([85,0,-11.5+1.5-0.4]) rotate([45,0,0]) cube([15,10,10]);
        translate([83.5,0,-9+1.5-0.4]) rotate([0,0,0]) cylinder(r=3, h=12, $fn=50); 
        translate([83.5,0,0+1.5-0.4]) rotate([0,0,0]) cylinder(r=1.4, h=12, $fn=50); 
        translate([83.5,0,2+1.5-0.4]) rotate([0,0,0]) cylinder(r2=1.4,r1=1.7, h=3, $fn=50); 
        
        // hold together shafts
        translate([80,30,-24]) rotate([0,90,0]) cylinder(r=2.55, h=12, $fn=50); 
        translate([-30,30,-24]) rotate([0,90,0]) cylinder(r=2.55, h=12, $fn=50); 
        translate([89,30,-24]) rotate([0,90,0]) cylinder(r1=2.55, r2=3, h=3, $fn=50); 
        translate([-30,30,-24]) rotate([0,90,0]) cylinder(r2=2.55, r1=3, h=3, $fn=50); 
        
        translate([80,30,-25.5]) rotate([0,90,0]) cylinder(r=1.5, h=12, $fn=50); 
        translate([-30,30,-25.5]) rotate([0,90,0]) cylinder(r=1.5, h=12, $fn=50); 
                
        translate([80,30,-19]) rotate([0,90,0]) cylinder(r=1.4, h=12, $fn=50); 
        translate([-30,30,-19]) rotate([0,90,0]) cylinder(r=1.4, h=12, $fn=50); 
        translate([89,30,-19]) rotate([0,90,0]) cylinder(r1=1.4, r2=1.8, h=3, $fn=50); 
        translate([-31,30,-19]) rotate([0,90,0]) cylinder(r2=1.4, r1=1.8, h=3, $fn=50); 
        
        
        // idler bearing spaces
        translate([-0.5,0,0+1.5-0.4]) rotate([0,90,0]) cylinder(r=22, h=9, $fn=50); 
        translate([-0.5+14,0,0+1.5-0.4]) rotate([0,90,0]) cylinder(r=22, h=9, $fn=50); 
        translate([-0.5+28,0,0+1.5-0.4]) rotate([0,90,0]) cylinder(r=22, h=9, $fn=50); 
        translate([-0.5+42,0,0+1.5-0.4]) rotate([0,90,0]) cylinder(r=22, h=9, $fn=50); 
        translate([-0.5+56,0,0+1.5-0.4]) rotate([0,90,0]) cylinder(r=22, h=9, $fn=50); 
        
        // idler body space
        translate([-5,0,0+1.5-0.4]) rotate([0,90,0]) cylinder(r=18, h=75.5, $fn=50); 
        translate([-30,0,0+1.5-0.4]) rotate([0,90,0]) cylinder(r=14, h=5, $fn=50); 
        translate([-30,0,-8+1.5-0.4]) rotate([0,90,0]) cylinder(r=4, h=5, $fn=50); 
        
        // motor coupling space
        translate([-26,0,0+1.5-0.4]) rotate([0,90,0]) cylinder(r=18, h=22, $fn=50);
        translate([-24.1-5,-10-1,-30+1.5-0.4]) cube([15,22,20+5]);

        // motor screws
        motor_screws();
        
        // idler tension springs and screws
        translate([-22,-27,-4]) rotate([0,0,0]) cylinder(r=1.7, h=30, $fn=50); 
        translate([91,-27,-4]) rotate([0,0,0]) cylinder(r=1.7, h=30, $fn=50); 
        translate([-22,-27.5,-4]) rotate([0,0,0]) cylinder(r=1.7, h=30, $fn=50); 
        translate([91,-27.5,-4]) rotate([0,0,0]) cylinder(r=1.7, h=30, $fn=50); 
        translate([-22,-26.5,-4]) rotate([0,0,0]) cylinder(r=1.7, h=30, $fn=50); 
        translate([91,-26.5,-4]) rotate([0,0,0]) cylinder(r=1.7, h=30, $fn=50);
        
        translate([-22,-27,6]) rotate([0,0,0]) cylinder(r=3.5+0.5, h=30, $fn=50); 
        translate([-22,-26.5,6.5]) rotate([-3,0,0]) cylinder(r=3.5+0.5, h=30, $fn=50); 
        translate([-22,-27.5,6.5]) rotate([3,0,0]) cylinder(r=3.5+0.5, h=30, $fn=50); 
        
        translate([91,-27,6]) rotate([0,0,0]) cylinder(r=3.5+0.5, h=30, $fn=50); 
        translate([91,-27.5,6.5]) rotate([3,0,0]) cylinder(r=3.5+0.5, h=30, $fn=50); 
        translate([91,-26.5,6.5]) rotate([-3,0,0]) cylinder(r=3.5+0.5, h=30, $fn=50); 
        
        translate([91,0,0]) idler_spring_screws();
        translate([-22,0,0]) idler_spring_screws();
        
        // front edge
        translate([-30,-35,-27]) cube([15,15,25]);
        translate([-30,-24,-35]) rotate([45,0,0]) cube([15,15,15]);
        
        translate([-30,-40,-23]) rotate([45,0,0]) cube([150,15,25]);
        
        // rear edge
        translate([-30,44,-20]) rotate([25,0,0]) cube([130,20,55]);
        translate([105.2,11.5,-20]) rotate([0,0,45]) cube([20,20,55]);
        translate([-19,44,-20]) rotate([25,0,0]) cube([100,20,55]);
        translate([-19,20,-17]) rotate([10,0,0])  cube([100,20,20]);
        
        // easy printing

        
        // endstop mount
       translate([10-1,15.5,3]) cube([4,20,9]);
        
    
        
       
        
        //version
        translate([-5,24.4,7]) rotate([-90,180,0]) linear_extrude(height = 0.8) 
        { text("R1",font = "helvetica:style=Bold", size=5, center=true); }  
    
    }
}



module idler_body()
{
    difference()
    {
        union()
        {
            idler_body_base();
            difference(){
            translate([10-1-2.6+0.40,15.5-1-1.5,3+1.2+5]) cube([6.6+2,20.2+2,20-5-1.3+1.5-0.4]);
            translate([0,10-1.5,0]) cube([100,12,43]);
           }
          
        }
        
            union(){
                translate([10-2.6+0.40,15.5-1.5,3-1]) cube([6.6,20.2,9+25]);
     translate([0,15.5+20.2-5.2-1.5,4+10]) rotate([0,90,0]) cylinder(r=2.7/2, h=50, $fn=50);
                translate ([70.5-1,-20+5,-19]) cube([12,30,15]);
                
                }
    
  
    }
     translate([10-1-2.6+0.40+1,15.5-1-1.5,3+1.2+12.5+1.5-0.4]) cube([6.6,1+1,20-12.5-1.3]);
}


rotate([0,180,0]) 

idler_body();

 


