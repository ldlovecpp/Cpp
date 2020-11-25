#include<iostream>
using namespace std;
template <class T>
struct ListNode
{
  T _val;
  ListNode<T>* _prev;
  ListNode<T>* _next;
  ListNode(T& v)
    :_val(v)
     ,_prev(nullptr)
     ,_next(nullptr)
  {}
};
template<class T,class Ref ,class Ptr>
class ListIterator
{
  typedef ListNode<T> Node;
  typedef ListIterator<T,Ref,Ptr> Self;
public:
  ListIterator(Node* node = nullptr)
    :_head(node)
  {}
  ListIterator(const Self& l)
    :_head(l._head)
  {}
  T& operator *()
  {
    return _head->_val;
  }
  T* operator &()
  {
    return &_head->val;
  }
  Self& operator ++()
  {
    _head = _head->_next;
    return *this;
  }
  Self& operator ++(int)
  {
    Self tmp = *this;
    _head = _head ->_next;
    return tmp;
  }
  Self& operator --()
  {
    _head = _head->_prev;
    return *this;
  }
  Self& operator --(int)
  {
    Self tmp = *this;
    _head = _head ->_prev;
    return tmp;
  }
  bool operator != (const Self& l)
  {
    return _head != l._head;
  }
  bool operator == (const Self& l)
  {
   return !_head == l._head;
  }
private:
  Node* _head;
};
template<class T>
class List{
public:
  typedef  ListNode<T> Node;
  typedef Node      
private:
  Node* head;
};
