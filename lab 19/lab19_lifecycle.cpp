#include <iostream>
#include <memory>
class BigOldClass {
 public:
  BigOldClass(int size) : _size(size) {
    std::cout << "constructing BigOldClass: " << this << std::endl;
  }
  BigOldClass(BigOldClass const &copy) {
    std::cout << "constructing BigOldClass by copying: " << this << std::endl;
    _size = copy._size;
  }
  ~BigOldClass() {
    std::cout << "destructing BigOldClass: " << this << std::endl;
  }
  int _size;
};
void print_copy(BigOldClass c) {
  std::cout << "pass by value: address: " << &c << std::endl;
}
void print_reference(BigOldClass const &c) {
  std::cout << "pass by const ref: address: " << &c << std::endl;
}
void print_pointer(BigOldClass const *c) {
  std::cout << "pass by raw ptr: address: " << c << std::endl;
}
void print_unique_pointer(std::unique_ptr<BigOldClass> const &c) {
  std::cout << "pass by const ref to unique_ptr: address: " << c.get()
            << std::endl;
}
int main() {
  BigOldClass c1(100);
  auto *c1_ptr = &c1;
  auto const c1_unique_ptr_copy = std::make_unique<BigOldClass>(c1);
  auto const c1_unique_ptr_emplace = std::make_unique<BigOldClass>(100);
  print_copy(c1);
  print_reference(c1);
  print_pointer(&c1);
  print_unique_pointer(c1_unique_ptr_copy);
  print_unique_pointer(c1_unique_ptr_emplace);
  return 0;
}