#include "Token.h"
#include <vector>

#pragma once
class Node
{
private:
	Node* parent;
	std::vector<Node*> children;
	int numChildren;
public:
	Node();
	Node(Token*, Node*);
	Node* addChild(Token*);
	Node* getChild(int n);
	//Node* getParent();
};

class Tree
{
private:
	Node* head;
	Node* curNode;
	int size;
public:
	Tree();
	void start();
	void addTerminal(Token*);
	void end();
	~Tree();
};

