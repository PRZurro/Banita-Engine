
// This is free code released into the public domain.
// Drafted by Ángel in January 2019.
// Use it at your own risk. It might have bugs.
// angel.rodriguez@esne.edu


#include "Keyboard.hpp"

#include <SDL_keyboard.h>


namespace banita
{
	Keyboard::Keyboard() : state(SDL_GetKeyboardState(nullptr)){}

    Keyboard::Key_Code Keyboard::translate_sdl_key_code (int sdl_key_code)
    {
        // Se podría hacer un array de traducción directa, pero con la sentencia
        // switch el compilador lo hará por nosotros de un modo transparente y
        // de sobra eficiente.

        switch (sdl_key_code)
        {
            case SDLK_RETURN:       return KEY_RETURN;
            case SDLK_ESCAPE:       return KEY_ESCAPE;
            case SDLK_BACKSPACE:    return KEY_BACKSPACE;
            case SDLK_TAB:          return KEY_TAB;
            case SDLK_SPACE:        return KEY_SPACE;

            case SDLK_a:            return KEY_A;
            case SDLK_b:            return KEY_B;
            case SDLK_c:            return KEY_C;
            case SDLK_d:            return KEY_D;
            case SDLK_e:            return KEY_E;
            case SDLK_f:            return KEY_F;
            case SDLK_g:            return KEY_G;
            case SDLK_h:            return KEY_H;
            case SDLK_i:            return KEY_I;
            case SDLK_j:            return KEY_J;
            case SDLK_k:            return KEY_K;
            case SDLK_l:            return KEY_L;
            case SDLK_m:            return KEY_M;
            case SDLK_n:            return KEY_N;
            case SDLK_o:            return KEY_O;
            case SDLK_p:            return KEY_P;
            case SDLK_q:            return KEY_Q;
            case SDLK_r:            return KEY_R;
            case SDLK_s:            return KEY_S;
            case SDLK_t:            return KEY_T;
            case SDLK_u:            return KEY_U;
            case SDLK_v:            return KEY_V;
            case SDLK_w:            return KEY_W;
            case SDLK_x:            return KEY_X;
            case SDLK_y:            return KEY_Y;
            case SDLK_z:            return KEY_Z;

            case SDLK_0:            return KEY_0;
            case SDLK_1:            return KEY_1;
            case SDLK_2:            return KEY_2;
            case SDLK_3:            return KEY_3;
            case SDLK_4:            return KEY_4;
            case SDLK_5:            return KEY_5;
            case SDLK_6:            return KEY_6;
            case SDLK_7:            return KEY_7;
            case SDLK_8:            return KEY_8;
            case SDLK_9:            return KEY_9;

			
			case SDLK_UP:			return KEY_ARROW_UP;
			case SDLK_DOWN:			return KEY_ARROW_DOWN;
			case SDLK_RIGHT:		return KEY_ARROW_LEFT;
			case SDLK_LEFT:			return KEY_ARROW_RIGHT;
			

            // ...
        }
        return KEY_UNKOWN;
    }

	int Keyboard::translate_key_code_sdl(Key_Code _key)
	{
		switch (_key)
		{
            case KEY_ESCAPE:            return SDLK_ESCAPE;
            case KEY_RETURN:            return SDLK_RETURN;         
            case KEY_BACKSPACE:         return SDLK_BACKSPACE;
            case KEY_TAB:               return SDLK_TAB;
            case KEY_SPACE:             return SDLK_SPACE;  
        
            case KEY_A:                 return SDLK_a;
            case KEY_B:                 return SDLK_b;
            case KEY_C:                 return SDLK_c;
            case KEY_D:                 return SDLK_d;
            case KEY_E:                 return SDLK_e;
            case KEY_F:                 return SDLK_f;
            case KEY_G:                 return SDLK_g;
            case KEY_H:                 return SDLK_h;
            case KEY_I:                 return SDLK_i;
            case KEY_J:                 return SDLK_j;
            case KEY_K:                 return SDLK_k;
            case KEY_L:                 return SDLK_l;
            case KEY_M:                 return SDLK_m;
            case KEY_N:                 return SDLK_n;
            case KEY_O:                 return SDLK_o;
            case KEY_P:                 return SDLK_p;
            case KEY_Q:                 return SDLK_q;
            case KEY_R:                 return SDLK_r;
            case KEY_S:                 return SDLK_s;
            case KEY_T:                 return SDLK_t;
            case KEY_U:                 return SDLK_u;
            case KEY_V:                 return SDLK_v;
            case KEY_W:                 return SDLK_w;
            case KEY_X:                 return SDLK_x;
            case KEY_Y:                 return SDLK_y;
            case KEY_Z:                 return SDLK_z;
        
            case KEY_0:                 return SDLK_0;
            case KEY_1:                 return SDLK_1;
            case KEY_2:                 return SDLK_2;
            case KEY_3:                 return SDLK_3;
            case KEY_4:                 return SDLK_4;
            case KEY_5:                 return SDLK_5;
            case KEY_6:                 return SDLK_6;
            case KEY_7:                 return SDLK_7;
            case KEY_8:                 return SDLK_8;
            case KEY_9:                 return SDLK_9;

			case KEY_ARROW_UP:			return SDLK_UP;
			case KEY_ARROW_DOWN:		return SDLK_DOWN;
			case KEY_ARROW_LEFT:		return SDLK_RIGHT;
			case KEY_ARROW_RIGHT:		return SDLK_LEFT;
			// ...
		}

		return KEY_UNKOWN;
	}

	Keyboard::Bool_Vector Keyboard::get_state_of_keys(std::vector<Key_Code>& _keys)
	{
		std::vector<bool> tempVector;

		for (auto & key : _keys)
		{
			tempVector.push_back(check_state_of_key(key));
		}

		return tempVector;
	
	}

	Keyboard::KC_Vector Keyboard::get_pressed_keys(KC_Vector & _keys)
	{
		{
			Bool_Vector tempVector = get_state_of_keys(_keys);
			KC_Vector tempKeyCodeV;

			for (size_t i = 0; i < _keys.size(); i++)
			{
				if (tempVector[i])
				{
					tempKeyCodeV.push_back(_keys[i]);
				}
			}

			return tempKeyCodeV;
		}
	}

}
