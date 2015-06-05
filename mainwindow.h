/***************************************************************************
**                                                                        **
**  QCustomPlot, an easy to use, modern plotting widget for Qt            **
**  Copyright (C) 2011, 2012, 2013, 2014 Emanuel Eichhammer               **
**                                                                        **
**  This program is free software: you can redistribute it and/or modify  **
**  it under the terms of the GNU General Public License as published by  **
**  the Free Software Foundation, either version 3 of the License, or     **
**  (at your option) any later version.                                   **
**                                                                        **
**  This program is distributed in the hope that it will be useful,       **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of        **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         **
**  GNU General Public License for more details.                          **
**                                                                        **
**  You should have received a copy of the GNU General Public License     **
**  along with this program.  If not, see http://www.gnu.org/licenses/.   **
**                                                                        **
****************************************************************************
**           Author: Emanuel Eichhammer                                   **
**  Website/Contact: http://www.qcustomplot.com/                          **
**             Date: 07.04.14                                             **
**          Version: 1.2.1                                                **
****************************************************************************/

/************************************************************************************************************
**                                                                                                         **
**  This is the example code for QCustomPlot.                                                              **
**                                                                                                         **
**  It demonstrates basic and some advanced capabilities of the widget. The interesting code is inside     **
**  the "setup(...)Demo" functions of MainWindow.                                                          **
**                                                                                                         **
**  In order to see a demo in action, call the respective "setup(...)Demo" function inside the             **
**  MainWindow constructor. Alternatively you may call setupDemo(i) where i is the index of the demo       **
**  you want (for those, see MainWindow constructor comments). All other functions here are merely a       **
**  way to easily create screenshots of all demos for the website. I.e. a timer is set to successively     **
**  setup all the demos and make a screenshot of the window area and save it in the ./screenshots          **
**  directory.                                                                                             **
**                                                                                                         **
*************************************************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H



#include "node.h"
#include <QMainWindow>
#include <QTimer>
#include "qcustomplot.h" // the header file of QCustomPlot. Don't forget to add it to your project, if you use an IDE, so it gets compiled.
#include <vector>
 #include <QtSerialPort/QSerialPort>


namespace Ui {
class MainWindow;

}

class MainWindow : public QMainWindow, public NODE_GROUP
{
  Q_OBJECT

  
public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  

  void setupGeneticAlgo(QCustomPlot *customPlot, NODE_GROUP &dd, double mutation_percent, double crossover_percent);
  void setupGraph(QCustomPlot *customPlot, NODE_GROUP &dd, double mutation_rate, double crossover_rate);
  vector<NODE> Init_Group(int group_size);
  double mutation_rate;
  double crossover_rate;

  
private slots:
    void on_Stop_clicked();

    void on_Step_clicked();

    void on_Mutation_Slider_valueChanged(int value);

    void on_num_moves_Slider_valueChanged(int value);

    void on_RCOM_Slider_valueChanged(int value);

    void on_pushButton_North_clicked();

    void on_pushButton_South_clicked();

    void on_pushButton_West_clicked();

    void on_pushButton_East_clicked();

    void on_pushButton_clicked();

private:
  Ui::MainWindow *ui;

  bool start,stop;
  vector<double> x_coords, y_coords;
  QCustomPlot *customPlot;
  NODE_GROUP dd;
  int i,m,num_moves;
  double time_delay,RCOMDEFAULT, dx, dy;


};



#endif // MAINWINDOW_H
