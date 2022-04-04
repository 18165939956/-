#include<stdio.h>
#include<stdlib.h>

int partition(int *a, int begin, int end);//��������
void qsort(int a[], int begin, int end);//���򻮷ֺ�������е�Ԫ��(ʹ�õݹ鷽ʽ)
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
{//��������
    int pivot = a[end];//����һ��pivotָ�룬�ѱ�pivotС�Ļ���ǰ��ȥ
    int i = begin;
    for(int j = begin; j < end; j++)
    {
        //�ѱ�pivotС��ȫ������ǰ��ȥ
        if(a[j] < pivot){
            //��������ָ��i��j
            Swap(&a[j],&a[i++]);
        }
    }
    Swap(&a[end],&a[i]);
    
    //����pivot��i��ֵ
    return i;
}
void qsort(int a[], int begin, int end)
{//���򻮷ֺ�������е�Ԫ��(ʹ�õݹ鷽ʽ)
    if(begin < end)
    {
        int mid = partition(a,begin,end);
        qsort(a,begin,mid-1);//���Ƕ��������������
        qsort(a,mid+1,end);//���Ƕ��Ұ�����������
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