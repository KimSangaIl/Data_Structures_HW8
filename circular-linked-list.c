/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	printf("[----- [Kim Sangil] [2019038041] -----]\n");

	char command;
	int key;
	listNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
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


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){

	if (h->rlink == h) {	//리스트에 헤드 노드만 있는 경우
		free(h);	//헤드 노드의 메모리를 해제
	}

	else {					//리스트에 헤드 노드 이외의 노드가 있는 경우
		listNode* temp = h->rlink;	//temp라는 노드 선언 및 헤드 노드의 오른쪽 링크, 즉 첫번째 노드로 초기화
		listNode* pre = NULL;		//pre라는 노드 선언 및 NULL로 초기화

		while (temp != h && temp != NULL) {	//temp노드가 헤드 노드와 NULL이 아니라면 반복
			pre = temp;			//pre노드를 temp노드로 초기화
			temp = temp->rlink;		//temp노드를 다음 노드로 이동
			free(pre);			//pre노드의 메모리를 해제
		}					//temp를 따라서 pre노드도 한 칸씩 이동하면서 모든 메모리를 해제
		free(h);				//헤드 노드의 메모리를 해제
	}

	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {

	listNode* new = (listNode*)malloc(sizeof(listNode));	//입력 받은 키 값을 저장할 new라는 노드에 메모리 할당
	new->key = key;		//new노드의 키 값을 입력 받은 키 값으로 초기화
	new->rlink = NULL;
	new->llink = NULL;	//new노드의 좌우 링크를 NULL로 초기화

	if (h == NULL) {	//헤더 노드가 NULL인 경우
		printf("Headnode is NULL!\n");	//오류 메시지 출력
	}

	else if (h->rlink == h) {	//리스트에 헤드 노드만 있는 경우
		h->rlink = new;		//헤드 노드의 오른쪽 링크를 new노드로 초기화
		h->llink = new;		//헤드 노드의 왼쪽 링크를 new노드로 초기화
		new->rlink = h;		//new노드의 오른쪽 링크를 헤드 노드로 초기화
		new->llink = h;		//new노드의 왼쪽 링크를 헤드 노드로 초기화
	}

	else {				//리스트에 헤드 노드 외의 다른 노드가 있는 경우
		new->llink = h->llink;	//new노드의 왼쪽 링크를 헤드 노드의 왼쪽 링크, 즉 마지막 노드로 초기화
		h->llink->rlink = new;	//헤드 노드의 왼쪽 링크의 오른쪽 링크, 즉 기존의 마지막 노드의 오른쪽 링크를 new노드로 초기화
		new->rlink = h;		//new노드의 오른쪽 링크를 헤드 노드로 초기화
		h->llink = new;		//헤드 노드의 왼쪽 링크를 new노드로 초기화
	}

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {

	if (h == NULL || h->rlink == h) {	//리스트가 공백이거나 헤드 노드 하나만 있는 경우
		printf("Nothing to delete!\n");	//오류 메시지 출력
	}

	else {
		listNode* temp = h->llink;	//temp라는 노드 선언 및 헤더 노드의 왼쪽 링크, 즉 마지막 노드로 초기화
		temp->llink->rlink = h;		//temp의 왼쪽 링크의 오른쪽 링크, 즉 마지막에서 두번째 노드의 오른쪽 링크를 헤드 노드로 초기화
		h->llink = temp->llink;		//헤드 노드의 왼쪽 링크를 temp의 왼쪽 링크로 초기화
		free(temp);			//마지막 노드인 temp노드의 메모리를 해제
	}

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {

	listNode* new = (listNode*)malloc(sizeof(listNode));	//입력 받은 키 값을 저장할 new라는 노드에 메모리 할당
	new->key = key;		//new노드의 키 값을 입력 받은 키 값으로 초기화
	new->rlink = NULL;
	new->llink = NULL;	//new노드의 좌우 링크를 NULL로 초기화

	if (h == NULL) {	//헤더 노드가 NULL인 경우
		printf("Headnode is NULL!\n");	//오류 메시지 출력
	}

	else if (h->rlink == h) {	//리스트에 헤드 노드만 있는 경우
		h->rlink = new;		//헤드 노드의 오른쪽 링크를 new노드로 초기화
		h->llink = new;		//헤드 노드의 왼쪽 링크를 new노드로 초기화
		new->rlink = h;		//new노드의 오른쪽 링크를 헤드 노드로 초기화
		new->llink = h;		//new노드의 왼쪽 링크를 헤드 노드로 초기화
	}

	else {				//리스트에 헤드 노드 외의 다른 노드가 있는 경우
		new->rlink = h->rlink;	//new노드의 오른쪽 링크를 헤드 노드의 오른쪽 링크, 즉 첫번째 노드로 초기화
		h->rlink->llink = new;	//헤드 노드의 오른쪽 링크의 왼쪽 링크, 즉 기존의 첫번째 노드의 왼쪽 링크를 new노드로 초기화
		new->llink = h;		//new노드의 왼쪽 링크를 헤드 노드로 초기화
		h->rlink = new;		//헤드 노드의 오른쪽 링크를 new노드로 초기화
	}

	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {

	if (h == NULL || h->rlink == h) {	//리스트가 공백이거나 헤드 노드 하나만 있는 경우
		printf("Nothing to delete!\n");	//오류 메시지 출력
	}

	else {
		listNode* temp = h->rlink;	//temp라는 노드 선언 및 헤더 노드의 오른쪽쪽 링크, 즉 첫번째 노드로 초기화
		temp->rlink->llink = h;		//temp노드의 오른쪽 링크의 왼쪽 링크, 즉 두번째 노드의 왼쪽 링크를 헤드 노드로 초기화
		h->rlink = temp->rlink;		//헤드 노드의 오른쪽 링크를 temp노드의 오른쪽 링크, 즉 두번째 노드로 초기화
		free(temp);			//temp노드의 메모리를 해제
	}

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {

	if (h == NULL || h->rlink == h) {	//리스트가 공백이거나 헤드 노드 하나만 있는 경우
		printf("Nothing to invert!\n");	//오류 메시지 출력
	}

	else {
		listNode* a = h->rlink;	//a라는 노드 선언 및 헤드 노드의 오른쪽 링크, 즉 첫번째 노드로 초기화
		listNode* b = h;		
		listNode* c = h;	//b, c라는 노드 선언 및 헤드 노드로 초기화

		h->llink = h->rlink;	//헤드 노드의 왼쪽 링크를 첫번째 노드로 초기화

		while (a != h && a != NULL) {	//a노드가 헤드 노드와 NULL이 아니라면 반복
			c = b;			//c노드를 b노드로 초기화
			b = a;			//b노드를 a노드로 초기화
			a = a->rlink;	//a노드를 다음 노드로 이동
			b->rlink = c;	//b노드의 오른쪽 링크를 b노드의 이전 노드인 c노드로 초기화
			b->llink = a;	//b노드의 왼쪽 링크를 b노드의 다음 노드인 a노드로 초기화
		}

		h->rlink = b;		//반복문 종료 후 마지막 노드는 b노드이고, 헤드 노드의 오른쪽 링크를 b노드로 초기화
	}

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {

	if (h == NULL) {			//헤더 노드가 NULL인 경우
		printf("Headnode is NULL!\n");	//오류 메시지 출력
	}

	else if (h->rlink == h) {	//리스트에 헤드 노드만 있는 경우
		insertFirst(h, key);	//함수를 호출해 리스트의 맨 앞에 노드를 삽입
	}

	else {
		listNode* new = (listNode*)malloc(sizeof(listNode));	//입력 받은 키 값을 저장할 new라는 노드에 메모리 할당
		new->key = key;			//new노드의 키 값을 입력 받은 키 값으로 초기화
		new->rlink = NULL;
		new->llink = NULL;		//new노드의 좌우 링크를 NULL로 초기화
		listNode* temp = h->rlink;	//temp라는 노드 선언 및 헤드 노드의 오른쪽 링크, 즉 첫번째 노드로 초기화

		while (temp != h && temp != NULL) {		//temp노드가 헤드 노드와 NULL이 아니라면 반복
			if (temp->key > key) {			//입력 받은 키 값보다 큰 값을 가진 노드를 찾은 경우
				if (temp == h->rlink) {		//찾은 노드가 첫번재 노드인 경우
					insertFirst(h, key);	//함수를 호출해 리스트의 맨 앞에 노드를 삽입
				}
				else {					//찾은 노드가 첫번째 노드가 아닌 경우
					new->rlink = temp;		//new노드의 오른쪽 링크를 찾은 노드로 초기화
					new->llink = temp->llink;	//new노드의 왼쪽 링크를 찾은 노드의 왼쪽 링크로 초기화
					temp->llink->rlink = new;	//찾은 노드의 이전 노드의 오른쪽 링크를 new노드로 초기화
					temp->llink = new;		//찾은 노드의 왼쪽 링크를 new노드로 초기화
				}
				return 0;	//노드를 삽입했다면 함수 종료
			}
			temp = temp->rlink;	//temp노드를 다음 노드로 이동
		}
		insertLast(h, key);		//입력받은 키 값보다 큰 값을 가지는 노드를 찾지 못했다면 함수를 호출해 리스트의 마지막에 노드를 삽입
	}

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {

	if (h == NULL || h->rlink == h) {	//리스트가 공백이거나 헤드 노드 하나만 있는 경우
		printf("Nothing to delete!\n");	//오류 메시지 출력
	}

	else {
		listNode* temp = h->rlink;	//temp라는 노드 선언 및 헤드 노드의 오른쪽 링크, 즉 첫번째 노드로 초기화

		while (temp != h && temp != NULL) {		//temp노드가 헤드 노드와 NULL이 아니라면 반복
			if (temp->key == key) {			//입력 받은 키 값을 가진 노드를 찾은 경우
				if (temp == h->rlink) {		//찾은 노드가 첫번재 노드인 경우
					deleteFirst(h);		//함수를 호출해 리스트의 맨 앞에 노드를 삭제
				}
				else if (temp->rlink == h) {	//찾은 노드가 마지막 노드인 경우
					deleteLast(h);		//함수를 호출해 리스트의 마지막 노드를 삭제
				}
				else {						//찾은 노드가 첫번째 노드가 아닌 경우
					temp->llink->rlink = temp->rlink;	//찾은 노드 이전 노드의 오른쪽 링크를 찾은 노드의 다음 노드로 초기화
					temp->rlink->llink = temp->llink;	//찾은 노드 다음 노드의 왼쪽 링크를 찾은 노드의 이전 노드로 초기화
					free(temp);				//temp노드의 메모리를 해제
				}
				return 0;	//노드를 삭제했다면 함수 종료
			}
			temp = temp->rlink;	//temp노드를 다음 노드로 이동
		}
		printf("cannot find the node for key = %d\n", key);	//입력받은 키 값을 가지는 노드를 찾지 못했다면 오류 메시지 출력
	}

	return 0;
}


