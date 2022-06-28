from pydoc import classname
import xml.etree.ElementTree as ET

def snakeCaseToCamelCase(wrd):
    wrd = [x for x in wrd]
    for i in range(len(wrd)):
        if i == 0:
            wrd[0] = wrd[0].upper()
        elif wrd[i - 1] == '_':
            wrd[i] = wrd[i].upper() 
    return ''.join([x for x in wrd if x != '_'])

class CppCodeGenerator:
    _entity = None
    _text = ""
    def __init__(self, xmlFile):
        self._entity = ET.parse(xmlFile).getroot()
        self._class_name = self._entity.get("name")
        self._private_properties_group = self._entity.findall("privateProperties/propGroup")
        self._private_properties = self._entity.findall("privateProperties/prop")
        self._init_method = self._entity.find("initMethod")
        self._public_methods = self._entity.findall("publicMethods/func")
        self._gettable_properties = []
        self._code_padding = 8
        for prop in self._private_properties:
            if prop.find("get") is not None:
                self._gettable_properties.append(prop)

    def begin(self):
        self._text = ""
        return self

    def appendName(self):
        self._text += self._entity.get("name")
        return self

    def codeFormat(self, code, start_padding):
        lines = [x for x in code.split("\n") if len(x.lstrip()) > 0]
        lines_stripped = [x.lstrip() for x in code.split("\n") if len(x.lstrip()) > 0]
        padding = [len(x) - len(x.lstrip()) for x in lines]
        min_padding = 10000
        for line in lines:
            pd =  len(line) - len(line.lstrip())
            if pd < min_padding:
                min_padding = pd
        ''
        delta_padding = [pad - min_padding for pad in padding]

        
        code = ''.join(" " * (start_padding + delta_padding[i]) + lines_stripped[i] + "\n" for i in range(len(lines_stripped)))
        return code

    def makeMethod(self, method, rtnType, name, args = None):
        arg_text = ""
        if args is not None:            
            for arg in args.findall("param"):
                arg_text += "{type} {name},".format(type=arg.get("type"), name=arg.get("name"))
            if len(arg_text) > 0:
                arg_text = arg_text[0: len(arg_text) - 1]
            
        self._text += "    {rtntype} {name}({args}){{\n".format(rtntype=rtnType, name=name, args=arg_text)
        self._text += self.codeFormat(method.find("code").text, self._code_padding)
        self._text += "    }\n\n"


    def appendClass(self):
        self._text += "class {classname} {{\n".format(classname=self._class_name)
        self._text += "private:\n"

        for propGroup in self._private_properties_group:
            name_text = '    {type}'.format(type=propGroup.get("type")) + ' ' + ''.join([x.get("name") + ', ' for x in propGroup.findall("prop")])
            if len(name_text) > 0:
                name_text = name_text[0 : len(name_text) - 2] + ";"
            self._text += name_text + "\n"

        for prop in self._private_properties:
            self._text += "    {type} {names};\n".format(type=prop.get("type"), names=prop.get("name"))


        self._text += "public:\n"

        if self._init_method is not None :
            self.makeMethod(self._init_method, self._init_method.get("rtntype"), "init",)
         
        for method in self._public_methods:
            self.makeMethod(method, method.get("rtntype"), method.get("name"), method.find("arguments"))
            

        # Generate getters
        for prop in self._gettable_properties:
            self._text += "    {type} get{suffix}({type} {name}){{\n".format(type=prop.get("type"), name = prop.get("name"), suffix=snakeCaseToCamelCase(prop.get("name")))
            self._text += "        return this->{name};\n".format(name = prop.get("name"))
            self._text += "    }\n"
        self._text += "};\n"
       
        return self




print(CppCodeGenerator("src\\xml\\mesh_model.xml").begin().appendClass()._text)