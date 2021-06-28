#include <unordered_map>
#include <stack>
#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
    unordered_map<char, int> oper_pri = {
        {'+', 1},
        {'-', 1},
        {'*', 2},
        {'/', 2},
        {'%', 2},
        {'^', 3}
    };

    stack<char> opers;
    stack<long long> nums;

    void cal() {
        long long b = nums.top(); nums.pop();
        long long a = nums.top(); nums.pop();
        char oper = opers.top(); opers.pop();
        long long res;
        switch (oper) {
            case '+': res = a + b; break;
            case '-': res = a - b; break;
            case '*': res = a * b; break;
            case '/': res = a / b; break;
            case '^': res = pow(a, b); break;
        }
        nums.push(res);
    }

    int calculate(string s) {
        nums.push(0);
        int n = s.size();
        for (int i = 0; i < n; i++) {
            if (s[i] == ' ') continue;
            else if (s[i] == '(') {
                opers.push('(');
                if (s[i+1] == '-') {
                    i++;
                    nums.push(0);
                    opers.push('-');
                }
            }
            else if (s[i] == ')') {
                while (opers.top() != '(') {
                    cal();
                }
                opers.pop();
            }
            else if ('0' <= s[i] && s[i] <= '9') {
                int l = i;
                while (i + 1 < n && '0' <= s[i+1] && s[i+1] <= '9') {
                    i++;
                }
                nums.push(stoll(s.substr(l, i-l+1)));
            }
            else {
                while (!opers.empty() && opers.top() != '(' && oper_pri[opers.top()] >= oper_pri[s[i]]) {
                    cal();
                }
                opers.push(s[i]);
            }

        }
        while (!opers.empty() && opers.top() != '(') {
            cal();
        }
        return nums.top();
    }
};