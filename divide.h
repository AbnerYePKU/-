//
//  divide.h
//  分治法
//
//  Created by 叶胥达 on 2018/7/7.
//  Copyright © 2018年 叶胥达. All rights reserved.
//

#ifndef divide_h
#define divide_h

/// BinarySearch(二分查找)
//  Function: 在数组 A[p:q] 中找到值为 x 的数的下标 index
//  Input: A,p,q,x
//  Output: index
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

/// Merge(数组整合)
// Function: A[p:r] 和 A[r:q] 已排序完毕, 将其合并在一起
// Input: A,p,r,q
template <typename T>
void Merge(T *A,int p,int r,int q){
    T *B=new T(q-p); // 开辟一个新的数组, 用于存储整合后的值
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

/// MergeSort(归并排序)
//  Function: 对 A[p:q] 从小到大排序
//  Input: A,p,q
template <typename T>
void MergeSort(T *A,int p,int q) {
    if(q-p<=1)return; // 待排序长度<=1
    int r=(p+q)/2; // 中央边界
    MergeSort<T>(A,p,r);
    MergeSort<T>(A,r,q);
    Merge<T>(A,p,r,q); // 整合
}

#endif /* divide_h */
