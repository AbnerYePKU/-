//
//  main.cpp
//  分治法
//
//  Created by 叶胥达 on 2018/7/7.
//  Copyright © 2018年 叶胥达. All rights reserved.
//

#include <iostream>
#include "divide.h"

using namespace std;

/// FindMax(最大值)
//  Function: 在大小为n数组A中找到最大值max和下标index
//  Input: A,n,&max,&index
void FindMax(const int *A,int n,int &max,int &index){
    index=0;
    max=A[0]; // 设置初始值
    for(int i=1;i<n;i++){
        if(A[i]>max){
            max=A[i];
            index=i;
        }
    }
}

int FindMax(const int *A,int n){
    int max=A[0]; // 设置初始值
    for(int i=1;i<n;i++){
        if(A[i]>max)max=A[i];
    }
    return max;
}

/// FindMin(最小值)
//  Function: 在大小为n数组A中找到最大值min和下标index
//  Input: A,n,&min,&index
void FindMin(const int *A,int n,int &min,int &index){
    index=0;
    min=A[0]; // 设置初始值
    for(int i=1;i<n;i++){
        if(A[i]<min){
            min=A[i];
            index=i;
        }
    }
}

int FindMin(const int *A,int n){
    int min=A[0]; // 设置初始值
    for(int i=1;i<n;i++){
        if(A[i]<min)min=A[i];
    }
    return min;
}

/// FindMaxMin(最大最小值)
//  Function: 在大小为n数组A中找到最大值max和最小值min
//  Input: A,n,&max,&min
void FindMaxMin(const int *A,int n,int &max,int &min){
    int k=n/2+n%2; // 把数组分成两组, 每组k个数
    int Super[k],Infer[k]; // 大数组和小数组
    for(int i=0;i<n/2;i++){
        if(A[2*i]>A[2*i+1]){
            Super[i]=A[2*i];
            Infer[i]=A[2*i+1];
        }
        else{
            Super[i]=A[2*i+1];
            Infer[i]=A[2*i];
        }
    }
    if(n%2)Super[k-1]=Infer[k-1]=A[n-1]; // 分组完毕
    max=FindMax(Super,k);
    min=FindMin(Infer,k);
}

