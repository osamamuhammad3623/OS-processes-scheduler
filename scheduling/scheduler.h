/******************************************************************************
 *
 * Module: Scheduler
 *
 * File Name: scheduler.h
 *
 * Description: Header file for Scheduler Class.
 *
 *******************************************************************************/

#include <vector>
#include <string>
#include "process.h"
using namespace std;

#ifndef SCHEDULER_H_
#define SCHEDULER_H_



typedef enum{

	FCFS,
	SJF_PREEMPTIVE ,
	SJF_NON_PREEPTIVE ,
	PRIORITY_PREEMPTIVE ,
	PRIORITY_NON_PREEMPTIVE ,
	ROUND_ROBIN

}SchedulingType;



/******************************************************************************
 *                        Scheduler Class                                     *
 ******************************************************************************/

class Scheduler{

private:
	SchedulingType type;
protected:

	vector<Process_Input> processes;

public:

	/*
	 * Description :
	 * Scheduler Constructor.
	 */
	Scheduler(vector<Process_Input> p = vector<Process_Input>() , SchedulingType type = FCFS);

	/*
	 * Description :
	 * Adds a process to the scheduler.
	 */
	void addProcess(Process_Input);

	/*
	 * Description :
	 * Sets the scheduling type.
	 */
	void setSchedulingType(SchedulingType type);

	/*
	 * Description :
	 * Returns an ordered list of processes and their durations of execution on the CPU.
	 */
	vector<Process_Output> getChart();

	/*
	 * Description :
	 * Scheduler Destructor.
	 */
	~Scheduler(){}

};


/******************************************************************************
 *                     FCFS Scheduler Class                                   *
 ******************************************************************************/

class FCFS_Scheduler : public Scheduler{


public:

	/*
	 * Description :
	 * FCFS Scheduler Constructor.
	 */
	FCFS_Scheduler(vector<Process_Input> p = vector<Process_Input>()):Scheduler(p){}

	/*
	 * Description :
	 * Returns an ordered list of processes and their durations of execution on the CPU.
	 */
	vector<Process_Output> getChart();

};


/******************************************************************************
 *                 SJF Preemptive Scheduler Class                             *
 ******************************************************************************/

class SJF_P_Scheduler : public Scheduler{

public:

	/*
	 * Description :
	 * SJF Preemptive Scheduler Constructor.
	 */
	SJF_P_Scheduler(vector<Process_Input> p = vector<Process_Input>()):Scheduler(p){}

	/*
	 * Description :
	 * Returns an ordered list of processes and their durations of execution on the CPU.
	 */
	vector<Process_Output> getChart();

};

/******************************************************************************
 *               SJF Non Preemptive Scheduler Class                           *
 ******************************************************************************/


class SJF_NP_Scheduler : public Scheduler{

public:

	/*
	 * Description :
	 * SJF Non Preemptive Scheduler Constructor.
	 */
	SJF_NP_Scheduler(vector<Process_Input> p = vector<Process_Input>()):Scheduler(p){}

	vector<Process_Output> getChart();

};

/******************************************************************************
 *               Priority Preemptive Scheduler Class                           *
 ******************************************************************************/

class PRI_P_Scheduler : public Scheduler{

public:

	/*
	 * Description :
	 * Priority Preemptive Scheduler Constructor.
	 */
	PRI_P_Scheduler(vector<Process_Input> p = vector<Process_Input>()):Scheduler(p){}

	/*
	 * Description :
	 * Returns an ordered list of processes and their durations of execution on the CPU.
	 */
	vector<Process_Output> getChart();

};



/******************************************************************************
 *               Priority Non Preemptive Scheduler Class                           *
 ******************************************************************************/

class PRI_NP_Scheduler : public Scheduler{

public:

	/*
	 * Description :
	 * Priority Non Preemptive Scheduler Constructor.
	 */
	PRI_NP_Scheduler(vector<Process_Input> p = vector<Process_Input>()):Scheduler(p){}

	/*
	 * Description :
	 * Returns an ordered list of processes and their durations of execution on the CPU.
	 */
	vector<Process_Output> getChart();

};


/******************************************************************************
 *                     Round Robin Scheduler Class                                   *
 ******************************************************************************/

class RR_Scheduler : public Scheduler{

private:
	int quantum;
public:

	/*
	 * Description :
	 * Round Robin Scheduler Constructor.
	 */
	RR_Scheduler(vector<Process_Input> p = vector<Process_Input>() , int q = 0):Scheduler(p){quantum = q;}


	/*
	 * Description :
	 * Setter of the quantum value.
	 */
	void setQuantum(int quantum);

	/*
	 * Description :
	 * Returns an ordered list of processes and their durations of execution on the CPU.
	 */
	vector<Process_Output> getChart();

};


/*
 * Description :
 * Returns the average waiting time of all processes.
 */
float average_waiting_time(vector<Process_Output> chart , int processes_number);

/*
 * Description :
 * Returns the average turnaround time of all processes.
 */
float average_turnAround_time(vector<Process_Output> chart , int processes_number);

#endif /* SCHEDULER_H_ */
