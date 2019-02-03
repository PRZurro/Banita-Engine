/**
* @file Task.hpp
* 		
* @author Pablo Rodr�guez Zurro
* 		  
* @date 28/12/2018
* 		
* @class Virtual pure class in charge of process components or an specific engine task
* 		 
* @brief 
*/

#pragma once

#include "declarations.hpp"

#include <list>

namespace banita
{
	class Component;
	class Kernel;

	class Task
	{
		using Components_List = std::list<Component * >;

	protected: 

		Components_List components;

		Kernel * kernel;
		Size_t priority;
		bool isFinished;

	public: 

		Task(Kernel * _kernel, Size_t _priority = -1, bool _isFinished = false);
		Task();

	public:
		//core methods
		virtual void initialize() = 0;
		virtual void execute(float _deltaTime) = 0;
		virtual void terminate() = 0 ;

	public:

		void add_component(Component * _component)
		{
			components.push_back(_component);
		}

	public: 
		//getters
		bool is_finished() const 
		{
			return isFinished;
		}

		Size_t get_priority() const
		{
			return priority;
		}

		Kernel& get_kernel() const
		{
			return *kernel;
		}

	public:
		//setters
		void set_kernel(Kernel & _kernel)
		{
			kernel = &_kernel;
		}

		void set_priority(Size_t _priority)
		{
			priority = _priority;
		}

		void finalize()
		{
			isFinished = true;
		}

		void set_finished(bool _state)
		{
			isFinished = _state;
		}
		
	public:
		//operators
		bool operator < (const Task & _task) const 
		{
			return this->priority < _task.priority;
		}

		bool operator > (const Task & _task) const
		{
			return !(*this < _task);
		}
		
		bool operator <= (const Task & _task) const
		{
			return this->priority <= _task.priority;
		}

		bool operator >= (const Task & _task) const
		{
			return this->priority >= _task.priority; //can't do the !() operation using the contiguous operator because there would be an untreated case
		}

		bool operator == (const Task & _task) const
		{
			return this->priority < _task.priority;
		}

		bool operator != (const Task & _task) const
		{
			return !(*this == _task);
		}
	};
}