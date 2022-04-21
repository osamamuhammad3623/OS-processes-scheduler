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

/*
 * Description :
 * Returns an ordered list of processes and their durations of execution on the CPU.
 */
vector<Process_Output> SJF_P_Scheduler::getChart() {

	vector <Process_Input> sortedArrival = sorted(processes, ARRIVAL_TIME);
	vector<Process_Input> readyqueue;  // vector that contains the arrived processes ready to be on CPU
	vector <Process_Output> SJF_P_OP; //vector that containes the processes according to SJF premptive
	Process_Output temp;
	int totalbursttime = 0;
	int oldtotalbursttime = 0;
	int sortedArrivalSize = sortedArrival.size();
	int arrivaltime = sortedArrival[0].arrival_time;
	int newarrivaltime = 0;

	while (sortedArrival.size() != 0 || readyqueue.size() != 0) {

		if (sortedArrival.size() != 0) {
			if (sortedArrival[0].arrival_time <= totalbursttime) {
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
			}
			else if (sortedArrival.size() != 0 && sortedArrival[0].arrival_time > totalbursttime && readyqueue.size() == 0) {

				newarrivaltime = sortedArrival[0].arrival_time;

			}
		}

		if (readyqueue.size()) {
			readyqueue = sorted(readyqueue, BURST_TIME);
			oldtotalbursttime = totalbursttime;
			totalbursttime = totalbursttime + readyqueue[0].burst_time;
		}


		if (sortedArrival.size() != 0) {
			if (totalbursttime <= sortedArrival[0].arrival_time && readyqueue.size()) {

				temp = { readyqueue[0].name , readyqueue[0].burst_time , readyqueue[0].arrival_time , oldtotalbursttime ,totalbursttime };
				SJF_P_OP.push_back(temp);
				readyqueue.erase(readyqueue.begin());

			}
			else if (totalbursttime > sortedArrival[0].arrival_time) { //preemption

				totalbursttime = sortedArrival[0].arrival_time;
				temp = { readyqueue[0].name , sortedArrival[0].arrival_time - oldtotalbursttime , readyqueue[0].arrival_time , oldtotalbursttime ,sortedArrival[0].arrival_time };
				readyqueue[0].burst_time = readyqueue[0].burst_time - (sortedArrival[0].arrival_time - oldtotalbursttime);  //new burst time =  burst time -duration
				SJF_P_OP.push_back(temp);
			}
			else if (totalbursttime < newarrivaltime && readyqueue.size() == 0)
			{
				readyqueue.push_back(sortedArrival[0]);
				temp = { "EMPTY" , readyqueue[0].arrival_time - totalbursttime ,totalbursttime , totalbursttime , readyqueue[0].arrival_time };
				SJF_P_OP.push_back(temp);
				totalbursttime = totalbursttime + readyqueue[0].arrival_time - totalbursttime;
				sortedArrival.erase(sortedArrival.begin());
			}
		}
		else {


			if (totalbursttime >= readyqueue[0].arrival_time) {
				for (int i = 0; i < readyqueue.size();) {

					if (readyqueue.size() != 0) {
						temp = { readyqueue[0].name , readyqueue[0].burst_time ,readyqueue[0].arrival_time , oldtotalbursttime , (oldtotalbursttime + readyqueue[0].burst_time) };
						SJF_P_OP.push_back(temp);
						oldtotalbursttime = oldtotalbursttime + readyqueue[0].burst_time;
						readyqueue.erase(readyqueue.begin());
					}
					else {
						i++;
					}
				}
			}

		}

	}


	for (int i = 0; i < SJF_P_OP.size() - 1; i++) {


		int j = i + 1;
		while (SJF_P_OP[i].name == SJF_P_OP[j].name) {

			temp = { SJF_P_OP[i].name , SJF_P_OP[i].duration + SJF_P_OP[j].duration , SJF_P_OP[i].arrival_time , SJF_P_OP[i].start_time ,SJF_P_OP[j].end_time };
			SJF_P_OP[j] = temp;
			SJF_P_OP.erase(SJF_P_OP.begin() + i);

		}


	}


	return SJF_P_OP;

}

