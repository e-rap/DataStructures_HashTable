#include <algorithm> // for std::sort
#include <cctype>    // for std::isalpha, std::isspace
#include <fstream>   // for std::ifstream, std::getline
#include "Indexer.h"

namespace indexer
{
  Indexer::Indexer(const std::string& file_name)
    : dict{}
  {
    IndexFile(file_name);
  }

  std::vector<Indexer::Index> Indexer::GetIndex(const std::string& word)
  {
    auto& locations = dict.at(word);
    auto comp = [](Index a, Index b)
    {
      if (a.line < b.line)
      {
        return true;
      }
      else if (a.line == b.line && a.col <= b.col)
      {
        return true;
      }
      else
      {
        return false;
      }
    };
    std::sort(locations.begin(), locations.end(), comp);
    return locations;
  }
  void Indexer::IndexFile(const std::string& file_name)
  {
    int line_number{ 1 };
    int col_number{};

    Index location{};
    std::string word{};

    std::ifstream fin{ file_name }; // Open the file
    std::string line{};

    // find each word in the file
    while (std::getline(fin, line))
    {
      col_number = 1;
      for (auto character : line)
      {
        if (std::isalpha(character) && word.empty())
        {
          location.col = col_number;
          location.line = line_number;
          word += character;
        }
        else if (std::isalpha(character))
        {
          word += character;
        }
        else if (std::isspace(character) && (!word.empty()))
        {
          auto& locations = dict.at(word);
          locations.push_back(location);
          location.col = 0;
          location.line = 0;
          word.clear();
        }
        else
        {
          // ignore character
        }
        ++col_number;
      }
      // save word before newline
      if (!word.empty())
      {
        auto& locations = dict.at(word);
        locations.push_back(location);
        location.col = 0;
        location.line = 0;
        word.clear();
      }
      ++line_number;
    }
  }
}
