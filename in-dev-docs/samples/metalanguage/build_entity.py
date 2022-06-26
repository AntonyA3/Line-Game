
import re
f = open("in-dev-docs\samples\metalanguage\grid.entity", "r")

grid = {
    "name": "Grid",
    "types":[
        {
            "id": "glm::vec3", 
            "properties":[
                {"name": "position", "ops": ["get", "set", "log"]},
                {"name": "row_vector", "ops": ["get", "set", "log"]},
                {"name": "column_vector", "ops": ["get", "set", "log"]}
            ]
        },
        {
            "id" : "int",
            "properties":[
                {"name": "row_count", "ops": ["get", "set", "log"]},
                {"name": "column_count", "ops": ["get", "set", "log"]}
            ]
        },
        {
            "id": "bool",
            "properties":[
                {"name": "changed", "ops": ["is", "log"]}
            ]
        }
    ],
    "cons": "this->changed = false;",
    "afterAnySet": "this->changed = true;", 
    "publicMethods": [
        {"rtntype": "void", "scope" : "public", "name": "reset"}
    ]
}

def makeVariables(varList):
    text = ""
    for typ in varList:
        text = text + typ["id"]
        for i in range(len(typ["properties"])):
            var = typ["properties"][i]
            i
            text = text + " " + var["name"]
            if i < len(typ["properties"]) - 1:
                text = text + ","

        text = text + ";\n"
    return text

def makeConstructor(name, cons):
    return """
        {name}(){{
            {cons}
        }}

    """.format(name=name, cons=cons)

def snakeToCamelCase(wrd):
    wrd = [x for x in wrd]
    for i in range(len(wrd)):
        if i == 0:
            wrd[0] = wrd[0].upper()
        elif wrd[i - 1] == '_':
            wrd[i] = wrd[i].upper() 
    return ''.join([x for x in wrd if x != '_'])

def makeSetters(types, afterAnySet):
    text = ""
    for typ in types:
        for prop in typ["properties"]:
            if "set" in  prop["ops"]:
                temp_text = """
                    void set{name}({typId} {propName}){{
                        this->{propName} = {propName};
                        {afterAnySet}
                    }}
                """.format(afterAnySet=afterAnySet, propName= prop["name"], name= snakeToCamelCase(prop["name"]), typId=typ["id"])
                text = text + temp_text
    return text

def makeGetters(types):
    text = ""
    for typ in types:
        for prop in typ["properties"]:
            if "get" in  prop["ops"]:
                temp_text = """
                    {typId} get{name}(){{
                        return this->{propName};
                    }}
                """.format(propName= prop["name"], name= snakeToCamelCase(prop["name"]), typId=typ["id"])
                text = text + temp_text

    return text

def makeIssers(types):
    text = ""
    for typ in types:
        for prop in typ["properties"]:
            if "is" in  prop["ops"]:
                temp_text = """
                    bool is{name}(){{
                        return this->{propName};
                    }}
                """.format(propName= prop["name"], name= snakeToCamelCase(prop["name"]))
                text = text + temp_text
    return text


def makeEntity(entity):
    text =\
    """
    class {name} {{
        private:
        {makeVariables}
        public:
        {makeConstructor}
        {makeSetters}
        {makeGetters}
        {makeIssers}

    }};
    """.format(name=entity["name"], makeGetters=makeGetters(entity["types"]) , makeConstructor=makeConstructor(entity["name"], entity["cons"]) ,makeVariables=makeVariables(entity["types"]), makeIssers=makeIssers(entity["types"]) , makeSetters=makeSetters(entity["types"], entity["afterAnySet"]))
    return text


def makePropertiesLogger(refname, types):
    text = ""
 
    for typ in types:
        for prop in typ["properties"]:
            if (('log' and 'get') in prop["ops"]) or (('log' and 'is') in prop["ops"]):
       
                if ('log' and 'get') in prop["ops"]:
                    text = text + "{type} {prop} = {name}.get{propname}(); \n".format(type=typ["id"], name=refname.lower(), prop=prop["name"], propname=snakeToCamelCase(prop["name"])) 
                
                    text = text + "ImGui::Text(\"" + prop["name"]
                    if typ["id"] == "glm::vec3":
                        text = text + " %f %f %f" + "\", "
                        text = text + "{name}.x, {name}.y, {name}.z);".format(name=prop["name"])
                    if typ["id"] == "int":
                        text = text + " %d" + "\", "
                        text = text + "{name});".format(name=prop["name"])
                    text = text + ";" + "\n"
                elif ('log' and 'is') in prop["ops"]:
                    text = text + "bool {prop} = {name}.is{propname}();".format( name=refname.lower(), prop=prop["name"], propname=snakeToCamelCase(prop["name"])) 
                    text = text + "\nImGui::Text(\"" + prop["name"] + "%d\" , {refname}.is{name}());".format(refname=refname.lower(), name=snakeToCamelCase(prop["name"])) 





    return text

def makeImGuiLoggerForEntity(entity):
    text = \
    """
    void log({name}& {nameLowerCase}){{
        {makePropertiesLogger}

    }}
    """.format(name=entity["name"], nameLowerCase=entity["name"].lower(), makePropertiesLogger=makePropertiesLogger(entity["name"], entity["types"]))
    return text

classtext = makeEntity(grid)

loggertext = makeImGuiLoggerForEntity(grid)

f.close()


f = open("in-dev-docs\samples\metalanguage\grid.cpp", "w")
f.write(classtext)
f.write(" \n")
f.write(loggertext)
f.close()
