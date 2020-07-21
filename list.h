#ifndef LIST_H
#define LIST_H
#include <iterator>

class Item;

using data_t=Item*;


class List {

using size_t = unsigned long;

private:
    struct Node{
        data_t data;
        Node* next = nullptr;
        Node* prev = nullptr;
    };

    static Node *createElement(const data_t &data);


    Node* m_first = nullptr;
    Node* m_last = nullptr;

    size_t m_size = 0;

public:

    List();
   ~List();

    bool empty() const;
    void pushBack(const data_t& value);
    void pushFront(const data_t& value);

    void popBack();
    void popFront();

    data_t &operator[](const size_t& m_node);
    const data_t& back() const;
    const data_t& front() const;

    data_t& front();
    data_t& back();

    void clear();

    // @TODO: Remove as Bool
    void remove(data_t& data);

    size_t getSize() const;


    class Iterator{
    private:
        List* m_list;
        Node* m_node;
public:
        Iterator(List* l, Node* n);
        virtual ~Iterator(){};
        Iterator& operator++();
        Iterator& operator++(int);
        Iterator& operator--();
        Iterator& operator--(int);
        Item*& operator*();
        bool operator==(const Iterator& rhs);
        bool operator!=(const Iterator& rhs);
    };

    Iterator begin(){
        return{
            this, m_first
        };
    }

    Iterator end(){
        return{
            this, nullptr
        };
    }

};


#endif // LIST_H

