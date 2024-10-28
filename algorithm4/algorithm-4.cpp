#include <iostream>

using namespace std;

class BinaryTree
{
public:
    struct Node
    {
    public:
        string value;
        int countRepeat = 0;
        Node *right;
        Node *left;
    };
    Node *first;

    BinaryTree()
    {
        first = NULL;
    }

    void add(string newValue)
    {
        if (first == NULL)
        {
            Node *newNode = new Node;
            newNode->value = newValue;
            newNode->left = NULL;
            newNode->right = NULL;
            newNode->countRepeat = 1;
            first = newNode;
        }
        else
        {
            Node *current = first;
            while (true)
            {
                if (newValue > current->value)
                {
                    if (current->right == NULL)
                    {
                        current->right = new Node;
                        current->right->value = newValue;
                        current->right->right = NULL;
                        current->right->left = NULL;
                        current->right->countRepeat = 1;
                        break;
                    }
                    current = current->right;
                }
                else if (newValue < current->value)
                {
                    if (current->left == NULL)
                    {
                        current->left = new Node;
                        current->left->value = newValue;
                        current->left->right = NULL;
                        current->left->left = NULL;
                        current->left->countRepeat = 1;
                        break;
                    }
                    current = current->left;
                }
                else if (newValue == current->value)
                {
                    current->countRepeat++;
                    break;
                }
            }
        }
    }

    void inOrder(Node *node)
    {
        if (node->left != NULL)
        {
            inOrder(node->left);
        }
        for (int i = 0; i < node->countRepeat; i++)
        {
            cout << node->value << "\n";
        }
        if (node->right != NULL)
        {
            inOrder(node->right);
        }
    }
};

int main()
{

    ios_base::sync_with_stdio(false);
    cout.tie(nullptr);
    cin.tie(nullptr);

    int n;
    string line;
    BinaryTree tree;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cin >> line;
        tree.add(line);
    }

    tree.inOrder(tree.first);

    return 0;
}