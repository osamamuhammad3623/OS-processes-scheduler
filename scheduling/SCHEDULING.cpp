//============================================================================
// Name        : SCHEDULING.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
//============================================================================

#include <iostream>
#include "scheduler.h"
using namespace std;

//int main() {

//	vector<Process_Input> processes = {



//						Process_Input(0,3),
//						Process_Input(0,3),
//						Process_Input(20,9),


//			//
//			//						Process_Input(0,3),
//			//						Process_Input(1,5),
//			//						Process_Input(1,1),
//			//						Process_Input(3,6),
//			//						Process_Input(8,2),


//			//			Process_Input(0,8,3),
//			//			Process_Input(1,1,1),
//			//			Process_Input(2,3,2),
//			//			Process_Input(3,2,3),
//			//			Process_Input(4,6,4)


//			//			Process_Input(0,6,5),
//			///		Process_Input(2,4,3),
//			//			Process_Input(3,2,1),
//			//		Process_Input(5,7,2),
//			//	Process_Input(18,2,0),
//			//Process_Input(19,1,1)

//	};

//	RR_Scheduler scheduler(processes , 3);

//	vector<Process_Output> out = scheduler.getChart();

//	cout<<"Average Waiting Time = "<<average_waiting_time(out, processes.size())<<endl<<endl;

//	cout<<"Average Turn around Time = "<<average_turnAround_time(out, processes.size())<<endl<<endl;

//	for(auto process : out){

//		process.print();

//	}

//	return 0;
//}
