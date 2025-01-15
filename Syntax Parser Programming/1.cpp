#include<iostream>
#include<stdio.h>
#include<vector>
#include<string>
#include<stack>
#include<map>
#include<iomanip>
#include<cstring>
#include<cstdlib>
using namespace std;
map<char, int>getnum;
vector<char>getzf;
vector<string>proce(8);
vector<string>first(20);
vector<string>follow(20);
int table[100][100];      //Ԥ�������
int num;
int numv;//�ս��������-1
char j[2];

//��ȡ�ս�������ս�������ʽ 
void  read()
{
	char c;
	int i = 0;
	int n = 0;
	cout << "******************************LL(1)�﷨����****************************" << endl;
	cout << "ע�⣺E'��H���棬T����J���棬�մ���@���� " << endl;
	cout << "���������ʽ�ļ��ϣ�����'@'��ʾ��,����һ������ʽ���У������'end'����:" << endl;
	string ss;
	string dd;
	int j = 0;
	int y = 0;
	while (cin >> ss && ss != "end")
	{
		dd.clear();
		dd += ss[0];
		proce[j] += dd;
		for (i = 3; i < ss.length(); i++)
		{
			if (ss[i] != '|') {
				dd.clear();
				dd += ss[i];
				proce[j] += dd;
			}
			else {
				dd.clear();
				dd += ss[0];
				dd += ss[++i];
				proce[++j] += dd;
			}
		}
		j++;
	}
	getnum['#'] = 0;//#���������־  
	getzf.push_back('#');
	//�ս��ѹջ 
	for (int i = 0; i < proce.size(); i++)
	{
		for (int k = 0; k < proce[i].length(); k++)
		{
			if (proce[i][k] != '-' && proce[i][k] != '|')
			{
				if (proce[i][k] < 64 || proce[i][k]>90)
				{
					for (y = 0; y < getzf.size(); y++) {
						if (proce[i][k] == getzf[y])
							break;
					}
					if (y == getzf.size() && k != 2) {
						getnum[proce[i][k]] = ++n;
						getzf.push_back(proce[i][k]);
					}
				}
			}
		}
	}
	getnum['@'] = ++n;
	numv = n;//�ս�����������ڵ�ǰn��ֵ 
	getzf.push_back('@');
	//���ս��ѹջ 
	for (int i = 0; i < proce.size(); i++)
	{
		for (int k = 0; k < proce[i].length(); k++)
		{
			if (proce[i][k] != '-' && proce[i][k] != '|' && proce[i][k] != '>')
			{
				if (proce[i][k] > 64 && proce[i][k] < 91)
				{
					for (y = 0; y < getzf.size(); y++) {
						if (proce[i][k] == getzf[y])
							break;
					}
					if (y == getzf.size()) {
						getnum[proce[i][k]] = ++n;
						num = n;
						getzf.push_back(proce[i][k]);
					}
				}
			}
		}
	}
}

//���ս����first���鸳ֵ
void get_firstT()
{
	int i;
	//�ȸ��ս����first���鸳ֵ
	for (i = 1; i <= numv; i++)
	{
		_itoa_s(i, j, 10);
		first[i] = j;
	}
}

//�����ս����first���鸳ֵ
string get_firstF(int* a)
{
	for (int i = 0; i < proce.size(); i++)
	{
		if (getnum[proce[i][0]] == *a)
		{
			if (getnum[proce[i][1]] <= numv)
			{
				_itoa_s(getnum[proce[i][1]], j, 10);
				first[*a] += j;
			}
			else
			{
				//first[getnum[proce[i][0]]].clear();
				first[getnum[proce[i][0]]] = get_firstF(&getnum[proce[i][1]]);
			}
		}
	}
	return first[*a];
}

//��follow�� 
void  get_follow(int* a) {
	int i, j1;
	int flag = 0;
	for (i = 0; i < proce.size(); i++)
	{
		for (j1 = 1; j1 < proce[i].length(); j1++)
		{
			if (getnum[proce[i][j1]] == *a)
			{
				if (j1 == proce[i].length() - 1)
				{
					if (getnum[proce[i][j1]] != getnum[proce[i][0]])
						follow[*a] += follow[getnum[proce[i][0]]];
				}
				else
				{
					if (getnum[proce[i][j1 + 1]] <= numv)
					{
						_itoa_s(getnum[proce[i][j1 + 1]], j, 10);
						follow[*a] += j;
					}
					else
					{
						for (int jj = 0; jj < first[getnum[proce[i][j1 + 1]]].size(); jj++)
						{
							if (atoi(&first[getnum[proce[i][j1 + 1]]][jj]) == numv)
								follow[*a] += follow[getnum[proce[i][0]]];
							else
								follow[*a] += first[getnum[proce[i][j1 + 1]]][jj];
						}
						flag = 1;//��־λ������Ѿ��ҵ�*a����ķ��ս���Ϳ���ֹͣ�� 
					}
				}
			}
		}

		if (flag == 1) break; //ֹͣѰ�� 
	}
}


