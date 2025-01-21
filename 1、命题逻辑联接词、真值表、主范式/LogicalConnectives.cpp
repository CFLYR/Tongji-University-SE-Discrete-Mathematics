#include <iostream>
#include <conio.h>

using namespace std;

void InputValue(int &value)
{
    char invalue;
    while (1) {
        invalue = _getch();
        if (invalue == '0' || invalue == '1') {
            cout << invalue << endl;
            break;
        }
        
    }
    value = (int(invalue) - 48);
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

int main()
{
    while (1) {
        system("cls");
        cout << "+-----------------------------------+" << endl;
        cout << "|        欢迎进入逻辑运算软件       |" << endl;
        cout << "+-----------------------------------+" << endl << endl;
        int p;
        int q;
        cout << "请输入 P 的值 (0或1): ";
        InputValue(p);
        cout << "请输入 Q 的值 (0或1): ";
        InputValue(q);

        cout << "合取" << endl;
        cout << "    P ∧ Q = " << (p && q) << endl;
        cout << "析取" << endl;
        cout << "    P ∨ Q = " << (p || q) << endl;
        cout << "条件:" << endl;
        cout << "    P -> Q = " << (!p || q) << endl;
        cout << "双条件:" << endl;
        cout << "    P <-> Q = " << ((!p || q) && (!q || p)) << endl;

        int continue_value;
        cout << "是否继续运算？ （y/n）: ";
        InputChoice(continue_value);
        if (!continue_value) {
            break;
        }
    }
    cout << endl;
    cout << "程序结束" << endl;

    return 0;
}
