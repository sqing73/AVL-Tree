#include "Tree.h"
#include <iostream>



AvlNode::AvlNode(int n){
    key = n;
    left = NULL;
    right = NULL;
    height = 0;
}

int Tree::heightDifference(AvlNode *parent) {
    if(parent == NULL)
        return 0;
    return getNodeHeight(parent->left)-getNodeHeight(parent->right);
}
int Tree::nodeLevel(AvlNode *node) {
    AvlNode* temp = root;
    int level = 0;
    while(temp -> key != node -> key){
        if(node->key < temp -> key){
            temp = temp-> left;
            level++;
        }
        else if(node->key > temp->key) {
            temp = temp->right;
            level++;
        }
    }
    return level;
}

Tree::Tree(){
    root = NULL;
    visited = 0;
    rotation = 0;
    counted = false;
    added = 0;

}

void Tree::reset(){
    visited = 0;
    rotation = 0;
    counted = 0;
    added = 0;
    inputNum = 0;
    foundedNum.clear();
}

Tree::~Tree(){

    destroyRecursive(root);

}

void Tree::destroyRecursive(AvlNode *node) {
    if(!node){
        destroyRecursive(node->left);
        destroyRecursive(node->right);
        delete node;
    }
}

int Tree::getNodeHeight(AvlNode* t){
    return t == NULL? -1 : t -> height;
}

void Tree::singleRotationWithLeft(AvlNode*& t){
    AvlNode* lc = t -> left;
    t -> left = lc -> right;
    lc -> right = t;
    t -> height = std::max(getNodeHeight(t -> left), getNodeHeight(t -> right))+1;
    lc -> height = std::max(getNodeHeight(lc -> left), t->height);
    t = lc;
    rotation++;

}

void Tree::singleRotationWithRight(AvlNode*& t){
    AvlNode* rc = t -> right;
    t -> right = rc -> left;
    rc -> left = t;
    t -> height = std::max(getNodeHeight(t -> left), getNodeHeight(t -> right)) + 1;
    rc -> height = std::max(getNodeHeight(t -> left), getNodeHeight(t -> right)) + 1;
    t = rc;
    rotation++;
}

void Tree::doubleRotationWithLeft(AvlNode*& t){
    singleRotationWithRight(t -> left);
    singleRotationWithLeft(t);


}

void Tree::doubleRotationWithRight(AvlNode*& t){
    singleRotationWithLeft(t -> right);
    singleRotationWithRight(t);
}

void Tree::lookUp(int n){
    inputNum++;
    if(this->lookUpHelper(n)==true){
        foundedNum.push_back(n);
    }
}
bool Tree::lookUpHelper(int n){
    AvlNode* temp = root;
    if(root == NULL)
        return false;
    while(temp -> key != n && temp != NULL){

        if(temp -> key < n){
            visited++;
            if(temp -> right == NULL){
                counted = true;
                return false;}
            temp = temp -> right;
        }
        else if(temp -> key > n){
            visited++;
            if(temp -> left == NULL){
                counted = true;
                return false;}
            temp = temp -> left;
        }
    }
    if(temp -> key == n){
        visited++;
        return true;
    }
    counted = true;
    return false;
}

void Tree::insert(int n){
    inputNum++;
    this->insertHelper(n, root);
    counted = false;
}

void Tree::insertHelper(int n, AvlNode*&  t){
    if(root == NULL){
        root = new AvlNode(n);
        added++;
        balance(t);
        return;
    }
    else if(counted == false){
        if(this -> lookUpHelper(n) == true)
            return;
    }
    if(t == nullptr) {
        added++;
        t = new AvlNode(n);
    }
    else if(n<t->key)
        insertHelper(n, t->left);
    else if(n>t->key)
        insertHelper(n,t->right);

    balance(t);
}

void Tree::balance(AvlNode* & t){
    if(t == NULL)
        return ;
    if(getNodeHeight(t -> left) - getNodeHeight(t -> right) > 1){
        if(getNodeHeight(t -> left -> left) >= getNodeHeight(t -> left -> right))
            singleRotationWithLeft(t);
        else
            doubleRotationWithLeft(t);
    }
    else if(getNodeHeight(t -> right) - getNodeHeight(t -> left) > 1){
        if(getNodeHeight(t -> right -> right) >= getNodeHeight(t -> right -> left))
            singleRotationWithRight(t);
        else
            doubleRotationWithRight(t);
    }

    t -> height = std::max(getNodeHeight(t -> left), getNodeHeight(t -> right)) + 1;
}

