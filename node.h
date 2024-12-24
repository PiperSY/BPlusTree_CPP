#ifndef NODE_H_
#define NODE_H_

//#include "leaf.h"

using namespace std;

/*
  Tree node implementation for internal nodes.
*/

template <typename T1 = int, typename T2 = int>
class Node {
  private:
    int order;
    bool is_leaf;
    T1 *keys;
    int keys_len;
    T2 ***values;
    int values_len;
    int *value_count;
    Node<T1, T2> *parent;
    Node<T1, T2> *next_node;
    Node<T1, T2> *prev_node;

  public:
    friend class Node<T1, T2>;
    //Node();
    Node(int ord, bool leaf = false, Node *parent_n = nullptr);
    //Node(int ord, Node *parent_n, bool leaf, T1 *keys_n, int keys_len_n, )
    ~Node();

    //void array_grow(int type);
    int key_value_index(T1 key);
    void insert_into_node(T1 key, T2 *value, int k_index);
    void insert_into_internal_node(T1 key, T2 *value, int k_index, int v_index);
    void insert_value_at_key(T2* value, int index);
    Node<T1, T2>* split_leaf(int split_index);
    Node<T1, T2>* split_parent(int split_index);

    void insert_key(T1 key, int k_index);
    void insert_value(T2 *value, int v_index);
    void insert_value_leaf(T2 *value, int v_index);
};

/*template <typename T1, typename T2>
Node<T1, T2>::Node()
{
  order = 10;
}*/

template <typename T1, typename T2>
Node<T1, T2>::Node(int ord, bool leaf = false, Node *parent_n = NULL)
{
  order = ord;
  is_leaf = leaf;
  //keys = new T1[order-1];
  keys_len = 0;
  values_len = 0;
  //if (is_leaf){
  //  value_count = new int[order-1];
  // } else {
  value_count = nullptr;
  // }
  /*int temp = order;
  if (is_leaf){ 
    values_len = order-1;
  }
  values = new T2[temp];*/
  keys = nullptr;
  values = nullptr;
  parent = parent_n;
  next_node = nullptr;
  prev_node = nullptr;
}

template <typename T1, typename T2>
Node<T1, T2>::~Node()
{
  delete [] keys;
  for (int i=0 ; i<values_len ; ++i){
    if (is_leaf) {
      for (int j=0 ; j<value_count[i] ; ++j){
        delete *((*(values+i))+j);
      }
    } else {
      delete *(*(values+i));
    }
    delete [] *(values+i);
  }
  delete [] values;
}

template <typename T1, typename T2>
void Node<T1, T2>::insert_key(T1 key, int k_index)
{
  ++keys_len;
  T1 *temp = new T1[keys_len];
  for (int i=0 ; i<k_index ; ++i){
    *(temp+i) = *(keys+i);
  }
  *(temp+k_index) = key;
  for (int i=k_index+1 ; i<keys_len ; ++i){
    *(temp+i) = *(keys+i-1);
  }
  delete [] keys;
  keys = temp;
}

template <typename T1, typename T2>
void Node<T1, T2>::insert_value_leaf(T2 *value, int v_index)
{
  ++values_len;
  T2 ***t_v = new T1**[values_len];
  int *t_c = new int[values_len];
  for (int i=values_len-1 ; i>v_index ; --i){
    *(t_v+i) = *(values+i-1);
    *(t_c+i) = *(value_count+i-1)
    //*(value_count+i) = *(value_count+i-1)
  }
  T2 **new_val = new T2*[1]{ value };
  *(t_v+v_index) = new_val;
  *(t_c+v_index) = 1;
  //*(value_count+v_index) = 1; 
  for (int i=v_index-1 ; i>=0 ; --i){
    *(t_v+i) = *(values+i);
    *(t_c+i) = *(value_count+i);
  }
  //*(t_v) = *(values)
  

  /*for (int i=0 ; i<values_len ; ++i){
    *(t_v+i) = *(values+i-1);
  }*/
  delete [] values;
  delete [] value_count;
  values = t_v;
  value_count = t_c;
}

