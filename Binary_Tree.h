  //  Copyright Nathan Cezar Cardoso [2017]

#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <cstdint>
#include <stdexcept>
#include "array_list.h"

namespace structures {
    /*!
    *  Início da Classe Árvore Binária
    */
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
        explicit Node(const T& dataP) {
            data = dataP;
            left = nullptr;
            right = nullptr;
        }

        ~Node() {
            delete left;
            delete right;
        }

        void insert(const T& data_) {
            Node* novoNodo;
            if (data_ < this->data) {
                if (this->left == nullptr) {
                    novoNodo = new Node(data_);
                    this->left = novoNodo;
                    if (this->left == nullptr)
                        throw std::out_of_range("Full");
                } else {
                    this->left->insert(data_);
                }
            } else {
                if (this->right == nullptr) {
                    novoNodo = new Node(data);
                    this->right = novoNodo;
                    if (this->right == nullptr)
                        throw std::out_of_range("Full");
                } else {
                    this->right->insert(data);
                }
            }
        }

        bool remove(const T& data_) {
                if (this == nullptr) {
                    return false;
                } else {
                    if (data_ < this->data) {
                        this->left->remove(data_);
                    } else if (data_ > this->data) {
                        this->right->remove(data_);
                    } else {
                        if (this->right != nullptr && this->left != nullptr) {
                            this->data = minimo(this->right);
                            this->right->remove(this->data);
                        } else {
                            if (this->right != nullptr) {
                                this->data = right->data;
                                return right->remove(right->data);
                            } else if (this->left != nullptr) {
                                this->data = left->data;
                                return left->remove(left->data);
                            } else {
                                delete this;
                                return true;
                            }
                        }
                    }
                }
                return false;
            }

        T minimo(const Node* ptr) {
            while (this->left != nullptr) {
                this->minimo(this->left);
            }
            return this->data;
        }

        bool contains(const T& data_) const {
            if (data_ == data) {
                return true;
            } else {
                if ((right != nullptr) && (data_ > data)) {
                    return right->contains(data_);
                } else if ((left != nullptr) && (data_ < data)) {
                    return left->contains(data_);
                }
            }
            return false;
        }

        void pre_order(ArrayList<T>& v) const {
            v.push_back(data);
            if (left != nullptr) {
                left->pre_order(v);
            }
            if (right != nullptr) {
                right->pre_order(v);
            }
        }

        void in_order(ArrayList<T>& v) const {
            if (left != nullptr) {
                left->in_order(v);
            }
            v.push_back(data);
            if (right != nullptr) {
                right->in_order(v);
            }
        }

        void post_order(ArrayList<T>& v) const {
            if (left != nullptr) {
                left->post_order(v);
            }
            if (right != nullptr) {
                right->post_order(v);
            }
            v.push_back(data);
        }

        T data;
        Node* left;
        Node* right;
    };

    Node* root = nullptr;
    std::size_t size_ = 0;
};
    /*!
    *  Destrutor
    */
template<typename T>
BinaryTree<T> :: ~BinaryTree() {
    size_ = 0;
    delete root;
}
    /*!
    *  insere um dado na árvore
    */
template<typename T>
void BinaryTree<T> :: insert(const T& data) {
    if (empty()) {
        root = new Node(data);
    } else {
        root->insert(data);
    }
    size_++;
}
    /*!
    *  remove um dado da árvore
    */
template<typename T>
void BinaryTree<T> :: remove(const T& data) {
    if (!empty()) {
        root->remove(data);
        size_--;
    }
}
    /*!
    *  verifica de contem um dado na árvore
    */
template<typename T>
bool BinaryTree<T> :: contains(const T& data) const {
    if (!empty()) {
        return root->contains(data);
    }
    return false;
}
    /*!
    *  verifica se a árvore está vazia
    */
template<typename T>
bool BinaryTree<T> :: empty() const {
    return (size() == 0);
}
    /*!
    *  retorna o tamanho da árvore
    */
template<typename T>
std::size_t BinaryTree<T> :: size() const {
    return size_;
}
    /*!
    *  adiciona um dado em pré ordem
    */
template<typename T>
ArrayList<T> BinaryTree<T> :: pre_order() const {
    structures::ArrayList<T> v{size()};
    if (!empty()) {
        root->pre_order(v);
    }
    return v;
}
    /*!
    *  adiciona um dado em ordem
    */
template<typename T>
ArrayList<T> BinaryTree<T> :: in_order() const {
    structures::ArrayList<T> v{size()};
    if (!empty()) {
        root->in_order(v);
    }
    return v;
}
    /*!
    *  adiciona um dado em pós ordem
    */
template<typename T>
ArrayList<T> BinaryTree<T> :: post_order() const {
    structures::ArrayList<T> v{size()};
    if (!empty()) {
        root->post_order(v);
    }
    return v;
}

}  //  namespace structures

#endif /* BINARY_TREE_H */
