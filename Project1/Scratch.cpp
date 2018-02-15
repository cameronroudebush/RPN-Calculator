
#include "stdafx.h"
#include "Split.h"
#include "BigNum.h"
#include "Stack.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

BigNum add(BigNum listOne, BigNum listTwo);
BigNum multiply(BigNum listOne, BigNum listTwo);
BigNum exponent(BigNum listOne, BigNum listTwo);

void leakTest() {
	Stack test;
	for (int i = 0; i < 10000; i++) {
		BigNum num;
		num.addNum(1);
		test.push(num);
		BigNum num1 = test.pop();
	}
}

int main()
{
	system("pause");
	leakTest();
	system("pause");



	string input;
	vector<string> tokens;
	Stack bigNums;
	char done = 0; // while loop holder until end of program
	int lineCounter, errorCount = 0;
	//lineCounter = blank line count. ErrorCount checks for operations being tried without the enough numbers to do them with

	while (!done) {
		// Prompt the user and read until two blank lines
		cout << "Enter input: ";
		cout.flush();
		lineCounter = 0;
		while (getline(cin, input)) {
			//checks for a blank line
			if (input.length() == 0) {
				lineCounter++;
			}
			else {
				// Split into a vector of tokens
				lineCounter = 0;
				split(input, tokens);
			}
			//check for how many blank lines there are
			if (lineCounter == 1) {
				break;
			}
		}
		//start cycling to put the user input in places
		if (tokens.size() != 0) {
			for (int j = 0; j < tokens.size(); j++) {
				//check to see if there is a plus and check math errors
				if (tokens[j].at(0) == '+' && !errorCount) {
					if (bigNums.lastPlace <= 1) {
						//if math is tried without enoug numbers in the stack then expression error
						if (errorCount < 1) errorCount++;
					}
					else {
						//call the add and re push
						bigNums.push(add(bigNums.pop(), bigNums.pop()));
					}
				}
				else if (tokens[j].at(0) == '*' && !errorCount) {
					//check to see if there is a multiply and check math errors
					if (bigNums.lastPlace <= 1) {
						//if math is tried without enoug numbers in the stack then expression error
						if (errorCount < 1) errorCount++;
					}
					else {
						//call the multiply and re push
						bigNums.push(multiply(bigNums.pop(), bigNums.pop()));
					}
				}
				else if (tokens[j].at(0) == '^' && !errorCount) {
					//check to see if there is an exponent and check math errors
					if (bigNums.lastPlace <= 1) {
						//if math is tried without enoug numbers in the stack then expression error
						if (errorCount < 1) errorCount++;
					}
					else {
						//call the exponent and re push
						bigNums.push(exponent(bigNums.pop(), bigNums.pop()));
					}
				}
				else {
					//no operators detected add the current values into the stack as a number
					BigNum num;
					for (int i = 0; i < tokens[j].size(); i++) {
						// checks to see if there is a non number in the value so it knows its an expression error
						if (tokens[j].at(i) >= '0' && tokens[j].at(i) <= '9') {
							num.addNum(tokens[j].at(i) - '0');
						}
						else {
							errorCount++;
						}
					}
					bigNums.push(num);
				}
			}
			//print out the user input
			cout << "User Input:" << endl;
			for (int i = 0; i < tokens.size(); i++) {
				cout << tokens[i] << " ";
			}
			cout << endl;
			/*if there is too many numbers left or too many operations
				were detected with not enough numbers print out an error and stop */
			if (bigNums.lastPlace >= 2 || errorCount) {
				cout << "Expression Error" << endl;
				//empty the stack
				while (bigNums.isEmpty()) {
					bigNums.pop();
				}
			}
			else {
				//no errors detected so print out the answer
				cout << "Answer:" << endl;
				while (bigNums.isEmpty()) {
					bigNums.pop().printBigNum();
				}
				cout << endl;
			}
			errorCount = 0; //reset expression errors
			tokens.clear(); //empty the input
		}
		else {
			done = 1;
		}
	}
	system("pause");
	return 0;
}

