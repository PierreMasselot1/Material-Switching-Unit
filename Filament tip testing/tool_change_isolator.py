import re

def toolChangeFromFile(filename):
    print('Temperature for the tool change in C?') 
    temp= int(input())
    print('Opening input Gcode file and creating output file TipTest.gcode')
    with open(filename, 'r') as gcode:
        lines=gcode.readlines()
    TipTest= open("TipTest.gcode",'w')
    startline= int(0)
    endline= int(0)
    testline= int(0)
    StartOfToolChange=False
    
    for line in lines:
        testline= testline + 1
        if StartOfToolChange==True:
            if "; Filament-specific end gcode" in line:
                endline= testline
                TipTest.write(line)
                TipTest.write(';Slicer generated Gcode end\n\n')
                TipTest.write(';Script generated Gcode begin\n')
                TipTest.write('G1 E-100\n')
                TipTest.write(';Script generated Gcode end\n\n')
                TipTest.write('; Original Gcode file start line: '+str(startline)+'\n')
                TipTest.write('; Original Gcode file end line: '+str(endline)+'\n')
                break
            TipTest.write(line)

        
        if "; toolchange #1" in line:
            startline= testline + 1
            print('starting to copy toolchange to ouput file')
            StartOfToolChange=True
            TipTest.write(';Script generated Gcode begin\n')
            TipTest.write('M83\n')
            TipTest.write('M109 S'+str(temp)+'\n')
            TipTest.write('G28\n')
            TipTest.write('G1 Z50\n')#move up 50mm
            TipTest.write('T1\n')
            TipTest.write('G1 E15 F1000\n')
            TipTest.write(';Script generated Gcode end\n\n')
            TipTest.write(';Slicer generated Gcode begin\n')
            
    testline= startline
    while True:
        if "; FILAMENT-SPECIFIC STARTING GCODE END" in lines[testline]:
            filament= re.sub(r'[;]', '', lines[testline - 4]) #use regular expressions to remove semicolons
            TipTest.write('; Filament profile name: '+filament+'\n')
            #print(filament)
            break;
        if testline== 1:
            TipTest.write('; No filament profile name found\n')
            break;
        testline -= 1
    
    StartOfFilamentParams=False
    for line in reversed(lines):
        if StartOfFilamentParams==True:
            if "; filament" not in line:
                break;
            TipTest.write(line)
        elif "; filament" in line:
            StartOfFilamentParams=True
            TipTest.write(line)
            
    TipTest.close()
    return
    
toolChangeFromFile('test.gcode')
end=input('Done! Press return key to close')