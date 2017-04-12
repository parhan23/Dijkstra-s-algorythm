#include "main.h"

Node *list = NULL;

int main(void)
{
    FILE *fp;
    Node *initNode;

#ifdef FP_DEFINED
    fp = fopen("graph2_2.in", "r");
#else
    fp = getFilePtr();
#endif

    buildGraph(fp);

    initNode = getInitNode();
    buildTree(initNode);
    printPaths();

    freeMem();
    
    return 0;
}

FILE * getFilePtr(void)
{
    char fname[MAX_FNAME];
    FILE *fp;
    
    do
    {
        system("cls");
        printf("Enter file name: ");
        scanf("%s", fname);
        fp = fopen(fname, "r");
    } while (!fp);
    
    return fp;
}

void buildGraph(FILE *fp)
{
    char nodeName;
    int edgeWeight;
    Node *ptr1, *ptr2;

    while (fscanf(fp, "%c", &nodeName) != EOF)
    {
        ptr1 = getPtr(nodeName);
        if (!ptr1)
            ptr1 = makeNode(nodeName);

        while (fscanf(fp, "%c", &nodeName) != EOF && nodeName != '\n')
        {
            if (nodeName == ' ')
                continue;
            fscanf(fp, "%d", &edgeWeight);

            ptr2 = getPtr(nodeName);
            if (!ptr2)
                ptr2 = makeNode(nodeName);
            
            linkNodes(ptr1, ptr2, edgeWeight);
        }
    }

    fclose(fp);
}

Node * makeNode(char aName)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    Node *ptr = list;

    newNode->name = aName;
    newNode->dist = -1;
    newNode->state = White;
    newNode->prev = NULL;
    newNode->links = NULL;

    if (!list)
    {
        newNode->next = NULL;
        list = newNode;
        return newNode;
    }

    while (ptr->next)
    {
        if (aName < ptr->next->name)
            break;
        else
            ptr = ptr->next;
    }

    newNode->next = ptr->next;
    ptr->next = newNode;
    
    return newNode;
}

Node * getPtr(char targetName)
{
    Node *ptr = list;

    while (ptr)
    {
        if (ptr->name == targetName)
            break;
        ptr = ptr->next;
    }

    return ptr;
}

void linkNodes(Node *init, Node *target, int edgeWeight)
{
    Link *newLink = (Link *)malloc(sizeof(Link));

    newLink->link = target;
    newLink->weight = edgeWeight;

    newLink->next = init->links;
    init->links = newLink;
}

Node * getInitNode(void)
{
    char nodeName;
    Node *initNode;
    
    do
    {
        system("cls");
        printf("Avaliable nodes:\n");
        printAvalNodes();
        printf("\n\nSelect initial node\n");
        printf("> ");
        scanf("%c", &nodeName);
        initNode = getPtr(nodeName);
    } while (!initNode);
    
    return initNode;
}

void printAvalNodes(void)
{
    Node *ptr = list;
    int nodesPrinted = 0;

    while (ptr)
    {
        printf("%c ", ptr->name);
        ptr = ptr->next;
        nodesPrinted++;
        if ((nodesPrinted % NODES_PER_ROW) == 0)
            printf("\n");
    }
}

void printPaths(void)
{
    Node *finish = list;
    Node *parent;

    setlocale(LC_ALL, "866");
    system("cls");
    while (finish)
    {
        printf("%c(%d)", finish->name, finish->dist);
        parent = finish->prev;
        while (parent)
        {
            printf(" <- %c(%d)", parent->name, parent->dist);
            parent = parent->prev;
        }
        printf("\n");
        finish = finish->next;
    }
}

void freeMem(void)
{
    Node *currNode = list, *prevNode;

    while (currNode)
    {
        prevNode = currNode;
        currNode = prevNode->next;
        free(prevNode);
    }
}