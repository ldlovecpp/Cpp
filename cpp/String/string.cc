#include<iostream>
#include<string.h>
using namespace std;
class String 
{
public:
  //6个基本成员函数
  String()
    :_ptr(new char)
     ,_size(0)
     ,_capacity(0)
  {
    _ptr[0] = '\0';
  }
  String(char* str)
    :_ptr(new char[strlen(str)+1])
     ,_size(strlen(str))
     ,_capacity(strlen(str))
  {
    strcpy(_ptr,str);
    _ptr[_size]='\0';
  }
  String(const String& s)
  {
   _ptr=nullptr;
   String tmp(s._ptr);
   Swap(tmp);
  }
  String& operator = (String tmp)
  {
    Swap(tmp);
    return *this;
  }
  ~String()
  {
    if(_ptr)
    {
      delete []_ptr;
    }
    _size=0;
    _capacity=0;
  }
  String* operator&()
  {
   return this;
  }
  const String* operator&() const
  {
    return this;
  }
  void Swap(String& tmp)
  {
    swap(_ptr,tmp._ptr);
    swap(_size,tmp._size);
    swap(_capacity,tmp._capacity);
  }  
  
  //空间相关
  void reserve(int n)
  {
   //创建新的空间,保存数据
   char* tmp = new char[n+1];
   strcpy(tmp,_ptr);
   //将原来的空间释放
   //把新的空间交给对象
   swap(tmp,_ptr);
   if(tmp)
   delete []tmp;
   _capacity = n;
  }

  void resize(int n,char c='\0')
  {
    if(n<0)
    {
      return;
    }
    else if(n<=_size)
    {
      _ptr[n]= '\0';
    }
    else if(n<_capacity)
    {
     for(int i=_size;i<_capacity;i++) 
     {
     _ptr[i]=c;
     }
    }
    else 
    {
      reserve(n);
      for(int i=_size;i<_capacity;i++)
      {
        _ptr[i] = c;
      }
    }
  }


  char* c_str()
  {
  return _ptr;
  }
private:
  char* _ptr;
  int _size;
  int _capacity;
};
ostream& operator << (ostream& out_put , String& s)
{
   out_put << s.c_str();
   return out_put;
}
void test1()
{
  String s("luodomg");
  cout<<"s: " <<s <<endl;
  String s2(s);
  cout << "s2: " <<s2 <<endl;
  String s3 = s;
  cout << "s3: " << s <<endl;
}
int main()
{
  test1();
}
