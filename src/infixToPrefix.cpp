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

std::string reverseString(std::string str) {
	std::string reverse;
	for (std::string::reverse_iterator it = str.rbegin(); it != str.rend(); ++it)	{
		reverse += *it;
	}
	return reverse;
}

std::string complementString(std::string str) {
	for (int i = 0; i < str.length(); ++i) {
		if (str[i] == '(') {
			str[i] = ')';
		}
		else if (str[i] == ')') {
			str[i] = '(';
		}
	}

	return str;
}

std::string infixToPostfixConverter(std::string equation, bool withP = false) {
	std::string postfixEquation = "";
	std::stack<char> operatorStack;
	int index = 0;

	for (int i = 0; i < equation.length(); ++i) {
		int precedence = getPrecedence(equation[i]);
		std::cout << postfixEquation << "  " << equation[i] << "  " << precedence << std::endl;
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


std::string infixToPrefixConverter(std::string equation, bool withP = false) {
	//reverse equation
	std::string reverseEquation = reverseString(equation);
	equation = complementString(reverseEquation);
	
	std::string postfixEquation = infixToPostfixConverter(equation);
	return reverseString(postfixEquation);
}

void test(std::string input, std::string expected) {
	std::cout << "Input : " << input << std::endl;
	std::cout << "Result: " << infixToPrefixConverter(input) << std::endl;
	std::cout << "Answer: " << expected << std::endl;
}

int main() {
	test("(A+B/C)*D+E/5", "+*+A/BCD/E5");}