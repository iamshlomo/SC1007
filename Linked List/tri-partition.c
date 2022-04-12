#include <stdio.h>
#include <stdlib.h>

struct _listNode{
    int item;
    struct _listNode* next;
};
typedef struct _listNode ListNode;

void printList(ListNode *head);
void deleteList(ListNode **ptrHead);

void triPartition(ListNode** head, int pivot);

int main()
{
    ListNode *head = NULL, *temp;
	int i = 0;
	int pivot = 0;

	scanf("%d",&pivot);

	while (scanf("%d", &i)){
		if (head == NULL){
			head = (ListNode*) malloc(sizeof(ListNode));
			temp = head;
		}
		else{
			temp->next = (ListNode*) malloc(sizeof(ListNode));
			temp = temp->next;
		}
		temp->item = i;
	}
	temp->next = NULL;


	triPartition(&head, pivot);
	printList(head);
	deleteList(&head);

	return 0;
}

void printList(ListNode *head){
    while(head !=NULL){
        printf("%d ",head->item);
        head = head->next;
    }
    printf("\n");
}

void deleteList(ListNode **ptrHead){
    ListNode *cur = *ptrHead;
    ListNode *temp;
    while (cur!= NULL) {
		temp=cur->next;
		free(cur);
		cur=temp;
	}
	*ptrHead=NULL;
}

void triPartition(ListNode** head, int pivot){ //received address to head

// Write your code here
ListNode *less, *same, *more, *temp;
ListNode **lessP = &less;
ListNode **sameP = &same;
ListNode **moreP = &more;

ListNode *cur = *head;

while(cur!=NULL){
	temp = cur;
	cur = cur->next;
	temp->next = NULL;

	if(temp->item < pivot){
		*lessP = temp;
		lessP = &(*lessP)->next;
	}
	else if(temp->item > pivot){
		*moreP = temp;
		moreP = &(*moreP)->next;
	}
	else if(temp->item == pivot){
		*sameP = temp;
		sameP = &(*sameP)->next;
	}
}
*sameP = more;
*lessP = same;
*head = less;
}
