
#define nameLength 10
#define surnameLenth 10
struct studentInfo{
		char surname1[surnameLenth];
		char name[nameLength];
		studentInfo *next;
		studentInfo *previous;
	
};
struct surnameMap{
	char surname[surnameLenth];
	surnameMap *next;
	studentInfo *first;
	studentInfo *tail;
	
};