int Tree::getVisited(){
    return visited;
}

int Tree::getRotation() {
    return rotation;
}

void Tree::getThree(){
    cout << "Added " << to_string(this->getAdded()) << " of " << inputNum << " nodes." << "\n" <<
         "Visited " << to_string(this->getVisited()) << " (" << this->getAmortizedVisited(inputNum) << ") nodes and performed " << this->getRotation()
         << " (" << this->getAmortizedRotation(inputNum) << ") rotations." << "\n";
}

void Tree::getLookUpThree(){
    string temp = "";
    for(size_t i = 0; i < foundedNum.size(); i++){
        if(i != foundedNum.size()-1)
            temp = temp + to_string(foundedNum[i]) + ", ";
        else
            temp += to_string(foundedNum[i]);
    }
    cout<< "Found " << foundedNum.size() << " of " << inputNum << " nodes: [" << temp << "]\n"
        << "Visited " << this->getVisited() << " (" << this->getAmortizedVisited(inputNum) << ") nodes and performed " << this->getRotation()
        << " (" << this->getAmortizedRotation(inputNum) << ") rotations." << "\n";
}

void Tree::printTreeHelper(AvlNode* node) {
    if (node == NULL)
        return;
    string space = "";
    for(int i = 0; i<this->nodeLevel(node); i++){
        space += "  ";
    }
    if (node->left == NULL && node->right == NULL)
        cout << space << "Leaf(" << node->key << ")" << endl;
    else if(node->left != NULL && node->right == NULL) {
        cout << space << "Node(" << node->key << ", h=" << node->height << "):" << endl;
        printTreeHelper(node->left);
        space += "  ";
        cout << space << "Null" << endl;
    }
    else if(node -> left == NULL && node->right != NULL){
        cout << space << "Node(" << node->key << ", h=" << node->height << "):" << endl;
        space += "  ";
        cout << space << "Null" << endl;
        printTreeHelper(node->right);
    }
    else {
        cout << space << "Node(" << node->key << ", h=" << node->height << "):" << endl;
        printTreeHelper(node->left);
        printTreeHelper(node->right);
    }
}
void Tree::findRotationHelper(AvlNode* node, vector<pair<int, int> >& ll,  vector<pair<int, int> >& lr, vector<pair<int, int> >& rl, vector<pair<int, int> >& rr, int f1, int f2, int max, int min) {

    if(!node){
        return;
    }
    if(node -> left != NULL || node -> right != NULL){ // non-leaf nodes
        int diff = heightDifference(node);
        if(diff == 1){//left tree is taller        left : 1    right : -1
            findRotationHelper(node -> left, ll, lr, rl, rr, 1, 0, node -> key -1, min);
            findRotationHelper(node -> right, ll, lr, rl, rr, 0 , 0, max, node -> key + 1);
        }else if(diff == -1){//right tree is taller
            findRotationHelper(node -> left, ll, lr, rl, rr, 0 , 0, node -> key -1, min);
            findRotationHelper(node -> right, ll, lr, rl, rr, -1, 0, max, node -> key + 1);
        }else if(diff == 0){
            if(f2 == 0){
                findRotationHelper(node -> left, ll, lr, rl, rr, f1, 1, node -> key - 1, min);
                findRotationHelper(node -> right, ll, lr, rl, rr, f1, -1, max, node -> key + 1);
            }

            else{
                findRotationHelper(node -> left, ll, lr, rl, rr, f1, f2, node -> key - 1, min);
                findRotationHelper(node -> right, ll, lr, rl, rr, f1, f2, max, node -> key + 1);
            }
        }
    }else{// reach the leaf node
        if(f1 == 1 && f2 == 1){
            //left-left rotation
            if((max) >= (min)){
                pair<int, int> range (min , max);
                ll.push_back(range);
            }
        }else if(f1 == 1 && f2 == -1){
            // left-right rotation
            if((max -1) >= (min + 1)){
                pair<int, int> range (min, max);
                lr.push_back(range);
            }
        }else if(f1 == -1 && f2 == 1){
            // right-left rotation
            if((max) >= (min)){
                pair<int, int> range (min, max);
                rl.push_back(range);
            }
        }else if(f1 == -1 && f2 == -1){
            // right-right rotation
            if((max ) >= (min)){
                pair<int, int> range (min, max);
                rr.push_back(range);
            }
        }else if(f1 != 0 && f2 == 0){
            // both rotations
            if(f1 == 1){
                if((min) <= (node -> key -1)){
                    pair<int, int> range (min, node -> key -1);
                    ll.push_back(range);
                }
                if((node -> key + 1) <= (max)){
                    pair<int, int> range (node -> key + 1, max);
                    lr.push_back(range);
                }
            }else if(f1 == -1){
                if((min) <= (node -> key -1)){
                    pair<int, int> range (min, node -> key - 1);
                    rl.push_back(range);
                }
                if((node -> key + 1) <= (max)){
                    pair<int, int> range (node -> key + 1, max);
                    rr.push_back(range);
                }
            }
        }
        else if(f1 == 0){
            // no rotation
            return;
        }
    }
}
void Tree::findRotation(vector<pair<int, int> >& ll,  vector<pair<int, int> >& lr, vector<pair<int, int> >& rl, vector<pair<int, int> >& rr){
    findRotationHelper(root, ll, lr, rl, rr, 0, 0, 2147483647, -2147483648);
}
/*void Tree::printRotation(vector<pair<int,int>>& ll, vector<pair<int,int>>& lr,vector<pair<int,int>>& rr, vector<pair<int,int>>& rl) {
    printRotationHelper(root, ll, lr, rl, rr, 0, 0, 2147483647,-2147483648);
}*/

