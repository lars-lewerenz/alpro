#include <memory>
#include <iostream>
#include <queue>

template <class T>
class BinaryTree
{
public:
    class BinaryTreeNode
    {
    public:
        using NodePtr = std::shared_ptr<BinaryTreeNode>;

        BinaryTreeNode(T newData) : data(newData) {}

        T get_data()
        {
            return data;
        }

        NodePtr get_left_child()
        {
            return left_child;
        }

        NodePtr get_right_child()
        {
            return right_child;
        }

        NodePtr set_left_child(T data)
        {
            if (!left_child)
            {
                left_child = std::make_shared<BinaryTreeNode>(data);
            }
            return left_child;
        }

        NodePtr set_right_child(T data)
        {
            if (!right_child)
            {
                right_child = std::make_shared<BinaryTreeNode>(data);
            }
            return right_child;
        }

    private:
        T data;
        NodePtr left_child;
        NodePtr right_child;
    };

    using NodePtr = typename BinaryTreeNode::NodePtr;

    BinaryTree() {}

    NodePtr get_root()
    {
        return root;
    }

    NodePtr set_root(T data)
    {
        root = std::make_shared<BinaryTreeNode>(data);
        return root;
    }

    std::vector<NodePtr> get_level_order()
    {
        std::vector<NodePtr> nodes;
        std::queue<NodePtr> q;
        q.push(root);

        while (!q.empty())
        {
            NodePtr node = q.front();
            q.pop();
            nodes.push_back(node);

            if (node->get_left_child())
            {
                q.push(node->get_left_child());
            }
            if (node->get_right_child())
            {
                q.push(node->get_right_child());
            }
        }
        return nodes;
    }

    void print_level_order()
    {
        for (auto pointer : get_level_order())
        {
            std::cout << " " << pointer->get_data() << " -> ";
        }
        std::cout << " null" << std::endl;
    }

private:
    NodePtr root;
};

int main()
{
    BinaryTree<int> tree;

    tree.set_root(42);
    auto root = tree.get_root();

    if (root)
    {
        std::cout << "Root data: " << root->get_data() << std::endl;
    }

    auto root_left_child = root->set_left_child(11);
    auto root_right_child = root->set_right_child(22);

    auto root_left_left_child = root_left_child->set_left_child(9);
    root_left_left_child->set_left_child(-6);
    root_left_left_child->set_right_child(22);

    root_left_child->set_right_child(0);

    auto root_right_right_child = root_right_child->set_right_child(544);
    root_right_right_child->set_left_child(11);

    // bei diesem Beispiel nicht so sinnvoll, weil der Baum NICHT linksvollstaendig ist.
    tree.print_level_order();
}
