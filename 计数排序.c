#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void counting_sort(int arr[], int len)
{
    if (len < 1) return;

    // Ѱ������Ԫ��
    int max = arr[0];
    for (size_t i = 1; i < len; i++)
        if (arr[i] > max) max = arr[i];

    // ����һ������Ϊmax+1������洢����������ʼ��Ϊ0
    int *count = (int *)malloc(sizeof(int) * (max + 1));
    memset(count, 0, sizeof(int) * (max + 1));

    // ����
    for (size_t i = 0; i < len; i++)
        count[arr[i]]++;

    // ͳ�Ƽ������ۼ�ֵ
    for (size_t i = 1; i < max + 1; i++)
        count[i] += count[i - 1];

    // ����һ����ʱ���鱣����
    int *output = (int *)malloc(sizeof(int) * len);

    // ��Ԫ�طŵ���ȷ��λ����
    for (size_t i = 0; i < len; i++)
    {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    // ��������ƻ�ԭ����
    for (size_t i = 0; i < len; i++)
        arr[i] = output[i];
}
void print_arr(int *a,int n )
{
    for(int i=0;i<n;i++)
    {
        printf("%d\n",a[i]);
    }
    putchar('\n');
}

int main(int argc, char const *argv[])
{
    int arr[] = {2, 4, 1, 2, 5, 3, 4, 8, 7};
    print_arr(arr, 9);
    counting_sort(arr, 9);
    print_arr(arr, 9);
    return 0;
}