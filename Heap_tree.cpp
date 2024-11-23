#include<iostream>
#include<stdexcept>
#include<type_traits>

struct Node {
  int key_;
  int value_;
  Node* left_ = nullptr;
  Node* right_ = nullptr;

  Node(int key, int value) : key_(key), value_(value), left_(nullptr), right_(nullptr) {}
};

class HeapTree {
public:
  HeapTree() : root_(nullptr) {}

  Node* getRoot() { return root_; }

  void insert(int key, int value) {
    ins(root_, key, value);
  }

  int search(int key) {
    return search_pr(root_, key);
  }

  void delete_leaf(int key) {
    root_ = delete_pr(root_, key);
  }

  void printTree() {
    printTree_pr(root_);
    std::cout << std::endl;
  }

private:
  void ins(Node* node, int key, int value) {
    if (node == nullptr) {
      root_ = new Node(key, value);
    }
    else if (key < node->key_) {
      if (node->left_ == nullptr) node->left_ = new Node(key, value);
      else ins(node->left_, key, value);
    }
    else if (key > node->key_) {
      if (node->right_ == nullptr) node->right_ = new Node(key, value);
      else ins(node->right_, key, value);
    }
    else if (key = node->key_) {
      throw std::runtime_error("Trying to insert duplicating key!");
    }
  }

  int search_pr(Node* node, int key) {
    if (node == nullptr) {
      throw std::runtime_error("Trying to search data in empty tree!");
    }
    if (node->key_ == key) return node->value_;
    return ((key < node->key_) ? search_pr(node->left_, key) : search_pr(node->right_, key));
  }

  Node* getMin(Node* node) {
    if (node == nullptr) throw std::runtime_error("Trying to get minimum key in empty tree!");
    if (node->left_ == nullptr) return node;
    return getMin(node->left_);
  }

  Node* getMax(Node* node) {
    if (node == nullptr) throw std::runtime_error("Trying to get maximum key in empty tree!");
    if (node->right_ == nullptr) return node;
    return getMax(node->right_);
  }

  Node* delete_pr(Node* node, int key) {
    if (node == nullptr) return nullptr;
    else if (key < node->key_) node->left_ = delete_pr(node->left_, key);
    else if (key > node->key_) node->right_ = delete_pr(node->right_, key);
    else {
      if (node->left_ == nullptr || node->right_ == nullptr) {
        Node* temp = node;
        if (node->left_ == nullptr) node = node->right_;
        else node = node->left_;
        delete temp;
      }
      else {
        Node* maxInLeft = getMax(node->left_);
        node->key_ = maxInLeft->key_;
        node->value_ = maxInLeft->value_;
        node->left_ = delete_pr(node->left_, maxInLeft->key_);
      }
    }
    return node;
  }

  void printTree_pr(Node* node) {
    if (node == nullptr) return;
    printTree_pr(node->left_);
    std::cout << node->key_ << "-" << node->value_ << " ";
    printTree_pr(node->right_);
  }

  Node* root_ = nullptr;
};

int main() {
  HeapTree tree;
  tree.insert(1, 50);
  tree.insert(5, 1000);
  tree.insert(3, 60);
  tree.printTree();
  tree.delete_leaf(1);
  tree.printTree();
  std::cout << tree.search(5);

  return 0;
}