#pragma once

#include "dynamic_array.hpp"

namespace ds {
  
template<typename T>
class stack {
public:
  // Construction and Destruction
  stack();
  stack stack(const stack& other);
  stack stack(stack&& other);
  ~stack();

  // Operator overloads
  stack& operator=(const stack& other);
  stack& operator=(stack&& other);
};

// IMPLEMENTATION
template<typename T>
stack::stack() {
}


template<typename T>
stack 
stack::stack(const stack& other) {
}

template<typename T>
stack 
stack::stack(stack&& other) {
}


template<typename T>
~stack::stack() {
}

stack& stack::operator=(const stack& other){
}

stack& stack::operator=(stack&& other) {
}

} // namespace ds
