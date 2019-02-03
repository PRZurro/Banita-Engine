
// This is free code released into the public domain.
// Drafted by Ángel in January 2019.
// Use it at your own risk. It might have bugs.
// angel.rodriguez@esne.edu

#include <SDL.h>
#include <cstdlib>

namespace banita
{

    extern void finalize ();

    /** Esta función se llama en aquellos lugares en los que se necesita
      * inicializar algún subsistema de SDL.
      */
    bool initialize (int subsystem)
    {
        // Se hace que al salir de la función main() se invoque automáticamente
        // a la función finalize() una vez:

        static bool finalize_is_not_set = true;

        if (finalize_is_not_set)
        {
            finalize_is_not_set = false;

            std::atexit (finalize);
        }

        // Se inicializa el subsistema si no estaba inicializado:

        if (!SDL_WasInit (subsystem))
        {
             return SDL_Init (subsystem) == 0;
        }

        return true;
    }

}
