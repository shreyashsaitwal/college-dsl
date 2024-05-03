#include <iostream>
#include <vector>

using namespace std;

enum EntryTag {
    raw, chain, uninitialized
};

template <typename T>
struct RawEntry {
    int key;
    T value;
};

template <typename T>
struct Entry {
    EntryTag tag;
    union Union {
        RawEntry<T> *raw;
        vector<RawEntry<T> *> chain;

        Union() : raw(nullptr) {}

        ~Union() {}
    } entry;

    Entry() : tag(EntryTag::uninitialized) {}
};

template <int SIZE, typename T>
struct HashTable {
   private:
    vector<Entry<T> *> entries;

    int hash_addr(int key) {
        return key % SIZE;
    }

   public:
    HashTable() {
        for (int i = 0; i < SIZE; i++) {
            entries.push_back(new Entry<T>());
        }
    }

    void insert(int key, T value) {
        int addr = hash_addr(key);
        cout << addr << " ";

        if (entries.at(addr)->tag == EntryTag::uninitialized) {
            RawEntry<T> *entry = new RawEntry<T>{key, value};
            entries.at(addr)->tag = EntryTag::raw;
            entries.at(addr)->entry.raw = entry;
            cout << "Inserted raw: " << key << endl;
        } else if (entries.at(addr)->tag == EntryTag::raw) {
            if (entries.at(addr)->entry.raw->key == key) {
                throw runtime_error("ERR: Duplicate key: " + to_string(key));
            }

            entries.at(addr)->tag = EntryTag::chain;
            RawEntry<T> *old = entries.at(addr)->entry.raw;
            RawEntry<T> *entry = new RawEntry<T>{key, value};
            entries.at(addr)->entry.chain.push_back(old);
            entries.at(addr)->entry.chain.push_back(entry);
            cout << "Inserted chain: " << key << endl;
        } else {
            for (RawEntry<T> *entry : entries.at(addr)->entry.chain) {
                if (entry->key == key) {
                    throw runtime_error("ERR: Duplicate key: " + to_string(key));
                }
            }

            RawEntry<T> *entry = new RawEntry<T>{key, value};
            entries.at(addr)->entry.chain.push_back(entry);
            cout << "Inserted chain: " << key << endl;
        }
    }

    T find(int key) {
        int addr = hash_addr(key);

        if (entries.at(addr)->tag == EntryTag::uninitialized) {
            return NULL;
        }

        if (entries.at(addr)->tag == EntryTag::raw) {
            return entries.at(addr)->entry.raw->value;
        }

        for (RawEntry<T> *entry : entries.at(addr)->entry.chain) {
            if (entry->key == key) {
                return entry->value;
            }
        }

        return NULL;
    }
};

int main() {
    HashTable<250, string> table;
    for (int i = 0; i < 250; i++) {
        // table.insert(i, to_string(i));
        cout << i % 250 << endl;
    }
}
