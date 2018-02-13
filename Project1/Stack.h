#pragma once
#include "BigNum.h"

const int SIZE = 100; //he said he will never give us more than 100 numbers
using namespace std;

class Stack {
private:
	//gotta store stuff on something
	BigNum array[SIZE];
public:
	//gotta know where the end is
	int lastPlace;
	Stack() {
		lastPlace = 0; //obviously there is no values so there is no ends
	}
	//puts something at the end of the array then adds one to lastPlace
	void push(BigNum newBigNum) {
		array[lastPlace] = newBigNum;
		lastPlace++;
	}
	//returns the last value of the list then empties it
	BigNum pop() {
		return array[--lastPlace];
	}
	//incase I wanna look at a specific poisition
	BigNum peek(int location) {
		return array[location];
	}
	//checks to see if we are empty or not
	int isEmpty() {
		if (lastPlace) {
			return 1;
		}
		else {
			return 0;
		}
	}
	//destructor
	~Stack() {
	}
};