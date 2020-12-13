
// PRUSA MMU2
// idler
// GNU GPL v3
// Josef Průša <iam@josefprusa.cz> and contributors
// http://www.reprap.org/wiki/Prusa_Mendel
// http://prusamendel.org

//modified by Pierre Masselot
//fits 608 bearings and embeds the bearings inside the print to avoid any assembly

module idler_segment_l()
{difference(){
    translate([0,0,-9]) rotate([0,90,0]) cylinder(r=11.5, h=8, $fn=50); 
    translate([0,0,-9]) rotate([0,90,0]) cylinder(r=3.95, h=100, $fn=50); }

}
    
module idler_segment_r()
{difference(){
    translate([0,0,-9]) rotate([0,90,0]) cylinder(r=11.5, h=8, $fn=50); 
    translate([0,0,-9]) rotate([0,90,0]) cylinder(r=3.95, h=60, $fn=50); }
 
}

module idler_segment_support(){
     
    {
    translate([8-0.2,0,-9]) rotate([0,90,0]) cylinder(r=11.5+0.8, h=0.4, $fn=50);
    translate([0-0.2,0,-9]) rotate([0,90,0]) cylinder(r=11.5+0.8, h=0.4, $fn=50); 
    difference(){  
     translate([-0.2,0,-9]) rotate([0,90,0]) cylinder(r=11.5+0.8, h=8.4, $fn=50); 
    translate([-0.2,0,-9]) rotate([0,90,0]) cylinder(r=11.5, h=8.4, $fn=50);
        }   }}



module idler()
{

    difference()
    {

    union()
        {
            // base body
            translate([-3,0,0]) rotate([0,90,0]) cylinder(r=17, h=71-2, $fn=50); 
            translate([-5,0,0]) rotate([0,90,0]) cylinder(r2=17,r1=16, h=2, $fn=50); 
            translate([68-2,0,0]) rotate([0,90,0]) cylinder(r1=17, r2=16, h=2, $fn=50); 
            
            // motor shaft coupling
            rotate([-60,0,0]) 
            difference()
            {
                union()
                {
                    translate([-25,0,0]) rotate([0,90,0]) cylinder(r=9, h=20, $fn=50); 
                    translate([-25,-6,5]) cube([20,12,9]);
                    translate([-25,-5,-5]) rotate([60,0,0]) cube([20,16,10]);
                }
                // screws
                translate([-10,0,0]) cylinder(r=1.6, h=12.5, $fn=50); 
                translate([-10,0,4]) cylinder(r=2, h=6.5, $fn=50); 
                translate([-10,0,10.4]) cylinder(r=3.1, h=5, $fn=50); 
                translate([-20,0,0]) cylinder(r=1.6, h=12.5, $fn=50);  
                translate([-20,0,4]) cylinder(r=2, h=6.5, $fn=50); 
                translate([-20,0,10.4]) cylinder(r=3.1, h=5, $fn=50); 
                
                // nuts
                /*translate([-12.8,-2.8,7]) cube([5.6,10,2+0.5]);
                translate([-22.8,-2.8,7]) cube([5.6,10,2+0.5]);
                translate([-12.8,2.8,6.9]) cube([5.6,10,2.2+0.5]);
                translate([-22.8,2.8,6.9]) cube([5.6,10,2.2+0.5]);*/
                
                
                translate([-26,6.5,10]) rotate([30,0,0]) cube([21,16,10]);
            }
        }


    // shaft reinforcement
    difference()
        {
            translate([-21,0,0]) rotate([0,90,0]) cylinder(r=7, h=15, $fn=50); 
            translate([-21,0,0]) rotate([0,90,0]) cylinder(r=6, h=15, $fn=50); 
            translate([-30,-3,15]) rotate([-60,0,0]) cube([30,100,10]);
        }

    // idler bearing segments
    rotate([-160/2,0,0])
    {
    translate([0,0,0]) idler_segment_r();
   
    translate([14,0,0]) rotate([40,0,0]) idler_segment_r();
    translate([28,0,0]) rotate([80,0,0]) idler_segment_l();
    translate([42,0,0]) rotate([120,0,0]) idler_segment_l();
    translate([56,0,0]) rotate([160,0,0]) idler_segment_l();    
    }
    
    // shaft
    difference()
    {
        union()
        {
        translate([-26,0,0]) rotate([0,90,0]) cylinder(r=2.60+0.1, h=25, $fn=50);
        translate([-26,0,0]) rotate([0,90,0]) cylinder(r2=2.60, r1=3, h=3, $fn=50);
        }
        translate([-25,-0.15,5]) rotate([-60,0,0]) cube([20,12,9]);
    }
    
  
   
       
    // shaft bearing

   
  
    
    // endstop cut
    difference()
    {
        translate([8-0.5,0,0]) rotate([0,90,0]) cylinder(r=20, h=6+1, $fn=50); 
        translate([8-0.5,0,0]) rotate([0,90,0]) cylinder(r=14.5, h=6+1, $fn=50); 
        /*difference()
        {*/
            translate([-5,-48,-30]) cube([350,54,50]);/*
            translate([-5,-16,9]) cube([30,30,30]);*/ //should not need that but need testing
        //}
    }
    
    // removal opening
   
    
    // flat bottom
    translate([-30,-25,11]) cube([150,50,15]);
    

    
}}


 translate([-70+2,0,0]) rotate([0,-90,0]) cylinder(r=3.95, h=7, $fn=50); 
rotate([0,180,0]) 
idler();




    
    
    
    
    
    
    