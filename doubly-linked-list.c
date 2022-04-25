#include<stdio.h>
#include<stdlib.h>

typedef struct Node { //구조체형 Node
	int key;
	struct Node* llink; //Node형 포인터 llink
	struct Node* rlink; //Node형 포인터 rlink
} listNode; //구조체 별칭 listNode



typedef struct Head { //구조체형 Head
	struct Node* first; //Node형 포인터 first
}headNode; //구조체 별칭  HeadNode

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         lab3의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
         - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
    printf("[----- [이동현] [2019038027] -----]");

	char command;
	int key;
	headNode* headnode=NULL; //headnode NULL로 초기화

	do{
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
		scanf(" %c", &command); //command를 입력받는다

		switch(command) {
		case 'z': case 'Z': //commande가 z나 Z일 때
			initialize(&headnode); //initialize함수 실행 
			break;
		case 'p': case 'P': //command가 p나 P일 때
			printList(headnode); //printlist 함수 실행
			break;
		case 'i': case 'I': //command가 i나 I일 떄
			printf("Your Key = ");
			scanf("%d", &key); //key를 입력받는다
			insertNode(headnode, key); //insertNode함수 실행
			break;
		case 'd': case 'D': //command가 d나 D일 때
			printf("Your Key = ");
			scanf("%d", &key); //key를 입력받는다
			deleteNode(headnode, key); //deleteNode함수 실행
			break;
		case 'n': case 'N': //command가 n이나 N일 때
			printf("Your Key = "); 
			scanf("%d", &key); //key를 입력받는다
			insertLast(headnode, key); //insertNode함수 실행
			break;
		case 'e': case 'E': //command가 e나 E일 때
			deleteLast(headnode); //deleteNode함수 실행
			break;
		case 'f': case 'F': //command가 f나 F일 때
			printf("Your Key = ");
			scanf("%d", &key); //key를 입력받는다
			insertFirst(headnode, key);
			break;
		case 't': case 'T': //command가 t나 T일 때
			deleteFirst(headnode); //deleteFirst함수 실행
			break;
		case 'r': case 'R': //command가 r이나 R일 때
			invertList(headnode); //invertList함수 실행
			break;
		case 'q': case 'Q': //command가 q나 Q일 때
			freeList(headnode); //freeList함수 실행
			break;
		default: //다른 값이 입력됐을 때
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //concentration 메시지 출력
			break;
		}

	}while(command != 'q' && command != 'Q'); //command가 q나 Q일 때 까지 반복

	return 1;
}


int initialize(headNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (headNode*)malloc(sizeof(headNode)); //headNode의 크기만큼 메모리 할당
	(*h)->first = NULL; //h의 first NULL로 초기화
	return 1;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first; //p에 h의 first 저장

	listNode* prev = NULL; //prev NULL로 초기화
	while(p != NULL) { //p가 NULL일 때까지 반복
		prev = p; //prev에 p 저장
		p = p->rlink; //p에 p의 rlink저장
		free(prev); //prev 메모리 해제
	}
	free(h); //h 메모리 해제
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p; //listNode형 포인터 p 선언

	printf("\n---PRINT\n");

	if(h == NULL) { //h가 NULL이라면
		printf("Nothing to print....\n"); //비었다는 메시지 출력
		return;
	}

	p = h->first; //p에 h의 first 저장

	while(p != NULL) { //p가 NULL일 때 까지 반복
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink; //p에 p의 rlink 저장
		i++; //i 1증가
	}

	printf("  items = %d\n", i);
}




