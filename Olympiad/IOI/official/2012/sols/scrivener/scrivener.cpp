/*
    Solution for Scrivener, with TypeLetter and GetLetter in O(log N) and UndoCommands in O(1).
    
    Author: Matteo Boscariol
*/

#include<cstdlib>
#define MAXC 1000000
#define LOGMAXC 20

class node {
public:
    char l;
    node** parents;
    int depth;


    node(char letter, node* parent) {
        l = letter;

        if(parent == NULL) {
            depth=-1;
            parents = new node*[1];
            parents[0] = NULL;
        }
        else {
            depth=parent->depth+1;
            parents = new node*[LOGMAXC];
            parents[0] = parent;
            for(int i=1, j=2; j<=depth+1; i++, j*=2) {
                parents[i] = parents[i-1]->parents[i-1];
            }
        }
    };
};

node** command_base;
int n_commands;
node* current_position;
node* tree_root;

void Init() {
    command_base = new node*[MAXC];
    n_commands = 0;
    current_position = tree_root = new node('\0',NULL);
}

void TypeLetter(char L) {
    command_base[n_commands] = current_position;
    n_commands++;
    node* n = new node(L, current_position);
    current_position = n;
}

void UndoCommands(int U) {
    node *n = command_base[n_commands - U];
    command_base[n_commands] = current_position;
    n_commands++;
    current_position = n;
}

char GetLetter(int P)  {
    node* n = current_position;
    int distance = current_position->depth - P;

    for(int shift = LOGMAXC; shift >= 0; shift--) {
        if((distance >> shift)%2 == 1) 
          n = n->parents[shift];
    }
    return n->l;
}

