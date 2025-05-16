/*******************************************************************************
** CPSC 131: Part 4 - Associative Containers
**           Binary Search Tree Quiz
**
** Using the methods discussed in class, implement the Binary Search Tree code
** asked for in each question (TO-DO) below. The tree shall have no duplicate keys.
**
** While the solutions to the questions below are highly inspired by the
** implementation examples presented in class, they will not be identical.  Read
** the questions carefully.
*******************************************************************************/


#include <compare>
#include <cstddef>
#include <format>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <utility>




template<typename Key, typename Value>
struct BST
{
  using KeyValue_Pair = std::pair<Key const, Value>;

  struct Node
  {
    Node() = default;
    Node( KeyValue_Pair const & pair ) : _pair{ pair } {}

    KeyValue_Pair _pair = { Key{}, Value{} };

    Node * _left   = nullptr;
    Node * _right  = nullptr;
    Node * _parent = nullptr;
  };

  Node *      _root = nullptr;
  std::size_t _size = 0;









  /*****************************************************************************
  ** Implement the BST's find function
  **   1)  find takes a key as its only argument and returns a pointer to the node containing that key
  **   2)  Write a recursive solution (not an iterative solution  Hint:  no while or for loops)
  **       o)  Write both the "public" and "private helper" functions
  **       o)  Clearly identify the Base Case, Visit, and Recurse steps  Hint:  write comments for each
  **           step before writing code
  **       o)  You may only compare the keys once
  *****************************************************************************/
  Node * find( Key const & key )
  {
    ///////////////////////// TO-DO (1) //////////////////////////////
    Node * current = _root;
    return find(key, current);
    /////////////////////// END-TO-DO (1) ////////////////////////////
  }


  Node * find( Key const & key, Node * current )
  {
    ///////////////////////// TO-DO (2) //////////////////////////////
    // base case
    if (current == nullptr) {
      return nullptr;
    }

    std::weak_ordering order = key <=> current->_pair.first;
    if (order == std::weak_ordering::equivalent) {
      // visit
      return current;
    } else if (order == std::weak_ordering::less) {
      // recurse left
      return find(key, current->_left);
    } else /* if (order == std::weak_ordering::greater) */{
      // recurse right
      return find(key, current->_right);
    }
    /////////////////////// END-TO-DO (2) ////////////////////////////
  }









  /*****************************************************************************
  ** Implement the BST's insert function
  **   1)  Insert takes a key-value pair as its only argument and returns a pointer to the
  **       node containing that key
  **   2)  Write an iterative solution (not a recursive solution)
  **   3)  You may only compare the keys once
  *****************************************************************************/
  Node * insert( KeyValue_Pair const & pair )
  {
    ///////////////////////// TO-DO (3) //////////////////////////////
    Node * node_ptr = _root;
    Node * parent_ptr = nullptr;
    std::weak_ordering order = std::weak_ordering::equivalent;

    while (node_ptr != nullptr) {
      order = pair.first <=> node_ptr->_pair.first;
      if (order == std::weak_ordering::equivalent) {
        return node_ptr;
      }
      parent_ptr = node_ptr;
      if (order == std::weak_ordering::less) {
        node_ptr = node_ptr->_left;
      } else {
        node_ptr = node_ptr->_right;
      }
    }

    Node * newNode = new Node (pair);
    newNode->_parent = parent_ptr;

    if (parent_ptr == nullptr) { _root = newNode; }
    else if (order == std::weak_ordering::less) { parent_ptr->_left = newNode; }
    else { parent_ptr->_right = newNode; }

    ++_size;
    return newNode;
    /////////////////////// END-TO-DO (3) ////////////////////////////
  }









  /*****************************************************************************
  ** Implement the BST's erase function
  **   1)  Erase takes a key as its only argument and returns nothing
  **   2)  Write an iterative solution (not a recursive solution)
  **   3)  Simplification:  Assume the node you are erasing does NOT have two children.
  **       o)  Do not write code to erase a node with two children!
  **   4)  Delegate to other member functions whenever possible
  *****************************************************************************/
  void erase( Key const & key )
  {
    ///////////////////////// TO-DO (4) //////////////////////////////
    Node * to_be_erased = find(key);

    if (to_be_erased == nullptr) return;

    Node ** parent = (to_be_erased->_parent == nullptr ? & _root : & ( to_be_erased->_parent->_left == to_be_erased ? to_be_erased->_parent->_left : to_be_erased->_parent->_right ) );
    Node *  child  = (to_be_erased->_left == nullptr ? to_be_erased->_right : to_be_erased->_left);

    *parent = child;
    if (child != nullptr) { child->_parent = to_be_erased->_parent; }

    delete to_be_erased;
    --_size;
    return;
    /////////////////////// END-TO-DO (4) ////////////////////////////
  }









  /*****************************************************************************
  ** Implement the BST's index operator function
  **   1)  operator[] takes a key as its only argument and returns a reference to the
  **       value associated with that key
  **   2)  If the key does not already exist, insert it
  *****************************************************************************/
  Value & operator[]( Key const & key )
  {
    ///////////////////////// TO-DO (5) //////////////////////////////
    Node * node = find(key);
    if (node == nullptr) { node = insert({key, {}}); }
    return node->_pair.second;
    /////////////////////// END-TO-DO (5) ////////////////////////////
  }









