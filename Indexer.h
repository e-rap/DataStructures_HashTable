#include <string>
#include <utility>  // for std::make_pair
#include <vector>
#include "HashTable.h"

namespace indexer
{
  ///
  /// Class Indexer builds index hash table for each word occuring in a text.
  /// Index keeps location of a word in the text file. The word location is defined
  /// by a pair (line, column), where line and column is the position of the first letter
  /// in a word.
  ///
  class Indexer
  {
  public:
    ///
    /// Index of a word in the text.
    /// Index defines (line, column) position of the word in the text.
    /// Line, column values start from 1.
    ///
    struct Index
    {
      size_t line; ///< line number from file
      size_t col;  ///< column number from file
    };

    using Dictionary = HashTable<std::string, std::vector<Index>>;

  public:
    /// Build index of a text file
    Indexer(const std::string& file_name);

    ///
    /// Get list of all indices of a word occuring in the text in a sorted order.
    /// The sorting order is defined by line and column position in ascending order.
    ///
    std::vector<Index> GetIndex(const std::string& word);

  private:
    /// Parses all words out of the input file and builds the index
    void IndexFile(const std::string& file_name);

    Dictionary dict; ///< dictionary of all indexed words
  };
}