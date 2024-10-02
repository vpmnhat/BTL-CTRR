#include "assignment.h"
using namespace std;

int prec(char c) {
	if (c == '^') return 3;
	if (c == '*' || c == '/') return 2;
	if (c == '+' || c == '-') return 1;
	if (c == '~') return 4;
	if (c == '&' || c == '|') return 3;
	if (c == '@') return 2;
	if (c == '#') return 1;
	else return 0;
}

string Infix2Postfix(string s) {
	stack<char> st;
	string res = "";
	bool b = false;
	for (int i = 0; i < (int)s.length(); i++) {
		char c = s[i];
		if (c >= '0' && c <= '9') {
			if (b) {
				res += ' ';
				res += c;
				b = false;
			}
			else res += c;
		}
		else if (c == '(') {
			st.push(c);
		}
		else if (c == ')') {
			while (st.top() != '(') {
				res += ' ';
				res += st.top();
				st.pop();
			}
			st.pop();
		}
		else {
			b = true;
			while (!st.empty() && prec(c) <= prec(st.top())) {
				res += ' ';
				res += st.top();
				st.pop();
			}
			st.push(c);
		}
	}
	while (!st.empty()) {
		res += ' ';
		res += st.top();
		st.pop();
	}
	return res;
}

string infixToPostfix(string s) {
	stack<char> st;
	string res = "";
	bool b = false;
	for (int i = 0; i < (int)s.length(); i++) {
		char c = s[i];
		if (c >= '0' && c <= '9') {
			if (b) {
				res += ' ';
				res += c;
				b = false;
			}
			else res += c;
		}
		else if (c == '(') {
			st.push(c);
		}
		else if (c == ')') {
			while (st.top() != '(') {
				res += ' ';
				res += st.top();
				st.pop();
			}
			st.pop();
		}
		else {
			b = true;
			while (!st.empty() && prec(c) < prec(st.top())) {
				res += ' ';
				res += st.top();
				st.pop();
			}
			st.push(c);
		}
	}
	while (!st.empty()) {
		res += ' ';
		res += st.top();
		st.pop();
	}
	return res;
}

string Infix2Prefix(string s) {
	reverse(s.begin(), s.end());
	int l = s.length();
	for (int i = 0; i < l; i++) {
		if (s[i] == '(') s[i] = ')';
		else if (s[i] == ')') s[i] = '(';
	}
	string res = infixToPostfix(s);
	reverse(res.begin(), res.end());
	return res;
}

string postfix(string s) {
	stack<double> st;
	int l = s.length();
	for (int i = 0; i < l; i++) {
		if (s[i] == ' ') continue;
		else if (s[i] >= '0' && s[i] <= '9') {
			double num = 0;
			while (s[i] >= '0' && s[i] <= '9') {
				num = num * 10 + double(s[i] - '0');
				i++;
			}
			i--;
			st.push(num);
		}
		else {
			double x = st.top();
			st.pop();
			double y = st.top();
			st.pop();
			if (s[i] == '+') st.push(y + x);
			else if (s[i] == '-') st.push(y - x);
			else if (s[i] == '*') st.push(y * x);
			else if (s[i] == '/') st.push(y / x);
			else if (s[i] == '^') st.push(pow(y, x));
		}
	}
	double d = st.top();
	d = round(d * 1e4) / 1e4;
	string str = to_string(d);
	str.erase(str.find_last_not_of('0') + 1, std::string::npos);
	str.erase(str.find_last_not_of('.') + 1, std::string::npos);
	return str;
}

string prefix(string s) {
	stack<double> st;
	for (int i = s.length() - 1; i >= 0; i--) {
		if (s[i] == ' ') continue;
		else if (s[i] >= '0' && s[i] <= '9') {
			double num = 0, j = i;
			while (i < (int)s.length() && s[i] >= '0' && s[i] <= '9') i--;
			i++;
			for (int k = i; k <= j; k++) num = num * 10 + double(s[k] - '0');
			st.push(num);
		}
		else {
			double x = st.top();
			st.pop();
			double y = st.top();
			st.pop();
			if (s[i] == '+') st.push(x + y);
			else if (s[i] == '-') st.push(x - y);
			else if (s[i] == '*') st.push(x * y);
			else if (s[i] == '/') st.push(x / y);
			else if (s[i] == '^') st.push(pow(x, y));
		}
	}
	double d = st.top();
	d = round(d * 1e4) / 1e4;
	string str = to_string(d);
	str.erase(str.find_last_not_of('0') + 1, std::string::npos);
	str.erase(str.find_last_not_of('.') + 1, std::string::npos);
	return str;
}

string PostfixPrefixCalculator(string input) {
	if (input[0] >= '0' && input[0] <= '9') return postfix(input);
	else return prefix(input);
}

