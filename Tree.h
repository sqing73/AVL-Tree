#ifndef TREE_H
#define TREE_H

#include<algorithm>
#include<vector>
#include <utility>
using namespace std;

class AvlNode{
public:
    int key;
    AvlNode* left;
    AvlNode* right;
    int height;
    AvlNode(int n);
};
class Tree{
public:
    Tree();
    ~Tree();
    int heightDifference(AvlNode* parent);
    void destroyRecursive(AvlNode* node);
    int nodeLevel(AvlNode* node);
    void reset();
    void insertHelper(int n, AvlNode*&  t);
    void lookUp(int n);
    bool lookUpHelper(int n);
    int getNodeHeight(AvlNode* t);
    void balance(AvlNode*& t);
    void singleRotationWithLeft(AvlNode*& t);
    void singleRotationWithRight(AvlNode*& t);
    void doubleRotationWithLeft(AvlNode*& t);
    void doubleRotationWithRight(AvlNode*& t);
    void printTreeHelper(AvlNode* node);
    void printTree();
    //void printRotation(vector<pair<int,int>>& ll, vector<pair<int,int>>& lr,vector<pair<int,int>>& rr, vector<pair<int,int>>& rl);
    //void printRotationHelper(AvlNode* node, vector<pair<int, int> >& ll,  vector<pair<int, int> >& lr, vector<pair<int, int> >& rl, vector<pair<int, int> >& rr, int f1, int f2, int max, int min);
    void insert(int n);
    int getVisited();
    int getRotation();
    double getAmortizedVisited(int n);
    double getAmortizedRotation(int n);
    void getThree();
    void getLookUpThree();
    int getAdded();
    int getInputNum();
    void findRotationHelper(AvlNode* root, vector<pair<int, int> >& ll,  vector<pair<int, int> >& lr, vector<pair<int, int> >& rl, vector<pair<int, int> >& rr, int f1, int f2, int max, int min);
    void findRotation(vector<pair<int, int> >& ll,  vector<pair<int, int> >& lr, vector<pair<int, int> >& rl, vector<pair<int, int> >& rr);
    //void printTree(AvlNode* node);
    //std::string inserts(std::string[]);
    //std::string lookups(std::string[]);
    //std::string prints(std::string[]);


private:
    AvlNode* root;
    int visited;
    int rotation;
    bool counted;
    int added;
    int inputNum;
    vector<int> foundedNum;


};


#endif
