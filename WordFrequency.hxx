#ifndef WORD_FREQUENCY_HXX
#define WORD_FREQUENCY_HXX

///////////////////////// TO-DO (1) //////////////////////////////
  /// Include necessary header files
  /// Hint:  Include what you use, use what you include
  ///
  /// Do not put anything else in this section, i.e. comments, classes, functions, etc.  Only #include directives
#include <string>     // string
#include <locale>     // locale
#include <cstddef>    // size_t
#include <unordered_map> // unordered_map

#include "WordFrequency.hpp"
/////////////////////// END-TO-DO (1) ////////////////////////////







// anonymous, unnamed namespace providing non-member private working area
namespace
{
  std::string sanitize( std::string_view word )
  {
    constexpr char bad_char[] = " \t\r\n\b\v_-\"'(){}+/*,=.!?:;";                     // leading and trailing characters to be removed
    static std::locale locality{ "en_GB.UTF-8" };

    auto startIndex = word.find_first_not_of( bad_char );                             // start with the first non-bad character
    if( startIndex == std::string_view::npos ) startIndex = word.size();              // if the word contains only bad characters ...

    std::size_t count    = 0;                                                         // assume the word contains only bad characters ...
    auto        endIndex = word.find_last_not_of( bad_char );                         // end with the first non-bad character

    if( endIndex != std::string_view::npos ) count = endIndex - startIndex + 1;       // number of characters to use in results

    std::string result{ word.substr( startIndex, count ) };                           // strip the leading and trailing bad characters
    for( auto & c : result ) c = std::tolower( c, locality );                         // convert to lower case

    return result;                                                                    // result is moved optimized (copy elision) to the caller, std::move( result ) not required
  }
}  // unnamed, anonymous namespace







// Implement WordFrequency::WordFrequency( std::istream ) - See requirements
///////////////////////// TO-DO (2) //////////////////////////////
template<typename Hasher>
WordFrequency<Hasher>::WordFrequency( std::istream & iStream)
{
  std::string word;

  while ( iStream >> std::ws >> word )
  {
    _hashtable[ sanitize(word) ]++;
    if ( iStream.eof() ) {
      iStream.setstate( std::ios::failbit );
    }
  }
}
/////////////////////// END-TO-DO (2) ////////////////////////////







// Implement WordFrequency::numberOfWords() const - See requirements
///////////////////////// TO-DO (3) //////////////////////////////
template<typename Hasher>
std::size_t WordFrequency<Hasher>::numberOfWords() const
{
  return _hashtable.size();
}
/////////////////////// END-TO-DO (3) ////////////////////////////







// Implement WordFrequency::wordCount( const std::string & ) const - See requirements
///////////////////////// TO-DO (4) //////////////////////////////
template<typename Hasher>
std::size_t WordFrequency<Hasher>::wordCount( std::string_view word ) const
{
  auto sanitized_itr = _hashtable.find( sanitize( word ) );

  if ( sanitized_itr == _hashtable.end() ) {
    return 0;
  } else {
    return sanitized_itr->second;
  }
}
/////////////////////// END-TO-DO (4) ////////////////////////////







// Implement WordFrequency::mostFrequentWord() const - See requirements
///////////////////////// TO-DO (5) //////////////////////////////
template<typename Hasher>
std::string WordFrequency<Hasher>::mostFrequentWord() const
{
  if ( _hashtable.empty() )
  {
    return "";
  } else {
    auto prev_ref = _hashtable.begin();

    for ( auto curr_ref = _hashtable.begin(); curr_ref != _hashtable.end(); curr_ref++ )
    {
      if ( curr_ref->second > prev_ref->second )
      {
        prev_ref = curr_ref;
      }
    }
    return prev_ref->first;
  }
}
/////////////////////// END-TO-DO (5) ////////////////////////////







// Implement WordFrequency::maxBucketSize() const - See requirements
///////////////////////// TO-DO (6) //////////////////////////////
  /// Hint: see the unordered_map's bucket interface at https://en.cppreference.com/w/cpp/container/unordered_map
template<typename Hasher>
std::size_t WordFrequency<Hasher>::maxBucketSize() const
{
  std::size_t maxSize = 0;
  std::size_t size = 0;

  for ( std::size_t index = 0; index < _hashtable.bucket_count(); index++ )
  {
    size = _hashtable.bucket_size( index );
    if ( size > maxSize ) maxSize = size;
  }
  return maxSize;
}
/////////////////////// END-TO-DO (6) ////////////////////////////







// Implement WordFrequency::bucketSizeAverage() const - See requirements
///////////////////////// TO-DO (7) //////////////////////////////
template<typename Hasher>
double WordFrequency<Hasher>::bucketSizeAverage() const
{
  std::size_t bucketCount = _hashtable.bucket_count();

  if ( bucketCount == 0 )
  {
    return 0.0;         // prevent dividing by zero
  }

  double numberOfWordsResult = static_cast<double>( numberOfWords() );    // cast to prevent rounding a decimal less than 1 to zero
  double bucketCountResult = static_cast<double>( bucketCount );
  return ( numberOfWordsResult / bucketCountResult );
}
/////////////////////// END-TO-DO (7) ////////////////////////////




#endif    // WORD_FREQUENCY_HXX
