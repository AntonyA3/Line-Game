import re
import json
import sys

files = sys.argv[1:]

def getJson(file):
    f = open(file, "r")
    text = f.readlines()
    return json.loads(''.join(text))

def snakeCaseToCamelCase(wrd):
    wrd = [x for x in wrd]
    for i in range(len(wrd)):
        if i == 0:
            wrd[0] = wrd[0].upper()
        elif wrd[i - 1] == '_':
            wrd[i] = wrd[i].upper() 
    return ''.join([x for x in wrd if x != '_'])


class MakeRepo:
    _entity = {}
    _text = """"""

    def __init__(self, entity):
        self._entity = entity
        self._text += "class {name}Repo : public Repo<{name}>{{}};\n".format(name=self._entity["name"])



class MakeImGuiLog:
    _entity = {}
    _text = """"""


    def __init__(self, entity):
        self._entity = entity
        self._text += "void log({name}& {nameLower}){{\n".format(name=entity["name"], nameLower=entity["name"].lower())
        for typ in entity["types"]:
            for prop in typ["properties"]:
                if ('log' in prop["ops"] and 'get' in prop["ops"]) or ('log' in prop["ops"] and 'is' in prop["ops"]):
                    if ('log' and 'get') in prop["ops"]:

                        self._text += "  " + "{type} {prop} = {name}.get{propname}(); \n".format(type=typ["id"], name=entity["name"].lower(), prop=prop["name"], propname=snakeCaseToCamelCase(prop["name"])) 
                    
                        self._text = self._text + "  "+ "ImGui::Text(\"" + prop["name"]
                        if typ["id"] == "glm::vec3":
                            self._text = self._text + " %f %f %f" + "\", "
                            self._text = self._text + "{name}.x, {name}.y, {name}.z);".format(name=prop["name"])
                        if typ["id"] == "int":
                            self._text = self._text + " %d" + "\", "
                            self._text = self._text + "{name});".format(name=prop["name"])
                        if typ["id"] == "float":
                            self._text = self._text + " %f" + "\", "
                            self._text = self._text + "{name});".format(name=prop["name"])
                        self._text = self._text + ";" + "\n"
                    elif ('log' and 'is') in prop["ops"]:
                        self._text = self._text + "bool {prop} = {name}.is{propname}();".format( name=entity["name"].lower(), prop=prop["name"], propname=snakeCaseToCamelCase(prop["name"])) 
                        self._text = self._text + "\nImGui::Text(\"" + prop["name"] + "%d\" , {refname}.is{name}());".format(refname=entity["name"].lower(), name=snakeCaseToCamelCase(prop["name"])) 
        self._text += "\n}"



class MakeClass:
    _entity = {}
    _text = """"""

    def __init__(self, entity):
        self._entity = entity
        self.evaluate()

    def makeConstructor(self):
        return {
            "definition" : "{name}(){{".format(name=self._entity["name"]),
            "code" :"{cons}".format(cons=self._entity["cons"]),
        }


    def makeSetters(self):
        setters = []
        for typ in self._entity["types"]:
            for prop in typ["properties"]:
                if "set" in  prop["ops"]:
                    func_def = {
                        "definition" : "void set{funcSuffix}({typeId} {argName}){{".format(typeId=typ["id"], argName=prop["name"], funcSuffix=snakeCaseToCamelCase(prop["name"])),
                        "code" : "this->{argName} = {argName};".format(argName=prop["name"]) 
                    }
                    setters.append(func_def)
        return setters

    def makeGetters(self):
        getters = []
        for typ in self._entity["types"]:
            for prop in typ["properties"]:
                if "get" in  prop["ops"]:
                    func_def = {
                        "definition" :"{typeId} get{funcSuffix}(){{".format(typeId=typ["id"], funcSuffix=snakeCaseToCamelCase(prop["name"])),
                        "code" : "return this->{argName};".format(argName=prop["name"])
                    }
                    getters.append(func_def)

        return getters


    def makeIssers(self):
        issers = []
        for typ in self._entity["types"]:
            for prop in typ["properties"]:
                if "is" in  prop["ops"]:
                    func_def = {
                        "definition" :"bool is{funcSuffix}(){{".format(funcSuffix=snakeCaseToCamelCase(prop["name"])),
                        "code" : "return this->{argName};".format(argName=prop["name"])
                    }
                    issers.append(func_def)
        return issers
    

    def makeVariables(self):
        varList = self._entity["types"]
        textList = []
        for typ in varList:
            text = typ["id"]
            for i in range(len(typ["properties"])):
                var = typ["properties"][i]
                i
                text = text + " " + var["name"]
                if i < len(typ["properties"]) - 1:
                    text = text + ","
            textList.append(text)

        return textList

    # [Tag] I need to actually Consider methods with arguments
    def makePublicFunc(self):
        funcs = []
        for method in self._entity["publicMethods"]:
            func_def = {
                "definition" : "{rtntype} {name}(){{".format(rtntype=method["rtntype"], name=method["name"]),
                "code" : "{code}".format(code=method["code"])
            }
            funcs.append(func_def)
        return funcs
            

    def evalFunc(self, func):
        self._text += "\n   " + func["definition"] + "\n"
        self._text += "     " + func["code"] + "\n"
        self._text += "   }\n"

    def evalFuncList(self, funcList):
        for func in funcList:
            self.evalFunc(func)
            

    def evaluate(self):
        self._text = """class {name}{{\n""".format(name=self._entity["name"])
        self._text += "\n"
        for line in self.makeVariables():
            self._text += "  " + line + ";\n"
        self._text += "\n"

        self._text += "  public:\n\n"

        if "cons" in self._entity:
            self.evalFunc(self.makeConstructor())
            
        self.evalFuncList(self.makeSetters())
        self.evalFuncList(self.makeGetters())
        self.evalFuncList(self.makeIssers())
        self.evalFuncList(self.makePublicFunc())
        self._text += "};"



def generateCppFiles(filePairs):
    for i in range(0,len(filePairs) - 1, 2):
        in_file = filePairs[i]
        out_file = filePairs[i + 1]
    
        f = open(in_file, "r")
        
        file_text = f.readlines()
        f.close()

        text = ""
        make_class_pattern ="<MakeClass>\(.*\)"
        arg_pattern = "(?<=[(])(.*)(?=[)])"
        for line in file_text:
            if re.search(make_class_pattern, line):
                pattern = re.findall(make_class_pattern, line)[0]
                file = re.findall(arg_pattern, line)[0]
                code = MakeClass(getJson(file))._text
                text += line.replace(pattern, code)
            # elif re.search("(<( *)MakeRepo( *)>)", line):
            #     file_src = re.findall("(?<=[(])(.*)(?=[)])", line)[0]
            #     code = MakeRepo(getJson(file_src))._text
            #     text += code
            # elif re.search("<( *)MakeImGuiLogger( *)>", line):
            #     file_src = re.findall("(?<=[(])(.*)(?=[)])", line)[0]
            #     code = MakeImGuiLog(getJson(file_src))._text
            #     text += code
            else:
                text += line


        f = open(out_file, "w")
        f.write(text)
        f.close()

generateCppFiles(files)


