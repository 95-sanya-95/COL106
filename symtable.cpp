/* Do NOT add/remove any includes statements from this header file */
/* unless EtPLICTLY clarified on Piazza. */
#include "symtable.h"
#include <iostream>
// Write your code below this line

int get_Height(SymNode *node)
{
    if (node == NULL)
    {
        return -1;
    }
    else
    {
        int h = 1 + max(get_Height(node->left), get_Height(node->right));
        return h;
    }
}

int is_balance(SymNode *node)
{ // 1 meres right heavy, -1 meres left heavy, 0 meres balanced
    if (node->left == NULL && node->right == NULL)
    {
        return 0;
    }
    else
    {
        int l1 = get_Height(node->left);
        int r1 = get_Height(node->right);
        if (l1 == r1 || abs(l1 - r1) == 1)
        {
            // cout<<"lopopo"<<endl;
            return 0;
        }
        else if (l1 - r1 >= 2)
        {
            // cout<<"lopopo"<<endl;
            return -1;
        }
        else
        {
            // cout<<"lopopo"<<endl;
            return 1;
        }
    }
}

int which_heavy(SymNode *node)
{ // 1 when right is heavy, -1 when left is heavy, 0 when both are equal
    if (node->left == NULL && node->right == NULL)
    {
        return 0;
    }
    else if (node->left == NULL)
    {
        return 1;
    }
    else if (node->right == NULL)
    {
        return -1;
    }
    else
    {
        int l1 = get_Height(node->left);
        int r1 = get_Height(node->right);
        if (l1 == r1)
        {
            return 0;
        }
        else if (l1 > r1)
        {
            return -1;
        }
        return 1;
    }
}

SymbolTable::SymbolTable()
{
    size = 0;
    root = NULL;
}

void update_height(SymNode *root)
{
    if (root == NULL)
    {
        return;
    }

    update_height(root->left);  // Recursively update the left subtree
    update_height(root->right); // Recursively update the right subtree

    // Update the height of the current node based on its children's heights
    int leftHeight = (root->left != NULL) ? root->left->height : -1;
    int rightHeight = (root->right != NULL) ? root->right->height : -1;
    root->height = 1 + max(leftHeight, rightHeight);
}

void SymbolTable::insert(string k) // need to optimise the update height function
{
    size++;
    if (root == NULL)
    {
        root = new SymNode(k);
    }

    else
    {
        SymNode *current = root;
        SymNode *parent = nullptr;
        while (current != NULL)
        {
            parent = current;
            if (k < current->key)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }

        SymNode *newNode = new SymNode(k);
        newNode->par = parent;
        current = newNode;

        if (k < parent->key)
        {
            parent->left = current;
        }
        else
        {
            parent->right = current;
        }
        // cout<<root->left->key<<endl;

        SymNode *c = current;
        while (c != NULL)
        {
            int n = get_Height(c);

            c->height = n;
            c = c->par;
        };
        SymNode *cu = current;

        while (is_balance(cu) == 0)
        {
            if (cu->par == NULL)
            {
                break;
            }
            cu = cu->par;
        }
        if (is_balance(cu) != 0)
        {
            current = cu;
        }

        if (is_balance(current) == 1)
        {
            if (which_heavy(current->right) == -1)
            {

                if (current->par == NULL)
                {

                    root = current->LeftRightRotation();
                }
                else
                {
                    SymNode *curr2 = current->par;
                    if (curr2->right == current)
                    {
                        SymNode *curr = current->LeftRightRotation();
                        curr->par = curr2;
                        curr2->right = curr;
                    }
                    else
                    {
                        SymNode *curr = current->LeftRightRotation();
                        curr->par = curr2;
                        curr2->left = curr;
                    }
                }
                update_height(root);
            }
            else
            {
                // cout<<"hey"<<endl;
                if (current->par == NULL)
                {
                    SymNode *curr = current->LeftLeftRotation();
                    root = curr;
                    curr->par = NULL;
                }
                else
                {
                    SymNode *curr2 = current->par;
                    if (curr2->right == current)
                    {
                        SymNode *curr = current->LeftLeftRotation();
                        curr->par = curr2;
                        curr2->right = curr;
                    }
                    else
                    {
                        SymNode *curr = current->LeftLeftRotation();
                        curr->par = curr2;
                        curr2->left = curr;
                    }
                }
                update_height(root);
            }
            return;
        }

        else if (is_balance(current) == -1)
        {
            if (which_heavy(current->left) == 1)
            {

                if (current->par == NULL)
                {

                    SymNode *curr = current->RightLeftRotation();
                    root = curr;
                    curr->par = NULL;
                }
                else
                {
                    SymNode *curr2 = current->par;
                    if (curr2->right == current)
                    {
                        SymNode *curr = current->RightLeftRotation();
                        curr->par = curr2;
                        curr2->right = curr;
                    }
                    else
                    {
                        SymNode *curr = current->RightLeftRotation();
                        curr->par = curr2;
                        curr2->left = curr;
                    }
                }
                update_height(root);
            }
            else
            {
                // cout<<"hey"<<endl;
                if (current->par == NULL)
                {
                    SymNode *curr = current->RightRightRotation();
                    root = curr;
                    curr->par = NULL;
                }
                else
                {
                    SymNode *curr2 = current->par;
                    if (curr2->right == current)
                    {
                        SymNode *curr = current->RightRightRotation();
                        curr->par = curr2;
                        curr2->right = curr;
                    }
                    else
                    {
                        SymNode *curr = current->RightRightRotation();
                        curr->par = curr2;
                        curr2->left = curr;
                    }
                }
                update_height(root);
            }
        }
        return;
    }
}

