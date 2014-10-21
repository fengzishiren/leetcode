/*
 LRU Cache
 Design and implement a data structure for Least Recently Used (LRU) cache. It should support the following operations: get and set.

 get(key) - Get the value (will always be positive) of the key if the key exists in the cache, otherwise return -1.
 set(key, value) - Set or insert the value if the key is not already present. When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.
 */
#include <iostream>
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

int main(int argc, char **argv) {

	LRUCache cache(10);
	cache.set(1, 3);
	cache.set(2, 3);
	cache.set(3, 3);
	cache.set(4, 3);
	cache.set(5, 3);
	cache.set(6, 3);
	cache.set(7, 3);
	cache.set(8, 3);
	cache.set(9, 3);
	cache.set(10, 3);
	cout << cache.get(1) << endl;
	cache.set(11, 3);
	cout << cache.get(1) << endl;
	cout << "crash" << endl;
	cout << cache.get(2) << endl;
	//[get(2),set(2,6),get(1),set(1,5),set(1,2),get(1),get(2)]
	cout << cache.get(2) << endl;
	cache.set(2, 6);
	cout << cache.get(1) << endl;
	cache.set(1, 5);
	cout << cache.get(1) << endl;
	cout << cache.get(2) << endl;
	cout << "end" << endl;
	return 0;
}

