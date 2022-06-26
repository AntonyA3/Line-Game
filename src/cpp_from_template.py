import re
from entity_to_class import *



import sys
# f = open("src\\main.template.cpp", "r")

files = sys.argv[1:]

def generateCppFiles(filePairs):
    for i in range(0,len(filePairs) - 1, 2):
        in_file = filePairs[i]
        out_file = filePairs[i + 1]
    
        f = open(in_file, "r")
        file_text = f.readlines()
        f.close()

        text = ""
        for line in file_text:
            if len(re.findall("( *)//( *)<[*]Entity[*]>(.*)", line)) > 0:
                instruction = line.replace("//", "").replace("<*Entity*>", "").lstrip().rstrip().split(" ")
                if instruction[0] == "class":
                    code = MakeClass(getJson(instruction[1]))._text
                    text += code
            else:
                text += line


        f = open(out_file, "w")
        f.write(text)
        f.close()

# print(text)


