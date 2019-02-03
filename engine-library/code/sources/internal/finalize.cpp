
// This is free code released into the public domain.
// Drafted by Ángel in January 2019.
// Use it at your own risk. It might have bugs.
// angel.rodriguez@esne.edu

#include <SDL.h>

namespace banita
{

    /** Esta función se llamará automáticamente al salir de la función main() solo
      * si se inicializa algún subsistema de SDL.
      */
    void finalize ()
    {
        SDL_Quit ();
    }

}
