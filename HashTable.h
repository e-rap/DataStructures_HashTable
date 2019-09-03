#pragma once

#include <list>

template <class KeyType, typename ValueType>
class HashTable
{
public:
  HashTable();
  virtual ~HashTable();

  void insert(KeyType key, ValueType value);

  ValueType& operator[](const KeyType& key);

  size_t size();

  bool empty();

  void clear();



private:

};

