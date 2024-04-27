#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include<math.h>
#include<string.h>
#include<time.h>
using namespace std;
constexpr auto MAX = 3;
//报警日期
typedef struct Date {
	int year;//报警日期年份
	int month;//报警日期月份
	int day;//报警日期
}Date;
//报警时间
typedef struct Time {
	int hour;//报警时
	int minute;//报警分
}Time;

//报警信息
typedef struct InforNode {
	Time t;//报警时间
	Time pt;//出警时间
	Date d;//报警日期
	Date pd;//出警日期
	char time[100];//案发时间
	char data[200];//报警内容
	char name[15];//报警人姓名
	char address[30];//报警人家庭住址
	char number[20];//报警人电话
	char pname[15];//出警人姓名
	char pdata[100];//出警人信息
	InforNode* next;//next指针
}InforNode,*InforList;
//创建链表
InforList Create() {
	InforList l;
	l = (InforNode*)malloc(sizeof(InforNode));
	if (!l) return NULL;
	l->next = NULL;
	return l;
}
//获取报警时间函数
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
//获取出警时间
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
//链表节点插入函数
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
//链表节点删除函数
void Delete(InforList l) {
	l->next = l->next->next;
}
//栈存储 
typedef struct Stack {
	InforNode data1[10000];//栈的数据
	int base;//栈底指针
	int top;//栈顶指针
	int stacksize;//栈的容量
}SqStack;
//初始化一个栈
Stack* InitStack() {
	Stack* s;
	s = (Stack*)malloc(sizeof(Stack));
	if (!s) return NULL;
	s->base = 0;
	s->top = s->base;
	s->stacksize = 10000;
	return s;
}
//入栈
void Push(Stack* s, InforNode n) {
	if (s->top - s->base >= 10000) return;
	s->data1[s->top] = n;
	s->top++;
}
//判断是否为空栈
bool Empty(Stack* s) {
	if (s->top == s->base) return true;
	else return false;
}
//出栈
InforNode& Pop(Stack* s, InforNode& n) {
	if (Empty(s)) return n;
	s->top--;
	n = s->data1[s->top];
	return n;
}
//队列存储结构
typedef struct Queue {
	InforNode data2[MAX];//队列数据
	int rear;//队尾指针
	int front;//队头指针
}Queue;
//初始化队列
Queue* InitQue() {
	Queue* q;
	q = (Queue*)malloc(sizeof(Queue));
	if (!q)return NULL;
	q->front = 0;
	q->rear = q->front;
	return q;
}
//判断是否为空队列
bool Empty(Queue* q) {
	if (q->rear == q->front) {
		return true;
	}
	else {
		return false;
	}
}
//判断是否为满
bool Full(Queue* q) {
	if ((q->rear + 1) % 3 == q->front) {
		return true;
	}
	else {
		return false;
	}
}
//入队
void EnQue(Queue* q, InforNode n) {
	if (Full(q)) return;
	q->data2[q->rear] = n;
	q->rear = (q->rear + 1) % 50;
	return;
}
//出队
InforNode& DeQue(Queue* q, InforNode& n) {
	if (Empty(q)) return n;
	n = q->data2[q->front];
	q->front++;
	return n;
}
//公示报警信息函数
void Show(InforNode n) {
	cout <<endl<<endl<< "报警时间为：" << n.d.year << "," << n.d.month << "，" << n.d.day <<endl<<" " <<
		"   " << n.t.hour << ":" << n.t.minute << endl;
	cout << "报警信息为：" <<n.time<<"     " << n.data << endl<<"报警人姓名："<<n.name
		<<endl<<"报警人电话："<<n.number<<endl<<"报警人住址："<<n.address<<endl;
	cout << "************************" << endl<<endl<<endl;
}
//公式出警信息
void PShow(InforNode n) {
	cout << endl << endl << "报警时间为：" << n.d.year << "," << n.d.month << "，" << n.d.day << endl << " " <<
		"   " << n.t.hour << ":" << n.t.minute << endl;
	cout << "报警信息为：" << n.time << "     " << n.data << endl << "报警人姓名：" << n.name
		<< endl << "报警人电话：" << n.number << endl << "报警人住址：" << n.address<<endl;
	cout << "出警人姓名为：" <<n.pname<< endl;
	cout << "出警人信息为：" <<n.pdata<< endl;
	cout << "出警时间为：  " << n.pd.year << "," << n.pd.month << "," << n.pd.day <<
		endl<<"  "<<n.pt.hour<<":"<<n.pt.minute<<endl;
	cout << "************************" << endl << endl << endl;
}
//记录报警信息
void ReCord(InforList l,Queue* q) {
	EnQue(q, *(l->next));
	Delete(l);
}
void RePort(InforList l, Queue* q, Stack* s);//报警系统函数声明
void CallOut(InforList l, Queue* q, Stack* s);//出警系统函数声明
void MainSystem(InforList l, Queue* q, Stack* s);//报警和出警系统管理系统函数声明

//报警系统的实现
void RePort(InforList l, Queue* q, Stack* s) {
	cout <<endl<<endl<< "----------------------------------" << endl;
	cout << "**********************************" << endl;
	cout << "****欢迎使用报警系统****" << endl;
	cout << "请填写报警信息：（案发时间，案件的主要内容,报警人姓名，报警人住址，报警人电话）" << endl;
	Insert(l);
	cout <<endl<<endl<< "报警结束" << endl;
	cout << "**************************************" << endl<<endl<<endl;
}
//出警系统的实现
void CallOut(InforList l,Queue* q,Stack* s) {
	cout <<endl<<endl<< "----------------------------------" << endl;
	cout << "**********************************" << endl;
	cout << "****欢迎使用出警系统****" << endl;
	InforNode n;
	int i;
	cout << "请选择想要进行的操作：" << endl;
	cout << "1、处理报警信息" << endl;
	cout << "2、查看待处理报警信息" << endl;
	cout << "3、查看已经出警信息" << endl;
	cout << "4、返回报警出警系统" << endl;
	cin >> i;
	if (i == 1) {
		if (Empty(q)) {
			cout << "无可处理报警信息" << endl << endl << endl;
			return;
		}
		n =DeQue(q, n);
		Show(n);
		cout << "是否要出警 1、出警 2、取消出警" << endl;
		cin >> i;
		if (i == 1) {
			cout << "请输入出警人姓名：" << endl;
			cin >> n.pname;
			cout << "请输入出警人信息：" << endl;
			cin >> n.pdata;
			n = *(CreatePTime(&n));
			Push(s, n);
			cout << "已出警" << endl<<endl;
		}
		else {
			EnQue(q, n);
			cout << "已取消出警" << endl << endl;
		}
		
	}
	else if (i == 3) {
		int t;
		t = s->top - 1;
		if (t < s->base) {
			cout << "无已经出警信息" << endl << endl;
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
			cout << "无待处理信息" << endl << endl;
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
//实时报警出警管理系统实现
void MainSystem(InforList l, Queue* q, Stack* s) {
	cout << "----------------------------------" << endl;
	cout << "**********************************" << endl;
	cout << "*****欢迎使用报警出警管理系统*****" << endl;
	cout << "请输入需求：1、进入报警系统 2、进入出警系统 3、退出系统" << endl;
	int i;
	if(Full(q)) {
		cout <<endl<<endl<< "！警告 ,报警信息过多请尽快处理" << endl;
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
		cout <<endl<<endl<< "******感谢您的使用*******" << endl;
		return;
	}
	MainSystem(l, q, s);

}
//主函数
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