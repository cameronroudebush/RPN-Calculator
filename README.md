# RPN-Calculator
Project 1 for my CS 3100 class (Data Structures)

Project details below: 

CS 3100 – Data Structures and Algorithms
Project #1 – Infinite Precision Arithmetic
Learning Objectives

    Apply basic object oriented programming concepts in C++
    Construct and use C++ objects making effective use of references and pointers
    Implement an abstract data type conforming to specific design specifications

Overview

In most programming languages, integer values are of a fixed size, e.g., 32 bits, 64 bits etc. The number of bits used to represent integers limits the magnitude of the numbers that can be represented. For example with 32 bits, the largest positive value is 232 or 4,294,967,296 which has 10 decimal digits of precision. For many problems 32 or 64 bits representation is sufficient, but there are problems that require much higher precision (e.g. banking). When this is the case, we can implement infinite precision arithmetic in software.
Assignment

Implement an infinite precision arithmetic package for non-negative integers and a stack-based calculator that operates on infinite precision values, along with support list and stack classes to support your solution.
Details

The input to this program should be read from standard input and the output should be directed to standard output. The name of the program should be Project1.

The input will consist of a series of arithmetic expressions given in postfix or Reverse Polish Notation (RPN). In RPN, the operands come before the operator. For example, you normally see multiplication written in infix notation as (a * b). In RPN, this expression would appear as (a b *). For expressions with more than one operator, each time an operator is encountered, it is applied to the two immediately preceding sub-expressions. For example, (a + b * c) in infix notation would be (a b c * +) in RPN. This means that operands b and c are multiplied, then the results of the multiplication are added to operand a. In RPN, operator precedence is not required because operators are always evaluated left to right. Thus, the expression ((a + b) * c) is written (a b + c *) in RPN.

Input operands consist of a string of digits, and may be of any length. You should trim any zeros appearing at the beginning of an operand (e.g. 000231 should be stored as 231). Expressions may also be of any length. Spaces and line breaks may appear within the expression arbitrarily, with the rule that a space or line break terminates an operand, and a blank line (i.e., two line breaks in a row) terminates an expression.

The operations are limited to addition (+), multiplication (*), and exponentiation (^). An error should be reported whenever the number of operators and operands are inconsistent (i.e., if there are no operands to the left of an operator, or if the expression ends without providing sufficient operators).

When an error is detected, processing should stop on the current expression, and your program should proceed to the next expression. For each expression, echo the input, followed by the result of the operation, or an error message, as appropriate. Be sure that the result is clearly marked on the output for readability.
Implementation

RPN simplifies the project since the evaluation of expressions can be implemented using a stack. As the expression is read in, operands are placed on the stack. Whenever an operator is read, the top two operands are removed from the stack, the operation is evaluated, and the result is placed back onto the stack. You may assume that the stack will never hold more than 100 operands.

The main problem in this project is implementation of infinite precision integers and calculation of the arithmetic operations +, *, and ^.

Integers are to be represented in your program by a linked list of digits, one digit per list node. Each digit may be represented as a character or as an integer, as you prefer. You will likely find that operations are easier to perform if the list of digits is stored in reverse order (low order to high order).

Addition is easily performed by starting with the low order digits of the two integers, and add each pair of digits as you move to the high order digits. Don't forget to carry when the sum of two digits is 10 or greater.

Multiplication is performed by multiplying the low order digit of the second operand against the entire first operand. Then the next digit of the second operand is multiplied against the first number, with a “0” placed at the end. This partial result is added to the partial result obtained from multiplying the previous digit. The process of multiplying by the next digit and adding to the previous partial result is repeated until the full multiplication has been completed.

Exponentiation is performed by multiplying the first operand to itself the appropriate number of times, decrementing the exponent once each time until done. In order to simplify implementation, you are guaranteed the exponent will be small enough to fit in an integer variable (C++ int datatype). You should write a routine to convert a number from the list representation to an integer variable, and use this to convert the top operand on the stack when the exponentiation operator is encountered. Be careful with exponents of 0 or 1.
Restrictions

Since one of the purposes of this assignment is to give you experience with dynamic memory allocation, stacks and lists, you must build your own list and stack class. Do not use the STL library stack or list classes in your solution.
Sample Input

Note that expressions can span multiple lines. A blank line (two linefeeds in a row) terminates and expression. Possible inputs that might be typed in the console window include:

000056669777     99999911111 + 352324012 + 03 ^
      555557778 *
<blank line>

99999999 990001 * 01119111
                55565  33333 + * +
88888888       +
<blank line>

123456789 1111111111 * 111119 2111111 9111111 * + * 1 ^
<blank line>

9 1 +        5 *     00000000 +
<blank line>

999999999 0 *
<blank line>

9 0 ^
<blank line>

5555555 333333
5454353 999999 666666 01 ^ * * +
<blank line>

3432 3333 9999 +
* ^ * * 6666 +
<blank line>


Sample Output

The output should echo the RPN expression on the first line. If there is no error in the expression, the result of evaluating the expression is displayed on the next line. Finally a blank line is used to separate successive expressions. If there is an error, display the RPN expression, the message “Expression Error” and a blank line.

The appropriate output for each of the input expressions given above are:

56669777 99999911111 + 352324012 + 3 ^ 555557778 *
562400792227677956625810678708149922000000
<blank line>

	Do not display leading zeros, linefeeds, or extra space.

99999999 990001 * 1119111 55565 33333 + * + 88888888 +
99099674628565
<blank line>

123456789 1111111111 * 111119 2111111 9111111 * + * 1 ^
2638486500477638652325851269760
<blank line>

	This is to test if the program can handle 1 as an exponent.

9 1 + 5 * 0 +
50
<blank line>

	This tests if the program can handle adding zero.

999999999 0 *
0
<blank line>

	This tests if the program can handle multiplication by zero.

9 0 ^
1
<blank line>

	This tests if the program can handle a zero exponent.

5555555 333333 5454353 999999 666666 1 ^ * * +
Expression Error
<blank line>

	This tests the error of having an insufficient number of operators. The numbers remaining in the stack are 3636228060866636235 and 5555555.

3432 3333 9999 + * ^ * * 6666 +
Expression Error
<blank line>

	This tests the error of having an insufficient number of operands. The program should ignore the remainder of the input until a new expression begins.

This project is worth 50 points, distributed as follows:
Task 	                                                                                                                Points
Your program correctly reads and echos input expressions, removing extra whitespace, linefeeds, and leading zeros. 	  5
Your program correctly implements an RPN calculator on input expressions using a stack data structure. 	              5
Your program correctly implements infinite-precision unsigned integers as a linked list of digits. 	                  5
Your program correctly implements the + operation with no errors. 	                                                  5
Your program correctly implements the * operation, including multiplication by zero, with no errors. 	                5
Your program correctly implements the ^ operation, including exponents of zero or one, with no errors. 	              5
Your program has no memory leaks. 	                                                                                  5
Your correctly handles incorrect input expressions, printing an error message without crashing. 	                    5
Your data structures (classes) are well-designed and efficiently implemented. 	                                      5
Your follows programming best practices (good variable names, program structure, etc.) and is well documented.        5
