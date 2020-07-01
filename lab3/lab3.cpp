#include "lab3.hpp"


int_list_t::int_list_t() : s(0), first(nullptr), last(nullptr) {}; // O(1)

int_list_t::int_list_t(const int_list_t &other) : int_list_t() {
  node_t *temp_node = other.first;
  for (int i = 0; i < other.size(); ++i) {
    push_back(temp_node->value);
    temp_node = temp_node->next;
  }
}; // COPY $other list O(other.s)
int_list_t::int_list_t(size_t count) : int_list_t() {
  for (int i = 0; i < count; ++i) {
    push_back(i);
  }
};// create list $count s and fill it with increazing numbers
int_list_t::int_list_t(size_t count, int value) : s(0), first(nullptr), last(nullptr) {
  for (int i = 0; i < count; ++i) {
    push_back(value);
  }
}; // create list $count s and fill it with $value O($count)
int_list_t::~int_list_t() {
  clear();
}; // O(s)

int_list_t &int_list_t::operator=(const int_list_t &other) {
  if (&other != this) {
    clear();
    node_t *temp_node = other.first;
    for (int i = 0; i < other.size(); ++i) {
      push_back(temp_node->value);
      temp_node = temp_node->next;
    }
  }
  return *this;
}; // O(s + other.s())

int &int_list_t::operator[](size_t pos) {
  if (pos >= s) {
    throw std::out_of_range("Trying to get array item with index more than array size");
  }
  return get_node_by_pos(pos)->value;
}; // O(min($pos, s - $pos))
const int int_list_t::operator[](size_t pos) const {
  if (pos >= s) {
    throw std::out_of_range("Trying to get array item with index more than array size");
  }
  return get_node_by_pos(pos)->value;
}; // O(min($pos, s - $pos))

int &int_list_t::back() {
  if (empty()) {
    throw std::out_of_range("Trying to call 'back()' from empty array");
  }
  return last->value;
}; // last element O(1)
const int int_list_t::back() const {
  if (empty()) {
    throw std::out_of_range("Trying to call 'back()' from empty array");
  }
  return last->value;
}; // O(1)

int &int_list_t::front() {
  if (empty()) {
    throw std::out_of_range("Trying to call 'front()' from empty array");
  }
  return first->value;
}; // first element O(1)
const int int_list_t::front() const {
  if (empty()) {
    throw std::out_of_range("Trying to call 'front()' from empty array");
  }
  return first->value;
}; // O(1)

void int_list_t::clear() {
  if (!empty()) {
    node_t *temp_node = first;
    node_t *next_node = first->next;
    while (next_node) {
      delete temp_node;
      temp_node = next_node;
      next_node = temp_node->next;
    }
    delete temp_node;
    first = nullptr;
    last = nullptr;
    s = 0;
  }
}; // O(s)
size_t int_list_t::size() const {
  return s;
}; // O(1)
bool int_list_t::empty() const {
  return s == 0;
}; // O(1)

