#include "Indexer.h"
#include <fstream>   // for std::ifstream, std::getline
#include <cctype>    // for std::isalpha, std::isspace
#include <algorithm> // for std::sort

namespace indexer
{
  // TODO :: cleanup indexer function. seperate into helper functions
  Indexer::Indexer(const std::string& file_name)
    : dict{}
  {

    std::ifstream fin{ file_name };
    std::string line{};

    int line_number{ 1 };
    int col_number{ 1 };

    Index location{};
    std::string word{};

    while (std::getline(fin, line))
    {
      col_number = 1;
      for (auto ch : line)
      {
        if (std::isalpha(ch) && word.empty())
        {
          location.col = col_number;
          location.line = line_number;
          word += ch;
        }
        else if (std::isalpha(ch))
        {
          word += ch;
        }
        else if (std::isspace(ch) && (!word.empty()))
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
      // TODO: Remove redundant mess
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
}
