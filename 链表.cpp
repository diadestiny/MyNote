#include"pch.h"


#include<iostream>
#include<stdio.h>
#include"math.h"
#include<vector>
#include<forward_list>
#define HEADFLAG -1
using namespace std;

struct	Node
{
	int data;
	struct Node * next;
};
struct Node* createList()
{
	struct Node *headNode = (struct Node*)malloc(sizeof(struct Node));
	headNode->data = HEADFLAG;
	headNode->next = NULL;
	return headNode;
}
struct Node* createNode(int data)
{
	struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}
void printList(struct Node* headNode)
{
	struct Node *pNode = headNode->next;
	while (pNode)
	{
		printf("%d->", pNode->data);
		pNode = pNode->next;

	}
	printf("\n");
};
void insertNodeHead(struct Node*headNode, int data)
{
	struct Node* newNode = createNode(data);
	newNode->next = headNode->next;
	headNode->next = newNode;
}
void deleteNodeByAppoin(struct Node*headNode, int posData)
{
	struct Node* posNode = headNode->next;
	struct Node* posNodeFront = headNode;
	if (posNode == NULL)
	{
		printf("无相关信息无法删除");
			return;
	}
	else {
		while (posNode->data != posData)
		{
			posNodeFront = posNode;
			posNode = posNodeFront->next;
			if (posNode ==NULL)
			{
				printf("无相关信息无法删除");
				return;
			}

		}
		posNodeFront->next = posNode->next;
		free(posNode);
	}
}
int main(int argc, char const *argv[])
{
	struct Node * headNode = createList();
	insertNodeHead(headNode, 1);
	insertNodeHead(headNode, 2);
	insertNodeHead(headNode, 3);
	printList(headNode);
	deleteNodeByAppoin(headNode,2);
		printList(headNode);
	system("pause");
	return 0;
}
