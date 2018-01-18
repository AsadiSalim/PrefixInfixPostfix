#include <iostream>
#include <stack>
#include <string>

int getPrecedence(char _operator) {
	if (_operator != '+' && _operator != '-' && _operator != '*' && _operator != '/' && _operator != '(' && _operator != ')') {
		return -1;
	}

	if (_operator == '*' || _operator == '/') {
		return 2;
	}
	else if (_operator == '(') {
		return 0;
	}
	else {
		return 1;
	}
}

char pop(std::stack<char>& stack) {
	char temp = stack.top();
	stack.pop();
	return temp;
}

std::string infixToPostfixConverter(std::string equation, bool withP = false) {
	std::string postfixEquation = "";
	std::stack<char> operatorStack;
	int index = 0;
	
	for (int i = 0; i < equation.length(); ++i) {
		int precedence = getPrecedence(equation[i]);
		if (precedence == -1) {
			postfixEquation += equation[i];
		}
		else if (equation[i] == '(') {
			operatorStack.push(equation[i]);
		}
		else
		{
			if (equation[i] == ')') {
				while (!operatorStack.empty() && operatorStack.top() != '(') {
					postfixEquation += std::string(1, pop(operatorStack));
				}
				pop(operatorStack);
			}
			else
			{
				while (!operatorStack.empty() && precedence <= getPrecedence(operatorStack.top())) {
					postfixEquation += std::string(1, pop(operatorStack));
				}
				operatorStack.push(equation[i]);
			}
			
		}
	}
	while (!operatorStack.empty()) {
		postfixEquation += std::string(1, pop(operatorStack));
	}

	return postfixEquation;
}

void testInput(std::string equation, std::string expected) {
	std::cout << "Input:  " << equation << std::endl;
	std::cout << "result: " << infixToPostfixConverter(equation) << std::endl;
	std::cout << "answer: " << expected << std::endl << std::endl;
}

int main() {
	testInput("A+B*C-D/E-F*G*H", "ABC*+DE/-FG*H*-");
	testInput("A+(B*C-(D/E-F)*G)*H", "ABC*DE/F-G*-H*+");
	char temp;
	std::cin >> temp;
}