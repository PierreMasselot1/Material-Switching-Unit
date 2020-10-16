# MMU2-on-any-printer
I'll progressively add files on the repository as the projects goes on, these are not final. Checkout my youtube channel (https://www.youtube.com/channel/UCF2tb5Hu6G_z-tB3_e_9U4A) for more info. This github is currently meant for people that want to take a look at the files or that want to contribute to the project. 
The code is in another repository (https://github.com/PierreMasselot1/Marlin-MMU-clone-on-any-printer) and is a simple fork of Marlin. The config files are the default ones and will need to be edited to your specific board. For now the minimum  board requirements are at least 5 independent motor control(X,Y,Z,Extruder,Idler) make sure to take into account dual Z steppers(can be solved easiely by using a splitter), but I highly recommend 6 independent motor controls because depending the result of the testing we may go to a direct drive route which would require an extra motor. If you are planning on contributing I recommend using the SKR pro (V1.1 is the one I am using but V1.2 will also work since they are basically the same) and if not you should definitely wait because things like the SKR mini E3 could work which would mean a much lower price and also a cleaner implementation (if you have and ender 3 or similar).


The list below is only ideas and any help is appreciated so if you have a cool idea or feature you would like to see added go for it.
What would be helpful:

Physical:
* cleaner models (I didn't really take care of aesthetics so if you think you can improve the design go for it)
* clean way to add a filament sensor
* cleaner merger/pulley body connection

Software:
* any potential bug
* quality of life improvement: physical buttons, info on LCD + interface, implementing a filament sensor ( error detection and "SpoolJoin" )


