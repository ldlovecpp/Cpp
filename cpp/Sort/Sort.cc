#include<iostream>
#include<stack>
using namespace std;
namespace  Sort
{
  template<class T>
  class Sort
  {
   public:
     
     void BubbleSort(T* arr,int len)
     {
          for(int i=0;i<len-1;i++)
          {
            for(int j=0;j<len-1-i;j++) 
            {
              if(arr[j]>arr[j-1])
              swap(arr[j],arr[j+1]);
            }
          }
     }
     
     int Divide(T* arr,int left,int right)
     {
        int pos = left;
        while(left < right)
        {
          while(left<right&&arr[right]>=arr[pos])
            --right;
          while(left<right&&arr[left]<=arr[pos])
            ++left;
          swap(arr[left],arr[right]);
        }
        swap(arr[left],arr[pos]);
        return left;
     }
     void QuickSortQ2(T* arr,int left,int right)
     {
      stack<int>sk;
      sk.push(left);
      sk.push(right);
      while(!sk.empty())
      {
        right = sk.top();
        sk.pop();
        left = sk.top();
        sk.pop();
        if(left<right){
          int mid = Divide(arr,left,right);
          sk.push(mid+1);
          sk.push(right);
          sk.push(left);
          sk.push(mid-1);
        }
      }
     }
     void QuickSortQ(T* arr,int left,int right)
     {
       if(left >= right)
       {
         return;
       }
       int mid =  Divide(arr,left,right);
       QuickSortQ(arr,left,mid-1);
       QuickSortQ(arr,mid+1,right);
     }
     void QuickSort(T* arr,int  len)
     {
      QuickSortQ2(arr,0,len-1);
     }
     void SertSort(int* arr,int len)
     {
       for(int i=1;i<len;++i)
       {
         int tmp = arr[i];
         int j=i;
         while(j>0&&arr[j-1]>tmp)
         {
           arr[j] = arr[j-1];
           --j;
         }
         arr[j] = tmp;
       }
     }
     void SheelSort(T* arr,int len)
     {
        int step  = len/2;
        while(step>=1)
        {
          for(int i=step;i<len;++i)
          {
            int tmp = arr[i];
            int j=i;
            while(j-step>=0&&arr[j-step]>tmp){
             arr[j] = arr[j-step];
             j-=step;
            }
            arr[j] = tmp;
          }
          step = step/2;
        }
     }
     void merage(T* arr,int left1,int right1,int left2,int right2,T* tmp)
     {
       int begin = left1;
       int idx = begin; 
       while(left1 <= right1 && left2 <= right2) 
       {
          if(arr[left1] < arr[left2])
          {
            tmp[idx++] = arr[left1++];
          }
          else 
          {
            tmp[idx++] = arr[left2++];
          }
       }
       while(left1<=right1)
       {
          tmp[idx++] = arr[left1++];
       }
       while(left2<=right2)
       {
          tmp[idx++] = arr[left2++];
       }
       for(int i=begin;i<idx;i++)
       {
         arr[i] = tmp[i];
       }
     }
     void merageSortQ(T* arr,int left,int right,T* tmp)
     {
        if(left < right)
        {
          int mid = left + (right-left) /2; 
          merageSortQ(arr,left,mid,tmp);
          merageSortQ(arr,mid+1,right,tmp);
          merage(arr,left,mid,mid+1,right,tmp);
        }
     }
     void merageSort(int* arr,int len)  
     {
       int* tmp = new T[len];
       merageSortQ(arr,0,len-1,tmp);
       delete []tmp;
     }
     //堆排序
     //向下调整
     void ShiftDown(T* arr,int parent,int len)
     {
       int child  =  parent * 2  + 1;
       while(child < len)
       {
          //取到两个孩子中最大的和母亲交换
          //更新孩子和母亲
          if(child+1 < len && arr[child +1] > arr[child])
          {
            child++;
          }
          if(arr[child] > arr[parent])
          {
           swap(arr[child],arr[parent]);
           parent = child;
           child =parent*2+1;
          }
          else 
            break;
       }
     }
     void HeapSort(T* arr,int len)
     {
       //建堆
       //从第一非叶子节点向上走,构建大堆
       for(int i=(len-2)/2 ;i>=0;i--)
       {
         ShiftDown(arr,i,len);
       }
       while(len > 1)
       {
         swap(arr[--len],arr[0]);
         ShiftDown(arr,0,len);
       }
     }
      
  };
};
void getNum(int* arr,int len)
{
   for(int i=0;i<len;i++) 
   {
     arr[i] = rand()%len;
   }
}
void printArr(int* arr,int len)
{
  for(int i=0;i<len;i++)
  {
    cout << arr[i]<<" " ;
  }
  cout <<endl;
}
void test()
{
   Sort::Sort<int>s;
   int* arr = new int[100];
   getNum(arr,100);
   printArr(arr,100);
   s.merageSort(arr,100);
   printArr(arr,100);
   delete []arr;
}
int main()
{
  test();
}
