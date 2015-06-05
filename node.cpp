

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
#include"node.h"
#include <QMainWindow>
#include <QTimer>





using namespace std;

vector<NODE> Init_Group(int number_of_nodes)

{

    vector<NODE> a;

    a.resize(number_of_nodes);

    int i,j,r;
    r = 0;

    for (i = 0; i < number_of_nodes; i++)
    {
            a[i].MOVE_NODE_ABS(0,0);
    }



    return a;
}

NODE_GROUP::NODE_GROUP(void)
{

    num_nodes = NUMBER_OF_NODES_IN_GROUP;
    node_group = Init_Group(num_nodes);
    num_generations=0;

}

NODE_GROUP NODE_GROUP::operator=(NODE_GROUP &b)
{

        NODE_GROUP a;

        cout<<"a.node_group.size(): "<<a.node_group.size()<<endl;
        a.num_nodes = b.num_nodes;
        a.node_group = b.node_group;
        a.num_generations = b.num_generations;
        return a;
}


NODE_GROUP::NODE_GROUP(int a)
{

    num_nodes = a;
    node_group = Init_Group(num_nodes);
    num_generations =0;
}

INDIVIDUAL::INDIVIDUAL(void)
{

    int i;
    int m;
    m = 6;
    fitness_score = 0;
    nodes_inrange = NUMBER_OF_NODES_IN_GROUP-1;

    chromosome.resize(m);
    for (i = 0; i < m; i++)
    {
        chromosome[i] = rand() % 2;

    }


    //Initialize the direction and speed genes to a random bit
}




    POLAR_COORDS::POLAR_COORDS(void)
    {

        mag = 0;
        angle = 0;
    }




COORDS::COORDS(void)
{
	x = 0;
	y = 0;



}

bool COORDS::operator <(const COORDS &p) const

{
	return x < p.x || (x == p.x && y < p.y);
}


int COORDS::operator==(COORDS a)

{
	if ((x == a.x) && (y == a.y))
	{
		return 1;
	}

	else

	{
		return 0;
	}
}




