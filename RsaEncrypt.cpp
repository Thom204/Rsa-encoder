#include <cmath>
#include <cstdio>
#include<iostream>
#include<bits/stdc++.h>
#include <limits>
#include <ostream>
#include <sstream>
#include <string>
#include <fstream>
#include"RsaEncrypt.h"
#include"MDC.h"

long mpow(long x, int p, int z){
	int rslt= 1;
	x= mod(x, z);
	if(x==0){return 0;}

	while(p>0){
		if(p%2==1){
			rslt= mod((rslt*x),z);
		}
		int auxp= p/2;
		p= auxp;
		x= mod((x*x),z);
	}
	return rslt;
}

long StrToIntFormat(const std::string& s){

	std::string new_str = "";
	char ch;
	int len =s.length();
	int asciich;
	long result;

	for(int i=0; i<len; ++i){
		ch = s[i];
		asciich= (ch-' ')+1;	
		//std::cout<<ch<<" : "<<asciich<<std::endl;
		new_str += (asciich<10)? ("0"+ std::to_string(asciich)): (std::to_string(asciich));

	}
	//std::cout<<new_str<<std::endl;
	std::istringstream (new_str) >>result;
	return result;
}

std::string IntToStrFromat(const std::string& s){
	std::string resStr= "";
	std::string aux;
	int len= s.length();
	int asciiN;
	char ch;

	for(int i=0; i<len; i+=2){
		if(len%2==1 && i==0){
			aux= s[i];
			i -=1;
		}else{
			aux= s.substr(i, 2);
		}
		std::istringstream ( aux )>> asciiN;
		ch = (' '+asciiN)-1;
		//std::cout<<aux<<" : "<<asciiN<<" : "<<ch<<std::endl;
		resStr +=ch;
	}
	return resStr; 
}

using namespace std;

