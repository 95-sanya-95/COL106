/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"


SymNode::SymNode(){
    key = "";
    height = -1; 
    par = NULL;
    left = NULL;
    right = NULL;
}

SymNode::SymNode(string k){
    key = k;
    height = 0;
    par = NULL;
    left = NULL;
    right = NULL;
}

SymNode* SymNode::LeftLeftRotation(){
    SymNode* r = right;
    right = r->left;  
    if (right != NULL) {
        right->par = this;
    }
    r->left = this;
    r->par = par;

    if (par != NULL) {
        if (par->left == this) {
            par->left = r;
        } else {
            par->right = r;
        }
    }
    par = r; 


    return r;
}


SymNode* SymNode::RightRightRotation(){
    SymNode* l = left;
    left = l->right;  
    if (left != NULL) {
        left->par = this;
    }
    l->right = this;
    l->par = par; 

    if (par != NULL) {
        if (par->left == this) {
            par->left = l;
        } else {
            par->right = l;
        }
    }
    par = l; 

    
    return l;
}

SymNode* SymNode::LeftRightRotation(){
    right = right->RightRightRotation(); 
    return LeftLeftRotation(); 
}

SymNode* SymNode::RightLeftRotation(){
    left = left->LeftLeftRotation(); 
    return RightRightRotation(); 
}

SymNode::~SymNode(){
    if (left != NULL) {
    left->par = NULL;
    delete left;
}
if (right != NULL) {
    right->par = NULL;
    delete right;
}

}
