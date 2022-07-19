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



    #First print all relevant information as comments on top of the file
    for line in lines:

        if "; FILAMENT-SPECIFIC STARTING GCODE END" in line and line-4>=0:
            filament= re.sub(r'[;]', '', lines[line - 4]) #use regular expressions to remove semicolons
            TipTest.write('; Filament profile name: '+filament+'\n')
            
        if "; filament" in line:
            TipTest.write(line)
    
    
    testline=0 #resest focused line
    TipTest.write('\n')


    #Actually go through the gcode and extract the toolchange sequence
    for line in lines:
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
            
    TipTest.close()
    return
    
toolChangeFromFile('test.gcode')
end=input('Done! Press return key to close')