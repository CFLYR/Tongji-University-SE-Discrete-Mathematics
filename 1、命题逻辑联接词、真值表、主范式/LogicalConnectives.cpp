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
        cout << "|        ��ӭ�����߼��������       |" << endl;
        cout << "+-----------------------------------+" << endl << endl;
        int p;
        int q;
        cout << "������ P ��ֵ (0��1): ";
        InputValue(p);
        cout << "������ Q ��ֵ (0��1): ";
        InputValue(q);

        cout << "��ȡ" << endl;
        cout << "    P �� Q = " << (p && q) << endl;
        cout << "��ȡ" << endl;
        cout << "    P �� Q = " << (p || q) << endl;
        cout << "����:" << endl;
        cout << "    P -> Q = " << (!p || q) << endl;
        cout << "˫����:" << endl;
        cout << "    P <-> Q = " << ((!p || q) && (!q || p)) << endl;

        int continue_value;
        cout << "�Ƿ�������㣿 ��y/n��: ";
        InputChoice(continue_value);
        if (!continue_value) {
            break;
        }
    }
    cout << endl;
    cout << "�������" << endl;

    return 0;
}
