// Idexer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "Indexer.h"

bool Compare(const indexer::Indexer::Index& ind1, const indexer::Indexer::Index& ind2)
{
    if (ind1.line != ind2.line || ind1.col != ind2.col)
        return false;

    return true;

}
bool IndexerTest(const std::string& file_name)
{
    indexer::Indexer indexer(file_name);

    // Test 1:
    {
        auto word_indexes = indexer.GetIndex("word");
        if (word_indexes.size() != 2)
            return false;
        if (!Compare(word_indexes[0], indexer::Indexer::Index{ 1, 6 }))
            return false;

        if (!Compare(word_indexes[1], indexer::Indexer::Index{ 2, 16 }))
            return false;
    }

    // Test 2:
    {
        auto word_indexes = indexer.GetIndex("Word");
        if (word_indexes.size() != 3)
            return false;
        if (!Compare(word_indexes[0], indexer::Indexer::Index{ 1, 1 }))
            return false;

        if (!Compare(word_indexes[1], indexer::Indexer::Index{ 2, 9 }))
            return false;

        if (!Compare(word_indexes[2], indexer::Indexer::Index{ 3, 4 }))
            return false;
    }

    // Test 3:
    {
        auto word_indexes = indexer.GetIndex("fact");
        if (word_indexes.size() != 1)
            return false;
        if (!Compare(word_indexes[0], indexer::Indexer::Index{ 8, 14 }))
            return false;
    }

    // Test 4:
    {
        auto word_indexes = indexer.GetIndex("Little");
        if (word_indexes.size() != 2)
            return false;
        if (!Compare(word_indexes[0], indexer::Indexer::Index{ 3, 29 }))
            return false;
        if (!Compare(word_indexes[1], indexer::Indexer::Index{ 10, 1 }))
            return false;

    }

    // Test 5:
    {
        auto word_indexes = indexer.GetIndex("LOL");
        if (word_indexes.size() != 0)
            return false;
    }

    // Test 6:
    {
        auto word_indexes = indexer.GetIndex("binds");
        if (word_indexes.size() != 1)
            return false;

        if (!Compare(word_indexes[0], indexer::Indexer::Index{ 6, 27 }))
            return false;

    }
    return true;
}

int main()
{
    if (IndexerTest("test.txt"))
        std::cout << "Passed" << std::endl;
    else
        std::cout << "Failed" << std::endl;

    return 0;
}