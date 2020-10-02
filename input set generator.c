#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
//this file has been edited by parth langalia. 
//purpose is to earn free t shirt.
int main()
{
	int p,i,a,b,c;
	FILE *fptr;
	fptr=fopen("input.txt","w");
	for(i=1;i<51;i++)
	{
		fprintf(fptr,"%d",i);
		fputs("\nProcess--Arrival--Brust\n",fptr);
		for(p=1;p<=5;p++)
		{
			a=rand()%10+1;
			b=rand()%10+1;
			c=rand()%10+1;
			fprintf(fptr,"%d\t",a);
			fprintf(fptr,"%d\t",b);
			fprintf(fptr,"%d\n",c);
		}
	}
	fclose(fptr);
	return 0;
}
