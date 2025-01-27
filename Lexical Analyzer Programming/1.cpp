#include<iostream>
#include<string> 
using namespace std;

string KEYWORD[5] = { "while", "if", "else", "switch", "case" }; //关键字 
char SEPARATER[5] = { ';', '{', '}', '(', ')' };  //分隔符
char OPERATOR[8] = { '+', '-', '*', '/', '>', '<', '=', '!' };   //运算符
char FILTER[4] = { ' ', '\t', '\r', '\n' };          //过滤符

bool IsKeyword(string word) {
    for (int i = 0; i < 5; i++) {
        if (KEYWORD[i] == word) {
            return true;
        }
    }
    return false;
}

bool IsSeparater(char ch) {
    for (int i = 0; i < 5; i++) {
        if (SEPARATER[i] == ch) {
            return true;
        }
    }
    return false;
}

bool IsOperator(char ch) {
    for (int i = 0; i < 8; i++) {
        if (OPERATOR[i] == ch) {
            return true;
        }
    }
    return false;
}

bool IsFilter(char ch) {
    for (int i = 0; i < 4; i++) {
        if (FILTER[i] == ch) {
            return true;
        }
    }
    return false;
}

bool IsLetter(char ch) {
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

bool IsDigit(char ch) {
    return (ch >= '0' && ch <= '9');
}

int main() {
    char ch = NULL;
    string s, strToken;
    FILE* file;
    errno_t err = freopen_s(&file, "example.txt", "r", stdin);
    if (err != 0 || file == nullptr) {
        cerr << "Error opening file. Please check the file path." << endl;
        return 1;
    }

    while (ch || cin >> ch) {
        strToken = "";
        if (IsFilter(ch)) {
            // 判断是否为过滤符
        }
        else if (IsLetter(ch)) {
            // 判断是否为关键字 
            while (IsLetter(ch)) {
                strToken += ch;
                cin >> ch; // 注意，退出循环前已经读取了下一字符存入ch 
            }
            if (IsKeyword(strToken))
                cout << "(" << strToken << ",_)" << endl; // 判断是否为关键字 
            else
                cout << "(" << "id," << strToken << ")" << endl; // 判断是否为标识符 
        }
        else if (IsDigit(ch)) { // 判断是否为数字 
            while (IsDigit(ch)) {
                strToken += ch;
                cin >> ch;
            }
            cout << "(" << "num," << strToken << ")" << endl;
        }
        else if (IsOperator(ch)) { // 判断是否为运算符 
            while (IsOperator(ch)) {
                strToken += ch;
                cin >> ch;
            }
            cout << "(" << "operator," << strToken << ")" << endl;
        }
        else if (IsSeparater(ch)) { // 判断是否为分隔符 
            cout << "(" << "separater," << ch << ")" << endl;
            if (cin >> ch) {} // 继续读取下一字符，若读完所有源程序，退出读取字符循环 
            else break;
        }
        else {
            cout << "无法识别该字符！" << endl;
            if (cin >> ch) {}
            else break;
        }
    }
    return 0;
}
