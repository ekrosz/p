#include <iostream>

class Node
{
    public:
        int data;
        Node* next;
        Node* prev;
};

class DoublyLinkedList
{
    public:
        Node* head;

        DoublyLinkedList()
        {
            head = NULL;
        }

        void add(int data)
        {
            Node* node = new Node();
            node->data = data;
            node->next = head;
            node->prev = NULL;

            if (head != NULL)
                head->prev = node;

            head = node;
        }

        void display()
        {
            Node* node = head;
            while (node != NULL) {
                std::cout << node->data << " ";
                node = node->next;
            }
            std::cout << std::endl;
        }

        void remove(int key)
        {
            Node* node = head;

            if (node != NULL && node->data == key)
            {
                head = node->next;

                if (head != NULL)
                    head->prev = NULL;

                delete node;
                return;
            }

            while (node != NULL && node->data != key)
            {
                node = node->next;
            }

            if (node == NULL)
                return;

            if (node->next != NULL)
                node->next->prev = node->prev;

            if (node->prev != NULL)
                node->prev->next = node->next;

            delete node;
        }
};

int main() {
    DoublyLinkedList list;
    list.add(1);
    list.add(2);
    list.add(3);
    list.display();
    list.remove(2);
    list.display();
    return 0;
}