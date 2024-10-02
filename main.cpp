#include "assignment.h"
using namespace std;

int main() {
	string infixLogic, infixMath, varlue;
	cin >> infixMath >> infixLogic >> varlue;
	cout << Infix2Postfix(infixMath) << '\n'
		<< Infix2Prefix(infixMath) << '\n'
		<< PostfixPrefixCalculator(infixMath) << '\n'
		<< LogicInfix2Postfix(infixLogic) << '\n'
		<< LogicInfix2Prefix(infixLogic) << '\n'
		<< LogicPostfixPrefixCalculator(infixLogic, varlue) << '\n';
}