double cross(const COORDS &O, const COORDS &A, const COORDS &B)
{
	return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

vector<COORDS>  Convex_Hull_Coords(vector<COORDS> P);

double PolygonArea(vector<COORDS> &node_group_coords, int size_of_node_group);






    void NODE::RandomWalk(int one_in_odds)
    {

        if (rand() %one_in_odds == 1)
        {

            if(rand()%2 == 1)
            {
                x = x + rand() %3 -1;
            }

            else
            {
                y = y + rand() %3 -1;
            }

        }
         else {}


    }

COORDS NODE::NODE_LOC(NODE a)

{

	COORDS xycoords;



    xycoords.x = a.x;
    xycoords.y = a.y;

	return xycoords;

}

void NODE::MOVE_NODE_ABS(double a, double b)

{
    x = a;
    y = b;
}

void NODE::MOVE_NODE(INDIVIDUAL &ind1)

{
    int direction, speed, x2, y2;
	direction = 0;
	speed = 0;
	x2 = 0;
	y2 = 0;

	if (ind1.chromosome[0] == 1)
	{
        direction = direction + 1;
	}
	if (ind1.chromosome[1] == 1)
	{
        direction = direction + 2;
	}
    if (ind1.chromosome[2] == 4)
	{
        direction = direction + 1;
	}
	if (ind1.chromosome[3] == 1)
	{
        speed = speed + 2;
	}
	if (ind1.chromosome[4] == 1)
	{
        speed = speed + 4;
	}
	if (ind1.chromosome[5] == 1)
	{
        speed = speed + 8;
	}
	////////////////
	if (speed == 0)
    {}
	else
	{
		{
			if (direction == 0)
			{
				y2 = 1 * speed;
			}
			else if (direction == 1)
			{
				y2 = -1 * speed;
			}
			else if (direction == 2)
			{
				x2 = 1 * speed;
			}
			else if (direction == 3)
			{
				x2 = -1 * speed;
			}
			else if (direction == 4)
			{
				y2 = 1 * speed;
				x2 = 1 * speed;
			}
			else if (direction == 5)
			{
				y2 = -1 * speed;
				x2 = -1 * speed;
			}
			else if (direction == 6)
			{
				y2 = 1 * speed;
				x2 = -1 * speed;
			}
			else if (direction == 7)
			{
				y2 = -1 * speed;
				x2 = 1 * speed;
			}
		}
	}
    x = (x + x2);
    y = (y + y2);
}

void NODE::MOVE_NODE(int d2, int d1, int d0, int b1, int b0)
{}



vector<COORDS> NODE_COORDS_INRANGE(NODE reference_node, NODE_GROUP b)
{}





void  NODE::INIT_POP(void)

{
    population = vector<INDIVIDUAL>(DEFAULT_POPULATION_SIZE);
    steps = steps + 1;
}


NODE::NODE(void)
{
    x = 0;
    y = 0;
	n = DEFAULT_POPULATION_SIZE;
	steps = 0;
	minimum_fitness = 10000000;
	average_fitness = 10000000;
    current_fitness = 10000000;
	fitsum = 0;
    num_nodes_inrange=NUMBER_OF_NODES_IN_GROUP-1;
    INIT_POP();
}

NODE::NODE(double a, double b, double c)
{
    x = a;
    y = b;
	RCOM = c;
	n = DEFAULT_POPULATION_SIZE;
	steps = 0;
	minimum_fitness = 10000000;
	average_fitness = 10000000;
    current_fitness = 10000000;
    fitsum = 0;
    num_nodes_inrange=NUMBER_OF_NODES_IN_GROUP-1;
	INIT_POP();
}

NODE::NODE(double a, double b)
{
    x = a;
    y = b;
	n = DEFAULT_POPULATION_SIZE;
	steps = 0;
	minimum_fitness = 10000000;
	average_fitness = 10000000;
    current_fitness = 10000000;
    fitsum = 0;
    num_nodes_inrange=NUMBER_OF_NODES_IN_GROUP-1;
	INIT_POP();
}
void NODE_GROUP::DISPLAY_POP(int index)
{
    int i,j,population_size, chromosome_length;
    population_size = node_group[index].population.size();
    chromosome_length = node_group[index].population[0].chromosome.size();
    cout << "Population for Node #"<<node_group[index].node_index<<": "<<endl;

    for (i = 0; i < population_size; i++)
	{
        for (j = 0; j < chromosome_length; j++)
		{
            cout << node_group[index].population[i].chromosome[j];
		}
        cout<<"   :   "<<node_group[index].population[i].fitness_score
            <<"   :   "<<node_group[index].population[i].nodes_inrange<<endl;
	}
    cout << endl;
}

void EVAL(NODE_GROUP &eval_group)
{}

void NODE_GROUP::EVAL_CURRENT(int index)
{
    int i;
    double temp_fitness,temp_radius;
    temp_fitness=0;
    node_group[index].num_nodes_inrange=0;
    for(i=0;i<num_nodes; i++)

        if(node_group[index].node_index != node_group[i].node_index)
        {
            temp_radius = sqrt(pow(node_group[index].x - node_group[i].x,2) + pow(node_group[index].y - node_group[i].y,2));

        if(temp_radius <= node_group[index].RCOM)
        {
            node_group[index].num_nodes_inrange++;
            temp_fitness = temp_fitness + (node_group[index].RCOM -temp_radius -1);
        }
        else {}
        node_group[index].current_fitness = temp_fitness;

        if(node_group[index].num_nodes_inrange <1)
        {
            node_group[index].current_fitness = 1000;
        }
        else {}
        }
        else {}
}


void NODE_GROUP::EVAL_POP(int index)
//Assigns a fitness value to each solution/individual in the population;
//afterwards the population is sorted from most fit (0) to least fit (infinity)
{
    int i,j, population_size;
    double temp_fitness, temp_radius,x_coord, y_coord;
    NODE test_node;
    test_node = node_group[index];
    population_size=test_node.population.size();
    x_coord = node_group[index].x;
    y_coord = node_group[index].y;
    node_group[index].fitsum=0;
    for(i=0;i<population_size;i++)
    {
        test_node.MOVE_NODE_ABS(x_coord,y_coord);
        test_node.MOVE_NODE(test_node.population[i]);
        temp_fitness = 0;
        node_group[index].population[i].nodes_inrange=0;
        for(j=0;j<num_nodes; j++)
        {
            if(test_node.node_index != node_group[j].node_index)
            {
                temp_radius = sqrt(pow((test_node.x - node_group[j].x),2) + pow((test_node.y - node_group[j].y),2));
            }
            else {}
            if (temp_radius <= test_node.RCOM)
                    {
                    temp_fitness = temp_fitness + (test_node.RCOM - temp_radius -1);
                    node_group[index].population[i].nodes_inrange++;
                    }
            else {}
        }
        if(test_node.population[i].nodes_inrange <1)
        {
            temp_fitness = 1000;
        }
        else {}

        node_group[index].population[i].fitness_score = temp_fitness;
        node_group[index].fitsum = node_group[index].fitsum + temp_fitness;
    }
    node_group[index].average_fitness = fitsum/population_size;
    node_group[index].sort_population();
    node_group[index].minimum_individual=node_group[index].population[0];
}

void NODE_GROUP::Generation(double mutation_percent, double crossover_percent, int index)
{
    int i,j,k,crossover_point,mutation_location,population_size;
    INDIVIDUAL child;
    k=0;
    population_size = node_group[index].population.size();
    node_group[index].steps++;

    for(i=0;i<population_size;i++)
    {
    //perform crossover first
    if (double(rand() % 101)/100 < crossover_percent)
    {
        crossover_point = rand() % 4 + 1;
    }
    else
    {
        crossover_point = 5;
    }
    for(j=0;j<crossover_point;j++)
    {
        child.chromosome[j] = node_group[index].population[k].chromosome[j];
    }
    k++;
    for(j=crossover_point;j<int(node_group[index].population[k].chromosome.size());j++)
    {
        child.chromosome[j] = node_group[index].population[k].chromosome[j];
    }
    k++;
    if (k % population_size)
    {
        k = 0;
    }
    else {}
    if (double(rand() % 101)/100 < mutation_percent)
    {
        mutation_location = rand() % child.chromosome.size();
        child.chromosome[mutation_location] = !child.chromosome[mutation_location];
    }
    else {}
            node_group[index].population.push_back(child);
    }
    EVAL_POP(index);
    node_group[index].population.resize(population_size);
}


void Roulette(double mutation_percent, double crossover_percent, int num_iterations, NODE_GROUP &eval_node_group)
{
}

void Genetic_Ops(double mutation_percent,double crossover_percent,NODE_GROUP node_group)
{
}



void NODE::NODE_PRINT_POP(void)
{}

// Based on C++ monotone chain 2D convex hull algorithm found on:

//http:// en.wikibooks.org/wiki/Algorithm_Implementation/Geometry/Convex_hull/Monotone_chain#C.2B.2B

//Adapted for use with COORDS class
// Asymptotic complexity: O(n log n).

vector<COORDS>  Convex_Hull_Coords(vector<COORDS> P)


{
	int i;
	int num_of_coords;
	num_of_coords = P.size();
	int k;

	k = 0;

	vector<COORDS> H(2 * num_of_coords);

	// Sort points lexicographically
	sort(P.begin(), P.end());


	// Build lower hull
	for (i = 0; i < num_of_coords; ++i) {
		while (k >= 2 && cross(H[k - 2], H[k - 1], P[i]) <= 0) k--;
		H[k++] = P[i];
	}

	// Build upper hull
	for (int i = num_of_coords - 2, t = k + 1; i >= 0; i--) {
		while (k >= t && cross(H[k - 2], H[k - 1], P[i]) <= 0) k--;
		H[k++] = P[i];
	}

	H.resize(k);

	if (k != 0)
	{
		H.resize(k - 1);
	}

	return H;
}




/////////////////////////////////////////////////////////////////////////


//PolygonArea Algorithm taken from http:// www.mathopenref.com/coordpolygonarea2.html
//
// CJN 9/26/2014

double PolygonArea(vector<COORDS> &node_group_coords, int size_of_node_group)
{
	double Area;
	int i;
	int j;

	Area = 0;

	j = size_of_node_group - 1;
	for (i = 0; i < size_of_node_group; i++)
	{
		Area = Area + (node_group_coords[j].x + node_group_coords[i].x) * (node_group_coords[j].y - node_group_coords[i].y);


		j = i;
	}


	return abs(Area / 2);
}

vector<COORDS> Get_Node_Group_Coords(NODE_GROUP &eval_group)
{}


void NODE::sort_population()
{
    int i, j, min_pos, population_size;
    double min_fitness, temp_fitness;
    INDIVIDUAL temp_ind;
    population_size = population.size();

    for (j = 0; j < population_size; j++)
    {
        min_fitness = population[j].fitness_score;
        min_pos = j;

        for (i = j; i < population_size; i++)
        {
            if(population[i].fitness_score < min_fitness)
            {
                min_fitness = population[i].fitness_score;
                min_pos = i;
            }
           else {}
        }
        temp_ind = population[j];
        population[j] = population[min_pos];
        population[min_pos] = temp_ind;

        temp_fitness = population[j].fitness_score;
        population[j].fitness_score = min_fitness;
        population[min_pos].fitness_score = temp_fitness;

        }

    minimum_individual = population[0];
    minimum_fitness = population[0].fitness_score;
}


bool validate_solution(INDIVIDUAL test_ind, NODE &test_node, NODE_GROUP &eval_group)
{}
