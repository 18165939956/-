#include<stdio.h>
#include<stdlib.h>

int partition(int *a, int begin, int end);//划分区块
void qsort(int a[], int begin, int end);//排序划分后各区块中的元素(使用递归方式)
void printf_a(int a[],int n );
void Swap(int *p1,int *p2);


void Swap(int *p1,int *p2)
{
    int tmp;
    tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}
int partition(int *a, int begin, int end)
{//划分区块
    int pivot = a[end];//定义一个pivot指针，把比pivot小的换到前面去
    int i = begin;
    for(int j = begin; j < end; j++)
    {
        //把比pivot小的全部换到前面去
        if(a[j] < pivot){
            //交换两个指针i和j
            Swap(&a[j],&a[i++]);
        }
    }
    Swap(&a[end],&a[i]);
    
    //交换pivot和i的值
    return i;
}
void qsort(int a[], int begin, int end)
{//排序划分后各区块中的元素(使用递归方式)
    if(begin < end)
    {
        int mid = partition(a,begin,end);
        qsort(a,begin,mid-1);//这是对左半区进行排序
        qsort(a,mid+1,end);//这是对右半区进行排序
    }
}
void quick_sort(int a[],int n)
{
    qsort(a,0,n-1);
}

void printf_a(int *a,int n )
{
    for(int i=0;i<n;i++)
    {
        printf("%d\n",a[i]);
    }
    putchar('\n');
}

int main()
{
    int a[]={9,5,2,7,12,4,3,1,11};
    int n=9;
    quick_sort(a,n);
    printf_a(a,n);
    return 0;
}