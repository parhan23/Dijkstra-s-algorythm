#include "main.h"

Link *queue = NULL;

void buildTree(Node *start)
{
    Node *current;
    Link *edge;
    
    start->dist = 0;
    start->state = Grey;
    enQue(start);
    while (current = deQue())  //Returns grey node with the least distance
                               //or NULL if queue is empty
    {
        edge = current->links;
        while (edge)
        {
            if (edge->link->state == Black)
            {
                edge = edge->next;
                continue;
            }

            if (edge->link->state == White ||
                current->dist + edge->weight < edge->link->dist)
            {
                edge->link->dist = current->dist + edge->weight;
                edge->link->prev = current;
            }
            edge->link->state = Grey;
            enQue(edge->link);
            edge = edge->next;
        }
        current->state = Black;
    }
}

void enQue(Node *newNode)
{
    Link *newQueNode = (Link *)malloc(sizeof(Link));

    newQueNode->link = newNode;
    newQueNode->weight = -2;  //Edge weight not used in queue
    
    newQueNode->next = queue;
    queue = newQueNode;
}

Node * deQue(void)
{
    Link *currLink;
    Link *prevFLink, *fLink;
    Node *foundNode;
    
    if (!queue)
        return NULL;
    
    currLink = queue;
    fLink = queue;
    prevFLink = NULL;
    
    while (currLink->next)
    {
        if (currLink->next->link->dist < fLink->link->dist)
        {
            fLink = currLink->next;
            prevFLink = currLink;
        }

        currLink = currLink->next;
    }
    foundNode = fLink->link;
    
    if (prevFLink == NULL)
        queue = queue->next;
    else
        prevFLink->next = fLink->next;

    free(fLink);

    return foundNode;
}