void int_list_t::insert(size_t pos, int new_val) {
  if (pos > s) {
    throw std::out_of_range("Trying to insert item into array with index more than array size");
  }
  node_t *new_node = new node_t(new_val);

  if (pos > s / 2) { // if new element if closer to the end
    // search for element with position $pos-1 to insert $new_val AFTER it because of situation where pos=s
    node_t *temp_node = get_node_by_pos(pos - 1);

    // bind $new_node with $temp_node and $temp_node->next
    new_node->set_next(temp_node->next);
    if (temp_node->next != nullptr) {  //needed to not throw exception in situation where pos=s
      temp_node->next->set_prev(new_node);
    }
    temp_node->set_next(new_node);
    new_node->set_prev(temp_node);
  } else {
    // search for element with position $pos to insert $new_val before it
    node_t *temp_node = get_node_by_pos(pos);

    // bind $new_node with $temp_node and $temp_node->prev
    if (!empty()) {
      new_node->set_prev(temp_node->prev);
      if (temp_node->prev != nullptr) {
        temp_node->prev->set_next(new_node);
      }
      temp_node->set_prev(new_node);
      new_node->set_next(temp_node);
    }
  }

  if (new_node->prev == nullptr) {
    first = new_node;
  }
  if (new_node->next == nullptr) {
    last = new_node;
  }
  ++s;
}; // insert element $new_val BEFORE element with index $pos O(min($pos, s - $pos))
void int_list_t::push_front(int new_val) {
  node_t *new_node = new node_t(new_val);
  if (!empty()) {
    new_node->set_next(first);
    first->set_prev(new_node);
  }
  first = new_node;
  if (empty()) {
    last = first;
  }
  ++s;
}; // O(1)
void int_list_t::push_back(int new_val) {
  node_t *new_node = new node_t(new_val);
  if (!empty()) {
    new_node->set_prev(last);
    last->set_next(new_node);
  }
  last = new_node;
  if (empty()) {
    first = last;
  }
  ++s;
}; // O(1)

void int_list_t::erase(size_t pos) {
  if (pos >= s) {
    throw std::out_of_range("Trying to erase item from array with index more than array size");
  }
  node_t *temp_node = get_node_by_pos(pos);
  if (temp_node->prev != nullptr) {
    temp_node->prev->set_next(temp_node->next);
  }
  if (temp_node->next != nullptr) {
    temp_node->next->set_prev(temp_node->prev);
  }
  delete temp_node;
  --s;
}; // remove element with index $pos O(min($pos, s - $pos))
void int_list_t::pop_front() {
  if (empty()) {
    throw std::out_of_range("Trying to call 'pop_front()' from empty array");
  }
  --s;
  if (empty()) {
    delete first;
    first = nullptr;
    last = nullptr;
  } else {
    node_t *temp_node = first->next;
    temp_node->set_prev(nullptr);
    delete first;
    first = temp_node;
  }

}; // O(1)
void int_list_t::pop_back() {
  if (empty()) {
    throw std::out_of_range("Trying to call 'pop_back()' from empty array");
  }
  --s;
  if (empty()) {
    delete last;
    last = nullptr;
    first = nullptr;
  } else {
    node_t *temp_node = last->prev;
    temp_node->set_next(nullptr);
    delete last;
    last = temp_node;
  }
}; // O(1)

int_list_t int_list_t::splice(size_t start_pos, size_t count) {
  if (start_pos + count >= s) {
    throw std::out_of_range("Trying to splice array with indexes more then array size");
  }
  if (count == 0) {
    throw std::out_of_range("Trying to splice into empty array");
  }
  node_t *start_temp_node = get_node_by_pos(start_pos);

  int_list_t res;
  res.push_back(start_temp_node->value);
  node_t *finish_temp_node = start_temp_node;
  // write next $count-1 values into $res;
  for (int i = 0; i < count - 1; ++i) {
    finish_temp_node = finish_temp_node->next;
    res.push_back(finish_temp_node->value);
  }

  // bind $start_temp_node->prev with $finish_temp_node->next
  if (finish_temp_node->next != nullptr) {
    finish_temp_node->next->set_prev(start_temp_node->prev);
  }
  if (start_temp_node->prev != nullptr) {
    start_temp_node->prev->set_next(finish_temp_node->next);
  }
  // deletes all nodes that have been spliced
  for (int i = 0; i < count - 1; ++i) {
    delete start_temp_node;
    start_temp_node = start_temp_node->next;
  }
  delete start_temp_node;
  s -= count;

  return res;
}; // splice part of list into result (not copy!) O($start_pos + $count)
int_list_t &int_list_t::merge(int_list_t &other) {
  if (this->empty()) {
    first = other.first;
  } else {
    last->next = other.first;
  }
  last = other.last;
  s += other.s;
  other.first = nullptr;
  other.last = nullptr;
  other.s = 0;
  return *this;
}; // merge two lists, after operation $other must be valid empty list O(1)

