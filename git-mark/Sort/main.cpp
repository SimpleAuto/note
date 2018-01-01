/*
 *************************************************************************
 *    File Name:  main.cpp
 *       Author: Thomas Shanghai,Inc.
 *         Mail: 982737593@qq.com
 * Created Time: 2018年01月01日 星期一 15时06分13秒
 * 
 *  Description: ...
 * 
 *************************************************************************
*/
#include<iostream>
using namespace std;

// ------------------------
// 归并排序
void Merge(int *ar, int *arr_1, int begin, int mid, int end)
{
    int low = begin;
    int m   = mid;
    int mm  = mid+1;
    int k = 0;

    while(low <= mid && mm <= end)
    {
        if(ar[low] < ar[mm])
            arr_1[k++] = ar[low++];
        else
            arr_1[k++] = ar[mm++];
    }

    for(;low<=mid;)
        arr_1[k++] = ar[low++];
    for(;mm <= end;)
        arr_1[k++] = ar[mm++];

    for(int i=0;i<k;++i)
        ar[begin++] = arr_1[i];
}
 
void MergeSort(int *ar, int *arr_1, int begin, int end) 
{
    if(begin < end)
    {
        int mid = (begin+end) / 2;
        MergeSort(ar, arr_1, begin, mid);
        MergeSort(ar, arr_1, mid+1, end);
        Merge(ar, arr_1, begin, mid, end);
    }
}
//-------------------------

//-------------------------
//快速排序
void QuickSort()
{

}
//-------------------------
int main()
{
    int arr[]  = {1,10,9,2,3,8,7,4,5,6};
    int length = sizeof(arr) / sizeof(arr[0]);
    int *arr_1 = new int[length]; 
    for(int i=0;i<length;++i) 
        cout << arr[i] << " ";
    cout << endl;

    cout << "Merge Sort" << endl;
    MergeSort(arr, arr_1, 0, length-1);
    for(int i=0;i<length;++i) 
        cout << arr[i] << " ";
    cout << endl;
    
    return 0;
}
