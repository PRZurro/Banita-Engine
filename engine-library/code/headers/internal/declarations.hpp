
// This is free code released into the public domain.
// Drafted by Ángel in January 2019.
// Use it at your own risk. It might have bugs.
// angel.rodriguez@esne.edu

#pragma once

// Se crean declaraciones adelantadas de algunos identificadores de librerías externas
// que se usan en las cabeceras del banita para que en los proyectos en los que se
// incluyan éstas no sea necesario añadir las cabeceras de las librerías externas.

///////////////////////////////////////// SDL /////////////////////////////////////////

typedef struct SDL_Window   SDL_Window;
typedef void              * SDL_GLContext;

/////////////////////////////////// OPENGL TOOLKIT ////////////////////////////////////

#pragma once

#include "Variant.hpp"

#include "glm/glm.hpp"
#include "Node.hpp"
#include "Render_Node.hpp"

#include "rapidxml.hpp"
#include <vector>
#include "fnv.hpp"


	//namespace glm
	//{
	//	class vec3;
	//	class vec4;
	//}
	//namespace glt
	//{
	//	class Matrix44;
	//	class Render_Node;
	//	class Node;
	//}
	//

using Vector4f = glm::vec4;
using Vector3f = glm::vec3;
using Matrix44 = glt::Matrix44;
using GLT_Node = glt::Node; // Angel's own class of transformation node
using RenderNode = glt::Render_Node;

namespace banita
{
	class Scene;
	class Component;
	class Entity;
	class Kernel;
	class Message_Handler;
	class Module;
	class Controller;

	//Definitions to use along the engine
	using String = std::string;
	using Size_t = std::size_t;
	using Int32 = std::uint32_t;
	using Var = Variant;

	/*using Matrix44 = toolkit::Matrix44f;
	using Vector3f = toolkit::Vector3f;*/ //deprecated
	
	using XML_Node = rapidxml::xml_node<>;
	using XML_Attr = rapidxml::xml_attribute<>;

	
	using GLT_Node_sptr = std::shared_ptr< GLT_Node >;
	using Entity_sptr = std::shared_ptr<Entity>;
	using Component_sptr = std::shared_ptr<Component>;
	using Scene_sptr = std::shared_ptr<Scene>;
	using Kernel_sptr = std::shared_ptr<Kernel>;
	using Module_sptr = std::shared_ptr<Module>;
	using Controller_sptr = std::shared_ptr<Controller>;
	using MH_sptr = std::shared_ptr<Message_Handler>; // MH = Message Handler
	

	typedef Component_sptr(*fnComponentGenerator) (Entity * entity);
	typedef Component_sptr(*fnControllerComponentGenerator) (Entity * entity, Message_Handler * mh);

	#define FNV32(X) toolkit::fnv32 (X)

	class String_Utilities
	{
	public:

		static std::vector<String> string_splitter(const String & _toSplit, char _delimitier);
	};
}

