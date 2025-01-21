#include <cctype>
#include <conio.h>
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <vector>

// ʹ�ñ�׼�����ռ�
using namespace std;

// ��������
bool CalculateExpression(const string& input, const map<char, bool>& values);
bool ParseExpression(const string& expr, const map<char, bool>& values, size_t& pos);
bool ParseTerm(const string& expr, const map<char, bool>& values, size_t& pos);
bool ParseFactor(const string& expr, const map<char, bool>& values, size_t& pos);

// ���㲼�����ʽ��������
bool CalculateExpression(const string& input, const map<char, bool>& values)
{
    size_t pos = 0; // ��ʼ��λ��Ϊ0
    return ParseExpression(input, values, pos); // �ӱ��ʽ��ʼ����
}

// �������ʽ
bool ParseExpression(const string& expr, const map<char, bool>& values, size_t& pos)
{
    bool left = ParseTerm(expr, values, pos); // ���������

    while (pos < expr.length()) { // �������ַ�������ʱ
        char op = expr[pos]; // ��ȡ��ǰ�ַ�
        if (op != '|' && op != '~' && op != '^')
            break; // ������ǻ򡢵ȼۡ��̺�����������˳�ѭ��
        pos++; // �ƶ�����һ���ַ�

        bool right = ParseTerm(expr, values, pos); // �����Ҳ���

        // ���������������
        switch (op) {
        case '|': // ������
            left = (left || right);
            break;
        case '~': // �ȼ�����
            left = (left == right);
            break;
        case '^': // �̺�����
            left = (!left || right);
            break;
        }
    }

    return left; // �������ս��
}

// ������
bool ParseTerm(const string& expr, const map<char, bool>& values, size_t& pos)
{
    bool result = ParseFactor(expr, values, pos); // ������һ������

    // ����������
    while (pos < expr.length() && expr[pos] == '&') { // �������ַ������������ʱ
        pos++; // �ƶ�����һ���ַ�
        result = result && ParseFactor(expr, values, pos); // ������һ�����Ӳ�����������
    }

    return result; // ������Ľ��
}

// ��������
bool ParseFactor(const string& expr, const map<char, bool>& values, size_t& pos)
{
    if (pos >= expr.length())
        return 0; // ����Ѿ������ַ���ĩβ������0

    char ch = expr[pos]; // ��ȡ��ǰ�ַ�
    if (ch == '(') { // ��������
        pos++; // �ƶ��������ڵĵ�һ���ַ�
        bool result = ParseExpression(expr, values, pos); // ���������ڵı��ʽ
        if (pos < expr.length() && expr[pos] == ')') { // �������������
            pos++; // �ƶ������ź����һ���ַ�
        }
        return result; // ���������ڱ��ʽ�Ľ��
    } else if (ch == '!') { // ���������
        pos++; // �ƶ�����һ���ַ�
        return !ParseFactor(expr, values, pos); // ����һ�����ӽ��з�����
    } else if (isalpha(ch)) { // �������
        pos++; // �ƶ�����һ���ַ�
        return values.at(ch); // ���ر�����ֵ
    }

    return 0; // ����������������������0
}

// ����Ƿ�Ϊ��Ч�����
bool IsValidOperator(char ch)
{
    if (ch == '!' || ch == '&' || ch == '|' || ch == '^' || ch == '~') {
        return true; // �������Ч�����������true
    } else {
        return false; // ���򷵻�false
    }
}

// ��ȡ���ʽ�е����б���
set<char> GetVariables(const string& input)
{
    set<char> variables; // ����һ���������洢����
    for (char ch : input) // ���������ַ�����ÿ���ַ�
        if (isalpha(ch)) // �������ĸ
            variables.insert(ch); // ������ӵ�����������
    return variables; // ���ر�������
}

// ��ӡ���ָ���
void PrintChartLine(int num_variables)
{
    for (int i = 0; i < num_variables; i++) // ��ÿ������
        cout << "+-------"; // ��ӡ�ָ���
    cout << "+-------+" << endl; // ��ӡ���ķָ���������
    return;
}

// ��ӡ��ֵ���ͷ
void PrintTableHeader(const set<char>& variables)
{
    cout << "��ֵ��" << endl;
    PrintChartLine(variables.size()); // ��ӡ�ϱ߽���

    cout << "|";
    for (char var : variables) { // ��ÿ������
        cout << "   " << var << "   |"; // ��ӡ������
    }
    cout << " value |" << endl; // ��ӡ"value"��
    PrintChartLine(variables.size()); // ��ӡ�±߽���
}

// ��ӡ��ֵ����
void PrintTableRow(const map<char, bool>& variable_values, bool result)
{
    cout << "|";
    for (const auto& pair : variable_values) { // ��ÿ������
        cout << "   " << pair.second << "   |"; // ��ӡ��ֵ
    }
    cout << "   " << result << "   |" << endl; // ��ӡ���
    PrintChartLine(variable_values.size()); // ��ӡ�зָ���
}

