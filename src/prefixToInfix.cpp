#include <iostream>
#include <stack>
#include <string>


char pop(std::stack<char>& equationStack) {
	char temp = equationStack.top();
	equationStack.pop();
	return temp;
}

std::string prefixToInfix(std::stack<char>& equationStack, bool withP) {
	if (equationStack.empty()) {
		return "";
	}

	char temp = pop(equationStack);
	std::string infixEquation;
	if (temp == '+' || temp == '-' || temp == '*' || temp == '/') {
		if (withP) {
			infixEquation += "(";
		}

		std::string operand1 = prefixToInfix(equationStack, withP);
		std::string operand2 = prefixToInfix(equationStack, withP);
		infixEquation += operand1 + std::string(1, temp) + operand2;

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

std::string prefixToInfixConverter(std::string equation, bool withP = false) {
	std::stack<char> equationStack;
	for (std::string::reverse_iterator it = equation.rbegin(); it != equation.rend(); it++) {
		equationStack.push(*it);
	}

	std::string infixEquation = prefixToInfix(equationStack, withP);

	return infixEquation;
}

int main() {
	std::string equation = "*+a-bc/-de+-fgh";
	std::cout << "result: " << prefixToInfixConverter(equation) << std::endl;
	std::cout << "answer: " << "a+b-c*d-e/f-g+h" << std::endl;
}