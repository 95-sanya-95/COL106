/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"
#include <iostream>
// Write your code below this line

EPPCompiler::EPPCompiler()
{
    mem_loc.resize(memory_size);
    for (int i = 0; i < memory_size; i++)
    {
        mem_loc[i] = 0;
    }
}

EPPCompiler::EPPCompiler(string out_file, int mem_limit)
{
    output_file = out_file;
    memory_size = mem_limit;
    mem_loc.resize(memory_size);
    // mem_loc.resize(memory_size);
    for (int i = 0; i < memory_size; i++)
    {
        mem_loc[i] = 0;
    }
}

void EPPCompiler::compile(vector<vector<string>> code)
{
    int n = code.size();
    // cout<<"code k size: "<<n<<endl;
    for (int j = 0; j < n; j++)
    {
        vector<string> exp = code[j];
        if (exp[0] == "del")
        {   
            int what = targ.symtable->search(exp[2]);
            mem_loc[what]=0;
            targ.symtable->assign_address(exp[2],-1);
            targ.parse(exp);
            vector<string> comman;
            comman.push_back("DEL = mem[" + to_string(what) + "]");
            // comman.push_back("PUSH = mem[" + to_string(what) + "]");
            write_to_file(comman);

        }

        else if (exp[0] == "ret")
        {
            targ.parse(exp);
            vector<string> comman = generate_targ_commands();
            write_to_file(comman);
        }

        else
        {  //cout<<mem_loc[0]<<endl;
            int add = 0;
            for (int i = 0; i < mem_loc.size(); i++)
            {
                if (mem_loc[i] == 0)
                {
                    add = i;
                    break;
                }
            }
            // cout<<"the memory it is accessing: "<<add<<endl;
            int what = targ.symtable->search(exp[0]);
            // cout<<"what is: "<<what<<endl;
            if(what==-1){
                targ.parse(exp);
                // for(int i=0; i<exp.size()-1; i++){
                //     cout << exp[i] << " ";
                // }
                // cout << exp[exp.size()-1] << endl;
                // cout<<targ.expr_trees.back()->type<<endl;
                // cout<<targ.expr_trees.back()->right->num<<endl;
                // if(targ.expr_trees.back()->right->left!=NULL){cout<<targ.expr_trees.back()->right->left->id<<endl;}
                targ.symtable->assign_address(exp[0],add);
                mem_loc[add]=1;

                vector<string> comman = generate_targ_commands();
                write_to_file(comman);
            }
            else{
                targ.parse(exp);
                targ.symtable->assign_address(exp[0],add);
                mem_loc[add]=1;
                mem_loc[what]=0;
                vector<string> comman = generate_targ_commands();
                write_to_file(comman);
            }
        }
    }
}

