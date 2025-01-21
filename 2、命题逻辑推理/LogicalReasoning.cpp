#include <cmath>
#include <iostream>

using namespace std;

int main()
{

    cout << "有以下命题：\n";
    cout << "1、营业员A或B偷了手表\n";
    cout << "2、若A作案，则作案不在营业时间\n";
    cout << "3、若B提供的证据正确，则货柜未上锁\n";
    cout << "4、若B提供的证据不正确，则作案发生在营业时间\n";
    cout << "5、货柜上了锁\n";

    cout << "\n有如下命题变元表示：\n";
    cout << "A : 营业员A偷了手表\n";
    cout << "B : 营业员B偷了手表\n";
    cout << "C : 作案不在营业时间\n";
    cout << "D : B提供的证据正确\n";
    cout << "E : 货柜未上锁\n";

    for (int i = 0; i < pow(2, 5); i++) {
        bool A = i & 0b1;
        bool B = i & 0b10;
        bool C = i & 0b100;
        bool D = i & 0b1000;
        bool E = i & 0b10000;
        if ((A || B) && (!A || C) && (!D || E) && (D || !C) && !E) {
            cout << "得到命题逻辑推理结果: A为" << (A ? "真" : "假") << ", B为" << (B ? "真" : "假") << endl
                 << endl;
            cout << "得到营业员 " << (A ? "A" : "") << (B ? "B" : "") << " 偷了手表\n";
        }
    }
    system("pause");
    return 0;
}