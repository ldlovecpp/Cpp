#include<iostream>
#include<mutex>
using namespace std;
//Shared_Ptr完美的解决了Auro_Ptr只能指针所带来的拷贝构造时资源丢失的问题,它引入了一个引用计数,当引用计数为0的时候它才会真正的释放资源
template<class T>
class Shared_Ptr
{
public:
  Shared_Ptr(T* ptr)
    :_ptr(ptr)
     ,_mutex(new mutex)
     ,ref_count(new int(1))
  {}
  Shared_Ptr(const Shared_Ptr<T>&sp)
    :_ptr(sp._ptr)
     ,_mutex(sp._mutex)
     ,ref_count(sp.ref_count)
  {
   AddRefCount(); 
  }
  Shared_Ptr<T>& operator = (const Shared_Ptr<T>& sp)
  {
    if(_ptr==sp._ptr)  
    {
      return *this;
    }
    Release();
    _mutex=sp._mutex;
    ref_count=sp.ref_count;
    _ptr=sp._ptr;
    AddRefCount();
    return *this;
  }
  T& operator * ()
  {
    return *_ptr;
  }
  T* operator ->()
  {
    return _ptr;
  }
  ~Shared_Ptr()
  {
    Release();
  }
private:
  void Release()
  {
   bool flag=false;
   _mutex->lock();
   if(--(*ref_count)==0)
   {
     delete _ptr;
     delete ref_count;
     flag=true;
   }
   _mutex->unlock();
   if(flag)
     delete _mutex;
  }
  void AddRefCount()
  {
   _mutex->lock();
   ++(*ref_count);
   _mutex->unlock();
  }
private:
  T* _ptr;
  mutex* _mutex;
  int* ref_count;
};
int main()
{
  int* p = new int(100);
  Shared_Ptr<int>sp(p);
  cout << *sp <<endl;
  Shared_Ptr<int>sp2(sp);
  cout << *sp <<endl;
}
