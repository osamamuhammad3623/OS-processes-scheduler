#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

/***************************************
    Tables Definitions
***************************************/
#define TABLE_WIDTH         (900)
#define CHART_HEIGHT        (80)
#define ARRIAVAL_TIME_INDEX (0)
#define BURST_TIME_INDEX    (1)
#define PRIORITY_INDEX      (2)

/***************************************
    Global variables declaration
***************************************/
extern int n; /* number of processes */
extern int col; /* number of columns needed for the selected algorithm */
extern int qunatum; /* needed for Round Robin algorithm */
extern QString selectedAlgorithm;


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_proceedBtn_clicked();

    void on_simulateBtn_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
