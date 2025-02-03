#include <iostream>
#include <memory>

template <class T>
class Node
{
    // Verwende ausnahmsweise public, weil dies nicht die main Logik ist
public:
    Node(T data) : data(data), prev(nullptr), next(nullptr) {}

    T data;
    std::shared_ptr<Node<T>> prev;
    std::shared_ptr<Node<T>> next;
};

template <class T>
class Queue
{
public:
    Queue() : head(nullptr), tail(nullptr), size(0) {}

    // Einfügen eines Elements am Ende der Queue (O(1))
    void push_back(T data)
    {
        auto new_node = std::make_shared<Node<T>>(data);

        if (tail)
        {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
        else
        {
            // Wenn die Queue leer ist, sowohl Kopf als auch Tail auf das neue Element setzen
            head = tail = new_node;
        }

        ++size;
    }

    // Entfernen eines Elements am Anfang der Queue (O(1))
    void pop_front()
    {
        if (head)
        {
            head = head->next;
            if (head)
                head->prev = nullptr;
            else
                tail = nullptr; // Wenn die Queue leer wird, auch den Tail nullen

            --size;
        }
    }

    // Gibt die Größe der Queue zurück (O(1))
    int get_size() const
    {
        return size;
    }

    // Gibt das Element am Anfang der Queue zurück (O(1))
    T front() const
    {
        if (head)
            return head->data;
        throw std::out_of_range("Queue is empty");
    }

    // Gibt das Element am Ende der Queue zurück (O(1))
    T back() const
    {
        if (tail)
            return tail->data;
        throw std::out_of_range("Queue is empty");
    }

private:
    std::shared_ptr<Node<T>> head;
    std::shared_ptr<Node<T>> tail;
    int size;
};

int main()
{
    Queue<int> queue;

    queue.push_back(10);
    queue.push_back(20);
    queue.push_back(30);

    std::cout << "Queue size: " << queue.get_size() << std::endl;
    std::cout << "Front: " << queue.front() << std::endl;
    std::cout << "Back: " << queue.back() << std::endl;

    queue.pop_front();
    std::cout << "Queue size after pop: " << queue.get_size() << std::endl;
    std::cout << "Front after pop: " << queue.front() << std::endl;
}
