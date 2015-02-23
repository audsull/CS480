#include "Tree.h"

Node::Node() {
	parent = NULL;
	numChildren = 0;
}
Node::Node(Token* t, Node* p) {
	parent = p;
	numChildren = 0;
}
Node* Node::addChild(Token* t) {
	Node* newNode = new Node(t, this);
	children.push_back(newNode);
	numChildren++;
	return newNode;
}
Tree::Tree() {
	head = new Node();
	curNode = head;
	size = 0;
}
void Tree::start() {
	curNode = curNode->addChild(NULL);
}
void Tree::end() {
	//curNode = curNode->getParent();
}
void Tree::addTerminal(Token* t) {
	curNode->addChild(t);
	size++;
}
