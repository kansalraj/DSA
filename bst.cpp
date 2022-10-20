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

Node *minVal(Node *root)
{
    if (root == NULL)
        return NULL;

    Node *temp = root;
    while (temp->left)
        temp = temp->left;
    return temp;
}

Node *maxVal(Node *root)
{
    if (root == NULL)
        return NULL;

    Node *temp = root;
    while (temp->right)
        temp = temp->right;
    return temp;
}

Node *deleteFromBST(Node *root, int val)
{
    if (root == NULL)
        return NULL;
    if (root->data == val)
    {
        // 0 child
        if (!root->left && !root->right)
        {
            delete root;
            return NULL;
        }
        // 1 child (left)
        if (root->left && !root->right)
        {
            Node *temp = root->left;
            delete root;
            return temp;
        }
        // 1 child (right)
        if (!root->left && root->right)
        {
            Node *temp = root->right;
            delete root;
            return temp;
        }
        // 2 child
        if (root->left && root->right)
        {
            // find inorder successor val
            int mini = minVal(root->right)->data;
            root->data = mini;
            root->right = deleteFromBST(root->right, mini);
            return root;
        }
    }
    else
    {
        if (val < root->data)
        {
            root->left = deleteFromBST(root->left, val);
            return root;
        }
        else
        {
            root->right = deleteFromBST(root->right, val);
            return root;
        }
    }
}

bool isBST(Node *root, int min, int max)
{
    if (root == NULL)
        return true;
    if (root->data <= max && root->data > min)
    {
        return isBST(root->left, min, root->data) && isBST(root->right, root->data, max);
    }
    else
    {
        return false;
    }
}

bool validateBST(Node *root)
{
    return isBST(root, INT_MIN, INT_MAX);
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

    cout << endl
         << minVal(root)->data << endl;
    cout << maxVal(root)->data << endl;
    root = deleteFromBST(root, 30);
    cout << "Printing level Order BST" << endl;
    levelOrderTraversal(root);
}