/*void Tree::printRotationHelper(AvlNode* node, vector<pair<int, int> >& ll,  vector<pair<int, int> >& lr, vector<pair<int, int> >& rl, vector<pair<int, int> >& rr, int f1, int f2, int max, int min){
    if(node == NULL)
        return;
    if(node -> left != NULL || node -> right != NULL) {
        int diff = this->getNodeHeight(node->left) - this->getNodeHeight(node->right);
        if (diff == 1) {//left subtree is heavier set f1:1 f2:0
            printRotationHelper(node->left, ll, lr, rl, rr, 1, 0, node->key - 1, min);
            //unset f1,f2
            printRotationHelper(node->right, ll, lr, rl, rr, 0, 0, max, node->key + 1);
        } else if (diff == -1) {//right subtree is heavy
            printRotationHelper(node->left, ll, lr, rl, rr, 0, 0, node->key - 1, min);
            printRotationHelper(node->right, ll, lr, rl, rr, -1, 0, max, node->key + 1);
        } else if (diff == 0) {
            if (f2 == 0) {
                printRotationHelper(node->left, ll, lr, rl, rr, f1, 1, node->key - 1, min);
                printRotationHelper(node->right, ll, lr, rl, rr, f1, -1, max, node->key + 1);
            }
        }
    }
        else{//leaf
            if(f1 == 1 && f2 == 1){
                //ll
                if(max >= min){
                    pair<int, int> range(min, max);
                    ll.push_back(range);
                }
            }//lr
            else if(f1 == 1 && f2 == -1){
                if((max-1) >= (min+1)){
                    pair<int, int> range(min, max);
                    lr.push_back(range);
                }
            }//rl
            else if(f1 == -1 && f2 == 1){
                if(max >= min){
                    pair<int, int> range(min, max);
                    rl.push_back(range);
                }
            }//rr
            else if(f1 == -1 && f2 == -1){
                if(max >= min){
                    pair<int, int> range(min, max);
                    rr.push_back(range);
                }
            }//ll & lr
            else if(f1 != 0 && f2 == 0){
                if(f1 == 1){
                    if(min <= (node ->key -1)){
                        pair<int, int> range(min, node->key-1);
                        ll.push_back(range);
                    }
                    if((node->key+1) <= max){
                        pair<int, int> range(node->key+1, max);
                        lr.push_back(range);
                    }
                }
                else if(f1 == -1){
                    if(min <= (node -> key-1)){
                        pair<int, int> range(min, node->key-1);
                        rl.push_back(range);
                    }
                    if((node->key+1) <= max){
                        pair<int, int> range(node->key+1, max);
                        rr.push_back(range);
                    }
                }
            }//not rotation
            else if(f1 == 0){
                return;
            }
        }
}*/

void Tree::printTree() {
    this->printTreeHelper(root);
}
int Tree::getAdded(){
    return added;
}

int Tree::getInputNum(){
    return inputNum;
}

double Tree::getAmortizedVisited(int n) {
    double amortizedVisited = double(visited) / n;
    return amortizedVisited;
}

double Tree::getAmortizedRotation(int n){
    double amortizedRotation = double(rotation) / n;
    return amortizedRotation;
}






