
// This is free code released into the public domain.
// Drafted by Ángel in January 2019.
// Use it at your own risk. It might have bugs.
// angel.rodriguez@esne.edu

#include <SDL.h>
#include <cassert>
#include <Window.hpp>
#include <OpenGL.hpp>
#include <internal/initialize.hpp>

namespace banita
{

    Window::Window(const std::string & title, int width, int height, bool fullscreen)
    {
        window     = nullptr;
        gl_context = nullptr;

        if (initialize (SDL_INIT_VIDEO))
        {
            SDL_GL_SetAttribute (SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute (SDL_GL_CONTEXT_MINOR_VERSION, 2);

            window = SDL_CreateWindow
            (
                title.c_str (),
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                width,
                height,
                SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
            );

            assert(window != nullptr);

            if (window)
            {
                gl_context = SDL_GL_CreateContext (window);

                assert(gl_context != nullptr);

                if (gl_context && glt::initialize_opengl_extensions ())
                {
                    if (fullscreen)
                    {
                        SDL_SetWindowFullscreen (window, SDL_WINDOW_FULLSCREEN_DESKTOP);
                    }
                }
            }
        }
    }

    Window::~Window()
    {
        if (gl_context) SDL_GL_DeleteContext (gl_context);
        if (window    ) SDL_DestroyWindow    (window    );
    }

    void Window::enable_vsync ()
    {
        if (gl_context) SDL_GL_SetSwapInterval (1);
    }

    void Window::disable_vsync ()
    {
        if (gl_context) SDL_GL_SetSwapInterval (0);
    }

    unsigned Window::get_width () const
    {
        int width = 0, height;

        if (window) SDL_GetWindowSize (window, &width, &height);

        return unsigned(width);
    }

    unsigned Window::get_height () const
    {
        int width, height = 0;

        if (window) SDL_GetWindowSize (window, &width, &height);

        return unsigned(height);
    }

    bool Window::poll (Event & event) const
    {
        if (window)     // Aunque sería raro, puede llegar a ocurrir que no se haya conseguido crear la ventana...
        {
            // Se extrae un evento usando SDL y se convierte a un evento propio de
            // nuestro engine:

            SDL_Event sdl_event;

            if (SDL_PollEvent (&sdl_event) > 0)
            {
                switch (sdl_event.type)
                {
                    case SDL_QUIT:
                    {
                        event.type = Event::CLOSE;
                        break;
                    }

                    case SDL_KEYDOWN:
                    {
                        event.type = Event::KEY_PRESSED;
                        event.data.keyboard.key_code = Keyboard::translate_sdl_key_code (sdl_event.key.keysym.sym);
                        break;
                    }

                    case SDL_KEYUP:
                    {
                        event.type = Event::KEY_RELEASED;
                        event.data.keyboard.key_code = Keyboard::translate_sdl_key_code (sdl_event.key.keysym.sym);
                        break;
                    }
                }

                return true;
            }
        }

        return false;
    }

    void Window::clear () const
    {
        if (gl_context) glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Window::swap_buffers () const
    {
        if (gl_context) SDL_GL_SwapWindow (window);
    }

}
