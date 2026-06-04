#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include<iomanip>
#include<limits>    

using namespace std;

template <typename T>

class MinHeap {

    vector<T> heap;

    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }   
    int right(int i) { return 2 * i + 2; }

    void heapifyDown(int i) {
        int smallest = i;
        int l = left(i);
        int r = right(i);

        if (l < heap.size() && heap[l] < heap[smallest]) {
            smallest = l;
        }
        if (r < heap.size() && heap[r] < heap[smallest]) {
            smallest = r;
        }
        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapifyDown(smallest);
        }
    }

    void heapifyUp(int i) {
        int p = parent(i);
        while (i > 0 && heap[p] > heap[i]) {
            swap(heap[i], heap[p]);
            i = p;
        }
    }

public:
    void insert(T value) {
        heap.push_back(value);
        heapifyUp(heap.size() - 1);
    }

    T getMin() {
        if (heap.empty()) throw runtime_error("Heap is empty");
        return heap[0];
    }

    T extractMin() {
        if (heap.empty()) throw runtime_error("Heap is empty");
        T minValue = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty()) {
            heapifyDown(0);
        }
        return minValue;
    }

    void decreaseKey(int i, T newValue) {
        if (i < 0 || i >= heap.size()) throw runtime_error("Index out of bounds");
        if (newValue > heap[i]) throw runtime_error("New value is greater than current value");
        heap[i] = newValue;
        heapifyUp(i);
    }

    void deleteKey(int i) {
        decreaseKey(i, numeric_limits<T>::min());
        extractMin();
    }

    int size() {
        return heap.size();
    }

    bool empty() {
        return heap.empty();
    }

    void printHeap() const
    {
        for (const T& elem : heap)
            cout << elem << " ";
        cout << endl;
    }
};

int main()
{
    MinHeap<int> minHeap;
    minHeap.insert(3);
    minHeap.insert(2);
    minHeap.insert(15);
    minHeap.insert(5);
    minHeap.insert(4);
    minHeap.insert(45);

    cout << "Min Heap: ";
    minHeap.printHeap();
    cout << "Minimum element: " << minHeap.getMin() << endl;

    minHeap.extractMin();
    cout << "After extracting min: ";
    minHeap.printHeap();

    // Delete node from min-heap
    minHeap.deleteKey(4);
    cout << "After deleting 4: ";
    minHeap.printHeap();

    // Decrease key in min-heap
    minHeap.decreaseKey(2, 1);
    cout << "After decreasing key at index 2 to 1: ";
    minHeap.printHeap();

    return 0;
}
