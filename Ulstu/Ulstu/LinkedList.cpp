#include <iostream>

class Node
{
    public:
        int data;
        Node* next;
};

class LinkedList
{
    public:
        Node* head;

        LinkedList()
        {
            head = NULL;
        }

        void add(int data)
        {
            Node* node = new Node();
            node->data = data;
            node->next = head;
            head = node;
        }

        void display()
        {
            Node* node = head;

            while (node != NULL)
            {
                std::cout << node->data << " ";
                node = node->next;
            }
            std::cout << std::endl;
        }

        void remove(int key)
        {
            Node* node = head;
            Node* prev = NULL;

            if (node != NULL && node->data == key)
            {
                head = node->next;
                delete node;
                return;
            }

            while (node != NULL && node->data != key)
            {
                prev = node;
                node = node->next;
            }

            if (node == NULL)
                return;

            prev->next = node->next;

            delete node;
        }
};

int main() {
    LinkedList list;
    list.add(1);
    list.add(2);
    list.add(3);
    list.display();
    list.remove(2);
    list.display();
    return 0;
}