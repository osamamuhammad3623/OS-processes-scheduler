/******************************************************************************
 *
 * Module: Process
 *
 * File Name: process.h
 *
 * Description: Header file for data-types and method declarations of the Process Class.
 *
 *******************************************************************************/
#ifndef PROCESS_H_
#define PROCESS_H_

#include <string>
#include<vector>
using namespace std;

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define INITIAL_PRIORITY	 (-1)
#define INITIAL_TIME		 (-1)
#define INITIAL_DURATION	 (-1)

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum{

	BURST_TIME,
	ARRIVAL_TIME,
	PRIORITY

}SortingCriteria;


typedef struct Process_Input{

	string name ;

	int arrival_time ;

	int burst_time ;

	int priority;

	/*
	 * Description :
	 * Process_InputInfo Constructors.
	 */
	Process_Input();

	Process_Input(int, int , int priority = INITIAL_PRIORITY);
	/*
	 * Description :
	 * Prints the values of the elements of the Process_InputInfo structure on the command line.
	 */
	void print();

}Process_Input;


typedef struct Process_Output{

	string name ;

	int duration ;

	int arrival_time;

	int start_time;

	int end_time;
	/*
	 * Description :
	 * Process_Output Structure Constructors.
	 */
	Process_Output();

	Process_Output(string , int , int arrival_time= INITIAL_TIME , int start_time = INITIAL_TIME  , int end_time = INITIAL_TIME);

	/*
	 * Description :
	 * Prints the values of the elements of the Process_Output structure on the command line.
	 */
	void print();


}Process_Output;


/*
 * Description :
 * Sorts the list of processes ascendingly according to a given criteria.
 */
vector<Process_Input> sorted(vector<Process_Input> processes, SortingCriteria criteria);

#endif /* PROCESS_H_ */
