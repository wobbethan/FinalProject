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
		RedBlackNode* grandparent = nullptr;
		RedBlackNode* uncle = nullptr;
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

    RedBlackNode* RotateLeft(RedBlackNode* node) { //GEEKS FOR GEEKS CHANGE CHANGE CHANGE CHANGE CHANGE 
        RedBlackNode* x = node->right;
        RedBlackNode* y = x->left;
        x->left = node;
        node->right = y;
        node->parent = x; // parent resetting is also important.
        if (y != nullptr)
            y->parent = node;
        return(x);
    }

    RedBlackNode* RotateRight(RedBlackNode* node) //GEEKS FOR GEEKS CHANGE CHANGE CHANGE CHANGE CHANGE 
    {
        RedBlackNode* x = node->left;
        RedBlackNode* y = x->right;
        x->right = node;
        node->left = y;
        node->parent = x;
        if (y != nullptr)
            y->parent = node;
        return(x);
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

    

    void maintainProperties(RedBlackNode* root) { //Geeks for Geek
        if (root->parent == nullptr) {  //identify root node of tree
            root->red = false; //set root to black;
        }
        else if (returnUncle(root) != nullptr && returnUncle(root)->red == true) {
                returnUncle(root)->red = false;
                root->parent->red = false;
                returnGrandParent(root)->red = true;
                cout << "Changing colors\n";
        }
        else if (returnUncle(root) != nullptr && returnUncle(root)->red == false) {
            cout << "Checking rotation\n";
                
                if (returnGrandParent(root)->right == root->parent && root->parent->left == root) {		//Black triangle Right left case
                    cout << " Right left roation\n";
                    RotateRight(returnGrandParent(root));
                    RotateLeft(returnGrandParent(root));
                    returnGrandParent(root)->red = !returnGrandParent(root)->red;
                    root->red = !root->red;
        		}
        		else if (returnGrandParent(root)->left == root->parent && root->parent->right == root) {		//Black triangle left right case
                    cout << " left right roation\n";
                    RotateLeft(returnGrandParent(root));
                    RotateRight(returnGrandParent(root));
                    returnGrandParent(root)->red = !returnGrandParent(root)->red;
                    root->red = !root->red;
        		}
        		else if (returnGrandParent(root)->left == root->parent && root->parent->left == root) {		//Black line left left case
                    cout << "left left roation\n";
                    RotateRight(returnGrandParent(root));
                    returnGrandParent(root)->red = !returnGrandParent(root)->red;
                    root->parent->red = !root->parent->red;


                }
        		else if (returnGrandParent(root)->right == root->parent && root->parent->right == root) {		//Black line right right case
                    cout << " Right right roation\n";
                    RotateLeft(returnGrandParent(root));
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


