//#pragma once
//#include "TaskScheduler.hpp"
//#include "LockFreeQueue.hpp"
//
//namespace Controller
//{
//	namespace Commands
//	{
//		class TaskScheduler
//		{
//		public:
//		    int scheduleTask(TaskConfig task) noexcept override;
//
//		    void CancelAllTask() noexcept override;;
//		private:
//			Controller::LockFreeQueue<TaskConfig> taskToBeExecuted;
//			Controller::LockFreeQueue<TaskConfig> runningTasks;
//			Controller::LockFreeQueue<TaskConfig> completedTasks;
//		};
//	}
//}
