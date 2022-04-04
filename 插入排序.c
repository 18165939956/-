#include<stdio.h>
#include<stdlib.h>

void printf_a(int a[],int n );


void printf_a(int a[],int n ){
    for(int i=0;i<n;i++)
    {
        printf("%d\n",a[i]);
    }
    putchar('\n');
}

int main(int argc,char const *argv[])
{
    int a[]={4,4,5,7,12,6,3,1,11};
    int n=9;
    printf_a(a,n);
    int i,j,insert;
    for(i = 1; i < n; i++)
    {
        insert = a[i];//往后挪动比insert小的值
        for(j=i;j>=1&&insert<a[j-1];j--)
            a[j]=a[j-1];
            //把insert放到正确的位置
            a[j]=insert;
    }
    printf_a(a,n);
    return 0;
}