#include <iostream>
#include <map>
#include <vector>

class Tree {
public:
    std::map<int, int> tree;

    void insert(int key, int V)
    {
        tree[key] = V;
    }

    bool searchKey(int key) {
        std::map<int, int>::iterator it = tree.find(key);
        return it != tree.end();
    }

    bool searchV(int V) {
        for (std::map<int, int>::iterator it = tree.begin(); it != tree.end(); ++it) 
        {
            if (it->second == V) 
            {
                return true;
            }
        }
        return false;
    }

    void printTree() {
        for (std::map<int, int>::iterator it = tree.begin(); it != tree.end(); ++it) 
        {
            std::cout << "Key: " << it->first << ", Value: " << it->second << std::endl;
        }
    }

    std::map<int, int> filter(int threshold) {
        std::map<int, int> filteredTree;
        for (std::map<int, int>::iterator it = tree.begin(); it != tree.end(); ++it) 
        {
            if (it->second > threshold) 
            {
                filteredTree[it->first] = it->second;
            }
        }
        return filteredTree;
    }

    std::vector<int> getUniqValues() {
        std::vector<int> uniqValues;
        for (std::map<int, int>::iterator it = tree.begin(); it != tree.end(); ++it) {
            bool isUniq = true;
            for (std::vector<int>::iterator iter = uniqValues.begin(); iter != uniqValues.end(); ++iter) {
                if (*iter == it->second) {
                    isUniq = false;
                    break;
                }
            }
            if (isUniq) {
                uniqValues.push_back(it->second);
            }
        }
        return uniqValues;
    }
};

int main() 
{
    Tree tree;
    tree.insert(1, 10);
    tree.insert(2, 20);
    tree.insert(3, 30);
    tree.insert(4, 40);

    std::cout << "Original Tree:" << std::endl;
    tree.printTree();

    std::cout << "Search by Key (2): " << tree.searchKey(2) << std::endl;
    std::cout << "Search by Value (25): " << tree.searchV(25) << std::endl;


    std::multimap<int, int> balancedTree;

    balancedTree.insert(std::make_pair(1, 10));
    balancedTree.insert(std::make_pair(2, 20));
    balancedTree.insert(std::make_pair(2, 25)); 
    balancedTree.insert(std::make_pair(3, 30));
    balancedTree.insert(std::make_pair(3, 35)); 



    std::cout << "Multimap contents:" << std::endl;

    std::multimap<int, int>::iterator it;
    
    for (it = balancedTree.begin(); it != balancedTree.end(); ++it) {
        std::cout << "Key: " << it->first << ", Value: " << it->second << std::endl;
    }

    std::multimap<int, int>::iterator lower, upper;

    int keyToFind = 2;
    std::cout << "Elements with key " << keyToFind << ":" << std::endl;

    lower = balancedTree.lower_bound(keyToFind);
    upper = balancedTree.upper_bound(keyToFind);

    for (it = lower; it != upper; ++it) {
        std::cout << "Value: " << it->second << std::endl;
    }

    return 0;
}