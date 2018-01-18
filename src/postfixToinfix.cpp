#include <iostream>
#include <stack>
#include <string>

char pop(std::stack<char>& stack) {
	char temp = stack.top();
	stack.pop();
	return temp;
}


std::string postfixToInfix(std::stack<char>& equationStack, bool withP) {
	if (equationStack.empty()) {
		return "";
	}

	char temp = pop(equationStack);
	std::string infixEquation;
	if (temp == '+' || temp == '-' || temp == '*' || temp == '/') {
		if (withP) {
			infixEquation += "(";
		}

		std::string operand1 = postfixToInfix(equationStack, withP);
		std::string operand2 = postfixToInfix(equationStack, withP);
		infixEquation += operand2 + std::string(1, temp) + operand1;

		if (withP) {
			infixEquation += ")";
		}
	}
	else {
		infixEquation += temp;
	}

	std::cout << infixEquation << std::endl;
	return infixEquation;
}

std::string postfixToInfixConverter(std::string equation, bool withP = false) {
	std::stack<char> equationStack;
	for (std::string::iterator it = equation.begin(); it != equation.end(); ++it) {
		equationStack.push(*it);
	}

	std::string infixEquation = postfixToInfix(equationStack, withP);
	return infixEquation;
}

int main() {
	std::string equation = "*abc-+de-fg-h+/*";
	std::cout << "result: " << postfixToInfixConverter(equation, false) << std::endl;
	std::cout << "answer: " << "a+b-c*d-e/f-g+h" << std::endl;
}