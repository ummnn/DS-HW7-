#include<stdio.h>
#include<stdlib.h>

typedef struct Node { //����ü�� Node
	int key;
	struct Node* llink; //Node�� ������ llink
	struct Node* rlink; //Node�� ������ rlink
} listNode; //����ü ��Ī listNode



typedef struct Head { //����ü�� Head
	struct Node* first; //Node�� ������ first
}headNode; //����ü ��Ī  HeadNode

/* �Լ� ����Ʈ */

/* note: initialize�� ���������͸� �Ű������� ����
         lab3�� initialize�� �������� ���� �Ұ� */
int initialize(headNode** h);

/* note: freeList�� �̱������͸� �Ű������� ����
        - initialize�� �� �ٸ��� ���� �Ұ�
         - ���������͸� �Ű������� �޾Ƶ� ������ �� ���� �� */
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
    printf("[----- [�̵���] [2019038027] -----]");

	char command;
	int key;
	headNode* headnode=NULL; //headnode NULL�� �ʱ�ȭ

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
		scanf(" %c", &command); //command�� �Է¹޴´�

		switch(command) {
		case 'z': case 'Z': //commande�� z�� Z�� ��
			initialize(&headnode); //initialize�Լ� ���� 
			break;
		case 'p': case 'P': //command�� p�� P�� ��
			printList(headnode); //printlist �Լ� ����
			break;
		case 'i': case 'I': //command�� i�� I�� ��
			printf("Your Key = ");
			scanf("%d", &key); //key�� �Է¹޴´�
			insertNode(headnode, key); //insertNode�Լ� ����
			break;
		case 'd': case 'D': //command�� d�� D�� ��
			printf("Your Key = ");
			scanf("%d", &key); //key�� �Է¹޴´�
			deleteNode(headnode, key); //deleteNode�Լ� ����
			break;
		case 'n': case 'N': //command�� n�̳� N�� ��
			printf("Your Key = "); 
			scanf("%d", &key); //key�� �Է¹޴´�
			insertLast(headnode, key); //insertNode�Լ� ����
			break;
		case 'e': case 'E': //command�� e�� E�� ��
			deleteLast(headnode); //deleteNode�Լ� ����
			break;
		case 'f': case 'F': //command�� f�� F�� ��
			printf("Your Key = ");
			scanf("%d", &key); //key�� �Է¹޴´�
			insertFirst(headnode, key);
			break;
		case 't': case 'T': //command�� t�� T�� ��
			deleteFirst(headnode); //deleteFirst�Լ� ����
			break;
		case 'r': case 'R': //command�� r�̳� R�� ��
			invertList(headnode); //invertList�Լ� ����
			break;
		case 'q': case 'Q': //command�� q�� Q�� ��
			freeList(headnode); //freeList�Լ� ����
			break;
		default: //�ٸ� ���� �Էµ��� ��
			printf("\n       >>>>>   Concentration!!   <<<<<     \n"); //concentration �޽��� ���
			break;
		}

	}while(command != 'q' && command != 'Q'); //command�� q�� Q�� �� ���� �ݺ�

	return 1;
}


int initialize(headNode** h) {

	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(*h != NULL)
		freeList(*h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (headNode*)malloc(sizeof(headNode)); //headNode�� ũ�⸸ŭ �޸� �Ҵ�
	(*h)->first = NULL; //h�� first NULL�� �ʱ�ȭ
	return 1;
}

int freeList(headNode* h){
	/* h�� ����� listNode �޸� ����
	 * headNode�� �����Ǿ�� ��.
	 */
	listNode* p = h->first; //p�� h�� first ����

	listNode* prev = NULL; //prev NULL�� �ʱ�ȭ
	while(p != NULL) { //p�� NULL�� ������ �ݺ�
		prev = p; //prev�� p ����
		p = p->rlink; //p�� p�� rlink����
		free(prev); //prev �޸� ����
	}
	free(h); //h �޸� ����
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p; //listNode�� ������ p ����

	printf("\n---PRINT\n");

	if(h == NULL) { //h�� NULL�̶��
		printf("Nothing to print....\n"); //����ٴ� �޽��� ���
		return;
	}

	p = h->first; //p�� h�� first ����

	while(p != NULL) { //p�� NULL�� �� ���� �ݺ�
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink; //p�� p�� rlink ����
		i++; //i 1����
	}

	printf("  items = %d\n", i);
}




/*
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode�� ũ�⸸ŭ �޸� �Ҵ�
	node->key = key; //node�� key�� key����
	node->rlink = NULL; //rlink �ʱ�ȭ
	node->llink = NULL; //llink �ʱ�ȭ

	if (h->first == NULL) //h�� first�� NULL�̶��
	{
		h->first = node; //h�� first�� node ����
		return 0;
	}

	listNode* n = h->first; //n�� h�� first ����
	while(n->rlink != NULL) { //n�� rlinkrk NULL�� �� ���� �ݺ�
		n = n->rlink; //n�� n�� rlink ����
	}
	n->rlink = node; //n�� rlink�� node ����
	node->llink = n; //node�� link�� n ����
	return 0;
}



/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {

	if (h->first == NULL) //h�� first�� NULL�̶��
	{
 		printf("nothing to delete.\n"); //����ٴ� �޽��� ���
		return 0;
	}

	listNode* n = h->first; ///
	listNode* trail = NULL;

	/* ��尡 �ϳ��� �ִ� ���, �� first node == last node��  ��� ó�� */
	if(n->rlink == NULL) { //n�� rlink�� NULL�̶��
		h->first = NULL; //h�� first NULL�� �ʱ�ȭ
		free(n); //n�޸� �Ҵ� ����
		return 0;
	}

	/* ������ ������ �̵� */
	while(n->rlink != NULL) { //n�� rlink�� NULL�ϋ����� �ݺ�
		trail = n; //trail�� n ����
		n = n->rlink; //n�� n�� rlink����
	}

	/* n�� �����ǹǷ�, ���� ����� ��ũ NULL ó�� */
	trail->rlink = NULL; //trail�� rlink NULL�� �ʱ�ȭ
	free(n); //n �޸� �Ҵ� ����

	return 0;
}



