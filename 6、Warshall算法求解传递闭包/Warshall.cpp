#include <conio.h>
#include <iostream>
#include <limits>
#include <vector>

#define MAX_SIZE 100

using namespace std;

void InputValue(int& value)
{
    char invalue;
    while (1) {
        invalue = _getch();
        if (invalue == '0' || invalue == '1') {
            cout << invalue;
            break;
        }
    }
    value = (int(invalue) - 48);
    return;
}

void CheckCin(int& value, const int lower_limit = 0, const int higher_limit = 10000)
{
    while (1) {
        cin >> value;
        if (cin.fail()) {
            cout << "输入错误，请重输\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        } else if (value < lower_limit || value > higher_limit) {
            cout << "输入错误，请重输\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
    return;
}

void InputMatrix(vector<vector<int>>& matrix)
{
    int size = int(matrix.size());
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int value;
            InputValue(value);
            matrix[i][j] = value;
            if (j != size - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }
}

vector<vector<int>> Warshall(const vector<vector<int>> matrix)
{
    int size = int(matrix.size());
    vector<vector<int>> warshall = matrix;
    for (int k = 0; k < size; k++) {
        // 对每个起点i
        for (int i = 0; i < size; i++) {
            // 对每个终点j
            for (int j = 0; j < size; j++) {
                // 如果i->k和k->j都存在路径,则i->j存在路径
                if (warshall[i][k] && warshall[k][j]) {
                    warshall[i][j] = 1;
                }
            }
        }
    }

    return warshall;
}

void PrintMatrix(const vector<vector<int>> matrix)
{
    int size = int(matrix.size());
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << matrix[i][j];
            if (j != size - 1) {
                cout << " ";
            }
        }
        cout << endl;
    }
    return;
}

void InputChoice(int& value)
{
    char invalue;
    while (1) {
        invalue = _getch();
        if (invalue == 'y') {
            cout << invalue << endl;
            value = 1;
            break;
        } else if (invalue == 'n') {
            cout << invalue << endl;
            value = 0;
            break;
        }
    }

    return;
}

int main()
{
    while (1) {
        system("cls");
        cout << "+--------------------------------------------------------------+\n";
        cout << "|                    Warshall方法求传递闭包                    |\n";
        cout << "+--------------------------------------------------------------+\n";
        cout << "请输入矩阵大小(1~100)\n";
        int size;
        CheckCin(size, 0, 100);
        vector<vector<int>> matrix(size, vector<int>(size));
        cout << "请依次输入矩阵元素值\n";
        InputMatrix(matrix);
        cout << "Warshall算法求传递闭包为：\n";
        PrintMatrix(Warshall(matrix));
        int continue_value;
        cout << "是否继续运算？ （y/n）: ";
        InputChoice(continue_value);
        if (!continue_value) {
            break;
        }
    }

    return 0;
}