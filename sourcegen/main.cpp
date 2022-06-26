#include <iostream>

/*
    [Tag] C++ STLHeaders
    [Description] These are the header files that are required from C++
*/
#include <string>
#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <vector>
#include <array>
#include <stack>
#include <unordered_map>
#include <set>
#include <optional>
#include <deque>


/*
    [Tag] Includes headers for GLM
    [Notes] 
*/

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/euler_angles.hpp>


/*
    [Tag] SDL Header and Main Definition and GLEW
    [Description] Include Headers From SDL2
    [Notes] Requires MAKEFILE deps[-lSDL2 -lglu32 -lopengl32 -lglew32]
*/
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#define GLEW_STATIC
#include <GL/glew.h>


/*
    [Tag] Includes headers for DearImGui
    [Notes] Depends include headers for SDL and GLEW
*/
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"


/*
    [Tag] Screen Size  and Name Definitions
    [Notes] Replace this with a config file property
*/
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define WINDOW_NAME "Line Runner Game and Editor"


/*
    [Tag] LineModel Class
    [Description] Contains a 3D Solid model that can be rendered with OpenGl
*/

class MeshModel{
    GLuint vertex_buffer;
    GLuint index_buffer;
    int index_count;

    public:
    void clear(){
        this->index_count = 0;
    }

    void bindBuffers(){
        glBindBuffer(GL_ARRAY_BUFFER, this->vertex_buffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->index_buffer);

    }
    void init(){
        this->clear();
        glGenBuffers(1, &vertex_buffer);
        glGenBuffers(1, &index_buffer);
    }

    void remodel(float * verticies, int verticies_count, unsigned int * indicies, int indicies_count){
        glBufferData(GL_ARRAY_BUFFER, verticies_count * sizeof(float), verticies, GL_DYNAMIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies_count * sizeof(unsigned int), indicies, GL_DYNAMIC_DRAW);
        this->index_count = indicies_count;
    }

    int getIndexCount(){
        return this->index_count;
    }
};

// [Tag] Grid Classes
// [Description] Contains the properties of a grid and the observer that remodels the grid if changed is true;
// [Notes] Uses a graph of Fresh flag to manage it's invariants
// [Tag] I will use a script to generate the grid and it's logger, based on the contents of the file

class Grid{

  glm::vec3 position, row_vector, column_vector;
  int row_count, column_count;
  bool changed;

  public:


   Grid(){
     this->changed = false;
   }

   void setPosition(glm::vec3 position){
     this->position = position;
   }

   void setRowVector(glm::vec3 row_vector){
     this->row_vector = row_vector;
   }

   void setColumnVector(glm::vec3 column_vector){
     this->column_vector = column_vector;
   }

   void setRowCount(int row_count){
     this->row_count = row_count;
   }

   void setColumnCount(int column_count){
     this->column_count = column_count;
   }

   glm::vec3 getPosition(){
     return this->position;
   }

   glm::vec3 getRowVector(){
     return this->row_vector;
   }

   glm::vec3 getColumnVector(){
     return this->column_vector;
   }

   int getRowCount(){
     return this->row_count;
   }

   int getColumnCount(){
     return this->column_count;
   }

   bool isChanged(){
     return this->changed;
   }
};
// class Grid
// {
//     bool changed;
//     glm::vec3 position, row_vector, column_vector;
//     int row_count, column_count;

//     void onChanged(){
//         this->changed = true;
//     }

// public:

//     Grid(){
//         this->changed = true;
//     }

//     void setPosition(glm::vec3 position){
//         this->position = position;
//         this->onChanged();
//     }

//     void setRowVector(glm::vec3 row_vector){
//         this->row_vector = row_vector;
//         this->onChanged();
//     }

//     void setColumnVector(glm::vec3 column_vector){
//         this->column_vector = column_vector;
//         this->onChanged();
//     }

//     void setRowCount(int row_count){
//         this->row_count = row_count;
//         this->onChanged();
//     }

//     void setColumnCount(int column_count){
//         this->column_count = column_count;
//         this->onChanged();
//     }
    
//     glm::vec3 getPosition(){
//         return this->position;
//     }

//     glm::vec3 getRowVector(){
//         return this->row_vector;
//     }

//     glm::vec3 getColumnVector(){
//         return this->column_vector;
//     }

//     int getRowCount(){
//         return this->row_count;    
//     }

//     int getColumnCount(){
//         return this->column_count; 
//     }
    
//     void reset(){
//         this->changed = false;
//     }

//     bool isChanged(){
//         return this->changed;
//     }
// };




// [Tag] Player Class
// [Description] Contains the properties of the Games player object
// [Notes] In the future the player may not have a setter for position
class Player{
    glm::vec3 position;
    glm::mat4 model_matrix;
    
    public:
    glm::vec3 getPosition(){
        return this->position;
    }

