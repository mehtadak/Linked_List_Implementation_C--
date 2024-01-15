#include<iostream>
#include<sstream>
#include<stdexcept>
#include<string>
#include <algorithm>

#include "algorithm.hpp"

SingleLink::SingleLink() : head_(nullptr), tail_(nullptr){}

SingleLink::SingleLink(int dat) {
  head_ = new Node(dat);
  tail_ = head_;
}

void SingleLink::append_back(int dat){
  Node* newNode = new Node(dat);
  if (head_ == nullptr){
    head_ = tail_ = newNode;
  } else {
    tail_ -> next_ = newNode;
    tail_ = newNode;
  }
}

std::ostream& operator<<(std::ostream &out, const SingleLink &s){
  Node* current = s.head_;
  while (current){
    out << current->data_;
    if (current->next_){
      out << ", ";
    }
    current = current->next_;
  }
  return out;
}

bool SingleLink::del(int val) {
    if (!head_) {return false;}

    if (head_->data_ == val) {
        Node* temp = head_;
        head_ = head_->next_;
        delete temp;
        if (!head_) {tail_ = nullptr;}
        return true;
    }

    Node* current = head_;
    while (current->next_) {
        if (current->next_->data_ == val) {
            Node* temp = current->next_;
            current->next_ = current->next_->next_;
            if (temp == tail_) {tail_ = current;}
            delete temp;
            return true;
        }
        current = current->next_;
    }
    return false;
}

Node& SingleLink::operator[](size_t index){
  Node* current = head_;
  for(size_t i = 0; i < index; ++i){
    if(!current){throw std::out_of_range("Index out of range");}
    current = current->next_;
  }
  if(!current){throw std::out_of_range("Index out of range");}
  return *current;
}

SingleLink::~SingleLink(){
  while(head_){
    Node* temp = head_;
    head_ = head_->next_;
    delete temp;
  }
  tail_ = nullptr;
}

SingleLink::SingleLink(const SingleLink &other) : head_(nullptr), tail_(nullptr) {
  Node* current = other.head_;
  while(current){
    append_back(current->data_);
    current = current->next_;
  }
}