
#include "binpacker.hh"

namespace glft {

BinPacker::BinPacker(float width, float height) {
	initialize(width, height);
}

BinPacker::~BinPacker() {
	if (root.left) deleteNode(root.left);
	if (root.right) deleteNode(root.right);
}

void BinPacker::deleteNode(Node* node) {
	if (node->right) deleteNode(node->right);
	if (node->left) deleteNode(node->left);
	delete node;
}

void BinPacker::initialize(float width, float height) {
	root.width = width;
	root.height = height;
	root.x = root.y = 0;
	root.left = root.right = 0;	
}

BinPacker::Node* BinPacker::insert(float width, float height) {
	return insert(&root, width, height);
}

BinPacker::Node* BinPacker::insert(Node* node, float width, float height) {
	if (node->left || node->right) {
		if (node->left) {
			Node *newNode = insert(node->left, width, height);
			if (newNode) return newNode;
		}
		if (node->right) {
			Node *newNode = insert(node->right, width, height);
			if (newNode) return newNode;
		}
		return nullptr;
	}

	// This node is a leaf, but can we fit the new rectangle here?
	if (width > node->width || height > node->height) return 0;

	// The new cell will fit, split the remaining space along the shorter axis,
	// that is probably more optimal.
	int w = node->width - width;
	int h = node->height - height;
	node->left = new Node();
	node->right = new Node();
	if (w <= h) {
		node->left->x = node->x + width;
		node->left->y = node->y;
		node->left->width = w;
		node->left->height = height;

		node->right->x = node->x;
		node->right->y = node->y + height;
		node->right->width = node->width;
		node->right->height = h;
	} else {
		node->left->x = node->x;
		node->left->y = node->y + height;
		node->left->width = width;
		node->left->height = h;

		node->right->x = node->x + width;
		node->right->y = node->y;
		node->right->width = w;
		node->right->height = node->height;
	}

	node->width = width;
	node->height = height;
	return node;
}

}