    void setPosition(glm::vec3 position){
        this->position = position;
    }

    glm::mat4 getModelMatrix(){
        this->model_matrix = glm::translate(glm::mat4(1.0f), this->position);
        return this->model_matrix;
    }

};


// [Tag] LineModel Class
// [Description] Contains a 3D line list that can be rendered with openGL


class LineModel{
    private:
        GLuint vertex_buffer;
        int vertex_count;
    public:
    
    void init(){
        this->clear();
        glGenBuffers(1, &vertex_buffer);
    }

    void incrementLine(){
        this->vertex_count += 2;
    }

    int getVertexCount(){
        return this->vertex_count;
    }

    GLuint getVertexBuffer(){
        return this->vertex_buffer;
    }

    void clear(){
        this->vertex_count = 0;
    }
};


// [Tag] A template for creating classes that are Repo's
// [Note] Any object in a repo must have a default constructor
template<typename T> 
class Repo{
    std::vector<T> objects;
    
    public: 
    int size(){
        return objects.size();
    }

    T& getAt(int i){
        return objects.at(i);
    }

    void insert(){
        this->objects.push_back(T());
    }

    void insert(T object){
        this->objects.push_back(object);
    }

    T * refLast(){
        return &objects.at(objects.size() - 1);
    }
};


class LineModelRepo : public Repo<LineModel>{};
class GridRepo : public Repo<Grid>{};
    

// [Tag] The space that the player is able to traverse in the game
// [Description] Contains the properties of the game's play area mechanic
// Similar to the game blue spheres in sonic 3, whenever the player reaches a vertex on a Grid
// The direction of the player either doesn't change of or the player rotates 90 degrees left or right to change the direction
// This game is simuilar but diffrent, the sonic 3 blue sphere game used a 2D grid to do this, however my game has the same mechanic
// however it does this in a spartial dimension. Therefore rather than a 3D grid, a graph based data structure where each node has 0 to 4 references to other nodes
// or even use a grid on sections of the level that are completely in 2D
// or have the player be made to either jump or fall onto a noter grid or graph

// [Note] The Reference grid and the game grid, both use the same datatype
class PlaySpace{

    class Graph{
        class Node{
            Node * north_con;
            Node * south_con;
            Node * east_con;
            Node * west_con;

            bool hasWestCon(){
                return this->west_con != NULL;
            }

            bool hasEastCon(){
                return this->east_con != NULL;
            }

            bool hasNorthCon(){
                return this->north_con != NULL;
            }
            bool hasSouthCon(){
                return this->south_con != NULL;
            }
        };
        std::vector<Node> nodes;

    };

    std::vector<Grid> grids;
    std::vector<Graph> graphs;

    void addGrid(Grid grid){
        this->grids.push_back(grid);
    }

    


};

// [Tag] Viewport Classes
// [Description] Contains the properties of the viewport
// [Notes] 

class Viewport{
    int width;
    int height;
    bool changed;
    public:

    void init(int width, int height){
        this->width = width;
        this->height = height;
        this->changed = true;
    }

    int getWidth(){
        return this->width;
    }

    int getHeight(){
        return this->height;
    }

    void setDimensions(int width, int height){
        this->changed = (this->width != width) || (this->height != height);
        this->width = width;
        this->height = height;
    }

    bool isChanged(){
        return this->changed;
    }

    void reset(){
        this->changed = false;
    }
};




class ReferenceGrid{
    Grid * grid;
    LineModel * line_model;

    public:
    
    void init(Grid * grid, LineModel * line_model){
        this->grid = grid;
        this->line_model = line_model;
    }

    Grid& getGrid(){
        return *this->grid;
    }

    void update(){
        if(grid->isChanged()){
            Grid& grid = *this->grid;
            LineModel& line_model = *this->line_model;
            std::vector<float> verticies;

            line_model.clear();

            for(int i = 0; i <= grid.getRowCount(); i++){
                glm::vec3 point = grid.getPosition() + grid.getRowVector() * (float)i;
                verticies.insert(verticies.end(), {point.x, point.y, point.z, 1.0f, 1.0f, 1.0f});
                point = point + grid.getColumnVector() * (float)grid.getColumnCount();
                verticies.insert(verticies.end(), {point.x, point.y, point.z, 1.0f, 1.0f, 1.0f});
                line_model.incrementLine();

            }

            for(int i = 0; i <= grid.getColumnCount(); i++){
                glm::vec3 point = grid.getPosition() + grid.getColumnVector() * (float)i;
                verticies.insert(verticies.end(), {point.x, point.y, point.z, 1.0f, 1.0f, 1.0f});
                point = point + grid.getRowVector() * (float)grid.getRowCount();
                verticies.insert(verticies.end(), {point.x, point.y, point.z, 1.0f, 1.0f, 1.0f});
                line_model.incrementLine();
            }
            glBindBuffer(GL_ARRAY_BUFFER, line_model.getVertexBuffer());
            glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(float), &verticies.at(0), GL_DYNAMIC_DRAW);
        }
    }
};



