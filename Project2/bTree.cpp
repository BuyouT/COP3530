#include "bTree.h"

bTree::bTree(int size) {
	// set the root null and input the size
	root = NULL;
	deg = size;
}

bTree::~bTree() {
	delete root;
}

void bTree::insert(string key, string value) {
	
	// If the root is empty set the key to the root
	if (root == NULL) {
		root = new Node(deg, true);
		root->values[0].id = key;
		root->values[0].value = value;
		root->amtkey = 1;
	}

	else {
		// If the node is full split it and then insert
		if (root->amtkey == 2*deg-1) {
			Node *temp = new Node(deg, false);
			temp->child[0] = root;
			temp->split(0, root);
			int i = 0;
			if (temp->values[0].id < key) {
				++i;
			}

			temp->child[i]->insert(key, value);
			root = temp;
		}

		// insert normally
		else {
			root->insert(key, value);
		}
	}
}

bool bTree::find(string key, string *value) {
	
	// Nothing in the tree
	if (root == NULL) {
		return false;
	}

	// Use the find function
	else {
		return root->find(key, value);
	}
}

bool bTree::delete_key(string key) {
	// Unnecessary deletion if it's empty
	if (root == NULL) {
		cout << "There are no keys inside the tree" << endl;
		return false;
	}

	// delete
	root->remove(key);

	// If the root is deleted set root to null
	if (root->amtkey == 0) {
		Node *temp = root;
		if (root->kid) {
			root = NULL;
		}
		else {
			root = root->child[0];
		}

		delete temp;
	}
	return true;
}

// contents of the tree
string bTree::toStr() {
	if (root != NULL) {
		return root->toStr();		
	}

	else {
		cout << "Tree is currently empty" << endl;
		return "";
	}
}
///////////////////////////////////////////////////////////
/////////////////////////NODE STUFF////////////////////////
///////////////////////////////////////////////////////////

bool Node::find(string key, string *value) {
	int i = 0;
	// goes through the tree until key is found
	while (i < amtkey && key > values[i].id) {
		++i;
	}

	if (values[i].id == key) {
		*value = values[i].value;
		return true;
	}

	if (kid) {
		return false;
	}

	child[i]->find(key, value);
}

void Node::insert(string key, string value) {
	int i = amtkey-1;

	// when the node is not full
	if (kid) {
		while (i >= 0 && values[i].id > key) {
			values[i+1] = values[i];
			--i;
		}

		values[i+1].id = key;
		values[i+1].value = value;
		++amtkey;
	}

	// when it's full split the node and insert
	else {
		while (i >= 0 && values[i].id > key) {
			--i;
		}

		if (child[i+1]->amtkey == 2*deg-1) {
			split(i+1, child[i+1]);

			if (values[i+1].id < key) {
				++i;
			}
		}

		child[i+1]->insert(key, value);
	}
}

// splitting function that grabs the mid key and makes it a parent
void Node::split(int index, Node *baby) {
	Node *temp = new Node(baby->deg, baby->kid);
	temp->amtkey = deg-1;

	for (int i = 0; i < deg-1; ++i) {
		temp->values[i] = baby->values[i+deg];
	}

	if (!(baby->kid)) {
		for (int i = 0; i < deg; ++i) {
			temp->child[i] = baby->child[i+deg];
		}
	}

	baby->amtkey = deg-1;

	for (int i = amtkey; i >= index+1; --i) {
		child[i+1] = child[i];
	}

	child[index+1] = temp;

	for (int i = amtkey; i >= index; --i) {
		values[i+1] = values[i];
	}

	values[index] = baby->values[deg-1];

	++amtkey;
}

// Looks for the index of the needed key
int Node::findKey(string key) {
	int index = 0;

	while (index < amtkey && values[index].id < key) {
		++index;
	}

	return index;
}

bool Node::remove(string key) {
	int index = findKey(key);
	bool flag = false;

	// when the key is found remove said key
	if (index < amtkey && values[index].id == key) {
		if (kid) {
			removeKid(index);
		}

		else {
			removeNoKid(index);
		}
	}

	// If it's not found or the node only contans a single key
	else {
		if (kid) {
			cout << "Key does not exist inside the tree" << endl;
			return false;
		}

		if (index == amtkey) {
			flag = true;
		}

		if (child[index]->amtkey < deg) {
			populate(index);
		}

		if (flag && index > amtkey) {
			child[index-1]->remove(key);
		}
		else {
			child[index]->remove(key);
		}
	}

	return true;
}

