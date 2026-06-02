#include <iostream>
#include <string>
#include <stack>
#include <cctype>

using namespace std;

// Function to determine the precedence of operators
int getPrecedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Function to perform basic arithmetic operations
double applyOp(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b == 0) {
                cout << "\nError: Division by zero!" << endl;
                return 0;
            }
            return a / b;
    }
    return 0;
}

// Function that evaluates the entire expression string
double evaluateExpression(string expr) {
    stack<double> values;    // Stack to store numbers
    stack<char> ops;         // Stack to store operators

    for (size_t i = 0; i < expr.length(); i++) {
        // Skip spaces
        if (isspace(expr[i])) continue;

        // If the current character is a number, parse the whole number (including decimals)
        if (isdigit(expr[i]) || expr[i] == '.') {
            string valStr = "";
            while (i < expr.length() && (isdigit(expr[i]) || expr[i] == '.')) {
                valStr += expr[i];
                i++;
            }
            values.push(stod(valStr));
            i--; // Step back because the loop will increment 'i'
        }
        // If the current character is an operator
        else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            // While top of 'ops' has same or higher precedence, apply it to the top two values
            while (!ops.empty() && getPrecedence(ops.top()) >= getPrecedence(expr[i])) {
                double val2 = values.top(); values.pop();
                double val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                
                values.push(applyOp(val1, val2, op));
            }
            // Push current operator to 'ops'
            ops.push(expr[i]);
        }
    }

    // Entire expression has been parsed, apply remaining ops
    while (!ops.empty()) {
        double val2 = values.top(); values.pop();
        double val1 = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        
        values.push(applyOp(val1, val2, op));
    }

    // The top of 'values' contains the final result
    return values.top();
}

int main() {
    string expression;

    cout << "=== Real-Time Expression Calculator ===" << endl;
    cout << "Type 'exit' to quit." << endl;

    while (true) {
        cout << "\nEnter expression (e.g., 10 + 2 * 6 / 3): ";
        getline(cin, expression);

        if (expression == "exit" || expression == "EXIT") {
            break;
        }

        try {
            double result = evaluateExpression(expression);
            cout << "Result: " << result << endl;
        } catch (...) {
            cout << "Invalid expression look closely at your syntax." << endl;
        }
    }

    return 0;
}