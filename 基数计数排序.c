#include <stdio.h>
#include <stdlib.h>
#define RADIX 10
typedef struct numbers{
    int data;
    struct numbers * nextPtr;
}LISTNUMBERS, * LISTNUMBERSPTR;
typedef struct node{
    LISTNUMBERSPTR numbersHeadPtr;
    LISTNUMBERSPTR numbersLastPtr;
    struct node * nextPtr;
}LISTNODE, * LISTNODEPTR;
void createListHead(LISTNUMBERSPTR *,LISTNUMBERSPTR *);
void insertSourceListEnd(LISTNUMBERSPTR *,int);
LISTNUMBERSPTR radixSort(LISTNODEPTR *,LISTNUMBERSPTR,LISTNUMBERSPTR * ,int);
void printList(LISTNUMBERSPTR);
int getMaxExponent(LISTNUMBERSPTR);
int getNumber(int,int);
int main(){
    LISTNODEPTR headPtr[RADIX],lastPtr[RADIX];
    LISTNUMBERSPTR sourceHeadPtr,sourceLastPtr;
    int i;
    for(i = 0;i < RADIX;i++){
        headPtr[i] = malloc(sizeof(LISTNODE));
        headPtr[i]->nextPtr = NULL;
        lastPtr[i] = headPtr[i];
        headPtr[i]->numbersHeadPtr = malloc(sizeof(LISTNUMBERS));
        headPtr[i]->numbersHeadPtr->nextPtr = NULL;
        headPtr[i]->numbersLastPtr = headPtr[i]->numbersHeadPtr;
    }
    createListHead(&sourceHeadPtr,&sourceLastPtr);
    printf("������ʮ���ƵķǸ�������-1������\n");
    int num;
    scanf("%d",&num);
    while(num != -1){
        insertSourceListEnd(&sourceLastPtr,num);
        scanf("%d",&num);
    }
    if(sourceHeadPtr->nextPtr != NULL){
        int max = getMaxExponent(sourceHeadPtr);
        sourceHeadPtr = radixSort(headPtr,sourceHeadPtr,&sourceLastPtr,max);
        printf("�����");
    }
    printList(sourceHeadPtr);
    return 0;
}
void createListHead(LISTNUMBERSPTR * headPtrPtr,LISTNUMBERSPTR * lastPtrPtr){
    (*headPtrPtr) = malloc(sizeof(LISTNUMBERS));
    if((*headPtrPtr) != NULL){
        (*headPtrPtr)->nextPtr = NULL;
        (*lastPtrPtr) = (*headPtrPtr);
    }
    else{
        printf("Error! -101");
    }
}
void insertSourceListEnd(LISTNUMBERSPTR * lastPtrPtr,int num){
    LISTNUMBERSPTR newPtr = malloc(sizeof(LISTNUMBERS));
    if(newPtr != NULL){
        newPtr->data = num;
        newPtr->nextPtr = NULL;
        (*lastPtrPtr)->nextPtr = newPtr;
        (*lastPtrPtr) = newPtr;
    }
    else{
        printf("Error! -102");
    }
}
int getMaxExponent(LISTNUMBERSPTR headPtr){
    headPtr = headPtr->nextPtr;
    int num = headPtr->data;
    int exp = 0;
    while(num > RADIX-1){
        num /= RADIX;
        exp++;
    }
    exp++;
    int max = exp;//�����һ������λ��
    while(headPtr->nextPtr != NULL){
        headPtr = headPtr->nextPtr;
        num = headPtr->data;
        exp = 0;
        while(num > RADIX-1){
        num /= RADIX;
        exp++;
        }
        if(headPtr != NULL){
            exp++;
            if(exp > max){
                max = exp;
            }
        }
    }//����ÿ����㲢�Ƚϴ�С
    return max;
}
LISTNUMBERSPTR radixSort(LISTNODEPTR * headPtr,LISTNUMBERSPTR srcHeadPtr,LISTNUMBERSPTR * srcLastPtrPtr,int max){
    int i,j,k;
    // printf("%d\n",max);
    for(i = 1;i <= max;i++){//����Ͱ�Ĵ���
        LISTNUMBERSPTR srcCurrentPtr = srcHeadPtr->nextPtr,srcPreviousPtr = srcHeadPtr;
        for(k = 0;k < RADIX;k++){
            headPtr[k]->numbersLastPtr = headPtr[k]->numbersHeadPtr;//����β���
        }
        while(srcCurrentPtr != NULL){
            int num = getNumber(srcCurrentPtr->data,i);//�õ���λ����
            // printf("%d ",num);
            // printf("%d\n",num);
            srcPreviousPtr->nextPtr = srcCurrentPtr->nextPtr;//�ƹ����ڵ�ָ��
            headPtr[num]->numbersLastPtr->nextPtr = srcCurrentPtr;//������ָ�Ľ�����Ͱ��
            srcCurrentPtr->nextPtr = NULL;
            srcCurrentPtr = srcPreviousPtr->nextPtr;//��ָ��ָ��ԭ����
            headPtr[num]->numbersLastPtr = headPtr[num]->numbersLastPtr->nextPtr;
        }//����Ͱ��
        (*srcLastPtrPtr) = srcPreviousPtr;
        if(headPtr[0]->numbersHeadPtr->nextPtr != NULL){
            (*srcLastPtrPtr)->nextPtr = headPtr[0]->numbersHeadPtr->nextPtr;
            (*srcLastPtrPtr) = headPtr[0]->numbersLastPtr;
            headPtr[0]->numbersHeadPtr->nextPtr = NULL;
        }
        for(j = 1;j < RADIX;j++){
            if(headPtr[j]->numbersHeadPtr->nextPtr != NULL){
                (*srcLastPtrPtr)->nextPtr = headPtr[j]->numbersHeadPtr->nextPtr;
                (*srcLastPtrPtr) = headPtr[j]->numbersLastPtr;
                headPtr[j]->numbersHeadPtr->nextPtr = NULL;
            }
            
        }//��Ͱ�е����������������ϲ���source�����У�ifѡ�����ǳ���Ҫ��û�и��������ͻ�ϣ�
    }
    // printList(srcHeadPtr);
    return srcHeadPtr;
}
int getNumber(int num,int exp){
    while(--exp){
        num /= RADIX;
    }
    return num % RADIX;
}
void printList(LISTNUMBERSPTR headPtr){
    headPtr = headPtr->nextPtr;
    while(headPtr != NULL){
        printf("%d ",headPtr->data);
        headPtr = headPtr->nextPtr;
    }
//    printf("%d\n",headPtr->source);
}
