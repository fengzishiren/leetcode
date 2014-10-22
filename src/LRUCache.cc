/*
 LRU Cache
 Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and set.

 get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
 set(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.
 */
#include <iostream>
#include <list>
#include <unordered_map>
#include <cstdlib>
#include <cstring>

using namespace std;

class LRUCache {
	struct entry {
		int key, value;
		entry* next;
	public:
		entry(int _key, int _value, entry* _next) :
				key(_key), value(_value), next(_next) {
		}
	};
	struct node {
		entry e;
		node *next;
		node(int _key, int _value, entry* _nexte) :
				e(_key, _value, _nexte), next(NULL) {
		}
	};
	node* head;
	node* tail;
	entry** table;
	size_t _capacity;
	size_t size;

	size_t hash(int key) {
		return key < 0 ? -key : key;
	}
	void add(node *n) {
		if (head == NULL) {
			tail = head = n;
		} else {
			tail->next = n;
			tail = n;
			tail->next = NULL;
		}
		size_t idx = hash(n->e.key) % _capacity;

		entry *e = &n->e;
		e->next = table[idx];
		table[idx] = e;

	}
	void print(node *head) {
		node *p = head;
		while (p) {
			cout << ':' << p << '\t';
			p = p->next;
		}
		cout << endl;
	}

	node* remove(node *n) {
		node *p = head;
		node *nprev = NULL;
		entry *v = &n->e;
		size_t idx = hash(v->key) % _capacity;
		entry* e = table[idx];
		entry *eprev = NULL;
		while (e != v) {
			eprev = e;
			e = e->next;
		}
		if (eprev)
			eprev->next = e->next;
		else
			table[idx] = NULL;

		while (p != n) {
			nprev = p;
			p = p->next;
		}
		if (nprev) {
			nprev->next = p->next;
		} else {
			head = p->next;
		}
		return n;
	}

public:

	LRUCache(int capacity) :
			head(NULL), tail(NULL), _capacity(capacity), size(0) {
		//load factor: 0.75
		table = new entry*[capacity * 4 * 3];
		memset(table, 0, sizeof(*table) * capacity * 4 * 3);
	}

	int get(int key) {
		size_t idx = hash(key) % _capacity;
		for (entry* e = table[idx]; e != NULL; e = e->next) {
			if (e->key == key) {
				add(remove((node *) e));
				return e->value;
			}
		}
		return -1;
	}

	void set(int key, int value) {
		size_t idx = hash(key) % _capacity;
		for (entry* e = table[idx]; e != NULL; e = e->next) {
			if (e->key == key) {
				e->value = value;
				add(remove((node *) e));
				return;
			}
		}
		node *newnode = new node(key, value, table[idx]);
		add(newnode);
		table[idx] = &newnode->e;

		if (++size > _capacity) {
			delete remove(head);
			size--;
		}
	}

	~LRUCache() {
		node *p = head;
		node *del;
		while (p) {
			del = p;
			p = p->next;
			delete del;
		}
		delete[] table;
	}
};
//typedef list<int> List;
//typedef list<int>::iterator Iterator;
//typedef pair<int,Iterator> Pair;
//typedef unordered_map<int, Pair> Map;
//
//class LRUCache{
//public:
//    Map map;
//    List llist;
//    int MAXCAP;
//    LRUCache(int capacity):MAXCAP(capacity) {
//    }
//
//    int get(int key) {
//        auto it = map.find(key);
//        if(it==map.end()) return -1;
//        auto &kv = it->second;
//        llist.erase(kv.second);
//        llist.push_front(key);
//        kv.second=llist.begin();
//        return kv.first;
//    }
//
//    void set(int key, int value) {
//        auto it = map.find(key);
//        if(it==map.end()){
//            if(map.size()>=MAXCAP){
//                map.erase(llist.back());
//                llist.pop_back();
//            }
//            llist.push_front(key);
//            map.insert(make_pair(key,Pair(value,llist.begin())));
//        }
//        else{
//            auto &kv = it->second;
//            llist.erase(kv.second);
//            llist.push_front(key);
//            kv.second=llist.begin();
//            kv.first=value;
//        }
//    }
//};
class LRUCache1 {
public:
	list<int> link;
	unordered_map<int, pair<int, list<int>::iterator>> cache;
	size_t capacity;
public:
	LRUCache1(size_t _capacity) :
			capacity(_capacity) {
	}

	void set(int key, int value) {
		auto pos = cache.find(key);
		if (pos == cache.end()) {
			link.push_front(key);
			cache[key] = make_pair(value, link.begin());
			if (cache.size() > capacity) {
				cache.erase(link.back());
				link.pop_back();
			}
		} else {
			auto it = pos->second.second;
			link.erase(it);
			link.push_front(key);
			pos->second.second = link.begin();
			pos->second.first = value;
		}
	}

	int get(int key) {
		auto pos = cache.find(key);
		if (pos != cache.end()) {
			link.erase(pos->second.second);
			link.push_front(key);
			pos->second.second = link.begin();
			return pos->second.first;
		}
		return -1;
	}

};

int main(int argc, char **argv) {
//2,[set(2,1),set(2,2),get(2),set(1,1),set(4,1),get(2)]

	LRUCache1 cache(2);
	cache.set(2, 1);

	cout << cache.get(2) << endl;

//	cache.set(2, 1);
//	cout << cache.get(2) << endl;
//	for (int i = 0; i < 19; ++i) {
//		cache.set(i, i);
//	}
//	for (auto v : cache.link) {
//		cout << v << '\t';
//	}
//	cout << endl;
//
//	for (int i = 0; i < 19; ++i) {
//		cout << cache.get(i) << '\t';
//	}
	cout << endl;
	return 0;
}

