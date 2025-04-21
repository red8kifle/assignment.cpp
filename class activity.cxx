#include<iostream>
using namespace std;

//1.Overloaded Function
int multiply (int x , int y){
	return x*y;
}
double multiply (double x ,double y){
	return x*y ;
}
int multiply(int x ,int y, int z){
	return x*y*z ;
}
int main(){
	cout<< multiply(1,2)<< '\n';
	cout<<multiply(10,2,5)<< '\n';
	cout<<multiply(2.5,5.0);
	return 0 ;
}

/* 2. Function templates
template<typename genericType>
genericType multiply (genericType x ,genericType y){
	return x*y;
}
int main(){
	cout<<multiply(10.5,8.5);
	cout<<multiply(10,10);
	return 0;
}

//3.name spaces
namespace num{
	int value(){return 10;}
}
namespace calc{
	const double e =2.718;
	double value(){return 3* e;}
}
int main(){
	cout<< num::value()<<'\n';
	cout<<calc::value()<<'\n';
	cout<<calc::e <<'\n';
	return 0;
}

//4. structures and nested structure in one example
struct patient{
	int id;
	string name;
};

struct Doctor{
	string name;
	int id;
	patient patient;
};

int main(){
	patient almaz, chala ;
	
	chala.id=5;
	chala.name="chala nega";
	almaz.id=89;
	almaz.name= "almaz alemu";
	cout<<almaz.name<<endl;
	cout<<almaz.id<<endl;
	
	Doctor rediet , Evana;
	
    rediet.name= "rediet kifle";
    rediet.id=12;
    rediet.patient=chala;//Assign chalaas the patient for rediet.
    
    cout<<rediet.name<<endl;
    cout<<rediet.id<<endl;
    cout<<rediet.patient.name<<endl;
    return 0;
}

  //4.1 pointer and structure
  struct student{
    int id;
    string name;
  }Tselot;
  int main(){
    student hayat;
    hayat.id=24;
    student*ptr;
    ptr=&hayat;
    cout<<ptr ->id;
    return 0;
  }
  */
    
    
    

	
	
	