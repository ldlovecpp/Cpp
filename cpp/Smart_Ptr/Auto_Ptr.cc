#include<iostream>
#include<memory>
using namespace std;
template<class T>
class AutoPtr
{
public:
  AutoPtr(T* ptr)
    :_ptr(ptr)
  {}
  AutoPtr(AutoPtr<T>& ap)
    :_ptr(ap._ptr)
  {
     ap._ptr=nullptr;
  }
  T& operator *()
  {
    return *_ptr;
  }
  T* operator -> ()
  {
    return _ptr;
  }
  AutoPtr<T>& operator = (AutoPtr<T>& ap)
  {
    if(this->_ptr==ap._ptr)
      return *this;
    if(_ptr)
    {
      delete _ptr;
    }
    _ptr=ap._ptr;
    ap._ptr=nullptr;
    return *this;
  }
private:
T* _ptr;
};
void test1()
{
  int* p= new int;
  AutoPtr<int>ap(p);
  *ap=10;
  AutoPtr<int>ap2(ap);
  cout << *ap <<endl;//程序会发生短错误,因为ap所携带的资源已经被ap2夺取,已经变成了空
}
void test2()
{
  int* p=new int;
  AutoPtr<int>ap(p);
  *ap=111;
  int* p2=new int;
  *p2=100;
  AutoPtr<int>ap2(p2);
  ap2=ap;
  cout << *p2 <<endl; //未定义行为,p2的资源已经被释放
}
int main()
{
  test2();
  return 0;
}
