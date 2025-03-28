#include <algorithm>                                                  // max()
#include <cmath>                                                      // abs(), pow()
#include <compare>                                                    // weak_ordering
#include <iomanip>                                                    // quoted(), ios::failbit
#include <iostream>                                                   // istream, ostream, ws()
#include <string>
#include <type_traits>                                                // is_floating_point_v, common_type_t
#include <utility>                                                    // move()

#include "GroceryItem.hpp"



/*******************************************************************************
**  Implementation of non-member private types, objects, and functions
*******************************************************************************/
namespace    // unnamed, anonymous namespace
{
  // Avoid direct equality comparisons on floating point numbers. Two values are equal if they are "close enough", which is
  // represented by Epsilon.  Usually, this is a pretty small number, but since we are dealing with money (only two, maybe three
  // decimal places) we need to be a bit more tolerant.
  //
  // The two values are "close enough" to be considered equal if the distance between lhs and rhs is less than:
  // o)  EPSILON1, otherwise
  // o)  EPSILON2 percentage of the larger value's magnitude

  template< typename T,  typename U >   requires std::is_floating_point_v<std::common_type_t<U, T> >
  constexpr bool floating_point_is_equal( T const lhs,  U const rhs,  long double const EPSILON1 = /*1e-12L*/ 1e-4L,  long double const EPSILON2 = 1e-8L ) noexcept
  {
    ///////////////////////// TO-DO (1) //////////////////////////////
      ///  Write the lines of code that compare two floating point numbers.  Return true when the left hand side (lhs) and the right
      ///  hand side (rhs) are within Epsilon, and false otherwise.
      ///
      ///  See: "Floating point equality" in https://www.learncpp.com/cpp-tutorial/relational-operators-and-floating-point-comparisons/
      ///
      ///  Hint:  Avoid writing code that looks like this:
      ///           if( some expression that is true ) return the constant "true"
      ///           else                               return the constant "false"
      ///         for example, avoid:
      ///           if (a < b) return true;
      ///           else       return false;
      ///         do this instead:
      ///           return a < b;
    auto val = std::abs( lhs - rhs );
    auto magnitude = std::max( std::abs( lhs ), std::abs( rhs ) );
    return val < EPSILON1 || val < EPSILON2 * magnitude;           // short circuit bool eval will determine lhs first
    /////////////////////// END-TO-DO (1) ////////////////////////////
  }
}    // unnamed, anonymous namespace







/*******************************************************************************
**  Constructors, assignments, and destructor
*******************************************************************************/

// Default and Conversion Constructor
///////////////////////// TO-DO (2) //////////////////////////////
  /// Copying the parameters into the object's attributes (member variables) "works" but is not correct.  Be sure to move the parameters into the object's attributes
GroceryItem::GroceryItem( std::string productName,
                          std::string brandName,
                          std::string upcCode,
                          double      price )
  : _upcCode(     std::move( upcCode     ) ),
    _brandName(   std::move( brandName   ) ),
    _productName( std::move( productName ) ),
    _price(                ( price       ) )
/////////////////////// END-TO-DO (2) ////////////////////////////
{}                                                                    // Avoid setting values in constructor's body (when possible)




// Copy constructor
///////////////////////// TO-DO (3) //////////////////////////////
GroceryItem::GroceryItem( GroceryItem const & other )
   :_upcCode(     other.upcCode()     ),
    _brandName(   other.brandName()   ),
    _productName( other.productName() ),
    _price(       other.price()       )
/////////////////////// END-TO-DO (3) ////////////////////////////
{}                                                                    // Avoid setting values in constructor's body (when possible)




// Move constructor
///////////////////////// TO-DO (4) //////////////////////////////
GroceryItem::GroceryItem( GroceryItem && other ) noexcept
  : _upcCode(     std::move( other._upcCode     ) ),
    _brandName(   std::move( other._brandName   ) ),
    _productName( std::move( other._productName ) ),
    _price(                ( other._price       ) )

// = default;
/////////////////////// END-TO-DO (4) ////////////////////////////
{}




// Copy Assignment Operator
GroceryItem & GroceryItem::operator=( GroceryItem const & rhs ) &
{
  ///////////////////////// TO-DO (5) //////////////////////////////
  if( this == &rhs ) return *this; // could invert this and enclose the next four lines to be more efficient
  _upcCode     = rhs.upcCode();
  _brandName   = rhs.brandName();
  _productName = rhs.productName();
  _price       = rhs.price();
  return *this;
  /////////////////////// END-TO-DO (5) ////////////////////////////
}




// Move Assignment Operator
///////////////////////// TO-DO (6) //////////////////////////////
GroceryItem & GroceryItem::operator=( GroceryItem && rhs ) & noexcept
{
  if( this == &rhs ) return *this;    // could invert this and enclose the next four lines to be more efficient
  _upcCode     = std::move( rhs._upcCode     );
  _brandName   = std::move( rhs._brandName   );
  _productName = std::move( rhs._productName );
  _price       =          ( rhs._price       );
  return *this;
}
/////////////////////// END-TO-DO (6) ////////////////////////////



