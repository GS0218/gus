#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include<math.h>
#include<string.h>
#include<time.h>
using namespace std;
constexpr auto MAX = 3;
//��������
typedef struct Date {
	int year;//�����������
	int month;//���������·�
	int day;//��������
}Date;
//����ʱ��
typedef struct Time {
	int hour;//����ʱ
	int minute;//������
}Time;

//������Ϣ
typedef struct InforNode {
	Time t;//����ʱ��
	Time pt;//����ʱ��
	Date d;//��������
	Date pd;//��������
	char time[100];//����ʱ��
	char data[200];//��������
	char name[15];//����������
	char address[30];//�����˼�ͥסַ
	char number[20];//�����˵绰
	char pname[15];//����������
	char pdata[100];//��������Ϣ
	InforNode* next;//nextָ��
}InforNode,*InforList;
//��������
InforList Create() {
	InforList l;
	l = (InforNode*)malloc(sizeof(InforNode));
	if (!l) return NULL;
	l->next = NULL;
	return l;
}
//��ȡ����ʱ�亯��
void CreateTime(InforList l) {
	time_t timep;
	struct tm* p;
	time(&timep);
	p = gmtime(&timep);
	l->d.year = p->tm_year + 1900;
	l->d.month = p->tm_mon + 1;
	l->d.day = p->tm_mday;
	l->t.hour = p->tm_hour + 8;
	l->t.minute = p->tm_min;
}
//��ȡ����ʱ��
InforList CreatePTime(InforList l) {
	time_t timep;
	struct tm* p;
	time(&timep);
	p = gmtime(&timep);
	l->pd.year = p->tm_year + 1900;
	l->pd.month = p->tm_mon + 1;
	l->pd.day = p->tm_mday;
	l->pt.hour = p->tm_hour + 8;
	l->pt.minute = p->tm_min;
	return l;
}
//����ڵ���뺯��
void Insert(InforList l) {
	InforNode* p;
	p = (InforList)malloc(sizeof(InforNode));
	CreateTime(p);
	cin >> p->time;
	cin >> p->data;
	cin >> p->name;
	cin >> p->address;
	cin >> p->number;
	p->next = l->next;
	l->next = p;
}
//����ڵ�ɾ������
void Delete(InforList l) {
	l->next = l->next->next;
}
//ջ�洢 
typedef struct Stack {
	InforNode data1[10000];//ջ������
	int base;//ջ��ָ��
	int top;//ջ��ָ��
	int stacksize;//ջ������
}SqStack;
//��ʼ��һ��ջ
Stack* InitStack() {
	Stack* s;
	s = (Stack*)malloc(sizeof(Stack));
	if (!s) return NULL;
	s->base = 0;
	s->top = s->base;
	s->stacksize = 10000;
	return s;
}
//��ջ
void Push(Stack* s, InforNode n) {
	if (s->top - s->base >= 10000) return;
	s->data1[s->top] = n;
	s->top++;
}
//�ж��Ƿ�Ϊ��ջ
bool Empty(Stack* s) {
	if (s->top == s->base) return true;
	else return false;
}
//��ջ
InforNode& Pop(Stack* s, InforNode& n) {
	if (Empty(s)) return n;
	s->top--;
	n = s->data1[s->top];
	return n;
}
//���д洢�ṹ
typedef struct Queue {
	InforNode data2[MAX];//��������
	int rear;//��βָ��
	int front;//��ͷָ��
}Queue;
//��ʼ������
Queue* InitQue() {
	Queue* q;
	q = (Queue*)malloc(sizeof(Queue));
	if (!q)return NULL;
	q->front = 0;
	q->rear = q->front;
	return q;
}
//�ж��Ƿ�Ϊ�ն���
bool Empty(Queue* q) {
	if (q->rear == q->front) {
		return true;
	}
	else {
		return false;
	}
}
//�ж��Ƿ�Ϊ��
bool Full(Queue* q) {
	if ((q->rear + 1) % 3 == q->front) {
		return true;
	}
	else {
		return false;
	}
}
//���
void EnQue(Queue* q, InforNode n) {
	if (Full(q)) return;
	q->data2[q->rear] = n;
	q->rear = (q->rear + 1) % 50;
	return;
}
//����
InforNode& DeQue(Queue* q, InforNode& n) {
	if (Empty(q)) return n;
	n = q->data2[q->front];
	q->front++;
	return n;
}
//��ʾ������Ϣ����
void Show(InforNode n) {
	cout <<endl<<endl<< "����ʱ��Ϊ��" << n.d.year << "," << n.d.month << "��" << n.d.day <<endl<<" " <<
		"   " << n.t.hour << ":" << n.t.minute << endl;
	cout << "������ϢΪ��" <<n.time<<"     " << n.data << endl<<"������������"<<n.name
		<<endl<<"�����˵绰��"<<n.number<<endl<<"������סַ��"<<n.address<<endl;
	cout << "************************" << endl<<endl<<endl;
}
//��ʽ������Ϣ
void PShow(InforNode n) {
	cout << endl << endl << "����ʱ��Ϊ��" << n.d.year << "," << n.d.month << "��" << n.d.day << endl << " " <<
		"   " << n.t.hour << ":" << n.t.minute << endl;
	cout << "������ϢΪ��" << n.time << "     " << n.data << endl << "������������" << n.name
		<< endl << "�����˵绰��" << n.number << endl << "������סַ��" << n.address<<endl;
	cout << "����������Ϊ��" <<n.pname<< endl;
	cout << "��������ϢΪ��" <<n.pdata<< endl;
	cout << "����ʱ��Ϊ��  " << n.pd.year << "," << n.pd.month << "," << n.pd.day <<
		endl<<"  "<<n.pt.hour<<":"<<n.pt.minute<<endl;
	cout << "************************" << endl << endl << endl;
}
//��¼������Ϣ
void ReCord(InforList l,Queue* q) {
	EnQue(q, *(l->next));
	Delete(l);
}
void RePort(InforList l, Queue* q, Stack* s);//����ϵͳ��������
void CallOut(InforList l, Queue* q, Stack* s);//����ϵͳ��������
void MainSystem(InforList l, Queue* q, Stack* s);//�����ͳ���ϵͳ����ϵͳ��������

