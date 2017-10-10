  //  Copyright Nathan Cezar Cardoso [2017]

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <cstdint>
#include <stdexcept>
#include "array_list.h"

namespace structures {

template<typename T>
class BinaryTree {
 public:
     BinaryTree() = default;
     
    virtual ~BinaryTree();

    void insert(const T& data);

    void remove(const T& data);

    bool contains(const T& data) const;

    bool empty() const;

    std::size_t size() const;

    ArrayList<T> pre_order() const;

    ArrayList<T> in_order() const;

    ArrayList<T> post_order() const;

 private:
    struct Node {
        Node(const T& data) {
            data = data;
            left = nullptr;
            right = nullptr;
        }       

        void insert(const T& data_) {
            Node* novoNodo;
            if (data_ < this-> data) {
                if (this-> left == nullptr) {
                    novoNodo = new Node(data);
                    novoNodo->left = nullptr;
                    novoNodo->right = nullptr;
                    this-> left = novoNodo;
                } else {
                    left->insert(data_);
                }
            } else {
                if (this-> right == nullptr) {
                    novoNodo = new Node(data);
                    novoNodo->left = nullptr;
                    novoNodo->right = nullptr;
                    this-> right = novoNodo;
                } else {
                    right->insert(data);
                }
            }
        }

        bool remove(const T& data_) {
            if (data_ == this-> data) {
                if ((this->left != nullptr) && (this->right != nullptr)) {
                    Node* novoNodo = this->right;
                    while (novoNodo->left != nullptr) {
                        novoNodo = novoNodo->left;
                    }
                    this->data = novoNodo->data;
                    return right->remove(this->data);                    
                } else {
                    if (this->right != nullptr) {
                        this->data = right->data;
                        return right->remove(this->data);
                    } else {
                        if (this->left != nullptr) {
                            this->data = left->data;
                            return left->remove(data);
                        } else {
                            delete this;
                            return true;
                        }
                    }
                }
            } else {
                if ((this->right != nullptr) && (this->data < data_)) {
                    return right->remove(data_);                    
                } else if ((this->left != nullptr) && (this->data > data_)) {
                    return left->remove(data_);
                }
            }
            return false;
        }

        bool contains(const T& data_) const {
            if (data_ == this->data) {
                return true;                
            } else {
                if ((this->left != nullptr) && (data_ < this->data)) {
                    return left->contains(data_);
                } else if ((this->right != nullptr) && (data_ > this->data)) {
                    return right->contains(data_);
                }
            }
            return false;
        }

        void pre_order(ArrayList<T>& v) const {
            v.push_back(this->data);
            if (this->left != nullptr) {
                left->pre_order(v);
            }
            if (this->right != nullptr) {
                right->pre_order(v);
            }
        }

        void in_order(ArrayList<T>& v) const {
            if (this->left != nullptr) {
                left->in_order(v);
            }
            v.push_back(this->data);
            if (this->right != nullptr) {
                right->in_order(v);
            }
        }

        void post_order(ArrayList<T>& v) const {
            if (this->left != nullptr) {
                left->post_order(v);
            }
            if (this->right != nullptr) {
                right->post_order(v);
            }
            v.push_back(this->data);
        }
        
        T data;
        Node* left;
        Node* right;
    };

    Node* root = nullptr;
    std::size_t size_ = 0;
};

template<typename T>
virtual BinaryTree :: ~BinaryTree() {    
    size_ = 0;
    delete root;
}

template<typename T>
void BinaryTree :: insert(const T& data) {
    if (empty()) {
        root = new Node(data);
    } else {
        root->insert(data);
    }
    size_++;
}

template<typename T>
void BinaryTree :: remove(const T& data) {
    if (!empty()) {
        size_--;
        root->remove(data);
    }
}

template<typename T>
bool BinaryTree :: contains(const T& data) const {
    if (!empty()) {
        return root->contains(data);
    }
    return false;
}

template<typename T>
bool empty() const {
    return (size() == 0);
}

template<typename T>
std::size_t BinaryTree :: size() const {
    return size_;
}

template<typename T>
ArrayList<T> BinaryTree :: pre_order() const {
    structures::ArrayList<T> v;
    if (!empty()) {
        root->pre_order(v);
    }
    return v;        
}

template<typename T>
ArrayList<T> BinaryTree :: in_order() const {
    structures::ArrayList<T> v;
    if (!empty()) {
        root->in_order(v);        
    }
    return v;
}

template<typename T>
ArrayList<T> BinaryTree :: post_order() const {
    structures::ArrayList<T> v;
    if (!empty()) {
        root->post_order(v);
    }
    return v;
}

}  //  namespace structures

#endif /* BINARY_TREE_H */

