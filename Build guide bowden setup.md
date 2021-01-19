This file is written using the Markdown markup language. If you want to contribute to the documentation and have an easier way to edit Markdown you can use editors like stackedit.io

**Multi-material upgrade on any printer: BUILD GUIDE**

The aim of this project is to popularize multi-material 3d printing by making a more reliable, cheaper, and hopefully better multi-material upgrade based on the MMU2 from Prusa. There is still a lot of work to do but this is prototype that works well enough to be considered as viable.

**Before you attempt to build this:**

This guide is currently meant for more advanced user, comfortable with Marlin configuration and with a bit of programming experience. The models may still need work and are not final. You will need to do a lot of tuning before you get everything going, parts modification may be required, and you will almost certainly need to do some troubleshooting. If you think this is too much for you do not worry, I will be releasing a tutorial that goes way more in depth and should be easier to follow, the models shown and provided in this video will be tested on multiple printers and the risk of something not working will be reduced by a lot. If you are still reading this and want to build this for yourself, I highly recommend you join the discord server. There is a help channel in there specifically to answer any questions or issues you have while building the MMU.

There are also a few things to know before deciding to build this upgrade. I don’t take any responsibility regarding your actions, this is still a prototype and requires heavy modifications of your printer, which could result in permanent damage, which is a risk that you should be willing to take if attempting this build.

There will also be improvements that may require extra parts in the future, you should be easily able to transition from this version to the newer ones, but this will add extra costs.

Lastly, this is not perfect, and your printer may not work as well as before so you should make sure that you can afford having your printer out of commission and keep a copy of the firmware for single filament on hand (you will work on it later in this guide) so that you can transition back to the original state to print improved parts or to fix models that may not be working correctly.

**Parts required**

All the following links may be affiliate links (mostly the amazon ones) and I may earn money if a purchase is made using those links. All the profit will go directly back in this project. The price mentioned is only to give you an idea as they may fluctuate. The ones mentioned are the lowest ones I could find including shipping to NA at the date of writing this.