/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode�� ũ�⸸ŭ �޸� �Ҵ�
	node->key = key; //node�� key�� key ����
	node->rlink = node->llink = NULL; //node�� rlink, llink NULL�� �ʱ�ȭ

	if(h->first == NULL) //h�� first�� NULL�̶��
	{
		h->first = node; //h�� first�� node ����
		return 1;
	}

	node->rlink = h->first; //node�� rlink�� h�� first����
	node->llink = NULL; //node�� llink�� NULL����

	listNode *p = h->first; //p�� h�� first����
	p->llink = node; //p�� link�� node ����
	h->first = node;  //h�� first�� node ����

	return 0;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL) //h�� first�� NULL�̶��
	{
		printf("nothing to delete.\n"); //����ٴ� �޽��� ���
		return 0;
	}
	listNode* n = h->first; //n��  h�� first����
	h->first = n->rlink; //h�� first�� n�� rlink����

	free(n); //n �޸� �Ҵ� ����

	return 0;
}



/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {


	if(h->first == NULL) { //h�� first�� NULL�̶��
		printf("nothing to invert...\n"); //����ٴ� �޽��� ���
		return 0;
	}
	listNode *n = h->first; //n�� h�� first����
	listNode *trail = NULL; //trail NULL�� �ʱ�ȭ
	listNode *middle = NULL; //middle NULL�� �ʱ�ȭ

	while(n != NULL){ //n�� NULL�� �ƴ϶�� �ݺ�
		trail = middle; //trail�� middle ����
		middle = n; //middle�� n ����
		n = n->rlink; //n�� n�� rlink ����
		middle->rlink = trail; //middle�� rlink�� trail ����
		middle->llink = n; //middle�� llink�� n ����
	}

	h->first = middle; //h�� first�� middle ����

	return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode�� ũ�⸸ŭ �޸� �Ҵ�
	node->key = key; //node�� key�� key ����
	node->llink = node->rlink = NULL; //node�� llink, rlink NULL�� �ʱ�ȭ

	if (h->first == NULL) //h�� first�� NULL�̶��
	{
		h->first = node; //h�� first�� node ����
		return 0;
	}

	listNode* n = h->first; //n�� h�� first����

	/* key�� �������� ������ ��ġ�� ã�´� */
	while(n != NULL) { //n�� NULL�� �ƴ϶�� �ݺ�
		if(n->key >= key) { //n�� key�� key���� ũ�ų� ���ٸ�
			/* ù ��� ���ʿ� �����ؾ��� ��� ���� �˻� */
			if(n == h->first) { //n�� h�� first�� ���ٸ�
				insertFirst(h, key); //insertFirst�Լ� ����
			} else { /* �߰��̰ų� �������� ��� */
				node->rlink = n; //node�� rlink�� n ����
				node->llink = n->llink; //node�� llink�� n�� llink ����
				n->llink->rlink = node; //n�� link�� rlink�� node ����
			}
			return 0;
		}

		n = n->rlink; //n�� n�� rlink ����
	}

	/* ������ ������ ã�� ���� ���, �������� ���� */
	insertLast(h, key); //insertLast�Լ� ����
	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL) //h�� first�� NULL�̶��
	{
		printf("nothing to delete.\n"); //����ٴ� �޽��� ���
		return 1;
	}

	listNode* n = h->first; //n�� h�� first ����

	while(n != NULL) { //n�� NULL�� �ƴ϶�� �ݺ�
		if(n->key == key) { //n�� key�� key�� ���ٸ�
			if(n == h->first) { /* ù ���° ��� �ΰ�� */
				deleteFirst(h); //deleteFirst�Լ� ����
			} else if (n->rlink == NULL){ /* ������ ����� ��� */
				deleteLast(h); //deleteLast�Լ� ����
			} else { /* �߰��� ��� */
				n->llink->rlink = n->rlink; //n�� llink�� rlink�� n�� rlink ����
				n->rlink->llink = n->llink; //n�� rlink�� llink�� n�� llink ����
				free(n); //n �޸� �Ҵ� ����
			}
			return 1;
		}

		n = n->rlink; //n�� n�� rlink ����
	}

	/* ã�� �� �Ѱ�� */
	printf("cannot find the node for key = %d\n", key); //ã�� �� ���ٴ� �޽��� ���
	return 1;
}


