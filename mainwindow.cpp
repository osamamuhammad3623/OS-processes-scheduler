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

}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
Supported algorithms: - Round Robin
                        FCFS
                        Preemptive Priority
                        Non-Preemptive Priority
                        Preemptive SJF
                        Non-Preemptive SJF
*/

void MainWindow::on_proceedBtn_clicked()
{
    int n = ui->n->value() ;
    if (n == 0){
        QMessageBox::information(this, "Processes number", "Enter a valid number of processes!");

    }else{
        QStringList header;
        qint16 tableWidth=780;
        ui->table->setRowCount(n);
        int algo_columns;
        if (ui->algorithm->currentText() == "Round Robin"){

            /* adjust table */
            algo_columns = 2;
            ui->table->setColumnCount(algo_columns);
            for (int i=0; i< algo_columns; i++){
                ui->table->setColumnWidth(i,tableWidth/algo_columns);
            }
            header << "process ID" << "Arrival Time";
            ui->table->setHorizontalHeaderLabels(header);


        }else if (ui->algorithm->currentText() == "FCFS"){
            algo_columns = 3;
            ui->table->setColumnCount(algo_columns);
            for (int i=0; i< algo_columns; i++){
                ui->table->setColumnWidth(i,tableWidth/algo_columns);
            }
            header << "process ID" << "Arrival Time" << "Burst Time";
            ui->table->setHorizontalHeaderLabels(header);
        }

        else if (ui->algorithm->currentText() == "Preemptive Priority"){
            algo_columns = 3;
            ui->table->setColumnCount(algo_columns);
            for (int i=0; i< algo_columns; i++){
                ui->table->setColumnWidth(i,tableWidth/algo_columns);
            }
            header << "process ID" << "Arrival Time" << "Priority";
            ui->table->setHorizontalHeaderLabels(header);
        }
    }
}


void MainWindow::on_simulateBtn_clicked()
{
    QVector<QVector<int>> output {{1,5},{2,10},{1,7},{3,3},{3,4}};
    qint8 si = output.size();
    ui->chart->setColumnCount(si);
    ui->chart->setRowCount(2);
    int chartHeight=80;
    ui->chart->setRowHeight(0,chartHeight/2);
    ui->chart->setRowHeight(1,chartHeight/2);

    auto model = ui->chart->model();
    for (int i=0; i< si; i++){
        model->setData(model->index(0,i),"P" + QString::number(output[i][0]));
        model->setData(model->index(1,i),QString::number(output[i][1]));
    }
}

