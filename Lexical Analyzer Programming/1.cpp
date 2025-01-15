#include<iostream>
#include<string> 
using namespace std;

string KEYWORD[5] = { "while", "if", "else", "switch", "case" }; //�ؼ��� 
char SEPARATER[5] = { ';', '{', '}', '(', ')' };  //�ָ���
char OPERATOR[8] = { '+', '-', '*', '/', '>', '<', '=', '!' };   //�����
char FILTER[4] = { ' ', '\t', '\r', '\n' };          //���˷�

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
            // �ж��Ƿ�Ϊ���˷�
        }
        else if (IsLetter(ch)) {
            // �ж��Ƿ�Ϊ�ؼ��� 
            while (IsLetter(ch)) {
                strToken += ch;
                cin >> ch; // ע�⣬�˳�ѭ��ǰ�Ѿ���ȡ����һ�ַ�����ch 
            }
            if (IsKeyword(strToken))
                cout << "(" << strToken << ",_)" << endl; // �ж��Ƿ�Ϊ�ؼ��� 
            else
                cout << "(" << "id," << strToken << ")" << endl; // �ж��Ƿ�Ϊ��ʶ�� 
        }
        else if (IsDigit(ch)) { // �ж��Ƿ�Ϊ���� 
            while (IsDigit(ch)) {
                strToken += ch;
                cin >> ch;
            }
            cout << "(" << "num," << strToken << ")" << endl;
        }
        else if (IsOperator(ch)) { // �ж��Ƿ�Ϊ����� 
            while (IsOperator(ch)) {
                strToken += ch;
                cin >> ch;
            }
            cout << "(" << "operator," << strToken << ")" << endl;
        }
        else if (IsSeparater(ch)) { // �ж��Ƿ�Ϊ�ָ��� 
            cout << "(" << "separater," << ch << ")" << endl;
            if (cin >> ch) {} // ������ȡ��һ�ַ�������������Դ�����˳���ȡ�ַ�ѭ�� 
            else break;
        }
        else {
            cout << "�޷�ʶ����ַ���" << endl;
            if (cin >> ch) {}
            else break;
        }
    }
    return 0;
}
