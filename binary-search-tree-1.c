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
	printf("-----������ 2021041047-----");


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


//inorder: ����-�߰�-������
void inorderTraversal(Node* ptr)
{
	if(ptr) {
		inorderTraversal(ptr->left);
		printf(" [%d] ", ptr->key);
		inorderTraversal(ptr->right);
	}
}

//preorder: �߰�-����-������
void preorderTraversal(Node* ptr)
{
	if(ptr) {
		printf(" [%d] ", ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}
}

//postorder: ����-������-�߰�
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
	//�� ��� ����
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	//head->left�� ��������� �ű�� ��带 ����.
	//head->left�� root����.
	if(head->left == NULL){
		head->left = newNode;
		return 1;
	}

	Node* ptr = head->left;
	Node* parentNode = NULL;
	while(ptr != NULL){
		//key���� ptr�� key���̸� �״�� ����
		//ó���� �ٷ� �ɸ��� ���� ���� if���� ����Ǿ��ٴ� ���
		//��ü�� root�̹Ƿ� parentNode�� NULL�̴�.
		if(ptr->key == key) return 1;

		//ptr���� �ƴѰ�� parentNode�� ptr�� �ű��
		parentNode = ptr;

		//ã�� key�� ũ�� ������, ������ �������� ptr�� �̵��Ѵ�.
		if(ptr->key<key) ptr=ptr->right;
		else ptr=ptr->left;
	}
	//�θ��� ���� �� ũ�� ���ʿ� ��ġ.
	if(parentNode->key >key) parentNode->left = newNode;
	//�׷��� ������(������) �����ʿ� ��ġ.
	else parentNode->right = newNode;
	return 1;

}

int deleteLeafNode(Node* head, int key)
{
	//��ó��
	if(head == NULL || head->left == NULL){
		printf("\n Error: Nothing to Delete.\n");
		return -1;
	}

	//root�� ptr��
	Node* ptr = head->left;
	//�θ� ���.
	Node* parentNode = head;

	while(ptr != NULL){
		//ã���� ��.
		if(ptr->key == key){
			//�¿� ������ ��� NULL == leaf ���.
			if(ptr->left == NULL && ptr->right == NULL){

				//ptr�� ������ �����ش�.
				if(parentNode == head) head->left = NULL;
				if(parentNode->left == ptr) parentNode->left = NULL;
				else parentNode->right = NULL;

				free(ptr);
			}
			//leaf�� �ƴѰ��.
			else printf("node [%d] is not a leaf\n", ptr->key);
			return 1;
		}
		//�̹� ptr�� �ƴ� ���.
		//parentNode�� �����ش�.
		parentNode = ptr;

		//�� ptr������ key�� ũ�� ������, ������ ���� ����.(������ �Ұ���)
		if(ptr->key < key) ptr = ptr->right;
		else ptr = ptr->left;
	}

	
}

//Ž��-����� ���
Node* searchRecursive(Node* ptr, int key)
{
	//ptr�� NULL�̸� NULL ����
	if(ptr == NULL) return NULL;

	//ã�� Ű���� ���� ptr�� ������ ���������� Ž��, ũ�� �������� Ž��
	if(ptr->key < key) ptr = searchRecursive(ptr->right, key);
	else if(ptr->key > key) ptr = searchRecursive(ptr->left, key);

	//�Ϲ������� ���⿡ �� ������ ptr�� key�� key�� ������ ��.
	//�� key�� ���� ������ ptr�� ����.
	//���� �ʴٸ� ������ �ɷ��� ptr ���� ������ ptr ���� �޾ƿ´�.
	return ptr;
}

//Ž��-�ݺ���(�������)
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
	//head�� �ٸ� ��忡 ������� �ʾ��� ��(head�� ����)
	if(head->left == head){
		free(head);
		return 1;
	}

	Node* p = head->left;

	//head ������ ���(root)�� �޾Ƽ� ����� �׷����� �� ���� �� head�� ����.
	freeNode(p);
	free(head);
	return 1;
}