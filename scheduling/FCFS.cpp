/******************************************************************************
 *
 * Module: FCFS Scheduler
 *
 * File Name: FCFS.cpp
 *
 * Description: Source file for FCFS Scheduler implementation.
 *
 *******************************************************************************/

#include <vector>
#include "scheduler.h"

/*
 * Description :
 * Returns an ordered list of processes and their durations of execution on the CPU.
 */

vector<Process_Output> FCFS_Scheduler::getChart(){
	vector<Process_Input> sorted_processes = sorted(processes, ARRIVAL_TIME);
	vector<Process_Output> FCFS_Output;
	Process_Output temp;

	temp = { sorted_processes[0].name, sorted_processes[0].burst_time, sorted_processes[0].arrival_time, sorted_processes[0].arrival_time, sorted_processes[0].arrival_time + sorted_processes[0].burst_time };

	FCFS_Output.push_back(temp);
	int j = 1;
	for (int i = 1; i <= sorted_processes.size() - 1; i++) {


		if (FCFS_Output[j - 1].start_time + FCFS_Output[j - 1].duration >= sorted_processes[i].arrival_time) {

			temp = { sorted_processes[i].name, sorted_processes[i].burst_time, sorted_processes[i].arrival_time, FCFS_Output[j - 1].end_time, sorted_processes[i].burst_time + FCFS_Output[j - 1].end_time };

			FCFS_Output.push_back(temp);
			j++;
		}
		else {

			temp = { "EMPTY", sorted_processes[i].arrival_time - FCFS_Output[j - 1].end_time,  FCFS_Output[j - 1].end_time, FCFS_Output[j - 1].end_time, sorted_processes[i].arrival_time };

			FCFS_Output.push_back(temp);
			j++;
			temp = { sorted_processes[i].name, sorted_processes[i].burst_time, sorted_processes[i].arrival_time, sorted_processes[i].arrival_time , sorted_processes[i].burst_time + sorted_processes[i].arrival_time };

			FCFS_Output.push_back(temp);
			j++;
		}

	}

	return FCFS_Output;
}
