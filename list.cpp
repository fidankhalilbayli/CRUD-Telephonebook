#include <iostream> 
#include <string.h> 
#include<stdlib.h>
#include<stdio.h>
#include "list.h"

using namespace std; 

/*creating the list*/
void List :: createlist(){
	head =NULL;
}

/*inserting everything from the text file into the struct  */
void List :: insertAll(){
	struct File_Record{
		char surname[10];	
		char name[10];

	};

	File_Record record;

	if ( !(phonebook = fopen("dataset_wOutTurkishChars.txt", "r") ) ) { 
		if ( !(phonebook = fopen("deneme.txt", "w+") ) ) { 
			cerr << "File could not be opened." << endl; 
			cerr << "Will work in memory only." << endl;
			return;		
		}
	}
	
	char x[10];
	char y[10];
	fseek(phonebook,0,SEEK_SET);
	while(!feof(phonebook)){
		fscanf(phonebook,"%s	%s",x,y);
		strcpy(record.name,x);
		strcpy(record.surname,y);
		if(feof(phonebook))
			break;	
		insertNewRecord(record.name,record.surname );
	}	
	fclose(phonebook);
}


surnameMap * List::create_node( char *name2,char *surname2){
	surnameMap *newperson;
	studentInfo *newnum;	
	newperson = new surnameMap;
	strcpy(newperson->surname, surname2);
	newnum = new studentInfo;	
	newperson->first = newnum;	
	strcpy(newnum->name, name2);
	newnum->next = NULL;
	newperson->next = NULL;
	return newperson;
}


void List::insertNewRecord(char *newname, char *newsurname)
{
	surnameMap *traverse, *behind, *newperson;
	studentInfo *newn;
	traverse = head;
	if (head == NULL) { /*if head is empty enter the new node here*/
		head = create_node(newname,newsurname);
		return;
	}

	if ( strcmp(newsurname, head->surname) < 0 ) { /*if new node is supposed t be added in front of the head*/
		newperson = create_node(newname,newsurname);
		newperson->next = head;
		head = newperson;
		newperson++;
		return;
	}

	while ( traverse && (strcmp(newsurname, traverse->surname) > 0) ) { /*if the new node comes after the traverse surname*/
		behind = traverse;
		traverse = traverse->next;
	}
	
	if (traverse && strcmp(newsurname, traverse->surname) == 0){ /*if this node was added previously*/
		newn = new studentInfo;
		newn->next = traverse->first;	
		traverse->first = newn;
		(newn->next)->previous=newn;
		strcpy(newn->name , newname);		
	}
	
	else {
		newperson = create_node(newname,newsurname);
		if (traverse) { /*add the newnode between*/
			newperson->next = traverse;
			behind->next = newperson;
		}
		else /*add the new node to the end*/
			behind->next = newperson;
	}
}

/*delete surname function delete the surname and all of the corresponding names of it*/
void List::deleteSurname(){
	char surname[10];	
	surnameMap * traverse=head;
	surnameMap* behind;
	studentInfo * p;
	
	cout<<endl<<"Enter the surname of the students you want to delete";
	cin>>surname;
	
	while (traverse) {/*go through every node until the surname matches with a node*/
        
        if (strcmp(surname,traverse->surname)==0){
            break;
        }
        behind=traverse;
        traverse = traverse->next;
    }
    
	if (traverse == NULL) {
        cout << endl << "Could not be found.";
        return;
	}	
	
	else {       /*if the surname match with a node in the list do the following*/ 
    	p = traverse->first;
        while (p) {/*delete the names according to the surname*/
			traverse->first = p->next;
			delete p;
			p = traverse->first;
		}
        
        if (traverse == head) {/*if the user wants to delete the first node*/
            head = traverse->next;
            delete traverse;
            return;        
        }
		else{   /*if the user wants to delete any node other than the first*/    
        behind->next= traverse->next;
        delete traverse;	
		return;
		}
    }
}
    
    
void List::deleteStudent(){
	char surname[10];
	char index[10];
	surnameMap * traverse=head;
	surnameMap * behind;
	studentInfo * p;
	studentInfo * tail;
	studentInfo * traverse1= new studentInfo ;
	traverse1->next=NULL;
	traverse1->previous=NULL;
	
	/*in order to delete a student first the surname of the student is asked if the surname exists the name is deleted*/
	cout<<endl<<"Enter the surname of the student you want to delete the name of";
	cin>>surname;
	
	while (traverse) {     
        if (strcmp(surname,traverse->surname)==0){
            break;
        }
        behind=traverse;
        traverse = traverse->next;
    }
    
	if (traverse == NULL) {
        cout << endl << "Could not be found.";
        return;
	}	
	else { 
		int i=0;
		traverse1=traverse->first;
		while (traverse1) {
            cout << endl <<i<< "    " << traverse1->name;
            i++;
            traverse1=traverse1->next;
        }
		traverse1=traverse->first;
        /*which name to delete is asked from the user*/
 		cout << endl << "Enter the name: ";
        cin >> index;
		while (traverse1) {       
       	if (strcmp(index,traverse1->name)==0){
           	break;}     	
       	tail=traverse1;
       	traverse1 = traverse1->next;
   	}
   	
		p=traverse1;	
		if(p== traverse->first){/*if the first name of the surname is wanted to be deleted do the following*/
			traverse->first= p->next;
			delete p;
			if(traverse->first==NULL){/*if all names related to a surname is deleted the surname is also deleted*/
				if (traverse == head) {/*if the surname is the first node*/
            		head = traverse->next;
           			delete traverse;
            		return;
       			}
				else{       /*if the surname is any node other than the first*/
      				behind->next= traverse->next;
        			delete traverse;	
					return;
				}			
			}
		    return;
		}
	
	else{	//record found
		(p->previous)->next = p->next;
		if(p->next){
		(p->next)->previous=p->previous;
		delete p;
		if(traverse->first==NULL){/*if all names related to a surname is deleted the surname is also deleted*/
			if (traverse == head) {/*if the surname is the first node*/
            	head = traverse->next;
           		delete traverse;
           		return;
       		}
			else{       /*if the surname is any node other than the first*/
				behind->next= traverse->next;
        		delete traverse;	
				return;
			}
			
			}
		}
		else{
			tail =p->previous;
			delete p;
			if(traverse->first==NULL){/*if all names related to a surname is deleted the surname is also deleted*/
				if (traverse == head) {/*if the surname is the first node*/
            		head = traverse->next;
           			delete traverse;
            		return;
       			}
				else{       /*if the surname is any node other than the first*/
      				behind->next= traverse->next;
        			delete traverse;	
					return;
				}
			
			}
		}
	}
}
}


