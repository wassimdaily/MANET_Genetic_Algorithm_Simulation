
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>
#include <unistd.h>
#include "node.h"

vector<NODE> MainWindow::Init_Group(int group_size)

{
    vector<NODE> a;

    a.resize(group_size);

    int i;

    for (i = 0; i < group_size; i++)
    {
            a[i].MOVE_NODE_ABS(0,0);
            a[i].node_index = i;

    }


    return a;
}


MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{

        srand((unsigned int)time(0));
  ui->setupUi(this);
   customPlot = new QCustomPlot(this);
     int i,group_size;
     time_delay = 0;
     num_moves = 20;
     mutation_rate = 0.25;
     crossover_rate = 1;
     RCOMDEFAULT = 10;
     dd.node_group = Init_Group(NUMBER_OF_NODES_IN_GROUP);
     group_size=dd.num_nodes;
     dx = 0;
     dy = 0;


     for(i=0;i<group_size;i++)
     {
         dd.node_group[i].RCOM = RCOMDEFAULT;
     }



  MainWindow::setupGraph(ui->graph_nodes,dd,mutation_rate, crossover_rate);

}


void MainWindow::setupGraph(QCustomPlot *customPlot, NODE_GROUP &dd, double mutation_rate, double crossover_rate)
{
    int i,group_size;

    group_size = dd.num_nodes;
    QVector<double> xunits(group_size), yunits(group_size);

    for(i=0;i<group_size;i++)
    {
        xunits[i] = dd.node_group[i].x;
        yunits[i] = dd.node_group[i].y;
    }

    customPlot->addGraph();
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");
    customPlot->graph()->setLineStyle(QCPGraph::lsNone);
    customPlot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssStar, Qt::red, 6));
    customPlot->xAxis->setRange(-50,50);
    customPlot->yAxis->setRange(-50,50);
    customPlot->graph()->setData(xunits,yunits);


}

void MainWindow::setupGeneticAlgo(QCustomPlot *customPlot, NODE_GROUP &dd, double mutation_percent, double crossover_percent)
{

        int i,j,k,next_step;
        QVector<double> graph_x(dd.num_nodes), graph_y(dd.num_nodes);
        next_step = 0;
        int start_s = clock();
        dd.num_generations++;
        double ds, ds_sum;
        ds = 6.283185307/100;
        QVector<double> theta(100), x1units(100), y1units(100);
        QCPCurve *circles[dd.num_nodes];


            for(i=0;i<dd.num_nodes;i++)
            {
                dd.node_group[i].x = dd.node_group[i].x+ dx;
                dd.node_group[i].y = dd.node_group[i].y+ dy;
                dd.node_group[i].RandomWalk(1);
            }

            for(i=0;i<dd.num_nodes;i++)
            {
                dd.EVAL_POP(i);
            }

            for(i=0;i<dd.num_nodes;i++)
            {
                dd.EVAL_CURRENT(i);
                {
                    for(j=0;j<20;j++)
                    {
                        dd.EVAL_POP(i);
                        dd.Generation(mutation_rate, crossover_rate,i);
                    }
                    if (dd.current_fitness == 1000 ||
                       (dd.node_group[i].population[0].fitness_score <= dd.node_group[i].current_fitness*.96))
                    {
                        dd.node_group[i].MOVE_NODE(dd.node_group[i].population[0]);
                    }
                    else {}
                }
            }

            for (i = 0; i < dd.num_nodes; i++)
            {
                dd.node_group[i].population.resize(0);
                dd.node_group[i].population.resize(DEFAULT_POPULATION_SIZE);

            }

        theta[0] = 0;
        ds_sum = 0;
        for(i=0;i<100;i++)
        {
            theta[i] = ds_sum;
            ds_sum = ds_sum + ds;
        }


              for(k=1;(ui->graph_nodes->plottableCount()>1);k++)
              {
                  ui->graph_nodes->removePlottable(1);
              }

          cout<<ui->graph_nodes->plottableCount()<<" plottables."<<endl;



        for(j=0;j<dd.num_nodes;j++)
        {
            circles[j] = new QCPCurve(ui->graph_nodes->xAxis, ui->graph_nodes->yAxis);
            ui->graph_nodes->addPlottable(circles[j]);
        for(i=0;i<100;i++)
        {
          x1units[i] = dd.node_group[j].RCOM*cos(theta[i]) + dd.node_group[j].x;
          y1units[i] = dd.node_group[j].RCOM*sin(theta[i]) + dd.node_group[j].y;
        }

        circles[j]->setData(x1units, y1units);

          }

          for(i=0;i<dd.num_nodes;i++)
          {
              dd.EVAL_CURRENT(i);
          cout<<"Node "<<i<<": av_fit: "<<dd.node_group[i].average_fitness
          <<" : curr_fit: "<<dd.node_group[i].current_fitness
          <<" : num_inrange: "<<dd.node_group[i].num_nodes_inrange<<endl;
          }

          for(i=0;i<dd.num_nodes;i++)
          {
              graph_x[i] = dd.node_group[i].x;
              graph_y[i] = dd.node_group[i].y;
          }

          connect(ui->graph_nodes->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
          connect(ui->graph_nodes->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));



          ui->graph_nodes->xAxis->setLabel("x");
          ui->graph_nodes->yAxis->setLabel("y");
          ui->graph_nodes->graph()->setLineStyle(QCPGraph::lsNone);
          ui->graph_nodes->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssStar, Qt::red, 6));
          ui->graph_nodes->xAxis->setRange(-100,100);
          ui->graph_nodes->yAxis->setRange(-100,100);
          ui->graph_nodes->graph()->clearData();
          ui->graph_nodes->graph()->setData(graph_x, graph_y);
          ui->graph_nodes->replot();

        int stop_s = clock();
        cout << "time: " << (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000 << endl;

     cout<<"Completed in "<<next_step<<" steps."<<endl;




}






