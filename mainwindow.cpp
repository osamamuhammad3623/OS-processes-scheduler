#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QVector"
#include "QDebug"
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
QString selectedAlgorithm;


/***************************************
    Functions implementation
***************************************/

/*
Description: A function to set the table according to the selected algorithm
*/
void configureTable(Ui::MainWindow* ui, int n_columns, QStringList* header){
    ui->table->setColumnCount(n_columns);
    for (int i=0; i< n_columns; i++){
        ui->table->setColumnWidth(i,TABLE_WIDTH/n_columns);
    }
    ui->table->setHorizontalHeaderLabels(*header);
}


/*
Description: A function to return the user-input data about processes in a 2D vector
*/
QVector<QVector<int>> getProcessInfo(Ui::MainWindow* ui){
    QVector<QVector<int>> data (n, QVector<int> (col)); /* 2D vector to store processes data */
    for (int i=0; i< n; i++){
        for (int j=0; j< col; j++){
            data[i][j] = ui->table->item(i,j)->text().toUInt();
        }
    }

    return data;
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
        if (selectedAlgorithm == "Round Robin"){
            header << "Arrival Time" << "Burst Time";
            col =2;

        }else if (selectedAlgorithm== "FCFS"){
            header << "process ID" << "Arrival Time" << "Burst Time";
            col =3;
        }
        else if (selectedAlgorithm== "Preemptive Priority"){
            header << "process ID" << "Arrival Time" << "Priority";
            col =3;
        }
        else if (selectedAlgorithm == "Non-Preemptive Priority"){
            header << "process ID" << "Arrival Time" << "Priority";
            col =3;
        }
        else if (selectedAlgorithm == "Preemptive SJF"){
            header << "process ID" << "Arrival Time" << "Priority";
            col =3;
        }
        else if (selectedAlgorithm == "Non-Preemptive SJF"){
            header << "process ID" << "Arrival Time" << "Priority";
            col =3;
        }

        configureTable(ui, col, &header);
    }
}


void MainWindow::on_simulateBtn_clicked()
{
    QVector<QVector<int>> processInfo = getProcessInfo(ui);
    /*

    Call function that implements the algorithm according to selectedAlgorithm

    */
    QVector<QVector<int>> output;
    qint8 si = output.size();

    /* Adjust chart columns */
    uint32_t totalTime =0;
    for (int i=0; i< si;i++){
        totalTime+= output[i][1];
    }
    ui->chart->setColumnCount(si);
    for (int i=0; i< si;i++){
        /* set column width according to time spent in CPU [longer timer -> wider cloumn] */
        ui->chart->setColumnWidth(i,(TABLE_WIDTH/totalTime)*output[i][1]);
    }

    /* Adjust chart rows */
    ui->chart->setRowCount(2); /* row-0 for which process in CPU, row-1 shows time taken in CPU */
    ui->chart->setRowHeight(0,CHART_HEIGHT/2);
    ui->chart->setRowHeight(1,CHART_HEIGHT/2);

    /* display algorithm output */
    auto model = ui->chart->model();
    for (int i=0; i< si; i++){
        model->setData(model->index(0,i),"P" + QString::number(output[i][0]));
        model->setData(model->index(1,i),QString::number(output[i][1]));
    }
}

