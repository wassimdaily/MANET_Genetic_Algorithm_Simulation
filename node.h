#ifndef NODE_H_
#define NODE_H_


#include<algorithm>
#include<cmath>
#include<complex>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<time.h>
#include<vector>
#include<math.h>
#include <QMainWindow>
#include <QTimer>


using namespace std;

#define DEFAULT_POPULATION_SIZE 20
#define NUMBER_OF_NODES_IN_GROUP 20


class INDIVIDUAL {


public:

    INDIVIDUAL(void);

    //initialize an individual



    vector<bool> chromosome;
    double fitness_score;
    int nodes_inrange;

    //d2, d1, and d0 are genes representing
    //the binary-coded direction in which a node can move

    //s2, s1, s0 are genes representing the binary-coded speed
    //of a node.

    // Direction:				Speed:
    //  d2d1d0					s2s1s0
    //000: North			000: immobile
    //001: South			001: 1 unit/move
    //010: East				010: 2 units/move
    //011: West				011: 3 units/move
    //100: North East		100: 4 units/move
    //101: South West		101: 5 units/move
    //110: North West		110: 6 units/move
    //111: South East		111: 7 units/move


};

class POLAR_COORDS {
//Polar Coordinate class.


public:

    POLAR_COORDS(void);

    double mag;
    double angle;
    //Phase is in radians.


};

class COORDS {


public:

    COORDS(void);
    double x;
    double y;

    int operator==(COORDS a);
    bool operator<(const COORDS &p) const;
};




class NODE : public COORDS
{



public:


    NODE(void); //i.e. p1.NODE();
    //the constructor
    //no return value

    NODE(double, double, double); //i.e. p1.NODE(1,1, 5);
    //initialize the node to a particular location denoted by Cartesian (x,y) coordinates
    //initializes the node's RCOM to 5 units

    NODE(double, double); //i.e. p1.NODE(1,1);
    //initialize the node to a particular location denoted by Cartesian (x,y) coordinates
    //initializes the node's RCOM to 4 units by default


    void sort_population();

    void NODE_PRINT_POP(void);
    //Print the chromosome patterns for each individual in the node's current population

    void MOVE_NODE(int, int, int, int, int); //i.e. p1.MOVE_NODE(1,0,0, 0,1,1);
    //this method call would move the node northeast two units.
    //i.e. the second integer indicates the number of units to move in a given direction
    //the first integer indicates a direction to move according to the following table:
    // Direction:				Speed:
    //  d2d1d0					s2s1s0
    //000: North			000: immobile
    //001: South			001: 1 unit/move
    //010: East				010: 2 units/move
    //011: West				011: 3 units/move
    //100: North East		100: 4 units/move
    //101: South West		101: 5 units/move
    //110: North West		110: 6 units/move
    //111: South East		111: 7 units/move
    //
    //i.e. if we have MOVE_NODE(101,011),
    //the node would move 3 units south and 3 units west (x-3,y-3)

    void MOVE_NODE(INDIVIDUAL&);
    //
    //Move the node to the position corresponding to the direction and speed indicated by the given INDIVIDUAL.
    //RELATIVE TO THE NODE'S CURRENT POSITION


    void MOVE_NODE_ABS(double a, double b);
    //Move the node to the given coordinates, absolutely. NOT RELATIVE TO THE NODE's CURRENT POSITION

    double x;		//node's current x-coordinate
    double y;		//node's current y-coordinate
    double RCOM;	//indicates the range (given in units) over which a node can detect other nodes.
    //i.e. if RCOM=4, the node can detect other nodes within +-4 units in the x and y directions.
    double minimum_fitness;
    double average_fitness;
    double fitsum;
    double current_fitness;
    INDIVIDUAL minimum_individual;

    int n;		//number of individuals in the population
    int steps;	//the number of genetic algorithm iterations completed
    int num_nodes_inrange;
    vector<int> Parent_Indices;


    vector<INDIVIDUAL> population; //node's population of individuals. Initialized randomly when node is constructed.

    void INIT_POP(void);

    int node_index;



    COORDS NODE_LOC(NODE a);

    bool NODE_LOC_EQUAL(NODE a);

    bool NODE_LOC_EQUAL(COORDS a);






    void RandomWalk(int one_in_odds);








};

class NODE_GROUP : public NODE
{
public:

    NODE_GROUP(void);
    NODE_GROUP(int a);
    NODE_GROUP operator=(NODE_GROUP &b);
    int num_nodes;
    int num_generations;
    vector<NODE> node_group;
    void EVAL_CURRENT(int index);
    void Generation(double mutation, double crossover, int index);
    void EVAL_POP(int index);
    void DISPLAY_POP(int index);

};



void Roulette(double mutation_percent, double crossover_percent,int num_iterations, NODE_GROUP &eval_node_group);
void EVAL(NODE_GROUP &eval_group);
vector<COORDS> Get_Node_Group_Coords(NODE_GROUP &eval_group);
vector<COORDS>  Convex_Hull_Coords(vector<COORDS> P);
double PolygonArea(vector<COORDS> &node_group_coords, int size_of_node_group);

bool validate_solution(INDIVIDUAL test_ind, NODE &test_node, NODE_GROUP &test_node_group);



#endif