MainWindow::~MainWindow()
{
  delete ui;
}


void MainWindow::on_Stop_clicked()
{
    stop = false;
    exit(0);
}


void MainWindow::on_Step_clicked()
{
    //ui->Step->setEnabled(false);
    start = true;
    int i;

    for(i=0;i<num_moves; i++)
    {
    setupGeneticAlgo(customPlot,dd, mutation_rate, crossover_rate);
    sleep(time_delay);
    }
}

void MainWindow::on_Mutation_Slider_valueChanged(int value)
{

    mutation_rate = (double)value/100;
    cout<<"mutation_rate: "<<mutation_rate<<endl;
}

void MainWindow::on_num_moves_Slider_valueChanged(int value)
{
    num_moves = value;
    cout<<"num_moves: "<<num_moves<<endl;
}

void MainWindow::on_RCOM_Slider_valueChanged(int value)
{
    int i,m;
    m=dd.node_group.size();
    for(i=0;i<m;i++)
    {
        dd.node_group[i].RCOM = value;

    }
    cout<<"RCOM = "<<value<<endl;
}

void MainWindow::on_pushButton_North_clicked()
{
    dy = .1;

    start = true;
    int i;

    for(i=0;i<num_moves; i++)
    {
    setupGeneticAlgo(customPlot,dd, mutation_rate, crossover_rate);
    sleep(time_delay);
    }
}

void MainWindow::on_pushButton_South_clicked()
{
    dy = -.1;

    start = true;
    int i;

    for(i=0;i<num_moves; i++)
    {
    setupGeneticAlgo(customPlot,dd, mutation_rate, crossover_rate);
    sleep(time_delay);
    }
}

void MainWindow::on_pushButton_West_clicked()
{
    dx = -.1;

    start = true;
    int i;

    for(i=0;i<num_moves; i++)
    {
    setupGeneticAlgo(customPlot,dd, mutation_rate, crossover_rate);
    sleep(time_delay);
    }
}

void MainWindow::on_pushButton_East_clicked()
{
    dx = .1;

    start = true;
    int i;

    for(i=0;i<num_moves; i++)
    {
    setupGeneticAlgo(customPlot,dd, mutation_rate, crossover_rate);
    sleep(time_delay);
    }
}

void MainWindow::on_pushButton_clicked()
{

    dd.node_group.resize(dd.node_group.size() -1);
    dd.num_nodes=dd.node_group.size();
    start = true;
    int i;

    for(i=0;i<num_moves; i++)
    {
    setupGeneticAlgo(customPlot,dd, mutation_rate, crossover_rate);
    sleep(time_delay);
    }

}
