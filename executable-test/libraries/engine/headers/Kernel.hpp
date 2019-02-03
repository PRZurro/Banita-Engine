/**
* @file Kernel.hpp
*
* @author Pablo Rodr�guez Zurro
*
* @date 28/12/2018
*
* @class Kernel
*
* @brief 
*/

#pragma once

#include "declarations.hpp"
#include "Task.hpp"
#include <list>
#include <Timer.hpp>
#include <set>

namespace banita
{
	class Kernel
	{
		using Task_Set = std::multiset< Task * >;
		
	private:
		Task_Set tasks; 
		Scene * scene;

		Timer timer;
		float time;

		bool exit;
		bool isPaused;

	public:

		/**
		 * @brief Construct a new Kernel object by default
		 * 
		 */
		Kernel() : scene(nullptr), exit(false), isPaused(false), time(1.f / 60.f) {}

		/**
		 * @brief Construct a new Kernel object and store the pointer to the scene received
		 * 
		 * @param _scene 
		 */
		Kernel(Scene * _scene) : scene(_scene), exit(false), isPaused(false), time(1.f / 60.f) {}

		/**
		 * @brief Destroy the Kernel object and destroy the tasks that store
		 * 
		 */
		~Kernel()
		{
			tasks.clear(); // it's required to clear the list to avoid unwanted memory allocation
		}

	public:

		/**
		 * @brief run the kernel
		 * 
		 */
		void run();
		
		/**
		 * @brief pause the kernel
		 * 
		 */
		void pause()
		{
			isPaused = (isPaused) ? false : true;
		}

		/**
		 * @brief stop the kernel
		 * 
		 */
		void stop()
		{
			exit = true;
		}

	private:
		/**
		 * @brief initialize the tasks 
		 * 
		 */
		void initialize_tasks();

		/**
		 * @brief update the tasks
		 * 
		 */
		void execute_tasks();

		/**
		 * @brief finalize the tasks
		 * 
		 */
		void terminate_tasks();
	
	public:

		/**
		 * @brief adds a task to the tasks set
		 * 
		 * @param _task 
		 */
		void add_task(Task & _task)
		{
			tasks.insert(&_task);
			_task.set_kernel(*this);
		}

		/**
		 * @brief adds an array of tasks to the current tasks set
		 * 
		 * @param _taskArray 
		 * @param _arraySize 
		 */
		void add_tasks(Task * _taskArray, Size_t _arraySize);

		/**
		 * @brief adds a set of tasks to the current tasks set
		 * 
		 * @param _tasks 
		 */
		void add_tasks(Task_Set & _tasks);

		/**
		 * @brief removes an specific task from the tasks set
		 * 
		 * @param _task task to remove
		 */
		void remove_task(Task & _task)
		{
			tasks.erase(&_task);
		}

	public:

		/**
		 * @brief get the pause state object
		 * 
		 * @return true 
		 * @return false 
		 */
		bool is_paused()
		{
			return isPaused;
		}

		/**
		 * @brief Get the scene object
		 * 
		 * @return Scene* 
		 */
		Scene * get_scene()
		{
			return scene;
		}

	public:
		// It is not needed to use an ordinary list because a set sortens the contents when they are inserted so, this methods are not needed

		static bool task_priority_comparator_lower_than(const Task * _task1, const Task * _task2) // can't call a predicate comparator without the static tag 
		{
			return _task1 < _task2;
		}

		static bool task_comparator_greater_than(const Task * _task1, const Task * _task2)
		{
			return _task1 > _task2;
		}

		static bool task_comparator_lower_or_equal_than(const Task * _task1, const Task * _task2)
		{
			return _task1 <= _task2;
		}

		static bool task_comparator_greater_or_equal_than(const Task * _task1, const Task * _task2)
		{
			return _task1 >= _task2;
		}
	};
}