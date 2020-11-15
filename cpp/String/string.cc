#include<iostream>
#include<string.h>
using namespace std;
class String 
{
public:
  //6个基本成员函数
  String()
    :_ptr(new char[16])
     ,_size(0)
     ,_capacity(15)
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
    :_ptr(nullptr)
     ,_size(0)
     ,_capacity(0)
  {
   String tmp(s._ptr);
   Swap(tmp);
  }
//  String(const String& s)
//    :_ptr(new char[strlen(s._ptr)])
//     ,_size(s._size)
//     ,_capacity(s._capacity)
//  {
//    strcpy(_ptr,s._ptr);
//  }
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
  void reserve(size_t n)
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

  void resize(size_t n,char c='\0')
  {
    if(n<=_size)
    {
      _ptr[n]= '\0';
    }
    else if(n<_capacity)
    {
     for(size_t i=_size;i<_capacity;i++) 
     {
     _ptr[i]=c;
     }
    }
    else 
    {
      reserve(n);
      for(size_t i=_size;i<_capacity;i++)
      {
        _ptr[i] = c;
      }
    }
  }

  char* c_str()
  {
  return _ptr;
  }

  //增
  void insert(size_t pos,char c)
  {
   if(_size<pos)
     return;
   if(_size ==_capacity)
   {
     size_t new_capacity = _capacity ==0 ? 15 : 2*_capacity;
     reserve(new_capacity);
   }
   size_t end = _size + 1 ;
   while(end>pos)
   {
    _ptr[end] = _ptr[end-1];
   }
   _ptr[pos] = c;
   _size++;
  }
  void insert(size_t pos,char* str)
  {
    if(pos>_size)
    {
      return;
    }
    size_t len = strlen(str);
    size_t end  = _size + len;
    while(end > pos)
    {
      _ptr[end] = _ptr[end-len];
      end--;
    }
    for(int i=0 ;i<len;i++)
    {
      _ptr[i+pos] = str[i];
    }
  }
  void insert(size_t pos,String s)
  {
    insert(pos,s._ptr);
  }
  void push_back(char c)
  {
   insert(_size,c);
  }
  //删
  void erase(size_t begin,size_t len)
  {
   if(_size==0)
     return;
   if(begin > _size)
     return;
   if(begin+len>=_size)
   {
    _size  = begin;
    _ptr[begin]  = '\0';
    return;
   }
   for(size_t i=begin+len;i<=_size;i++)
   {
     _ptr[i-len]=_ptr[i];
   }
   _size-=len;
  }
  void pop_back()
  {
    erase(_size-1,1);
  }
  //查
  size_t find(char* str)
  {
   if(str==nullptr)
     return -1;
   for(size_t i=0;i<_size;i++)
   {
      if(_ptr[i]==str[0]) 
      {
        size_t j = 0;
        for(j=i;j<_size&&j<strlen(str)+i&&str[j-i]==_ptr[j];j++);
        if(j==strlen(str)+i)
          return i;
      }
   }
   return -1;  
  }
  size_t find(char c)
  {
     for(size_t i=0;i<_size;i++)
     {
       if(c==_ptr[i])
       {
         return i;
       }
     }
     return -1;
  }
  //迭代器
  typedef char* iterator;  
  typedef const char* const_iterator;
  iterator begin()
  {
    return _ptr;
  }
  iterator end()
  {
    return _ptr+_size;
  }
  const_iterator cbegin() const
  {
    return  _ptr;
  }
  const_iterator cend()
  {
    return _ptr+_size;
  }
private:
  char* _ptr;
  size_t _size;
  size_t _capacity;
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
void test2()
{
//  String s("luodong");
  String s2;
  s2.insert(0,'a');
  s2.insert(0,'b');
  s2.insert(0,'c');
  s2.insert(0,'d');
  s2.insert(0,'e');
  cout << s2 <<endl;
  s2.insert(0,"wdy");
  cout << s2 <<endl;
  String s3("ilove");
  s2.insert(0,s3);
  cout<< s2 <<endl;
  s2.push_back('1');
  s2.push_back('2');
  s2.push_back('3');
  s2.push_back('4');
  s2.push_back('5');
  cout<< s2 <<endl;
}
void test3()
{
  String s("luodong");
  s.pop_back();
  s.pop_back();
  s.pop_back();
  cout << s <<endl;
}
void test()
{
  String s("luodong");
  s.insert(0,"wangdingyang");
  cout << s  <<endl;
}
int main()
{
  test();
}
