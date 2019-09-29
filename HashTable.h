#pragma once

#include <list>
#include <functional> // for std::function
#include <stdexcept>  // for std::out_of_range
#include <sstream>    // for std::stringstream
#include <cmath>      // for std::floor
#include <utility>    // for std::pair
#include <string>
#include <array>

#define INITIAL_HASH_TABLE_SIZE 101 ///< used to set std::array size

/**
 * Templated Hash Table class. uses a hashing function to store keys.
 * hash collisions are handled by chaining to a linked list. the size
 * of the has table is 101 (large prime number).
 */
template <typename KeyType, typename ValueType>
class HashTable
{
private:
  using Entry = std::pair<KeyType, ValueType>;               ///< Data structure to store key and value
  using Bucket = std::list<Entry>;                           ///< bucket to store collisions.
  using Table = std::array<Bucket, INITIAL_HASH_TABLE_SIZE>; ///< Table of the hash table.

public:
  using HashFunc = std::function<size_t(const KeyType&)>;    ///< Hash Function type

  ///
  /// Constructor.
  ///
  /// @param[in] hash_func A user specified hash_function. defaults to
  ///            the internal default hash function if not specified.
  ///
  HashTable();

  HashTable(HashFunc hash_func);

  /** Destructor. */
  virtual ~HashTable();

  ///
  /// Inserts key-value pair into the hash table.
  ///
  /// If the key exists overwrites the existing value.
  ///
  /// @param[in] key key to insert.
  /// @param[in] value value to insert.
  ///
  void insert(const KeyType& key, ValueType& value);

  ///
  /// Returns a reference to the value if the key exists.
  /// If the key does not exist, inserts a key with a default
  /// constructed value
  ///
  /// @returns A reference to the value for the input key.
  ///
  ValueType& at(const KeyType& key);

  size_t size() const;                    ///< Returns the number of keys in the hash_table.
  bool exists(const KeyType& key) const;  ///< Checks if key exists.
  void clear();                           ///< Clears the entire contents of the hashtable.

private:
  Entry* find_key(const KeyType& key);    ///< returns pointer to entry if key is within hashtable, else returns nullptr

  static size_t default_hash_func(const std::string& key);  ///< Default hash function.

  size_t num_keys;                        ///< Number of key,value pairs stored in the hash table.
  static const size_t num_buckets;        ///< Number of table within the hashtable. Should be a prime number 1.3x the number of keys.
  HashFunc hash_func;                     ///< Hashing function.
  Table table;                            ///< The table of the hash table.

};

template<typename KeyType, typename ValueType>
const size_t HashTable<KeyType, ValueType>::num_buckets = INITIAL_HASH_TABLE_SIZE;

template<typename KeyType, typename ValueType>
inline HashTable<KeyType, ValueType>::HashTable()
  : hash_func{ default_hash_func }, table{}, num_keys{ 0 }
{
}

template<typename KeyType, typename ValueType>
inline HashTable<KeyType, ValueType>::HashTable(HashFunc hash_func)
  : hash_func{ hash_func }, table{}, num_keys{ 0 }
{
}

template<typename KeyType, typename ValueType>
inline HashTable<KeyType, ValueType>::~HashTable()
{
  clear();
}

template<typename KeyType, typename ValueType>
inline void HashTable<KeyType, ValueType>::insert(const KeyType& key, ValueType& value)
{
  // Hash the key
  Entry* entry_ptr{ find_key(key) };
  if (entry_ptr == nullptr)
  {
    size_t bucket_index{ hash_func(key) };
    table[bucket_index].emplace_back(key, value);
    ++num_keys;
  }
  else
  {
    entry_ptr->second = value; // update value of existing key
  }
}

template<typename KeyType, typename ValueType>
inline ValueType& HashTable<KeyType, ValueType>::at(const KeyType& key)
{
  Entry* entry_ptr{ find_key(key) };
  if (entry_ptr == nullptr)
  {
    insert(key, ValueType{});
    entry_ptr = find_key(key);
  }
  return entry_ptr->second;
}

template<typename KeyType, typename ValueType>
inline size_t HashTable<KeyType, ValueType>::size() const
{
  return num_keys;
}

template<typename KeyType, typename ValueType>
inline bool HashTable<KeyType, ValueType>::exists(const KeyType& key) const
{
  return ((find_key(key) != nullptr) ? true : false);
}

template<typename KeyType, typename ValueType>
inline void HashTable<KeyType, ValueType>::clear()
{
  for (auto& bucket : table)
  {
    bucket.clear();
  }
}

template<typename KeyType, typename ValueType>
inline typename HashTable<KeyType, ValueType>::Entry* HashTable<KeyType, ValueType>::find_key(const KeyType& key)
{
  Entry* ret_val{ nullptr };
  size_t bucket_index{ hash_func(key) };
  for (Entry& entry : table[bucket_index])
  {
    if (entry.first == key)
    {
      ret_val = &entry;
    }
  }
  return ret_val;
}

template<typename KeyType, typename ValueType>
inline size_t HashTable<KeyType, ValueType>::default_hash_func(const std::string& key)
{
  // hash function for a string from: http://www.cse.yorku.ca/~oz/hash.html
  unsigned long hash{ 5381 };
  for (auto& ch : key)
  {
    hash = ((hash << 5) + hash) + ch; /* hash * 33 + c */
  }

  return hash % num_buckets;
}
