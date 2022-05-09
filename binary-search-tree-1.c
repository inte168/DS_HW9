/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	printf("-----허정윤 2021041047-----");


	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;
	return 1;
}


//inorder: 왼쪽-중간-오른쪽
void inorderTraversal(Node* ptr)
{
	if(ptr) {
		inorderTraversal(ptr->left);
		printf(" [%d] ", ptr->key);
		inorderTraversal(ptr->right);
	}
}

//preorder: 중간-왼쪽-오른쪽
void preorderTraversal(Node* ptr)
{
	if(ptr) {
		printf(" [%d] ", ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}
}

//postorder: 왼쪽-오른쪽-중간
void postorderTraversal(Node* ptr)
{
	if(ptr) {
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf(" [%d] ", ptr->key);
	}
}


int insert(Node* head, int key)
{
	if(head == NULL){
		printf("Error: head is NULL.\n");
		return 1;
	}
	//새 노드 생성
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	//head->left가 비어있으면 거기로 노드를 삽입.
	//head->left는 root노드다.
	if(head->left == NULL){
		head->left = newNode;
		return 1;
	}

	Node* ptr = head->left;
	Node* parentNode = NULL;
	while(ptr != NULL){
		//key값이 ptr의 key값이면 그대로 리턴
		//처음에 바로 걸리는 경우는 위의 if문도 실행되었다는 얘기
		//자체가 root이므로 parentNode가 NULL이다.
		if(ptr->key == key) return 1;

		//ptr값이 아닌경우 parentNode로 ptr을 옮기고
		parentNode = ptr;

		//찾는 key가 크면 오른쪽, 작으면 왼쪽으로 ptr을 이동한다.
		if(ptr->key<key) ptr=ptr->right;
		else ptr=ptr->left;
	}
	//부모노드 값이 더 크면 왼쪽에 배치.
	if(parentNode->key >key) parentNode->left = newNode;
	//그렇지 않으면(작으면) 오른쪽에 배치.
	else parentNode->right = newNode;
	return 1;

}

int deleteLeafNode(Node* head, int key)
{
	//전처리
	if(head == NULL || head->left == NULL){
		printf("\n Error: Nothing to Delete.\n");
		return -1;
	}

	//root를 ptr에
	Node* ptr = head->left;
	//부모 노드.
	Node* parentNode = head;

	while(ptr != NULL){
		//찾았을 때.
		if(ptr->key == key){
			//좌우 연결이 모두 NULL == leaf 노드.
			if(ptr->left == NULL && ptr->right == NULL){

				//ptr의 연결을 끊어준다.
				if(parentNode == head) head->left = NULL;
				if(parentNode->left == ptr) parentNode->left = NULL;
				else parentNode->right = NULL;

				free(ptr);
			}
			//leaf가 아닌경우.
			else printf("node [%d] is not a leaf\n", ptr->key);
			return 1;
		}
		//이번 ptr이 아닌 경우.
		//parentNode를 내려준다.
		parentNode = ptr;

		//현 ptr값보다 key가 크면 오른쪽, 작으면 왼쪽 노드로.(같은건 불가능)
		if(ptr->key < key) ptr = ptr->right;
		else ptr = ptr->left;
	}

	
}

//탐색-재귀적 방식
Node* searchRecursive(Node* ptr, int key)
{
	//ptr이 NULL이면 NULL 리턴
	if(ptr == NULL) return NULL;

	//찾는 키보다 현재 ptr이 작으면 오른쪽으로 탐색, 크면 왼쪽으로 탐색
	if(ptr->key < key) ptr = searchRecursive(ptr->right, key);
	else if(ptr->key > key) ptr = searchRecursive(ptr->left, key);

	//일반적으로 여기에 올 때에는 ptr의 key와 key가 동일할 때.
	//즉 key의 값과 동일한 ptr을 리턴.
	//같지 않다면 위에서 걸려서 ptr 값이 동일한 ptr 값을 받아온다.
	return ptr;
}

//탐색-반복문(비순차적)
Node* searchIterative(Node* head, int key)
{
	Node*ptr = head->left;

	while(ptr != NULL){
		if(ptr->key == key) return ptr;

		if(ptr->key < key ) ptr = ptr->right;
		else ptr = ptr->left;
	}

	return NULL;
}

void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{
	//head가 다른 노드에 연결되지 않았을 때(head만 있음)
	if(head->left == head){
		free(head);
		return 1;
	}

	Node* p = head->left;

	//head 왼쪽의 노드(root)를 받아서 연결된 그래프를 쭉 해제 후 head도 해제.
	freeNode(p);
	free(head);
	return 1;
}