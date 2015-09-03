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

int atoi(char *str)
{
	int i;
	int ret = 0;
	int bneg = 0; 

	i=0;
	if(str[i] == '-') {
		bneg = 1;
		i++;
	}
	while(str[i] != '\0') {
		ret = ret * 10 + str[i]-'0';
		i++;
	}
	if(bneg) ret *= -1;
	return ret;
}

void itoa(int num, char *buf, int base)
{
	int rem, i=0, j, temp, minus = 0;

	if(num == 0) {
		buf[0] = '0';
		buf[1] = '\0';
		return;
	}

	if(num < 0) {
		minus = 1;
		num *= -1;
	}

	while(num > 0) {
		rem = num % base;
		buf[i++] = (rem>9) ? rem-10+'a' : rem + '0';
		num = (int)(num/base);
	}

	for(j=0 ; j<i/2 ; j++) {
		temp = buf[i-j-1];
		buf[i-j-1] = buf[j];
		buf[j] = temp;
	}

	buf[i] = '\0';
	if(minus) {
		for(j=i ; j>=0 ; j--) {
			buf[j+1] = buf[j];
		}
		buf[0] = '-';
	}
}

int main()
{
	char a[128], b[128], c[16], d[16];
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

	sprintf(d, "%d", -12345);
	cout << "atoi(-12345) : " << atoi(d) << endl;

	itoa(-12345, c, 10);
	cout << "itoa(-12345) : " << c << endl;
	itoa(12345, c, 2);
	cout << "itoa(12345, base 2) : " << c << endl;
	itoa(12345, c, 16);
	cout << "itoa(12345, base 16) : " << c << endl;

	return 0;
}
