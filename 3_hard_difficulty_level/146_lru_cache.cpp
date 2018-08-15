/*
146. Leetcode coding challenge: LRU Cache

Design and implement a data structure for Least Recently Used (LRU) cache. It
should support the following operations: get and put.

get(key) - Get the value (will always be positive) of the key if the key exists
in the cache, otherwise return -1. put(key, value) - Set or insert the value if
the key is not already present. When the cache reached its capacity, it should
invalidate the least recently used item before inserting a new item.

Follow up:
Could you do both operations in O(1) time complexity?

Example:

LRUCache cache = new LRUCache(capacity);

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // returns 1
cache.put(3, 3);    // evicts key 2
cache.get(2);       // returns -1 (not found)
cache.put(4, 4);    // evicts key 1
cache.get(1);       // returns -1 (not found)
cache.get(3);       // returns 3
cache.get(4);       // returns 4
*/

#include <iostream>
#include <list>
#include <unordered_map>

using std::cout;
using std::end;
using std::list;
using std::make_pair;
using std::pair;
using std::unordered_map;

class LRUCache {
  list<pair<int, int>> lru_cache_{};
  unordered_map<int, list<pair<int, int>>::iterator> lru_cache_index_{};
  const size_t max_capacity_;

 public:
  explicit LRUCache(const size_t capacity) : max_capacity_{capacity} {}

  int get(const int key) {
    if (lru_cache_index_.find(key) != end(lru_cache_index_)) {
      const int value{lru_cache_index_[key]->second};
      lru_cache_.erase(lru_cache_index_[key]);
      const auto new_cache_item_iter_pos =
          lru_cache_.insert(end(lru_cache_), make_pair(key, value));
      lru_cache_index_[key] = new_cache_item_iter_pos;
      return value;
    }

    return -1;
  }

  void put(const int key, const int value) {
    if (lru_cache_index_.find(key) != end(lru_cache_index_)) {
      lru_cache_.erase(lru_cache_index_[key]);
      const auto new_cache_item_iter_pos =
          lru_cache_.insert(end(lru_cache_), make_pair(key, value));
      lru_cache_index_[key] = new_cache_item_iter_pos;

    } else if (lru_cache_.size() == max_capacity_) {
      lru_cache_index_.erase(lru_cache_.front().first);
      lru_cache_.pop_front();
      const auto new_cache_item_iter_pos =
          lru_cache_.insert(end(lru_cache_), make_pair(key, value));
      lru_cache_index_[key] = new_cache_item_iter_pos;

    } else {
      const auto new_cache_item_iter_pos =
          lru_cache_.insert(end(lru_cache_), make_pair(key, value));
      lru_cache_index_[key] = new_cache_item_iter_pos;
    }
  }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache lru_cache{capacity};
 * int param_1 = lru_cache.get(key);
 * lru_cache.put(key, value);
 */

int main() {
  LRUCache cache{2};
  cout << "1. cache.put(1, 1)\n";
  cache.put(1, 1);
  cout << "2. cache.put(2, 2)\n";
  cache.put(2, 2);
  cout << "3. cache.get(1) -> " << cache.get(1) << '\n';  // returns 1
  cout << "4. cache.put(3, 3)\n";
  cache.put(3, 3);  // evicts key 2
  cout << "5. cache.get(2) -> " << cache.get(2)
       << '\n';  // returns -1 (not found)
  cout << "6. cache.put(4, 4)\n";
  cache.put(4, 4);  // evicts key 1
  cout << "7. cache.get(1) -> " << cache.get(1)
       << '\n';  // returns -1 (not found)
  cout << "8. cache.get(3) -> " << cache.get(3) << '\n';  // returns 3
  cout << "9. cache.get(4) -> " << cache.get(4) << '\n';  // returns 4

  return 0;
}
