#include "Task.hpp"
#include "declarations.hpp"

namespace banita
{
	Task::Task(Kernel * _kernel, Size_t _priority, bool _isFinished) : kernel(_kernel), priority(_priority), isFinished(_isFinished)
	{}
	Task::Task() : kernel(nullptr), priority(100), isFinished(false)
	{

	}
}

