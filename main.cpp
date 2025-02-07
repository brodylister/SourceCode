#include <iostream>
#include <memory>
#include <vector>

#include "GroceryItem.hpp"
/*
INSTRUCTIONS:
Implement function main() to use the GroceryItem class:
  a. Read a grocery item 1 from standard input (std::cin) until end of file 2. For each
  grocery item read:
    i. Store the grocery item in a dynamically created object (e.g., new,
    make_unique, …)
    ii. Store the grocery item’s pointer in a standard vector
  b. After you have reached the end of file, write the grocery items 3 to standard
  output (std::cout) in reverse order using constant reverse iterators
  c. Be sure to release the dynamically allocated objects before exiting the
  program

*/

int main() {
  // going to attempt to implement this with normal pointers (fingers crossed)
  std::vector<GroceryItem*> cart;
  GroceryItem               item;

  // read GroceryItems from cin
  while( std::cout << "Enter UPC, Product Brand, Product Name, and Price\n", std::cin >> item )
  {                                                                     // will use GroceryItem's op>> to store cin to item, loop will continue until end of file
    GroceryItem * ptrItem = new GroceryItem( std::move( item ) );       // move item to memory and make pointer
    cart.push_back( ptrItem );                                          // could potentially condense these lines into an emplace_back

    std::cout << "Item added to shopping cart: " << *cart.back() << "\n\n";
  }

  // write GroceryItems to cout in reverse order (using std::const_reverse_iterator)
  for (std::vector<GroceryItem *>::const_reverse_iterator it = cart.crbegin(); it != cart.crend(); ++it) {
    std::cout << **it << "\n";
    delete *it;
  }


  /*

  example implementation with smart pointers:
  std::vector<std::make_unique<GroceryItem>> cart;
  GroceryItem                                item;

  while ( std::cout << "Enter UPC, Product Brand, Product Name, and Price\n", std::cin >> item ) {
    cart.emplace_back(std::make_unique<GroceryItem>(std::move(item)));
  }

  for (auto it = cart.crbegin(), it < crend(); ++it) {
    std::cout << **it << "\n";
  }

  */
  return 0;
}
