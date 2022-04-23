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

	float arrival_time ;

	float burst_time ;

	float priority;

	/*
	 * Description :
	 * Process_InputInfo Constructors.
	 */
	Process_Input();

	Process_Input(float, float , float priority = INITIAL_PRIORITY);
	/*
	 * Description :
	 * Prints the values of the elements of the Process_InputInfo structure on the command line.
	 */
	void print();

}Process_Input;


typedef struct Process_Output{

	string name ;

	float duration ;

	float arrival_time;

	float start_time;

	float end_time;
	/*
	 * Description :
	 * Process_Output Structure Constructors.
	 */
	Process_Output();

	Process_Output(string , float , float arrival_time= INITIAL_TIME , float start_time = INITIAL_TIME  , float end_time = INITIAL_TIME);

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
