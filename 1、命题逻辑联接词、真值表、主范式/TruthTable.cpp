#include <cctype>
#include <conio.h>
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <vector>

// 使用标准命名空间
using namespace std;

// 函数声明
bool CalculateExpression(const string& input, const map<char, bool>& values);
bool ParseExpression(const string& expr, const map<char, bool>& values, size_t& pos);
bool ParseTerm(const string& expr, const map<char, bool>& values, size_t& pos);
bool ParseFactor(const string& expr, const map<char, bool>& values, size_t& pos);

// 计算布尔表达式的主函数
bool CalculateExpression(const string& input, const map<char, bool>& values)
{
    size_t pos = 0; // 初始化位置为0
    return ParseExpression(input, values, pos); // 从表达式开始解析
}

// 解析表达式
bool ParseExpression(const string& expr, const map<char, bool>& values, size_t& pos)
{
    bool left = ParseTerm(expr, values, pos); // 解析左侧项

    while (pos < expr.length()) { // 当还有字符待处理时
        char op = expr[pos]; // 获取当前字符
        if (op != '|' && op != '~' && op != '^')
            break; // 如果不是或、等价、蕴含运算符，则退出循环
        pos++; // 移动到下一个字符

        bool right = ParseTerm(expr, values, pos); // 解析右侧项

        // 根据运算符计算结果
        switch (op) {
        case '|': // 或运算
            left = (left || right);
            break;
        case '~': // 等价运算
            left = (left == right);
            break;
        case '^': // 蕴含运算
            left = (!left || right);
            break;
        }
    }

    return left; // 返回最终结果
}

// 解析项
bool ParseTerm(const string& expr, const map<char, bool>& values, size_t& pos)
{
    bool result = ParseFactor(expr, values, pos); // 解析第一个因子

    // 处理与运算
    while (pos < expr.length() && expr[pos] == '&') { // 当还有字符且是与运算符时
        pos++; // 移动到下一个字符
        result = result && ParseFactor(expr, values, pos); // 解析下一个因子并进行与运算
    }

    return result; // 返回项的结果
}

// 解析因子
bool ParseFactor(const string& expr, const map<char, bool>& values, size_t& pos)
{
    if (pos >= expr.length())
        return 0; // 如果已经到达字符串末尾，返回0

    char ch = expr[pos]; // 获取当前字符
    if (ch == '(') { // 处理括号
        pos++; // 移动到括号内的第一个字符
        bool result = ParseExpression(expr, values, pos); // 解析括号内的表达式
        if (pos < expr.length() && expr[pos] == ')') { // 如果遇到右括号
            pos++; // 移动到括号后的下一个字符
        }
        return result; // 返回括号内表达式的结果
    } else if (ch == '!') { // 处理非运算
        pos++; // 移动到下一个字符
        return !ParseFactor(expr, values, pos); // 对下一个因子进行非运算
    } else if (isalpha(ch)) { // 处理变量
        pos++; // 移动到下一个字符
        return values.at(ch); // 返回变量的值
    }

    return 0; // 如果都不是上述情况，返回0
}

// 检查是否为有效运算符
bool IsValidOperator(char ch)
{
    if (ch == '!' || ch == '&' || ch == '|' || ch == '^' || ch == '~') {
        return true; // 如果是有效运算符，返回true
    } else {
        return false; // 否则返回false
    }
}

// 获取表达式中的所有变量
set<char> GetVariables(const string& input)
{
    set<char> variables; // 创建一个集合来存储变量
    for (char ch : input) // 遍历输入字符串的每个字符
        if (isalpha(ch)) // 如果是字母
            variables.insert(ch); // 将其添加到变量集合中
    return variables; // 返回变量集合
}

// 打印表格分隔线
void PrintChartLine(int num_variables)
{
    for (int i = 0; i < num_variables; i++) // 对每个变量
        cout << "+-------"; // 打印分隔符
    cout << "+-------+" << endl; // 打印最后的分隔符并换行
    return;
}

// 打印真值表表头
void PrintTableHeader(const set<char>& variables)
{
    cout << "真值表：" << endl;
    PrintChartLine(variables.size()); // 打印上边界线

    cout << "|";
    for (char var : variables) { // 对每个变量
        cout << "   " << var << "   |"; // 打印变量名
    }
    cout << " value |" << endl; // 打印"value"列
    PrintChartLine(variables.size()); // 打印下边界线
}

// 打印真值表行
void PrintTableRow(const map<char, bool>& variable_values, bool result)
{
    cout << "|";
    for (const auto& pair : variable_values) { // 对每个变量
        cout << "   " << pair.second << "   |"; // 打印其值
    }
    cout << "   " << result << "   |" << endl; // 打印结果
    PrintChartLine(variable_values.size()); // 打印行分隔线
}

