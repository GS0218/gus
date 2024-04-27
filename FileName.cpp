#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

// ����ָ����Χ�ڵ��������
int generateRandomInt(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// ����ָ����Χ�ڵ����������
float generateRandomFloat(int min, int max) {
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

// �����������ʽ
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

    if (allowParentheses && operation != '/') { // �������㲻��Ҫ����
        expression = "(" + expression + ")";
    }

    expression += " = ";
    return expression;
}

int main() {
    srand(time(0)); // �õ�ǰʱ���ʼ�������������

    int maxNum, numQuestions;
    char operation;
    bool allowParentheses, allowDecimals;

    cout << "�������������";
    cin >> maxNum;
    cout << "��������Ŀ������";
    cin >> numQuestions;
    cout << "�������������+��-��*��/����";
    cin >> operation;
    cout << "�Ƿ�����ʹ�����ţ���1��ʾ����0��ʾ��������";
    cin >> allowParentheses;
    cout << "�Ƿ�����С������1��ʾ����0��ʾ��������";
    cin >> allowDecimals;

    ofstream outputFile("exercises.txt"); // ������ļ� "exercises.txt"
    if (!outputFile) {
        cerr << "�����ļ�ʱ��������";
        return 1;
    }

    for (int i = 0; i < numQuestions; ++i) {
        string expression = generateExpression(maxNum, allowDecimals, allowParentheses, operation);
        cout << expression << endl;
        outputFile << expression << endl;
    }

    cout << "�ѽ�������浽�ļ�exercises.txt�С�" << endl;

    outputFile.close();

    return 0;
}
