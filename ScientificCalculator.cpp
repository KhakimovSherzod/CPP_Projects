#include <iostream>
#include <sstream>
#include <cmath>
#include <stack>
#include <stdexcept>
#include <map>
#include <functional>

using namespace std;

class Calculator {
public:
    Calculator() {
        // Register supported functions
        functions["sin"] = [](double a) { return sin(a); };
        functions["cos"] = [](double a) { return cos(a); };
        functions["tan"] = [](double a) { return tan(a); };
        functions["log"] = [](double a) { return log(a); };
        functions["sqrt"] = [](double a) { return sqrt(a); };
        functions["exp"] = [](double a) { return exp(a); };
    }

    double evaluate(const string &expression) {
        stringstream ss(expression);
        return evaluateExpression(ss);
    }

private:
    map<string, function<double(double)>> functions;

    double evaluateExpression(stringstream &ss) {
        stack<double> values;
        stack<char> ops;
        string token;

        while (ss >> token) {
            if (isdigit(token[0]) || (token[0] == '-' && token.length() > 1)) {
                values.push(stod(token));
            } else if (isalpha(token[0])) {
                string func = token;
                double value = parseValue(ss);
                if (functions.find(func) != functions.end()) {
                    values.push(functions[func](value));
                } else {
                    throw runtime_error("Unknown function: " + func);
                }
            } else if (token == "(") {
                values.push(evaluateExpression(ss));
            } else if (token == ")") {
                break;
            } else if (isOperator(token[0])) {
                while (!ops.empty() && precedence(ops.top()) >= precedence(token[0])) {
                    applyOperation(values, ops.top());
                    ops.pop();
                }
                ops.push(token[0]);
            } else {
                throw runtime_error("Invalid token: " + token);
            }
        }

        while (!ops.empty()) {
            applyOperation(values, ops.top());
            ops.pop();
        }

        return values.top();
    }

    double parseValue(stringstream &ss) {
        string token;
        ss >> token;
        if (isdigit(token[0]) || (token[0] == '-' && token.length() > 1)) {
            return stod(token);
        } else if (token == "(") {
            return evaluateExpression(ss);
        } else {
            throw runtime_error("Expected a value, got: " + token);
        }
    }

    void applyOperation(stack<double> &values, char op) {
        if (values.size() < 2) throw runtime_error("Insufficient values for operation");
        double b = values.top();
        values.pop();
        double a = values.top();
        values.pop();
        switch (op) {
            case '+': values.push(a + b); break;
            case '-': values.push(a - b); break;
            case '*': values.push(a * b); break;
            case '/':
                if (b == 0) throw runtime_error("Division by zero");
                values.push(a / b);
                break;
            case '^': values.push(pow(a, b)); break;
            default: throw runtime_error("Unknown operator: " + string(1, op));
        }
    }

    bool isOperator(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
    }

    int precedence(char op) {
        switch (op) {
            case '+':
            case '-': return 1;
            case '*':
            case '/': return 2;
            case '^': return 3;
            default: return 0;
        }
    }
};

int main() {
    Calculator calc;
    string expression;

    cout << "=== Scientific Calculator ===\n";
    cout << "Enter an expression (or type 'exit' to quit): ";

    while (getline(cin, expression)) {
        if (expression == "exit") break;

        try {
            double result = calc.evaluate(expression);
            cout << "Result: " << result << endl;
        } catch (const runtime_error &e) {
            cout << "Error: " << e.what() << endl;
        }

        cout << "Enter another expression (or type 'exit' to quit): ";
    }

    return 0;
}
