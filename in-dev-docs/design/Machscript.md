# MachScript #

Machscript is an internal DSL that encapsulates c++ functionality similar to how php is a hyper processor of html
Machscript is a domain specific scripting langauage that will be used in the game. It is a superset of c++  but has extra constructs that extend c++ with meta programming features that do not exist. 
It has the constructs of Entity and Generator

if a generator is able to interprete the properties of a entity, it will convert the entity into a c++ construct

An entity is data that can be converted to various constructs in c++ based on a schema that can be parsed by a python script so that it can be either used to create a new c++ file or can be inserted into a c++ file at locations with certain comments

## Schema ##
The schema is an XML schema and the python CPP generator should be able to use this XML file to generate
- A class
- An ImGui Logger
- An Imgui Editor