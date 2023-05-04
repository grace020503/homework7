#include<stdio.h>
#include<stdlib.h>


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

int initialize(headNode** h); // 리스트 선언

int freeList(headNode* h); // 리스트 초기화

int insertNode(headNode* h, int key); // 노드 삽입 함수
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h); // 노드 삭제 함수
int deleteFirst(headNode* h);
int invertList(headNode* h); // 노드 반전 함수

void printList(headNode* h); // 노드 출력


int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		Printstudent();
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


void Printstudent()
{
	char *name = "Kim sieun";
	char *id = "2021053007";
	printf("----- [%s] [%s] -----\n", name, id);
}

// 리스트 실행 함수
int initialize(headNode** h) {

	if(*h != NULL)
		freeList(*h); // 리스트 초기화

	*h = (headNode*)malloc(sizeof(headNode)); // 동적 메모리 할당
	(*h)->first = NULL;
	return 1;
}

// 리스트 초기화 함수
int freeList(headNode* h){
	listNode* p = h->first; // 첫번째 리스트를 가리키는 포인터 생성

	listNode* prev = NULL; // 이전 노드를 가리키는 포인터 초기화
	while(p != NULL) { // while루프로 모든 노드 초기화
		prev = p;
		p = p->rlink;
		free(prev);
	}
	free(h); // headnode 포인터가 가리키는 메모리 해제, 전체 리스트 삭제
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) { // 리스트가 비어있을 때 출력 함수
		printf("Nothing to print....\n");
		return;
	}

	p = h->first; // 첫번째 노드를 가리킨다

	while(p != NULL) { // 마지막 빈 노드를 발견할 때까지 반복
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink; // 다음 오른쪽 노드 출력 준비
		i++;
	}

	printf("  items = %d\n", i);
}




int insertLast(headNode* h, int key) { // 리스트 마지막 부분에 노드 삽입

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL; // 오른쪽 노드 초기화
	node->llink = NULL; // 왼쪽 노드 초기화

	if (h->first == NULL) // 리스트가 비어있을 때
	{
		h->first = node; // 새로운 노드 설정
		return 0; // 종료
	}

	listNode* n = h->first;
	while(n->rlink != NULL) {
		n = n->rlink; // 비어있는 노드 탐색 = 마지막 노드 탐색
	}
	n->rlink = node;
	node->llink = n;
	return 0;
}



int deleteLast(headNode* h) { // 마지막 노드 삭제

	if (h->first == NULL) // 리스트가 비어있는 경우
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;
	
	if(n->rlink == NULL) { //리스트가 하나인 경우 첫번째 노드 삭제
		h->first = NULL;
		free(n);
		return 0;
	}

	while(n->rlink != NULL) { //마지막 노드 탐색
		trail = n;
		n = n->rlink; // 마지막 노드의 왼쪽 링크를 trail로 설정
	}

	trail->rlink = NULL; // trail 포인터의 오른쪽 링크를 null
	free(n);

	return 0;
}



int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 새로운 노드 동적 할당
	node->key = key;
	node->rlink = node->llink = NULL;

	if(h->first == NULL) // 리스트가 비어있는 경우
	{
		h->first = node; // 첫번째 노드 설정
		return 1;
	}

	node->rlink = h->first; //새로운 노드를 첫번째 노드로 설정, 기존의 첫번째 노드는 오른쪽 링크로 변경
	node->llink = NULL; // 왼쪽 링크를 마지막 노드로 설정

	listNode *p = h->first;
	p->llink = node;
	h->first = node;

	return 0;
}

int deleteFirst(headNode* h) { // 첫번째 노드 삭제

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first; // 두번째 노드를 첫번째 노드로 설정 후 기존의 첫번째 노드 삭제
	h->first = n->rlink;

	free(n);

	return 0;
}



int invertList(headNode* h) { // 첫번째 노드 앞에 새로운 삽입


	if(h->first == NULL) { // 리스트가 비어있는 경우
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first;
	listNode *trail = NULL;
	listNode *middle = NULL;

	while(n != NULL){ // 기존의 첫번째 노드를 오른쪽 링크로 이동, 새로운 첫번째 노드 설정
		trail = middle;
		middle = n;
		n = n->rlink;
		middle->rlink = trail;
		middle->llink = n;
	}

	h->first = middle;

	return 0;
}



int insertNode(headNode* h, int key) { // 리스트에 도스 추가

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL;

	if (h->first == NULL)
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;

	while(n != NULL) { // key값을 비교하여 적절한 위치에 노드 삽입
		if(n->key >= key) {
			if(n == h->first) {
				insertFirst(h, key);
			} else { 
				node->rlink = n;
				node->llink = n->llink;
				n->llink->rlink = node;
			}
			return 0;
		}

		n = n->rlink;
	}

	insertLast(h, key);
	return 0;
}

int deleteNode(headNode* h, int key) { // 특정 key의 노드 삭제

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* n = h->first;

	while(n != NULL) {
		if(n->key == key) {
			if(n == h->first) {
				deleteFirst(h);
			} else if (n->rlink == NULL){
				deleteLast(h);
			} else { 
				n->llink->rlink = n->rlink;
				n->rlink->llink = n->llink;
				free(n);
			}
			return 1;
		}

		n = n->rlink;
	}

	printf("cannot find the node for key = %d\n", key);
	return 1;
}