/*
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode의 크기만큼 메모리 할당
	node->key = key; //node의 key에 key저장
	node->rlink = NULL; //rlink 초기화
	node->llink = NULL; //llink 초기화

	if (h->first == NULL) //h의 first가 NULL이라면
	{
		h->first = node; //h의 first에 node 저장
		return 0;
	}

	listNode* n = h->first; //n에 h의 first 저장
	while(n->rlink != NULL) { //n의 rlinkrk NULL일 떄 까지 반복
		n = n->rlink; //n에 n의 rlink 저장
	}
	n->rlink = node; //n의 rlink에 node 저장
	node->llink = n; //node의 link에 n 저장
	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	if (h->first == NULL) //h의 first가 NULL이라면
	{
 		printf("nothing to delete.\n"); //비었다는 메시지 출력
		return 0;
	}

	listNode* n = h->first; ///
	listNode* trail = NULL;

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->rlink == NULL) { //n의 rlink가 NULL이라면
		h->first = NULL; //h의 first NULL로 초기화
		free(n); //n메모리 할당 해제
		return 0;
	}

	/* 마지막 노드까지 이동 */
	while(n->rlink != NULL) { //n의 rlink가 NULL일떄까지 반복
		trail = n; //trail에 n 저장
		n = n->rlink; //n에 n의 rlink저장
	}

	/* n이 삭제되므로, 이전 노드의 링크 NULL 처리 */
	trail->rlink = NULL; //trail의 rlink NULL로 초기화
	free(n); //n 메모리 할당 해제

	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode의 크기만큼 메모리 할당
	node->key = key; //node의 key에 key 저장
	node->rlink = node->llink = NULL; //node의 rlink, llink NULL로 초기화

	if(h->first == NULL) //h의 first가 NULL이라면
	{
		h->first = node; //h의 first에 node 저장
		return 1;
	}

	node->rlink = h->first; //node의 rlink에 h의 first저장
	node->llink = NULL; //node의 llink에 NULL저장

	listNode *p = h->first; //p에 h의 first저장
	p->llink = node; //p의 link에 node 저장
	h->first = node;  //h의 first에 node 저장

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL) //h의 first가 NULL이라면
	{
		printf("nothing to delete.\n"); //비었다는 메시지 출력
		return 0;
	}
	listNode* n = h->first; //n에  h의 first저장
	h->first = n->rlink; //h의 first에 n의 rlink저장

	free(n); //n 메모리 할당 해제

	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {


	if(h->first == NULL) { //h의 first가 NULL이라면
		printf("nothing to invert...\n"); //비었다는 메시지 출력
		return 0;
	}
	listNode *n = h->first; //n에 h의 first저장
	listNode *trail = NULL; //trail NULL로 초기화
	listNode *middle = NULL; //middle NULL로 초기화

	while(n != NULL){ //n이 NULL이 아니라면 반복
		trail = middle; //trail에 middle 저장
		middle = n; //middle에 n 저장
		n = n->rlink; //n에 n의 rlink 저장
		middle->rlink = trail; //middle의 rlink에 trail 저장
		middle->llink = n; //middle의 llink에 n 저장
	}

	h->first = middle; //h의 first에 middle 저장

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode의 크기만큼 메모리 할당
	node->key = key; //node의 key에 key 저장
	node->llink = node->rlink = NULL; //node의 llink, rlink NULL로 초기화

	if (h->first == NULL) //h의 first가 NULL이라면
	{
		h->first = node; //h의 first에 node 저장
		return 0;
	}

	listNode* n = h->first; //n에 h의 first저장

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) { //n이 NULL이 아니라면 반복
		if(n->key >= key) { //n의 key가 key보다 크거나 같다면
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) { //n이 h의 first와 같다면
				insertFirst(h, key); //insertFirst함수 실행
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n; //node의 rlink에 n 저장
				node->llink = n->llink; //node의 llink에 n의 llink 저장
				n->llink->rlink = node; //n의 link의 rlink에 node 저장
			}
			return 0;
		}

		n = n->rlink; //n에 n의 rlink 저장
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key); //insertLast함수 실행
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL) //h의 first가 NULL이라면
	{
		printf("nothing to delete.\n"); //비었다는 메시지 출력
		return 1;
	}

	listNode* n = h->first; //n에 h의 first 저장

	while(n != NULL) { //n이 NULL이 아니라면 반복
		if(n->key == key) { //n의 key와 key가 같다면
			if(n == h->first) { /* 첫 노드째 노드 인경우 */
				deleteFirst(h); //deleteFirst함수 실행
			} else if (n->rlink == NULL){ /* 마지막 노드인 경우 */
				deleteLast(h); //deleteLast함수 실행
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink; //n의 llink의 rlink에 n의 rlink 저장
				n->rlink->llink = n->llink; //n의 rlink의 llink에 n의 llink 저장
				free(n); //n 메모리 할당 해제
			}
			return 1;
		}

		n = n->rlink; //n에 n의 rlink 저장
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key); //찾을 수 없다는 메시지 출력
	return 1;
}


