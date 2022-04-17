/******************************************************************************
 *
 * Module: SJF - Preemptive Scheduler
 *
 * File Name: SJF_P.cpp
 *
 * Description: Source file for  SJF - Preemptive Scheduler implementation.
 *
 *******************************************************************************/

#include <vector>
#include "scheduler.h"

#define NEXT_PROCESS_NUMBER 0

/*
 * Description :
 * Returns an ordered list of processes and their durations of execution on the CPU.
 */
vector<Process_Output> SJF_P_Scheduler::getChart(){
	/*The  vector used to store the result of the Scheduling and will be returned */
		vector<Process_Output>result;

		/*Sort the Processes based on the arrival time */
		vector<Process_Input> buffer = sorted(this->processes , ARRIVAL_TIME);


		/*Queue for process ready to run (Arrival time is equal to cpu time)*/
		vector<Process_Input> ReadyQueue;



		int arrival_time = buffer[NEXT_PROCESS_NUMBER].arrival_time;
		int CPU_time = 0;

		if(buffer[NEXT_PROCESS_NUMBER].arrival_time !=0)
		{
			result.push_back(Process_Output("IDLE", arrival_time - 0,0,0,arrival_time));
			CPU_time+= arrival_time;

		}

		while(buffer.size() != 0 || ReadyQueue.size() != 0)
		{


			/*Add to the ready queue all the process with the same arrival time*/
			while (buffer.size() != 0  &&  arrival_time == buffer[NEXT_PROCESS_NUMBER].arrival_time)
			{
				/*Push the process into the ready queue*/
				ReadyQueue.push_back(buffer[NEXT_PROCESS_NUMBER]);

				/*Remove the added process from the buffer*/
				buffer= vector<Process_Input>(buffer.begin()+1 , buffer.end());

			}




			int new_arrival_time =0;

			if(buffer.size() != 0)
			{
				 new_arrival_time = buffer[NEXT_PROCESS_NUMBER].arrival_time;
			}


			/*Sort the processes in the ready queue according to the priority*/
			ReadyQueue = sorted(ReadyQueue , BURST_TIME);

			/*Store the cpu time in case there is an interrupt*/
			int old_CPU_time = CPU_time;
			CPU_time += ReadyQueue[0].burst_time;

			/*Case 1 : Proccess came with higher priority and no interrupt */
			if(CPU_time <= new_arrival_time && new_arrival_time !=0)
			{
				result.push_back(Process_Output( ReadyQueue[0].name, ReadyQueue[0].burst_time,ReadyQueue[0].arrival_time,old_CPU_time,CPU_time));
				ReadyQueue = vector<Process_Input>(ReadyQueue.begin()+1 , ReadyQueue.end());
			}


	/*The buffer is empty and now we sort the queue with priority and fill it*/
			else if(new_arrival_time == 0)
			{
				while(ReadyQueue.size() != 0)
				{
					result.push_back(Process_Output( ReadyQueue[0].name, ReadyQueue[0].burst_time,ReadyQueue[0].arrival_time,old_CPU_time,old_CPU_time+ ReadyQueue[0].burst_time));
					old_CPU_time += ReadyQueue[0].burst_time;
					ReadyQueue = vector<Process_Input>(ReadyQueue.begin()+1 , ReadyQueue.end());

				}
			}

			/*There may be an interrupt so there is a need to add the new processes to ready queue and check*/
			else if(CPU_time > new_arrival_time)
			{

				CPU_time = old_CPU_time + (new_arrival_time - old_CPU_time);
				result.push_back(Process_Output( ReadyQueue[0].name, new_arrival_time - old_CPU_time,ReadyQueue[0].arrival_time,old_CPU_time,new_arrival_time));
				ReadyQueue[0].burst_time = ReadyQueue[0].burst_time -(new_arrival_time - old_CPU_time);


			}


			if(CPU_time < new_arrival_time && ReadyQueue.size() != 0)
			{
				continue;
			}

			else if (CPU_time < new_arrival_time && ReadyQueue.size() == 0)
			{
				result.push_back(Process_Output("IDLE", new_arrival_time- CPU_time,CPU_time,CPU_time,new_arrival_time));
				CPU_time +=  new_arrival_time- CPU_time;
			}

			arrival_time = new_arrival_time;

		}


		for(int i = 0; i < (int)result.size();i++)
		{
			while(result[i].name == result[i+1].name)
			{
				Process_Output p(result[i].name,result[i].duration+result[i+1].duration,result[i].arrival_time,result[i].start_time,result[i+1].end_time);
				result[i] = p;
				result.erase(result.begin()+i+1);


			}
		}

		return result;




	return result;

}
