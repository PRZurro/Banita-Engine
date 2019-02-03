/**
 * @file BanitaEngine.hpp
 * @author Pablo Rodríguez Zurro (pablorodriguezzurro@gmail.com)
 * @brief Core class that encapsulates the engine library to avoid header inclusion errors
 * @version 0.1
 * @date 2019-02-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#pragma once

#include <string>

namespace banita
{
	class BanitaEngine
	{
	public:
		/**
		 * @brief Construct a new Banita Engine object. This serves as a encapsulator, to avoid errors of header inclusion
		 * 
		 */
		BanitaEngine();
	
		/**
		 * @brief Destroy the Banita Engine object
		 * 
		 */
		~BanitaEngine()
		{
		}

	public:

		/**
		 * @brief run the engine. Create a new window, scene and input task. 
		 * 
		 * @param scenePath 
		 * @param windowWidth 
		 * @param windowHeight 
		 * @param windowName 
		 * @param fullscreen 
		 */
		void run(std::string scenePath = "../../assets/Scenes/test_scene.xml" , int windowWidth = 1280, int windowHeight = 720, std::string windowName = "BanitaEngine", bool fullscreen = false);
	};
}
