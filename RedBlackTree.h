#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

class RedBlackNode {
	
	public:
		game gameObj;
		int ID = 0;
		bool red = true;
        int height = 0;
		RedBlackNode* left = nullptr;
		RedBlackNode* right = nullptr;
		RedBlackNode* parent = nullptr;

		RedBlackNode() {};
		RedBlackNode(game obj, int id, RedBlackNode* _parent){
			this->gameObj = obj;
			this->ID = id;
            this->parent = _parent;
            
		}
	};

class redBlack {
private:
    RedBlackNode* root = nullptr;

public:

    RedBlackNode* RotateLeft(RedBlackNode* n) {  //I think rotations are wrong
        RedBlackNode* grandchild = n->right->left;

        RedBlackNode* newParent = n->right;
        newParent->left = n;
        n->right = grandchild;
        return newParent;
        // code taken from lecture slides
    }

    RedBlackNode* RotateRight(RedBlackNode* n)
    {
        RedBlackNode* grandchild = n->left->right;
        RedBlackNode* newParent = n->left;
        newParent->right = n;
        n->left = grandchild;
        return newParent;
        // code taken from lecture slides
    }

    RedBlackNode* returnGrandParent(RedBlackNode* root) {
        if (root->parent->parent == nullptr) { // returns a nullptr if the grandparent is also null
            return nullptr; // also for if the root node is the child of the first root node
            cout << "returning null";
        }
        else {
            return root->parent->parent;
        }
    }

    RedBlackNode* returnUncle(RedBlackNode* root) {
        // might need to workshop this as assigning the root's parent to parent might not actually make it that item
        if (returnGrandParent(root) != nullptr) {
            if (returnGrandParent(root)->left != nullptr && returnGrandParent(root)->left->ID == root->parent->ID) {
                return returnGrandParent(root)->right;
            }
            else if (returnGrandParent(root)->right != nullptr && returnGrandParent(root)->right->ID == root->parent->ID) {
                return returnGrandParent(root)->left;
            }
        }
        return nullptr;

    }

    

    void maintainProperties(RedBlackNode* root) { //created mostly with Geeks for Geek psuedocode
        if (root->parent == nullptr) {  //identify root node of tree
            root->red = false; //set root to black;
        }
        else if (returnUncle(root) != nullptr && returnUncle(root)->red == true) {
                returnUncle(root)->red = false;
                root->parent->red = false;
                returnGrandParent(root)->red = true;
                cout << "Changing colors\n";
        }
        else if (root->red == true && root->parent->red == true) {
            cout << "Checking rotation\n";
                
                if (returnGrandParent(root)->right == root->parent && root->parent->left == root) {		//pretty sure the order of everything is right but idk what node the rotation should be called on
                    cout << " Right left roation\n";
                    RotateRight(root->parent);
                    RotateLeft(root);
                    returnGrandParent(root)->red = !returnGrandParent(root)->red;
                    root->red = !root->red;
        		}
        		else if (returnGrandParent(root)->left == root->parent && root->parent->right == root) {
                    cout << " left right roation\n";
                    RotateLeft(root->parent);
                    RotateRight(root);
                    returnGrandParent(root)->red = !returnGrandParent(root)->red;
                    root->red = !root->red;
        		}
        		else if (returnGrandParent(root)->left == root->parent && root->parent->left == root) {
                    cout << "left left roation\n";
                   RotateRight(root);
                   returnGrandParent(root)->red = !returnGrandParent(root)->red;
                   root->parent->red = !root->parent->red;


                }
        		else if (returnGrandParent(root)->right == root->parent && root->parent->right == root) {
                    cout << " Right right roation\n";
                    RotateLeft(root);
                    returnGrandParent(root)->red = !returnGrandParent(root)->red;
                    root->parent->red = !root->parent->red;
                }
        }
        
    }


    void InsertHelp(game gameObj, int ID) {
        this->root = Insert(this->root, nullptr, gameObj, ID);
    }

    RedBlackNode* Insert(RedBlackNode* root, RedBlackNode* parent, game gameObj, int ID) {
        if (root == nullptr)
        {
            cout << "Inserting: "<<ID<<endl;
            root = new RedBlackNode(gameObj, ID,parent);
            if (parent != nullptr && parent->ID > root->ID) {
                parent->left = root;
            }
            else if(parent != nullptr) {
                parent->right = root;

            }
            maintainProperties(root);
        }
        else if (ID > root->ID) {
            root->right = Insert(root->right, root, gameObj, ID);

        }
        else if (ID < root->ID) {

            root->left = Insert(root->left,root,gameObj, ID);
        }
        else {
            cout << "unsuccessful" << endl;
            return nullptr;
        }
        return root;
    }

    RedBlackNode* searchGameID(RedBlackNode* root, int ID) { // basic bst search to search for desired parameter

        if (root == nullptr) {
            return nullptr;
        }

        else if (root->ID == ID) {
            return root;
        }

        else if (root->ID > ID) {
            searchGameID(root->left, ID);
        }

        else {
            searchGameID(root->right, ID);
        }

        //cout << "ID could not be found" << endl; // prints this if no conditions are met, so ID isn't in the tree
        return nullptr;

    }

    RedBlackNode* searchHelper(int ID) {
        return searchGameID(this->root, ID);
    }



};


