#include <stdio.h>
#include <stdlib.h>

void merge(int a[], int temp[],int begin,int mid,int end);
void msort(int a[], int temp[],int begin, int end);
void merge_a(int a[],int n);
void printf_a(int a[],int n );

void printf_a(int a[],int n ){
    for(int i=0;i<n;i++)
    {
        printf("%d\n",a[i]);
    }
    putchar('\n');
}
//创建归并排序入口
void merge_a(int a[],int n)
{
    //分配一个数组
    int* temp = (int*)malloc(n *sizeof(int));
    if(temp)
    {
        msort(a,temp,0,n-1);
        free(temp);
    }
    else
    {
        printf("error!");
    }
}
//归并排序
void msort(int a[], int temp[],int begin, int end)
{
    if (begin<end)//判断是否只有一个元素
    {   
        //找中间点
        int mid = (begin + end)/2;
        //递归划分左半区
        msort(a,temp,begin,mid);
        //递归划分右半区
        msort(a,temp,mid+1,end);
        //合并已经排序的部分
        merge(a,temp,begin,mid,end);
    }
}
//合并
void merge(int a[], int temp[],int begin,int mid,int end)
{
    //标记左半区第一个未排序的元素
    int b_pos = begin;
    //标记右半区第一个未排序的元素
    int e_pos = mid + 1;
    //临时数组元素的下标
    int pos = begin;

    //合并
    while(b_pos <= mid && e_pos <= end)//判断是否可以合并
    {
        if(a[b_pos] < a[e_pos])//判断大小并赋值给temp
            temp[pos++] = a[b_pos++];
        else
            temp[pos++] = a[e_pos++];
    }
    //合并左半区剩余的元素
    while(b_pos <= mid)
    {
        temp[pos++] = a[b_pos++];
    }
    //合并右半区剩余的元素
    while(e_pos <= end)
    {
        temp[pos++] = a[e_pos++];
    }
    //把临时数组中合并后的元素复制回原来的数组
    while (begin <= end)
    {
        a[begin] = temp[begin];
        begin++;
    }
}

int main(int argc,char const *argv[])
{
    int a[]={4,4,5,7,12,6,3,1,11};
    int n=9;
    printf_a(a,n);
    merge_a(a,n);
    printf_a(a,n);
    return 0;
}