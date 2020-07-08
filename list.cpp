#include "list.h"
#include <stdexcept>

List::List() = default;

List::~List() { clear(); }

bool List::empty() const { return m_first == nullptr; }

void List::push_back(const data_t &value) {
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

void List::push_front(const data_t &value) {
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

void List::pop_back() {
    if (m_last == nullptr) {
        throw std::runtime_error("Cannot call pop_back on empty list!");
    }
    auto *tmp = m_last->prev;
    delete m_last;
    m_last = tmp;
    m_size--;
}

void List::pop_front() {
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

void List::remove(Item *item)
{
    Element* copy = m_first;
    if(!copy) return;

    while(copy) {
        if(copy->data == item) {
            //will be deleted in the end
            Element* e = copy;
            //check for potential nullptrs
            //only one element, is now gone
            if(copy->next == nullptr && copy->prev == nullptr) {
                m_first = nullptr;
                m_last = nullptr;
            }
            //prev is now new last element
            else if(copy->next == nullptr)  {
                m_last = copy->prev;
                m_last->next = nullptr;
            }
            //prev is nullptr; next element is new first
            else if(copy->prev == nullptr) {
                m_first = copy->next;
                m_first->prev = nullptr;
            }else {
                //prev pointer of following element is previous element
                copy->next->prev = copy->prev;
                //next pointer of previous element is next element
                copy->prev->next = copy->next;
            }
            copy = copy->next;
            delete e;
        } else {
            copy = copy->next;
        }
    }
}

void List::clear() {
    auto *current = m_first;
    while (current != nullptr) {
        auto *tmp = current;
        current = current->next;
        delete tmp;
    }
}

List::size_t List::size() const { return m_size; }

List::Element *List::createElement(const data_t &data) {
    auto *tmp = new Element;
    tmp->data = data;
    return tmp;
}

List::iterator::iterator(Element* e) : element(e) {

}

Item*& List::iterator::operator*() {
    if(element == nullptr) throw std::runtime_error("cant deref invalid iterator");
    return element->data;
}

List::iterator& List::iterator::operator++() {
    if(element == nullptr) {
        throw std::runtime_error("cant increment on illegal iterator");
    }
    element = element->next;
    return *this;
}

List::iterator& List::iterator::operator--() {
    if(element->prev == nullptr) {
        throw std::runtime_error("cant decrement begin iterator");
    }
    element = element->prev;
    return *this;
}

bool List::iterator::operator==(const iterator& i) {
    return element == i.element;
}


bool List::iterator::operator!=(const iterator &i) {
    return element != i.element;
}
