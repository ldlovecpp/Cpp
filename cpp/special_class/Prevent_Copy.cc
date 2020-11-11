#include<iostream>
using namespace std;
//思路：
//1.禁止拷贝构造函数和赋值运算符重在函数即可
class Prevent_Copy
{
public:
   Prevent_Copy(){};
   void print(){cout << "1 " <<endl;}
private:
   Prevent_Copy(const Prevent_Copy& pc) = delete;
   Prevent_Copy& operator = (const Prevent_Copy& pc)  = delete;
};
int main()
{
  Prevent_Copy pc;
  pc.print();
  return 0;
}
