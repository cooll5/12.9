#include<iostream>
#include<windows.h>

using namespace std;

typedef int Info;
struct Node
{
	Node* left,
		* right;
	Info info;
};

Node* CreateTree(int nodeCount)
{
	if (nodeCount == 0)
		return NULL;
	else
	{
		Node* newNode = new Node;
		cout << " Enter node value: ";
		cin >> newNode->info;
		int leftCount = nodeCount / 2;
		int rightCount = nodeCount - leftCount - 1;
		newNode->left = CreateTree(leftCount);
		newNode->right = CreateTree(rightCount);
		return newNode;
	}
}

void PrintTree(Node* root, int level)
{
	if (root != NULL)
	{
		PrintTree(root->right, level + 1);
		for (int i = 1; i++ <= level;)
			cout << "  ";
		cout << root->info << endl;
		PrintTree(root->left, level + 1);
	}
}

void PrefixOrder(Node* root, int& S)
{
	if (root != NULL)
	{
		if (root->info)
		{
			S += root->info;

			cout << root->info << " ";
		}
		PrefixOrder(root->left,  S);
		PrefixOrder(root->right,  S);
	}
}

Node* rightRotation(Node* p)
{
	Node* q = p->left;
	p->left = q->right;
	q->right = p;
	return q;
}
Node* leftRotation(Node* q)
{
	Node* p = q->right;
	q->right = p->left;
	p->left = q;
	return p;
}
int Height(Node* root)
{
	if (root == NULL)
		return 0;
	int hL = Height(root->left);
	int hR = Height(root->right);
	return (hL > hR ? hL : hR) + 1;
}
int BFactor(Node* root)
{
	return Height(root->right) - Height(root->left);
}

Node* balanceHeight(Node* p)
{
	if (BFactor(p) == 2)
	{
		if (BFactor(p->right) < 0)
			p->right = rightRotation(p->right);
		return leftRotation(p);
	}
	if (BFactor(p) == -2)
	{
		if (BFactor(p->left) > 0)
			p->left = leftRotation(p->left);
		return rightRotation(p);
	}
	return p;
}

Node* Insert(Node* p, Info value)
{
	if (!p)
	{
		p = new Node;
		p->info = value;
		p->left = NULL;
		p->right = NULL;
		return p;
	}
	if (value < p->info)
		p->left = Insert(p->left, value);
	else
		if (value > p->info)
			p->right = Insert(p->right, value);
	return balanceHeight(p);
}

Node* FindMax(Node* root)
{
	if (root->right != NULL)
		return FindMax(root->right);
	else
		return root;
}

Node* BinarySearchDelete(Node* root, Info value)
{
	if (NULL == root) return NULL; // �� ������� �����
	if (root->info == value) // ������� �����
	{
		if (NULL == root->left && NULL == root->right) // �������� �����
		{
			delete root;
			return NULL;
		}
		if (NULL == root->right && root->left != NULL) // ����� � �����
		{ // (����) ��������
			Node* temp = root->left;

			delete root;
			return temp;
		}
		if (NULL == root->left && root->right != NULL) // ����� � �����
		{ // (������) ��������
			Node* temp = root->right;
			delete root;
			return temp;
		} // ����� � �����
		root->info = FindMax(root->left)->info; // ���������
		root->left = BinarySearchDelete(root->left, root->info);
		return root;
	}
	// �� ������� ����� -
	if (value < root->info) // ������� ����� �
	{ // ����� ��-�����
		root->left = BinarySearchDelete(root->left, value);
		return root;
	}
	if (value > root->info) // ������� ����� �
	{ // ������� ��-�����
		root->right = BinarySearchDelete(root->right, value);
		return root;
	}
	return root;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int n, value, menu, S = 0;
	cout << "����� ������� ��������: ";
	cin >> n;

	bool found = false;
	Node* root = NULL;

	for (int i = 0; i++ < n;)
	{
		cout << " �������: "; cin >> value;
		root = Insert(root, value);
	}

	cout << endl;

	do {
		cout << "������� ��:" << endl;
		cout << " [1] -  ������� ������;" << endl;
		cout << " [2] -  �������� �������;" << endl;
		cout << " [3] -  ������������ ������;" << endl;
		cout << " [4] -  �������� �������;" << endl;
		cout << " [5] -  ������ ������ �����;" << endl;
		cout << " [6] -  ������� ����;" << endl;
		cout << " [0] -   �����" << endl;
		cout << endl;
		cin >> menu;

		switch (menu)
		{
		case 1:
			PrintTree(root, 0);
			cout << endl;
			break;
		case 2:
			cout << " �������: "; cin >> value;
			Insert(root, value);
			cout << endl;
			break;
		case 3:
			balanceHeight(root);
			cout << endl;
			break;
		case 4:
			cout << " �������: "; cin >> value;
			BinarySearchDelete(root, value);
			cout << endl;
			break;
		case 5:
			cout << " �������: "; cin >> value;
			BinarySearchDelete(root, value);
			cout << endl;
			break;
		case 6:
			cout << " S = " << S;
			cout << endl << endl;
			cout << endl << endl;
			break;
		case 0:
			cout << endl;
			break;
		}
	} 	while (menu != 0);

	return 0;
}