BigNum add(BigNum listOne, BigNum listTwo) {
	Num * listOneCurrent = listOne.head;
	Num * listTwoCurrent = listTwo.head;
	int carry = 0, done = 0;
	BigNum finalValue;
	//cycle listOne and listTwo to last value in the list
	while (listOneCurrent->next) {
		listOneCurrent = listOneCurrent->next;
	}
	while (listTwoCurrent->next) {
		listTwoCurrent = listTwoCurrent->next;
	}
	//do long addition until empty
	while (!done) {
		//while a value exists in listOne add a number and move over
		if (listOneCurrent) {
			carry += listOneCurrent->number;
			listOneCurrent = listOneCurrent->previous;
		}
		//while a value exists in listTwo add a number and move over
		if (listTwoCurrent) {
			carry += listTwoCurrent->number;
			listTwoCurrent = listTwoCurrent->previous;
		}
		//check to see if we need to carry
		if (carry >= 10) {
			finalValue.addNumReverse(carry - 10);
			carry = 0;
			carry++;
		}
		//we dont need to carry so just add it
		else {
			finalValue.addNumReverse(carry);
			carry = 0;
		}
		//check to see if we are out of values
		if (!listOneCurrent && !listTwoCurrent) {
			done = 1;
		}
	}
	//print the last value
	while (carry > 0) {
		finalValue.addNumReverse(carry);
		carry -= 10;
	}
	//return our answer
	return finalValue;
}
BigNum multiply(BigNum listOne, BigNum listTwo) {
	//check to make sure we are not multiplying by 0 and if we are return 0
	if (!listTwo.head->next && listTwo.head->number == 0) {
		return listTwo;
	}
	if (!listOne.head->next && listOne.head->number == 0) {
		return listOne;
	}
	Num * listOneCurrent = listOne.head;
	Num * listTwoCurrent = listTwo.head;
	int carry = 0, value = 0, done = 0, cycle = 0;
	BigNum finalValue;
	BigNum reset; //null bigNum for resetting finalValue before adding numbers to it
	Stack partial; //Stores the numbers that will need added together from multiplication
	//cycles to end of both lists
	while (listOneCurrent->next) {
		listOneCurrent = listOneCurrent->next;
	}
	while (listTwoCurrent->next) {
		listTwoCurrent = listTwoCurrent->next;
	}
	while (!done) {
		//multiply the listOne values against the first listTwo value then reset listOne to start and shift listTwo over one
		while (listOneCurrent) {
			//multiply the values we currently have
			value = listOneCurrent->number * listTwoCurrent->number;
			//add the carry then empty it
			value += carry;
			carry = 0;
			//check to see if we need to carry
			if (value >= 10) {
				finalValue.addNumReverse(value % 10); //ex 12 % 10 is 2 or 8 % 10 is 8
				carry = floor(value / 10); //take the floor of whatever value we had so floor(81/10) is floor(8.1) = 8
			}
			else {
				//if we don't need to carry just throw it in there
				finalValue.addNumReverse(value);
			}
			value = 0;
			//shift listOne back one so we can do the next multiply
			listOneCurrent = listOneCurrent->previous;
		}
		//print the last value
		while (carry > 0) {
			finalValue.addNumReverse(carry % 10);
			carry = floor(carry / 10);
		}
		//push the final set we got
		partial.push(finalValue);
		//shift listTwo back if we have anything left
		if (listTwoCurrent) {
			listTwoCurrent = listTwoCurrent->previous;
		}
		//if we don't have anything left we are done and can add the numbers
		if (!listTwoCurrent) {
			done = 1;
		}
		finalValue = reset; //turn finalValue back to null
		cycle++;//add one to cycle so a 0 will be added to the end of the next multiply
		for (int i = 0; i < cycle; i++) finalValue.addNumReverse(0);
		listOneCurrent = listOne.head; //set listOneCurrent back off of null
		while (listOneCurrent->next) { // shift it to the end for the next multiply step
			listOneCurrent = listOneCurrent->next;
		}
		//go ahead and add so partial list never gets too big for the stack
		while (partial.lastPlace > 1) {
			partial.push(add(partial.pop(), partial.pop()));
		}
	}
	//while we have values to add do it
	while (partial.lastPlace > 1) {
		partial.push(add(partial.pop(), partial.pop()));
	}
	//return our last value
	return partial.pop();
}

BigNum exponent(BigNum listOne, BigNum listTwo) {
	//check to see if its to the 0
	if (listTwo.head->number == 0) {
		BigNum returner;
		returner.addNum(1);
		return returner; //anything to the 0 is 1
	}
	//check to see if its to the 1
	else if (listTwo.head->number == 1 && !listTwo.head->next) {
		return listOne; //anything to the 1 is itself
	}
	else {
		//if its not the special cases just keep calling multiply until done
		BigNum value = listOne;
		Num * listTwoCurrent = listTwo.head;
		string exponent;
		while (listTwoCurrent) {
			exponent.append(to_string(listTwoCurrent->number));
			listTwoCurrent = listTwoCurrent->next;
		}
		for (int i = 0; i < stoi(exponent) - 1; i++) {
			value = multiply(value, listOne); //loop multiplcation of itself the given amount of times
			
		}
		return value;
	}
}