#include<iostream>
#include<cstring>
#include<cstdlib>
#include<fstream>
#include<ctime>
#include"red_polje.h"
//#include"red_pokazivac.h"

using namespace std;

struct tsalter{
	telement element;
	int prazan;
};

void fill(telement *&polje,int n){
	for(int i=0;i<n;i++){
		polje[i].ai=rand()%491+10;
		polje[i].bi=rand()%721+80;
		polje[i].ci=rand()%5+1;
		polje[i].di=rand()%5+1;
	}
}

void fill(telement ** polje2,telement *&polje,int n){
	int ** tru = new int*[5];
	for(int i=0;i<5;i++) tru[i]=new int[5];
	fill(polje,n);
	for(int i=0;i<n;i++)
		for(int j=0;j<5;j++)
			polje2[i][j]=polje[i];
}

void unos(telement ** polje,int n){
	char num[10];
	char zi[2];
	char zj[2];
	for	(int i=0;i<n;i++)
		for(int j=0;j<5;j++){
			
			char pin[50]="Osoba";
			itoa(i+1,zi,10);
			itoa(j+1,zj,10);
			strcpy(num,zi);
			strcat(num,zj);
			strcat(pin,num);
			strcpy(polje[i][j].pi,pin);
			polje[i][j].spol=(polje[i][j].ci==3?0:rand()%2);
			polje[i][j].rodendan.tm_year=((polje[i][j].ci==3?rand()%31+64:(polje[i][j].ci==4?rand()%35+14:rand()%46+49)));
			polje[i][j].rodendan.tm_mon = rand()%12;
			polje[i][j].rodendan.tm_mday = rand()%31+1;
//test			cout<<2014-(polje[i][j].rodendan.tm_year+1900)<<endl;
			
		}
	
			
}

int generiraj(telement ** polje2,int n){
	telement * polje = new telement[n];
	fill(polje2,polje,n);
	unos(polje2,n);
//test	for(int i=0;i<n;i++){for(int j=0;j<5;j++)if((polje2[i][j].di==4 && 2014-(polje2[i][j].rodendan.tm_year+1900)<40 && polje2[i][j].rodendan.tm_mon+1==1)|| polje2[i][j].ci==3 && polje2[i][j].di==5)cout<<polje2[i][j].pi<<" "<<polje2[i][j].ai<<" "<<polje2[i][j].bi<<" "<<polje2[i][j].ci<<" "<<polje2[i][j].di<<" "<<polje2[i][j].rodendan.tm_mday<<"."<<polje2[i][j].rodendan.tm_mon+1<<"."<<2014-(polje2[i][j].rodendan.tm_year+1900)<<endl;}
	return n;
}

void trudnice(){
	InitQ(pom);
	while(!IsEmptyQ(q)){
		if(FrontQ(q).ci==3 && FrontQ(q).di==5){
			//test cout<<"Odlazi trudnica "<<FrontQ(q).pi<<endl;
			DeQueueQ(q);
		}
		else{
			EnQueueQ(FrontQ(q),pom);
			DeQueueQ(q);
		}
	}
	while(!IsEmptyQ(pom)){
		EnQueueQ(FrontQ(pom),q);
		DeQueueQ(pom);
	}
}

