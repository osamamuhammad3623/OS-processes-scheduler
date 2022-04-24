/******************************************************************************
 *
 * Module: Round Robin Scheduler
 *
 * File Name: RoundRobin.cpp
 *
 * Description: Source file for Round Robin Scheduler implementation.
 *
 *******************************************************************************/

#include <vector>
#include "scheduler.h"


#define NEXT_PROCESS_NUMBER 0

#define POP_FIRST_FROM_READY_QUEUE() ReadyQueue = vector<Process_Input>(ReadyQueue.begin()+1 , ReadyQueue.end())
#define PUSH_LAST_INTO_READY_QUEUE() ReadyQueue.push_back(ReadyQueue[0])

#define MIN(a,b) ( (a)<(b) ? (a):(b))


bool PushFlag = false;
bool idle = false;


/*
 * Description :
 * Returns an ordered list of processes and their durations of execution on the CPU.
 */
vector<Process_Output> RR_Scheduler::getChart(){

	/*The  vector used to store the result of the Scheduling and will be returned */
	vector<Process_Output>result;

	/*Sort the Processes based on the arrival time */
	vector<Process_Input> buffer = sorted(this->processes , ARRIVAL_TIME);


	/*Queue for process ready to run (Arrival time is equal to cpu time)*/
	vector<Process_Input> ReadyQueue;


	Process_Input temp;
	temp.burst_time = 0;

	float arrival_time = buffer[NEXT_PROCESS_NUMBER].arrival_time;
	float CPU_time = 0;

	if(buffer[NEXT_PROCESS_NUMBER].arrival_time !=0)
	{
		result.push_back(Process_Output("IDLE", arrival_time - 0,0,0,arrival_time));
		CPU_time+= arrival_time;
	}

	while(buffer.size() != 0 || ReadyQueue.size() != 0 || temp.burst_time>0 )
	{
		/*Add to the ready queue all the process with the same arrival time*/
		while (buffer.size() != 0  &&   buffer[NEXT_PROCESS_NUMBER].arrival_time <=CPU_time )
		{
			/*Push the process into the ready queue*/
			ReadyQueue.push_back(buffer[NEXT_PROCESS_NUMBER]);
			/*Remove the added process from the buffer*/
			buffer = vector<Process_Input>(buffer.begin()+1 , buffer.end());
		}


		if(PushFlag)
		{
			ReadyQueue.push_back(temp);
			PushFlag = false;
		}

		if(ReadyQueue.size() == 0 && buffer.size() != 0)
		{
			result.push_back(Process_Output("IDLE",buffer[NEXT_PROCESS_NUMBER].arrival_time-CPU_time,CPU_time,CPU_time,buffer[NEXT_PROCESS_NUMBER].arrival_time));
			CPU_time = buffer[NEXT_PROCESS_NUMBER].arrival_time;
			continue;
		}


		float min = MIN(ReadyQueue[0].burst_time,quantum);
		result.push_back(Process_Output(ReadyQueue[0].name,min,ReadyQueue[0].arrival_time,CPU_time,CPU_time+min));
		ReadyQueue[0].burst_time -= min;
		CPU_time += min;

		/*The process has finished running on cpu */
		if(ReadyQueue[0].burst_time <= 0)
		{
			POP_FIRST_FROM_READY_QUEUE();
			temp.burst_time = 0;
		}

		else
		{
			temp = ReadyQueue[0];
			POP_FIRST_FROM_READY_QUEUE();
			PushFlag = true;
		}



	}


	return result;

}
