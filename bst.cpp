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

int solveKthSmallest(Node *root, int &i, int k)
{
    if (root == NULL)
        return -1;

    // L
    int left = solveKthSmallest(root->left, i, k);
    if (left != -1)
        return left;

    // N
    i++;
    if (i == k)
        return root->data;

    // R
    return solveKthSmallest(root->right, i, k);
}

int kthSmallest(Node *root, int k)
{
    int i = 0;
    return solveKthSmallest(root, i, k);
}

pair<int, int> predecessorSuccessor(Node *root, int key)
{
    Node *temp = root;
    int pred = -1;
    int succ = -1;

    // Finding key
    while (temp->data != key)
    {
        if (temp->data > key)
        {
            succ = temp->data;
            temp = temp->left;
        }
        else
        {
            pred = temp->data;
            temp = temp->right;
        }
    }

    // pred ;
    Node *left = temp->left;
    while (left)
    {
        pred = left->data;
        left = left->right;
    }

    // succ
    Node *right = temp->right;
    while (right)
    {
        succ = right->data;
        right = right->left;
    }
    return {pred, succ};
}

Node *LCAinaBSTRecursive(Node *root, Node *P, Node *Q)
{
    if (root == NULL)
        return NULL;
    if (root->data > P->data && root->data > Q->data)
        return LCAinaBSTRecursive(root->left, P, Q);
    if (root->data < P->data && root->data < Q->data)
        return LCAinaBSTRecursive(root->right, P, Q);
    return root;
}

Node *LCAinaBSTIterative(Node *root, Node *P, Node *Q)
{
    if (root == NULL)
        return NULL;
    while (root)
    {
        if (root->data > P->data && root->data > Q->data)
            root = root->left;
        else if (root->data < P->data && root->data < Q->data)
            root = root->right;
        else
            return root;
    }
}

void storeUsingInorder(Node *root, vector<int> &in)
{
    if (root == NULL)
        return;
    storeUsingInorder(root->left, in);
    in.push_back(root->data);
    storeUsingInorder(root->right, in);
}

bool twoSumInBST(Node *root, int target)
{
    vector<int> inorderVal;
    storeUsingInorder(root, inorderVal);
    int i = 0, j = inorderVal.size() - 1;
    while (i < j)
    {
        int sum = inorderVal[i] + inorderVal[j];
        if (sum == target)
            return true;
        if (sum > target)
            j--;
        else
            i++;
    }
    return false;
}

Node *flattenBSTToSortedLL(Node *root)
{
    vector<int> inorderVal;
    storeUsingInorder(root, inorderVal);
    int n = inorderVal.size();

    Node *newRoot = new Node(inorderVal[0]);
    Node *curr = newRoot;

    for (int i = 1; i < n; i++)
    {
        Node *temp = new Node(inorderVal[i]);
        curr->left = NULL;
        curr->right = temp;
        curr = temp;
    }
    curr->left = NULL;
    curr->right = NULL;
    return newRoot;
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