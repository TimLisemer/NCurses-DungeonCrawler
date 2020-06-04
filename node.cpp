#include "node.h"
#include <sstream>
#include <vector>

template <> std::string Node::get(const std::string &key) const {
  auto item = items.find(key);
  if (item == items.end())
    throw std::out_of_range("No attribute " + key + " found!");
  return item->second;
}

template <> double Node::get(const std::string &key) const {
  auto item = items.find(key);
  if (item == items.end())
    throw std::out_of_range("No attribute " + key + " found!");
  return std::stod(item->second);
}

template <> long Node::get(const std::string &key) const {
  auto item = items.find(key);
  if (item == items.end())
    throw std::out_of_range("No attribute " + key + " found!");
  return std::stol(item->second);
}

template <> int Node::get(const std::string &key) const {
  auto item = items.find(key);
  if (item == items.end())
    throw std::out_of_range("No attribute " + key + " found!");
  return std::stoi(item->second);
}

template <> char Node::get(const std::string &key) const {
  auto item = items.find(key);
  if (item == items.end())
    throw std::out_of_range("No attribute " + key + " found!");
  return item->second.at(0);
}

template <> std::vector<int> Node::get(const std::string &key) const {
  auto item = items.find(key);
  if (item == items.end())
    throw std::out_of_range("No attribute " + key + " found!");
  std::stringstream list;
  list << item->second;
  std::vector<int> tmp;
  if (list.str().empty())
    return tmp;
  while (!list.eof()) {
    int val;
    list >> val;
    tmp.push_back(val);
  }
  return tmp;
}

void Node::set(const std::string &key, const std::vector<int> &value) {
  std::stringstream tmp;
  for (int i = 0; i < static_cast<int>(value.size()) - 1; i++) {
    tmp << value.at(i) << " ";
  }
  if (value.size() > 0)
    tmp << value.back();

  items[key] = tmp.str(); //.substr(0, tmp.str().size() - 1);
}

bool Node::exists(const std::string &key) const {
  return items.find(key) != items.end();
}

void Node::set(const std::string &key, const std::string &value) {
  items[key] = value;
}

void Node::set(const std::string &key, char c) { items[key] = c; }

std::istream &operator>>(std::istream &in, Node &node) {
  std::string line;
  getline(in, line);

  node.name = line;
  while (in.peek() == '\t') {
    getline(in, line);

    // Remove tab
    line = line.substr(line.find_first_of("-") + 1);

    // Remove spaces
    while (line.at(0) == ' ')
      line = line.substr(1);

    // Extract the key
    std::string key = line.substr(0, line.find_first_of(":"));

    // Remove trailing spaces from key
    while (key.back() == ' ')
      key.pop_back();

    // Extract value
    std::string value = line.substr(line.find_first_of(":") + 1);

    // Remove spaces from value
    while (value.at(0) == ' ')
      value = value.substr(1);

    // Remove trailing spaces from value
    while (value.back() == ' ')
      value.pop_back();

    node.items[key] = value;
  }
  return in;
}

std::ostream &operator<<(std::ostream &out, const Node &node) {
  out << node.name << "\n";
  for (const auto &item : node.items) {
    out << "\t- " << item.first << ": " << item.second << "\n";
  }
  return out;
}
