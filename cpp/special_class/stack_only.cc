#include<iostream>
using namespace std;
//只能在栈上创建对象
//设计思路：
//1.删除operator new 函数
//2.删除opertor delete 函数
//3.将构造函数设置为私有
//4.提供一个静态函数用以在栈上创建对象
class Stack_Only
{
public:
  static Stack_Only create()
  {
    return Stack_Only();
  }
  void print()
  {
    cout << "1" <<endl;
  }
private:
  Stack_Only(){}
  void* operator new (size_t size)  = delete;
  void operator delete(void* p) = delete;
};
int main()
{
  Stack_Only sk  = Stack_Only::create();
  sk.print();
  return 0;
}
