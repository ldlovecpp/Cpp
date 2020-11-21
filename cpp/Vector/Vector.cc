#include<iostream>
using namespace std;
namespace LD
{
  template<class T>
  class Vector
  {
  public:
    //迭代器
    typedef T* iterator;
    typedef const T* const_iterator;
    iterator begin() const
    {
      return _start;
    }
    iterator end() const
    {
      return _finish;
    }
    const_iterator cbegin() const
    {
      return _start;
    }
    const_iterator cend() const
    {
      return _finish;
    }

    //容器大小
    size_t size() const
    {
      return _finish - _start;
    }
    size_t capacity() const
    {
      return _eos - _start;
    }

    //支持随机访问
    T& operator [] (size_t pos) const
    {
       return _start[pos];
    }

    //扩容
    void reserve(size_t n)
    {
       if(n>capacity())
       {
         size_t oldSize = size();
         T* tmp  = new T[n];
         for(size_t i=0;i<size();i++)
         {
           //不可使用memcpy等浅拷贝函数,因为原始数据可能携带资源
           tmp[i] = _start[i];
         }
         if(_start!=nullptr)
         {
           delete _start;
         }
         _start = tmp;
         tmp = nullptr;
         _finish = _start  + oldSize;
         _eos = _start + n;
       }
    }
    void resize(size_t n ,const T& val = T())
    {
      //如果n小于size,将size()缩小即可
      if(n<size())
      {
        _finish = _start + n;
        return;
      }

      //如果n超过了容器的最大容量,扩容
      if(n>capacity())
      {
       reserve(n);
      }
      //将size扩大到n
      for(int i = size();i<n;i++)
      {
        _start[i] = val;
      }
      //更新_finish位置
      _finish = _start+n;
    }


    //构造函数
    Vector()
      :_start(nullptr)
       ,_finish(nullptr)
       ,_eos(nullptr)
    {}

    Vector(size_t n,const T& val = T())
      :_start(nullptr)
       ,_finish(nullptr)
       ,_eos(nullptr)
    {
      resize(n,val);
    }

    //赋值运算符重载
    Vector<T>& operator = (Vector<T> v)
    {
      _start = _finish = _eos = nullptr;
      Swap(v);
      return *this;
    }
    void Swap(Vector<T>& v)
    {
      swap(_start,v._start);
      swap(_finish,v._finish);
      swap(_eos,v._eos);
    }
    template<class InputIterator>
    Vector(InputIterator begin,InputIterator end)
    {
      reserve(end-begin);
      while(begin!=end)
      {
        push_back(*begin);
        ++begin;
      }
    }
    Vector(const Vector<T>& v)
      :_start(nullptr)
       ,_finish(nullptr)
       ,_eos(nullptr)
    {
     reserve(v.capacity());
     iterator it = begin();
     const_iterator vit = v.cbegin();
     while(vit != v.cend())
     {
        *it = *vit;
        ++vit;
        ++it;
     }
     _finish = _start + v.size();
    }
    //增
    void push_back(const T& val)
    {
     insert(end(),val);
    }
    void insert(iterator pos,const T& val)
    {
      if(pos>=begin() && pos<=end())
      {
        if(_finish == _eos)
        {
         size_t distance = pos - _start;
         size_t new_Size = capacity() == 0 ? 15 : 2*capacity();
         reserve(new_Size);
         pos = _start + distance;
        }
        iterator end = _finish-1;
        while(end > pos)
        {
          *(end+1) = *end;
          --end;
        }
        *pos = val;
        ++_finish;
      }
    }
    //删
    void pop_back()
    {
      erase(end()-1);
    }
    iterator erase(iterator pos)
    {
      if(pos>=begin()&&pos<end())
      {
        iterator begin = pos+1;
        while(begin < end())
        {
        *(begin -1 )  = *begin;
         ++begin;
        }
        --_finish;
        return pos;
      }
      return end();
    }
    //查
    iterator find(const T& val)
    {
      for(int i=0;i<size();++i)  
      {
        if(val==_start[i])
        {
          return _start + i;
        }
      }
      return end();
    }
   //重载运算符     
   bool operator == (const Vector<T>&v)
   {
     iterator vidx = v.begin();
     iterator idx = _start;
     while(vidx < v._finish && idx < _finish)
     {
       if(*vidx != *idx)
       {
        break; 
       }
       ++vidx;
       ++idx;
     }
     return vidx == v._finish && idx == _finish;
   }
   bool operator != (const Vector<T>& v)
   {
     return !(*this == v);
   }
   private:
       T* _start;
       T* _finish;
       T* _eos;
  };
}
void print(LD::Vector<int>&arr)
{
  for(auto& a : arr)
  {
    cout << a << " ";
  }
  cout << endl;
}
void test1()
{
   LD::Vector<int>a; 
   a.push_back(1);
   a.push_back(2);
   a.push_back(3);
   a.push_back(4);
   a.push_back(5);
   cout << a.size() <<endl;
   LD::Vector<int>b(a);
   print(b);
   b.pop_back();
   b.pop_back();
   b.pop_back();
   print(b);
}
int main()
{
   test1();
}
