
// This is free code released into the public domain.
// Drafted by Ángel in January 2019.
// Use it at your own risk. It might have bugs.
// angel.rodriguez@esne.edu

#pragma once

#include <memory>
#include <string>
#include <internal/declarations.hpp>

namespace banita
{

    class Window;

    class Sample_Renderer
    {

        // Se crea un puntero a Render_Node porque al usar una declaración adelantada
        // para no exportar dependencias con esta cabecera, solo se pueden definir
        // punteros o referencias a los tipos declarados de modo adelantado.

        std::unique_ptr< glt::Render_Node > renderer;

        Window * window;

    public:

        Sample_Renderer(Window & given_window);

        /** En este caso es necesario definir explícitamente el destructor en el archivo
          * de implementación (CPP) para que el compilador pueda destruir el Render_Node.
          * Si se deja que el compilador cree un destructor por defecto en el programa
          * que use el engine, como solo tendrá una declaración adelantada, no sabrá cómo
          * destruirlo y ello dará lugar a un error de compilación.
          */
       ~Sample_Renderer();

        void render ();

    };

}
