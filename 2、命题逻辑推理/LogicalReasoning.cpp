#include <cmath>
#include <iostream>

using namespace std;

int main()
{

    cout << "���������⣺\n";
    cout << "1��ӪҵԱA��B͵���ֱ�\n";
    cout << "2����A����������������Ӫҵʱ��\n";
    cout << "3����B�ṩ��֤����ȷ�������δ����\n";
    cout << "4����B�ṩ��֤�ݲ���ȷ��������������Ӫҵʱ��\n";
    cout << "5������������\n";

    cout << "\n�����������Ԫ��ʾ��\n";
    cout << "A : ӪҵԱA͵���ֱ�\n";
    cout << "B : ӪҵԱB͵���ֱ�\n";
    cout << "C : ��������Ӫҵʱ��\n";
    cout << "D : B�ṩ��֤����ȷ\n";
    cout << "E : ����δ����\n";

    for (int i = 0; i < pow(2, 5); i++) {
        bool A = i & 0b1;
        bool B = i & 0b10;
        bool C = i & 0b100;
        bool D = i & 0b1000;
        bool E = i & 0b10000;
        if ((A || B) && (!A || C) && (!D || E) && (D || !C) && !E) {
            cout << "�õ������߼�������: AΪ" << (A ? "��" : "��") << ", BΪ" << (B ? "��" : "��") << endl
                 << endl;
            cout << "�õ�ӪҵԱ " << (A ? "A" : "") << (B ? "B" : "") << " ͵���ֱ�\n";
        }
    }
    system("pause");
    return 0;
}