/*update list updates the surname*/
void List::updatelist(){
	surnameMap * traverse=head;
	surnameMap * behind;	
	surnameMap * added= new surnameMap;
	studentInfo * p= new studentInfo;
	studentInfo * tail;
	studentInfo * traverse1;
	
	added->next=NULL;
	added->first=NULL;
	p->next=NULL;
	
	char surname[10];
	char surname_new[10];
	
	/*at first the surname that is wanted to be updated is entered by the user then the code looks for a match between the input and the surname nodes*/
	cout<<endl<<"Enter the surname you want to update: ";
	cin>>surname;
	
	while (traverse) {       
       	if (strcmp(surname,traverse->surname)==0){
           	break;}     	
       	behind=traverse;
       	traverse = traverse->next;
   	}
   	
	if (traverse == NULL) {
        cout << endl << "Could not be found.";
        return;
	}	
	
	else {/*if a match is found do the following*/
		cout<<"Enter the new surname you want to update: ";
		cin>>surname_new;
		strcpy(added->surname,surname_new);
	    /*first delete the surname node*/
	    p = traverse->first;
 
        if (traverse == head) {
            head = head->next;
            delete traverse;                  
        }
        else{      
       		behind->next= traverse->next;
        	delete traverse;			
		}	
	/*link the new node surname with the names of the deleted surname*/
	p=traverse->first;
	added->first=p;
	traverse=head;
	behind=head;
        /*then add the new surname node and add it according to its alphabetical order*/
	    if (strcmp(added->surname,head->surname) < 0) {/*add before the head*/
            added->next = head;
            head =added;
            return;
        }        
        while (traverse && (strcmp(added->surname,traverse->surname) > 0)) {/*look for the place to add between */
            behind = traverse;
            traverse = traverse->next;
        }        
        if (traverse){/*add in between*/
			added->next = traverse;  
            behind->next =added;        
        } 
		else {/*add to the end*/
			  behind->next = added;
		}   
	}  
}
/*update the name in the circular list*/
void List::updatename(){
    surnameMap * traverse=head;
	surnameMap * behind;
	studentInfo * p= new studentInfo;
	studentInfo * tail;
	studentInfo * traverse1;
	
	char surname[10];
	int index;
	/*at first the surname of the name is entered by the user and a match is looked for between the list surnames and the input*/
	cout<<"Enter the surname of the name you want to update";
  	cin>>surname;
  	
	while (traverse) {       
      	if (strcmp(surname,traverse->surname)==0){
       		break;}       	
      	behind=traverse;
   		traverse = traverse->next;
   	}
	if (traverse == NULL) {
        cout << endl << "Could not be found.";
        return;
	}	
	else {/*if the match is found all the names related to the surname are printed and the name to be updated is asked from the user*/
	int i=1;
	p=traverse->first;
	while (p) {
        cout << endl <<i<< "    " << p->name;
        i++;
        p=p->next;
    }
    p=traverse->first;
    cout<<endl<<"Enter the index you want to update";
  	cin>>index;	
  	/*then the name is found in the list and updated*/
  	for (int a = 1; a < index; a++) {
            p->previous= p;              
            p = p->next;       
    }
    
    cout << endl << "Enter the new name of the student: ";
    cin >> p->name;
    }
}
		
/*empties the list*/		
void List::makeEmpty()
{
	surnameMap *p;
	studentInfo *q;
	while (head) {
		p = head;
		head = head->next;
		q = p->first;
		while (q){
			p->first = p->first->next;
			delete q;
			q = p->first;
		}
		delete p;
	}	
}


void List::write_tofile()
{ 

     surnameMap * traverse = head;
    studentInfo * p;
	
	char c= '\n';


	if ( !(phonebook = fopen( "emailList.txt", "w" ) ) ) { 
			cerr << "File could not be opened" << endl; 
			return;	
	}

    
    while (traverse) {
        fprintf(phonebook,"%s ",traverse->surname);      
        p = traverse->first;
        while (p) {
            fprintf(phonebook,"%s ",p->name);
            p=p->next;          
        }
     fprintf(phonebook,"%c ",c);
        
        traverse = traverse->next;
    }
    fclose(phonebook);
}
