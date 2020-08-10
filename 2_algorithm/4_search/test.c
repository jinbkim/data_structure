#include<stdio.h>
#include<stdlib.h>
#include<time.h> 


static int move = 0;
void hanoi(int n, char a, char b, char c){
	if(n==1){
		move++;
		//printf("%d %d\n",a,c);
	}else{
		hanoi(n-1,a,c,b);
		move++;
		//printf("%d %d\n",a,c);
		hanoi(n-1,b,a,c);
	}
	
}

int sqr(int k){
	if(k==1)
		return 2;
	else
		return sqr(k-1)*2;
}

int main(){
	int N;
	clock_t finish, start;
	double duration;
	
	char a = 1, b = 2, c = 3;
	scanf("%d",&N);
	printf("%d\n",sqr(N)-1);
	start = clock();
	hanoi(N,a,b,c);
	finish = clock();
	duration = (double)(finish-start)/CLOCKS_PER_SEC;
	printf("걸린 시간 : %lf",duration);
	return 0;
}