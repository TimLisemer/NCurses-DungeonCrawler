#include "list.h"
#include <stdexcept>
#include "item.h"

bool List::Iterator::isIndexAtEnd() const {
   return index >= list->size;
}

List::Iterator::Iterator(List* list, const SizeT& index)
   : list(list), index(index) {}

List::Iterator& List::Iterator::operator++() {
   if(isIndexAtEnd()) {
      throw std::runtime_error(ERR_PLUS_END);
   }
   index++;
   return *this;
}

List::Iterator& List::Iterator::operator--() {
   if(index == 0) {
      throw std::runtime_error(ERR_MINUS_BEGIN);
   }
   if(isIndexAtEnd()) {
      throw std::runtime_error(ERR_MINUS_END);
   }
   index--;
   return *this;
}

bool List::Iterator::operator==(const Iterator& rhs) const {
   return this->list == rhs.list && this->index == rhs.index;
}

bool List::Iterator::operator!=(const Iterator& rhs) const {
   return !(*this == rhs);
}

Item* List::Iterator::operator*() const {
   if(isIndexAtEnd()) {
      throw std::runtime_error(ERR_MINUS_END);
   }

   return (*list)[index];
}

// ReSharper disable once CppMemberFunctionMayBeConst
Item*& List::operator[](const SizeT& index) {
   auto* tmp = first;
   for(auto i = 0; i < index; ++i) {
      tmp = tmp->next;
   }

   return tmp->item;
}

List::~List() {
   clear();
}

bool List::isEmpty() const {
   return first == nullptr;
}

void List::pushBack(Item* item) {
   if(first == nullptr) {
      first = createElement(item);
      first->prev = nullptr;
      first->next = nullptr;
      last = first;
   } else {
      auto* tmp = createElement(item);
      tmp->next = nullptr;
      tmp->prev = last;
      last->next = tmp;
      last = tmp;
   }
   size++;
}

void List::pushFront(Item* item) {
   if(first == nullptr) {
      first = createElement(item);
      first->prev = nullptr;
      first->next = nullptr;
      last = first;
   } else {
      auto* tmp = createElement(item);
      tmp->next = first;
      tmp->prev = nullptr;
      first->prev = tmp;
      first = tmp;
   }
   size++;
}

void List::popBack() {
   if(last == nullptr) {
      throw std::runtime_error("Cannot call pop_back on empty list!");
   }
   auto* tmp = last->prev;
   delete last;
   last = tmp;
   size--;
}

void List::popFront() {
   if(first == nullptr) {
      throw std::runtime_error("Cannot call pop_front on empty list!");
   }
   auto* tmp = first->next;
   delete first;
   first = tmp;
   size--;
}

const Item* List::getFront() const {
   if(first == nullptr) {
      throw std::runtime_error("List is empty!");
   }
   return first->item;
}

const Item* List::getBack() const {
   if(last == nullptr) {
      throw std::runtime_error("List is empty!");
   }
   return last->item;
}

Item* List::getFront() {
   if(first == nullptr) {
      throw std::runtime_error("List is empty!");
   }
   return first->item;
}

Item* List::getBack() {
   if(last == nullptr) {
      throw std::runtime_error("List is empty!");
   }
   return last->item;
}

// ReSharper disable once CppMemberFunctionMayBeConst
void List::clear() {
   auto* current = first;
   while(current != nullptr) {
      auto* tmp = current;
      current = current->next;
      //delete tmp->item; // TODO: wtf
      delete tmp;
   }
}

// ReSharper disable once CppMemberFunctionMayBeConst
bool List::remove(Item* item) {
   auto* tmp = first;
   while(tmp) {
      if(tmp->item == item) {
         if(tmp->prev) {
            tmp->prev->next = tmp->next;
            if(tmp->next) {
               tmp->next->prev = tmp->prev;
            } else {
               last = tmp->prev;
            }
         } else {
            first = tmp->next;
            if(tmp->next) {
               tmp->next->prev = nullptr;
            } else {
               last = tmp->prev;
            }
         }

         delete tmp;
         size--;
         return true;
      }
      tmp = tmp->next;
   }

   return false;
}

List::SizeT List::getSize() const {
   return size;
}

List::Iterator List::begin() {
   return {this, 0};
}

List::Iterator List::end() {
   return {this, size};
}

List::Node* List::createElement(Item* data) {
   auto* tmp = new Node;
   tmp->item = data;
   return tmp;
}
