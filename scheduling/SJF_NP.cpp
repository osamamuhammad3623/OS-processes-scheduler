/******************************************************************************
 *
 * Module: SJF - Non Preemptive Scheduler
 *
 * File Name: SJF_NP.cpp
 *
 * Description: Source file for SJF - Non Preemptive Scheduler implementation.
 *
 *******************************************************************************/

#include <vector>
#include "scheduler.h"

/*
 * Description :
 * Returns an ordered list of processes and their durations of execution on the CPU.
 */
vector<Process_Output> SJF_NP_Scheduler::getChart(){

	for(size_t i = 0; i < processes.size() ; i++){

		processes[i].priority = processes[i].burst_time;
	}

	PRI_NP_Scheduler scheduler(processes);

	return scheduler.getChart();
}