// ��ȡ���ʽ�ķ�ʽ
string GetCanonicalForm(const vector<bool>& results, bool is_true_form)
{
    string canonical_form; // ���ڴ洢��ʽ
    char term_prefix = is_true_form ? 'M' : 'm'; // ȷ�����ǰ׺
    string separator = "��";
    if (is_true_form) {
        separator = "��";
    }

    for (size_t i = 0; i < results.size(); ++i) { // �������н��
        if (results[i] == is_true_form) { // ��������������ʽ
            if (!canonical_form.empty()) { // ������ǵ�һ��
                canonical_form += separator; // ��ӷָ���
            }
            canonical_form += term_prefix + string("<") + to_string(i) + string(">"); // �����
        }
    }

    // �����ʽΪ�գ�����"1"��"0"�����򷵻ع���ķ�ʽ
    return canonical_form.empty() ? (is_true_form ? "1" : "0") : canonical_form;
}

// ���㲢��ӡ��ֵ��ͷ�ʽ
void CalculateAndPrint(const string& input)
{
    set<char> variables = GetVariables(input); // ��ȡ���б���
    int num_variables = static_cast<int>(variables.size()); // ��ȡ��������

    PrintTableHeader(variables); // ��ӡ��ͷ

    vector<bool> results; // �洢���п�������Ľ��
    for (int i = 0; i < (1 << num_variables); ++i) { // �������п��ܵ��������
        map<char, bool> variable_values; // �洢��ǰ��ϵı���ֵ
        int index = 0;
        for (char var : variables) { // Ϊÿ��������ֵ
            variable_values[var] = (i & (1 << index)) != 0;
            ++index;
        }

        bool result = CalculateExpression(input, variable_values); // ������
        results.push_back(result); // �洢���
        PrintTableRow(variable_values, result); // ��ӡ��ǰ��
    }

    cout << "����ȡ��ʽ: " << endl;
    cout << GetCanonicalForm(results, true) << endl; // ��ӡ����ȡ��ʽ

    cout << "����ȡ��ʽ: " << endl;
    cout << GetCanonicalForm(results, false) << endl; // ��ӡ����ȡ��ʽ
}

// ��������Ƿ���Ч
bool IsValidInput(const string& input)
{
    if (input.empty()) { // �������Ϊ��
        cout << "������Ч" << endl;
        return false;
    }

    stack<char> parentheses; // ���ڼ������ƥ��
    char previous = '\0'; // �洢ǰһ���ַ�

    for (size_t i = 0; i < input.length(); i++) { // ���������ַ���
        char ch = input[i]; // ��ȡ��ǰ�ַ�

        // ����ַ��Ƿ���Ч
        if (!((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || IsValidOperator(ch) || ch == '(' || ch == ')')) {
            cout << "������Ч" << endl;
            return false;
        }

        // ����﷨����
        if ((i == 0 && (ch == '&' || ch == '|' || ch == '~' || ch == '^')) || (previous == '(' && ch == ')') || (previous == '!' && ch == '!') || (ch == '!' && isalpha(previous)) || ((isalpha(ch) && previous == ')') || (ch == '(' && isalpha(previous))) || (isalpha(ch) && isalpha(previous)) || ((ch == '&' || ch == '|' || ch == '~' || ch == '^') && (!isalpha(previous) && previous != ')'))) {
            cout << "������Ч" << endl;
            return false;
        }

        // �������ƥ��
        if (ch == '(') {
            parentheses.push(ch);
        } else if (ch == ')') {
            if (parentheses.empty()) {
                cout << "������Ч" << endl;
                return false;
            }
            parentheses.pop();
        }

        previous = ch; // ����ǰһ���ַ�
    }

    // ������һ���ַ�������ƥ��
    if (IsValidOperator(previous) || previous == '!' || !parentheses.empty()) {
        cout << "������Ч" << endl;
        return false;
    }

    return true; // ���ͨ�����м�飬����true
}

// ��ȡ�û�ѡ��y/n��
void InputChoice(int& value)
{
    char in_value;
    while (1) { // ѭ��ֱ�������Ч����
        in_value = _getch(); // ��ȡ�û�������ַ�
        if (in_value == 'y') {
            cout << in_value << endl;
            value = 1;
            break;
        } else if (in_value == 'n') {
            cout << in_value << endl;
            value = 0;
            break;
        }
    }
    return;
}

// ��ӡ�˵�
void PrintMenu()
{
    printf("+-------------------------------------+\n");
    printf("|                                     |\n");
    printf("|        ��ӭ�����߼��������         |\n");
    printf("|    (��������ֵ��,����ʽ,֧������)   |\n");
    printf("|                                     |\n");
    printf("|              ��!��ʾ��              |\n");
    printf("|              ��&��ʾ��              |\n");
    printf("|              ��|��ʾ��              |\n");
    printf("|             ��^��ʾ�̺�             |\n");
    printf("|             ��~��ʾ��ֵ             |\n");
    printf("|                                     |\n");
    printf("+-------------------------------------+\n\n");

    return;
}

int main()
{
    while (1) { // ��ѭ��
        system("cls"); // ����
        PrintMenu(); // ��ӡ�˵�
        cout << "��������ʽ���������ֻ֧�ִ�Сд����Ӣ����ĸ��" << endl;
        string input;
        while (1) { // ѭ��ֱ�������Ч����
            cin >> input;
            if (IsValidInput(input)) {
                break;
            }
        }

        CalculateAndPrint(input); // ���㲢��ӡ���

        int continue_value;
        cout << "�Ƿ�������㣿 ��y/n��: ";
        InputChoice(continue_value); // ��ȡ�û��Ƿ������ѡ��
        if (!continue_value) {
            break; // ����û�ѡ�񲻼������˳���ѭ��
        }
    }
    cout << endl;
    cout << "��лʹ��" << endl;
    return 0; // �������
}