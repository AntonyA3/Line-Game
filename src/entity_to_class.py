import json


def getJson(file):
    f = open(file, "r")
    return json.loads(''.join(f.readlines()))



def snakeCaseToCamelCase(wrd):
    wrd = [x for x in wrd]
    for i in range(len(wrd)):
        if i == 0:
            wrd[0] = wrd[0].upper()
        elif wrd[i - 1] == '_':
            wrd[i] = wrd[i].upper() 
    return ''.join([x for x in wrd if x != '_'])



class MakeClass:
    _entity = {}
    _text = """"""

    def __init__(self, entity):
        self._entity = entity
        self.evaluate()

        print("make class")

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
            
            # "definition" :"bool is{funcSuffix}(){{".format(funcSuffix=snakeCaseToCamelCase(prop["name"])),
            #             "code" : "return this->{argName};".format(argName=prop["name"])

            # {"rtntype": "void", "name": "reset", "code": "this->changed = false;"}
    



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