// [Tag] Cursor Class
// [Description] Contains the properties of a camera
// [Notes] Uses a graph of Fresh flag to manage it's invariants

class Cursor{
    glm::vec2 target;
    glm::vec2 delta;

    public:
    void init(){

    }

    glm::vec2 getTarget(){
        return this->target;
    }

    glm::vec2 setTarget(glm::vec2 target){
        this->delta = target - this->target;
        this->target = target;

    }

    glm::vec2 getDelta(){
        return this->delta;
    }


};


// [Tag] Camera Class
// [Description] Contains the properties of a camera
// [Notes] Uses a graph of Fresh flag to manage it's invariants


//Pre Declared Camera


class Camera{
    class Freshness{
        Freshness * parent;
        bool fresh;

        public:
        Freshness(){
            this->parent = NULL;
        }

        void init(Freshness * parent){
            this->parent = parent;
        }

        void refresh(){
            this->fresh = true;
        }

        void defresh(){
            this->fresh = false;
            if(this->parent != NULL){
                this->parent->defresh();
            }
        }

        bool isFresh(){
            return this->fresh;
        }
    };

    float aspect_ratio, fov, near, far;
    glm::vec3 position, rotation;
    glm::mat4 translation_mat, rotation_mat, transformation_mat,
    view_mat, projection_mat, projection_view_mat,
    inverse_projection_view_mat;

    Freshness translation_mat_fresh, rotation_mat_fresh, transformation_mat_fresh,
    view_mat_fresh, projection_mat_fresh, projection_view_mat_fresh,
    inverse_projection_view_mat_fresh;
    
    void changedPosition(){
        this->translation_mat_fresh.defresh();
    }

    void changedRotation(){
        this->rotation_mat_fresh.defresh();
    }

    void changedProjection(){
        this->projection_mat_fresh.defresh();
    }

    public: 
    void init(){
        this->translation_mat_fresh.init(&this->transformation_mat_fresh);
        this->rotation_mat_fresh.init(&this->transformation_mat_fresh);
        this->transformation_mat_fresh.init(&this->view_mat_fresh);
        this->view_mat_fresh.init(&this->projection_view_mat_fresh);
        this->projection_mat_fresh.init(&this->projection_view_mat_fresh);
        this->projection_view_mat_fresh.init(&this->inverse_projection_view_mat_fresh);
    }

    void moveTo(glm::vec3 position){
        this->position = position;
        this->changedPosition();
    }

    void move(glm::vec3 velocity, float time){
        this->moveTo(this->getPosition() + velocity * time);
    }

    glm::vec3 getPosition(){
        return this->position;
    }

    void setRotation(glm::vec3 rotation){
        this->rotation = rotation;
        this->changedRotation();
    }

    glm::vec3 getRotation(){
        return this->rotation;
    }

    void setAspectRatio(float aspect_ratio){
        this->aspect_ratio = aspect_ratio;
        this->changedProjection();
    }

    float getAspectRatio(){
        return this->aspect_ratio;
    }

    void setFov(float fov){
        this->fov = fov;
        this->changedProjection();
    }

    float getFov(){
        return this->fov;
    }

    void setNear(float near){
        this->near = near;
        this->changedProjection();
    }

    float getNear(){
        return this->near;
    }

    void setFar(float far){
        this->far = far;
        this->changedProjection();
    }

    float getFar(){
        return this->far;
    }
    
    glm::mat4 getTranslationMatrix(){
        if(!this->translation_mat_fresh.isFresh()){
            this->translation_mat = glm::translate(glm::mat4(1.0f), this->position);
            this->translation_mat_fresh.refresh();
        }
        return this->translation_mat;
    }

    glm::mat4 getRotationMatrix(){
        if(!this->rotation_mat_fresh.isFresh()){
            glm::vec3 &rotation = this->rotation;
            this->rotation_mat = glm::yawPitchRoll(rotation.x, rotation.y, rotation.z);
            this->rotation_mat_fresh.refresh();
        }
        return this->rotation_mat;
    }

    glm::mat4 getTransformationMatrix(){
        if(!this->transformation_mat_fresh.isFresh()){
            this->transformation_mat = this->getTranslationMatrix() * this->getRotationMatrix();
            this->transformation_mat_fresh.refresh();
        }
        return this->transformation_mat;
    }

    glm::mat4 getViewMatrix(){
        if(!this->view_mat_fresh.isFresh()){
            this->view_mat = glm::inverse(this->getTransformationMatrix());
            this->view_mat_fresh.refresh();
        }
        return this->view_mat;
    }

