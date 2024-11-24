#include<iostream>
#include<stdexcept>
#include<cmath>
#include<string>

template <typename T>
struct Node
{
  int key_;
  T value_;
  Node<T>* left_;
  Node<T>* right_;
  int height_; // height is the longest route from current node to the lowest leaf (non-existing node height is 0, node without children height is 1)

  Node (int key, T value) : key_(key), value_(value), left_(nullptr), right_(nullptr), height_(1) {}
};

template <typename T>
class AVLTree
{
public:
  AVLTree() : root_(nullptr) {}

  void insert(int key, T value) {
    root_ = insert_pr(root_, key, value);
  }

  void remove(int key) {
    root_ = delete_pr(root_, key);
  }

  int search(int key) {
    return search_pr(root_, key);
  }
  void printTree() {
    printTree_pr(root_);
    std::cout << std::endl;
  }

private:
  Node<T>* root_;

  int height(Node<T>* node) {
    if (node == nullptr) {
      return 0;
    }
    return node->height_;
  }

  int balanceFactor(Node<T>* node) {
    if (node == nullptr) {
      return 0;
    }
    return height(node->left_) - height(node->right_);
  }

  Node<T>* rRotate(Node<T>* y) {
    Node<T>* x = y->left_;
    Node<T>* t2 = x->right_;

    x->right_ = y;
    y->left_ = t2;

    y->height_ = std::max(height(y->left_), height(y->right_)) + 1;
    x->height_ = std::max(height(x->left_), height(x->right_)) + 1;

    return x;
  }

  Node<T>* lRotate(Node<T>* x) {
    Node<T>* y = x->right_;
    Node<T>* t2 = y->left_;

    y->left_ = x;
    x->right_ = t2;

    x->height_ = std::max(height(x->left_), height(x->right_)) + 1;
    y->height_ = std::max(height(y->left_), height(y->right_)) + 1;

    return y;
  }

  Node<T>* balance(Node<T>* node) {
    int cur_balance = balanceFactor(node);

    if (cur_balance > 1 && balanceFactor(node->left_) >= 0) return rRotate(node);
    if (cur_balance > 1 && balanceFactor(node->left_) < 0) {
      node->left_ = lRotate(node->left_);
      return rRotate(node);
    }
    if (cur_balance < -1 && balanceFactor(node->right_) <= 0) return lRotate(node);
    if (cur_balance < -1 && balanceFactor(node->right_) > 0) {
      node->right_ = rRotate(node->right_);
      return lRotate(node);
    }
    return node;
  }

  Node<T>* insert_pr(Node<T>* node, int key, T value) {
    if (node == nullptr) {
      return new Node(key, value);
    }
    if (key < node->key_) node->left_ = insert_pr(node->left_, key, value);
    else if (key > node->key_) node->right_ = insert_pr(node->right_, key, value);
    else throw std::runtime_error("Trying to insert duplicating key!");

    node->height_ = std::max(height(node->left_), height(node->right_)) + 1;
    
    return balance(node);
  }

  Node<T>* getMin(Node<T>* node) {
    if (node == nullptr) throw std::runtime_error("Trying to get minimum key in empty tree!");
    if (node->left_ == nullptr) return node;
    return getMin(node->left_);
  }

  Node<T>* getMax(Node<T>* node) {
    if (node == nullptr) throw std::runtime_error("Trying to get maximum key in empty tree!");
    if (node->right_ == nullptr) return node;
    return getMax(node->right_);
  }

  Node<T>* delete_pr(Node<T>* node, int key) {
    if (node == nullptr) return nullptr;
    else if (key < node->key_) node->left_ = delete_pr(node->left_, key);
    else if (key > node->key_) node->right_ = delete_pr(node->right_, key);
    else {
      if (node->left_ == nullptr || node->right_ == nullptr) {
        Node<T>* temp = node;
        if (node->left_ == nullptr) node = node->right_;
        else node = node->left_;
        delete temp;
      }
      else {
        Node<T>* minInRight = getMin(node->right_);
        node->key_ = minInRight->key_;
        node->value_ = minInRight->value_;
        node->right_ = delete_pr(node->left_, minInRight->key_);
      }
    }
    if (node == nullptr) return node;
    node->height_ = std::max(height(node->left_), height(node->right_)) + 1;

    return balance(node);
  }

  int search_pr(Node<T>* node, int key) {
    if (node == nullptr) {
      throw std::runtime_error("Trying to search data in empty tree!");
    }
    if (node->key_ == key) return node->value_;
    return ((key < node->key_) ? search_pr(node->left_, key) : search_pr(node->right_, key));
  }

  void printTree_pr(Node<T>* node) {
    if (node == nullptr) return;
    printTree_pr(node->left_);
    std::cout << node->key_ << "-" << node->value_ << " ";
    printTree_pr(node->right_);
  }
};

int main() {
  AVLTree<int> tree;
  tree.insert(1, 50);
  tree.insert(5, 1000);
  tree.insert(3, 60);
  tree.printTree();
  tree.remove(1);
  tree.printTree();
  std::cout << tree.search(5) << std::endl;
  AVLTree<std::string> str_tree;
  str_tree.insert(1, "qwerty");
  str_tree.insert(10, "asdfg");
  str_tree.insert(7, "zxcv");
  str_tree.insert(9, "rfv");
  str_tree.printTree();

  return 0;
}