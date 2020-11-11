#include<iostream>
#include<mutex>
using namespace std;
//懒汉模式
//程序一启动就会实例化出一个对象
//不管用不用
//优点： 实现简单
//缺点： 程序有可能启动慢
//实现方式：
//1.防拷贝,构造函数私有
//2.在类中定义一个静态变量，然后提供一个静态函数作为获取它的接口，然后在类外调用接口进行实例化
class Singleton
{
public:
   static Singleton* create_Singleton()
   {
     return &single;
   }
   void print() { cout << 1 << endl; }
  //数据段创建对象
  static Singleton single;
private:
  //防止创建对象,防止继承
  Singleton(){}
  //防拷贝
  Singleton(const Singleton& st) = delete;
  Singleton& operator =  (const Singleton& st) = delete;
};
Singleton Singleton::single;
//饿汉模式
//第一次创建对象的时候实列化出对象，以后直接使用对象
//优点： 程序启动快
//缺点： 实现困难
//实现方式：
//1.防拷贝，构造函数私有
//2.考虑多线程先的安全问题（双验证）
class Singleton2{
public:
  static Singleton2* create()
  {
    if(self==nullptr)
    {
      mtx.lock();
      if(self==nullptr)
      {
        self = new Singleton2;
        return self;
      }
      mtx.unlock();
    }
    return self;
  }
  void print()
  {
    cout << "print () " <<endl;
  }
public:
  static mutex mtx;
  static Singleton2* self;
private:
  Singleton2(){}
  Singleton2(const Singleton2& s2 )  = delete;
  Singleton2 operator = (const Singleton2& s2) = delete;
};
mutex Singleton2::mtx;
Singleton2* Singleton2::self = nullptr;
int main()
{
  Singleton2* p = Singleton2::create();
  p->print();
  return 0;
}
