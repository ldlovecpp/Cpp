#include<iostream>
using namespace std;
namespace MyVector
{
   template<class T>
  class vector{
    typedef T* Iterator;
    //构造函数
    vector()
      :_start(nullptr)
       ,_finish(nullptr)
       ,_endOfStorage(nullptr)
    {}
    vector(size_t size)
    {
      _start= new T[size];
      _finish  = _start;
      _endOfStorage = _start + size;
    }
    vector(size_t n , const T& val)
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
   vector(const vector<T>&arr)
    {
      _start = new T[arr.capacity()];
      _finish = _start + arr.size();
      _endOfStorage = _start  + arr.capacity();
      for(size_t i = 0;i<size();i++)
      {
        _start[i] = arr[i];
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
