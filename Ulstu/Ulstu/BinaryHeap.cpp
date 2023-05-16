#include <iostream>
#include <vector>

class BinaryHeap
{
    private:
        std::vector<int> heap;
        int left(int parent);
        int right(int parent);
        int parent(int child);
        void heapify_up(int index);
        void heapify_down(int index);

    public:
        BinaryHeap() {}
        void Insert(int element);
        void DeleteMin();
        int ExtractMin();
        void DisplayHeap();
        int Size();
};

int BinaryHeap::Size()
{
    return heap.size();
}

int BinaryHeap::left(int parent)
{
    int l = 2 * parent + 1;

    if (l < heap.size())
        return l;
    else
        return -1;
}

int BinaryHeap::right(int parent)
{
    int r = 2 * parent + 2;

    if (r < heap.size())
        return r;
    else
        return -1;
}

int BinaryHeap::parent(int child)
{
    int p = (child - 1) / 2;

    if (child == 0)
        return -1;
    else
        return p;
}

void BinaryHeap::heapify_up(int index)
{
    if (index >= 0 && parent(index) >= 0 && heap[parent(index)] > heap[index])
    {
        std::swap(heap[index], heap[parent(index)]);
        heapify_up(parent(index));
    }
}

void BinaryHeap::heapify_down(int index)
{
    int child_index = left(index);
    if (child_index > 0 && right(index) > 0 && heap[child_index] > heap[right(index)])
    {
        child_index = right(index);
    }

    if (child_index > 0)
    {
        std::swap(heap[index], heap[child_index]);
        heapify_down(child_index);
    }
}

void BinaryHeap::Insert(int element)
{
    heap.push_back(element);
    heapify_up(heap.size() - 1);
}

void BinaryHeap::DeleteMin()
{
    if (heap.size() == 0)
    {
        std::cout << "Heap is empty\n";
        return;
    }
    heap[0] = heap[heap.size() - 1];
    heap.pop_back();
    heapify_down(0);
}

int BinaryHeap::ExtractMin()
{
    if (heap.size() == 0) {
        return -1;
    }
    else
        return heap.front();
}

void BinaryHeap::DisplayHeap()
{
    std::vector<int>::iterator pos = heap.begin();
    std::cout << "Heap -->  ";

    while (pos != heap.end())
    {
        std::cout << *pos << " ";
        pos++;
    }
    std::cout << std::endl;
}

int main() {
    BinaryHeap h;
    h.Insert(3);
    h.Insert(2);
    h.Insert(15);
    h.DisplayHeap();
    std::cout << "Size of heap --> " << h.Size() << std::endl;
    std::cout << "Min Element --> " << h.ExtractMin() << std::endl;
    h.DeleteMin();
    h.DisplayHeap();
    return 0;
}