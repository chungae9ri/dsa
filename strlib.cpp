#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int strlen(char* p)
{
	int cnt=0;

	while(*p++ != '\0') {
		cnt++;
	}
	return cnt;
}

int strcmp(char* p, char* q)
{
	int ret=0;
	while(*p++ == *q++) {
		/*do nothing*/
	}
	if(*p=='\0' && *q=='\0') return 0;
	else return 1;
}

char* strcat(char* p, char* q) 
{
	char* tmp;
	char* r = (char*)malloc(strlen(p)+strlen(q));
	tmp=r;
	while(*p != '\0') {
		*tmp = *p;
		p++,tmp++;
	}
	while(*q != '\0') {
		*tmp=*q;
		q++, tmp++;
	}
	*tmp = '\0';
	return r;
}

char* strchr(char* p, int c)
{
	while(*p != '\0') {
		if (*p == c)
			return p;
		p++;
	}
	return NULL;
}

int main()
{
	char a[128], b[128];
	char *cat, *chr;
	int cnt;
	scanf("%s", a);
	cnt = strlen(a);
	cout << "strlen(a) : " << cnt << endl;
	scanf("%s", b);
	cnt = strcmp(a, b);
	cout << "strcmp(a,b) : " << cnt << endl;
	cat = strcat(a,b);
	cout << "strcat(a,b) : " << cat << endl;
	chr = strchr(cat, 'c');
	if(chr != NULL)
		cout << "strchr(a, 'c') :" << *chr << endl;
	free(cat);
	return 0;
}
