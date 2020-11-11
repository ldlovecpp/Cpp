#include<iostream>
using namespace std;
class Heap_Only
{
public:
  static Heap_Only* create()
  {
    return new Heap_Only;
  }
  void print()
  {
    cout << 1 <<endl;
  }
private:
  Heap_Only(){};
};
int main()
{
  Heap_Only* p =  Heap_Only::create();
  p->print();
  return 0;
}
