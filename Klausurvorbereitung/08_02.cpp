#include <memory>
#include <iostream>
#include <queue>
#include <vector>

template <class T>
class BinaryTree
{
public:
    class BinaryTreeNode : public std::enable_shared_from_this<BinaryTreeNode>
    {
    public:
        using NodePtr = std::shared_ptr<BinaryTreeNode>;
        using WeakNodePtr = std::weak_ptr<BinaryTreeNode>;

        BinaryTreeNode(T newData) : data(newData) {}

        BinaryTreeNode(NodePtr parent, T newData) : parent(parent), data(newData) {}

        T get_data()
        {
            return data;
        }

        WeakNodePtr get_parent()
        {
            return parent;
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
                left_child = std::make_shared<BinaryTreeNode>(this->shared_from_this(), data);
            }
            return left_child;
        }

        NodePtr set_right_child(T data)
        {
            if (!right_child)
            {
                right_child = std::make_shared<BinaryTreeNode>(this->shared_from_this(), data);
            }
            return right_child;
        }

    private:
        T data;

        WeakNodePtr parent;
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

    void in_order_traversal(std::vector<NodePtr> &nodes, NodePtr root)
    {
        if (!root)
        {
            return;
        }
        in_order_traversal(nodes, root->get_left_child());
        nodes.push_back(root);
        in_order_traversal(nodes, root->get_right_child());
    }

    void pre_order_traversal(std::vector<NodePtr> &nodes, NodePtr root)
    {
        if (!root)
        {
            return;
        }
        nodes.push_back(root);
        pre_order_traversal(nodes, root->get_left_child());
        pre_order_traversal(nodes, root->get_right_child());
    }

    void post_order_traversal(std::vector<NodePtr> &nodes, NodePtr root)
    {
        if (!root)
        {
            return;
        }
        post_order_traversal(nodes, root->get_left_child());
        post_order_traversal(nodes, root->get_right_child());
        nodes.push_back(root);
    }

    std::vector<NodePtr> get_pre_order()
    {
        std::vector<NodePtr> nodes;
        pre_order_traversal(nodes, root);
        return nodes;
    }

    std::vector<NodePtr> get_in_order()
    {
        std::vector<NodePtr> nodes;
        in_order_traversal(nodes, root);
        return nodes;
    }

    std::vector<NodePtr> get_post_order()
    {
        std::vector<NodePtr> nodes;
        post_order_traversal(nodes, root);
        return nodes;
    }

    void print_order(const std::string &name, const std::vector<NodePtr> &order)
    {
        std::cout << name << " Traversierung: ";
        for (auto pointer : order)
        {
            std::cout << pointer->get_data() << " -> ";
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
    // Also ist keine (eindeutige) Rekonstruktion moeglich
    tree.print_order("Level Order", tree.get_level_order());
    tree.print_order("In Order", tree.get_in_order());
    tree.print_order("Pre Order", tree.get_pre_order());
    tree.print_order("Post Order", tree.get_post_order());

    std::cout << root_right_right_child->get_parent().lock()->get_data() << std::endl;
}
