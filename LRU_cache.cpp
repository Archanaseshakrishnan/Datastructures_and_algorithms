#include <iostream>
#include <unordered_map>
using namespace std;
struct Node
{
    Node * left;
    Node * right;
    int key;
    int val;

    Node (int key, int val) : key(key), val(val), left(nullptr), right(nullptr) {}
};

class LRUCache {
    int capacity;
    unordered_map<int, Node*> cache;
    Node * head;
    Node * tail;
    void addNode(Node * node)
    {
        Node * prevEnd = tail->left;
        prevEnd->right = node;
        node->left = prevEnd;
        node->right = tail;
        tail->left = node;  
    }
    void removeNode(Node * node)
    {
        Node * prevNode = node->left;
        Node * nextNode = node->right;
        prevNode->right = nextNode;
        nextNode->left = prevNode;
    }
public:
    LRUCache(int capacity) : capacity(capacity){
        head = new Node(-1, -1);
        tail = new Node(-1, -1);
        head->right = tail;
        head->left = nullptr;
        tail->left = head;
        tail->right = nullptr;
    }
    int get(int key) {
        if (cache.find(key) == cache.end())
            return -1;
        Node * node = cache[key];
        removeNode(node);
        addNode(node);
        return node->val;
    }
    void put(int key, int value) {
        auto it = cache.find(key);
        if (it != cache.end())
        {
            it->second->val = value;
            removeNode(it->second);
            addNode(it->second);
        }
        else
        {
            cache[key] = new Node(key, value);
            addNode(cache[key]);
        }
        if (cache.size() == capacity)
        {
            Node * lruNode = head->right;
            removeNode(lruNode);
            cache.erase(lruNode->key);
            delete lruNode;
        }
    }
};

int main() {
    LRUCache lru(2); // Capacity of 2
    
    cout << "Testing LRU Cache with capacity 2\n";
    cout << "==================================\n\n";
    
    // Put operations
    cout << "put(1, 1)\n";
    lru.put(1, 1);
    
    cout << "put(2, 2)\n";
    lru.put(2, 2);
    
    cout << "get(1) = " << lru.get(1) << "\n"; // Should return 1
    
    cout << "put(3, 3) - This evicts key 2 (LRU)\n";
    lru.put(3, 3);
    
    cout << "get(2) = " << lru.get(2) << "\n"; // Should return -1 (evicted)
    
    cout << "put(4, 4) - This evicts key 1 (LRU)\n";
    lru.put(4, 4);
    
    cout << "get(1) = " << lru.get(1) << "\n"; // Should return -1 (evicted)
    cout << "get(3) = " << lru.get(3) << "\n"; // Should return 3
    cout << "get(4) = " << lru.get(4) << "\n"; // Should return 4
    
    return 0;
}
