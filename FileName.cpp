#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

// 生成指定范围内的随机整数
int generateRandomInt(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// 生成指定范围内的随机浮点数
float generateRandomFloat(int min, int max) {
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

// 生成算术表达式
string generateExpression(int maxNum, bool allowDecimals, bool allowParentheses, char operation) {
    int num1 = generateRandomInt(1, maxNum);
    int num2 = generateRandomInt(1, maxNum);
    float result;
    stringstream expressionStream;

    if (allowDecimals) {
        float floatNum1 = generateRandomFloat(1, maxNum);
        float floatNum2 = generateRandomFloat(1, maxNum);
        result = floatNum1 + floatNum2;
        expressionStream << floatNum1 << " " << operation << " " << floatNum2;
    }
    else {
        result = num1 + num2;
        expressionStream << num1 << " " << operation << " " << num2;
    }

    string expression = expressionStream.str();

    if (allowParentheses && operation != '/') { // 除法运算不需要括号
        expression = "(" + expression + ")";
    }

    expression += " = ";
    return expression;
}

int main() {
    srand(time(0)); // 用当前时间初始化随机数生成器

    int maxNum, numQuestions;
    char operation;
    bool allowParentheses, allowDecimals;

    cout << "请输入最大数：";
    cin >> maxNum;
    cout << "请输入题目数量：";
    cin >> numQuestions;
    cout << "请输入运算符（+、-、*、/）：";
    cin >> operation;
    cout << "是否允许使用括号？（1表示允许，0表示不允许）：";
    cin >> allowParentheses;
    cout << "是否允许小数？（1表示允许，0表示不允许）：";
    cin >> allowDecimals;

    ofstream outputFile("exercises.txt"); // 输出到文件 "exercises.txt"
    if (!outputFile) {
        cerr << "创建文件时发生错误。";
        return 1;
    }

    for (int i = 0; i < numQuestions; ++i) {
        string expression = generateExpression(maxNum, allowDecimals, allowParentheses, operation);
        cout << expression << endl;
        outputFile << expression << endl;
    }

    cout << "已将结果保存到文件exercises.txt中。" << endl;

    outputFile.close();

    return 0;
}
