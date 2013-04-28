#ifndef _GLFT_BINPACKER_HH_
#define _GLFT_BINPACKER_HH_

namespace glft {

class GLFT_EXPORT BinPacker {
public:
	struct Node {
		Node* left;
		Node* right;
		
		float x;
		float y;
		float width;
		float height;
	};
	///initializes the bin with the given size
	BinPacker(float width = 2048, float height = 2048);
	
	///cleans up all nodes
	~BinPacker();
	
	///initializes the bin with the given size
	void initialize(float width, float height);
	
	///Inserts a new rectangle of the given size into the bin.
	///@returns pointer to the new node, or 0 if there's no fit
	Node* insert(float width, float height);
private:
	Node root;
	
	///Inserts a new rectangle of the given size
	///@param node node to insert into
	///@returns new node, or 0 if there's no fit
	Node* insert(Node* node, float width, float height);
	
	///recursively deletes a node and all its childrens
	void deleteNode(Node* node);
};

}

#endif
