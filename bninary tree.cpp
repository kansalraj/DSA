#include <iostream>
#include <queue>
#include <stack>
#include <map>
using namespace std;

class node
{
public:
    int data;
    node *left;
    node *right;

    node(int d)
    {
        this->data = d;
        this->left = NULL;
        this->right = NULL;
    }
};

node *buildTree(node *root)
{
    cout << "Enter the data: " << endl;
    int data;
    cin >> data;
    root = new node(data);

    if (data == -1)
        return NULL;

    cout << "Enter the data for left of " << data << endl;
    root->left = buildTree(root->left);
    cout << "Enter the data for right of " << data << endl;
    root->right = buildTree(root->right);
    return root;
}

void levelOrderTraversal(node *root)
{
    queue<node *> q;
    q.push(root);
    q.push(NULL);

    while (!q.empty())
    {
        node *temp = q.front();
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

void reverseOrderTraversal(node *root)
{
    queue<node *> q;
    stack<node *> s;
    q.push(root);
    q.push(NULL);

    while (!q.empty())
    {
        node *temp = q.front();
        q.pop();
        if (temp == NULL)
        {
            s.push(NULL);
            // cout << endl;
            if (!q.empty())
            {
                q.push(NULL);
            }
        }
        else
        {
            s.push(temp);
            // cout << temp->data << " ";
            if (temp->left)
                q.push(temp->left);
            if (temp->right)
                q.push(temp->right);
        }
    }

    while (!s.empty())
    {
        node *temp = s.top();
        s.pop();
        if (temp == NULL)
        {
            cout << endl;
        }
        else
        {
            cout << temp->data << " ";
        }
    }
    cout << endl;
}

void inorder(node *root)
{
    if (root == NULL)
        return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

void preorder(node *root)
{
    if (root == NULL)
        return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void buildFromLevelOrder(node *&root)
{
    queue<node *> q;
    cout << "Enter data for root :" << endl;
    int data;
    cin >> data;
    root = new node(data);
    q.push(root);

    while (!q.empty())
    {
        node *temp = q.front();
        q.pop();

        cout << "Enter data for left node of :" << temp->data << endl;
        int leftData;
        cin >> leftData;
        if (leftData != -1)
        {
            temp->left = new node(leftData);
            q.push(temp->left);
        }

        cout << "Enter data for right node of :" << temp->data << endl;
        int rightData;
        cin >> rightData;
        if (rightData != -1)
        {
            temp->right = new node(rightData);
            q.push(temp->right);
        }
    }
}

int noOfLeafNodesRecusion(node *node)
{
    if (node == NULL)
        return 0;
    if (node->left == NULL && node->right == NULL)
        return 1;
    return noOfLeafNodesRecusion(node->left) + noOfLeafNodesRecusion(node->right);
}

void noOfLeavesUsingInorder(node *root, int &count)
{
    if (root == NULL)
        return;
    noOfLeavesUsingInorder(root->left, count);
    if (root->left == NULL && root->right == NULL)
        count++;
    noOfLeavesUsingInorder(root->right, count);
}

int heightByRecursion(node *root)
{
    if (root == NULL)
        return 0;
    int l = heightByRecursion(root->left);
    int r = heightByRecursion(root->right);
    if (l > r)
    {
        return 1 + l;
    }
    else
    {
        return 1 + r;
    }
}

pair<int, int> diamtereFast(node *root)
{
    if (root == NULL)
    {
        pair<int, int> p = make_pair(0, 0);
        return p;
    }

    pair<int, int> left = diamtereFast(root->left);
    pair<int, int> right = diamtereFast(root->right);

    int op1 = left.first;
    int op2 = right.first;
    int op3 = left.second + right.second + 1;
    pair<int, int> ans;
    ans.first = max(op1, max(op2, op3));
    ans.second = max(left.second, right.second) + 1;
    return ans;
}

int diameter(node *root)
{
    return diamtereFast(root).first;
}

pair<bool, int> isBalancedTreeFast(node *root)
{
    if (root == NULL)
        return make_pair(true, 0);

    pair<bool, int> left = isBalancedTreeFast(root->left);
    pair<bool, int> right = isBalancedTreeFast(root->right);

    bool op1 = left.first;
    bool op2 = right.first;
    bool op3 = abs(left.second - right.second) <= 1;
    return make_pair(op1 && op2 && op3, max(left.second, right.second) + 1);
}

bool isBalancedTree(node *root)
{
    return isBalancedTreeFast(root).first;
}

bool isIdentical(node *r1, node *r2)
{
    if (r1 == NULL && r2 == NULL)
        return true;
    if (r1 == NULL && r2 != NULL)
        return false;
    if (r1 != NULL && r2 == NULL)
        return false;

    bool left = isIdentical(r1->left, r2->left);
    bool right = isIdentical(r1->right, r2->right);
    return left && right && r1->data == r2->data;
}

pair<bool, int> isSumTreeFast(node *root)
{
    if (root == NULL)
    {
        return make_pair(true, 0);
    }
    if (root->left == NULL && root->right == NULL)
    {
        return make_pair(true, root->data);
    }

    pair<bool, int> left = isSumTreeFast(root->left);
    pair<bool, int> right = isSumTreeFast(root->right);
    return make_pair(left.first && left.second && root->data == left.second + right.second, root->data + left.second + right.second);
}

bool isSumTree(node *root)
{
    return isSumTreeFast(root).first;
}

vector<int> zigZagTraversasl(node *root)
{
    vector<int> result;
    if (root == NULL)
        return result;

    queue<node *> q;
    q.push(root);
    bool leftToRight = true;

    while (!q.empty())
    {
        int size = q.size();
        vector<int> ans(size);
        for (int i = 0; i < size; i++)
        {
            node *temp = q.front();
            q.pop();

            int index = leftToRight ? i : size - i - 1;
            ans[index] = temp->data;

            if (temp->left)
                q.push(temp->left);
            if (temp->right)
                q.push(temp->right);
        }

        leftToRight = !leftToRight;
        for (auto i : ans)
            result.push_back(i);
    }
    return result;
}

void traverseLeft(node *root, vector<int> &ans)
{
    if ((root == NULL) || (root->left == NULL && root->right == NULL))
        return;
    ans.push_back(root->data);

    if (root->left)
        traverseLeft(root->left, ans);
    else
        traverseLeft(root->right, ans);
}

void traverseLeaf(node *root, vector<int> &ans)
{
    if (root == NULL)
        return;
    if (root->left == NULL && root->right == NULL)
    {
        ans.push_back(root->data);
        return;
    }
    traverseLeaf(root->left, ans);
    traverseLeaf(root->right, ans);
}

void traverseRight(node *root, vector<int> &ans)
{
    if ((root == NULL) || (root->left == NULL && root->right == NULL))
        return;
    if (root->right)
        traverseRight(root->right, ans);
    else
        traverseRight(root->left, ans);
    ans.push_back(root->data);
}

vector<int> boundary(node *root)
{
    vector<int> ans;
    if (root == NULL)
        return ans;

    ans.push_back(root->data);

    traverseLeft(root->left, ans);

    traverseLeaf(root->left, ans);
    traverseLeaf(root->right, ans);

    traverseRight(root->right, ans);
    return ans;
}

vector<int> verticalOrder(node *root)
{
    map<int, map<int, vector<int>>> nodex;
    queue<pair<node *, pair<int, int>>> q;
    vector<int> ans;

    if (root == NULL)
        return ans;

    q.push(make_pair(root, make_pair(0, 0)));

    while (!q.empty())
    {
        pair<node *, pair<int, int>> temp = q.front();
        q.pop();
        node *frontNode = temp.first;
        int hd = temp.second.first;
        int lvl = temp.second.second;

        nodex[hd][lvl].push_back(frontNode->data);

        if (frontNode->left)
        {
            q.push(make_pair(frontNode->left, make_pair(hd - 1, lvl + 1)));
        }
        if (frontNode->right)
        {
            q.push(make_pair(frontNode->right, make_pair(hd + 1, lvl + 1)));
        }
    }

    for (auto i : nodex)
    {
        for (auto j : i.second)
        {
            for (auto k : j.second)
            {
                ans.push_back(k);
            }
        }
    }
    return ans;
}

vector<int> topView(node *root)
{
    vector<int> ans;
    if (root == NULL)
        return ans;
    map<int, int> topNode;
    queue<pair<node *, int>> q;
    q.push(make_pair(root, 0));

    while (!q.empty())
    {
        pair<node *, int> temp = q.front();
        q.pop();
        node *tempNode = temp.first;
        int hd = temp.second;
        if (topNode.find(hd) == topNode.end())
            topNode[hd] = tempNode->data;
        if (tempNode->left)
            q.push(make_pair(tempNode->left, hd - 1));
        if (tempNode->right)
            q.push(make_pair(tempNode->right, hd + 1));
    }
    for (auto i : topNode)
    {
        ans.push_back(i.second);
    }
    return ans;
}

vector<int> bottomView(node *root)
{
    vector<int> ans;
    if (root == NULL)
        return ans;

    map<int, int> bottoms;
    queue<pair<node *, int>> q;

    q.push(make_pair(root, 0));
    while (!q.empty())
    {
        pair<node *, int> temp = q.front();
        q.pop();
        bottoms[temp.second] = temp.first->data;
        if (temp.first->left)
            q.push(make_pair(temp.first->left, temp.second - 1));
        if (temp.first->right)
            q.push(make_pair(temp.first->right, temp.second + 1));
    }

    for (auto i : bottoms)
    {
        ans.push_back(i.second);
    }
    return ans;
}

void solveLeftView(node *root, vector<int> &ans, int lvl)
{
    if (root == NULL)
        return;

    if (lvl == ans.size())
        ans.push_back(root->data);
    solveLeftView(root->left, ans, lvl + 1);
    solveLeftView(root->right, ans, lvl + 1);
}

vector<int> leftView(node *root)
{
    vector<int> ans;
    solveLeftView(root, ans, 0);
    return ans;
}

void solveRightView(node *root, vector<int> &ans, int lvl)
{
    if (root == NULL)
        return;

    if (lvl == ans.size())
        ans.push_back(root->data);
    solveRightView(root->right, ans, lvl + 1);

    solveRightView(root->left, ans, lvl + 1);
}

vector<int> rightView(node *root)
{
    vector<int> ans;
    solveRightView(root, ans, 0);
    return ans;
}

void solveSumOfLongRootToLeafPath(node *root, int len, int &maxLen, int sum, int &maxSum)
{
    if (root == NULL)
    {
        if (len > maxLen)
        {
            maxLen = len;
            maxSum = sum;
        }
        if (len == maxLen)
            maxSum = max(sum, maxSum);
    }
    else
    {
        solveSumOfLongRootToLeafPath(root->left, len + 1, maxLen, sum + root->data, maxSum);
        solveSumOfLongRootToLeafPath(root->right, len + 1, maxLen, sum + root->data, maxSum);
    }
}

int sumOfLongRootToLeafPath(node *root)
{
    int len = 0;
    int maxLen = 0;
    int sum = 0;
    int maxSum = INT_MIN;
    solveSumOfLongRootToLeafPath(root, len, maxLen, sum, maxSum);
    return maxSum;
}

// Function to return the lowest common ancestor in a Binary Tree.
node *lca(node *root, int n1, int n2)
{
    if (root == NULL)
        return NULL;
    if (root->data == n1 || root->data == n2)
        return root;
    node *leftAns = lca(root->left, n1, n2);
    node *rightAns = lca(root->right, n1, n2);
    if (leftAns == NULL && rightAns == NULL)
        return NULL;
    if (leftAns != NULL && rightAns != NULL)
        return root;
    if (leftAns == NULL && rightAns != NULL)
        return rightAns;
    if (leftAns != NULL && rightAns == NULL)
        return leftAns;
}

void solveSumKPaths(node *root, int k, int &count, vector<int> path)
{
    if (root == NULL)
        return;
    path.push_back(root->data);
    solveSumKPaths(root->left, k, count, path);
    solveSumKPaths(root->right, k, count, path);
    int sum = 0;
    for (int i = path.size() - 1; i >= 0; i--)
    {
        sum += path[i];
        if (sum == k)
            count++;
    }
    // path.pop_back();
}

int sumKPaths(node *root, int k)
{
    int count = 0;
    vector<int> path;
    solveSumKPaths(root, k, count, path);
    return count;
}

node *solveKthAncestor(node *root, int &k, int nodeVal)
{
    if (root == NULL)
        return NULL;
    if (root->data == nodeVal)
        return root;

    node *leftAns = solveKthAncestor(root->left, k, nodeVal);
    node *rightAns = solveKthAncestor(root->right, k, nodeVal);

    if (leftAns != NULL || rightAns != NULL)
    {
        k--;
        if (k <= 0)
        {
            k = INT_MAX;
            return root;
        }
        return leftAns != NULL ? leftAns : rightAns;
    }
    return NULL;
}

int kthAncestor(node *root, int k, int nodeVal)
{
    node *ans = solveKthAncestor(root, k, nodeVal);
    if (ans == NULL || ans->data == nodeVal)
        return -1;
    return ans->data;
}

void createMapping(int in[], int n, map<int, int> &nodeToIndex)
{
    for (int i = 0; i < n; i++)
        nodeToIndex[in[i]] = i;
}

node *solveBuildTreeFromInOrderAndPreOrder(int in[], int pre[], int &preOrderIndex, int inOrderStart,
                                           int inOrderEnd, int n, map<int, int> &nodeToIndex)
{
    if (preOrderIndex >= n || (inOrderStart > inOrderEnd))
        return NULL;

    int element = pre[preOrderIndex++];
    node *root = new node(element);
    int pos = nodeToIndex[element];

    root->left = solveBuildTreeFromInOrderAndPreOrder(in, pre, preOrderIndex, inOrderStart,
                                                      pos - 1, n, nodeToIndex);
    root->right = solveBuildTreeFromInOrderAndPreOrder(in, pre, preOrderIndex, pos + 1,
                                                       inOrderEnd, n, nodeToIndex);
    return root;
}

node *buildTreeFromInOrderAndPreOrder(int in[], int pre[], int n)
{
    map<int, int> nodeToIndex;
    createMapping(in, n, nodeToIndex);
    int preOrderIndex = 0;
    node *ans = solveBuildTreeFromInOrderAndPreOrder(in, pre, preOrderIndex,
                                                     0, n - 1, n, nodeToIndex);
    return ans;
}

node *solveBuildTreeFromInAndPostOrder(int in[], int post[], int &postOrderIndex, int inOrderStart,
                                       int inOrderEnd, int n, map<int, int> &nodeToIndex)
{
    if (postOrderIndex < 0 || inOrderStart > inOrderEnd)
        return NULL;
    int ele = post[postOrderIndex--];
    int pos = nodeToIndex[ele];
    node *root = new node(ele);
    root->right = solveBuildTreeFromInAndPostOrder(in, post, postOrderIndex, pos + 1, inOrderEnd, n,
                                                   nodeToIndex);
    root->left = solveBuildTreeFromInAndPostOrder(in, post, postOrderIndex, inOrderStart, pos - 1, n,
                                                  nodeToIndex);
    return root;
}

node *buildTreeFromInAndPostOrder(int in[], int post[], int n)
{
    map<int, int> nodeToIndex;
    createMapping(in, n, nodeToIndex);
    int postOrderIndex = n - 1;
    node *ans = solveBuildTreeFromInAndPostOrder(in, post, postOrderIndex, 0, n - 1, n, nodeToIndex);
    return ans;
}

node *createNodeToParent(node *root, int target, map<node *, node *> &nodeToParent)
{
    node *targetNode = NULL;
    queue<node *> q;
    q.push(root);
    nodeToParent[root] = NULL;

    while (!q.empty())
    {
        node *front = q.front();
        q.pop();

        if (front->data == target)
            targetNode = front;
        if (front->left)
        {
            q.push(front->left);
            nodeToParent[front->left] = front;
        }
        if (front->right)
        {
            q.push(front->right);
            nodeToParent[front->right] = front;
        }
    }
    return targetNode;
}

int burnTree(node *root, map<node *, node *> &nodeToParent)
{
    int ans = 0;
    map<node *, bool> visited;
    queue<node *> q;
    q.push(root);
    visited[root] = true;

    while (!q.empty())
    {
        int size = q.size();
        for (int i = 0; i < size; i++)
        {
            node *front = q.front();
            q.pop();

            if (front->left && !visited[front->left])
            {
                visited[front->left] = true;
                q.push(front->left);
            }
            if (front->right && !visited[front->right])
            {
                visited[front->right] = true;
                q.push(front->right);
            }
            if (nodeToParent[front] && !visited[nodeToParent[front]])
            {
                visited[nodeToParent[front]] = true;
                q.push(nodeToParent[front]);
            }
        }
        if (q.size())
            ans++;
    }
    return ans;
}

int minTimeToBurnTree(node *root, int target)
{
    map<node *, node *> nodeToParent;
    node *targetNode = createNodeToParent(root, target, nodeToParent);
    int ans = burnTree(targetNode, nodeToParent);
    return ans;
}

void morrisTraversalInorder(node *root)
{
    node *curr = root;
    while (curr)
    {
        if (curr->left)
        {
            node *pred = curr->left;
            // finding predecessor
            while (pred->right && pred->right != curr)
                pred = pred->right;

            if (pred->right == NULL)
            {
                pred->right = curr;
                curr = curr->left;
            }
            else
            {
                pred->right = NULL;
                cout << curr->data << " ";
                curr = curr->right;
            }
        }
        else
        {
            cout << curr->data << " ";
            curr = curr->right;
        }
    }
}

// flatten using Morris Traversal
void flatten(node *root)
{
    node *curr = root;
    while (curr)
    {
        if (curr->left)
        {
            node *pred = curr->left;
            while (pred->right)
                pred = pred->right;
            pred->right = curr->right;
            curr->right = curr->left;
            curr->left = NULL;
        }
        curr = curr->right;
    }
}

int main()
{
    node *root = NULL;
    buildFromLevelOrder(root);
    // 1 3 7 -1 -1 11 -1 -1 5 17 -1 -1 -1
    // 1 3 5 7 11 17 -1 -1 -1 -1 -1 -1 -1
    // cout<<"NoOfLeaves: "<<noOfLeafNodesRecusion(root)<<endl;
    // int count = 0;
    // noOfLeavesUsingInorder(root, count);
    // cout<<"NoOfLeaves: "<<count<<endl;
    // cout<<"Diameter of tree: "<<heightByRecursion(root)<<endl;
    // cout<<"Height of tree: "<<diameter(root)<<endl;
    // cout << "isBalancedTree: " << isBalancedTree(root) << endl;
    // cout << "isSumTree: " << isSumTree(root) << endl;
    vector<int> v = zigZagTraversasl(root);
    for (int i; i < v.size(); i++)
    {
        cout << v[i] << " ";
    }
    std::cout << endl
              << "Helloxx a" << std::endl;
}