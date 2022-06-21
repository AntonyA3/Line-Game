# Camera #

A camera contains the intrinsic properties of a camera that can be changed freely like the position and the rotation. A camera has other properties such as the view matrix, which both depend on whether the position or the rotation has changed. However 

Gettable and Settable Properties
- Position
- Rotation
- Aspect Ratio
- Field of View
- near
- far

# Update Tree

- inverse_projection_view
    - projection_view
        - projection_matrix
            - aspect ratio
            - field of view
            - near
            - far
        - view_matrix
            - transformation_matrix
                - translation_matrix
                    - position
                - rotation_matrix
                    - rotation

# Storing The Dirty Flag
I was considering using a tree, however I should have a Graph, where each property will be represented as a Vertex of the graph. This vertex will have a reference to it; parents and references to its children
- The dirty flag can be propogated from child to parent/
- if a property is dirty, the properties children would need to be cleaned.
- a better name will be (fresh)

# Steps Taken To make camera
a: Added Position as a vector 3
b: Added Rotation as a vector 3
c: Added Translation Matrix
d:  glm::vec3 position (getter and setter)
    glm::vec3 rotation (getter and setter)
    glm::mat4 translation (getter)
e: bool for translation fress flag
f: create a constructor that will create the invarient graph
g: While working through this I was able to think of a better way to represent the propagation of (fresh) flags



- on position change
    - translation not fresh
    - view matrix not fresh
    - projection_view not fresh
    - inverse matrix not fresh

- on rotation change
    - rotation_matrix  not fresh

- When the public entities change, it sets all the properties that depend on it as false;
- Whe I use a getter to get the properties, if it is false, it recalculates the properties, by using the properties getters, recursivelly cleaning the properties as it uses them.

- predeclare the camera
- I created sub classes within the camera, to manage the invarients of each of the properties in the camera, as if it was a tree;
- Each references the properties of it's children. objects that are used in calculations;
- Each reference a property called freshness which is propagated 
- However the design is wrong undortunately.
- I will therefore create a new design by decoupling the properties themselfs, away from the freshness
- I will see if there is a syntax error
- I will set the camera properties pre parsing

- I need to get forward vector
- Change the camera setPosition function to a moveTo function