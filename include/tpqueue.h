// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <iostream>
#include <string>

struct SYM {
  char ch;
  int prior;
};

template <typename T, int size>
class TPQueue {
 private:
  struct NODE {
    T data;
    NODE* next;
  };
  NODE* head;
  int members;
  NODE* create(T);

 public:
  TPQueue();
  void push(T);
  bool isFull();
  bool isEmpty();
  T pop();
  ~TPQueue();
};

template <typename T, int size>
TPQueue<T, size>::TPQueue():head(nullptr), members(0){}

template <typename T, int size>
typename TPQueue<T, size>::NODE* TPQueue<T, size>::create(T value) {
  NODE* temp = new NODE;
  temp->data.ch = value.ch;
  temp->data.prior = value.prior;
  temp->next = nullptr;
  return temp;
}

template <typename T, int size>
bool TPQueue<T, size>::isEmpty() {
  return head == nullptr;
}

template <typename T, int size>
bool TPQueue<T, size>::isFull() {
  return members == size;
}

template <typename T, int size>
void TPQueue<T, size>::push(T item) {
  bool flag = true;
  if (isFull())
    throw std::string("Full!");
  else if (isEmpty()) {
    head = create(item);
    members++;
  } else {
    NODE* temp = head;
    if (temp->data.prior < item.prior) {
      NODE* copy = create(item);
      copy->next = head;
      head = copy;
      members++;
      flag = false;
    } else if (flag) {
      while (temp->next && flag) {
        if (temp->data.prior >= item.prior && temp->next->data.prior < item.prior) {
          NODE* copy = create(item);
          copy->next = temp->next;
          temp->next = copy;
          members++;
          flag = false;
        }
        temp = temp->next;
      }
    }
    if (flag) {
      NODE* copy = create(item);
      temp->next = copy;
    }
  }
}

template <typename T, int size>
T TPQueue<T, size>::pop() {
    if (isEmpty()) throw std::string("Empty");
    NODE* temp = head->next;
    T copy = head->data;
    delete head;
    members--;
    head = temp;
    return copy;
}

template <typename T, int size>
TPQueue<T, size>::~TPQueue() {
    if (isEmpty()) throw std::string("Empty");
    while (head) {
    NODE* temp = head->next;
    delete head;
    members--;
    head = temp;
    }
}

#endif  // INCLUDE_TPQUEUE_H_
