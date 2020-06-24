#ifndef LIST_H
#define LIST_H
#include <string>

class Item;

const std::string ERR_PLUS_END = "Can't call ++ on end iterator!";
const std::string ERR_MINUS_END = "Can't call -- on end iterator!";
const std::string ERR_MINUS_BEGIN = "Can't call -- on begin iterator!";
const std::string ERR_DEREFERENCE_END = "Can't dereference end iterator!";

class List {
public:
   using SizeT = unsigned long;

   class Iterator {
   private:
      List* list;
      SizeT index;

      bool isIndexAtEnd() const;

   public:
      Iterator(List* list, const SizeT& index);

      Iterator& operator++();
      Iterator& operator--();
      bool operator==(const Iterator& rhs) const;
      bool operator!=(const Iterator& rhs) const;
      Item* operator*() const;
   };

   Item* &operator[](const SizeT& index);

   List() = default;
   ~List();

   bool isEmpty() const;

   void pushBack(Item* item);
   void pushFront(Item* item);

   void popBack();
   void popFront();

   const Item* getFront() const;
   const Item* getBack() const;

   Item* getFront();
   Item* getBack();

   void clear();

   bool remove(Item* item);

   SizeT getSize() const;

   Iterator begin();
   Iterator end();

private:
   struct Node {
      Item* item = nullptr;
      Node* next = nullptr;
      Node* prev = nullptr;
   };

   Node* createElement(Item* data);

   Node* first = nullptr;
   Node* last = nullptr;

   SizeT size = 0;
};

#endif // LIST_H
