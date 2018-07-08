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

/// FindSecond(第二大)
//  Function: 在大小为n的数组A中找出第二大数second
//  Input: A,n
//  Output: second
int FindSecond(const int *A,int n){
    struct Node{ // 链表
        int info;
        Node* next;
    };
    Node *List=new Node[n]; // n元链表
    Node **pList=new Node *[n]; // n元指针数组
    for(int i=0;i<n;i++){
        List[i].info=A[i];
        List[i].next=nullptr;
        pList[i]=List+i;
    }
    int k=n; // 每轮淘汰赛之后剩余的元素个数
    while(k>1){ // 尚未决出冠军
        int i;
        for(i=0;i<k/2;i++){
            if(pList[2*i]->info>pList[2*i+1]->info){
                pList[2*i+1]->next=pList[2*i]->next; // 败者指向胜者的前一个对手
                pList[2*i]->next=pList[2*i+1]; // 胜者指向败者
                pList[i]=pList[2*i]; // 胜者放在第i位
            }
            else{
                pList[2*i]->next=pList[2*i+1]->next;
                pList[2*i+1]->next=pList[2*i];
                pList[i]=pList[2*i+1];
            }
        }
        if(k%2){
            pList[i]=pList[k-1];
        }
        k=k/2+k%2; // 剩下的人数减半
    }
    // 现在 pList[0] 指向的 Node 是冠军, 把他打败过的选手选出来
    Node *p=pList[0]->next;
    int second=p->info;
    while(p=p->next){ // 指向下一个
        if(second<p->info)second=p->info;
    }
    free(pList);
    free(List);
    return second;
}

/// Select(选第k小)
//  Function: 选出n元数组A中第k小的元素(k<=n)e. 结果可能会改变A
//  Input: A,n,k
//  Output: e(第k小)
int Select(int *A,int n,int k){
    
    /// 寻找中位数
    int q=n/5,r=n%5; // n=5q+r
    if(q==0){
        sort(A,A+n);
        return A[k-1];
    }
    int *M=new int[q]; // 存储q个五元组的中位数
    for(int i=0,*Five;i<q;i++){
        Five=A+5*i;
        sort(Five,Five+5); // 五个一排序
        M[i]=Five[2]; // 中位数
    }
    int m_=Select(M,q,q/2+q%2); // 用中位数m_将集合划分
    free(M); // 及时释放内存
    
    /// 将A中的所有数分配到S[0]和S[1]
    int S[2][n],t[2]={0,0},j; // S[0],S[1]分别存储比m_小和大的元素
    for(int i=0,*Five;i<q;i++){
        Five=A+5*i;
        if(Five[2]>m_){ // 五元组中位数大于m_
            j=Five[0]>m_; // 0或1
            S[j][t[j]++]=Five[0]; // 根据与m_的大小关系进行分配
            j=Five[1]>m_;
            S[j][t[j]++]=Five[1];
            j=1;
            S[j][t[j]++]=Five[2]; // 大于m_的直接分配到S[1]
            S[j][t[j]++]=Five[3];
            S[j][t[j]++]=Five[4];
        }
        else if(Five[2]<m_){ // 五元组中位数小于m_
            j=0;
            S[j][t[j]++]=Five[0]; // 小于m_的直接分配到S[0]
            S[j][t[j]++]=Five[1];
            S[j][t[j]++]=Five[2];
            j=Five[3]>m_; // 0或1
            S[j][t[j]++]=Five[3]; // 根据与m_的大小关系进行分配
            j=Five[4]>m_;
            S[j][t[j]++]=Five[4];
        }
        else{
            j=0;
            S[j][t[j]++]=Five[0]; // 小于m_的直接分配到S[0]
            S[j][t[j]++]=Five[1];
            S[j][t[j]++]=Five[2];
            j=1;
            S[j][t[j]++]=Five[3];
            S[j][t[j]++]=Five[4];
        }
    }
    // 对余下的r个数进行处理
    for(int k=0,j,*Five;k<r;k++){
        Five=A+5*q;
        j=Five[k]>m_;
        S[j][t[j]++]=Five[k];
    }
    
    /// 递归处理
    if(k<=t[0]) return Select(S[0],t[0],k); // 从S[0]中选择
    else return Select(S[1],t[1],k-t[0]); // 从S[1]中选择
}

int BWPairs(const int *A,int n,int m_){
    int i=0,j=0,k,pairs=0;
    while(j!=n){
        while(j<n&&A[j]>m_)j++;
        k=j;
        while(k<n&&!(A[k]>m_))k++;
        pairs+=(j-i)*(k-j);
        i+=k-j;
        j=k;
    }
    return pairs;
}

/// Inversions(逆序数)
//  Function: 对于n元整数数组A(元素互不相等), 计算其逆序数
//  Input: A,n(可能改变A)
//  Output: inv
int Inversions(int *A,int n){
    /// 求中位数m_
    if(n<=1)return 0;
    auto Middle=[](const int *A,int n){
        int *B=new int[n];
        memcpy(B,A,n*sizeof(int));
        int m_=Select(B,n,n>>1);
        free(B);
        return m_;
    };
    int m_=Middle(A,n);
    /// 计算逆序数inv
    int inv=BWPairs(A,n,m_);
    /// 构造黑色集B, 白色集W
    int *B=new int((n>>1)+1),iterB=0;
    int *W=A,iterW=0;
    for(int i=0;i<n;i++){
        if(A[i]>m_)B[iterB++]=A[i];
        else W[iterW++]=A[i];
    }
    /// 计算逆序数inv
    inv+=Inversions(B,iterB);free(B);
    inv+=Inversions(W,iterW);
    return inv;
}
