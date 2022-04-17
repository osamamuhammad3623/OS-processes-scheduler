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

	int max = 0 ;

	for(auto process : processes){

		if(process.burst_time > max){

			max = process.burst_time;

		}

	}

	RR_Scheduler scheduler(processes,max+1);

	return scheduler.getChart();
}
