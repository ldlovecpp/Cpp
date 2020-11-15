#include<iostream>
using std::cout;
using std::endl;
using std::cin;
namespace MyVector
{

  template<class T>
  class vector{
  public:
    typedef T* Iterator;
    //构造函数
    vector()
      :_start(nullptr)
       ,_finish(nullptr)
       ,_endOfStorage(nullptr)
    {}
    vector(size_t n , const T& val = T())
    {
      _start  = new T[n];
      _finish = _start+n;
      _endOfStorage = _start + n;
      Iterator p = begin();
      while(p!=end())
      {
        *p = val;
      }
    }
    vector(Iterator left,Iterator right)
    {
      int size =  right - left;
      resize(size);
      for(int i =0  ;i< size;i++)
      {
        _start[i] = *left++;
      }
    }
    vector(const vector<T>&arr)
      :_start(nullptr)
       ,_finish(nullptr)
       ,_endOfStorage(nullptr)
    {
     reserve(arr.capacity());
     Iterator p = begin();
     Iterator q  = arr.begin();
     while(q!=arr.end())
     {
       *p++ = *q++;
     }
    }
    //大小 
    size_t capacity()
    {
      return _endOfStorage - _start;
    }
    size_t size()
    {
      return _finish - _start;
    }

    //运算符重载 
    T& operator [](size_t n)
    {
      return _start[n];
    }
    T& operator = (const T& val)
    {
    }

    vector<T>& operator = (const vector<T> arr)
    {
      Swap(arr);
    }
  
    void Swap(const vector<T>& arr)
    {
      swap(_start,arr.start);
    }
    //迭代器
    Iterator begin()
    {
     return _start;
    }
    Iterator end()
    {
      return _finish;
    }
    
    //增
    void reserve()
    {
      int oldSize = size();
      int newSize=size()==0?15:2*oldSize;
      //开辟空间
      T* tmp = new T[newSize];
      //先拷贝之前的数据到新的空间
      for(size_t i=0;i<oldSize;i++)
      {
        tmp[i] = _start[i];
      }
      //释放原来的空间
      delete [] _start;
      //更新指针
      _start =  tmp;
      _finish = _start + oldSize;
      _endOfStorage = _start + newSize; 
    }

    void resize(size_t newSize)
    {
     while(capacity() <= newSize)
     {
       reserve(); 
     }
     _finish = _start + newSize;
    }
    
    void insert(size_t  pos,T val)
    {
      if(pos>size())
      {
        return;
      }
      if(_finish==_endOfStorage)
      {
         reserve(); 
      }
      for(size_t i=size();i>pos;i--)  
      {
        _start[i] = _start[i-1];
      }
      _start[pos] = val;
      _finish++;
    }
    void push_back(const T& val)
    {
       insert(size(),val);
    }
    //删
    void erase()
    {

    }
    void pop_back()
    {

    }
    //查
    int find(const T& val)
    {
       for(Iterator it = _start ;it< _finish;it++)
       {
          if((*it)==val)
            return it - _start;
       }
       return -1;
    }
    //析构函数
    ~vector()
    {
      delete []_start;
      _start = _finish = _endOfStorage = nullptr;
    }
  private:
    T* _start;
    T* _finish;
    T* _endOfStorage;
  };
}
void print(MyVector::vector<int>arr)
{
   for(int i=0;i<arr.size();i++)
   {
     std::cout << arr[i] <<std::endl;
   }
}
void test()
{
   MyVector::vector<int>arr;
   arr.push_back(1);
   arr.push_back(2);
   arr.push_back(3);
   arr.push_back(4);
   arr.push_back(5);
   print(arr);
}
int main()
{
  test();
}
