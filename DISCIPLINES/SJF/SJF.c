//
// Created by wassim on 25/11/17.
//
// 
//
// Created by wassim on 25/11/17.
/*
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
void main()
{
	char nom[50];
	char d_arriv[50];
	char c;
	float tex[50];
	int temp , i = 0;
	do {
		printf("doner le nom du processus");
		scanf("%s", &nom[i]);
		printf("date d'arriver");
		scanf("%s", &d_arriv[i]);
		printf("Temp d'execution");
		scanf("%f", &tex);
		printf("ajouter un processus ? O/N ");
		scanf("%c", &c);
		i++;
	} while (c != 'n'||'N');
	
	for(int x=0 ; x<i ; x++)
	{
	if (d_arriv[x] == d_arriv[x+1])
	{
	
	for (int j = 0; j<i; j++)
	{
		int pos = j;
		for (int k = j + 1; k<i; k++)
		{
			if (tex[k]<tex[pos])
				pos = k;
		}

		temp = tex[j];
		tex[j] = tex[pos];
		tex[pos] = temp;

		temp = p[j];
		p[j] = p[pos];
		p[pos] = temp;
	}

}
else ( fifo());
}
}

*/


