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
  std::vector<std::unique_ptr<GroceryItem>> groceryItemInputs;

  GroceryItem input;
  while (std::cin >> input) { // read from cin and verify data, will read until EOF
    std::unique_ptr<GroceryItem> GroceryItemPtr = std::make_unique<GroceryItem>( input );
    groceryItemInputs.push_back( GroceryItemPtr );
  }

  for( auto output = groceryItemInputs.rbegin(); output != groceryItemInputs.rend(); output++) // reverse iterate through groceryItemInputs and write to cout
  {
    std::cout << *( *output );
    delete *(output);
  }
    return 0;
}