void Node::removeKid(int index) {
	// Normal remove
	for (int i = index+1; i < amtkey; ++i) {
		values[i-1] = values[i];
	}

	--amtkey;
}

void Node::removeNoKid(int index) {
	// Takes care if the key has children
	string k = values[index].id;

	if (child[index]->amtkey >= deg) {
		string prev = getBack(index);
		string prevV = getBackV(index);
		values[index].id = prev;
		values[index].value = prevV;
		child[index]->remove(prev);
	}

	else if (child[index+1]->amtkey >= deg) {
		string next = getNext(index);
		string nextV = getNextV(index);
		values[index].id = next;
		values[index].value = nextV;
		child[index+1]->remove(next);
	}

	else {
		unite(index);
		child[index]->remove(k);
	}
}

// For keys
string Node::getBack(int index) {
	// children on the left side
	Node *temp = child[index];

	while (!temp->kid) {
		temp = temp->child[temp->amtkey];
	}

	return temp->values[temp->amtkey-1].id;
}

// For Values
string Node::getBackV(int index) {
	// children on the left side 
	Node *temp = child[index];

	while (!temp->kid) {
		temp = temp->child[temp->amtkey];
	}

	return temp->values[temp->amtkey-1].value;
}

// For keys
string Node::getNext(int index) {
	// For children on the right
	Node *temp = child[index+1];

	while (!temp->kid) {
		temp = temp->child[0];
	}

	return temp->values[0].id;
}

// For values
string Node::getNextV(int index) {
	// For children on the right
	Node *temp = child[index+1];

	while (!temp->kid) {
		temp = temp->child[0];
	}

	return temp->values[0].value;
}

void Node::populate(int index) {

	// Use key of a previous child
	if (index != 0 && child[index+1]->amtkey >= deg) {
		borrowBack(index);
	}

	// Use key of a next child
	else if (index != amtkey && child[index+1]->amtkey >= deg) {
		borrowNext(index);
	}

	// Unite sibling together
	else {
		if (index != amtkey) {
			unite(index);
		}
		else {
			unite(index-1);
		}
	}
}

// Hold a previous child
void Node::borrowBack(int index) {
	
	Node *c = child[index];
	Node *bro = child[index-1];

	for (int i = c->amtkey-1; i >= 0; --i) {
		c->values[index+1] = c->values[index];
	}

	if (!(c->kid)) {
		for (int i = c->amtkey; i >= 0; --i) {
			c->child[i+1] = c->child[i];
		}
	}

	c->values[0] = values[index-1];

	if (!kid) {
		c->child[0] = bro->child[bro->amtkey];
	}

	values[index-1] = bro->values[bro->amtkey-1];

	++c->amtkey;
	--bro->amtkey;
}

// Holds a next child
void Node::borrowNext(int index) {
	
	Node *c = child[index];
	Node *bro = child[index-1];

	c->values[c->amtkey] = values[index];

	if (!(c->kid)) {
		c->child[(c->amtkey)+1] = bro->child[0];
	}

	values[index] = bro->values[0];

	for (int i = 1; i < bro->amtkey; ++i) {
		bro->values[i-1] = bro->values[i];
	}

	if (!(bro->kid)) {
		for (int i = 1; i <= bro->amtkey; ++i) {
			bro->child[i-1] = bro->child[i];
		}
	}

	++c->amtkey;
	--bro->amtkey;
}

// It unites the current child with the next child
void Node::unite(int index) {
	Node *c = child[index];
	Node *bro = child[index+1];

	c->values[deg-1] = values[index];

	for (int i = 0; i < bro->amtkey; ++i) {
		c->values[i+deg] = bro->values[i];
	}

	if (!(c->kid)) {
		for (int i = 0; i < bro->amtkey; ++i) {
			c->child[i+deg] = bro->child[i];
		}
	}

	for (int i = index+1; i < amtkey; ++i) {
		values[i-1] = values[i];
	}

	for (int i = index+2; i < amtkey; ++i) {
		child[i-1] = child[i];
	}

	c->amtkey += bro->amtkey+1;
	--amtkey;

	delete bro;
}

string Node::toStr() {
	// Call the traverse function and returns it's contents
	string s = "";
	traverse(&s);
	return s;
}

void Node::traverse(string *s) {
	// Goes through the tree and save the string in the respective address
    int i;
    for (i = 0; i < amtkey; i++)
    {
        if (!kid)
            child[i]->traverse(s);
        *s += values[i].id + "\n";
    }

    if (!kid)
        child[i]->traverse(s);
}