
// This is free code released into the public domain.
// Drafted by Ángel in January 2019.
// Use it at your own risk. It might have bugs.
// angel.rodriguez@esne.edu

// SDL no soluciona del todo bien el problema de llamar a main() desde WinMain().
// Esta es una alternativa que funciona y no da problemas.

#if defined(_WIN32) || defined(_WIN64)

    #include <windows.h>

    extern int main (int , char ** );

    int WINAPI WinMain (HINSTANCE , HINSTANCE , LPSTR , INT )
    {
        return main (__argc, __argv);
    }

#endif
