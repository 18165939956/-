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
//�����鲢�������
void merge_a(int a[],int n)
{
    //����һ������
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
//�鲢����
void msort(int a[], int temp[],int begin, int end)
{
    if (begin<end)//�ж��Ƿ�ֻ��һ��Ԫ��
    {   
        //���м��
        int mid = (begin + end)/2;
        //�ݹ黮�������
        msort(a,temp,begin,mid);
        //�ݹ黮���Ұ���
        msort(a,temp,mid+1,end);
        //�ϲ��Ѿ�����Ĳ���
        merge(a,temp,begin,mid,end);
    }
}
//�ϲ�
void merge(int a[], int temp[],int begin,int mid,int end)
{
    //����������һ��δ�����Ԫ��
    int b_pos = begin;
    //����Ұ�����һ��δ�����Ԫ��
    int e_pos = mid + 1;
    //��ʱ����Ԫ�ص��±�
    int pos = begin;

    //�ϲ�
    while(b_pos <= mid && e_pos <= end)//�ж��Ƿ���Ժϲ�
    {
        if(a[b_pos] < a[e_pos])//�жϴ�С����ֵ��temp
            temp[pos++] = a[b_pos++];
        else
            temp[pos++] = a[e_pos++];
    }
    //�ϲ������ʣ���Ԫ��
    while(b_pos <= mid)
    {
        temp[pos++] = a[b_pos++];
    }
    //�ϲ��Ұ���ʣ���Ԫ��
    while(e_pos <= end)
    {
        temp[pos++] = a[e_pos++];
    }
    //����ʱ�����кϲ����Ԫ�ظ��ƻ�ԭ��������
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