// Destructor
///////////////////////// TO-DO (7) //////////////////////////////
GroceryItem::~GroceryItem() noexcept = default;
/////////////////////// END-TO-DO (7) ////////////////////////////








/*******************************************************************************
**  Accessors
*******************************************************************************/

// upcCode() const    (L-value objects)
///////////////////////// TO-DO (8) //////////////////////////////
std::string const & GroceryItem::upcCode() const &
{
  return _upcCode;
}
/////////////////////// END-TO-DO (8) ////////////////////////////




// brandName() const    (L-value objects)
std::string const & GroceryItem::brandName() const &
{
  ///////////////////////// TO-DO (9) //////////////////////////////
  return _brandName;
  /////////////////////// END-TO-DO (9) ////////////////////////////
}




// productName() const    (L-value objects)
///////////////////////// TO-DO (10) //////////////////////////////
std::string const & GroceryItem::productName() const &
{
  return _productName;
}
/////////////////////// END-TO-DO (10) ////////////////////////////



// price() const    (L-value and, because there is no R-value overload, R-value objects)
///////////////////////// TO-DO (11) //////////////////////////////
double GroceryItem::price() const &
{
  return _price;
}
/////////////////////// END-TO-DO (11) ////////////////////////////




// upcCode()    (R-value objects)
///////////////////////// TO-DO (12) //////////////////////////////
std::string GroceryItem::upcCode() &&
{
  return std::move( _upcCode );
}
/////////////////////// END-TO-DO (12) ////////////////////////////




// brandName()    (R-value objects)
///////////////////////// TO-DO (13) //////////////////////////////
std::string GroceryItem::brandName() &&
{
  return std::move( _brandName );
}
/////////////////////// END-TO-DO (13) ////////////////////////////




// productName()    (R-value objects)
std::string GroceryItem::productName() &&
{
  ///////////////////////// TO-DO (14) //////////////////////////////
  return std::move( _productName );
  /////////////////////// END-TO-DO (14) ////////////////////////////
}








/*******************************************************************************
**  Modifiers
*******************************************************************************/

// upcCode(...)
GroceryItem & GroceryItem::upcCode( std::string newUpcCode ) &
{
  ///////////////////////// TO-DO (15) //////////////////////////////
    /// Copy assignment "works" but is not correct.  Be sure to move newUpcCode into _upcCode
  _upcCode = std::move( newUpcCode );
  return *this;
  /////////////////////// END-TO-DO (15) ////////////////////////////
}




// brandName(...)
///////////////////////// TO-DO (16) //////////////////////////////
GroceryItem & GroceryItem::brandName( std::string newBrandName ) &
{
  _brandName = std::move( newBrandName );
  return *this;
}
/////////////////////// END-TO-DO (16) ////////////////////////////




// productName(...)
GroceryItem & GroceryItem::productName( std::string newProductName ) &
///////////////////////// TO-DO (17) //////////////////////////////
{
  _productName = std::move( newProductName );
  return *this;
}
/////////////////////// END-TO-DO (17) ////////////////////////////




// price(...)
///////////////////////// TO-DO (18) //////////////////////////////
GroceryItem & GroceryItem::price( double newPrice) &
{
  _price = newPrice;
  return *this;
}
/////////////////////// END-TO-DO (18) ////////////////////////////








/*******************************************************************************
**  Relational Operators
*******************************************************************************/

// operator<=>(...)
std::weak_ordering GroceryItem::operator<=>( const GroceryItem & rhs ) const noexcept
{
  // Design decision:  A very simple and convenient defaulted 3-way comparison operator
  //                         auto operator<=>( const GroceryItem & ) const = default;
  //                   in the class definition (header file) would get very close to what is needed and would allow both the <=> and
  //                   the == operators defined here to be skipped.  The physical ordering of the attributes in the class definition
  //                   would have to be changed (easy enough in this case) but the default directly compares floating point types
  //                   (price) for equality, and that should be avoided, in general. For example, if x and y are of type double,
  //                   then  x < y  is okay but  x == y  is not.  So these (operator<=> and operator==) explicit definitions are
  //                   provided.
  //
  //                   Also, many ordering (sorting) algorithms, like those used in std::map and std::set, require at least a weak
  //                   ordering of elements. operator<=> provides only a partial ordering when comparing floating point numbers.
  //
  // Weak order:       Objects that compare equal but are not substitutable (identical).  For example, since _price can be within
  //                   EPSILON, GroceryItem("ProductName", "BrandName", "UPC", 9.99999) and GroceryItem("ProductName", "BrandName",
  //                   "UPC", 10.00001) are equal but they are not identical.  If you ignore case when comparing strings, as another
  //                   example, GroceryItem("ProductName") and GroceryItem("productName") are equal but they are not identical.
  //
  // See std::weak_ordering    at https://en.cppreference.com/w/cpp/utility/compare/weak_ordering and
  //     std::partial_ordering at https://en.cppreference.com/w/cpp/utility/compare/partial_ordering
  //     The Three-Way Comparison Operator at  http://modernescpp.com/index.php/c-20-the-three-way-comparison-operator
  //     Spaceship (Three way comparison) Operator Demystified https://youtu.be/S9ShnAFmiWM
  //
  //
  // Grocery items are equal if all attributes are equal (or within Epsilon for floating point numbers, like price). Grocery items are ordered
  // (sorted) by UPC code, product name, brand name, then price.

  ///////////////////////// TO-DO (19) //////////////////////////////
  if( std::weak_ordering result = ( _upcCode <=> rhs.upcCode() ); result != 0 )
  {
    return result;
  }
  if( std::weak_ordering result = ( _productName <=> rhs.productName() ); result != 0 )
  {
    return result;
  }
  if( std::weak_ordering result = ( _brandName <=> rhs.brandName() ); result != 0 )
  {
    return result;
  }

  if( floating_point_is_equal( _price, rhs.price() ) )
  {
    return std::weak_ordering::equivalent;
  }
  if( _price < rhs.price() )
  {
    return std::weak_ordering::less;
  }

  return std::weak_ordering::greater;
  /////////////////////// END-TO-DO (19) ////////////////////////////
}




