#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<process.h>
#include<dos.h>

struct emp{
	char name[20],gender[10],id[5];
	int age;
	float salary;
}e;

FILE *fp;

long int size=sizeof(e);

void add();
void display();
void del();
void search();
void modify();

void main()
{
	int ch;
	while(1){
	 clrscr();
	 printf("\t\t\tEmployee Management System\n");
	 printf("1->Add Employee\n");
	 printf("2->Display all records\n");
	 printf("3->Delete record\n");
	 printf("4->Search\n");
	 printf("5->Modify\n");
	 printf("6->Exit\n");
	 scanf("%d",&ch);
	 switch(ch){
		case 1:
			add();
			break;
		case 2:
			display();
			break;
		case 3:
			del();
			break;
		case 4:
			search();
			break;
		case 5:
			modify();
			break;
		case 6:
			exit(0);
		default:
			printf("Invalid Choice\n");
			break;
	 }
	getch();
	}
}

void add()
{
	printf("Enter Employee ID: \n");
	scanf("%s",e.id);
	printf("Enter Employee Name: \n");
	fflush(stdin);
	gets(e.name);
	printf("Enter Age: \n");
	scanf("%d",&e.age);
	printf("Enter Salary: \n");
	scanf("%f",&e.salary);
	printf("Enter Gender: \n");
	scanf("%s",e.gender);
	fp=fopen("Employee.txt","ab");
	fwrite(&e,size,1,fp);
	printf("Record added successfully\n");
	fclose(fp);
	printf("Press any Key to continue...");
}

void display()
{
	clrscr();
	printf("%-5s %-30s %-10s %-15s %s\n\n","ID","Name","Age","Salary","Gender");
	fp=fopen("Employee.txt","rb");
	while(fread(&e,size,1,fp)==1){
	 printf("%-5s %-30s %-10d %-15.2f %s\n\n",e.id,e.name,e.age,e.salary,e.gender);
	}
	fclose(fp);
	printf("Press any Key to continue...\n");
}

void del()
{
	FILE *ft;
	char id[5];
	int flag=0;
	printf("Enter the ID: \n");
	scanf("%s",id);
	fp=fopen("Employee.txt","rb");
	ft=fopen("Temp.txt","wb");
	while(fread(&e,size,1,fp)==1){
	 if(strcmp(id,e.id)!=0){
	  fwrite(&e,size,1,ft);
	 }
	 else if(strcmp(id,e.id)==0){
	  flag=1;
	 }
	}
	fclose(fp);
	fclose(ft);
	if(flag==0){
	 printf("Record not found...\n");
	}
	else{
	 remove("Employee.txt");
	 rename("Temp.txt","Employee.txt");
	 printf("Record deleted successfully...\n");
	}
	printf("Press any Key to continue...\n");
}

void search()
{
	char name[20];
	int flag=0;
	printf("Enter the Name: \n");
	fflush(stdin);
	gets(name);
	clrscr();
	fp=fopen("Employee.txt","rb");
	printf("%-5s %-30s %-10s %-15s %s\n\n","ID","Name","Age","Salary","Gender");
	while(fread(&e,size,1,fp)==1){
	 if(strcmp(name,e.name)==0){
	  printf("%-5s %-30s %-10d %-15.2f %s\n\n",e.id,e.name,e.age,e.salary,e.gender);
	  flag=1;
	 }
	}
	fclose(fp);
	if(flag==0){
	 printf("Record not found...\n");
	}
	else{
	 printf("Record found successfully...\n");
	}
	printf("Press any Key to continue...\n");
}

void modify()
{
	char id[5];
	int flag=0;
	printf("Enter the ID: \n");
	scanf("%s",id);
	fp=fopen("Employee.txt","rb+");
	while(fread(&e,size,1,fp)==1){
	 if(strcmp(id,e.id)==0){
	  flag=1;
	 }
	}
	if(flag==0){
	 printf("Record not found...\n");
	}
	else{
	 fseek(fp,-size,1);
	 printf("Enter New ID: \n");
	 scanf("%s",e.id);
	 printf("Enter New Name: \n");
	 fflush(stdin);
	 gets(e.name);
	 printf("Enter New Age: \n");
	 scanf("%d",&e.age);
	 printf("Enter New Salary: \n");
	 scanf("%f",&e.salary);
	 printf("Enter New Gender: \n");
	 scanf("%s",e.gender);
	 fwrite(&e,size,1,fp);
	 printf("Record modified successfully...\n");
	}
	fclose(fp);
	printf("Press any Key to continue...\n");
}