//����ϵͳ��ʵ��
void RePort(InforList l, Queue* q, Stack* s) {
	cout <<endl<<endl<< "----------------------------------" << endl;
	cout << "**********************************" << endl;
	cout << "****��ӭʹ�ñ���ϵͳ****" << endl;
	cout << "����д������Ϣ��������ʱ�䣬��������Ҫ����,������������������סַ�������˵绰��" << endl;
	Insert(l);
	cout <<endl<<endl<< "��������" << endl;
	cout << "**************************************" << endl<<endl<<endl;
}
//����ϵͳ��ʵ��
void CallOut(InforList l,Queue* q,Stack* s) {
	cout <<endl<<endl<< "----------------------------------" << endl;
	cout << "**********************************" << endl;
	cout << "****��ӭʹ�ó���ϵͳ****" << endl;
	InforNode n;
	int i;
	cout << "��ѡ����Ҫ���еĲ�����" << endl;
	cout << "1����������Ϣ" << endl;
	cout << "2���鿴����������Ϣ" << endl;
	cout << "3���鿴�Ѿ�������Ϣ" << endl;
	cout << "4�����ر�������ϵͳ" << endl;
	cin >> i;
	if (i == 1) {
		if (Empty(q)) {
			cout << "�޿ɴ�������Ϣ" << endl << endl << endl;
			return;
		}
		n =DeQue(q, n);
		Show(n);
		cout << "�Ƿ�Ҫ���� 1������ 2��ȡ������" << endl;
		cin >> i;
		if (i == 1) {
			cout << "�����������������" << endl;
			cin >> n.pname;
			cout << "�������������Ϣ��" << endl;
			cin >> n.pdata;
			n = *(CreatePTime(&n));
			Push(s, n);
			cout << "�ѳ���" << endl<<endl;
		}
		else {
			EnQue(q, n);
			cout << "��ȡ������" << endl << endl;
		}
		
	}
	else if (i == 3) {
		int t;
		t = s->top - 1;
		if (t < s->base) {
			cout << "���Ѿ�������Ϣ" << endl << endl;
		}
		while (t >= s->base) {
			PShow(s->data1[t]);
			t--;
		}
		
	}
	else if (i == 2) {
		int t;
		t = q->front;
		if (t % 3 == q->rear) {
			cout << "�޴�������Ϣ" << endl << endl;
		}
		while (t % 3 < q->rear) {
			Show(q->data2[t]);
			t = (t + 1) % 3;
		}
		
	}
	else if (i == 4) {
		return;
	}
	CallOut(l, q, s);
}
//ʵʱ������������ϵͳʵ��
void MainSystem(InforList l, Queue* q, Stack* s) {
	cout << "----------------------------------" << endl;
	cout << "**********************************" << endl;
	cout << "*****��ӭʹ�ñ�����������ϵͳ*****" << endl;
	cout << "����������1�����뱨��ϵͳ 2���������ϵͳ 3���˳�ϵͳ" << endl;
	int i;
	if(Full(q)) {
		cout <<endl<<endl<< "������ ,������Ϣ�����뾡�촦��" << endl;
	}

	cin >> i;
	if (i == 1) {
		RePort(l, q, s);
		ReCord(l, q);
		
	}
	else if (i == 2) {
		CallOut(l, q, s);
		
	}
	else if (i == 3) {
		cout <<endl<<endl<< "******��л����ʹ��*******" << endl;
		return;
	}
	MainSystem(l, q, s);

}
//������
int main() {
	InforList l;
	Stack* s;
	Queue* q;
	l = Create();
	s = InitStack();
	q = InitQue();
	MainSystem(l, q, s);
	return 0;
}