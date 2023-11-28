#include <iostream>
#include <string>
#include <list>
using namespace std;

class Laptop
{
    string CPU;
    unsigned int memory_size;
public:
    Laptop()
    {
        CPU = "";
        memory_size = 0;
    }

    Laptop(const string& S, unsigned int a)
    {
        CPU = S;
        memory_size = a;
    }

    void setCPU(const string& S) { CPU = S; }
    void setMemorySize(unsigned int a) { memory_size = a; }

    string getCPU()	const { return CPU; }
    unsigned int getMemorySize() const { return memory_size; }

    bool operator>(const Laptop& B) const
    {
        return this->getMemorySize() > B.getMemorySize();
    }
};

ostream& operator<<(ostream& f, const Laptop& A)
{
    f << A.getMemorySize();

    return f;
}



template <class T>
class FibonacciHeapNode 
{
public:
    T key;
    int degree;
    bool marked;
    list<FibonacciHeapNode<T>*> children;

    FibonacciHeapNode(T val)
    {
        key = val;
        degree = 0;
        marked = 0;
    }
};

template <class T>
class FibonacciHeap 
{
private:
    list<FibonacciHeapNode<T>*> rootList;
    FibonacciHeapNode<T>* maxNode;

    void mergeLists(list<FibonacciHeapNode<T>*>& list1, list<FibonacciHeapNode<T>*>& list2) 
    {
        list1.splice(list1.end(), list2);
    }

    void updateMaxNode()
    {
        maxNode = NULL;
        for (typename list<FibonacciHeapNode<T>*>::iterator it = rootList.begin();
            it != rootList.end();
            maxNode = !maxNode || (*it)->key > maxNode->key ? *it : maxNode, ++it);
    }

public:
    void insert(const T& key) 
    {
        FibonacciHeapNode<T>* newNode = new FibonacciHeapNode<T>(key);

        if (!newNode)
            return;

        rootList.push_back(newNode);

        maxNode = !maxNode || newNode->key > maxNode->key ? newNode : maxNode;
    }

    T extractMax()
    {
        if (!maxNode)
            return T();

        T maxKey = maxNode->key;

        mergeLists(rootList, maxNode->children);

        rootList.remove(maxNode);
        delete maxNode;

        updateMaxNode();

        return maxKey;
    }

    void printDescendingPriority() const
    {
        list<FibonacciHeapNode<T>*> tempRootList = rootList;        
        
        tempRootList.sort([](const FibonacciHeapNode<T>* a, const FibonacciHeapNode<T>* b) {
            return a->key > b->key;
            });

        for (typename list<FibonacciHeapNode<T>*>::iterator it = tempRootList.begin();
            it != tempRootList.end(); ++it)
            cout << (*it)->key << " ";

        cout << endl;
    }
};

int main() 
{
    FibonacciHeap<Laptop> fibonacciHeap;

    Laptop A("A", 12), B("B", 4), C("C", 16), D("D", 2);

    fibonacciHeap.insert(A);
    fibonacciHeap.insert(B);
    fibonacciHeap.insert(C);
    fibonacciHeap.insert(D);

    std::cout << "Elements before ExtractMax: ";
    fibonacciHeap.printDescendingPriority();

    Laptop maxElement = fibonacciHeap.extractMax();
    std::cout << "Extracted Max Element: " << maxElement << std::endl;

    std::cout << "Elements after ExtractMax: ";
    fibonacciHeap.printDescendingPriority();

    return 0;
}