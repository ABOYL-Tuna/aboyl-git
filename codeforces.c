#include<stdio.h>

int main() {
	int t;
	int a[100000];
	scanf("%d",&t);
	while(t--) {
		int n,i,j;
		int flag=1;
		scanf("%d",&n);
		for(i=0; i<n; i++)
			scanf("%d",&a[i]);
		int max=1,ma=1;
		for(i=0; i<n; i++) {
			int num=1,b=1;
			for(j=i+1; j<n; j++)
				if(a[i]==a[j]) {
					num++;
					b=j+1;
				}
			if(b>ma)ma=b;
			if(b==n) {
				printf("1 %d\n",n);
				flag=0;
				break;
			}
		}
		if(flag)printf("1 %d\n",ma);
	}

	return 0;
}