// 获取表达式的范式
string GetCanonicalForm(const vector<bool>& results, bool is_true_form)
{
    string canonical_form; // 用于存储范式
    char term_prefix = is_true_form ? 'M' : 'm'; // 确定项的前缀
    string separator = "∨";
    if (is_true_form) {
        separator = "∧";
    }

    for (size_t i = 0; i < results.size(); ++i) { // 遍历所有结果
        if (results[i] == is_true_form) { // 如果结果符合所求范式
            if (!canonical_form.empty()) { // 如果不是第一项
                canonical_form += separator; // 添加分隔符
            }
            canonical_form += term_prefix + string("<") + to_string(i) + string(">"); // 添加项
        }
    }

    // 如果范式为空，返回"1"或"0"，否则返回构造的范式
    return canonical_form.empty() ? (is_true_form ? "1" : "0") : canonical_form;
}

// 计算并打印真值表和范式
void CalculateAndPrint(const string& input)
{
    set<char> variables = GetVariables(input); // 获取所有变量
    int num_variables = static_cast<int>(variables.size()); // 获取变量数量

    PrintTableHeader(variables); // 打印表头

    vector<bool> results; // 存储所有可能输入的结果
    for (int i = 0; i < (1 << num_variables); ++i) { // 遍历所有可能的输入组合
        map<char, bool> variable_values; // 存储当前组合的变量值
        int index = 0;
        for (char var : variables) { // 为每个变量赋值
            variable_values[var] = (i & (1 << index)) != 0;
            ++index;
        }

        bool result = CalculateExpression(input, variable_values); // 计算结果
        results.push_back(result); // 存储结果
        PrintTableRow(variable_values, result); // 打印当前行
    }

    cout << "主析取范式: " << endl;
    cout << GetCanonicalForm(results, true) << endl; // 打印主析取范式

    cout << "主合取范式: " << endl;
    cout << GetCanonicalForm(results, false) << endl; // 打印主合取范式
}

// 检查输入是否有效
bool IsValidInput(const string& input)
{
    if (input.empty()) { // 如果输入为空
        cout << "输入无效" << endl;
        return false;
    }

    stack<char> parentheses; // 用于检查括号匹配
    char previous = '\0'; // 存储前一个字符

    for (size_t i = 0; i < input.length(); i++) { // 遍历输入字符串
        char ch = input[i]; // 获取当前字符

        // 检查字符是否有效
        if (!((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || IsValidOperator(ch) || ch == '(' || ch == ')')) {
            cout << "输入无效" << endl;
            return false;
        }

        // 检查语法错误
        if ((i == 0 && (ch == '&' || ch == '|' || ch == '~' || ch == '^')) || (previous == '(' && ch == ')') || (previous == '!' && ch == '!') || (ch == '!' && isalpha(previous)) || ((isalpha(ch) && previous == ')') || (ch == '(' && isalpha(previous))) || (isalpha(ch) && isalpha(previous)) || ((ch == '&' || ch == '|' || ch == '~' || ch == '^') && (!isalpha(previous) && previous != ')'))) {
            cout << "输入无效" << endl;
            return false;
        }

        // 检查括号匹配
        if (ch == '(') {
            parentheses.push(ch);
        } else if (ch == ')') {
            if (parentheses.empty()) {
                cout << "输入无效" << endl;
                return false;
            }
            parentheses.pop();
        }

        previous = ch; // 更新前一个字符
    }

    // 检查最后一个字符和括号匹配
    if (IsValidOperator(previous) || previous == '!' || !parentheses.empty()) {
        cout << "输入无效" << endl;
        return false;
    }

    return true; // 如果通过所有检查，返回true
}

// 获取用户选择（y/n）
void InputChoice(int& value)
{
    char in_value;
    while (1) { // 循环直到获得有效输入
        in_value = _getch(); // 获取用户输入的字符
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

// 打印菜单
void PrintMenu()
{
    printf("+-------------------------------------+\n");
    printf("|                                     |\n");
    printf("|        欢迎进入逻辑运算软件         |\n");
    printf("|    (可运算真值表,主范式,支持括号)   |\n");
    printf("|                                     |\n");
    printf("|              用!表示非              |\n");
    printf("|              用&表示与              |\n");
    printf("|              用|表示或              |\n");
    printf("|             用^表示蕴含             |\n");
    printf("|             用~表示等值             |\n");
    printf("|                                     |\n");
    printf("+-------------------------------------+\n\n");

    return;
}

int main()
{
    while (1) { // 主循环
        system("cls"); // 清屏
        PrintMenu(); // 打印菜单
        cout << "请输入表达式（命题变项只支持大小写单个英文字母）" << endl;
        string input;
        while (1) { // 循环直到获得有效输入
            cin >> input;
            if (IsValidInput(input)) {
                break;
            }
        }

        CalculateAndPrint(input); // 计算并打印结果

        int continue_value;
        cout << "是否继续计算？ （y/n）: ";
        InputChoice(continue_value); // 获取用户是否继续的选择
        if (!continue_value) {
            break; // 如果用户选择不继续，退出主循环
        }
    }
    cout << endl;
    cout << "感谢使用" << endl;
    return 0; // 程序结束
}