#include <iostream>
#include <stack>
#include <string>

char pop(std::stack<char>& equationStack) {
	char temp = equationStack.top();
	equationStack.pop();
	return temp;
}

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

std::string prefixToPostfix(std::string equation) {
	std::string infixEquation = prefixToInfixConverter(equation);
	//std::cout << "Infix: " << infixEquation << std::endl;
	std::string postfixEquation = infixToPostfixConverter(infixEquation);

	return postfixEquation;
}

void test(std::string input, std::string expected) {
	std::cout << "Input : " << input << std::endl;
	std::cout << "Result: " << prefixToPostfix(input) << std::endl;
	std::cout << "Expect: " << expected << std::endl;
	std::cout << std::endl;
}

int main() {
	test("++A*BCD", "ABC*+D+");
	test("*+AB+CD", "ABC*+D+");
	test("+*AB*CD", "AB*CD*+");
	test("+++ABCD", "AB+C+D+");

	char temp;
	std::cin >> temp;
}