int SymbolTable::search(string k)
{
    SymNode *current = root;
    while (current != NULL)
    {
        if (current->key == k)
        {
            return current->address;
        }
        else if (k > current->key)
        {
            current = current->right;
        }
        else
        {
            current = current->left;
        }
    }
    return -1; // not found case
}

void SymbolTable::assign_address(string k, int idt)
{
    SymNode *current = root;
    while (current != NULL)
    {
        if (current->key == k)
        {
            current->address = idt;
            return;
        }
        else if (k > current->key)
        {
            current = current->right;
        }
        else
        {
            current = current->left;
        }
    }
    return;
}

int SymbolTable::get_size()
{
    return size;
}

SymNode *SymbolTable::get_root()
{
    return root;
}

SymbolTable::~SymbolTable()
{
    delete root; // will automatically delete all the elements, as I have  deleted left and right in the destructor of symnode.
}

void SymbolTable::remove(string k)
{
    if (root == NULL)
    {
        return;
    }
    SymNode *curr = root;
    while (curr != NULL)
    {
        if (k.compare(curr->key) < 0)
        {
            curr = curr->left;
        }
        else if (k.compare(curr->key) > 0)
        {
            curr = curr->right;
        }
        else
        {
            break;
        }
    }
    if (curr == NULL)
    {
        return;
    }
    size--;

    SymNode *still_left = curr;
    if (curr->left == NULL && curr->right == NULL)
    {
        SymNode *paren = curr->par;
        if (paren == NULL)
        {
            root = NULL;
            delete curr;
            return;
        }
        if (paren->right == curr)
        {
            paren->right = NULL;
        }
        else
        {
            paren->left = NULL;
        }
        still_left = paren;
        delete curr;
    }

    else if (curr->left == NULL && curr->right != NULL)
    {
        SymNode *paren = curr->par;
        if (paren == NULL)
        {
            root = curr->right;
            curr->right = NULL;
            root->par = NULL;
            delete curr;
            return;
        }
        if (paren->right == curr)
        {
            paren->right = curr->right;
        }
        else
        {
            paren->left = curr->right;
        }
        curr->right->par = paren;
        still_left = paren;
        curr->right = NULL;
        delete curr;
    }

    else if (curr->left != NULL && curr->right == NULL)
    {
        SymNode *paren = curr->par;
        if (paren == NULL)
        {
            root = curr->left;
            curr->left = NULL;
            root->par = NULL;
            delete curr;
            return;
        }
        if (paren->right == curr)
        {
            paren->right = curr->left;
        }
        else
        {
            paren->left = curr->left;
        }
        curr->left->par = paren;
        still_left = paren;
        curr->left = NULL;
        delete curr;
    }

    else
    {
        SymNode *tempo = curr->right;
        while (tempo->left != NULL)
        {
            tempo = tempo->left;
        }
        string t = tempo->key;
        tempo->key = curr->key;
        curr->key = t;
        int z = tempo->address;
        tempo->address = curr->address;
        curr->address = z;
        curr = tempo;
        if (curr->par->right == curr)
        {
            curr->par->right = curr->right;
        }
        else
        {
            curr->par->left = curr->right;
        }
        if (curr->right != NULL)
        {
            curr->right->par = curr->par;
            curr->right = NULL;
        }
        still_left = curr->par;
        delete curr;
    }

    curr = still_left;
    curr->height = get_Height(curr);

    if (is_balance(curr) == 1)
    {
        if (which_heavy(curr->right) == -1)
        {
            if (curr->par == NULL)
            {
                root = curr->LeftRightRotation();
            }
            else
            {
                SymNode *res = curr->LeftRightRotation();
                SymNode *paren = res->par;
                if (paren->left == curr)
                {
                    paren->left = res;
                }
                else
                {
                    paren->right = res;
                }
                curr = res;
            }
        }
        else
        {
            if (curr->par == NULL)
            {
                root = curr->LeftLeftRotation();
            }
            else
            {
                SymNode *res = curr->LeftLeftRotation();
                SymNode *paren = res->par;
                if (paren->left == curr)
                {
                    paren->left = res;
                }
                else
                {
                    paren->right = res;
                }
                curr = res;
            }
        }
    }
    else if (is_balance(curr) == -1)
    {
        if (which_heavy(curr->left) == 1)
        {
            if (curr->par == NULL)
            {
                root = curr->RightLeftRotation();
            }
            else
            {
                SymNode *res = curr->RightLeftRotation();
                SymNode *paren = res->par;
                if (paren->left == curr)
                {
                    paren->left = res;
                }
                else
                {
                    paren->right = res;
                }
                curr = res;
            }
        }
        else
        {
            if (curr->par == NULL)
            {
                root = curr->RightRightRotation();
            }
            else
            {
                SymNode *res = curr->RightRightRotation();
                SymNode *paren = res->par;
                if (paren->left == curr)
                {
                    paren->left = res;
                }
                else
                {
                    paren->right = res;
                }
                curr = res;
            }
        }
    }

    while (curr->par != NULL)
    {
        curr = curr->par;
        curr->height = get_Height(curr);
        if (is_balance(curr) == 0)
        {
            continue;
        }
        else if (is_balance(curr) == 1)
        {
            if (which_heavy(curr->right) == -1)
            {
                if (curr->par == NULL)
                {
                    root = curr->LeftRightRotation();
                }
                else
                {
                    SymNode *res = curr->LeftRightRotation();
                    SymNode *paren = res->par;
                    if (paren->left == curr)
                    {
                        paren->left = res;
                    }
                    else
                    {
                        paren->right = res;
                    }
                    curr = res;
                }
            }
            else
            {
                if (curr->par == NULL)
                {
                    root = curr->LeftLeftRotation();
                }
                else
                {
                    SymNode *res = curr->LeftLeftRotation();
                    SymNode *paren = res->par;
                    if (paren->left == curr)
                    {
                        paren->left = res;
                    }
                    else
                    {
                        paren->right = res;
                    }
                    curr = res;
                }
            }
        }
        else if (is_balance(curr) == -1)
        {
            if (which_heavy(curr->left) == 1)
            {
                if (curr->par == NULL)
                {
                    root = curr->RightLeftRotation();
                }
                else
                {
                    SymNode *res = curr->RightLeftRotation();
                    SymNode *paren = res->par;
                    if (paren->left == curr)
                    {
                        paren->left = res;
                    }
                    else
                    {
                        paren->right = res;
                    }
                    curr = res;
                }
            }
            else
            {
                if (curr->par == NULL)
                {
                    root = curr->RightRightRotation();
                }
                else
                {
                    SymNode *res = curr->RightRightRotation();
                    SymNode *paren = res->par;
                    if (paren->left == curr)
                    {
                        paren->left = res;
                    }
                    else
                    {
                        paren->right = res;
                    }
                    curr = res;
                }
            }
        }
    }
}

