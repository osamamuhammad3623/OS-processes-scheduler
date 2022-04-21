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

	vector<Process_Input> sortedArrival = sorted(processes, ARRIVAL_TIME);
	vector<Process_Input> readyqueue;
	vector<Process_Output> SJF_NP_OP;
	Process_Output temp;
	int totalbursttime = 0;
	int sortedArrivalSize = sortedArrival.size();

	while (sortedArrival.size()) {

		readyqueue.push_back(sortedArrival[0]);
		for (int i = 1;i < sortedArrival.size();) {

			if (sortedArrival[0].arrival_time == sortedArrival[i].arrival_time) {

				readyqueue.push_back(sortedArrival[i]);
				sortedArrival.erase(sortedArrival.begin() + 1);  //remove the pushed process to queue from the main vector
			}
			else
			{
				i++;
			}
		}
		sortedArrival.erase(sortedArrival.begin());  //remove the previously pushed process to the queue from the main vector

		readyqueue = sorted(readyqueue, BURST_TIME);  //queue has processes of same arrival time sorted according to burst time

		while (readyqueue.size()) {
			if (readyqueue[0].arrival_time > totalbursttime) {
				temp = { "EMPTY" , readyqueue[0].arrival_time - totalbursttime , totalbursttime , totalbursttime , readyqueue[0].arrival_time };
				SJF_NP_OP.push_back(temp);
				totalbursttime = totalbursttime + readyqueue[0].arrival_time - totalbursttime;
			}

			temp = { readyqueue[0].name , readyqueue[0].burst_time , readyqueue[0].arrival_time , totalbursttime , totalbursttime + readyqueue[0].burst_time };
			SJF_NP_OP.push_back(temp);
			totalbursttime = totalbursttime + readyqueue[0].burst_time;
			readyqueue.erase(readyqueue.begin());


			for (int i = 0; i < sortedArrival.size();) {

				if ((sortedArrival[0].arrival_time <= totalbursttime) ) {

					readyqueue.push_back(sortedArrival[0]);
					sortedArrival.erase(sortedArrival.begin());
	
				}
				else {
					i++;
				}
			}

			readyqueue = sorted(readyqueue, BURST_TIME);
		}

	}

	return SJF_NP_OP;

}







