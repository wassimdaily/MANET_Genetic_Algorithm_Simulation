#include <algorithm>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<iostream>
#include<random>
#include<time.h>
#include <vector>

using namespace std;


bool Rand_Gen(void)

{


	bool binary_array[2];

	binary_array[0] = 0;
	binary_array[1] = 1;



	return binary_array[rand() % 2];
}

