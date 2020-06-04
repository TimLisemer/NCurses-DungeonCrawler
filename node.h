#ifndef NODE_H
#define NODE_H

// BEGIN
#include <iostream>
#include <map>
#include <string>
#include <typeinfo>
#include <vector>

struct Node {
  std::string name;
  std::map<std::string, std::string> items;

  template <typename T> T get(const std::string &key) const {

    throw std::runtime_error(
        std::string("Datatype ") + typeid(T).name() +
        " not yet supported (Datatype name may be mangled). Key was " + key);
  }

  template <typename T> void set(const std::string &key, T value) {
    items[key] = std::to_string(value);
  }

  void set(const std::string &key, const std::string &value);
  void set(const std::string &key, char c);
  void set(const std::string &key, const std::vector<int> &value);

  bool exists(const std::string &key) const;

  friend std::ostream &operator<<(std::ostream &out, const Node &node);
  friend std::istream &operator>>(std::istream &in, Node &node);
};

#endif // NODE_H
