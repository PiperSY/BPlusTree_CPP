#ifndef LEAF_H_
#define LEAF_H_

using namespace std;

/*
  Tree node implementation for leaf nodes.
*/
template <typename T1, typename T2>
class BPlusTree;
template <typename T1>
class Node;

template <typename T1 = int, typename T2 = int>
class Leaf {
  private:
    int order;
    T1 *keys;
    int keys_len;
    T2 ***values;
    int values_len;
    int *value_count;
    Node<T1> *parent;
    Leaf<T1, T2> *next_node;
    Leaf<T1, T2> *prev_node;

    Leaf(int ord, Node *parent_n = nullptr);
    ~Leaf();

    int key_value_index(T1 key);
    void insert_into_node(T1 key, T2 *value, in k_index);
    void insert_value_at_key(T2 *value int index);
    Leaf<T1, T2>* split(int split_index);
    void insert_key(T1 key, int k_index);
    void insert_value(T2 *value, int v_index);

  public:
    friend class Leaf<T1, T2>;
    friend class Node<T1>;
    friend class BPlusTree<T1, T2>;


};

#endif