// operator==(...)
bool GroceryItem::operator==( const GroceryItem & rhs ) const noexcept
{
  // All attributes must be equal for the two grocery items to be equal to the other.  This can be done in any order, so put the
  // quickest and then the most likely to be different first.

  ///////////////////////// TO-DO (20) //////////////////////////////
  return ( floating_point_is_equal( _price, rhs.price() ) &&
           _upcCode == rhs.upcCode() &&
           _brandName == rhs.brandName() &&
           _productName == rhs.productName()
           );                                                     // uses short circuit bool eval
  /////////////////////// END-TO-DO (20) ////////////////////////////
}








/*******************************************************************************
**  Insertion and Extraction Operators
*******************************************************************************/

// operator>>(...)
std::istream & operator>>( std::istream & stream, GroceryItem & groceryItem )
{
  // A lot can go wrong when reading from streams - no permission, wrong types, end of file, etc. Minimal exception guarantee says
  // there should be no side effects if an error or exception occurs, so let's do our work in a local object and move it into place
  // at the end if all goes well.
  //
  // This function should be symmetrical with operator<< below.  Read what your write, and write what you read

  char delimiter = '\x{00}';                                          // C++23 delimited escape sequence for the character whose value is zero (the null character)
  ///////////////////////// TO-DO (21) //////////////////////////////
    ///
    ///
    /// Assume fields are separated by commas & optional spaces, and string attributes are enclosed with double quotes.  For example:
    ///    UPC Code         | Brand Name | Product Name                                                  | Price
    ///    -----------------+------------+---------------------------------------------------------------+-------
    ///    "00034000020706",  "York",      "York Peppermint Patties Dark Chocolate Covered Snack Size"  ,  12.64
    ///
    ///
    /// Hint:  Use std::quoted to read and write quoted strings.  See
    ///        1) https://en.cppreference.com/w/cpp/io/manip/quoted
    ///        2) https://www.youtube.com/watch?v=Mu-GUZuU31A
  GroceryItem item;

  if(
      stream >> std::ws >> std::quoted( item._upcCode ) &&
      stream >> std::ws >> delimiter && delimiter == ',' &&
      stream >> std::ws >> std::quoted( item._brandName ) &&
      stream >> std::ws >> delimiter && delimiter == ',' &&
      stream >> std::ws >> std::quoted( item._productName ) &&
      stream >> std::ws >> delimiter && delimiter == ',' &&
      stream >> std::ws >> item._price )                                   // using short circuit bool eval again
  {
    groceryItem = std::move( item );
  }
  else stream.setstate( std::ios::failbit );
  return stream;
  /////////////////////// END-TO-DO (21) ////////////////////////////
}




// operator<<(...)
std::ostream & operator<<( std::ostream & stream, const GroceryItem & groceryItem )
{
  ///////////////////////// TO-DO (22) //////////////////////////////
    /// This function should be symmetrical with operator>> above.  Read what your write, and write what you read
    ///
    /// Hint:  Brand and product names may have quotes, which need to escaped when printing.  Use std::quoted to read and write quoted strings.  See
    ///        1) https://en.cppreference.com/w/cpp/io/manip/quoted
    ///        2) https://www.youtube.com/watch?v=Mu-GUZuU31A
  const std::string separator = ", ";
  stream << std::quoted( groceryItem._upcCode ) << separator
         << std::quoted( groceryItem._brandName ) << separator
         << std::quoted( groceryItem._productName ) << separator
         << groceryItem._price;
  return stream;
  /////////////////////// END-TO-DO (22) ////////////////////////////
}
