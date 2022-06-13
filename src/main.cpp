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
#include <map>
#include <set>
#include <optional>
#include <deque>

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


namespace Glof{
    /*
        [Tag] SDL_Poll Events
        [Description] Both SDL and ImGui poll their events within the applications/ gameloop
        [Notes] Should occur every render frame
    */
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

    /*
        [Tag] Initialse ImGui
    */
    IMGUI_CHECKVERSION();
    ImGui::CreateContext(NULL);

    ImGuiIO& io = ImGui::GetIO(); 
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::StyleColorsDark(NULL);
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init("#version 150");

    /*
        [Tag] Render Loop
        [Notes] For tasks that occur everytime rendering needs to occur
    */
    while (true)
    {
        Glof::pollSDL();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        bool show_demo_window = true;
        if (show_demo_window){
            ImGui::ShowDemoWindow(&show_demo_window);
        }

        // Main rendering Stage
        glViewport(0, 0, screen_width, screen_height);
        glClearColor(0.5f, 0.5, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        //ImGui Final Stage
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        //Frame Swap
        SDL_GL_SwapWindow(window);
    }

    return 0;
}