// void inorderTraversal(SymNode *root)
// {
//     if (root != nullptr)
//     {
//         inorderTraversal(root->left);
//         std::cout << root->key << " ";
//         inorderTraversal(root->right);
//     }
// }

// int main()
// {
//     SymbolTable *table = new SymbolTable();

//     table->insert("s");
//     table->insert("h");
//     table->insert("a");
//     table->insert("c");
//     table->insert("b");
//     table->insert("e");
//     cout<<"root is: "<<table->get_root()->key<<endl;
//     cout<<"root's height is: "<<table->get_root()->height<<endl;
//     cout<<table->get_root()->left->key<<endl;
//     cout<<table->get_root()->left->height<<endl;
//     cout<<table->get_root()->right->left->key<<endl;
//     cout<<table->get_root()->right->left->height<<endl;
//     cout<<table->get_root()->right->right->key<<endl;
//     std::cout << "Inorder traversal of the AVL tree: ";
//     inorderTraversal(table->get_root());
//     std::cout << std::endl;
//     // table->remove()
//     // table->remove("yuvi");
//     std::cout << "Inorder traversal of the AVL tree: ";
//     inorderTraversal(table->get_root());
//     std::cout << std::endl;
//     return 0;
// }

// int main(){
//     SymbolTable ayo;
//     ayo.insert("s");
//     cout << ayo.get_root()->height << endl;
//     ayo.insert("h");
//     cout << ayo.get_root()->height << endl;
//     ayo.insert("a");
//     ayo.insert("c");
//     ayo.insert("b");
//     ayo.insert("e");
//     cout << ayo.get_root()->height << endl;
//     cout << ayo.get_root()->right->left->key << endl;
//     ayo.remove("e");
//     cout << ayo.get_root()->key << endl;
//     ayo.remove("a");
//     cout << ayo.get_root()->key << endl;
//     // cout << 123432 << endl;
//     // cout << ayo.get_root()->key << endl;
//     ayo.remove("b");
//     cout << ayo.get_root()->key << endl;
// }