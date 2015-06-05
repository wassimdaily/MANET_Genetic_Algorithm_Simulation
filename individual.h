#ifndef INDIVIDUAL_H_
#define INDIVIDUAL_H_


#include<vector>
#include<time.h>
#include <ctime>
#include <cstdlib>



class INDIVIDUAL {

public:

	INDIVIDUAL(void);
	//initialize an individual


	vector<bool> chromosome;
	double fitness_score;

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

#endif
