#define MAX 5
#define MIN 3   //5/2=ceiling of 2.5
#include <iostream>
#include <cmath>
#include <stdlib.h>

using namespace std;

struct node {
    int ele[MAX];
    struct node * child[MAX];  //max of 5
    struct node * parent;    //holds address of parent node of every node
};
typedef struct node * NODE;

class btree{
    NODE root;  //declare root
public:
    btree(){                 //constructor
        root=createNode();
    }
    void insert_integer(int);
    int searchNode(int);
    void displayTree();
    int isFull(NODE);
    NODE createNode();
    NODE find_leaf(NODE,int);
    void split(NODE);
    void sort_node(NODE);
    void new_parent(NODE,int,int);
};
NODE btree::createNode()  //creates a node
{
    int i;
    NODE temp= new struct node;
    if(!temp)
    {
        cout<<"Out of memory";
        exit(0);
    }
    for(i=0;i<MAX;i++)
    {
        temp->ele[i]=-1;
        temp->child[i]=NULL;
    }
    temp->parent=NULL;
    return temp;
}
void btree::insert_integer(int n) {  //insertion into node
    int i, j, t, max;
    NODE temp = find_leaf(root, n);
    if (!temp) {
        cout << "Error. Duplicate";
        return;
    }
    if (!isFull(temp)) {
        cout << "Element inserted succesfully\n";
        for (i = 0; i < MAX; i++) {
            if (temp->ele[i] == -1) {
                temp->ele[i] = n;
                break;
            }
            max = temp->ele[i];
        }

        sort_node(temp);
        if (n > max && temp->parent != NULL)
            new_parent(temp->parent, n, max);
        return;
    }
    if (isFull(temp)) {
        split(temp);
        insert_integer(n);
    }
}
void btree::sort_node(NODE x) {
    int i, j;
    int temp_ele;
    NODE temp_child;
    for (i = 0; i < MAX && x->ele[i] != -1; i++)
    {
        for (j = i + 1; j < MAX && x->ele[j] != -1; j++) {
            if (x->ele[i] > x->ele[j]) {
                temp_ele = x->ele[i];
                temp_child = x->child[i];

                x->ele[i] = x->ele[j];
                x->child[i] = x->child[j];
            }
        }
    }
}
int btree::isFull(NODE x)   //check if it full
{
    return(x->ele[MAX-1]==-1)?0:1;
}


NODE btree::find_leaf(NODE x, int key)
{
    int i;
    if(x->child[0]==NULL)
    {
        for(i=0;i<MAX;i++)
            if(key==x->ele[i])
                return NULL;
            return x;
    }
    for(i=0;i<MAX;i++)
    {
        if(x->ele[i]>=key)
            return find_leaf(x->child[i],key);
        if(x->ele[i]==-1)
            return find_leaf(x->child[i-1],key);
    }
    return find_leaf(x->child[MAX-1],key);
}

void btree::split(NODE x) {   //split if full
    int i;
    NODE temp;
    if (x->parent = NULL) {
        temp = createNode();
        root = createNode();

        root->ele[0] = x->ele[MIN - 1];
        root->child[0] = x;
        root->ele[1] = x->ele[MAX - 1];
        root->child[1] = temp;

        x->parent = root;
        temp->parent = x->parent;
    } else {
        if (isFull(x->parent))
            split(x->parent);
        temp = createNode();
        temp->parent = x->parent;
        for (i = 0; i < MAX; i++) {
            if (x->parent->ele[i] == x->ele[MAX - 1])
                x->parent->child[i] = temp;
            if (x->parent->ele[i] == -1) {
                x->parent->ele[i] = x->ele[MIN - 1];
                x->parent->child[i] = x;
                break;
            }
        }
    }
    for (i = 0; i < MIN; i++) {
        temp->ele[i] = x->ele[MIN + i];
        x->ele[MIN + i] = -1;
        temp->child[i] = x->child[MIN + i];
        if (temp->child[i] != NULL)
            temp->child[i]->parent = temp;
        x->child[MIN + i] = NULL;
    }
    sort_node(x->parent);
}

void btree::new_parent(NODE x, int n, int max)  //promotion to a new parent
{
    int i,new_max;
    for(i=0;i<MAX&&(x->ele[i]!=-1);i++)
    {
        new_max = x->ele[i];
        if (x->ele[i] == max)
            x->ele[i] = n;
    }
    if(n>new_max && x->parent!=NULL)
        new_parent(x->parent,n,max);
}

int btree::searchNode(int key)
{
    NODE temp = find_leaf(root, key);
    if (temp == NULL)
        return 1;
    return 0;
}
void btree::displayTree() {
    NODE queue[50];
    int f = 0, r = -1, lvl = -1, i;
    queue[++r] = NULL;
    queue[++r] = root;
    while (f < r) {
        if (queue[f] == NULL) {
            cout << "\n\nLevel-->" << ++lvl << endl;
            if (queue[r] != NULL)
                queue[++r] = NULL;
            f++;
        } else {
            for (i = 0; i < MAX; i++) {
                if (queue[f]->ele[i] != -1)
                    cout << queue[f]->ele[i] << " ";
                if (queue[f]->child[i] != NULL)
                    queue[++r] = queue[f]->child[i];
            }
            cout << " ";
            f++;
        }
    }
}
int main() {
    btree b;
    int choice, n, error;
    while (1) {   //menu for user while user is running program
        cout
                << "Select your choice\n1.Insertion of N (in the range [0,...,3*N], with N >= 400. \n2.Search keys in range [N, 2*N\n3.Display 5 way B Tree.\n4.Exit\nEnter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Input N integer: ";
                cin >> n;
                for(int i = 0 ; i < n; i++)
                {
                    b.insert_integer(rand() % (3*n) + 0);   //takes user input of n and Generates a sequence of N random integers in the range
                }
                break;

            case 2:
                cout << "Type in integer in range [N, 2*N]: ";   //to find number in the range of  [N, 2*N]
                cin >> n;
                error = b.searchNode(n);
                if (error)
                    cout << "Element found";
                else
                    cout << "Element was not found";
                break;

            case 3:
                b.displayTree();   //display tree
                break;
            default:
                exit(0);
        }

    }
}