Products in green are the ones that I consider as necessary to buy specifically for this build and in red the ones that you may need to buy but that come in big packs and that you will most likely use for other projects(let’s say that you need only 15 screws for this build and we are not going to count the 700 screws in the pack in the final price) and that you probably already have like M3 bolts and nuts. The red items will be allocated a very small budget but will not be included completely in the final price calculations.
| Part name | Picture | Links | Pcs in pack | Pcs needed | Price $ |
|--|--|--|--|--|--|
| 608 ball bearings| ![608 ball bearings](https://i.postimg.cc/25rbdbp3/image.png) |[https://amzn.to/35gdeBc](https://amzn.to/35gdeBc)<br />[https://amzn.to/3olusVk](https://amzn.to/3olusVk)<br />[https://amzn.to/3hQoNny](https://amzn.to/3hQoNny)<br />[https://aliexpi.com/Ep3X](https://aliexpi.com/Ep3X)| 20 <br /> 20 <br /> 10<br /> 10|6|5.17$|
|Heated inserts M3|![enter image description here](https://i.postimg.cc/RhX4VChC/image.png)|[https://amzn.to/3pVMIou](https://amzn.to/3pVMIou)<br/> [https://amzn.to/3bfT7qr](https://amzn.to/3bfT7qr) (better choice)|20<br/> 420|4|10$|
|M3 and M2 bolts and nuts| ![](https://i.postimg.cc/C5WJ8kzc/image.png)|[https://amzn.to/35dwXSc](https://amzn.to/35dwXSc)|700|≃20|20$|
|PTFE tubing<br/> PC4-M10<br/> PC4-M6|![enter image description here](https://i.postimg.cc/FzggY8XH/image.png)|[https://amzn.to/3nBpF0Z](https://amzn.to/3nBpF0Z)<br/>these type of kits include everything you will need and are the best value|4m<br/>8pcs<br/>8pcs|2m<br/>6 pcs<br/>5pcs|10$|
|5mm to 5mm coupler|![enter image description here](https://i.postimg.cc/yxv34Hzc/image.png)|[https://amzn.to/3otoqSL](https://amzn.to/3otoqSL)<br/>[https://amzn.to/3otoqSL](https://amzn.to/3otoqSL)<br/>if they are available to you I highly recommend going with the non-flexible couplers|2</br>2|1|7$|
|Metal rod 5mmx125mm (a little longer won’t cause any problems)|![enter image description here](https://i.postimg.cc/mDVghy6G/image.png)|[https://amzn.to/2Lzjy0b](https://amzn.to/2Lzjy0b)<br/>[https://amzn.to/3nSM61z](https://amzn.to/3nSM61z)|5<br/>10|2|12$|
|MK8 gears with filament groove|![enter image description here](https://i.postimg.cc/m2WTRqrF/image.png)|[https://amzn.to/3noCCuF](https://amzn.to/3noCCuF)|5|5|8$|
|Nema 17 stepper motor|![enter image description here](https://i.postimg.cc/tJ3QYqgn/image.png)|[https://amzn.to/3osSZbb](https://amzn.to/3osSZbb)|1|1|14$|
|Endstops|![enter image description here](https://i.postimg.cc/hG6Hszz7/image.png)|[https://amzn.to/3hWqekq](https://amzn.to/3hWqekq)|10|1|8|
|Idler springs|https://i.postimg.cc/RVdy8bJm/image.png|[https://shop.prusa3d.com/en/spare-parts/599-idler-spring.html](https://shop.prusa3d.com/en/spare-parts/599-idler-spring.html) <br/>[https://www.voxelfactory.com/collections/original-prusa-i3-mk2-mk2s-parts/products/replacement-tension-spring-for-prusa-i3-mk2s-or-mk3](https://www.voxelfactory.com/collections/original-prusa-i3-mk2-mk2s-parts/products/replacement-tension-spring-for-prusa-i3-mk2s-or-mk3)|1|2|4-8$|
|total|||||78$|



**Prebuild checks**

Before trying to build this upgrade, you should have a fully working printer, with a compatible mainboard (check below), with Marlin configured properly for a single extruder. You should get the Marlin source code from my GitHub repo: [https://github.com/PierreMasselot1/MMU2-on-any-printer](https://github.com/PierreMasselot1/MMU2-on-any-printer) (I will create a proper fork in the future and create a pull request so that we may have this upgrade in the actual official release of Marlin, but in order to do that I need to be at a more final and stable stage of development). Once you have Marlin configured for your printer before upgrading to the MMU keep a copy in a known location so that you can easily transition back to stock if the upgrade where to fail. After that, download the latest version of PrusaSlicer and follow this guide ([https://www.youtube.com/watch?v=Wz2Soog4HkQ&t=245s](https://www.youtube.com/watch?v=Wz2Soog4HkQ&t=245s) ) on how to set everything up for your printer in a single extruder mode. Once all off that is done download the latest files from my GitHub and start printing them using the methods and settings mentioned below. Check that you also have all the components and tools required.

**Motherboard compatibility**

Your mother board will need to have 5 dedicated stepper motor control (and in case of a dual Z make sure that your printer is using a splitter internally, meaning that you have 6 motor plugs available or use a splitter for your Z axis : [https://amzn.to/35fcFaS](https://amzn.to/35fcFaS) or [https://amzn.to/2L60ard](https://amzn.to/2L60ard) ). Once you have checked that your motherboard supports enough motor controls make sure that you have a way to access to at least two I/O pins: one for the endstop and one for the magnetic rotary encoder (will most likely be an AS5600 in I2C mode) that I am working on. You should also have some access to VCC and ground but even if there are no extra dedicated pins you could easily use one from any of the endstops. You will also need to make sure that you have access to 3.3V (or be ready to convert 5 to 3.3) but as I said your endstops may already have this available. If you have endstop pins for X,Y and Z max you should be good to go.

We are currently working with Paul Lewis to replace/ give the option to have a servo motor controlling the idler instead of a servo motor. This means that we will eventually need only 4 stepper motor control and a servo port (you will need a single free pin and some ways to get your servo connected to vcc and ground).

Mother board with extra endstops connector and easily accessible expansion pins will be the easiest to work with since less tweaking will have to be done to the Pins file of your specific board. If by any chance you were to modify something to fit your setup and think that it could be useful to other people, make sure to let me know and maybe do a pull request.

If your current motherboard isn’t compatible, changing your printer’s mainboard is an easy process and I recommend the SKR 1.4 or SKR PRO V1.1 boards if you are buying them specifically for this

**Printing**

Since we are currently working on the 3d files constantly, you will need to download the original files from GitHub and then convert them into an stl file in order to be able to print them. All the files are currently in .f3d which means that fusion 360 is needed in order to convert them. If you have any problem regarding the stl conversion message me and I will add the STLs in GitHub as well.

**Idler body, pulley body and merger:**

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

**For PrusaSlicer**

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

**Assembly:**

Assembly is relatively easy.

The first thing is to assemble the merger and check that it works properly as mentioned previously. It uses only PC4 M10 pneumatic couplers that you should be able to screw in by hand. You may need a bit more force for the end, but it should not take too much force otherwise you could strip the connectors and have to reprint the model.

![enter image description here](https://i.postimg.cc/zXw0vdnQ/image.png)

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

Attach each PC4-M6 couplers to the output of the MMU.
![enter image description here](https://i.postimg.cc/XqY751rg/image.png)

You then have to wire up the endstop for idler body, which you will then secure using M2*12 screws and nuts. It should be facing inward towards the center of the idler
![enter image description here](https://i.postimg.cc/SKbSdxXR/image.png)

Place a bearing on the end of the idler and pass it through the motor hole of the idler body. You will then be able to press fit it in the dedicated slot.
![enter image description here](https://i.postimg.cc/XJVVM1k0/image.png)
Once it is done insert the motor in the idler and secure it to the body using M3x8 screws. After this is done put M3x12 screws in the idler (in the heated inserts) and secure it to the motor. No need to tighten them extremely hard since you might rip out the inserts.

![enter image description here](https://i.postimg.cc/KjWFMGSZ/image.png)

After this is done check that the idler can properly rotate and triggers the endstop properly.

![enter image description here](https://i.postimg.cc/yYws68yj/image.png)

Assemble the idler body and pulley body as shown and insert the remaining metal rod through the dedicated holes.

![enter image description here](https://i.postimg.cc/MGwwR34j/image.png)

The amount of force required to insert the rods may vary depending on your print settings but I still need feedback regarding clearances so if you have a well calibrated printer let me know whether the clearances are right or whether I need to increase them.

![enter image description here](https://i.postimg.cc/5yXW1hHD/image.png)

You can now insert the spring and the screws: M3x(from 25 mm up to 35 mm) in order to tension the idler. For now idler tension will be made through trial and error but a good indicator is when you are able to open idler slightly and that the springs push it back in a closed position. I will add visual indicators in a later model as well as find other springs.

![enter image description here](https://i.postimg.cc/1565qFt2/image.png)

You will then need to mount the MMU to your printer. A mount for aluminum extrusions will be designed shortly but you will have to improvise for now, either design your own or use zip ties.

You can then connect the merger to the nozzle. Try to have about 5 cm of space in between so that the filament changes can be as fast as possible but not below 4 cm so that the ptfe tube bend isn’t too hard (potentially causing issues).

You can then connect each of the merger inputs to the MMU outputs making sure that the ptfe tubing is long enough to reach the extremities of the axis.

You are now done with the building process.

**Marlin configuration**

This needs to be done **after** you have successfully configured Marlin for a single extruder setup (You may have seen that in the configuration file there is a default of 3 extruders, but this should not cause any problems when setting up your printer for a single nozzle. If it does you can switch it back to one but remember that you need to switch it back to 3 when configuring for the multi-material upgrade).

![enter image description here](https://i.postimg.cc/HL0y4KLG/image.png)

This build guide is only for a bowden style setup but as you can see we will soon have support for direct drive. The Bowden tube length will vary depending on your setup but you should try to have it as short as possible since it will directly impact the filament change time

![enter image description here](https://i.postimg.cc/XqPGY6s5/image.png)

Remember to set your extrude_maxlength higher than your bowden tube length

![enter image description here](https://i.postimg.cc/9QZRCSZ4/image.png)

You should then enable XMAX plug (uncomment it by removing the //) since this is what we are going to be using to home the idler. If you board does not have an XMAX endstop you can find a free IO pin and connect your enstop to that, but you will need to configure an XMAX enstop inside your boards pins file similarly to what is shown below. If you need help with that step reach out to me on the discord server.
![enter image description here](https://i.postimg.cc/4NhnQM88/image.png)

You may also need to invert the endstop logic depending on your board. If the idler doesn’t home (considers the endstop as always triggered) this may be the problem. Usually this will be like your other endstops.

![enter image description here](https://i.postimg.cc/0N9QxN93/image.png)

You will also need to define driver type for each motor

![enter image description here](https://i.postimg.cc/BtWSzShm/image.png)

Similarly to your XYZ axis you can change the direction of the extruder stepper in order to match the expected behavior. If when homing the idler goes in the opposite direction you would change E1 dir to false(Or E x if you have setup custom extruder pins)
![enter image description here](https://i.postimg.cc/tgRxkknY/image.png)
You are now done with the software modifications.

**Slicer settings.**

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

**Tips to get a successful multicolor print.**

Idler tension is key to get good prints. If you see any extrusion discrepancies or under extrusion, then the fix will most likely be to increase idler tension.

If your filaments are all new, then it is recommended to turn on prime all printing extruders since it will shape all the filaments at the start of the print which will help you detect any problems at the beginning.

Another failure point that I have seen is on the coupler and the gears, if they are not tight enough, they will slip on the rod, resulting in under extrusion or even no extrusion in some cases.

The purge block is a huge waste of filament, but it can be adjusted based on the filament transition (transitioning from blue to cyan will require less purging that from black to white). Other things like wipe in object and wipe in infill can be enabled an optimized in order to reduce filament waste.

**Working on**

As I said this not a final version and I am working on multiple improvements. First off, use interface on the lcd to be easily able to load in new filaments, select a specific filament when working with a single extruder print.

I am also working on a filament sensor which would help a lot with filament load failures, filament jams, filament slipping in the extruder and would help a lot with the success rate of multicolor and single-color prints.

Servomotor controlled idler: no need for homing, more board compatibility since no stepper drivers required

A lot of nice to have features and complex multi-material 3d designs to demonstrate the capabilities of such multi-material upgrades, using different materials as well as some that are not supposed to bond well together (I have a few ideas of 3d printing processes that could fix that).

