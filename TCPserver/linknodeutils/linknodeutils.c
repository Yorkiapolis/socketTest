//
// Created by york on 2021/10/19.
//
#include <linknodeutils.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct SocketNode{
    __int32_t _sock;
    SocketNode *next;
} SocketNode;

SocketNode *CreateNode(__int32_t sockArg){
    SocketNode *node = malloc(sizeof(SocketNode));
    node._sock = sockArg;
    node->next = NULL;
    return node;
}

void InsertNode(SocketNode *head, SocketNode *insertNode, int len){
    SocketNode *current = head;
    while (!current->next){
        current = current->next;
    }
    current->next = insertNode;
    len++;
}





