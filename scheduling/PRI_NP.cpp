/******************************************************************************
 *
 * Module: priority - Non Preemptive Scheduler
 *
 * File Name: PRI_NP.cpp
 *
 * Description: Source file for priority - Non Preemptive Scheduler implementation.
 *
 *******************************************************************************/

#include <vector>
#include "scheduler.h"
#include <iostream>
using namespace std;

#define SUBSET(TYPE,VECTOR, START) vector<TYPE>(VECTOR.begin()+START , VECTOR.end())



/*
 * Description :
 * Returns an ordered list of processes and their durations of execution on the CPU.
 */
vector<Process_Output> PRI_NP_Scheduler::getChart(){

	if(processes.size() == 0){
		return {};
	}

	int total_time = 0;

	vector<Process_Input> buffer = sorted(this->processes , ARRIVAL_TIME);

	vector<Process_Output> result;

	while(buffer.size() != 0){

		vector<Process_Input> q = vector<Process_Input>();

		q.push_back(buffer[0]);

		/*Add all processes with the same arrival time*/
		for(size_t i = 1 ; i < buffer.size() ; i++){

			if(buffer[i].arrival_time == buffer[0].arrival_time){

				q.push_back(buffer[i]);

			}

		}

		/*Sort the ready processes according to their priority*/
		q = sorted(q , PRIORITY);

		/*Remove them from the buffer*/
		buffer = SUBSET(Process_Input,buffer,q.size());


		/*For each process in the ready queue:*/
		while(q.size()!= 0){

			Process_Input process = q[0];
			/*If it hasn't arrived yet, The CPU is not utilized*/
			if(process.arrival_time > total_time){

				result.push_back(Process_Output("EMPTY",
						process.arrival_time - total_time,
						INITIAL_TIME,
						total_time,
						process.arrival_time));

				total_time = process.arrival_time;


			}
			/*Select the first one to execute*/
			result.push_back( Process_Output(process.name,
					process.burst_time ,
					process.arrival_time,
					total_time ,
					total_time+process.burst_time));

			total_time += process.burst_time;
			/*Remove it from the Queue*/
			q = SUBSET(Process_Input,q, 1);

			/*Check for available processes now*/
			int new_processes_count = 0;

			for(auto waiting_process : buffer){

				if(waiting_process.arrival_time <= total_time){

					q.push_back(waiting_process);

					new_processes_count++;

				}

			}
			/*Remove the added processes from the buffer*/
			if(new_processes_count !=0){

				buffer = SUBSET(Process_Input, buffer, new_processes_count);

				q = sorted(q , PRIORITY);

			}


		}



	}


	return result;

}
