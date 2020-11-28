#include<iostream>
using namespace std;
template <class T>
struct ListNode
{
  T _val;
  ListNode<T>* _prev;
  ListNode<T>* _next;
  ListNode(T v=T())
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
  Node* _head;
};
template<class T>
class List{
public:
  typedef  ListNode<T> Node;
  typedef ListIterator<T,T&,T*> iterator;
  typedef  const ListIterator<T,T&,T*> const_iterator;
  //构造函数
  List()
  {
    CreateHead();
  }
  template <class Iterator> 
  List(Iterator begin ,Iterator end)
  {
    CreateHead();
    while(begin != end)
    {
      push_back(*begin);
      ++begin;
    }
  }
  List(List<T>& lst)
  {
   CreateHead();
   List<T>tmp(lst.begin(),lst.end());
   Swap(tmp);
  }
  void Swap(List<T>& lst)
  {
    head = lst.head;
    lst.head = nullptr;
  }
  List<T>& operator = (List<T> lst)
  {
    Swap(lst);
    return *this;
  }
  //析构
  ~List()
  {
    clear();
  }
  //清理
  void clear()
  {
    if(head == nullptr)
      return;
    else 
    {
      Node* p = head->_next;
      while(p!=head)
      {
       Node* n = p->_next;
       delete p;
       p=n;
      }
      delete head;
      head = nullptr;
    }
  }

  //增删查改
  //增
  iterator insert(iterator pos,const T& val)
  {
    Node* p = pos._head;
    Node* new_node = new Node(val);
    new_node->_next = p->_next;
    new_node->_prev = p;
    p->_next->_prev = new_node;
    p->_next = new_node;
    return iterator(new_node);
  }
  void push_back(const T& v)
  {
   insert(iterator(head->_prev),v);
  }
  void push_front(const T& v)
  {
    insert(iterator(head),v);
  }
 //删除
  iterator erase(iterator pos)
  {
   Node* p = pos._head;
   p->_prev->_next = p->_next;
   p->_next->_prev = p->_prev;
   Node* res = p->_next;
   delete p;
   return iterator(res);
  }
  void pop_back()
  {
    erase(iterator(head->_prev));
  }
  void pop_front()
  {
    erase(iterator(head->_next));
  }

  //查找
  iterator find(const T& val)
  {
  for(iterator i =begin();i<end();i++)
  {
    if((*i)==val){
      return i;
    }
  }
  return end();
  }
  void CreateHead()
  {
    head = new Node;
    head->_next = head->_prev = head;
  }

  //迭代器
  iterator begin() const
  {
    return iterator(head->_next);
  }
  iterator end()  const
  {
    return iterator(head);
  }
  iterator cbegin() const
  {
    return const_iterator(head->_next);
  }
  iterator cend() const
  {
    return const_iterator(head);
  }
private:
  Node* head;
};
void print(List<int>&lst)
{
  for(List<int>::iterator p =lst.begin() ; p != lst.end();p++)
  {
     cout << *p <<endl;
  }
  cout << endl;
}
void test()
{
  List<int>lst;
  lst.push_back(1);
  lst.push_back(2);
  lst.push_back(3);
  lst.push_back(4);
  lst.push_back(5);
  lst.push_back(6);
  print(lst);
  lst.pop_front();
  print(lst);
  lst.pop_front();
  print(lst);
  lst.pop_front();
  print(lst);
}
int main()
{
  test();
}
