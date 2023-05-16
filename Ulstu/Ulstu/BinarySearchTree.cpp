#include <iostream>

class Node {
public:
    int data;
    Node* left;
    Node* right;
};

class BinarySearchTree
{
    public:
        Node* root;

        BinarySearchTree()
        {
            root = NULL;
        }

        Node* createNode(int data)
        {
            Node* node = new Node();
            node->data = data;
            node->left = NULL;
            node->right = NULL;
            return node;
        }

        Node* insert(Node* node, int data)
        {
            if (node == NULL)
            {
                return createNode(data);
            }

            if (data < node->data)
            {
                node->left = insert(node->left, data);
            }
            else if (data > node->data)
            {
                node->right = insert(node->right, data);
            }

            return node;
        }

        void insert(int data)
        {
            root = insert(root, data);
        }

        Node* minValueNode(Node* node)
        {
            Node* current = node;

            while (current && current->left != NULL)
            {
                current = current->left;
            }

            return current;
        }

        Node* deleteNode(Node* root, int key)
        {
            if (root == NULL)
                return root;

            if (key < root->data)
            {
                root->left = deleteNode(root->left, key);
            }
            else if (key > root->data)
            {
                root->right = deleteNode(root->right, key);
            }
            else
            {
                if (root->left == NULL)
                {
                    Node* temp = root->right;
                    delete root;
                    return temp;
                }
                else if (root->right == NULL)
                {
                    Node* temp = root->left;
                    delete root;
                    return temp;
                }

                Node* temp = minValueNode(root->right);
                root->data = temp->data;
                root->right = deleteNode(root->right, temp->data);
            }

            return root;
        }

        void deleteValue(int key)
        {
            root = deleteNode(root, key);
        }

        Node* search(Node* root, int key)
        {
            if (root == NULL || root->data == key) {
                return root;
            }

            if (root->data < key) {
                return search(root->right, key);
            }

            return search(root->left, key);
        }

        bool search(int key)
        {
            Node* res = search(root, key);
            return res != NULL;
        }

        void inorder(Node* root)
        {
            if (root != NULL) {
                inorder(root->left);
                std::cout << root->data << " ";
                inorder(root->right);
            }
        }

        void display()
        {
            inorder(root);
            std::cout << std::endl;
        }
};

int main()
{
    BinarySearchTree tree;
    tree.insert(8);
    tree.insert(3);
    tree.insert(10);
    tree.insert(1);
    tree.insert(6);
    tree.display();
    std::cout << "Searching for 10: " << (tree.search(10) ? "Found" : "Not found") << std::endl;
    std::cout << "Deleting 10" << std::endl;
    tree.deleteValue(10);
    tree.display();
    std::cout << "Searching for 10: " << (tree.search(10) ? "Found" : "Not found") << std::endl;
    return 0;
}