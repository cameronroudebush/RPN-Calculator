#pragma once
#include <string>
#include <array>
#include <iostream>

using namespace std;

class Num {
public:
	//we are going to want to be able to look forwards and backwards
	int number;
	Num *next;
	Num *previous;
	//empty constructor
	Num() {
		number = 0;
		next = nullptr;
		previous = nullptr;
	}
	//constructor to pass stuff and have values
	Num(int newNumber, Num *newNext, Num *newPrevious) {
		number = newNumber;
		next = newNext;
		previous = newPrevious;
	}
	//allow me to set the nextValue
	void setNext(Num *newNext) {
		next = newNext;
	}
};

class BigNum {
public:
	//gotta know where to start
	Num * head;
	//don't need to pass stuff when we start out
	BigNum() {
		head = nullptr;
	}
	//copy contructor
	BigNum(const BigNum& copyMe) {
		head = nullptr;
		Num* currentNum = copyMe.head;
		while (currentNum) {
			addNum(currentNum->number);
			currentNum = currentNum->next;
		}
	}
	void operator=(BigNum& copyMe) {
		head = nullptr;
		Num* currentNum = copyMe.head;
		while (currentNum) {
			addNum(currentNum->number);
			currentNum = currentNum->next;
		}
	}
	//add a number to the list of the bigNum
	void addNum(int theNum) {
		Num *newNum, *currentNum;
		newNum = new Num();
		newNum->number = (theNum);
		if (!head) { //if head is null its easy
			head = newNum;
		}
		else {
			//cycle through to find the end and add a number there
			currentNum = head;
			while (currentNum->next) {
				currentNum = currentNum->next;
			}
			currentNum->next = newNum;
			newNum->previous = currentNum;
		}
	}
	//this does the same thing as above but in reverse order. Fixes an inefficiency I had orignally
	void addNumReverse(int theNum) {
		Num *newNum, *currentNum;
		newNum = new Num();
		newNum->number = (theNum);
		if (!head) {
			head = newNum;
		}
		else {
			currentNum = head;
			while (currentNum->previous) {
				currentNum = currentNum->previous;
			}
			currentNum->previous = newNum;
			newNum->next = currentNum;
			head = currentNum->previous;
		}
	}
	//just ptrints out the digits
	void printBigNum() {
		Num *current = head;
		//print out stuff while we can
		while (current) {
			cout << current->number;
			current = current->next;
		}
		cout << " ";
	}
	//the good ole destructor
	~BigNum() {
		Num *killMeNow = head;
		Num *killMeLater = nullptr;

		while (killMeNow) {
			killMeLater = killMeNow->next;
			delete killMeNow;
			killMeNow = killMeLater;
		}
	}
};