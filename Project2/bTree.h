#ifndef BTREE_H
#define BTREE_H
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Node {
private:
  // holds key and values
  struct key {
    string id;
    string value;
  };

  key *values;
  Node **child;
  int deg;
  int amtkey;
  bool kid;
public:
  Node(int d, bool l) {
    deg = d;
    kid = l;

    values = new key[2*deg-1];
    child = new Node *[2*deg];

    amtkey = 0;
  }
  bool find(string key, string *value);
  void insert(string key, string value);
  void split(int index, Node *baby);
  int findKey(string key);
  bool remove(string key);
  void removeKid(int index);
  void removeNoKid(int index);
  string getBack(int index);
  string getNext(int index);
  string getBackV(int index);
  string getNextV(int index);
  void populate(int index);
  void borrowBack(int index);
  void borrowNext(int index);
  void unite(int index);
  string toStr();
  void traverse(string *s);
  friend class bTree;
};

class bTree {
private:
  Node *root;
  int deg;
public:
  //Constructor
  bTree(int size);

  //Destructor
  ~bTree();

  //Inserts the value pair into the tree
  void insert(string key, string value);

  // Searches for the key in the tree, if found, it returns
  // true else returns false.
  // If the key is found, it stores the value in the *value variable
  bool find(string key, string *value);

  //Searches for the key and deletes it. Returns true if deletion was
  //successful, returns false if the key wasn't found
  bool delete_key(string key);

  // concatenates the contents of the tree from an inorder traversal
  // into an output stream with each string item followed by a 
  // newline character in the stream
  string toStr();
};


#endif