#include<iostream>
using namespace std;
//我们知道Auto_Ptr智能指针的缺点在于它的拷贝构造函数和赋值运算符重载函数释放了被复制对象的资源，从而造成未定义行为,Unique_Ptr解决了这个问题但是解决方法比较暴力直接禁用了拷贝构造和赋值运算符可以复制对象的方法
template<class T>
class Unique_Ptr
{
public:
  Unique_Ptr(T* ptr)
    :_ptr(ptr)
  {}
  Unique_Ptr(Unique_Ptr<T>&up)=delete ;
  Unique_Ptr& operator = (Unique_Ptr<T>& up)=delete;
  T& operator *()
  {
   return *_ptr;
  }
  T* operator ->()
  {
  return _ptr;
  }
  ~Unique_Ptr()
  {
    if(_ptr)
      delete _ptr;
  }
private:
  T* _ptr; 
};
int main()
{
  int* p = new int(1);
  Unique_Ptr<int>up(p);
  cout << *up<<endl;
}
