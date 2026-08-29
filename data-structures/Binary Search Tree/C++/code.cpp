#include <iostream>

class BinarySearchTree
{
private:
    struct Node
    {
        int value;
        Node* left;
        Node* right;

        Node(int value)
            : value(value), left(nullptr), right(nullptr)
        {
        }
    };

    Node* root;

    Node* insert(Node* node, int value)
    {
        if (node == nullptr)
        {
            return new Node(value);
        }

        if (value < node->value)
        {
            node->left = insert(node->left, value);
        }
        else if (value > node->value)
        {
            node->right = insert(node->right, value);
        }

        return node;
    }

    Node* search(Node* node, int value) const
    {
        if (node == nullptr || node->value == value)
        {
            return node;
        }

        if (value < node->value)
        {
            return search(node->left, value);
        }

        return search(node->right, value);
    }

    Node* findMin(Node* node) const
    {
        Node* current = node;

        while (current != nullptr && current->left != nullptr)
        {
            current = current->left;
        }

        return current;
    }

    Node* remove(Node* node, int value)
    {
        if (node == nullptr)
        {
            return nullptr;
        }

        if (value < node->value)
        {
            node->left = remove(node->left, value);
        }
        else if (value > node->value)
        {
            node->right = remove(node->right, value);
        }
        else
        {
            // No children.
            if (node->left == nullptr && node->right == nullptr)
            {
                delete node;
                return nullptr;
            }

            // Only right child.
            if (node->left == nullptr)
            {
                Node* child = node->right;

                delete node;

                return child;
            }

            // Only left child.
            if (node->right == nullptr)
            {
                Node* child = node->left;

                delete node;

                return child;
            }

            // Two children.
            Node* successor = findMin(node->right);

            node->value = successor->value;
            node->right = remove(node->right, successor->value);
        }

        return node;
    }

    void inorder(Node* node) const
    {
        if (node == nullptr)
        {
            return;
        }

        inorder(node->left);
        std::cout << node->value << " ";
        inorder(node->right);
    }

    void preorder(Node* node) const
    {
        if (node == nullptr)
        {
            return;
        }

        std::cout << node->value << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node* node) const
    {
        if (node == nullptr)
        {
            return;
        }

        postorder(node->left);
        postorder(node->right);
        std::cout << node->value << " ";
    }

    void freeTree(Node* node)
    {
        if (node == nullptr)
        {
            return;
        }

        freeTree(node->left);
        freeTree(node->right);

        delete node;
    }

public:
    BinarySearchTree()
        : root(nullptr)
    {
    }

    ~BinarySearchTree()
    {
        freeTree(root);
    }

    void insert(int value)
    {
        root = insert(root, value);
    }

    bool search(int value) const
    {
        return search(root, value) != nullptr;
    }

    void remove(int value)
    {
        root = remove(root, value);
    }

    void inorder() const
    {
        inorder(root);
        std::cout << "\n";
    }

    void preorder() const
    {
        preorder(root);
        std::cout << "\n";
    }

    void postorder() const
    {
        postorder(root);
        std::cout << "\n";
    }
};

int main()
{
    BinarySearchTree tree;

    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);

    std::cout << "In-order: ";
    tree.inorder();

    std::cout << "Pre-order: ";
    tree.preorder();

    std::cout << "Post-order: ";
    tree.postorder();

    std::cout << "Search 40: "
              << (tree.search(40) ? "found" : "not found")
              << "\n";

    tree.remove(30);

    std::cout << "After deleting 30: ";
    tree.inorder();

    return 0;
}