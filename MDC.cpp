#include <cmath>
#include<iostream>
#include <type_traits>
#include"MDC.h"

long mod(long a, long b) {return (((a%b)+b)%b);}

bool isPrime(int p){
	int n= std::sqrt(p);
	for(int i=2; i<n; i++){
		if(p%i==0){
			return false;
		}
	}
	return true;
}

long mcd(long a, long b){
	while (b>0) {
		long r= mod(a,b);
		a=b;
		b=r;
	}
	return a;
}

int mcdr(int a, int b) {
	std::cout<<"mcd("<<a<<","<<b<<") =";
	if (b==0) {
		return a;
	}else{
		int r= mod(a,b);
		return mcdr(b,r);
	}
}

void  bezoutIdentity(long arr[], long a, long b) {
	long s1=1;
	long t1=0;
	long s=0;
	long t=1;

	while (b>0) {
		long r= mod(a,b);
		long q= a/b;

		a=b;
		b=r;

		long sAux = s1;
		s1= s;
		s= sAux- q*s;

		long tAux = t1;
		t1=t;
		t= tAux- q*t;
	}
	arr[0]= a;
	arr[1]= s1;
	arr[2]= t1;
}

long inverseMod(long a, long n){
	long arr[3];
	bezoutIdentity(arr, a, n);
	long b= arr[1];
	return mod(b,n);
}

using namespace std;

/*int main(){
	
	cout<<"bienvenido al programa"<<endl;
	while (true){

		int a;
		int b;
		int m;
		long arr[3];
		int choice;

		cout<<"opciones: "<<endl;	
		cout<<"  1. calculadora mcd"<<endl;
		cout<<"  2. calculadora recursiva de mcd"<<endl;
		cout<<"  3. identidad de bezout"<<endl;
		cout<<"  4. inverso modular"<<endl;
		cout<<"  0. salir"<<endl;
		cin>>choice;

		switch (choice) {
			case 0:
				return 0;
				break;

			case 1: 
				cout<<"primer numero"<<endl;
				cin>>a;
				cout<<"segundo numero"<<endl;
				cin>>b;
				m= mcd(a,b);
				cout<<m<<endl;
				break;

			case 2:
				cout<<"primer numero"<<endl;
				cin>>a;
				cout<<"segundo numero"<<endl;
				cin>>b;
				m= mcdr(a,b);
				cout<<m<<endl;
				break;

			case 3:
				cout<<"primer numero"<<endl;
				cin>>a;
				cout<<"segundo numero"<<endl;
				cin>>b;
				bezoutIdentity(arr, a, b);
				cout<<arr[0]<<"="<<arr[1]<<"*"<<a<<"+"<<arr[2]<<"*"<<b<<endl;
				break;

			case 4:
				cout<<"inserte numero a"<<endl;
				cin>>a;
				cout<<"inserte valor n"<<endl;
				cin>>b;
				m= inverseMod(a,b);
				cout<<"el inverso de "<<a<<" modulo "<<b<<" es "<<m<<endl;
				cout<<a<<"*"<<m<<"="<< a*m<<"mod "<<b<<"="<<mcd(a,b)<<endl;
				break;

			default:
				return 0;
		}
	}
	return 0;
}*/
