#include <iostream>         // istream, ostream
#include <memory>
#include <vector>
#include <utility>          // move()

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
  std::vector<std::unique_ptr<GroceryItem>> cart;
  GroceryItem               item;

  std::cout << "Welcome to Kroger.  Place grocery items into your shopping cart by entering each item's information. \nEnclose string entries in quotes, separate fields with commas. \nFor example:  \"00016000306707\", \"Betty Crocker\", \"Betty Crocker Double Chocolate Chunk Cookie Mix\", 17.19 \nEnter CTL-Z (Windows) or CTL-D (Linux) to quit.\n\n";

  std::cout << "Enter UPC, Product Brand, Product Name, and Price:\n";
  // read GroceryItems from cin
  while( std::cin >> item )
  {                                                                          // will use GroceryItem's op>> to store cin to item, loop will continue until end of file or invalid input
    cart.push_back( std::make_unique<GroceryItem>( std::move( item ) ) );   // is emplace_back better?
    std::cout << "Item added to shopping cart: " << *cart.back() << "\n\n";

    std::cout << "Enter UPC, Product Brand, Product Name, and Price:\n";    // this is not a great way of writing this loop but it works and I couldn't think of anything else
  }

  // write GroceryItems to cout in reverse order (using std::const_reverse_iterator)
  std::cout << "Here is a list of items in your shopping cart:\n";
  for( auto it = cart.crbegin(); it != cart.crend(); ++it )
  {
    std::cout << **it << '\n';
  }
  return 0;
}
