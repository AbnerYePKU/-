//
//  divide.h
//  分治法
//
//  Created by 叶胥达 on 2018/7/7.
//  Copyright © 2018年 叶胥达. All rights reserved.
//

#ifndef divide_h
#define divide_h

template <typename T>
int BinarySearch(const T *A,int p,int q,int x){
    int l=p,r=q-1; // 左边界和右边界
    while(r>=l){
        int m=(l+r)/2; // 中央边界
        if(A[m]>x)r=m-1;
        else if(A[m]<x)l=m+1;
        else return m;
    }
    return -1;
}

template <typename T>
void Merge(T *A,int p,int r,int q){
    T *B=new T[q-p]; // 开辟一个新的数组, 用于存储整合后的值
    int i=p,j=r,k=0; // 整合开始的下标
    while(1){ // 循环未结束
        bool i_end=(i==r),j_end=(j==q);
        if(i_end&&j_end)break;
        if(i_end)B[k++]=A[j++]; // A[p:r] 循环结束
        else if(j_end)B[k++]=A[i++]; // A[r,q] 循环结束
        else if(A[i]>A[j])B[k++]=A[j++]; // 选择较小值
        else B[k++]=A[i++];
    }
    memcpy(A+p,B,sizeof(T)*(q-p));
    free(B);
}

template <typename T>
void MergeSort(T *A,int p,int q) {
    if(q-p<=1)return; // 待排序长度<=1
    int r=(p+q)/2; // 中央边界
    MergeSort<T>(A,p,r);
    MergeSort<T>(A,r,q);
    Merge<T>(A,p,r,q); // 整合
}

void FindMax(const int *A,int n,int &max,int &index);
int FindMax(const int *A,int n);

void FindMin(const int *A,int n,int &min,int &index);
int FindMin(const int *A,int n);

void FindMaxMin(const int *A,int n,int &max,int &min);

int FindSecond(const int *A,int n);

int Select(int *A,int n,int k);

int BWPairs(const int *A,int n,int m_);
int Inversions(int *A,int n);

#endif /* divide_h */
