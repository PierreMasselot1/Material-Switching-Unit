def toolChangeFromFile(filename):
    print('Temperature for the tool change in C?') 
    temp= int(input())
    print('Opening input Gcode file and creating output file TipTest.gcode')
    gcode = open(filename,'r')
    TipTest= open("TipTest.gcode",'w')
    
    lines=gcode.readlines()
    StartOfToolChange=False
    
    for line in lines:
        
        if StartOfToolChange==True:
            if "; Filament-specific end gcode " in line:
                TipTest.write(line)
                TipTest.write('G1 E-100\n')
                return
            TipTest.write(line)

        
        if "; toolchange #1" in line:
            print('starting to copy toolchange to ouput file')
            StartOfToolChange=True
            TipTest.write('M83\n')
            TipTest.write('M109 S'+str(temp)+'\n')
            TipTest.write('G28\n')
            TipTest.write('G1 Z50\n')#move up 50mm
            TipTest.write('T1\n')
            TipTest.write('G1 E15 F1000\n')
            
       

toolChangeFromFile('test.gcode')
end=input('Done! Press return key to close')