    glm::mat4 getProjectionMatrix(){
        if(!this->projection_mat_fresh.isFresh()){
            this->projection_mat = glm::perspective(this->fov, this->aspect_ratio, this->near, this->far);
            this->projection_mat_fresh.refresh();
        }
        return this->projection_mat;
    }

    glm::mat4 getProjectionViewMatrix(){
        if(!this->projection_view_mat_fresh.isFresh()){
            this->projection_view_mat = this->getProjectionMatrix() * this->getViewMatrix();
            this->projection_view_mat_fresh.refresh();
        }
        return this->projection_view_mat;
    }

    glm::mat4 getInverseProjectionViewMatrix(){
        if(!this->inverse_projection_view_mat_fresh.isFresh()){
            this->inverse_projection_view_mat = glm::inverse(this->getProjectionViewMatrix());
            this->inverse_projection_view_mat_fresh.refresh();
        }
        return this->inverse_projection_view_mat;
    }

    glm::vec3 getRightVector(){
        return glm::vec3(this->getRotationMatrix() * glm::vec4(1, 0, 0, 1));      
    }

    glm::vec3 getUpVector(){
        return glm::vec3(this->getRotationMatrix() * glm::vec4(0, 1, 0, 1));      
    }

    glm::vec3 getForwardVector(){
        return glm::vec3(this->getRotationMatrix() * glm::vec4(0, 0, 1, 1));      

    }
};


// [Tag] ShaderProgram Class 
// [Description] Contain the attributes and vertex layout for a shader program

class ShaderProgram{
    struct VertexAttribute{
        int location;
        int size;
        int offset;
        GLenum datatype;
        GLenum normalized;
    };
    int vertex_size;
    GLuint program;
    std::vector<VertexAttribute> attributes;
    std::unordered_map<std::string, GLuint> uniform_attributes;
    public:
    void init(){
        this->program = glCreateProgram();
    }

    // [Note] Presumes that the verticies are floats
    void addVertexAttribute(int location, int size, GLenum normalized, int offset){
        attributes.push_back({location, size, offset, GL_FLOAT, normalized});
        attributes.shrink_to_fit();
        vertex_size += size * sizeof(float);
    }

    void addUniformAttribute(const char * name){
        this->uniform_attributes.emplace(std::pair<std::string, GLuint>(std::string(name), glGetUniformLocation(this->getProgram(), name)));
    }

    GLuint getUniformLocation(const char * name){
        return this->uniform_attributes.at(name);
    }
    void setUniformMatrix(const char * name, float * matrix){
        glUniformMatrix4fv(uniform_attributes.at(name), 1, GL_FALSE, (GLfloat *)matrix);
    }

    void useVertexAttributes(){
        for(int i = 0; i < attributes.size(); i++){
            glVertexAttribPointer(attributes.at(i).location, attributes.at(i).size, attributes.at(i).datatype, attributes.at(i).normalized, vertex_size, (void*) attributes.at(i).offset);
            glEnableVertexAttribArray(attributes.at(i).location);
        }
    }


    GLuint getProgram(){
        return this->program;
    }

    void use(){
        glUseProgram(this->program);
    }

};


// [Tag] InputButton Class properties
// [Description] Contains the properties of an input button
// [Notes] 


class InputButton
{    
    public:
    enum State{
        Pressed, Down, Released, Up
    };
    
    private:    
    InputButton::State state;
    const char * state_string;

    void updateStateString(){
        switch (this->state)
        {
        case State::Pressed:
            state_string = "Pressed";
            break;
        case State::Down:
            state_string = "Down";
            break;
        case State::Released:
            state_string = "Released";
            break;
        case State::Up:
            state_string = "Up";
            break;
        }
    }
    public:

    void init(){
        this->state = State::Up;
        this->state_string = "Up";
    }

    bool isPressed(){
        return this->state == State::Pressed;
    }    
    
    bool isDown(){
        return this->state == State::Down;
    }

    bool isPressedOrDown(){
        return (this->state == State::Pressed) || (this->state == State::Down);
    }

    bool isReleased(){
        return this->state == State::Released;
    }

    bool isUp(){
        return this->state == State::Up;
    }

    bool isReleasedOrUp(){
        return (this->state == State::Released) || (this->state == State::Up);
    }

    void onInputDown(){
        switch (this->state)
        {
        case State::Pressed:
        case State::Down:
            this->state = State::Down;
            break;
        case State::Released:
        case State::Up:
            this->state = State::Pressed;
            break;
        }
        this->updateStateString();

    }

    void onInputUp(){
        switch (this->state)
        {
        case State::Pressed:
        case State::Down:
            this->state = State::Released;
            break;
        case State::Released:
        case State::Up:
            this->state = State::Up;
            break;
        }
        this->updateStateString();
    }

    

    const char * getState(){
        return this->state_string;
    }
};


