#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <stack>
#include <queue>

using namespace std;


struct Node
{
	Node() {}
	Node(const string& data) : _data(data) {}

	vector<Node*> _children;
	string _data;


};

Node* CreateTree()
{
	Node* root = new Node("���ߺ�");
	{
		Node * node1 = new Node("���α׷�����");
		root->_children.push_back(node1);
		{
			Node* _node1 = new Node("�������α׷���");
			node1->_children.push_back(_node1);

			Node* _node2 = new Node("Ŭ���̾�Ʈ���α׷���");
			node1->_children.push_back(_node2);

			Node* _node3 = new Node("�������α׷���");
			node1->_children.push_back(_node3);
		}
		Node* node2 = new Node("��ȹ��");
		root->_children.push_back(node2);
		{
			Node* _node1 = new Node("����������");
			node2->_children.push_back(_node1);

			Node* _node2 = new Node("���丮");
			node2->_children.push_back(_node2);

			Node* _node3 = new Node("�ý��� ��ȹ");
			node2->_children.push_back(_node3);
		}

		Node* node3 = new Node("��Ʈ��");
		root->_children.push_back(node3);
		{
			Node* _node1 = new Node("���");
			node3->_children.push_back(_node1);

			Node* _node2 = new Node("�𵨸�");
			node3->_children.push_back(_node2);

			Node* _node3 = new Node("�Ϸ���Ʈ");
			node3->_children.push_back(_node3);
		}
	}
	return root;
}

void PrintTree(Node* node,int depth)
{
	for (int i = 0; i < depth; i++)
	{
		cout << "- ";
	}
	cout << node->_data << '\n';

	for (auto child : node->_children)
	{
		PrintTree(child,depth+1);
	}
	
}

int main()
{
	Node* root = CreateTree();
	PrintTree(root,0);

	return 0;
}