#include "ProgressCtrl.h"

/* made by changhee.byun [NexStreaming Audio Solution] */

ProgressCtrl::ProgressCtrl()
{
	_global_max = 100;	
	_global_min = 0;
	_previous_progress = 0;
}

ProgressCtrl::ProgressCtrl(ProgressCallbackFunction callback_function, void* context)
{
	_global_max = 100;	
	_global_min = 0;	
	_previous_progress = 0;

	_progress_callback = callback_function;
	_callback_context = context;

}


ProgressCtrl::~ProgressCtrl()
{
}

void ProgressCtrl::SetCallbackMethod(ProgressCallbackFunction callback_function, void* context)
{
	_progress_callback = callback_function;
	_callback_context = context;
}


int ProgressCtrl::SetProgress(int progress)
{
	int current = progress;

	if (_previous_progress != progress)
	{
		auto iter_local_min = _local_min.rbegin();
		auto iter_local_max = _local_max.rbegin();

		while (		iter_local_min != _local_min.rend() 
				&&	iter_local_max != _local_max.rend()) 
		{
			current = (int)((float)(current * *iter_local_max) * 0.01f);
			current += *iter_local_min;

			++iter_local_min;
			++iter_local_max;			
		}

		
		current = (int)((float)(current * _global_max) * 0.01f);
		current += _global_min;

		_progress_callback(current, _callback_context);
		_previous_progress = progress;
	}	

	return current;
}

void ProgressCtrl::SetGlobalMax(int max)
{
	_global_max = max;
}

void ProgressCtrl::SetGlobalMin(int min)
{
	_global_min = min;
}

// you should call this method to start local progress at the start of function.
void ProgressCtrl::StartProgress()
{
	_local_max.push_back(0);
	_local_min.push_back(0);
}

// you should call this method to set local progress percentage at the next of StartLocalProgress()
void ProgressCtrl::SetLocalProgressPercentage(int max)
{
	if (_local_max.empty() == false)
	{
		SetLocalMin(_local_max.back());
		_local_max.pop_back();
		_previous_progress = 0;
	}

	_local_max.push_back(max);
}

// you should call this method to end local progress at the end of function.
void ProgressCtrl::EndProgress()
{
	_local_max.pop_back();
	_local_min.pop_back();
}


// private method
void ProgressCtrl::SetLocalMin(int min)
{
	if (_local_min.empty() == false)
	{
		min += _local_min.back();
		_local_min.pop_back();
	}

	_local_min.push_back(min);
		
}


int			ProgressCtrl::GetGlobalMax()
{
	return _global_max;
}

int			ProgressCtrl::GetGlobalMin()
{
	return _global_min;
}

int			ProgressCtrl::GetCurrentLocalMax()
{	
	if (_local_max.size() != 0)
	{
		return _local_max.back();
	}
	else
	{
		return 100;
	}	
}

int			ProgressCtrl::GetCurrentLocalMin()
{
	if (_local_min.size() != 0)
	{
		return _local_min.back();
	}
	else
	{
		return 100;
	}
}


void ProgressCtrl::ChildProgressCallback(int progress, void* context)
{
	ProgressCtrl* me = (ProgressCtrl*)context;
	me->SetProgress(progress);
}


ProgressCallbackFunction ProgressCtrl::GetCallbackMethod()
{
	return _progress_callback;
}

void* ProgressCtrl::GetContext()
{
	return _callback_context;
}