// [Tag] Logger Utility Class
// [Tag] Grid logger has been ticketed, the other loggers are unticketed tasks
namespace ImGuiLogger{
    void log(Grid& grid){
        if(ImGui::TreeNode("Grid")){
            glm::vec3 position = grid.getPosition();
            glm::vec3 row_vector = grid.getRowVector();
            glm::vec3 column_vector = grid.getColumnVector();
            int row_count = grid.getRowCount();
            int column_count = grid.getColumnCount();
            ImGui::Text("Position %f, %f, %f", position.x, position.y, position.z);
            ImGui::Text("Row Vector %f, %f, %f", row_vector.x, row_vector.y, row_vector.z);
            ImGui::Text("Column Vector %f, %f, %f", column_vector.x, column_vector.y, column_vector.z);
            ImGui::Text("Row Count %d", row_count);
            ImGui::Text("Column Count %d", column_count);
            ImGui::TreePop();
        }
    }

    void log(Camera& camera){
        if(ImGui::TreeNode("Camera")){
            ImGui::Text("Position %f, %f, %f", camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
            ImGui::Text("Rotation %f, %f, %f", camera.getRotation().x, camera.getRotation().y, camera.getRotation().z);
            ImGui::Text("AspectRatio %f", camera.getAspectRatio());
            ImGui::Text("Fov %f", camera.getFov());
            ImGui::Text("Near %f", camera.getNear());
            ImGui::Text("Far %f", camera.getFar());
            ImGui::Spacing();
            ImGui::Text("Translation Matrix %s", glm::to_string(camera.getTranslationMatrix()).c_str());
            ImGui::Text("Rotation Matrix %s", glm::to_string(camera.getRotationMatrix()).c_str());
            ImGui::Text("View Matrix %s", glm::to_string(camera.getViewMatrix()).c_str());
            ImGui::TreePop();
        }
    }

    void log(InputButton& button){
        if(ImGui::TreeNode("Button")){
            ImGui::Text("State %s", button.getState());
            ImGui::TreePop();
        }
    }

    void log(Cursor& cursor){
        if(ImGui::TreeNode("Cursor")){
            ImGui::Text("Target %f %f", cursor.getTarget().x, cursor.getTarget().y);
            ImGui::Text("Delta %f %f", cursor.getDelta().x, cursor.getDelta().y);

            ImGui::TreePop();
        }
    }

    void log(Player& player){
        if(ImGui::TreeNode("Player")){
            ImGui::Text("Position %f %f %f", player.getPosition().x, player.getPosition().y, player.getPosition().z);
            ImGui::Text("Model Matrix %s", glm::to_string(player.getModelMatrix()).c_str());
            ImGui::TreePop();
        }
    }     
};



namespace Glof{
    
    // [Tag] SDL_Poll Events
    // [Description] Both SDL and ImGui poll their events within the applications/ gameloop
    // [Notes] Should occur every render frame
    
    void pollSDL(){
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            switch (event.type)
            {
            case SDL_QUIT:
                exit(0);
                break;
            }
        }
    }
}


