#include<iostream>
#include<ctime>
using namespace std;

struct telement{
	char pi[50];
	tm rodendan;
	int spol,ai,bi,ci,di;
};

struct tred{
	telement element[10000];
	int front, rear;
};

tred q,pom;


int AddOne(int n){
	return((n+1)%10000);
};

void InitQ(tred& q){
	q.front=0;
	q.rear=9999;
};

int IsEmptyQ(tred& q){
	if(AddOne(q.rear)==q.front) return 1;
	else return 0;
};

telement FrontQ(tred& q){
	return (q.front[q.element]);
};

int EnQueueQ(telement x, tred& q){
	if(AddOne(AddOne(q.rear))==q.front) return 0;
	q.rear=AddOne(q.rear);
	q.rear[q.element]=x;
	return 1;
};

int DeQueueQ(tred& q){
	if(IsEmptyQ(q)) return 0;
	q.front = AddOne(q.front);
	return 1;
};




