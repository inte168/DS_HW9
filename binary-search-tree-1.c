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



void inorderTraversal(Node* ptr)
{

}

void preorderTraversal(Node* ptr)
{

}

void postorderTraversal(Node* ptr)
{

}


int insert(Node* head, int key)
{
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
	//
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
		}
		return 1;
	}
}

Node* searchRecursive(Node* ptr, int key)
{

}

Node* searchIterative(Node* head, int key)
{

}

int freeBST(Node* head)
{
	//head가 다른 노드에 연결되지 않았을 때(head만 있음)
	if(head->left == head){
		free(head);
		return 1;
	}

	Node* p = head->left;

	//왼쪽의 노드(root)를 받아서 해제 후 head도 해제.
	//solution은 함수이니 안되면 함수로.
	Node* pre = NULL;
	while(1){
		if(p->left != NULL){
			pre = p;
			p = p->left;
		}
		else if(p->right !=NULL){
			pre = p;
			p=p->right;
		}
		else {
			free(p);
			p = pre;
		}
	}
	free(head);
	return 1;
}




