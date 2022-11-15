#include <iostream>
#include <memory>
class BigOldClass {
 public:
  BigOldClass(int size) : _size(size) {}
  int _size;
};
class BigDataManager {
 public:
  // Create a constructor that takes in a shared pointer to a
  // BigOldClass and initializes the data_ member
  // --- Your code here
  BigDataManager(std::shared_ptr<BigOldClass> data) : data_(data) {}
  //
  std::shared_ptr<BigOldClass> data_;
};
std::shared_ptr<BigOldClass> make_big_thing() {
  // create and return a shared pointer to a BigOldClass, you can set whatever
  // "size" you want.
  return std::make_shared<BigOldClass>(10);
}
void print_manager(BigDataManager const &m) {
  std::cout << "Data of size: " << m.data_->_size << std::endl;
}
int main() {
  // call make_big_thing -- use auto!
  auto big_thing = make_big_thing();
  // construct a BigDataManager using the BigOldClass you just got from calling
  // make_big_thing
  BigDataManager manager(big_thing);

  // call print_manager using the BigDataManager you just created
  print_manager(manager);
  return 0;
}