
#include <iostream> 
#include<string.h>
#include <stdlib.h> 
#include <iomanip> 
#include "list.h" 

using namespace std;
typedef surnameMap surnameM;
typedef List list;
list deneme;

void print_menu();  
void add_record();
void update_record();

int main(){
	int choice;
	while(1){
		print_menu();
		cin>>choice;
		switch(choice){
			case 1:
				deneme.createlist();
				break;
			case 2:
				deneme.insertAll();
				break;
			case 3:
				add_record();
				break;
			case 4:
				deneme.deleteStudent();
				break;
			case 5:
				deneme.deleteSurname();
				break;
			case 6:
				update_record();
				
				break;
			case 7:
				deneme.write_tofile();
				break;
				
			default:
				cout<<"Wrong input.Try again please"<<endl;
				break;
		}
	}
	deneme.makeEmpty();
	return 0;
}





void print_menu(){
    cout << endl << endl << "e-mail Address Program" << endl;
    cout << "1)Create" << endl;
    cout << "2)Insert All" << endl;
    cout << "3)Insert New Record" << endl;
    cout << "4)Delete Student" << endl;
    cout << "5)Delete Surname Node" << endl;
    cout << "6)Update" << endl;
    cout << "7)Write to File" << endl;
         
    cout << endl << "Enter a choice: ";
}

void add_record()
{
	char newname[nameLength], surname[surnameLenth];
	cout << "Please enter contact information you want to add" << endl;
	cout << "Surname : " ;	
	cin.ignore(1000, '\n'); 
	cin.getline(surname, surnameLenth); 
	
	cout << "Name : " ;	
	cin >> setw(nameLength) >> newname;
	cin.ignore(1000, '\n'); 
	deneme.insertNewRecord(newname,surname);
	cout << "Record added" << endl;
	getchar();
};



void update_record(){
	char input[10];
	cout<<endl<<"What do you want to update (Name/Surname)";
	cin>>input;
	if(strcmp(input,"Name"))
	deneme.updatelist();
	else if (strcmp(input,"Surame"))
	deneme.updatename();
	else{

	cout<<"wrong input";
	return;
		}
	
	getchar();
}
