#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

template <typename K, typename V>
class Dictionary {
   private:
    map<K, V> dict;

   public:
    void insertOrUpdate(K key, V value) {
        dict[key] = value;
    }

    int size() {
        return dict.size();
    }

    void deleteKey(K key) {
        auto it = dict.find(key);
        dict.erase(it);
    }

    V *find(K key) {
        auto it = dict.find(key);
        if (it != dict.end()) {
            return &*it;
        }
        return nullptr;
    }
};

int main() {
    Dictionary<int, string> dict;
    
}
