#pragma once

#include <iostream>

#include <iostream>

class int_list_t {
private:
  struct node_t {
    int value;
    struct node_t *next;
    struct node_t *prev;

    node_t(int new_value) :
        value(new_value),
        next(nullptr),
        prev(nullptr) {};

    void set_prev(node_t *new_prev) {
      prev = new_prev;
    };

    void set_next(node_t *new_next) {
      next = new_next;
    };
  };

public:
  int_list_t(); // O(1)

  int_list_t(const int_list_t &other); // COPY $other list O(other.size)
  int_list_t(size_t count);// create list $count s and fill it with increazing numbers
  int_list_t(size_t count, int value); // create list $count s and fill it with $value O($count)
  ~int_list_t(); // O(size)

  int_list_t &operator=(const int_list_t &other); // O(s + other.size())

  int &operator[](size_t pos); // O(min($pos, s - $pos))
  const int operator[](size_t pos) const; // O(min($pos, s - $pos))

  int &back(); // last element O(1)
  const int back() const; // O(1)

  int &front(); // first element O(1)
  const int front() const; // O(1)

  void clear(); // O(size)
  size_t size() const; // O(1)
  bool empty() const; // O(1)

  void insert(size_t pos, int new_val); // insert element $new_val BEFORE element with index $pos O(min($pos, s - $pos))
  void push_front(int new_val); // O(1)
  void push_back(int new_val); // O(1)

  void erase(size_t pos); // remove element with index $pos O(min($pos, s - $pos))
  void pop_front(); // O(1)
  void pop_back(); // O(1)

  int_list_t
  splice(size_t start_pos, size_t count); // splice part of list into result (not copy!) O($start_pos + $count)
  int_list_t &merge(int_list_t &other); // merge two lists, after operation $other must be valid empty list O(1)

  void reverse(); // O(size)
  void swap(int_list_t &other); // O(1)

  friend std::istream &operator>>(std::istream &stream, int_list_t &list); // O(size)
  friend std::ostream &operator<<(std::ostream &stream, const int_list_t &list); // O(size)

private:
  node_t *first;
  node_t *last;
  size_t s;

  node_t *get_node_by_pos(size_t pos) {
    if (pos >= s) {
      return nullptr;
    }
    if (pos > s / 2) {
      node_t *temp_node = last;
      for (int i = s - 1; i > pos; --i) {
        temp_node = temp_node->prev;
      }
      return temp_node;
    } else {
      node_t *temp_node = first;
      for (int i = 0; i < pos; ++i) {
        temp_node = temp_node->next;
      }
      return temp_node;
    }
  }

  node_t *get_node_by_pos(size_t pos) const {
    if (pos >= s) {
      return nullptr;
    }
    if (pos > s / 2) {
      node_t *temp_node = last;
      for (int i = s - 1; i > pos; --i) {
        temp_node = temp_node->prev;
      }
      return temp_node;
    } else {
      node_t *temp_node = first;
      for (int i = 0; i < pos; ++i) {
        temp_node = temp_node->next;
      }
      return temp_node;
    }
  }
};
