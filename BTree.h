#pragma once
#include "game.h"
using namespace std;


struct BTreeNode {

    //////// ATTRIBUTES ////////
    game* keys; // array of keys
    BTreeNode** children; // array of child pointers (max: l+1)
    int l;      // max number of keys, max children per node: l+1
    int n;      // number of children
    bool leaf;  // true when node is leaf 

    //////// CONSTRUCTOR //////// 
    BTreeNode(int l, bool leaf);
    BTreeNode(int l, bool leaf, game* keys, BTreeNode** children, int n);

    //////// FUNCTIONS ////////
    void insert(game aGame, int gameID);
    void split(int i, BTreeNode* aNode);
    BTreeNode* search(int gameID);

};

class BTree {
    //////// ATTRIBUTES /////////
    BTreeNode* root;
    int l;

public:

    //////// CONSTRUCTOR //////// 
    BTree(int l);

    //////// FUNCTIONS ////////
    void insert(game aGame, int gameID);
    game searchID(int gameID);

};

BTree::BTree(int l) { // Tree Constructor
    root = nullptr;
    this->l = l;
}

BTreeNode::BTreeNode(int l, bool leaf) { //Node Constructor
    this->leaf = leaf;
    this->l = l;
    keys = new game[l];
    children = new BTreeNode * [l + 1];
    n = 0;
}

BTreeNode::BTreeNode(int l, bool leaf, game* keys, BTreeNode** children, int n) { // Node Constructor
    this->leaf = leaf;
    this->l = l;
    this->keys = keys;
    this->children = children;
    this->n = n;
}

void BTreeNode::split(int i, BTreeNode* firstChild) { //Created with Geeks for Geeks and Programiz Psuedocode
    int newN = l % 2 == 0 ? l / 2 - 1 : l / 2;
    game* newKeysArray = new game[l];
    BTreeNode** newChildrenArray = new BTreeNode * [l + 1];

    for (int j = 0; j < newN; j++)
        newKeysArray[j] = firstChild->keys[j + l / 2 + 1];

    if (firstChild->leaf == false) {
        for (int j = 0; j < newN + 1; j++) {
            newChildrenArray[j] = firstChild->children[j + l / 2 + 1];
        }
    }

    BTreeNode* secondChild = new BTreeNode(firstChild->l, firstChild->leaf, newKeysArray, newChildrenArray, newN);

    firstChild->n = l / 2;

    for (int j = n; j >= i + 1; j--)
        children[j + 1] = children[j];
    children[i + 1] = secondChild;

    for (int j = n - 1; j >= i; j--)
        keys[j + 1] = keys[j];
    keys[i] = firstChild->keys[l / 2];

    n++;
}

void BTreeNode::insert(game aGame, int gameID) { //Created with Geeks for Geeks and Programiz Psuedocode
    int index = n - 1;

    if (leaf) {
        while (index >= 0 && keys[index].getGameID() > gameID) {
            keys[index + 1] = keys[index];
            index--;
        }

        keys[index + 1] = aGame;
        n++;
    }
    else {
        while (index >= 0 && keys[index].getGameID() > gameID)
            index--;

        if (children[index + 1]->n == l) {
            split(index + 1, children[index + 1]);

            if (keys[index + 1].getGameID() < gameID)
                index++;
        }
        children[index + 1]->insert(aGame, gameID);
    }
}

void BTree::insert(game aGame, int gameID) { //Created with Geeks for Geeks and Programiz Psuedocode
    if (root == nullptr) {   // tree emtpy, create root
        root = new BTreeNode(l, true);
        root->keys[root->n++] = aGame;
    }
    else {   // the tree is not empty
        if (root->n == l) {  // root has no space
            BTreeNode* newNode = new BTreeNode(l, false);

            newNode->children[0] = root;

            newNode->split(0, root);

            int i = 0;
            if (newNode->keys[0].getGameID() < gameID)
                i++;
            newNode->children[i]->insert(aGame, gameID);

            root = newNode;
        }
        else
            root->insert(aGame, gameID);
    }
}




game BTree::searchID(int gameID) {
    BTreeNode* node = root->search(gameID);
    for (int i = 0; i < node->n; i++) {
        if (gameID == node->keys[i].getGameID())
            return node->keys[i];
    }
    return game();
}

BTreeNode* BTreeNode::search(int gameID) {
    int i = 0;
    while (gameID > keys[i].getGameID() && i < n)
        i++;

    if (gameID == keys[i].getGameID())
        return this;
    else if (leaf)
        return nullptr;
    else
        return children[i]->search(gameID);
}