vector<string> generate(ExprTreeNode *temp, SymbolTable *symT)
{
    vector<string> str;
    if (temp == NULL)
    {
        return str;
    }
    if (temp->right != NULL)
    {
        if (temp->right->type == "ADD")
        {
            
            vector<string> right_subtree = generate(temp->right, symT);
            vector<string> left_subtree = generate(temp->left, symT);
            str.insert(str.end(), left_subtree.begin(), left_subtree.end());
            str.insert(str.end(), right_subtree.begin(), right_subtree.end());
            str.push_back("ADD");
        }
        else if (temp->right->type == "SUB")
        {
            
            vector<string> right_subtree = generate(temp->right, symT);
            vector<string> left_subtree = generate(temp->left, symT);
            str.insert(str.end(), left_subtree.begin(), left_subtree.end());
            str.insert(str.end(), right_subtree.begin(), right_subtree.end());
            str.push_back("SUB");
        }
        else if (temp->right->type == "MUL")
        {
            
            vector<string> right_subtree = generate(temp->left, symT);
            vector<string> left_subtree = generate(temp->right, symT);
            str.insert(str.end(), left_subtree.begin(), left_subtree.end());
            str.insert(str.end(), right_subtree.begin(), right_subtree.end());
            str.push_back("MUL");
        }
        else if (temp->right->type == "DIV")
        {
            
            vector<string> right_subtree = generate(temp->left, symT);
            vector<string> left_subtree = generate(temp->right, symT);
            str.insert(str.end(), left_subtree.begin(), left_subtree.end());
            str.insert(str.end(), right_subtree.begin(), right_subtree.end());
            str.push_back("DIV");
        }

        else if (temp->right->type == "VAL")
        {
            str.push_back("PUSH " + to_string(temp->right->num));
        }
        else if (temp->right->type == "VAR")
        {
            str.push_back("PUSH mem[" + to_string(symT->search(temp->right->id)) + "]");
        }
    }
    
    if (temp->left != NULL)
    {
        if (temp->left->type == "DEL")
        {
            str.push_back("DEL = mem[" + temp->left->id + "]");
            // str.push_back("DEL = mem[" + temp->left->id + "]");
            // str.push_back("PUSH = mem[" + temp->left->id + "]");
        }
        else if (temp->left->type == "RET")
        {
            str.push_back("RET = POP");
        }
        else if (temp->type==":=" && temp->left->type == "VAR")
        {
            str.push_back("mem[" + to_string(symT->search(temp->left->id)) + "] = POP");
        }
        else if (temp->type!=":=" && temp->left->type == "VAR"){
            str.push_back("PUSH mem[" + to_string(symT->search(temp->left->id)) + "]");
        }
        else if(temp->left->type == "VAL"){
            str.push_back("PUSH " + to_string(temp->left->num));
        }
        else if (temp->left->type == "ADD")
        {
            
            vector<string> right_subtree = generate(temp->right, symT);
            vector<string> left_subtree = generate(temp->left, symT);
            str.insert(str.end(), left_subtree.begin(), left_subtree.end());
            str.insert(str.end(), right_subtree.begin(), right_subtree.end());
            str.push_back("ADD");
        }
        else if (temp->left->type == "SUB")
        {
            
            vector<string> right_subtree = generate(temp->right, symT);
            vector<string> left_subtree = generate(temp->left, symT);
            str.insert(str.end(), left_subtree.begin(), left_subtree.end());
            str.insert(str.end(), right_subtree.begin(), right_subtree.end());
            str.push_back("SUB");
        }
        else if (temp->left->type == "MUL")
        {
            
            vector<string> right_subtree = generate(temp->left, symT);
            vector<string> left_subtree = generate(temp->right, symT);
            str.insert(str.end(), left_subtree.begin(), left_subtree.end());
            str.insert(str.end(), right_subtree.begin(), right_subtree.end());
            str.push_back("MUL");
        }
        else if (temp->left->type == "DIV")
        {
            
            vector<string> right_subtree = generate(temp->left, symT);
            vector<string> left_subtree = generate(temp->right, symT);
            str.insert(str.end(), left_subtree.begin(), left_subtree.end());
            str.insert(str.end(), right_subtree.begin(), right_subtree.end());
            str.push_back("DIV");
        }
    }
    return str;
}

vector<string> EPPCompiler::generate_targ_commands()
{
    ExprTreeNode *tree = targ.expr_trees.back();
    // cout<<tree->type<<endl;
    // cout<<tree->right->type<<endl;
    // if(tree->right->left != NULL){ cout<<tree->right->left->id<<endl;}
    // if(tree->right->right != NULL){ cout<<tree->right->right->id<<endl;}
    vector<string>final = generate(tree, targ.symtable);
    return final;
}

void EPPCompiler::write_to_file(vector<string> commands)
{
    ofstream outFile(output_file, ios::app);
    for (const string &comman : commands)
    {
        outFile << comman << endl;
    }
    outFile.close();

}

EPPCompiler::~EPPCompiler()
{
}

// int main(){
//     vector<string> vec1;
//     vec1.push_back("x");
//     vec1.push_back(":=");
//     vec1.push_back("3");
    
    
//     // b=(((2×a)+(a-7))-(12))
//     vector<string> vec2;
//     vec2.push_back("y");
//     vec2.push_back(":=");
//     vec2.push_back("2");

//     vector<string> vec3;
//     vec3.push_back("z");
//     vec3.push_back(":=");
//     vec3.push_back("(");
//     vec3.push_back("x");
//     vec3.push_back("-");
//     vec3.push_back("y");
//     vec3.push_back(")");

//     vector<string> vec4;
//     vec4.push_back("ret");
//     vec4.push_back(":=");
//     vec4.push_back("z");
    
//     vector<vector<string> > code;
//     code.push_back(vec1);
//     code.push_back(vec2);
//     code.push_back(vec3);
//     code.push_back(vec4);
//     // cout<<stoi("-123")<<endl;

//     EPPCompiler compiler("outp.txt",3);
//     compiler.compile(code);
// }

// // g++ -std=c++20 eppcompiler.cpp symnode.cpp parser.cpp symtable.cpp exprtreenode.cpp heapnode.cpp minheap.cpp -o k
