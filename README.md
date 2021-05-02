# Material Switching Unit (MSU)

  <img src="https://i.ibb.co/pQHj8GD/DSC00081.jpg"> 

This is a work in progress, all the current 3d files work good enough but are not final. Checkout my YouTube channel (https://www.youtube.com/channel/UCF2tb5Hu6G_z-tB3_e_9U4A) for more info and updates on the progress of this project.

This GitHub is currently meant for people that want to take a look at the files or that want to contribute to the project. The MSU itself works but unless you have some significant background in programming and or programming you will have quite a bit of trouble getting everything running. Making this solution more reliable and accessible is the current goal for this project. 

This solution is extremely cheap an can be built for roughly 70$. In terms of board compatibility the simplest setup should be compatible with most 3D printers (even the stock ender 3 mainboard is compatible). The device has currently two different "versions" one is controlled by two stepper motors (and therefore requires at least one extra extruder support on the board which is uncommon) the second version, which is the one we are trying to transition to is controlled by one stepper motor (which plays the role of extruder and can actually directly be taken off of the old extruder) and one servo motor. Meaning that for the motor controls only one extra GIO pin is required which makes this compatible with almost any board.



There is also a difference between direct drive printers and bowden printers. In the case of a bowden printer the MSU will replace the extruder. In the case of a direct drive printer, the MSU is added but the original extruder remains. This means two things. First, the control logic is a bit different since we need to controls the two motors during a filament change and we also need to adjust the filament switching logic accordingly. Second, this also means that the compatibility is slightly reduced...well actually maybe not, I am working on controlling both the original extruder and the MSU with the same stepper driver, by using a parallel motor splitter (which is the 1 to 2 cable that most people use for dual Z axis). This does mean that there will be even more logic required since we absolutely **can't** have the two motors working at the same time since they have different steps per mm and would be working against each other. This is doable since we can engage or disengage the idler easily and basically push the filament out of the extruder assembly and then engage the idler to take over with the MSU. 

And here is one of the prints with the first working prototype:
 <img src="https://i.ibb.co/ZXKqCYj/IMG-1161.jpg" title="Water Dragon by Cipis"> 
 
If you want to contact me, asks questions, provide ideas or just stay up to date with this project join the discord server: https://discord.gg/Pj8bwTn
If you want to contact me privately, you can do so on discord or email me at: pierre.masselot.d@gmail.com  (only for relatively serious inquiries if you just need help please use discord as I will be able to respond much faster and other people will also be able to help you too)