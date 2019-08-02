#include <string>
#include <stdio.h>
#include <vector>
#include <stack>
#include <bits/stdc++.h>

#include "test_framework/generic_test.h"

using std::string;
using std::stringstream;
using std::vector;
using std::stack;

/*
 * Exercise 8.2 - Evalue Reverse Polish Notation Expressions
 * Evaluate a reverse polish notation expression contained
 * within a string. Elements are seperated by commas and follow
 * the format of A, B, o
 * A is a sequence/single digit OR RPN expression
 * B is a sequance/single digit OR RPN expression
 * o is the operator of +,-,x,/
 *
 * Initial Thoughts:
 * I can use a string tokenizer to read the comma delimitted elements
 * into a vector which would make life much easier.
 * To evaluate the expression, I can use a stack to store what a RPN section
 * evaluated too. For example with "3,4,+,2,x,1,+" I would do these steps:
 * 1. Push 3 and 4 onto stack
 * 2. Read operator o (it's a +)
 * 3. stack.push(pop() + pop())
 *  Something like that then keep continuing
 */
int Evaluate(const string &expression) {
    /*
    // Check if string is empty
    if (expression.empty()) {
        return 0; // Return 0 on empty string
    }
    // Tokenize string
    vector<string> tokens;
    stringstream ss(expression);
    string temp;
    while (std::getline(ss, temp, ',')) {
        tokens.push_back(temp);
    }

    // Check for simple expression
    if (tokens.size() == 1) return std::stoi(tokens[0]);

    // Else at least 3 elements of A,B,o
    stack<int> evalStack; // Store working values
    evalStack.push(std::stoi(tokens[0]));
    // Iterate through each element
    for (int i = 1; i < tokens.size(); i++) {
        evalStack.pop();
        int a = evalStack.top();
        int b = std::stoi(tokens[i]);
        evalStack.push(b);
        string o = tokens[++i];
        if(o == "+")
        {
            evalStack.push(a+b);
        } else if(o == "-")
        {
            evalStack.push(a-b);
        } else if(o == "*")
        {
            evalStack.push(a*b);
        } else if(o == "/")
        {
            evalStack.push(a/b);
        } else {
            // invalid op
            evalStack.push(0);
        }
    }
    return evalStack.top();
     */

    // Results:
    // There must be something wrong with the input format.
    // The first string received was "121,1007,121,/,_,1006,+"
    // and I was expecting A,B,o with the rules above.
    //
    // Below is the book's solution:
    // Average running time:  490 us
    // Median running time:    <1 us

    // Ah... so after debugging the solution, the above input would
    // be valid if I simply pushed the values to the stack.
    // Receiving a number pushes a value onto the stack
    // Receiving an operator performs the operation on 2 pop'd elements
    // from the stack and pushes the result.

    stack<int> intermediate_results;
    stringstream ss(expression);
    string token;
    const char kDelimiter = ',';
    // I'm guessing this is a function within a function to simplify checking for operators
    const std::unordered_map<string, std::function<int(int, int)>> kOperators = {
            {"+", [](int x, int y) -> int { return x + y; }},
            {"-", [](int x, int y) -> int { return x - y; }},
            {"*", [](int x, int y) -> int { return x * y; }},
            {"/", [](int x, int y) -> int { return x / y; }}};

    while(getline(ss, token, kDelimiter))
    {
        if(kOperators.count(token))
        {
            const int y = intermediate_results.top();
            intermediate_results.pop();
            const int x = intermediate_results.top();
            intermediate_results.pop();

            intermediate_results.push(kOperators.at(token)(x, y));
        } else {
            intermediate_results.emplace(stoi(token));
        }
    }
    return intermediate_results.top();
}

int main(int argc, char *argv[]) {
    std::vector<std::string> args{argv + 1, argv + argc};
    std::vector<std::string> param_names{"expression"};
    return GenericTestMain(args, "evaluate_rpn.cc", "evaluate_rpn.tsv", &Evaluate,
                           DefaultComparator{}, param_names);
}
