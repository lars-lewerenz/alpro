#include <memory>
#include <iostream>
#include <cassert>

template <class T>
class Node
{

    using NodePtr = std::shared_ptr<Node<T>>;

public:
    Node(T value) : data(value)
    {
    }

    NodePtr get_next()
    {
        return next;
    }

    T get_data()
    {
        return data;
    }

    NodePtr set_next(T data)
    {
        next = std::make_shared<Node<T>>(data);
        return next;
    }

    NodePtr set_next(NodePtr ptr)
    {
        next = ptr;
        return ptr;
    }

private:
    T data;
    NodePtr next;
};

template <class T>
class EinfachVerketteteListe
{
    using NodePtr = std::shared_ptr<Node<T>>;

public:
    EinfachVerketteteListe(T headValue)
    {
        head = std::make_shared<Node<T>>(headValue);
        anzahl = 1;
    }

    EinfachVerketteteListe() {}

    NodePtr get_head()
    {
        return head;
    }

    int size() const
    {
        return anzahl;
    }

    NodePtr next(const NodePtr &ptr)
    {
        return ptr->get_next();
    }

    NodePtr insert_front(T headValue)
    {
        anzahl++;
        NodePtr newHeadPtr = std::make_shared<Node<T>>(headValue);
        if (head)
        {
            newHeadPtr->set_next(head);
        }
        head = newHeadPtr;
        return head;
    }

    NodePtr insert_after(NodePtr predecessor, T value)
    {
        anzahl++;
        NodePtr newPtr = std::make_shared<Node<T>>(value);
        if (predecessor->get_next())
        {
            newPtr->set_next(predecessor->get_next());
        }
        predecessor->set_next(newPtr);
        return newPtr;
    }

    void remove_after(NodePtr predecessor)
    {
        if (!predecessor->get_next())
        {
            std::cout << "Hier kannst du gar nichts loeschen!" << std::endl;
            return;
        }
        NodePtr next = predecessor->get_next();
        if (next->get_next())
        {
            predecessor->set_next(next->get_next());
        }
        else
        {
            predecessor->set_next(nullptr);
        }
        next.reset();
        anzahl--;
    }

    void remove_front()
    {
        auto removed = head;
        head = head->get_next();
        removed.reset();
        anzahl--;
    }

    void drucke() const
    {
        std::cout << "Liste vom Typ " << typeid(T).name() << " (" << size() << "): " << std::endl;
        NodePtr current = head;
        while (current)
        {
            std::cout << current->get_data() << " -> ";
            current = current->get_next();
        }
        std::cout << "null" << std::endl;
    }

private:
    size_t anzahl = 0;
    NodePtr head;
};

int main()
{
    EinfachVerketteteListe<int> liste(2);
    auto head = liste.get_head();

    std::cout << "HEAD: " << head->get_data() << std::endl;

    auto nextPtr = liste.insert_after(head, 32);

    std::cout << "HEAD: " << head->get_next()->get_data() << std::endl;

    liste.insert_after(nextPtr, 42);

    liste.drucke();

    liste.remove_after(head);

    liste.drucke();

    liste.remove_front();

    liste.drucke();
}