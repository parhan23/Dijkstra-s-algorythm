#include <stdio.h>
#include <windows.h>
#include <locale.h>

#define FP_DEFINED

#define MAX_FNAME 31
#define NODES_PER_ROW 20

enum NodeState
{
    White = 0,
    Grey = 1,
    Black = 2
};

typedef struct Link Link;

struct Node
{
    char name;
    int dist;
    int state;

    Node *prev;
    Link *links;
    Node *next;
};

struct Link
{
    Node *link;
    int weight;
    Link *next;
};

FILE * getFilePtr(void);

void buildGraph(FILE *);
Node * makeNode(char);
Node * getPtr(char);
void linkNodes(Node *, Node *, int);

Node * getInitNode(void);
void printAvalNodes(void);

void buildTree(Node *);
void enQue(Node *);
Node * deQue(void);

void printPaths(void);
void freeMem(void);