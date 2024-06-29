/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

//Write your code below this line

ExprTreeNode::ExprTreeNode(){
    type="";
    id="";
    num=0;
    left = NULL;
    right = NULL;
}

ExprTreeNode::ExprTreeNode(string t,int v){
    type = t;
    if(t=="VAL"){
        num = v;
        id="";
        left = NULL;
        right = NULL;
    }
    if(t=="DEL"){
        num = 0;
        id="";
        left = NULL;
        right = NULL;
    }
    if(t=="RET"){
        num = 0;
        id="";
        left = NULL;
        right = NULL;
    }
    if(t=="VAR"){
        num = 0;
        id="";
        left = NULL;
        right = NULL;
    }
    else{
        num = 0;
        id="";
        left = NULL;
        right = NULL;
    }
  
}

ExprTreeNode::~ExprTreeNode(){
    delete left;
    delete right; // TAKE CARE THAT I HAVE DELETED THEM
}

