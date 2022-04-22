#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QVector"
#include "QDebug"
#include <vector>
#include "QMessageBox"
#include <QtWidgets>
#include "scheduling/process.h"
#include "scheduling/scheduler.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->rrquantum->setHidden(true); /* hide the quantum option as start-up */
    this->setWindowTitle("OS Processes Scheduler");
}

MainWindow::~MainWindow()
{
    delete ui;
}

/***************************************
    Global variables
***************************************/
int n=0; /* number of processes */
int col; /* number of columns needed for the selected algorithm */
float quantum;
QString selectedAlgorithm;
bool allDataValid=true;


/***************************************
    Functions implementation
***************************************/

void MainWindow::configureTable(int n_columns, QStringList* header){
    ui->table->setColumnCount(n_columns);
    for (int i=0; i< n_columns; i++){
        ui->table->setColumnWidth(i,TABLE_WIDTH/n_columns);
    }
    ui->table->setHorizontalHeaderLabels(*header);
}

bool MainWindow::isValidTime(QString text){
    bool ok=false;
    text.toFloat(&ok);

    return ok;
}

bool MainWindow::isValidPriority(QString text){
    bool ok=false;
    text.toUInt(&ok);

    return ok;
}

vector<Process_Input> MainWindow::getProcessInfo(){
    vector<Process_Input> userInput(n);

    /* Getting Arrival time & burst time [needed for all algorithms] */
    QString validArrival, validBurst;
    for (int i=0; i< n; i++){
        userInput[i].name = "P" + to_string(i+1);

        /* checking if all cells contain valid data [numbers only] */
        validArrival = ui->table->item(i,ARRIAVAL_TIME_INDEX)->text();
        validBurst = ui->table->item(i,BURST_TIME_INDEX)->text();

        if (isValidTime(validArrival) && isValidTime(validBurst)){
            userInput[i].arrival_time = validArrival.toFloat();
            userInput[i].burst_time = validBurst.toFloat();

            if ((userInput[i].burst_time <= 0) || (userInput[i].arrival_time < 0)){
                allDataValid=false; /* burst time NOT < 0, arrival time can NOT be negative */
            }

        }else{
            allDataValid=false;
        }
    }

    /* Getting process priority [needed only for priority algorithms] */
    if (col == 3){
        for (int i=0; i< n; i++){
            validArrival = ui->table->item(i,PRIORITY_INDEX)->text();
            /* check if user entered a numeric value */
            if (isValidPriority(validArrival)){
                userInput[i].priority = ui->table->item(i,PRIORITY_INDEX)->text().toUInt();
            }else{
                allDataValid=false;
            }
        }
    }

    return userInput;
}


/*
Description: A function to map between user selected algorithm & Scheduling type to be called/executed
*/
SchedulingType type_map(string type){

    if(type == "FCFS"){
        return FCFS;
    }

    else if(type == "Preemptive Priority"){
        return PRIORITY_PREEMPTIVE;
    }

    else if(type == "Non-Preemptive Priority"){
        return PRIORITY_NON_PREEMPTIVE;
    }

    else if(type == "Preemptive SJF"){
        return SJF_PREEMPTIVE;
    }

    else if(type == "Non-Preemptive SJF"){
        return SJF_NON_PREEPTIVE;
    }

    else if(type == "Round Robin"){
        return ROUND_ROBIN;
    }

    return PRIORITY_NON_PREEMPTIVE;
}


void MainWindow::configureGanttChart(vector<Process_Output> & output){
    int si = output.size();
    float totalTime=1, widthPerUnitTime=1, p_duration;
    for (auto p: output){
        totalTime+= p.duration;
    }

    widthPerUnitTime = (TABLE_WIDTH/totalTime);

    ui->chart->setColumnCount(si);
    for (int i=0; i< si;i++){
        p_duration = output[i].duration;
        ui->chart->setColumnWidth(i,(widthPerUnitTime*p_duration));
    }

    /* Adjust chart rows */
    ui->chart->setRowCount(2); /* row-0 for which process in CPU, row-1 shows time taken in CPU */
    ui->chart->setRowHeight(0,CHART_HEIGHT/2);
    ui->chart->setRowHeight(1,CHART_HEIGHT/2);
}


void MainWindow::on_proceedBtn_clicked()
{
    n = ui->n->value() ;
    if (n == 0){
        QMessageBox::information(this, "Processes number", "Enter a valid number of processes!");

    }else{
        QStringList header;
        ui->table->setRowCount(n);
        selectedAlgorithm = ui->algorithm->currentText();

        if (selectedAlgorithm== "Preemptive Priority" || selectedAlgorithm == "Non-Preemptive Priority"){
            header << "Arrival Time" << "Burst Time" << "Priority";
            col =3;
        }
        /* other algorithms don't need Priority column */
        else{
            header << "Arrival Time" << "Burst Time";
            col =2;
        }

        configureTable(col, &header);
    }
}


void MainWindow::on_simulateBtn_clicked()
{
    allDataValid=true;
    vector<Process_Input> processInfo = getProcessInfo(); /* get processes info that user entered in table */
    if (allDataValid){
        SchedulingType selected_algo = type_map(selectedAlgorithm.toStdString());

        vector<Process_Output> output;
        if (selectedAlgorithm != "Round Robin"){
            Scheduler s(processInfo, selected_algo);
            output= s.getChart();
        }else{
            quantum = ui->rrquantum->value();
            RR_Scheduler rrs(processInfo, quantum);
            output= rrs.getChart();
        }

        configureGanttChart(output);

        /* display algorithm output */
        ui->chart->clear();
        auto model = ui->chart->model();
        for (int i=0; i< output.size(); i++){
            model->setData(model->index(0,i),QString::fromStdString(output[i].name));
            model->setData(model->index(1,i),output[i].duration); /* time in CPU */
        }

        /* calculating waiting/turnaround times and display them */
        float waitingTime = average_waiting_time(output,n);
        float taTime = average_turnAround_time(output,n);
        ui->waiting_time_label->setText(QString::fromStdString(to_string(waitingTime)));
        ui->turnaround_time_label->setText(QString::fromStdString(to_string(taTime)));

    }else{
        QMessageBox::information(this, "Invalid Data", "Enter valid numbers!");
        ui->table->clearContents();
    }
}


/* allow user to enter a quantum */
void MainWindow::on_algorithm_currentTextChanged(const QString &arg1)
{
    selectedAlgorithm = arg1;
    if (selectedAlgorithm == "Round Robin"){
        ui->rrquantum->setHidden(false);
    }else{
        ui->rrquantum->setHidden(true);
    }

}