  /*****************************************************************************
  ** Implement the BST's clear function
  **   1)  Clear takes a pointer-to-Node as its only argument and returns nothing
  **   2)  Write a recursive solution (not an iterative solution  Hint:  no while or for loops)
  **       o)  Write the "private helper" function only (the "public" function is provided)
  **       o)  Clearly identify the Base Case, Visit, and Recurse steps  Hint:  write comments for each
  **           step before writing code
  *****************************************************************************/
  void clear() noexcept
  {
    clear( _root );
    _root = nullptr;
    _size = 0;
  }


  void clear( Node * current ) noexcept
  {
    ///////////////////////// TO-DO (6) //////////////////////////////

    Node * left = current->_left;
    Node * right = current->_right;

    // recurse
    if (left != nullptr) clear(left);
    if (right != nullptr) clear(right);

    // base case and visit
    delete current;
    return;

    /////////////////////// END-TO-DO (6) ////////////////////////////
  }









  /*****************************************************************************
  ** Implement the BST's Level-Order (Breadth-First) print function.
  **   1)  level_order_print takes no arguments and returns nothing
  **   2)  Write an iterative solution (not a recursive solution)
  **       Hint:  You'll need a queue of pointer-to-Node
  **   3)  Use the member function display() to output your data similar to the print(...) function below
  *****************************************************************************/
  void level_order_print() noexcept
  {
    auto count = 0uz;

    ///////////////////////// TO-DO (7) //////////////////////////////
    std::queue<Node *> queue;
    Node * left = nullptr;
    Node * right = nullptr;
    for (queue.push(_root); !queue.empty(); queue.pop()) {
      left = queue.front()->_left;
      right = queue.front()->_right;

      if (left != nullptr) { queue.push(left); }
      if (right != nullptr) { queue.push(right); }

      display(queue.front(), count);
    }
    /////////////////////// END-TO-DO (7) ////////////////////////////
  }









  void print()
  {
    auto count = 0uz;
    print( _root, count );
  }

  void print( Node * current, std::size_t & count )  // in-order traversal
  {
    // Base case
    if( current == nullptr ) return;


    // Recurse left
    print( current->_left, count );


    // Visit
    display( current, count );

    // Recurse right
    print( current->_right, count );
  }









  void display( Node * node, std::size_t & count )
  {
    auto && [key, value] = node->_pair;
    std::cout << std::format( "{:3}:  {{{}, {}}}\n", ++count, key, value );
  }









  ~BST() noexcept
  { clear(); }
};



























int main()
{
  BST<unsigned int, std::string> myTree;

  std::cout << "Test Case 1:\n";                     //          50         //
  myTree[50] = "indeed";                             //        /   \        //
  myTree.insert( { 40, "Structures" } );             //       40    60      //
  myTree.insert( { 60, "very" } );                   //      / \   / \      //
  myTree.insert( { 30, "Lego" } );                   //     30 45 55  70    //
  myTree.insert( { 45, "are" } );
  myTree[55] = "truly";
  myTree[70] = "entertaining";
  std::cout << "In-order (depth-first) traversal\n";
  myTree.print();
  std::cout << "------------------------------\n\n\n";


  std::cout << "\n\nTest Case 2:\n";
  std::cout << "Level-order (breadth-first) traversal\n";
  myTree.level_order_print();
  std::cout << "------------------------------\n\n\n";



  std::cout << "\n\nTest Case 3:\n";                 //          50         //
  myTree.erase( 70 );                                //        /   \        //
  myTree[30] = "Data";                               //       40    55      //
  myTree.erase( 60 );                                //      / \     \      //
  myTree.insert( { 75, "awesome" } );                //     30 45     75    //
  myTree.insert( { 50, "never" } );
  std::cout << "In-order (depth-first) traversal\n";
  myTree.print();
  std::cout << "------------------------------\n\n\n";




  std::cout << "\n\nTest Case 4:\n";
  std::cout << "Level-order (breadth-first) traversal\n";
  myTree.level_order_print();
  std::cout << "------------------------------\n\n\n";



  std::cout << "\n\nTest Case 5:\n";
  BST<char, int> anotherTree;
  anotherTree.find ('A');
  anotherTree.erase('B');
  std::cout << "myTree._size:       " << myTree     ._size << '\n'
            << "anotherTree._size:  " << anotherTree._size << '\n';

  auto n1 = anotherTree.insert({ 'C',0 });
  auto n2 = anotherTree.insert({ 'D',0 });
  auto n3 = anotherTree.insert({ 'B',0 });
  auto n4 = anotherTree.insert({ 'C',0 });
  auto n5 = anotherTree.insert({ 'D',0 });
  auto n6 = anotherTree.insert({ 'B',0 });
  std::cout << std::boolalpha
            << "Node 'B' found:  " << (n3 == n6 && n6 == anotherTree.find('B')) << '\n'
            << "Node 'C' found:  " << (n1 == n4 && n4 == anotherTree.find('C')) << '\n'
            << "Node 'D' found:  " << (n2 == n5 && n5 == anotherTree.find('D')) << '\n';
    std::cout << "------------------------------\n";
}
