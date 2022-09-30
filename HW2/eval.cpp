
#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;

//function declaration
int evaluate(string infix, string& postfix, bool& result);
bool valid(string infix);
string InfixToPostfix(string infix);
bool solvePostfix(string postfix);
//function implementation
bool valid(string infix)
{
	//if the infix size is 0, then return false
	if (infix.size() == 0)
		return false;
	//if that is not the case, then change the infix string such that it does not have spaces
	//check to make sure the infix has T and/or F
	int bad_ch = 0;
	int operands = 0;
	int parentheses_completed = 0;
	string no_space_infix = "";
	for (int i = 0; i < infix.size(); i++) 
	{
		if (infix[i] != ' ')
		{
			no_space_infix += infix[i];
			if (infix[i] != 'T' && infix[i] != 'F' && infix[i] != '(' && infix[i] != ')' && infix[i] != '&' && infix[i] != '|' && infix[i] != '!')
				bad_ch++;
			if (infix[i] == 'T' || infix[i] == 'F')
				operands++;
			if (infix[i] == '(')
				parentheses_completed++;
			if (infix[i] == ')')
				parentheses_completed--;
		}
	}
	//if no T or F, or a bad character shows, or the parentheses are incomplete, return false
	if (bad_ch > 0 ||operands == 0 || parentheses_completed != 0)
		return false;
	//loop through the no_space_infix and check that all rules are met
	int nl = no_space_infix.size();
	//the infix cannot end with a binary or unary operator or (, and it cannot begin with a binary operator or )
	if (no_space_infix[nl - 1] == '|' || no_space_infix[nl - 1] == '&' || no_space_infix[nl - 1] == '!' || no_space_infix[nl-1] == '(' || no_space_infix[0] == '|' || no_space_infix[0] == '&' || no_space_infix[0] == ')' ) 
		return false;
	for (int j = 0; j < nl; j++)
	{
		if (j >= 1)
		{
			if (no_space_infix[j] == '|' || no_space_infix[j] == '&') //before - T,F,) //after - T,F,!,( //everything else is invalid
			{
				if ((no_space_infix[j - 1] != 'T' && no_space_infix[j - 1] != 'F' && no_space_infix[j - 1] != ')') || (no_space_infix[j + 1] != 'T' && no_space_infix[j + 1] != 'F' && no_space_infix[j + 1] != '(' && no_space_infix[j + 1] != '!'))
					return false;
			}
		}
		if (no_space_infix[j] == 'T' || no_space_infix[j] == 'F') //if we have T,F can't have T,F, ! after the operand
		{
			if (no_space_infix[j + 1] == 'T' || no_space_infix[j + 1] == 'F' || no_space_infix[j + 1] == '(' || no_space_infix[j + 1] == '!')
				return false;
		}
	}
	return true;
}

string InfixToPostfix(string infix)
{
	string postfix;
	stack<char> OperatorStack;
	for (auto ch : infix)
	{
		switch (ch)
		{
		case 'T':
		case 'F':
			postfix += ch;
			break;
		case '!':
			OperatorStack.push(ch);
			break;
		case '(':
			OperatorStack.push(ch);
			break;
		case ')':
			while (OperatorStack.top() != '(')
			{
				postfix += OperatorStack.top();
				OperatorStack.pop();
			}
			OperatorStack.pop();
			break;
		case '|':
		case '&':
			while (!OperatorStack.empty() && OperatorStack.top() != '(' && ch >= OperatorStack.top())
			{
				postfix += OperatorStack.top();
				OperatorStack.pop();
			}
			OperatorStack.push(ch);
			break;
		default:
			break;
		}
	}
	while (!OperatorStack.empty())
	{
		postfix += OperatorStack.top();
		OperatorStack.pop();
	}
	return postfix;
}

bool solvePostfix(string postfix)
{
	stack<char> OperandStack;
	for (auto ch : postfix)
	{
		if (ch == 'T' || ch == 'F')
		{
			OperandStack.push(ch);
		}
		else if (ch == '!')
		{
			char result;
			char operand = OperandStack.top();
			OperandStack.pop();
			if (operand == 'T')
				result = 'F';
			if (operand == 'F')
				result = 'T';
			OperandStack.push(result);
		}
		else
		{
			char operand2 = OperandStack.top();
			OperandStack.pop();
			char operand1 = OperandStack.top();
			OperandStack.pop();
			if (ch == '&')
			{
				char result1;
				if (operand1 == 'T' && operand2 == 'T')
					result1 = 'T';
				else
					result1 = 'F';
				OperandStack.push(result1);
			}
			if (ch == '|')
			{
				char result2;
				if (operand1 == 'T' || operand2 == 'T')
					result2 = 'T';
				else
					result2 = 'F';
				OperandStack.push(result2);
			}
		}
	}
	if (OperandStack.top() == 'T')
		return true;
	else
	{
		return false;
	}
}

int evaluate(string infix, string & postfix, bool & result)
{
	if (!valid(infix))
		return 1;
	else
	{
		postfix = InfixToPostfix(infix);
		result = solvePostfix(postfix);
		return 0;
	}
}

int main()
{
	string pf;
	bool answer;
	assert(evaluate("T| F", pf, answer) == 0 && pf == "TF|"  &&  answer);
	assert(evaluate("T|", pf, answer) == 1);
	assert(evaluate(")(", pf, answer) == 1);
	assert(evaluate("F F", pf, answer) == 1);
	assert(evaluate("TF", pf, answer) == 1);
	assert(evaluate("()", pf, answer) == 1);
	assert(evaluate(")T(", pf, answer) == 1);
	assert(evaluate("&T", pf, answer) == 1);
	assert(evaluate("&T", pf, answer) == 1);
	assert(evaluate("T&", pf, answer) == 1);
	assert(evaluate("Tr", pf, answer) == 1);
	assert(evaluate("r", pf, answer) == 1);
	assert(evaluate("(T|F)T(", pf, answer) == 1);
	assert(evaluate("T&F&", pf, answer) == 1);
	assert(evaluate("T(F|T)", pf, answer) == 1);
	assert(evaluate("T(&T)", pf, answer) == 1);
	assert(evaluate("(T&(F|F)", pf, answer) == 1);
	assert(evaluate(" ", pf, answer) == 1);
	assert(evaluate("T|F", pf, answer) == 0 && pf == "TF|" && answer);
	assert(evaluate("T&F", pf, answer) == 0 && pf == "TF&" && !answer);
	assert(evaluate("F  |  !F & (T&F) ", pf, answer) == 0 && pf == "FF!TF&&|" && !answer);
	assert(evaluate(" F  ", pf, answer) == 0 && pf == "F" && !answer);
	assert(evaluate("((T))", pf, answer) == 0 && pf == "T"  &&  answer);
	assert(evaluate("T", pf, answer) == 0 && pf == "T"  &&  answer); 
	assert(evaluate("(F)", pf, answer) == 0 && pf == "F"  &&  !answer);
	assert(evaluate("T&(F)", pf, answer) == 0 && pf == "TF&"  &&  !answer);
	assert(evaluate("T & !F", pf, answer) == 0 &&  answer);
	assert(evaluate("!(F|T)", pf, answer) == 0 &&  !answer);
	assert(evaluate("!F|T", pf, answer) == 0 &&  answer);
	assert(evaluate("T|F&F", pf, answer) == 0 &&  answer);
	assert(evaluate("T&!(F|T&T|F)|!!!(F&T&F)", pf, answer) == 0 &&  answer);
	cout << "Passed all tests" << endl;
}
