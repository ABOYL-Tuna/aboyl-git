#include<stdio.h>
int main() {
	char s[100];
	char t[100];
	scanf("%s%s",s,t);
	int j=0,tem=0;
	while(s[j]!='\0') {
		if(t[0]==s[j]) {
			int i=0;
			tem=1;
			while(t[i+1]!='\0') {
				i++;
				j++;
				if(t[i]!=s[j]) {
					printf("No");
					return 0;
				}

			}
		}
		j++;
		if(tem) {
			printf("Yes");
			return 0;
		}
	}
	printf("No");
	return 0;
}
