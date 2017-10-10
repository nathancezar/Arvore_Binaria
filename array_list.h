// Copyright [2017] <Nathan Cezar Cardoso>
#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {
    /*!
    *  início da classe ArrayList
    */
template<typename T>
class ArrayList {
 public:
    /*!
    *  construtor sem parâmetros
    */
    ArrayList();
   /*!
    *  construtor com parâmetro de tamanho
    */
    explicit ArrayList(std::size_t max_size);
    /*!
    *  Destrutor
    */
    ~ArrayList();
    /*!
    *  Limpar a lista
    */
    void clear();
    /*!
    *  inserir no fim
    */
    void push_back(const T& data);
    /*!
    *  inserir no inicio
    */
    void push_front(const T& data);
    /*!
    *  inserir na posição
    */
    void insert(const T& data, std::size_t index);
    /*!
    *  inserir em ordem
    */
    void insert_sorted(const T& data);
    /*!
    *  retirar da posição
    */
    T pop(std::size_t index);
    /*!
    *  retirar do fim
    */
    T pop_back();
    /*!
    *  retirar do início
    */
    T pop_front();
    /*!
    *  remover da lista
    */
    void remove(const T& data);
    /*!
    *  lista cheia
    */
    bool full() const;
    /*!
    *  lista vazia
    */
    bool empty() const;
    /*!
    *  verificar se contem na lista
    */
    bool contains(const T& data) const;
    /*!
    *  retorna a posição de um dado, caso ele exista na lista
    */
    std::size_t find(const T& data) const;
    /*!
    *  retorna o tamanho atual da lista
    */
    std::size_t size() const;
    /*!
    *  retorna o tamanho máximo da lista
    */
    std::size_t max_size() const;
    /*!
    *  verifica se o index passado está dentro dos limites, caso positivo retorna o dado nesta posição
    */
    T& at(std::size_t index);
    /*!
    *  retorna o dado na posição, sem verificar se o índex está correto
    */
    T& operator[](std::size_t index);
    /*!
    *  verifica o index e retorna o endereço de memória do dado
    */
    const T& at(std::size_t index) const;
    /*!
    *  retorna o endereço de memória do dado
    */
    const T& operator[](std::size_t index) const;

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;
    static const auto DEFAULT_MAX = 10u;
};  //  Fim da Classe ArrayList

template<typename T>
ArrayList<T> :: ArrayList() {
    max_size_ = DEFAULT_MAX;
    size_ = -1;
    contents = new T[max_size_];
}

template<typename T>
ArrayList<T> :: ArrayList(std::size_t  max_size) {
    max_size_ = max_size;
    size_ = -1;
    contents = new T[max_size_];
}

template<typename T>
ArrayList<T> :: ~ArrayList() {
    delete[] contents;
}

template<typename T>
void ArrayList<T> :: clear() {
    size_ = -1;
}

template<typename T>
void ArrayList<T> :: push_back(const T& data) {
    insert(data, size_+1);
}

template<typename T>
void ArrayList<T> :: push_front(const T& data) {
    insert(data, 0);
}

template<typename T>
void ArrayList<T> :: insert(const T& data, std::size_t index) {
    if (full())
        throw std :: out_of_range("Full");
    if (index > (size_ +1) || index < 0)
        throw std :: out_of_range("Incorrect Index");
    size_++;
    for (int i = size_; i > index; i--) {
        contents[i] = contents[i - 1];
    }
    contents[index] = data;
}

template<typename T>
void ArrayList<T> :: insert_sorted(const T& data) {
    if (full())
        throw std :: out_of_range("Full");
    int current = 0;
    for (int i = 0; i < size_; i++) {
        if (data > contents[i]) {
            current++;
        }
    }
    insert(data, current);
}

template<typename T>
T ArrayList<T> :: pop(std :: size_t index) {
    T data;
    if (index > size_ || index < 0)
        throw std :: out_of_range("Incorrect Index");
    if (empty())
        throw std :: out_of_range("Empty");
    data = contents[index];
    for (int i = index; i < size_; i++) {
        contents[i] = contents[i + 1];
    }
    size_--;
    return data;
}

template<typename T>
T ArrayList<T> :: pop_back() {
    return pop(size_);
}

template<typename T>
T ArrayList<T> :: pop_front() {
    return pop(0);
}

template<typename T>
void ArrayList<T> :: remove(const T& data) {
    if (empty())
        throw std :: out_of_range("Empty");
    pop(find(data));
}

template<typename T>
size_t ArrayList<T> :: find(const T& data) const {
    if (empty())
        throw std :: out_of_range("Empty");
    for (int i = 0; i < size_+1; i++) {
        if (contents[i] == data)
            return i;
    }
    return (size_ + 1);
}

template<typename T>
bool ArrayList<T> ::  full() const {
    return (size_ == (max_size_ - 1));
}

template<typename T>
bool ArrayList<T> :: empty() const {
    return (size_ == -1);
}

template<typename T>
bool ArrayList<T> :: contains(const T& data) const {
    return  find(data) != (size_ + 1);
}

template<typename T>
size_t ArrayList<T> :: size() const {
    return size_ + 1;
}

template<typename T>
size_t ArrayList<T> :: max_size() const {
    return max_size_;
}

template<typename T>
T& ArrayList<T> :: at(size_t index) {
    if ((index > size_) || index < 0)
        throw std :: out_of_range("Incorrect Index");
    return contents[index];
}

template<typename T>
T& ArrayList<T> :: operator[](size_t index) {
    return at(index);
}

template<typename T>
const T& ArrayList<T> :: at(size_t index) const {
    return at(index);
}

template<typename T>
const T& ArrayList<T> :: operator[](size_t index) const {
    return at(index);
}

}  //  namespace structures

#endif