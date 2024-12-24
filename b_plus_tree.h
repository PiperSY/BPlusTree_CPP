#ifndef B_PLUS_TREE_H_
#define B_PLUS_TREE_H_

#include "node.h"

using namespace std;

template <typename T1 = int, typename T2 = int>
class BPlusTree {
  private:
    int order;
    int min_keys;
    Node *root;

    bool is_empty();
    Node* get_leaf_node(T1 key);
    Node* get_leaf_node_with_indices(T1 key);
    bool insert_into_parent(T1 key, Node* new_node, int parent_k_i, int parent_v_i);
    void balance_internal_node(Node *node, int parent_k_i, int parent_v_i);
    void delete_from_internal_node(Node *node, int k_i);
    int get_ordered_succ(Node *node, int index);
    Node* merge(Node *left_node, Node *right_node, int index);
    void left_rotate(Node *left_node, Node *right_node, int index);
    void right_rotate(Node *left_node, Node *right_node, int index);

  public:
    friend class Node<T1, T2>;
    
    BPlusTree(int order_n);
    ~BPlusTree();

    T2** retrieve(T1 key);
    T2** retrieve_range(T1 key1 = NULL, T1 key2 = NULL);
    bool insert(T1 key, T2 *value);
    bool remove(T1 key, T2 *value = nullptr, Node *start = nullptr);

};

template<typename T1, typename T2>
BPlusTree<T1, T2>::BPlusTree(int order_n)
{
  order = order_n;
  min_keys = order%2 == 0 ? order/2-1 : order/2;
  root = new Node(order, true);
}

template<typename T1, typename T2>
BPlusTree<T1, T2>::~BPlusTree()
{
  delete root;
}


#endif