int main() {
	ifstream keyfile("keys.txt");
	int z,n,phi,s,p,q;
	bool mode = false;
	string lineContent="";
	string group;
	long encodedLine;
	string decodedLine;
	ifstream inputFile;
	ofstream outputFile;

	int choice;
	char confirmation;

	for(int i=0; i<2; i++){
		getline(keyfile, lineContent);
		if(i==0){
			istringstream( lineContent )>>z;
		}else{
			istringstream( lineContent )>>n;
		}
	}
	keyfile.close();

	cout<<"welcome to the program"<<endl;

	while(true){
		
		cout<<endl<<"current mode "<<(mode?"encrypt":"test");
		cout<<endl<<"current keys: "<<n<<" "<<z<<endl<<"select an option: "<<endl<<
			"  1. ecrypt text file"<<endl<<"  2. decrypt text file"<<endl<<"  3. set public keys using private key insertion"<<
			endl<<"  4. set public keys by direct insertion"<<endl<<"  5. switch encryption mode"<<endl<<"  0. exit program"<<endl;
		cin>>choice;

		switch (choice) {
			
			case 0:
				return 0;

			case 1:	
				cout<<endl<<"!!warning!!"<<endl<<"make sure the text to encrypt is already stored in crypt/input.txt"<<endl;
				cout<<"do you want to proceed? y|n ";
				cin>>confirmation;
				if (confirmation=='n'){return 0;}

				inputFile.open("crypt/input.txt");
				outputFile.open("crypt/encrypted.txt");
				
				if(inputFile.is_open() && outputFile.is_open()){

					cout<<endl<<"reading file"<<endl;
					cout<<"parsing"<<endl;
					cout<<"encrypting file with keys: "<<n<<" "<<z<<endl;

					while (getline(inputFile, lineContent)){
					
						int len= lineContent.length();

						for (int i=0; i<len; i+=2){

							if(len-i <= 2){
								group = lineContent.substr(i, len-i);
							}else{
								group = lineContent.substr(i, 2);
							}
							encodedLine= StrToIntFormat(group);
							//cout<<encodedLine<<" : "<<mpow(encodedLine,n ,z)<<endl;
							outputFile << mpow(StrToIntFormat(group), n, z)<<" ";
						}
							outputFile<<"\n";
							cout<<"."<<endl;
					}
					cout<<"file succesfully encrypted"<<endl<<endl;
					inputFile.close();
					outputFile.close();							
					if(mode){
						remove("crypt/input.txt");
					}

				}else{
					cout<<"opening error"<<endl;
					cout<<"files may already been encrypted"<<endl;
					return 1;
				}
				break;

			case 2:
				inputFile.open("crypt/encrypted.txt");
				outputFile.open("crypt/decrypted.txt");

				if(inputFile.is_open() && outputFile.is_open()) {
					cout<<"reading file"<<endl;
					cout<<"insert private key (p or q) to start decryption: ";
					cin>>p;
					q= z/p;
					if(p*q!=z){
						cout<<"incorrect key"; 
						break;
					}
					phi=(p-1)*(q-1);
					s=inverseMod(n, phi);

					if(mod(n*s, phi)!=1){
						cout<<"s key error";
						return 1;
					}
					cout<<"decrypting file "<<endl;

					while(getline(inputFile, lineContent)){

						stringstream ss(lineContent);
						while(getline(ss, group, ' ')){
							istringstream(group)>> encodedLine;
							decodedLine= to_string(mpow(encodedLine, s, z));
							//cout<<encodedLine<<" : "<<decodedLine<<endl;
							outputFile<<IntToStrFromat(decodedLine);
						}
						outputFile<<"\n";
						cout<<"."<<endl;
					}
					cout<<"file succesfully decrypted"<<endl;
					inputFile.close();
					outputFile.close();
					if(mode){
						remove("crypt/encrypted.txt");
					}
					rename("crypt/decrypted.txt", "crypt/input.txt");
					break;
				}else{
					cout<<"opening error"<<endl;
					cout<<"there may not be any encrypted files"<<endl;
					return 1;
				}
				break;
			
			case 3:
				outputFile.open("tmp.txt");
				remove("keys.txt");

				cout<<"insert prime p: "<<endl;
				cin>>p;
				cout<<"insert prime q: "<<endl;
				cin>>q;
				if (isPrime(p) && isPrime(q)){
					z=p*q;
				}else{
					cout<<"p and q must be prime numbers"<<endl; 
					break;
				}
				if(z>= numeric_limits<int>::max()){
					cout<<"module too large, try smaller p, q values"<<endl;
					break;
				}else if(z<= 9595){
					cout<<"module too short try larger p, q values"<<endl;
					break;
				}
				cout<<"insert number n: "<<endl;
				cin>>n;						

				phi= (p-1)*(q-1);
				if(mcd(n,phi)==1){
					outputFile<<z<<"\n"<<n;
					outputFile.close();
					rename("tmp.txt","keys.txt");
					remove("tmp.txt");
					cout<<"succesfully set keys: "<<n<<" "<<z<<endl;
					break;

				}else{
					cout<<"invalid value for n"<<endl<<"try using a prime value instead"<<endl;
					break;
				}
				break;

			case 4:
				outputFile.open("tmp.txt");
				remove("keys.txt");

				cout<<"insert public key z (modulo key)"<<endl;
				cin>>z;
				if(z>= numeric_limits<int>::max()){
					cout<<"module too large, try a samller value for z";
					break;
				}else if(z<= 9595){
					cout<<"module too short try a value larger than 9595";
					break;
				}
				cout<<"insert public key n (power key) for this mode n has to be prime"<<endl;
				cin>>n;
				if(!isPrime(n)){
					cout<<"for this mode of insertion n has to be prime";
					break;
				}
				outputFile<<z<<"\n"<<n;
				outputFile.close();
				rename("tmp.txt","keys.txt");
				remove("tmp.txt");
				cout<<"succesfully set keys: "<<n<<" "<<z<<endl;
				break;

			case 5:
				cout<<endl<<"modes: "<<endl<<"  -test: leaves the input file unaltered and generates a encrypted copy"<<
				endl<<"  -crypt: deletes input file after encryption so encrypted information can only be accessed via decrypting"<<endl;
				cout<<endl<<"current mode: "<<(mode?"encrypt":"test");
				cout<<" do you want to shwitch? y|n"<<endl;
				cin>>confirmation;
				if(confirmation == 'n'){break;}
				mode= !mode;
				break;

			default:
				return 0;

		}
	}

	cout<<"files closed"<<endl<<"thanks for using";
	
	return 0;
}
