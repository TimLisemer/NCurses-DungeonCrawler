#ifndef LIST_H
#define LIST_H
#include <iterator>
#include "item.h"

class Item;

using data_t = Item*;

class List {
private:
    using size_t = unsigned long;
    struct Element {
        data_t data;
        Element *next = nullptr;
        Element *prev = nullptr;
    };

    static Element *createElement(const data_t &data);

    Element *m_first = nullptr;
    Element *m_last = nullptr;

    size_t m_size = 0;

public:
    class iterator {
    public:
        //constructs the iterators
        iterator(Element* e);

        iterator& operator++();
        iterator& operator--();
        Item*& operator*();
        bool operator==(const iterator& i);
        bool operator!=(const iterator& i);

    private:
        Element* element;

    };

    List();
    ~List();

    bool empty() const;

    void push_back(const data_t &value);
    void push_front(const data_t &value);

    void pop_back();
    void pop_front();

    const data_t &front() const;
    const data_t &back() const;

    data_t &front();
    data_t &back();

    void remove(Item *item);

    void clear();

    size_t size() const;

    iterator begin() { return iterator(m_first); }

    iterator end() {
        if(m_last) return iterator(m_last->next);
        return nullptr;
    }

};

#endif // LIST_H
