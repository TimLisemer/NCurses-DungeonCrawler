#include "list.h"
#include <stdexcept>
#include "item.h"
#include <string>


//Class List
List::List() = default;

List::~List() { clear(); }

bool List::empty() const { return m_first == nullptr; }

void List::pushBack(const data_t &value) {
  if (m_first == nullptr) {
    m_first = createElement(value);
    m_first->prev = nullptr;
    m_first->next = nullptr;
    m_last = m_first;
  } else {
    auto *tmp = createElement(value);
    tmp->next = nullptr;
    tmp->prev = m_last;
    m_last->next = tmp;
    m_last = tmp;
  }
  m_size++;
}

void List::pushFront(const data_t &value) {
  if (m_first == nullptr) {
    m_first = createElement(value);
    m_first->prev = nullptr;
    m_first->next = nullptr;
    m_last = m_first;
  } else {
    auto *tmp = createElement(value);
    tmp->next = m_first;
    tmp->prev = nullptr;
    m_first->prev = tmp;
    m_first = tmp;
  }
  m_size++;
}

void List::popBack() {
  if (m_last == nullptr) {
    throw std::runtime_error("Cannot call pop_back on empty list!");
  }
  auto *tmp = m_last->prev;
  delete m_last;
  m_last = tmp;
  m_size--;
}

void List::popFront() {
  if (m_first == nullptr) {
    throw std::runtime_error("Cannot call pop_front on empty list!");
  }
  auto *tmp = m_first->next;
  delete m_first;
  m_first = tmp;
  m_size--;
}

const data_t &List::front() const {
  if (m_first == nullptr) {
    throw std::runtime_error("List is empty!");
  }
  return m_first->data;
}

const data_t &List::back() const {
  if (m_last == nullptr) {
    throw std::runtime_error("List is empty!");
  }
  return m_last->data;
}

data_t &List::front() {
  if (m_first == nullptr) {
    throw std::runtime_error("List is empty!");
  }
  return m_first->data;
}

data_t &List::back() {
  if (m_last == nullptr) {
    throw std::runtime_error("List is empty!");
  }
  return m_last->data;
}

void List::clear() {
  auto *current = m_first;
  while (current != nullptr) {
    auto *tmp = current;
    current = current->next;
    delete tmp;
  }
}


void List::remove(data_t &data) {
    Node* current = m_first;
    Node* tmp = nullptr;
    while (current->next != nullptr) {
        // remove first element
        if (current->data == data) {
            m_first->next->prev = nullptr;
            m_first = current->next;
            tmp = current;
            current = current->next;
            delete tmp;
        } else if (current->next->data == data) {

            if (current->next->next == nullptr) {
                tmp = current->next;
                current->next = nullptr;
                m_last = current;

            } else {
                current->next->next->prev = current;
                tmp = current->next;
                current->next = current->next->next;
            }
            delete tmp;
        } else {
            current = current->next;
        }
    }

    if (current->data == data) {
        tmp = m_first;
        m_first = current->next;
        delete tmp;
    }
}

data_t& List::operator[](const size_t &m_node){
    auto* tmp = m_first;
    for(size_t i = 0; i < m_node; i++){
        tmp = tmp->next;
    }
    return tmp->data;
}

List::size_t List::getSize() const { return m_size; }

List::Node *List::createElement(const data_t &data) {
  auto *tmp = new Node;
  tmp->data = data;
  return tmp;
}

//Class Iterator
List::Iterator::Iterator(List* l, Node* n):m_list(l), m_node(n){

}


List::Iterator& List::Iterator::operator++(){
    if(m_node == nullptr){
    throw std::out_of_range("Out Of Range, no next");
    }
    m_node = m_node->next;
    return *this;
}

List::Iterator& List::Iterator::operator++(int){
    if(m_node == nullptr){
    throw std::out_of_range("Out Of Range, no next");
    }
    m_node = m_node->next;
    return *this;
}

List::Iterator& List::Iterator::operator--(){
    if(m_node == nullptr){
        throw std::out_of_range("Out of Range, no prev");
    }
    m_node = m_node->prev;
    return *this;
}

List::Iterator& List::Iterator::operator--(int){
    if(m_node == nullptr){
        throw std::out_of_range("Out of Range, no prev");
    }
    m_node = m_node->prev;
    return *this;
}


Item*& List::Iterator::operator*(){
    if(m_node!=nullptr){
        return m_node->data;
    }else{
        throw std::out_of_range("No Pointer refernce existing!");
    }

}

bool List::Iterator::operator==(const Iterator &rhs){
    if(rhs.m_node == m_node && rhs.m_list == m_list){
        return true;
    }
    return false;
}


bool List::Iterator::operator!=(const Iterator &rhs){
    if(rhs.m_node == m_node && rhs.m_list == m_list){
        return false;
    }
    return true;
}
