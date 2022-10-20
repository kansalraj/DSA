#include <iostream>
#include <queue>

using namespace std;

class Node
{
public:
    int data;
    Node *left;
    Node *right;

    Node(int d)
    {
        this->data = d;
        this->left = NULL;
        this->right = NULL;
    }
};

Node *insertIntoBST(Node *root, int data)
{
    // base case
    if (root == NULL)
    {
        root = new Node(data);
        return root;
    }
    if (data > root->data)
        root->right = insertIntoBST(root->right, data);
    else
        root->left = insertIntoBST(root->left, data);
    return root;
}

void takeInput(Node *&root)
{
    int data;
    cin >> data;

    while (data != -1)
    {
        root = insertIntoBST(root, data);
        cin >> data;
    }
}

void levelOrderTraversal(Node *root)
{
    queue<Node *> q;
    q.push(root);
    q.push(NULL);

    while (!q.empty())
    {
        Node *temp = q.front();
        q.pop();
        if (temp == NULL)
        {
            cout << endl;
            if (!q.empty())
            {
                q.push(NULL);
            }
        }
        else
        {
            cout << temp->data << " ";
            if (temp->left)
                q.push(temp->left);
            if (temp->right)
                q.push(temp->right);
        }
    }
}

void inorder(Node *root)
{
    if (root == NULL)
        return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void preorder(Node *root)
{
    if (root == NULL)
        return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void postOrder(Node *root)
{
    if (root == NULL)
        return;
    postOrder(root->left);
    postOrder(root->right);
    cout << root->data << " ";
}

// recursive search
bool searchInBST(Node *root, int x)
{
    if (root == NULL)
        return false;
    if (root->data == x)
        return true;
    if (x < root->data)
        return searchInBST(root->left, x);
    else
        return searchInBST(root->right, x);
}

bool iterativeSearchInBST(Node *root, int x)
{
    Node *temp = root;
    while (temp)
    {
        if (temp->data == x)
            return true;
        if (temp->data > x)
            temp = temp->left;
        else
            temp = temp->right;
    }
    return false;
}

int main()
{
    std::cout << "make BST" << std::endl;
    Node *root = NULL;
    takeInput(root);

    cout << "Printing level Order BST" << endl;
    levelOrderTraversal(root);

    cout << "Printing Inorder" << endl;
    inorder(root);

    cout << endl
         << "Printing Preorder" << endl;
    preorder(root);

    cout << endl
         << "Printing Postorder" << endl;
    postOrder(root);
}