string LogicInfix2Postfix(string s) {
	s = regex_replace(s, regex("<->"), "#");
	s = regex_replace(s, regex("->"), "@");
	stack<char> st;
	string res = "";
	for (int i = 0; i < (int)s.length(); i++) {
		if (s[i] >= 'a' && s[i] <= 'z') res += s[i];
		else if (s[i] == '(') st.push('(');
		else if (s[i] == ')') {
			while (st.top() != '(') {
				res += st.top();
				st.pop();
			}
			st.pop();
		}
		else {
			while (!st.empty() && prec(s[i]) <= prec(st.top())) {
				res += st.top();
				st.pop();
			}
			st.push(s[i]);
		}
	}
	while (!st.empty()) {
		res += st.top();
		st.pop();
	}
	res = regex_replace(res, regex("#"), "<->");
	res = regex_replace(res, regex("@"), "->");
	return res;
}

string LogicInfixToPostfix(string s) {
	s = '(' + s + ')';
	stack<char> st;
	string res = "";
	int l = s.length();
	for (int i = 0; i < l; i++) {
		char c = s[i];
		if (c >= 'a' && c <= 'z') {
			res += c;
		}
		else if (c == '(') {
			st.push(c);
		}
		else if (c == ')') {
			while (st.top() != '(') {
				res += st.top();
				st.pop();
			}
			st.pop();
		}
		else {
			while (prec(c) < prec(st.top())) {
				res += st.top();
				st.pop();
			}
			st.push(c);
		}
	}
	while (!st.empty()) {
		res += st.top();
		st.pop();
	}
	return res;
}

string LogicInfix2Prefix(string s) {
	s = regex_replace(s, regex("<->"), "#");
	s = regex_replace(s, regex("->"), "@");
	s = regex_replace(s, regex(" "), "");
	reverse(s.begin(), s.end());
	int l = s.length();
	for (int i = 0; i < l; i++) {
		if (s[i] == '(') s[i] = ')';
		else if (s[i] == ')') s[i] = '(';
	}
	string res = LogicInfixToPostfix(s);
	reverse(res.begin(), res.end());
	res = regex_replace(res, regex("#"), "<->");
	res = regex_replace(res, regex("@"), "->");
	return res;
}

string logicprefix(string input, string varlue) {
	input = regex_replace(input, regex("<->"), "#");
	input = regex_replace(input, regex("->"), "@");
	map<char, int> mp;
	vector<char> vc;
	vector<int> vi;
	int l = varlue.length();
	for (int i = 0; i < l; i++) {
		if (varlue[i] >= 'a' && varlue[i] <= 'z') vc.push_back(varlue[i]);
		else if (varlue[i] == '0') vi.push_back(0);
		else if (varlue[i] == '1') vi.push_back(1);
	}
	for (int i = 0; i < (int)vi.size(); i++) mp[vc[i]] = vi[i];
	stack<int> st;
	for (int i = (int)input.length() - 1; i >= 0; i--) {
		if (input[i] >= 'a' && input[i] <= 'z') st.push(mp[input[i]]);
		else if (input[i] == '~') {
			int x = st.top();
			st.pop();
			st.push(1 - x);
		}
		else {
			int x = st.top();
			st.pop();
			int y = st.top();
			st.pop();
			if (input[i] == '&') st.push(x & y);
			else if (input[i] == '|') st.push(x | y);
			else if (input[i] == '#') st.push((x == y) ? 1 : 0);
			else if (input[i] == '@') st.push((x == 1 && y == 0) ? 0 : 1);
		}
	}
	if (st.top() == 1) return "TRUE";
	return "FALSE";
}

string logicpostfix(string input, string varlue) {
	input = regex_replace(input, regex("<->"), "#");
	input = regex_replace(input, regex("->"), "@");
	map<char, int> mp;
	vector<char> vc;
	vector<int> vi;
	int l = varlue.length();
	for (int i = 0; i < l; i++) {
		if (varlue[i] >= 'a' && varlue[i] <= 'z') vc.push_back(varlue[i]);
		else if (varlue[i] == '0') vi.push_back(0);
		else if (varlue[i] == '1') vi.push_back(1);
	}
	for (int i = 0; i < (int)vi.size(); i++) mp[vc[i]] = vi[i];
	stack<int> st;
	for (int i = 0; i < (int)input.length(); i++) {
		if (input[i] >= 'a' && input[i] <= 'z') st.push(mp[input[i]]);
		else if (input[i] == '~') {
			int x = st.top();
			st.pop();
			st.push(1 - x);
		}
		else {
			int x = st.top();
			st.pop();
			int y = st.top();
			st.pop();
			if (input[i] == '&') st.push(x & y);
			else if (input[i] == '|') st.push(x | y);
			else if (input[i] == '#') st.push((x == y) ? 1 : 0);
			else if (input[i] == '@') st.push((y == 1 && x == 0) ? 0 : 1);
		}
	}
	if (st.top() == 1) return "TRUE";
	return "FALSE";
}

string LogicPostfixPrefixCalculator(string input, string varlue) {
	if (input[0] >= 'a' && input[0] <= 'z') return logicpostfix(input, varlue);
	return logicprefix(input, varlue);
}