//��Ԥ�������
void get_table()
{
	memset(table, -1, sizeof(table));
	for (int i = 0; i < proce.size(); i++)   //ɨ���в���ʽ
	{
		if (proce[i][1] == '@')     //ֱ���Ƴ����ֵģ������£�follow��=����ʽ��ߵ�vn��Ԫ���
		{
			string flw = follow[getnum[proce[i][0]]];
			for (int k = 0; k < flw.size(); k++)
			{
				table[getnum[proce[i][0]]][flw[k] - '0'] = i;
			}
		}
		string temps = first[getnum[proce[i][1]]];
		for (int j = 0; j < temps.size(); j++)               //����first��
		{
			if (atoi(&temps[j]) != numv)
			{
				table[getnum[proce[i][0]]][temps[j] - '0'] = i;
			}
			else                                     //�п��ֵģ�����follw��
			{
				string flw = follow[getnum[proce[i][1]]];
				for (int k = 0; k < flw.size(); k++)
				{
					table[getnum[proce[i][0]]][flw[k] - '0'] = i;
				}
			}
		}
	}
}

//�ɶ�Ӧ�±��ö�Ӧ����ʽ
string get_proce(int i)
{
	if (i < 0)return " ";
	string ss;
	ss += proce[i][0];
	ss += "->";
	for (int j = 1; j < proce[i].size(); j++)
		ss += proce[i][j];
	return ss;
}

//���Ԥ������� 
void print_table()
{
	cout << "���ķ���Ӧ��Ԥ����������£�" << endl;
	cout << "________________________________________________________" << endl;
	for (int i = 0; i < numv; i++)
		cout << '\t' << getzf[i];
	cout << endl;
	for (int i = numv + 1; i <= num; i++)
	{
		cout << endl << "________________________________________________________" << endl;
		cout << getzf[i];
		for (int j = 0; j < numv; j++)
		{
			cout << '\t' << get_proce(table[i][j]) << "";
		}
	}
	cout << endl << "________________________________________________________" << endl;
	cout << endl;
}

//��ӡջ��Ԫ��
void print_stack(stack<char>sta) {
	int length = sta.size();//ջ��Ԫ����Ŀ
	vector<char>temp;
	for (int i = 0; i < length; i++) {
		temp.push_back(sta.top());
		sta.pop();
	}
	for (int j = length - 1; j >= 0; j--) {
		cout << temp[j];

	}
	cout << "\t\t";
}

//��ӡ�ж����ĵ�ǰԪ��
void print_string(string str, int index) {
	int length = str.size();
	for (int i = index; i < length; i++) {
		cout << str[i];
	}
	cout << '#';
	cout << "\t\t";
}


//����word���Ŵ��ĺϷ���(�ؼ�)
string word;
bool analyze()
{
	stack<char>sta;//����ջ 
	sta.push('#');  //#���Ƚ�ջ 
	sta.push(proce[0][0]);//����ʼ��ѹ�����ջ�н��г�ʼ�� 
	int i = 0;
	int count = 1;//�������  
	printf("����\t\t����ջ\t\t�ж���\t\tʹ�ù���\n");//��ͷ 
	while (!sta.empty())
	{
		cout << count << "\t\t";
		print_stack(sta);//��ӡ��ǰ����ջ 
		print_string(word, i);//��ӡ��ǰ�ж��� 
		int cur = sta.top();//ȡ������ջ��ջ��Ԫ�� 
		sta.pop();
		if (cur == word[i])       //�������ջ��ջ��Ԫ�����ж����ĵ�һ��Ԫ����ͬ�������ս���Ļ�������ƥ��ɹ�������ջ����ջ��Ԫ�� 
		{
			i++;
			printf("ƥ���ջ\n");
		}
		else  if (cur == '#')   //�������ջ��ջ��Ԫ��Ϊ#������������
		{
			return 1;
		}
		else  if (table[getnum[cur]][getnum[word[i]]] != -1) //���Ҷ�Ӧ��Ԥ������� 
		{

			int k = table[getnum[cur]][getnum[word[i]]];
			cout << proce[k][0] << "->";
			for (int j = 1; j < proce[k].size(); j++)
				cout << proce[k][j];
			cout << endl;
			//��ʹ�õĲ���ʽ����������ջ�У���ȡ����һ����ջ��Ԫ�� 
			for (int j = proce[k].size() - 1; j > 0; j--)
			{
				if (proce[k][j] != '@')
					sta.push(proce[k][j]);
			}
		}
		else
		{
			return 0;
		}
		count++;
	}
	return 1;
}


//������жϵķ��Ŵ� 
void scanf()
{
	cout << "��������ж��ķ��Ŵ���";
	cin >> word;
	cout << "�жϷ��������£�" << endl;
	if (analyze())
		cout << endl << "���ϣ��÷��Ŵ���Ч���Ǹ��ķ��ľ��ͣ�" << endl;
	else
		cout << endl << "�����÷��Ŵ����Ǹ��ķ��ľ��ͣ�" << endl;
}


int main()
{
	int k;
	int j;
	read();
	//�ս����first�� 
	get_firstT();
	//���ս����first�� 
	for (k = numv + 1; k <= num; k++)
	{
		get_firstF(&k);
	}

	follow[numv + 1] += '0';
	for (k = numv + 1; k <= num; k++)
	{
		get_follow(&k);
	}
	cout << endl;
	get_table();
	print_table();
	scanf();
	return 0;
}
