#include <algorithm>
#include <conio.h>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

#define MAX_SIZE 100

using namespace std;

struct TreeNode {
    int num;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int n)
        : num(n)
        , left(NULL)
        , right(NULL)
    {
    }
};

void InitNodes(vector<TreeNode*>& nodes, const vector<int>& weights)
{
    for (auto weight : weights)
        nodes.push_back(new TreeNode(weight));
}

void BuildHuffmanTree(vector<TreeNode*>& nodes, TreeNode*& root)
{
    while (nodes.size() > 1) {
        stable_sort(nodes.begin(), nodes.end(), [](const TreeNode* a, const TreeNode* b) {
            return a->num < b->num;
        });

        TreeNode* left = nodes.front();
        nodes.erase(nodes.begin());
        TreeNode* right = nodes.front();
        nodes.erase(nodes.begin());

        TreeNode* parent = new TreeNode(left->num + right->num);
        parent->left = left;
        parent->right = right;
        nodes.push_back(parent);
    }
    root = nodes.front();
}

void PrintCodes(TreeNode* node, string prefix)
{
    if (node) {
        PrintCodes(node->left, prefix + "0");
        if (!node->left && !node->right)
            cout << setw(5) << node->num << ": " << prefix << endl;
        PrintCodes(node->right, prefix + "1");
    }
}

void CheckCin(int& value, const int lower_limit = 0, const int higher_limit = 10000)
{
    while (1) {
        cin >> value;
        if (cin.fail()) {
            cout << "�������������\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        } else if (value < lower_limit || value > higher_limit) {
            cout << "�������������\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
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
        cout << "|                          ���Ŷ�Ԫ��                          |\n";
        cout << "+--------------------------------------------------------------+\n";
        cout << " ������ڵ����: (2~100)\n";
        int n;
        CheckCin(n, 2, MAX_SIZE);
        vector<int> weights;
        cout << " ������ڵ�Ȩ��: (0~100)\n";
        for (int i = 0; i < n; i++) {
            cout << "�ڵ�" << i + 1 << ": ";
            int weight;
            CheckCin(weight, 0, MAX_SIZE);
            weights.push_back(weight);
        }
        TreeNode* root;
        vector<TreeNode*> nodes;
        InitNodes(nodes, weights);
        BuildHuffmanTree(nodes, root);
        cout << " �ڵ����: \n";
        PrintCodes(root, "");
        int continue_value;
        cout << "�Ƿ�������㣿 ��y/n��: ";
        InputChoice(continue_value);
        if (!continue_value) {
            break;
        }
    }

    return 0;
}