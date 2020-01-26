
#ifndef LIST
#define LIST

#include "node.h" 
 
struct List{
	surnameMap *head;
	int personcount;
	char *filename;
	FILE *phonebook;
	void createlist();
	surnameMap *create_node(char *, char *);
	void makeEmpty();
	void insertAll();
	void insertNewRecord(char *, char *);
	void deleteStudent(); 
	void deleteSurname();
	void updatelist();
	void updatename();
	void read_fromfile();
	void write_tofile();
};

#endif
