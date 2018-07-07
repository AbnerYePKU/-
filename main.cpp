//
//  main.cpp
//  分治法
//
//  Created by 叶胥达 on 2018/7/7.
//  Copyright © 2018年 叶胥达. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "divide.h" // 分治法头文件

using namespace std;

int main(){
    srand((unsigned)time(NULL));
    int A[30];
    for(int i=0;i<30;i++)A[i]=rand()%100;
    for(int i=0;i<30;i++)cout << A[i] << " ";cout << endl;
    MergeSort(A, 0, 30);
    for(int i=0;i<30;i++)cout << A[i] << " ";cout << endl;
}