void dodaj(telement ** polje,int n){
	tsalter salter[5];
	for(int i=0;i<5;i++) {salter[i].prazan=1;}
		
	
	//ispis svih osoba u polju for(int i=0;i<5;i++){for(int j=0;j<5;j++)cout<<polje[i][j].pi<<" "<<polje[i][j].ai<<" "<<polje[i][j].bi<<" "<<polje[i][j].ci<<" "<<polje[i][j].di<<" "<<polje[i][j].rodendan.tm_mday<<"."<<polje[i][j].rodendan.tm_mon+1<<"."<<2014-(polje[i][j].rodendan.tm_year+1900)<<endl;}
	
	int tiem;
	for(int j=0;j<5;j++){
		for(int i=0;i<n;i++){
			telement novi = polje[i][j];
			int zbrajaj =0;
			if(novi.ci==4) zbrajaj =1;
			if(zbrajaj) tiem+=novi.ai;
			if(tiem>1000) trudnice();
			for(int k =0;k<5;k++){
				if(!salter[k].prazan){ 
			 		salter[k].element.bi-=novi.ai; 
					if(salter[k].element.bi<=0){
						salter[k].prazan=1;
					//	cout<<"Odlazi "<<salter[k].element.di<<endl;
					}
					}
				}
			if(IsEmptyQ(q)){
				if(salter[novi.di-1].prazan){
					salter[novi.di-1].element=novi;
					salter[novi.di-1].prazan=0;
				}
				else EnQueueQ(novi,q);
			}
			else{
					telement prvi = FrontQ(q);
					if(salter[prvi.di-1].prazan){
						if(novi.di==prvi.di){
							if(prvi.ci<novi.ci){
								salter[prvi.di-1].element=prvi;
								salter[prvi.di-1].prazan=0;
								DeQueueQ(q);
								EnQueueQ(novi,q);
							}
							else{ salter[novi.di-1].element = novi;salter[prvi.di-1].prazan=0;}
						}
						else{
							salter[prvi.di-1].element = prvi;
							salter[prvi.di-1].prazan=0;
							DeQueueQ(q);
							EnQueueQ(novi,q);
					}
				}
				else{EnQueueQ(novi,q);}		
			}
		}
	}
cout<<"Stanje glavnog reda\nIme i prezime\t Spol\t Rodendan\t ai\t bi\tci\t di\n";
while(!IsEmptyQ(q)){
	telement x = FrontQ(q);
	EnQueueQ(x,pom);
	cout<<x.pi<<" \t "<<x.spol<<" \t "<<x.rodendan.tm_mday<<"."<<x.rodendan.tm_mon+1<<"."<<x.rodendan.tm_year+1900<<" \t "<<x.ai<<" \t "<<x.bi<<" \t "<<x.ci<<" \t "<<x.di<<endl;
	DeQueueQ(q);	
}
while(!IsEmptyQ(pom)){
	EnQueueQ(FrontQ(pom),q);
	DeQueueQ(pom);
}
};

void horoskop(){
	cout<<"\nOsobe mlade od 40 godina horoskopskog znaka jarac u redu za uplatu lutrije "<<endl<<endl;	
	cout<<"Ime i prezime\t Spol\t Rodendan\t ai\t bi\tci\t di\n";
	while(!IsEmptyQ(q)){
		telement x = FrontQ(q);
		EnQueueQ(x,pom);
		if( (2014-(x.rodendan.tm_year+1900)<40) && ((x.rodendan.tm_mon+1==12 && (x.rodendan.tm_mday>=22&&x.rodendan.tm_mday<=31)) || (x.rodendan.tm_mon+1==1 && (x.rodendan.tm_mday>=1 && x.rodendan.tm_mday<=20))) && x.di==3)
		cout<<x.pi<<" \t "<<x.spol<<" \t "<<x.rodendan.tm_mday<<"."<<x.rodendan.tm_mon+1<<"."<<x.rodendan.tm_year+1900<<" \t "<<x.ai<<" \t "<<x.bi<<" \t "<<x.ci<<" \t "<<x.di<<endl;
		DeQueueQ(q);	
	}
	while(!IsEmptyQ(pom)){
		EnQueueQ(FrontQ(pom),q);
		DeQueueQ(pom);
	}
	
};

int main(){
	InitQ(q);
	InitQ(pom);
	int n;
	cout<<"N ";
	cin>>n;
	telement ** polje2=new telement*[n];
	for(int i=0;i<n;i++) polje2[i] = new telement[5];
	generiraj(polje2,n);
	dodaj(polje2,n);
	horoskop();
}
