#include <iostream>
#include <queue>
using namespace std;

class Node {
public:
	int data;
	Node* left;
	Node* right;
	int vc;
	Node(int data) {
		this->data = data;
		this->left = NULL;
		this->right = NULL;
		this->vc = 0;
	}
};
Node* buildTree() {
	int data;
	cin >> data;
	Node* root;
	if (data != -1)
		root = new Node(data);
	else {
		return NULL;
	}
	root->left = buildTree();
	root->right = buildTree();
	return root;
}

void preOrder(Node *root) {
	if (root == NULL) {
		return;
	}
	cout << root->data << ",";
	preOrder(root->left);
	preOrder(root->right);
}

void postOrder(Node *root) {
	if (root == NULL) {
		return;
	}
	postOrder(root->left);
	postOrder(root->right);
	cout << root->data << ",";


}

void inOrder(Node *root) {
	if (root == NULL) {
		return;
	}
	inOrder(root->left);
	cout << root->data << ",";
	inOrder(root->right);
}

void levelOrder(Node *root) {
	queue<Node*> qu;
	qu.push(root);
	while (!qu.empty()) {
		Node* to_be_removed = qu.front();
		qu.pop();
		cout << to_be_removed->data << ",";
		if (to_be_removed->left != NULL) {
			qu.push(to_be_removed->left);
		}
		if (to_be_removed->right != NULL) {
			qu.push(to_be_removed->right);
		}
	}
}

int vertexCover(Node* root) {
	if (root == NULL) return 0;
	if (root->left == NULL and root->right == NULL) return 0;
	if (root->vc != 0) {
		return root->vc;
	}
	int including = 1 + vertexCover(root->left) + vertexCover(root->right);
	int excluding = 0;
	if (root->left != NULL) {
		excluding = excluding + 1 + vertexCover(root->left->left) + vertexCover(root->left->right);
	}
	if (root->right != NULL) {
		excluding = excluding + 1 + vertexCover(root->right->left) + vertexCover(root->right->right);
	}

	root->vc = min(including, excluding);
	return root->vc;
}

int minHeight(Node* root) {
	if (root == NULL) {
		return 0;
	}
	if (root->left == NULL and root->right == NULL) {
		return 1;
	}
	int lh = INT_MAX;
	int rh = INT_MAX;
	if (root->left != NULL)
		lh = minHeight(root->left);
	if (root->right != NULL)
		rh = minHeight(root->right);

	return 1 + min(lh, rh);
}

int maxHeight(Node* root) {
	if (root == NULL) {
		return 0;
	}

	int lh = maxHeight(root->left);
	int rh = maxHeight(root->right);

	return 1 + max(lh, rh);
}

class Pair {
public:
	int height;
	int diameter;
};


Pair diameter(Node* root) {
	if (root == NULL) {
		Pair p;
		p.diameter = 0;
		p.height = 0;
		return p;
	}

	Pair result;
	Pair left = diameter(root->left);
	Pair right = diameter(root->right);
	result.height = max(left.height, right.height) + 1;
	result.diameter = max(left.diameter, max(right.diameter, left.height + right.height));
	return result;

}

int diameterOfBinaryTree(Node* root) {
	Pair p = diameter(root);
	return p.diameter;
}

int maxPathFromRoot2Leaf(Node* root) {
	if (root == NULL) return 0;

	int left = maxPathFromRoot2Leaf(root->left);
	int right = maxPathFromRoot2Leaf(root->right);

	return max(left, right) + root->data;
}

int maxsum = 0;

int maxSumFromLeaf2Leaf(Node* root) {
	if (root == NULL) return 0;

	int left = maxSumFromLeaf2Leaf(root->left);
	int right = maxSumFromLeaf2Leaf(root->right);
	int cand = left + right + root->data;
	if (maxsum < cand) maxsum = cand;
	return max(left, right) + root->data;
}

int maxSum = INT_MIN;
int helper(Node* root) {
	if (root == NULL) {
		return 0;
	}
	int left = helper(root->left);
	int right = helper(root->right);

	int cand1 = root->val;
	int cand2 = left + root->val;
	int cand3 = right + root->val;
	int cand4 = left + right + root->val;

	maxSum = max(cand1, max(cand2, max(cand3, max(cand4, maxSum))));

	return max(left, max(right, 0)) + root->val;
	// return max(left, right) + root->val;


}
int maxPathSum(Node* root) {
	helper(root);
	return maxSum;
}

int main(int argc, char const *argv[])
{
	Node* root = buildTree();
	// preOrder(root);
	// cout << endl;
	// levelOrder(root);
	// cout << endl;
	// cout << vertexCover(root);
	// cout << endl;
	// cout << minHeight(root) << endl;
	// cout << maxHeight(root) << endl;
	// maxSumFromLeaf2Leaf(root);
	// cout << maxSum;
	return 0;
}
