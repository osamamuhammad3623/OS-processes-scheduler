/******************************************************************************
 *
 * Module: Scheduler
 *
 * File Name: scheduler.cpp
 *
 * Description: Source file for Scheduler Class.
 *
 *******************************************************************************/
#include <iostream>
using namespace std;
#include "scheduler.h"

/*
 * Description :
 * Scheduler Constructor.
 */
Scheduler::Scheduler(vector<Process_Input> p , SchedulingType type){

	this->processes = p;

	this->type = type;


}

/*
 * Description :
 * Adds a process to the scheduler.
 */
void Scheduler::addProcess(Process_Input p){

	processes.push_back(p);

}

/*
 * Description :
 * Sets the scheduling type.
 */
void Scheduler::setSchedulingType(SchedulingType type){
	this->type = type;
}

/*
 * Description :
 * Returns an ordered list of processes and their durations of execution on the CPU.
 */
vector<Process_Output> Scheduler::getChart(){

	switch(type){

	case FCFS:
		return ((FCFS_Scheduler*)this)->getChart();

	case SJF_NON_PREEPTIVE:
		return ((SJF_NP_Scheduler*)this)->getChart();

	case SJF_PREEMPTIVE:
		return ((SJF_P_Scheduler*)this)->getChart();

	case PRIORITY_NON_PREEMPTIVE:
		return ((PRI_NP_Scheduler*)this)->getChart();

	case PRIORITY_PREEMPTIVE:
		return ((PRI_P_Scheduler*)this)->getChart();

	case ROUND_ROBIN:
		return ((RR_Scheduler*)this)->getChart();
	}
	return {};

}

/*
 * Description :
 * Returns the waiting time of a certain process.
 */
static int waiting_time(vector<Process_Output> chart, string name){

	int total = 0;

	bool firstOccurence = false;

	int last_index = -1;

	for(size_t i = 0 ; i < chart.size() ; i++){

		Process_Output process = chart[i];

		if(process.name == name){

			if(firstOccurence == false){

				total+= process.start_time - process.arrival_time;

				firstOccurence = true;
			}

			else{

				total+= process.start_time- chart[last_index].end_time;

			}

			last_index = i ;

		}

	}

	return total;
}


static int turnAround_time(vector<Process_Output> chart, string name){

	for(size_t i = chart.size()-1 ; i>= 0 ; i--){

		if(chart[i].name == name){

			return chart[i].end_time - chart[i].arrival_time;

		}

	}

}
/*
 * Description :
 * Returns the average waiting time of all processes.
 */
float average_waiting_time(vector<Process_Output> chart , int processes_number){

	int result = 0 ;

	for(int i = 1 ; i<= processes_number ; i++){

		result += waiting_time(chart, "P"+to_string(i));


	}

	return (float)result/processes_number;
}

/*
 * Description :
 * Returns the average turnaround time of all processes.
 */
float average_turnAround_time(vector<Process_Output> chart , int processes_number){

	int result = 0 ;

	for(int i = 1 ; i<= processes_number ; i++){

		//cout<<"The waiting time of "<<"P"+to_string(i)<<" is "<<waiting_time(chart, "P"+to_string(i))<<endl<<endl;
		result +=turnAround_time(chart, "P"+to_string(i));


	}

	return (float)result/processes_number;
}

