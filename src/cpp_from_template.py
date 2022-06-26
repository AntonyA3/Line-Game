import re
from entity_to_class import *




f = open("src\\main.template.cpp", "r")

text = ""
for line in f.readlines():


    if len(re.findall("( *)//( *)<[*]Entity[*]>(.*)", line)) > 0:
        instruction = line.replace("//", "").replace("<*Entity*>", "").lstrip().rstrip().split(" ")
        if instruction[0] == "class":
            code = MakeClass(getJson(instruction[1]))._text
            text += code
    else:
        text += line

f.close()

f = open("src_gen\\main.cpp", "w")
f.write(text)
f.close()

# print(text)


