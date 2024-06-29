/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"
#include <iostream>
// Write your code below this line

Parser::Parser()
{
    symtable = new SymbolTable();
}

void Parser::parse(vector<string> expression)
{

    vector<ExprTreeNode *> stack(0);
    ExprTreeNode *root = new ExprTreeNode();
    root->type = ":=";
    ExprTreeNode *left_var = new ExprTreeNode();

    if (expression[0] == "del")
    {
        left_var->type = "DEL";
        root->left = left_var; ///
        ExprTreeNode *right_var = new ExprTreeNode();
        right_var->type = "VAR";
        right_var->id = "expression[2]";
        root->right = right_var; ///
        string del = expression[2];
        symtable->remove(del);
        expr_trees.push_back(root);
        return;
    }

    else if (expression[0] == "ret")
    {
        left_var->type = "RET"; // How to return the expression?????
        root->left = left_var;

        ExprTreeNode *root1 = new ExprTreeNode();
        ExprTreeNode *current = root1;

        vector<string> exp(expression.begin() + 2, expression.end());
        for (int i = 0; i < exp.size(); i++)
        {

            if (exp[i] == "(")
            {
                ExprTreeNode *Node = new ExprTreeNode();
                stack.push_back(current);
                current->left = Node;
                current = Node;
            }

            else if (exp[i] == "+" || exp[i] == "-" || exp[i] == "*" || exp[i] == "/")
            {
                if (exp[i] == "+")
                {
                    current->type = "ADD";
                    stack.push_back(current);
                    ExprTreeNode *Node = new ExprTreeNode();
                    current->right = Node;
                    current = Node;
                }
                else if (exp[i] == "-")
                {
                    current->type = "SUB";
                    stack.push_back(current);
                    ExprTreeNode *Node = new ExprTreeNode();
                    current->right = Node;
                    current = Node;
                }
                else if (exp[i] == "*")
                {
                    current->type = "MUL";
                    stack.push_back(current);
                    ExprTreeNode *Node = new ExprTreeNode();
                    current->right = Node;
                    current = Node;
                }
                else if (exp[i] == "/")
                {
                    current->type = "DIV";
                    stack.push_back(current);
                    ExprTreeNode *Node = new ExprTreeNode();
                    current->right = Node;
                    current = Node;
                }
                else
                {
                    current->type = "MOD";
                    stack.push_back(current);
                    ExprTreeNode *Node = new ExprTreeNode();
                    current->right = Node;
                    current = Node;
                }
            }

            else if (exp[i] == ")")
            {
                if (stack.size() > 0)
                {
                    current = stack[stack.size() - 1];
                    stack.pop_back();
                }
            }

            else
            {
                string s = exp[i];
                if (s[0] == 'a' || s[0] == 'b' || s[0] == 'c' || s[0] == 'd' || s[0] == 'e' || s[0] == 'f' || s[0] == 'g' || s[0] == 'h' || s[0] == 'i' ||
                    s[0] == 'j' || s[0] == 'k' || s[0] == 'l' || s[0] == 'm' || s[0] == 'n' || s[0] == 'o' || s[0] == 'p' || s[0] == 'q' || s[0] == 'r' || s[0] == 's' ||
                    s[0] == 't' || s[0] == 'u' || s[0] == 'v' || s[0] == 'w' || s[0] == 'x' || s[0] == 'y' || s[0] == 'z')
                {

                    current->type = "VAR";
                    current->id = exp[i];
                    if (stack.size() > 0)
                    {
                        current = stack[stack.size() - 1];
                        stack.pop_back();
                    }
                }

                else
                {
                    int n = stoi(s);
                    current->type = "VAL";
                    current->num = n;
                    if (stack.size() > 0)
                    {
                        current = stack[stack.size() - 1];
                        stack.pop_back();
                    }
                }
            }
        }
        root->right = root1;
        expr_trees.push_back(root);
    }

    else
    {
        left_var->type = "VAR";
        left_var->id = expression[0];
        symtable->insert(left_var->id);

        root->left = left_var;

        ExprTreeNode *root1 = new ExprTreeNode();
        ExprTreeNode *current = root1;

        vector<string> exp(expression.begin() + 2, expression.end());
        for (int i = 0; i < exp.size(); i++)
        {

            if (exp[i] == "(")
            {
                ExprTreeNode *Node = new ExprTreeNode();
                stack.push_back(current);
                current->left = Node;
                current = Node;
            }

            else if (exp[i] == "+" || exp[i] == "-" || exp[i] == "*" || exp[i] == "/")
            {
                if (exp[i] == "+")
                {
                    current->type = "ADD";
                    stack.push_back(current);
                    ExprTreeNode *Node = new ExprTreeNode();
                    current->right = Node;
                    current = Node;
                }
                else if (exp[i] == "-")
                {
                    current->type = "SUB";
                    stack.push_back(current);
                    ExprTreeNode *Node = new ExprTreeNode();
                    current->right = Node;
                    current = Node;
                }
                else if (exp[i] == "*")
                {
                    current->type = "MUL";
                    stack.push_back(current);
                    ExprTreeNode *Node = new ExprTreeNode();
                    current->right = Node;
                    current = Node;
                }
                else if (exp[i] == "/")
                {
                    current->type = "DIV";
                    stack.push_back(current);
                    ExprTreeNode *Node = new ExprTreeNode();
                    current->right = Node;
                    current = Node;
                }
                else
                {
                    current->type = "MOD";
                    stack.push_back(current);
                    ExprTreeNode *Node = new ExprTreeNode();
                    current->right = Node;
                    current = Node;
                }
            }

            else if (exp[i] == ")")
            {
                if (stack.size() > 0)
                {
                    current = stack[stack.size() - 1];
                    stack.pop_back();
                }
            }

            else
            {
                string s = exp[i];
                if (s[0] == 'a' || s[0] == 'b' || s[0] == 'c' || s[0] == 'd' || s[0] == 'e' || s[0] == 'f' || s[0] == 'g' || s[0] == 'h' || s[0] == 'i' ||
                    s[0] == 'j' || s[0] == 'k' || s[0] == 'l' || s[0] == 'm' || s[0] == 'n' || s[0] == 'o' || s[0] == 'p' || s[0] == 'q' || s[0] == 'r' || s[0] == 's' ||
                    s[0] == 't' || s[0] == 'u' || s[0] == 'v' || s[0] == 'w' || s[0] == 'x' || s[0] == 'y' || s[0] == 'z')
                {

                    current->type = "VAR";
                    current->id = exp[i];
                    if (stack.size() > 0)
                    {
                        current = stack[stack.size() - 1];
                        stack.pop_back();
                    }
                }

                else
                {
                    int n = stoi(s);
                    current->type = "VAL";
                    current->num = n;
                    if (stack.size() > 0)
                    {
                        current = stack[stack.size() - 1];
                        stack.pop_back();
                    }
                }
            }
        }
        root->right = root1;
        expr_trees.push_back(root);
    }
}

Parser::~Parser()
{
    while (!expr_trees.empty())
    {
        delete expr_trees.back();
        expr_trees.pop_back();
    }
}
