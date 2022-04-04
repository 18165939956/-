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
    printf("请输入十进制的非负数，以-1结束：\n");
    int num;
    scanf("%d",&num);
    while(num != -1){
        insertSourceListEnd(&sourceLastPtr,num);
        scanf("%d",&num);
    }
    if(sourceHeadPtr->nextPtr != NULL){
        int max = getMaxExponent(sourceHeadPtr);
        sourceHeadPtr = radixSort(headPtr,sourceHeadPtr,&sourceLastPtr,max);
        printf("排序后：");
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
    int max = exp;//计算第一个结点的位数
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
    }//遍历每个结点并比较大小
    return max;
}
LISTNUMBERSPTR radixSort(LISTNODEPTR * headPtr,LISTNUMBERSPTR srcHeadPtr,LISTNUMBERSPTR * srcLastPtrPtr,int max){
    int i,j,k;
    // printf("%d\n",max);
    for(i = 1;i <= max;i++){//放入桶的次数
        LISTNUMBERSPTR srcCurrentPtr = srcHeadPtr->nextPtr,srcPreviousPtr = srcHeadPtr;
        for(k = 0;k < RADIX;k++){
            headPtr[k]->numbersLastPtr = headPtr[k]->numbersHeadPtr;//重置尾结点
        }
        while(srcCurrentPtr != NULL){
            int num = getNumber(srcCurrentPtr->data,i);//得到该位数字
            // printf("%d ",num);
            // printf("%d\n",num);
            srcPreviousPtr->nextPtr = srcCurrentPtr->nextPtr;//绕过现在的指针
            headPtr[num]->numbersLastPtr->nextPtr = srcCurrentPtr;//将现在指的结点接入桶中
            srcCurrentPtr->nextPtr = NULL;
            srcCurrentPtr = srcPreviousPtr->nextPtr;//将指针指回原链表
            headPtr[num]->numbersLastPtr = headPtr[num]->numbersLastPtr->nextPtr;
        }//放入桶中
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
            
        }//把桶中的数字连接起来，合并到source链表中（if选择语句非常重要，没有该语句链表就会断）
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