void int_list_t::reverse() {
  node_t *temp_node = first;
  node_t *next_node = first->next;
  for (int i = 0; i < s - 1; ++i) {
    temp_node->set_next(temp_node->prev);
    temp_node->set_prev(next_node);
    temp_node = next_node;
    next_node = next_node->next;
  } // after cycle temp_node = last, next_node = nullptr
  last->next = last->prev;
  last->prev = nullptr;
  last = first;
  first = temp_node;
}; // O(s)
void int_list_t::swap(int_list_t &other) {
  std::swap(s, other.s);
  std::swap(first, other.first);
  std::swap(last, other.last);
}; // O(1)

std::istream &operator>>(std::istream &stream, int_list_t &list) {
  int temp = 0;
  list.clear();
  while (stream >> temp) {
    list.push_back(temp);
  }
  return stream;
}

std::ostream &operator<<(std::ostream &stream, const int_list_t &list) {
  stream << '[';
  if (!list.empty()) {
    for (int i = 0; i < list.s - 1; ++i) {
      stream << list[i] << ", ";
    }
    stream << list[list.s - 1];
  }
  stream << ']';
  return stream;
}

int main(int argc, char **argv) {
  int_list_t list_of_numbers(5);
  std::cout << "list_of_numbers:                  " << list_of_numbers << std::endl;
  int_list_t empty_list;
  std::cout << "empty_list:                       " << empty_list << std::endl;

  int_list_t list_copied(list_of_numbers);
  std::cout << "list_copied:                      " << list_copied << std::endl;
  int_list_t empty_list_copied(empty_list);
  std::cout << "empty_list_copied:                " << empty_list_copied << std::endl;

  list_copied = list_of_numbers;
  std::cout << "list_copied after assignment:     " << list_copied << std::endl;
  int_list_t empty_list_assigned = empty_list;
  std::cout << "empty_list_assigned:              " << empty_list_assigned << std::endl;

  std::cout << "list_of_numbers.front():          " << list_of_numbers.front() << std::endl;
  std::cout << "list_of_numbers.back():           " << list_of_numbers.back() << std::endl;

  list_of_numbers.insert(3, 10);
  std::cout << "list_of_numbers after insert:     " << list_of_numbers << std::endl;
  list_of_numbers.push_front(-1);
  std::cout << "list_of_numbers after push_front: " << list_of_numbers << std::endl;
  list_of_numbers.push_back(5);
  std::cout << "list_of_numbers after push_back:  " << list_of_numbers << std::endl;

  list_of_numbers.erase(4);
  std::cout << "list_of_numbers after erase:      " << list_of_numbers << std::endl;
  list_of_numbers.pop_front();
  std::cout << "list_of_numbers after pop_front:  " << list_of_numbers << std::endl;
  list_of_numbers.pop_back();
  std::cout << "list_of_numbers after pop_back:   " << list_of_numbers << std::endl;

  int_list_t new_list = list_of_numbers.splice(1, 2);
  std::cout << "new_list after splice:            " << new_list << std::endl;
  std::cout << "list_of_numbers after splice:     " << list_of_numbers << std::endl;

  new_list.swap(list_of_numbers);
  std::cout << "new_list after swap:              " << new_list << std::endl;
  std::cout << "list_of_numbers after swap:       " << list_of_numbers << std::endl;

  new_list.reverse();
  std::cout << "new_list after reverse():         " << new_list << std::endl;

  list_of_numbers.merge(new_list);
  std::cout << "list_of_numbers after merge:      " << list_of_numbers << std::endl;
  std::cout << "new_list after merge:             " << new_list << std::endl;

  //int_list_t input_list;
  //std::cout << "Введите числа через пробел, для выхода из цикла нажмите Ctrl+D (*nux) или Ctrl+Z (Windows)" << std::endl;
  //std::cin >> input_list;
  //std::cout << input_list << std::endl;
  return 0;
}