int main(int argc, char const *argv[])
{
    /*
        [Tag] Initialse SDL and OpenGL
    */

    SDL_Window *window;
    SDL_GLContext gl_context;
    SDL_Renderer *renderer;
    float screen_width = SCREEN_WIDTH;
    float screen_height = SCREEN_HEIGHT;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    window = SDL_CreateWindow(WINDOW_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (int)screen_width, (int)screen_height,
                              SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if (!window)
    {
        printf("Failed to open %d x %d window: %s\n", (int)screen_width, (int)screen_height, SDL_GetError());
        exit(1);
    }

    gl_context = SDL_GL_CreateContext(window);
    SDL_GL_SetSwapInterval(1);

    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_GL_MakeCurrent(window, gl_context);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }

    
    // [Tag] Initialse ImGui
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext(NULL);

    ImGuiIO& io = ImGui::GetIO(); 
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::StyleColorsDark(NULL);
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init("#version 150");

    /*
        [Tag] Hello Triangle Init
        [Notes] Requires OpenGL
    */

   /*
        [Tag] Compile the Shader
        [Notes] This should be seperated from main
    */
    static const char * camera_3d_shader_src = "#version 330 \n" 
    "uniform mat4 view_mat;\n"
    "uniform mat4 proj_mat;\n"
    "vec4 projectToCamera(vec4 pos){\n"
        "return proj_mat * view_mat * pos;\n"
    "}";

    static const char * model_render_shader_src =
    "uniform mat4 model_mat;\n"
    "vec4 transformToModel(vec4 pos){\n"
        "return model_mat * pos;\n"
    "}";


    static const char * vertex_shader_src = 
    "layout (location = 0) in vec3 vpos;\n"
    "layout (location = 1) in vec3 vcolor;\n"
    "out vec3 fcolor;\n"
    "void main(){\n"
        "fcolor = vcolor;\n"
        "gl_Position = projectToCamera(transformToModel(vec4(vpos, 1.0f)));\n"
    "}";

    static const char * fragment_shader_src = "#version 330 \n"
    "in vec3 fcolor;\n"
    "out vec4 color;\n"
    "void main(){\n"
        "color = vec4(fcolor, 1.0f);\n"
    "}";

    // [Note] The shader is buildt by joining these 3 files, maybe I should make a shader Builder

    const char *vertex_shader_srcs[] = {
        camera_3d_shader_src,
        model_render_shader_src,
        vertex_shader_src
    };

    // [Tag] Create Shader Program
    ShaderProgram flat_shader_program;
    flat_shader_program.init();
    flat_shader_program.addVertexAttribute(0, 3, GL_FALSE, 0);
    flat_shader_program.addVertexAttribute(1, 3, GL_FALSE, 3 * sizeof(float));


    {
        char info_buffer[1000];
        int info_length = 0;
        GLint compile_status;


        GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, 3, &vertex_shader_srcs[0], NULL);
        glCompileShader(vertex_shader);
        {
            glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &compile_status);
            if(compile_status != GL_TRUE){
                glGetShaderInfoLog(vertex_shader, 1000, &info_length, info_buffer);
                std::cout << info_buffer << std::endl;
            }
        }

        GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader, 1, &fragment_shader_src, NULL);
        glCompileShader(fragment_shader);
        {
            glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &compile_status);
            if(compile_status != GL_TRUE){
                glGetShaderInfoLog(fragment_shader, 1000, &info_length, info_buffer);
                std::cout << info_buffer << std::endl;
            }
        }
        {
            
            glAttachShader(flat_shader_program.getProgram(), vertex_shader);
            glAttachShader(flat_shader_program.getProgram(), fragment_shader);
            glLinkProgram(flat_shader_program.getProgram());
            glGetProgramiv(flat_shader_program.getProgram(), GL_LINK_STATUS, &compile_status);
            if(compile_status != GL_TRUE){
                glGetProgramInfoLog(flat_shader_program.getProgram(), 1000, NULL, info_buffer);
                std::cout << info_buffer << std::endl;

            }
            glDeleteShader(vertex_shader);
            glDeleteShader(fragment_shader);
        }

        // Get the Attibutes
        {
            int attribute_count;
            glGetProgramiv(flat_shader_program.getProgram(), GL_ACTIVE_ATTRIBUTES, &attribute_count);
            int floats_per_vertex = 0;
            for(int i = 0; i < attribute_count; i++){
                int name_size = 1000;
                char name[name_size];
                int name_length;
                int var_size;
                GLenum var_type;
                int size;
                glGetActiveAttrib(flat_shader_program.getProgram(), (GLuint)i, name_size, &name_length, &var_size, &var_type, name);
                int attrib_loc = glGetAttribLocation(flat_shader_program.getProgram(), name);
                int attrib_size = 0;
                if(var_type == GL_FLOAT_VEC3){
                    attrib_size = 3;
                }
                floats_per_vertex += attrib_size;
                //Print the Attribute details

                std::cout << "name: " << std::string(name) << std::endl;
                std::cout << "attribute location: " << attrib_loc << std::endl;
                if(var_type == GL_FLOAT_VEC3){
                    std::cout << "attribute size: " << attrib_size << std::endl;
                }
                std::cout << "var type: " << var_type << std::endl;
                std::cout << "var_size: " << var_size << std::endl << std::endl;
            }
                std::cout << "floats_per_vertex: " << floats_per_vertex << std::endl << std::endl;



        }
    }    
    
    flat_shader_program.addUniformAttribute("view_mat");
    flat_shader_program.addUniformAttribute("proj_mat");
    flat_shader_program.addUniformAttribute("model_mat");

    // [Tag] Make Hell Triangle Mesh
    MeshModel hello_triangle_model;
    hello_triangle_model.init();

    {
        float verticies[18] = {
            -0.5f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            -0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.5f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f
        };
        unsigned int indicies[3] = {
            0, 1, 2
        };
        hello_triangle_model.bindBuffers();
        hello_triangle_model.remodel(verticies, 18, indicies, 3);
    }

    // [Tag] Make Cube Mesh
    MeshModel cube_model;
    cube_model.init();
    {
        float verticies[144] = {
            //Front 
            1.0f, -1.0f, -1.0f,     1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, -1.0f,      1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, -1.0f,     1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, -1.0f,    1.0f, 1.0f, 1.0f,

            //Left
            -1.0f, -1.0f, -1.0f,    1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, -1.0f,     1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,      1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,      1.0f, 1.0f, 1.0f,
            
            //Right
            1.0f, -1.0f, 1.0f,      1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,       1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, -1.0f,      1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, -1.0f,     1.0f, 1.0f, 1.0f,
            
            //Top
            1.0f, 1.0f, -1.0f,      1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,       1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,      1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, -1.0f,     1.0f, 1.0f, 1.0f,

            //Back
            -1.0f, -1.0f, 1.0f,     1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,      1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,       1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,      1.0f, 1.0f, 1.0f,
            
            //Bottom
            -1.0f, -1.0f, -1.0f,    1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,     1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,      1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, -1.0f,     1.0f, 1.0f, 1.0f,        
        };
            
        unsigned int indicies[36] = {
            0, 1, 2,        0, 2, 3,
            4, 5, 6,        4, 6, 7,
            8, 9, 10,       8, 10, 11,
            12, 13, 14,     12, 14, 15,
            16, 17, 18,     16, 18, 19,
            20, 21, 22,     20, 22, 23
        };
        cube_model.bindBuffers();
        cube_model.remodel(verticies, 144, indicies, 36);   
    }

    // [Tag] Initialised the Grid and it's model
    // [Notes] In the future, The Line Model should be able to be updatad based on changes in the grid

    LineModelRepo line_models;
    line_models.insert();
    line_models.refLast()->init();

    GridRepo grids;
    grids.insert();
    grids.refLast()->reset();
    grids.refLast()->setPosition(glm::vec3(0, 0, 0));
    grids.refLast()->setRowVector(glm::vec3(1, 0, 0));
    grids.refLast()->setColumnVector(glm::vec3(0, 0, 1));
    grids.refLast()->setRowCount(32);
    grids.refLast()->setColumnCount(32);

    // Initialise the Player
    Player player;
    player.setPosition(glm::vec3(10, 0, 0));

    ReferenceGrid floor_grid;
    floor_grid.init(grids.refLast(), line_models.refLast());
    
    // [Tag] Initialised the Camera
    // [Notes] In the future, these might be set with Json

    Camera camera;
    camera.init();
    camera.moveTo(glm::vec3(0, 0, 0));
    camera.setRotation(glm::vec3(0, 0, 0));
    camera.setAspectRatio(1.0f);
    camera.setNear(0.1f);
    camera.setFar(100.0f);
    camera.setFov(M_2_PI);

    // [Tag] Initialised the Input
    // [Notes] In the future, these might be set with Json
    
    const unsigned char * keyboard_state = SDL_GetKeyboardState(NULL);
    InputButton forwardButton;
    forwardButton.init();
    InputButton backwardsButton;
    backwardsButton.init();
    InputButton leftButton;
    leftButton.init();
    InputButton rightButton;
    rightButton.init();

    //  [Tag] Gets the mouse state When initialising
    int mouse_x, mouse_y;
    int mouse_button_mask = SDL_GetMouseState(&mouse_x, &mouse_y);
    InputButton primaryButton;
    primaryButton.init();
    InputButton secondaryButton;
    secondaryButton.init();
    Cursor cursor;
    cursor.init();


    // [Tag] Initialise the viewport
    Viewport viewport;
    
    // [Tag] Render Loop
    // [Notes] For tasks that occur everytime rendering needs to occur

    
    
    while (true)
    {
        
        // [Tag] Update The Viewport
        // [Tag] reset the viewport change  
        // [Notes] Maybe there should be a list of resetable objects either a pointer to a delegated property or to a class with a reset function
        viewport.reset();
        {
            int width, height;
            SDL_GetWindowSize(window, &width, &height);
            viewport.setDimensions(width, height);
        }
        // [Tag] Update The Input Buttons

       if(keyboard_state[SDL_SCANCODE_W]){
           forwardButton.onInputDown();
       }else{
           forwardButton.onInputUp();
       }

       if(keyboard_state[SDL_SCANCODE_S]){
           backwardsButton.onInputDown();
       }else{
           backwardsButton.onInputUp();
       }

        if(keyboard_state[SDL_SCANCODE_A]){
            leftButton.onInputDown();
        }else{
            leftButton.onInputUp();
        }

        if(keyboard_state[SDL_SCANCODE_D]){
            rightButton.onInputDown();
        }else{
            rightButton.onInputUp();
        }
        
        //  [Tag] Gets the mouse state When Updating
        int mouse_x, mouse_y;
        int mouse_button_mask = SDL_GetMouseState(&mouse_x, &mouse_y);
        
        if(SDL_BUTTON_RMASK & mouse_button_mask){
            secondaryButton.onInputDown();
        }else{
            secondaryButton.onInputUp();
        }

        
        cursor.setTarget(glm::vec2(mouse_x, mouse_y));
        
        // [Tag] Camera Controller

        // [Tag] Update aspect ratio depending on viewport dimensions
        if(viewport.isChanged()){
            camera.setAspectRatio(viewport.getWidth() / (float)viewport.getHeight());
        }
        

        if(forwardButton.isPressedOrDown()){
            camera.move(camera.getForwardVector() * -10.0f, 1 / 60.0f);
        }else if(backwardsButton.isPressedOrDown()){
            camera.move(camera.getForwardVector() * 10.0f, 1 / 60.0f);
        }

        if(leftButton.isPressedOrDown()){
            camera.move(camera.getRightVector() * -10.0f, 1 / 60.0f);
        }else if(rightButton.isPressedOrDown()){
            camera.move(camera.getRightVector() * 10.0f, 1 / 60.0f);
        }

        if(secondaryButton.isPressedOrDown()){
            camera.setRotation(glm::vec3(camera.getRotation().x + cursor.getDelta().x * -1.0f / 60.0f, camera.getRotation().y + cursor.getDelta().y * 1.0f / 60.0f, 0.0f));
        }
        Glof::pollSDL();
         
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        bool show_demo_window = true;
        if (show_demo_window){
            ImGui::ShowDemoWindow(&show_demo_window);
        }

        
        // [Tag] ImGui Log Window
        // [Notes] These should be put in a method to build the log properties from a camera

        ImGui::Begin("Log", NULL, 0);

        ImGuiLogger::log(floor_grid.getGrid());
        ImGuiLogger::log(camera);
        ImGuiLogger::log(forwardButton);
        ImGuiLogger::log(cursor);
        ImGuiLogger::log(player);

        

        


        ImGui::End();
       
        // [Tag] ImGui Editor Window
        // [Notes] These should be put in a method to build the editor properties from a grid

        ImGui::Begin("Edit", NULL, 0);

        

        if(ImGui::TreeNode("Grid")){
            Grid& fg = floor_grid.getGrid();
            glm::vec3 position = fg.getPosition();
            glm::vec3 row_vector = fg.getRowVector();
            glm::vec3 column_vector = fg.getColumnVector();
            int row_count = fg.getRowCount();
            int column_count = fg.getColumnCount();

            if(ImGui::InputFloat3("Position", &position.x, "%.3f", 0)){
                fg.setPosition(position);
            }

            if(ImGui::InputFloat3("Row Vector", &row_vector.x, "%.3f", 0)){
                fg.setRowVector(row_vector);
            }

            if(ImGui::InputFloat3("Column Vector", &column_vector.x, "%.3f", 0)){
                fg.setColumnVector(column_vector);
            }

            if(ImGui::InputInt("Row Count", &row_count, 1, 8, 0)){
                fg.setRowCount(row_count);
            }

            if(ImGui::InputInt("Column Count", &column_count, 1, 8, 0)){
                fg.setColumnCount(column_count);
            }

            ImGui::TreePop();
        }

        ImGui::End();

        
        // [Tag] Update Grid Re modeller
        
        floor_grid.update();
        
        // Main rendering Stage
        glViewport(0, 0, viewport.getWidth(), viewport.getHeight());
        glClearColor(0.5f, 0.5, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // [Tag] Render Hello Triangle
        flat_shader_program.use();
        hello_triangle_model.bindBuffers();

        // [Note] Not all shaders will have these properties
        flat_shader_program.setUniformMatrix("proj_mat", &camera.getProjectionMatrix()[0][0]);
        flat_shader_program.setUniformMatrix("view_mat", &camera.getViewMatrix()[0][0]);
        {
            glm::mat4 identity = glm::mat4(1.0f);
            flat_shader_program.setUniformMatrix("model_mat", &identity[0][0]);
        }

        // [Note] Not all meshModels will have this vertex layout
        flat_shader_program.useVertexAttributes();
        
        glDrawElements(GL_TRIANGLES, hello_triangle_model.getIndexCount(), GL_UNSIGNED_INT, 0);

        // [Tag] Render cube model player place holder
        // [Note] This has been duplicated, maybe I should create a class called vertex layout
        cube_model.bindBuffers();
        flat_shader_program.setUniformMatrix("model_mat", &player.getModelMatrix()[0][0]);

        flat_shader_program.useVertexAttributes();
        glDrawElements(GL_TRIANGLES, cube_model.getIndexCount(), GL_UNSIGNED_INT, 0);


        {
            glm::mat4 identity = glm::mat4(1.0f);
            flat_shader_program.setUniformMatrix("model_mat", &identity[0][0]);
        }

        // [Tag] Render Floor Grid
        for(int i = 0; i < line_models.size(); i++){
            
            glBindBuffer(GL_ARRAY_BUFFER, line_models.getAt(i).getVertexBuffer());
            flat_shader_program.setUniformMatrix("proj_mat", &camera.getProjectionMatrix()[0][0]);
            flat_shader_program.setUniformMatrix("view_mat", &camera.getViewMatrix()[0][0]);

            flat_shader_program.useVertexAttributes();

            glDrawArrays(GL_LINES, 0, line_models.getAt(i).getVertexCount());
        }
        

        //ImGui Final Stage
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        //Frame Swap
        SDL_GL_SwapWindow(window);
    }

    return 0;
}
