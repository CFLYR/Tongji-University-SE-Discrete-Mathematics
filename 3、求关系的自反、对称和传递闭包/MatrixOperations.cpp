#include<iostream>
#include<conio.h>
#include <vector>
#include <limits>



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
        }
        else if (value < lower_limit || value>higher_limit) {
            cout << "输入错误，请重输\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }
    return;
}

void InputMatrix(vector<vector<int>>& matrix) {
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



vector<vector<int>> Reflexive(const vector<vector<int>> matrix) {
    int size = int(matrix.size());
    vector<vector<int>>reflexive = matrix;
    for (int i = 0; i < size; i++) {
        reflexive[i][i] = 1;
    }
    return reflexive;
}


vector<vector<int>> Symmetric(const vector<vector<int>> matrix) {
    int size = int(matrix.size());
    vector<vector<int>>symmetric = matrix;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (symmetric[i][j]) {
                symmetric[j][i] = 1;
            }
        }
    }
    return symmetric;
}

vector<vector<int>> Multiplication(const vector<vector<int>> matrix_1, const vector<vector<int>> matrix_2) {
    int size = int(matrix_1.size());
    vector<vector<int>> multiplication(size, vector<int>(size));
    for (int l = 0; l < size; l++) {
        for (int k = 0; k < size; k++) {
            int multiply = 0;
            for (int i = 0; i < size; i++) {
                multiply += matrix_1[l][i] * matrix_2[i][k];
            }
            multiplication[l][k] = bool(multiply);
        }
    }
    return multiplication;
}

vector<vector<int>> Power(const vector<vector<int>> matrix, int power) {
    int size = int(matrix.size());
    vector<vector<int>> powered = matrix;
    for (int i = 0; i < size - 1; i++) {
        powered = Multiplication(powered, matrix);
    }
    return powered;
}


vector<vector<int>> Transitive(const vector<vector<int>> matrix) {
    int size = int(matrix.size());
    vector<vector<int>> transitive(size, vector<int>(size));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int transi = 0;
            for (int k = 0; k < size; k++) {
                transi += Power(matrix, k + 1)[i][j];
            }
            transitive[i][j] = bool(transi);
        }
    }
    
    return transitive;
}

void PrintMatrix(const vector<vector<int>> matrix) {
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
        }
        else if (invalue == 'n') {
            cout << invalue << endl;
            value = 0;
            break;
        }

    }

    return;
}


int main() {

    while (1) {
        system("cls");
        cout << "+--------------------------------------------------------------+\n" ;
        cout << "|                  关系的自反、对称、传递闭包                  |\n" ;
        cout << "+--------------------------------------------------------------+\n" ;
        cout << "请输入矩阵大小(1~100)\n";
        int size;
        CheckCin(size, 0, 100);
        vector<vector<int>> matrix(size, vector<int>(size));
        cout << "请依次输入矩阵元素值\n";
        InputMatrix(matrix);

        cout << "自反闭包为：\n";
        PrintMatrix(Reflexive(matrix));
        cout << "对称闭包为：\n";
        PrintMatrix(Symmetric(matrix));
        cout << "传递闭包为：\n";
        PrintMatrix(Transitive(matrix));

        int continue_value;
        cout << "是否继续运算？ （y/n）: ";
        InputChoice(continue_value);
        if (!continue_value) {
            break;
        }
    }



	return 0;
}