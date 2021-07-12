  

This file is written using the Markdown markup language. If you want to contribute to the documentation and have an easier way to edit Markdown you can use editors like stackedit.io 

## **Multi-material upgrade on any printer: BUILD GUIDE**

The aim of this project is to popularize multi-material 3d printing by making a more reliable, cheaper, and hopefully better multi-material upgrade based on the MMU2 from Prusa. There is still a lot of work to do but this is prototype that works well enough to be considered as viable.

## **Different setups and compatibility**

The MSU can be build in a few ways, and more options are being added. They all present benefits so we will go over the different setups that one can run. The first thing that you will see are the board requirements which will help you decide which setup you can and want to  use. Those requirements don't include the filament flow sensor yet. If you also want to be able to support it when we finish working on it you will need two extra GPIO pins.

 be preceded by [**setup type**] and ended by [**/setup type**]
ex: 
[**Bowden style version**] information specific to a bowden style setup [**/Bowden style version**]
information relevant for both setups
[**Direct drive version**]information specific to direct drive setups[/**Direct drive version**]


**Bowden style version**
requirements: 

servo idler **(recommended)**: 4 stepper motor controls and drivers(X,Y,Z,E), 1 GPIO pin(servo control) and access to 12V (servo power)

stepper motor controlled idler: 5 stepper motor controls and driver(X,Y,Z,E, IDLER), 1 extra endstop port (the idler needs homing for positional accuracy)

It is the simplest setup, the MSU acts as the extruder and the filament changing process is simple, unload the filament until it clears the merger and then reload the new one by changing the idler position to put pressure on the filament that needs to be used.
This will be compatible with almost every printer and motherboard when using the servo-version.

**Direct drive version**
requirements: servo idler: 5+1 stepper motor controls and drivers(X,Y,Z,E), 1 GPIO pin(servo control) and access to 12V (servo power)
stepper motor controlled idler **(ideal)**: 6+1 stepper motor controls and driver(X,Y,Z,E, IDLER), 1 extra endstop port (the idler needs homing for positional accuracy).

The additional optional stepper motor control is used in order to be able to control the extruder and the MSU independantly, will allow for slightly faster tool change and less complexity

**Direct drive version linked extruders**

requirements: servo idler: 4 stepper motor controls and drivers(X,Y,Z,(E and IDLER combined)), 1 GPIO pin (servo control) and access to 12V (servo power)
stepper motor controlled idler: 5 stepper motor controls and driver(X,Y,Z,(E and IDLER combined)), 1 extra endstop port (the idler needs homing for positional accuracy)


This is the same version as the direct drive one with the only difference being that the extruder son both the MSU and on the actual extruder will be connected to the same driver meaning that a lot more logic needs to be implemented in order to never have both of them running at the same time, since they have different steps per mm meaning that if we run them at the same time one will be fighting against the other.

## **Before you attempt to build this:**

This guide is currently meant for more advanced user, comfortable with Marlin configuration and with a bit of programming experience. The models may still need work and are not final. You will need to do a lot of tuning before you get everything going, parts modification may be required, and you will almost certainly need to do some troubleshooting. If you are still reading this and want to build this for yourself, I highly recommend you join the discord server (you will find it in the readme file). There is a help channel in there specifically to answer any questions or issues you have while building the MSU.

There are also a few things to know before deciding to build this upgrade. I don’t take any responsibility regarding your actions, this is still a prototype and requires heavy modifications of your printer, which could result in permanent damage, which is a risk that you should be willing to take if attempting this build.

There will also be improvements that may require extra parts in the future, you should be easily able to transition from this version to the newer ones, but this will add extra costs.

Lastly, this is not perfect, and your printer may not work as well as before so you should make sure that you can afford having your printer out of commission and keep a copy of the firmware for single filament on hand (you will work on it later in this guide) so that you can transition back to the original state to print improved parts or to fix models that may not be working correctly.

## **Parts required**

All the following links may be affiliate links (mostly the amazon ones) and I may earn money if a purchase is made using those links. All the profit will go directly back in this project. The price mentioned is only to give you an idea as they may fluctuate. The ones mentioned are the lowest ones I could find including shipping to NA at the date of writing this.

The price total will not match the list exactly since some of those components come in packs of 700 (like screws) when we only need a few and you probably already have them.

| Part name | Picture | Links | Pcs in pack | Pcs needed | Price $ |
|--|--|--|--|--|--|
| 608 ball bearings| ![608 ball bearings](https://i.postimg.cc/25rbdbp3/image.png) |[https://amzn.to/3ePrE0i](https://amzn.to/3ePrE0i)<br />[https://aliexpi.com/Ep3X](https://aliexpi.com/Ep3X)|10|6|5.17$|
|Heated inserts M3|![enter image description here](https://i.postimg.cc/RhX4VChC/image.png)|[https://amzn.to/3ogq3nt](https://amzn.to/3ogq3nt)|100|~10|10$|
|M3 and M2 bolts and nuts| ![](https://i.postimg.cc/C5WJ8kzc/image.png)|[https://amzn.to/3bu7WVL](https://amzn.to/3bu7WVL)|700|~20|20$|
|PTFE tubing<br/> PC4-M10<br/> PC4-M6|![enter image description here](https://i.postimg.cc/FzggY8XH/image.png)|[https://amzn.to/2RWcyNH](https://amzn.to/2RWcyNH)<br/>these type of kits include everything you will need(and much more with the new merger) and are the best value|5m<br/>10 pcs<br/>10 pcs|0.5m<br/>1 pcs<br/>1pcs|10$|
|5mm to 5mm coupler|![enter image description here](https://i.postimg.cc/yxv34Hzc/image.png)|[https://amzn.to/3ou1XG1](https://amzn.to/3ou1XG1)<br/>[https://amzn.to/3ybPWcp](https://amzn.to/3ybPWcp)<br/>In a last resort situation you can opt of the flexible 5 to 5 couplers that are more commonly available, but definitely replace it with a solid coupler ASAP|2|1|7$|
|Metal rod 5mmx124mm (a little longer won’t cause any problems and you will have a hard time finding a rod exactly to size)|![enter image description here](https://i.postimg.cc/mDVghy6G/image.png)|[https://amzn.to/3btXOMH](https://amzn.to/3btXOMH)<br/>[https://amzn.to/3tSTv3Y](https://amzn.to/3tSTv3Y)<br/> Following links are for a D shaft, basically a rod with one side machined in order to be able to easiely secure and mount the gears. (making a D shape, hence the name)<br/>Similar results can be optained by using a dremel to flatten the rod at each set screw position<br/> https://aliexpi.com/Zrzg|5<br/>|2|8.5$|
|MK8 gears with filament groove|![enter image description here](https://i.postimg.cc/m2WTRqrF/image.png)|[https://amzn.to/3uQZVlo](https://amzn.to/3uQZVlo)|5|5|8$|
|Nema 17 stepper motor|![enter image description here](https://i.postimg.cc/tJ3QYqgn/image.png)|[https://amzn.to/3wy6Gcv](https://amzn.to/3wy6Gcv)|1|1 or 2 for direct drive<p>-1 if servo controlled idler|14$|
|Servo (for servo controlled idler)|[![616z-Elw-Ukz-L-AC-SL1001.jpg](https://i.postimg.cc/Dydk3RVc/616z-Elw-Ukz-L-AC-SL1001.jpg)](https://postimg.cc/3dRbgSxy)|https://amzn.to/3bQh1sd<p>when using a servo you wil need one less stepper motor so take it into consideration when ordering|1|1 or 0|17$|
|Endstops|![enter image description here](https://i.postimg.cc/hG6Hszz7/image.png)|[https://amzn.to/3wy6WrZ](https://amzn.to/3wy6WrZ) <br> Only needed when running the stepper controlled idler|10|1|8|
|Idler springs|![idler springs](https://i.postimg.cc/RVdy8bJm/image.png)|[https://shop.prusa3d.com/en/spare-parts/599-idler-spring.html](https://shop.prusa3d.com/en/spare-parts/599-idler-spring.html) <br/>[https://www.voxelfactory.com/collections/original-prusa-i3-mk2-mk2s-parts/products/replacement-tension-spring-for-prusa-i3-mk2s-or-mk3](https://www.voxelfactory.com/collections/original-prusa-i3-mk2-mk2s-parts/products/replacement-tension-spring-for-prusa-i3-mk2s-or-mk3)<br/>(next links are not originial prusa springs but match the specs closly and will work perfectly fine)<br/>https://amzn.to/3hKlO2d   <br/> https://aliexpi.com/HHM1<br/>You will want to choose 10mm length 0.9mm wire diameter and 5mm outer diameter|1|2|4-8$|
||| [**Direct drive version**]<p>for the direct drive version you will only need one extra stepper motor, you can use the link above<p>[**/Direct drive version**]
|||[**Direct drive version linked extruders**]<p>for this version you will also need  the extra stepper driver but also a stepper motor splitter linked below<p>[**/Direct drive version linked extruders**]|||
|Stepper parallel module|[![61ma7umi-Js-L-SL1001.jpg](https://i.postimg.cc/VvrBwxHL/61ma7umi-Js-L-SL1001.jpg)](https://postimg.cc/LgSZBbpr)|https://amzn.to/3hNCplH|3|1|8$
|total bowden |||||78$|
|total direct drive|||||83$|
|total direct drive linked extruder|||||91$|




## **Prebuild checks**

[**Direct drive version**]

The first thing you should do is to find some way to feed the filament to the extruder using a bowden tube, you will most likely have to design an adapter to be able to fit a PC4 M6 or M10 coupler on there. I will try to have as many of those in the GitHub repo but you may have to design it yourself. If you do end up designing one make sure to add it to the repo so that other people can use it (you can do so by creating a pull request). If you don't know how to or don't want to spend the time designing one shoot me a pm on discord and I could design one for you setup in exchange for  a small commission.

You will also need to make sure that your extruder assembly can easily grab filament with minimum pressure applied. Since we need to change the filament multiple times during the print, the extruder gears need to be able to grab onto the filament and feed it to the nozzle without any clogs or jams. To test this you can simply go inside motion in Marlin and extrude a long distance, and while the extruder is running slowly insert the filament into the extruder. The pressure required for the filament to be grabbed by the gears should be minimal and once grabed the filament should be able to be fed up to the nozzle without any clogging or jamming. If the filament is not bein grabbed by the gears, you may need to reduce the extruder idle pressure by slightly shortening the spring (proceed at your own risk! this has a high chance of messing up your extruder and you will most likely end up needing to order a new extruder spring) if the filament is being grabbed by the gears but is not feeding correctly up to the nozzle its most likely because there are some gaps in the assembly where the filament can escape and cause jams. To fix this you will have to get creative but some modifications for your specific extruder probably already exist because printing with super flexible filaments has similar requirements. These modifications will most likely involve lining as much as the filament path with PTFE tubing. Finally, some extruders may simply not work very well for the MSU and you may have to switch to a known compatible extruder (I will work on a list of compatible extruders at some point in the future)

 [**/Direct drive version**]
 
Before trying to build this upgrade, you should have a fully working printer, with a compatible mainboard (check below), with Marlin configured properly for a single extruder. You should get the Marlin source code from the Marlin fork that is inside the repo, it is currently a submodule of this repo so you will have to clone it independantly. Once you have Marlin configured for your printer before upgrading to the MSU keep a copy in a known location so that you can easily transition back to stock if the upgrade where to fail. 

After that, download the latest version of PrusaSlicer and follow this guide ([https://www.youtube.com/watch?v=Wz2Soog4HkQ&t=245s](https://www.youtube.com/watch?v=Wz2Soog4HkQ&t=245s) ) on how to set everything up for your printer in a single extruder mode. 

Once all off that is done download the latest files from my GitHub and start printing them using the methods and settings mentioned below. Check that you also have all the components and tools required.

## **Motherboard compatibility**

Your mother board will need to have 5 dedicated stepper motor control (and in case of a dual Z make sure that your printer is using a splitter internally, meaning that you have 6 motor plugs available or use a splitter for your Z axis : [https://amzn.to/35fcFaS](https://amzn.to/35fcFaS) or [https://amzn.to/2L60ard](https://amzn.to/2L60ard) ). Once you have checked that your motherboard supports enough motor controls make sure that you have a way to access to at least two I/O pins: one for the endstop and one for the magnetic rotary encoder (will most likely be an AS5600 in I2C mode) that I am working on. You should also have some access to VCC and ground but even if there are no extra dedicated pins you could easily use one from any of the endstops. You will also need to make sure that you have access to 3.3V (or be ready to convert 5 to 3.3) but as I said your endstops may already have this available. If you have endstop pins for X,Y and Z max you should be good to go.

We are currently working with Paul Lewis to replace/ give the option to have a servo motor controlling the idler instead of a servo motor. This means that we will eventually need only 4 stepper motor control and a servo port (you will need a single free pin and some ways to get your servo connected to vcc and ground).

Mother board with extra endstops connector and easily accessible expansion pins will be the easiest to work with since less tweaking will have to be done to the Pins file of your specific board. If by any chance you were to modify something to fit your setup and think that it could be useful to other people, make sure to let me know and maybe do a pull request.

If your current motherboard isn’t compatible, changing your printer’s mainboard is an easy process and I recommend the SKR 1.4 or SKR PRO V1.1 boards if you are buying them specifically for this

## **Printing**

Since we are currently working on the 3d files constantly, you will need to download the original files from GitHub and then convert them into an stl file in order to be able to print them. All the files are currently in .f3d which means that fusion 360 is needed in order to convert them. If you have any problem regarding the stl conversion message me and I will add the STLs in GitHub as well.

## **Idler body, pulley body and merger:**

All of those files are in the F3D folder insider the parts folder. In order to convert them to stl you will need to download fusion 360([https://www.autodesk.ca/en/products/fusion-360/personal](https://www.autodesk.ca/en/products/fusion-360/personal) ) after doing all of the setup you will have to open each file, select the object you want to print by right clicking on it and using save as STL

![enter image description here](https://i.postimg.cc/yNjDSKk5/image.png)

The idler body and the pulley body are both in the same file, the merger and the idler are in a separate file each. Once you have all of them converted to stl they are easy to print, they do not require any support (except the idler but see details below) and you can print them at a 0.2 mm layer height and 0.1mm layer height for the merger. Infill should be at least 20%.

**Idler**

This model prints vertically as shown below:

![enter image description here](https://i.postimg.cc/ryBSSSVL/image.png)

Once the model is on the build plate you will need to use supports only touching build plate and add a support blocker in the center of the idler.

![enter image description here](https://i.postimg.cc/MTcQBGgT/image.png)

All of the settings that I am using can easily be found inside other slicers (PrusaSlicer shown below)

![enter image description here](https://i.postimg.cc/WpkZbhMY/image.png)

once you have selected support blocker you will need to click once at the center of the idler so that no support is printed inside the motor shaft mount. Slice the model using the layer height that you want to use (I personally used 0.2mm)

go into preview mode and use the slider to mark the last layer before closing the bearing enclosure as shown below. In the latest version of the idler there is a step at each end of the bearing to help with friction. You will need to make sure to put the pause before that step.

![enter image description here](https://i.postimg.cc/NMrKMzr2/image.png)

Use the arrow up and down to go up layer by layer.

Mark down this layer height for each bearing, you should have 5 values for the 5 bearings.

You then have to add a pause at layer line script for each of those values in cura go to extensions-> post processing-> modify gcode->add a script->pause at height.

From the drop-down menu select pause at layer No and change the pause layer to the first value that you took. Repeat with each value.

![enter image description here](https://i.postimg.cc/vBWGCFVh/image.png)

Reslice your model one last time and start the print, your printer should pause before closing a bearing enclosure and insert the 608 ball bearings before resuming the print.

Once the print is completely done make sure that your bearings can spin freely and insert the heated inserts/embedded nuts into your print (heated inserts position and demo below)

![enter image description here](https://i.postimg.cc/cHWpgKv7/image.png)

You are now done with the idler.

## **For PrusaSlicer**

Use paint on supports to support the endstop slot and support blockers to prevent any supports from blocking the motor shaft.

![enter image description here](https://i.postimg.cc/KYSVwKDX/image.png)

Layer pause

![enter image description here](https://i.postimg.cc/C1vchdkx/image.png)

Right click on the orange plus icon and insert pause print Gcode

Here it is so that you can copy it

G0 X0 Y0

M104 S0 ; standby temperature

M0 ; Do the actual pause

M109 S200 ; resume temperature you may need to change that value to match the material you are using


The merger may require a bit of post processing since any stringing and print defects that happened insider the tube may jam the filament. First try to insert your ptfe tube in each dedicated slot and then put a filament through. If holes themselves seem too tight for the filament you most likely have problems with horizontal expansion, so I recommend that you make use of the help channel on discord. If there seems to be a point where the filament gets jammed then make sure that your ptfe tube is cut straight and properly inserted, if it is the case try to put a bit of pressure on the filament or use a hard object to remove the jam. If there is some slight friction this is normal, and it will get better and better and the merger wears out.

## **Assembly:**

Assembly is relatively easy.

### Old merger only
The first thing is to assemble the merger and check that it works properly as mentioned previously. It uses only PC4 M10 pneumatic couplers that you should be able to screw in by hand. You may need a bit more force for the end, but it should not take too much force otherwise you could strip the connectors and have to reprint the model.

![enter image description here](https://i.postimg.cc/zXw0vdnQ/image.png)

### New merger
the merger needs a bit of support touching build plate in order to print successfully. It only needs one PC4 M10 coupler on the output since it is a press fit design.
Also check that the clearances are right before assembly by checking every filament path.

You can now set the merger aside.

![enter image description here](https://i.postimg.cc/FK6x8w4Y/image.png)

You will then need to setup your motor. Connect the motor and one of the 5mm metal rod. If you are using a flexible coupler, make sure that the two ends are touching to reduce flex to a maximum. Slide all the extruder gears onto the rod but do not tighten them too much yet: the screws used are really small and can be damaged easily and you will need to be further in assembly in order to align the gears properly.

![enter image description here](https://i.postimg.cc/h4T0ZC3G/image.png)

The next parts that will need work are the pulley body and the idler. They both need heated inserts.

[idler picture todo still not reprinted]

If you are not familiar with heated inserts here is a guide: [https://hackaday.com/2019/02/28/threading-3d-printed-parts-how-to-use-heat-set-inserts/](https://hackaday.com/2019/02/28/threading-3d-printed-parts-how-to-use-heat-set-inserts/)

They are not that difficult to use just make sure to not heat up your part for too long.

![enter image description here](https://i.postimg.cc/RZFKmGGK/image.png)

You can then insert the motor and shaft assembly. Secure the motor using M3*8 screws, if they don’t align with the motor (by about 1mm) checkout the latest update of this model since the previous one didn’t have the correct spacing (with a bit of work even that one worked just not perfectly). You can now align each of the gears with the filament slot corresponding and properly tighten them.

![enter image description here](https://i.postimg.cc/PJyvs8wS/image.png)

Attach each PC4-M6 couplers to the output of the MSU.

![enter image description here](https://i.postimg.cc/XqY751rg/image.png)

If using the stepper idler version of the upgrade, you then have to wire up the endstop for idler body, which you will then secure using M2*12 screws and nuts. It should be facing inward towards the center of the idler

![enter image description here](https://i.postimg.cc/SKbSdxXR/image.png)

Place a bearing on the end of the idler and pass it through the motor hole of the idler body. You will then be able to press fit it in the dedicated slot.

![enter image description here](https://i.postimg.cc/XJVVM1k0/image.png)

Once it is done insert the motor in the idler and secure it to the body using M3x8 screws.
If you are using the servo version the procedure is similar with the only difference being that you will need M4 screw in order to secure it to the idler-servo body.
 After this is done put M3x12 screws in the idler (in the heated inserts) and secure it to the motor. No need to tighten them extremely hard since you might rip out the inserts.

![enter image description here](https://i.postimg.cc/KjWFMGSZ/image.png)

After this is done check that the idler can properly rotate and triggers the endstop properly (once again only for the stepper controlled idler).

![enter image description here](https://i.postimg.cc/yYws68yj/image.png)

Assemble the idler body and pulley body as shown and insert the remaining metal rod through the dedicated holes.

![enter image description here](https://i.postimg.cc/MGwwR34j/image.png)

The amount of force required to insert the rods may vary depending on your print settings but I still need feedback regarding clearances so if you have a well calibrated printer let me know whether the clearances are right or whether I need to increase/decrease them.

![enter image description here](https://i.postimg.cc/5yXW1hHD/image.png)

You can now insert the spring and the screws: M3x(from 25 mm up to 35 mm) in order to tension the idler. For now idler tension will be made through trial and error but a good indicator is when you are able to open idler slightly and that the springs push it back in a closed position. I will add visual indicators in a later model as well as find other springs.

![enter image description here](https://i.postimg.cc/1565qFt2/image.png)

You will then need to mount the MSU to your printer. A mount for aluminum extrusions will be designed shortly but you will have to improvise for now, either design your own or use zip ties.
### Old merger only(will remove after testing)
(You can then connect the merger to the nozzle. Try to have about 5 cm of space in between so that the filament changes can be as fast as possible but not below 4 cm so that the ptfe tube bend isn’t too hard (potentially causing issues).)

You can then connect each of the merger inputs to the MSU outputs making sure that the ptfe tubing is long enough to reach the extremities of the axis.
### New merger (V2)
Insert the merger inside the pulley body (the fit should be a press fit), and secure it in place using 2 M3x8 mm. You can now connect the PTFE tube from the output of the merger up to the nozzle. Make sure that the PTFE tube is going inside it's dedicated slot inside the merger (and not simply into the coupler), if there are clogs with regular filament (1.75mm that hasn't been inside the nozzle) inside the merger try with and without the coupler. If it doesn't  jam without the coupler it means that the PTFE tube was not properly inserted. If it jams in both cases it means that your clearances a probably off, try increasing the scale of the model.

You are now done with the building process.

## **Marlin configuration[TODO: update to the latest version]**
### if you are building it now and find a setting that you are not sure about, contact me on discord
This needs to be done **after** you have successfully configured Marlin for a single extruder setup (You may have seen that in the configuration file there is a default of 3 extruders, but this should not cause any problems when setting up your printer for a single nozzle. If it does you can switch it back to one but remember that you need to switch it back to 3 when configuring for the multi-material upgrade).

The following code snippet are the MSU related settings inside the Configuration.h file (Marlin/Marlin/Configuration.h)

This line needs to be uncommented in order to enable MSU functionalities
```cpp 
#define MSU
```
The following lines of code are responsible for the selection of the type of setup you want to run. Choose one between bowden, direct-drive, and direct-drive with linked extruders. On top of that you have the option to use a servo controlled iderl, the default being a stepper-controlled idler
```cpp
#if  ENABLED(MSU)
//#define MSU_BOWDEN_TUBE_SETUP //enable when working with the MSU as a bowden extruder itself
//#define MSU_DIRECT_DRIVE_SETUP //enable to work in a direct drive setup, if doing so don't forget to disable MSU_BOWDEN_TUBE_SETUP
//#define MSU_DIRECT_DRIVE_LINKED_EXTRUDER_SETUP //enable to work in a direct drive setup where both the MSU extruder and the actual extruder are connected to a parrallel module
//#define MSU_SERVO_IDLER //enable to control the idler using a servo
```
The following lines are additional configuration options that are most likely already good but that you want to double check in case you have a different setup. Use the description to understand what each setting does and adjust them accordingly
```cpp
#define MSU_MENU//LCD Menu

#define MSU_EXTRUDER_ENBR 0//define the MSU extruder motor nbr. ex: when using the E1 port and if defined correctly in the pins file of you board you would use MSU_EXTRUDER_ENBR 1

#if ENABLED(MSU_SERVO_IDLER)
	#define MSU_SERVO_IDLER_NBR 0//if your board has servo support select the servo nbr you want to use(if you are not sure you can check in the pins file of your board but 0 will most likely be the default servo port for your board). If your board doesn't support them directly you can also define a custom one in your pins file once again
#else
	#define MSU_IDLER_ENBR 1 //define the idler extruder motor nbr.
#endif

#if ENABLED(MSU_DIRECT_DRIVE_SETUP)
	#define MSU_ORIGINAL_EXTRUDER_ENBR 2//define the extruder nbr that the actual extruder is connected to
#endif
  
#if DISABLED(MSU_SERVO_IDLER)
	#define MSU_IDLER_ENDSTOP_AXIS X //select the endstop connected
	#define MSU_IDLER_ENDSTOP_MINMAX MAX
	//#define IDLER_ENDSTOP_PIN //TODO for a custom endstop pin.
#endif

  
```
The two next lines are to set the length of the bowden tube and of the distance from the nozzle to the extruder gears (only required for direct drive)
```cpp
#define MSU_BOWDEN_TUBE_SETUP_LENGTH 200//bowden tube length from the crossing point of the merger to the nozzle

#define MSU_NOZZLE_EXTRUDER_GEAR_LENGTH 40 //Only necessary for direct drive setups, the distance from the extruder gear up to the nozzle.

#endif 
```

Remember to set your extrude_maxlength higher than your bowden tube length
```cpp
/**
* Prevent a single extrusion longer than EXTRUDE_MAXLENGTH.
* Note: For Bowden Extruders make this large enough to allow load/unload.
*/
#define  PREVENT_LENGTHY_EXTRUDE
#define  EXTRUDE_MAXLENGTH  200
```
You should then enable XMAX plug (uncomment it by removing the //) since this is what we are going to be using to home the idler.
```cpp
// Specify here all the endstop connectors that are connected to any endstop or probe.
// Almost all printers will be using one per axis. Probes will use one or more of the
// extra connectors. Leave undefined any used for non-endstop and non-probe purposes.
#define  USE_XMIN_PLUG
#define  USE_YMIN_PLUG
#define  USE_ZMIN_PLUG
//#define USE_XMAX_PLUG
//#define USE_YMAX_PLUG
//#define USE_ZMAX_PLUG
```
 If you board does not have an XMAX endstop you can find a free IO pin and connect your enstop to that, but you will need to configure an XMAX enstop inside your boards pins file similarly to what is shown below. If you won't know where that pins file is you can find it using google but the general location is:
 Marlin\Marlin\src\pins\...
 
 
```cpp
#define X_MAX_PIN PC2 // use your boards pin diagram to figure out which pin to use
```
You may also need to invert the endstop logic depending on your board. If the idler doesn’t home (considers the endstop as always triggered) this may be the problem.
```cpp
// Mechanical endstop with COM to ground and NC to Signal uses "false" here (most common setup).
#define  X_MIN_ENDSTOP_INVERTING false // Set to true to invert the logic of the endstop.
#define  Y_MIN_ENDSTOP_INVERTING false // Set to true to invert the logic of the endstop.
#define  Z_MIN_ENDSTOP_INVERTING false // Set to true to invert the logic of the endstop.
#define  X_MAX_ENDSTOP_INVERTING false // Set to true to invert the logic of the endstop.
#define  Y_MAX_ENDSTOP_INVERTING false // Set to true to invert the logic of the endstop.
#define  Z_MAX_ENDSTOP_INVERTING false // Set to true to invert the logic of the endstop.
#define  Z_MIN_PROBE_ENDSTOP_INVERTING false // Set to true to invert the logic of the probe.
```
You will also need to define driver type for each motor

```cpp
#define  X_DRIVER_TYPE A4988
#define  Y_DRIVER_TYPE A4988
#define  Z_DRIVER_TYPE A4988
//#define X2_DRIVER_TYPE A4988
//#define Y2_DRIVER_TYPE A4988
//#define Z2_DRIVER_TYPE A4988
//#define Z3_DRIVER_TYPE A4988
//#define Z4_DRIVER_TYPE A4988
#define  E0_DRIVER_TYPE A4988
//#define E1_DRIVER_TYPE A4988
//#define E2_DRIVER_TYPE A4988
//#define E3_DRIVER_TYPE A4988
//#define E4_DRIVER_TYPE A4988
//#define E5_DRIVER_TYPE A4988
//#define E6_DRIVER_TYPE A4988
//#define E7_DRIVER_TYPE A4988
```
Similarly to your XYZ axis you can change the direction of the extruder stepper in order to match the expected behavior. If when homing the idler goes in the opposite direction you would change E1 dir to false(Or E x if you have setup custom extruder pins)
```cpp
// For direct drive extruder v9 set to true, for geared extruder set to false.
#define  INVERT_E0_DIR false
#define  INVERT_E1_DIR false
#define  INVERT_E2_DIR false
#define  INVERT_E3_DIR false
#define  INVERT_E4_DIR false
#define  INVERT_E5_DIR false
#define  INVERT_E6_DIR false
#define  INVERT_E7_DIR false
```

you will also need to enable distinc e factors if you are using a stepper controlled idler since you will need different steps per mm for the extruder and for the idler
```cpp
#define DISTINCT_E_FACTORS
```
You are now done with the software modifications.

## **Slicer settings.**

You will now need to configure the slicer in order to adapt it to your printer.

You can use the same slicer profile that you were using or create a new one (recommended)

The first thing you will need to do is change the number of extruders to 3, in the printer settings tab and to check the single extruder multi material

![enter image description here](https://i.postimg.cc/wThRdZh1/image.png)

You also need to use relative E distance

You should now have 5 extruders to work with.

In there you can change retraction settings (choose a setting similar to what you were using before) and also select the extruder color: extremely useful for multi-color prints.

![enter image description here](https://i.postimg.cc/Y0NrJcJk/image.png)

Now go to the single extruder multimaterial parameters(Single extruder MM setup)

You will have four things to adjust. First off, the cooling tube position. In order to find it simply measure from your nozzle to the middle of the cooling block on your extruder. The cooling tube length will vary depending on your extruder but 10mm seems to be a good value for most extruders. The filament parking position should be the cooling tube position+ (the cooling tube length/2) since we are handling the unloading and reloading in Marlin (may not be as necessary right now but when working with less capable boards will enable us to make some really interesting stuff…  more info on that later) the extra loading distance should be at 0 and be tweaked if you find that it doesn’t start extruding exactly when restarting (this is irrelevant when using a wipe tower).

![enter image description here](https://i.postimg.cc/hGHKvPnc/image.png)

You will then go in filament settings and make sure that you have keep fan always on turned on since it will stop when doing tool changes and not turn on for small patch of color.

![enter image description here](https://i.postimg.cc/ZKVZ3Lmf/image.png)

Then go in advanced and change 4 things. The number of cooling moves: too low and it will jam and too high and it will take a huge amount of time. 3 seems to work well for me, the speed of the cooling move can also be adjusted but it doesn’t matter much, a little faster will speed up a filament change

![enter image description here](https://i.postimg.cc/qRsH7sQx/image.png)

In here you can adjust the filament change time in order to get more accurate time extimates for your print. While the speed is constantly changing as I improve the loading and unloading sequence and since it will also vary based on your ptfe tube length I recommend you measure the tool change time for your setup by sending T1 or any toolchange gcode and measure the time that it takes. This setting is very usefull since leaving it at 0 will give you some extremly optimistic results and on a 15 hr print it may be off by up to two hour, and this can result in lack of sleep...don't ask me why.
The last thing in there that your will need to adjust is the ramming setting. The default one seems to work but with a bit of tweaking you can get a way cleaner filament tip the following picture is an example of what I am running but you will need to do a bit of experimenting on your side.

![enter image description here](https://i.postimg.cc/L6CKh6kw/image.png)

You just need to click on ramming settings to get access to these controls.

In print settings make sure that you have the wipe tower enabled inside of the Multiple extruder tab and prime all printing extruders enabled as well.

![enter image description here](https://i.postimg.cc/GtLVhZ4b/image.png)

You are now done with slicer settings.

To print you will just need to import a multicolor model. Launch prusa slicer, open all the parts of your model at the same time.

![enter image description here](https://i.postimg.cc/7ZGc61ZJ/image.png)

Click open

![enter image description here](https://i.postimg.cc/gJdBNfq3/image.png)

Hit yes

You will then be able to select different extruders on the right hand side of your screen. Happy printing!

If you have any problems, make sure to message me on discord so that I can both help you and improve the documentation.

## **Tips to get a successful multicolor print.**

Idler tension is key to get good prints. If you see any extrusion discrepancies or under extrusion, then the fix will most likely be to increase idler tension.

If your filaments are all new, then it is recommended to turn on prime all printing extruders since it will shape all the filaments at the start of the print which will help you detect any problems at the beginning.

Another failure point that I have seen is on the coupler and the gears, if they are not tight enough, they will slip on the rod, resulting in under extrusion or even no extrusion in some cases.

The purge block is a huge waste of filament, but it can be adjusted based on the filament transition (transitioning from blue to cyan will require less purging that from black to white). Other things like wipe in object and wipe in infill can be enabled an optimized in order to reduce filament waste.

## **Working on**

I am working on a filament sensor which would help a lot with filament load failures, filament jams, filament slipping in the extruder and would help a lot with the success rate of multicolor and single-color prints.

Documentation improvements.

Compatibility lists.

Adding as many hotend settings specifically for the MSU.

A lot of nice to have features and complex multi-material 3d designs to demonstrate the capabilities of such multi-material upgrades, using different materials as well as some that are not supposed to bond well together (I have a few ideas of 3d printing processes that could fix that).
