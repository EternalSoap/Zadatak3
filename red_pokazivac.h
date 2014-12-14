#include<iostream>
#include<ctime>
using namespace std;

struct telement{
	char pi[50];
	tm rodendan;
	int spol,ai,bi,ci,di;
};

struct treds{
	telement element;
	treds* sljedeci;
};

struct tred{
	treds* front;
	treds* rear;
};

tred q,pom;

void InitQ(tred& q){
	q.front=q.rear=new treds;
	q.front->sljedeci=q.rear->sljedeci=NULL;
};

int IsEmptyQ(tred& q){
	if(q.front==q.rear) return 1;
	return 0;
};

telement FrontQ(tred& q){
	return q.front->sljedeci->element;
};

void EnQueueQ(telement x,tred& q){
	treds* novi=new treds;
	novi->element = x;
	novi->sljedeci=NULL;
	q.rear->sljedeci=novi;
	q.rear=novi;
};

int DeQueueQ(tred& q){
	if(IsEmptyQ(q)) return 0;
	treds*c=q.front;
	q.front=q.front->sljedeci;
	delete c;
	return 1;
};

