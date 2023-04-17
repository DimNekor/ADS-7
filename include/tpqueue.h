// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <iostream>
#include <string>

struct SYM {
  char ch;
  int prior;
};

template <typename T>
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
  bool isEmpty();
  T pop();
  ~TPQueue();
};

template <typename T>
TPQueue<T>::TPQueue():head(nullptr), members(0) {}

template <typename T>
typename TPQueue<T>::NODE* TPQueue<T>::create(T value) {
  NODE* temp = new NODE;
  temp->data.ch = value.ch;
  temp->data.prior = value.prior;
  temp->next = nullptr;
  return temp;
}

template <typename T>
bool TPQueue<T>::isEmpty() {
  return head == nullptr;
}

template <typename T>
void TPQueue<T>::push(T item) {
  bool flag = true;
  if (isEmpty()) {
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
        if (temp->data.prior >= item.prior &&
            temp->next->data.prior < item.prior) {
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

template <typename T>
T TPQueue<T>::pop() {
    if (isEmpty()) throw std::string("Empty");
    NODE* temp = head->next;
    T copy = head->data;
    delete head;
    members--;
    head = temp;
    return copy;
}

template <typename T>
TPQueue<T>::~TPQueue() {
    if (isEmpty()) throw std::string("Empty");
    while (head) {
    NODE* temp = head->next;
    delete head;
    members--;
    head = temp;
    }
}

#endif  // INCLUDE_TPQUEUE_H_
