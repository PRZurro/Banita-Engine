#include "Kernel.hpp"
#include "declarations.hpp"

namespace banita
{
	void Kernel::run()
	{
		initialize_tasks();

		do
		{
			timer.start();

			if (!isPaused)
				execute_tasks();

			time = timer.elapsed_seconds();
		} while (!exit);

		terminate_tasks();
	}

	void Kernel::initialize_tasks()
	{
		for (Task * _task : tasks)
		{
			_task->initialize();
		}
	}

	void Kernel::execute_tasks()
	{
		auto iterator = tasks.begin(), end = tasks.end();

		Task * task = nullptr;

		for (iterator; iterator != end && !exit; ++iterator)
		{
			if (exit)
			{
				break;
			}

			task = *iterator;

			task->execute(time);

			if (task->is_finished())
			{
				task->terminate();
				tasks.erase(iterator); // the task is deleted from the list more efficiently than remove function, which needs a task pointer that prevents the use of (Task * _task : tasks)
			}
			else
			{
				task->execute(time);
			}

			if (tasks.empty())
			{
				stop();
				break; // breaks the loop 
			}
		}
	}

	void Kernel::terminate_tasks()
	{
		for (Task * _task : tasks)
		{
			_task->terminate();
		}
	}

	void Kernel::add_tasks(Task* _taskArray, Size_t _arraySize)
	{
		for (size_t i = 0; i < _arraySize; i++)
		{
			tasks.insert(&_taskArray[i]);
			_taskArray[i].set_kernel(*this);
		}
	}

	void Kernel::add_tasks(Task_Set & _tasks)
	{
		auto iterator = _tasks.begin(), end = _tasks.end();

		for (iterator; iterator != end && !exit; ++iterator)
		{
			Task * tempTask = *iterator;

			tempTask->set_kernel(*this);
			tasks.insert(tempTask);
		}
	}
}