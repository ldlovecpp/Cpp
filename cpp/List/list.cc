#include<iostream>
using namespace std;
template <class T>
struct ListNode
{
  T val;
  ListNode* _prev;
  ListNode* _next;
};
template<class T>
class List{
  typedef  ListNode<T> Node;
 private:
  Node* head;
};
