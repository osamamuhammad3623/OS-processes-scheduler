/******************************************************************************
 *
 * Module: Process
 *
 * File Name: process.cpp
 *
 * Description: Source file for the Process Class.
 *
 *******************************************************************************/

#include "process.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define SWAP(TYPE,A,B) {TYPE temp; temp = A ; A = B ; B = temp;}

int g_count = 0 ;
/*
 * Description :
 * Process_Input Constructor.
 */
Process_Input::Process_Input(){

	this->burst_time  = INITIAL_TIME;

	this->arrival_time  = INITIAL_TIME;

	this->priority  = INITIAL_PRIORITY ;
}


Process_Input::Process_Input(float arrival_time ,float burst_time ,float priority ){

	this->burst_time  = burst_time;

	this->arrival_time  = arrival_time;

	this->priority  = priority ;
}

/*
 * Description :
 * Prints the values of the elements of the Process_Input structure on the command line.
 */
void Process_Input::print(){

	cout<<"Arrival Time = "<<arrival_time<<endl;

	cout<<"Burst Time = "<<burst_time<<endl;

	cout<<"priority = "<<priority<<endl;

}

/*
 * Description :
 * Process_Output Structure Constructors.
 */
Process_Output::Process_Output(){

	name = "NONE";

	duration  = INITIAL_DURATION;

	arrival_time = INITIAL_TIME;

	start_time = INITIAL_TIME;

	end_time = INITIAL_TIME;
}

Process_Output::Process_Output(string name , float duration, float arrival_time , float start_time  , float end_time){

	this->name = name;

	this->duration  = duration;

	this->arrival_time = arrival_time;

	this->start_time = start_time;

	this->end_time = end_time;

}


/*
 * Description :
 * Prints the values of the elements of the Process_Output structure on the command line.
 */
void Process_Output::print(){

	cout<<"Name : "<<name<<endl;

	cout<<"Duration = "<<duration<<endl;

	cout<<"Start time = "<<start_time<<endl;

	cout<<"End time = "<<end_time<<endl;


}
/*
 * Description :
 * Sorts the list of processes ascendingly according to a given criteria.
 */
vector<Process_Input> sorted(vector<Process_Input> processes , SortingCriteria criteria){

	vector<Process_Input> buffer = processes;

	for(size_t i = 0 ; i < processes.size()-1 ; i++){

		bool sorted = true;
		float left_value = 0 , right_value = 0;

		for(size_t j = 0 ; j < processes.size()-i-1 ; j++){

			switch(criteria){

			case ARRIVAL_TIME:

				left_value = buffer[j].arrival_time;
				right_value =  buffer[j+1].arrival_time;
				break;

			case BURST_TIME:

				left_value = buffer[j].burst_time;
				right_value =  buffer[j+1].burst_time;
				break;

			case PRIORITY:
				left_value = buffer[j].priority;
				right_value =  buffer[j+1].priority;
				break;

			}


			if(left_value > right_value){

				sorted = false;
				SWAP(Process_Input,buffer[j] , buffer[j+1]);

			}

		}


		if(sorted){

			return buffer;

		}

	}

	return buffer;

}
