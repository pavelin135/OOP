#include <iostream>
#include <string>


class Superhero {
public:
    std::string alias;
    std::string realName;
    std::string dateOfBirth;
    std::string gender;
    std::string superpower;
    std::string weakness;
    int victories;
    int powerRating;

    Superhero(const std::string& alias, const std::string& realName, const std::string& dateOfBirth,
        const std::string& gender, const std::string& superpower, const std::string& weakness,
        int victories, int powerRating)
    {
        this->alias = alias;
        this->realName = realName;
        this->dateOfBirth = dateOfBirth;
        this->gender = gender;
        this->superpower = superpower;
        this->weakness = weakness;
        this->victories = victories;
        this->powerRating = powerRating;
    }
};

// Узел дерева
template<typename K, typename C>
class Node {
public:
    K key;
    C* data;
    Node* left;
    Node* right;
    Node* parent;

    Node(const K& key, C* data)
        : key(key), data(data), left(nullptr), right(nullptr), parent(nullptr) {}
};


template<typename K, typename C>
Node<K, C>* findSuccessor(Node<K, C>* node) {
    if (node == nullptr)
        return nullptr;

    if (node->right != nullptr) {
        // Если у узла есть правый потомок, ищем самый левый узел в правом поддереве
        node = node->right;
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    // Если у узла нет правого поддерева, поднимаемся вверх по родительским узлам
    // до тех пор, пока мы не станем правым потомком своего родителя
    Node<K, C>* parent = node->parent;
    while (parent != nullptr && node == parent->right) {
        node = parent;
        parent = parent->parent;
    }

    return parent;
}
// Шаблон класса Дерева поиска
template<typename K, typename C>
class BinarySearchTree {
protected:
    Node<K,C>* root;
public:
    BinarySearchTree()
    {
        root = NULL;
    }

    ~BinarySearchTree() {
        if (root != NULL)
        {
            delete root->left;
            delete root->right;

            delete root;
        }
    }

    void insert(const K& key, C* data) {
        Node<K, C>* newNode = new Node<K, C>(key, data);
        if (newNode == NULL)
            return;

        if (root == NULL) {
            root = newNode;
        }
        else {
            Node<K, C>* current = root;
            Node<K, C>* parent = NULL;
            while (true) {
                parent = current;
                if (key < current->key) {
                    current = current->left;
                    if (current == NULL) {
                        parent->left = newNode;
                        newNode->parent = parent;
                        break;
                    }
                }
                else {
                    current = current->right;
                    if (current == NULL) {
                        parent->right = newNode;
                        newNode->parent = parent;
                        break;
                    }
                }
            }
        }
    }

    void remove(Node<K, C>* node) {
        if (node == NULL)
            return;

        if (node->left == NULL && node->right == NULL) {
            if (node == root)
                root = NULL;
            else if (node->parent->left == node)
                node->parent->left = NULL;
            else
                node->parent->right = NULL;
        }
        else if (node->left == NULL || node->right == NULL) {
            Node<K, C>* child = (node->left != NULL) ? node->left : node->right;
            if (node == root) {
                root = child;
                child->parent = NULL;
            }
            else {
                if (node->parent->left == node)
                    node->parent->left = child;
                else
                    node->parent->right = child;
                child->parent = node->parent;
            }
        }
        else {
            Node<K, C>* successor = findSuccessor(node);
            node->key = successor->key;
            node->data = successor->data;
            remove(successor);
        }
        delete node;
    }

    C* operator[](const K& key)
    {
        Node<K, C>* node = findNode(key);
        if (node != NULL)
            return node->data;
        return NULL;
    }
};

int main()
{
    Superhero s("a", "b", "c", "d", "e", "f", 1, 2);

    Node<std::string, Superhero> U(s.alias, &s);

    BinarySearchTree<std::string, Superhero> A;
    
    A.insert(s.alias, &s);
    A.remove(&U);
}