template <typename T1, typename T2>
void Node<T1, T2>::insert_value(T2 *value, int v_index)
{
  ++values_len;
  T2 ***t_v = new T1**[values_len];
  for (int i=values_len-1 ; i>v_index ; --i){
    *(t_v+i) = *(values+i-1);
  }
  T2 **new_val = new T2*[1]{ value };
  *(t_v+v_index) = new_val;
  //*(value_count+v_index) = 1; 
  for (int i=v_index-1 ; i>=0 ; --i){
    *(t_v+i) = *(values+i);
  }
  //*(t_v) = *(values)
  

  /*for (int i=0 ; i<values_len ; ++i){
    *(t_v+i) = *(values+i-1);
  }*/
  delete [] values;
  values = t_v;
}

template <typename T1, typename T2>
int Node<T1, T2>::key_value_index(T1 key)
{
  return 0;
}

template <typename T1, typename T2>
void Node<T1, T2>::insert_into_node(T1 key, T2 *value, int k_index)
{
  insert_key(key, k_index);
  insert_value(value, k_index);
}

template <typename T1, typename T2>
void Node<T1, T2>::insert_into_internal_node(T1 key, T2 *value, int k_index, int v_index)
{
  insert_key(key, k_index);
  insert_value(value, v_index);
}

template <typename T1, typename T2>
void Node<T1, T2>::insert_value_at_key(T2 *value, int index)
{
  int t_i = *(value_count+index)+1;
  *(value_count+index) = t_i;
  T2 **t_v = new T2*[t_i];
  for (int i=0 ; i<t_i-1 ; ++i){
    *(t_v+i) = *(*(values+index)+i);
  }
  *(t_v+t_i-1) = value;
  delete [] *(values+index);
  *(values+index) = t_v;
}

template <typename T1, typename T2>
Node<T1, T2>* Node<T1, T2>::split_leaf(int split_index)
{
  Node *new_node = new Node<T1, T2>(order, true, parent);
  int l_2 = keys_len-split_index;
  T1 *t_k1 = new T1[split_index];
  T1 *t_k2 = new T1[l_2];
  T2 ***t_v1 = new T2**[split_index];
  T2 ***t_v2 = new T2**[l_2];
  int *v_c1 = new int[split_index];
  int *v_c2 = new int[l_2];
  for (int i=0 ; i<split_index ; ++i){
    *(t_k1+i) = *(keys+i);
    *(t_v1+i) = *(values+i);
    *(v_c1+i) = *(value_count+i);
  }
  int count = 0;
  for (int i=split_index ; i<keys_len ; ++i){
    *(t_k2+count) = *(keys+i);
    *(t_v2+count) = *(values+i);
    *(v_c2+count) = *(value_count+i);
    ++count;
  }
  
  delete [] keys;
  delete [] values;
  delete [] value_count;
  keys = t_k1;
  values = t_v1;
  value_count = v_c1;
  keys_len = split_index;
  values_len = split_index;
  new_node->keys = t_k2;
  new_node->values = t_v2;
  new_node->value_count = v_c2;
  new_node->keys_len = l_2;
  new_node->values_len = l_2;

  new_node->next_node = next_node;
  if (next_node != nullptr){
    next_node->prev_node = new_node;
  }
  next_node = new_node;

  return new_node;
}

template <typename T1, typename T2>
Node<T1, T2>* Node<T1, T2>::split_parent(int split_index)
{
  Node *new_node = new Node<T1, T2>(order, false, parent);
  int n_sp_i = split_index+1;
  int l_k_2 = keys_len-n_sp_i;
  int l_v_2 = values_len-n_sp_i;
  T1 *t_k1 = new T1[split_index];
  T1 *t_k2 = new T1[l_k_2];
  T2 ***t_v1 = new T2**[n_sp_i];
  T2 ***t_v2 = new T2**[l_v_2];

  for (int i=0 ; i<split_index ; ++i){
    *(t_k1+i) = *(keys+i);
    *(t_v1+i) = *(values+i);
  }
  *(t_v1+split_index) = *(values+split_index);

  int count = 0;
  for (int i=n_sp_i ; i<keys_len ; ++i){
    *(t_k2+count) = *(keys+i);
    *(t_v2+count) = *(values+i);
    ++count;
  }
  *(t_v2+values_len) = *(values+values_len);
  
  delete [] keys;
  delete [] values;
  keys = t_k1;
  values = t_v1;
  keys_len = split_index;
  values_len = n_sp_i;
  new_node->keys = t_k2;
  new_node->values = t_v2;
  new_node->keys_len = l_k_2;
  new_node->value_len = l_v_2;

  new_node->next_node = next_node;
  if (next_node != nullptr){
    next_node->prev_node = new_node;
  }
  next_node = new_node;

  return new_node;
}

#endif