#include "ESDL.h"


ESDL_Window::ESDL_Window(int width,int height,std::string name,int SDL_renderer_flags,SDL_BlendMode SDL_blend_flag)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    win = SDL_CreateWindow(name.data(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    rend = SDL_CreateRenderer(win, -1, SDL_renderer_flags);
    surf = SDL_GetWindowSurface(win);

    time = std::chrono::high_resolution_clock::now();

    SDL_SetRenderDrawBlendMode(rend, SDL_blend_flag);
}


int ESDL_Window::GetKeys()
{
    if(event.type == SDL_KEYUP)
    {
        try
        {
            keyboard.at(event.key.keysym.sym) = false;
        }

        catch (const std::exception&)
        {
            keyboard.insert({event.key.keysym.sym,false});
        }
    }
    else
    {
        try
        {
            keyboard.at(event.key.keysym.sym) = true;
        }

        catch (const std::exception&)
        {
            keyboard.insert({event.key.keysym.sym,true});
        }
    }
    return 0;
}

int ESDL_Window::HandleSDLEvents()
{
    last_keyboard = keyboard;
    while (SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case(SDL_KEYDOWN):
                GetKeys();
            break;

            case(SDL_KEYUP):
                GetKeys();
            break;

            case(SDL_QUIT):
                quit = true;
            break;

            case(SDL_MOUSEMOTION):
                mouse_pos.x = event.motion.x;
                mouse_pos.y = event.motion.y;
            break;
        }
    }
    return 0;
}

int ESDL_Window::HandleKeys()
{
    if (keyboard[SDLK_LCTRL] & keyboard[SDLK_z])
        quit = true;
    if(keyboard[SDLK_b] & !last_keyboard[SDLK_b])
        debug = !debug;

    return 0;
}

int ESDL_Window::Update()
{
    HandleSDLEvents();
    HandleKeys();

    SDL_RenderPresent(rend);
    SDL_SetRenderDrawColor(rend,0,0,0,255);
    SDL_RenderClear(rend);
    delta_m = GetDeltaTime();
    delta = delta_m/1000;

    return 0;
}

float ESDL_Window::GetDeltaTime()
{
    std::chrono::time_point<std::chrono::system_clock> last_time = time;
    time = std::chrono::high_resolution_clock::now();

    float delta = std::chrono::duration_cast<std::chrono::microseconds>(time - last_time).count();

    return delta;
}
