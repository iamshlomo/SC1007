#include <stdio.h>
#include <stdlib.h>

struct _listNode{
    int item;
    struct _listNode* next;
};
typedef struct _listNode ListNode;

typedef struct _linkedList{
    ListNode *head;
    int size;
}LinkedList;

void printList(LinkedList ll);
void deleteList(LinkedList* llptr);

LinkedList rearrange (LinkedList ll);

int main()
{
    LinkedList ll;

    ll.head = NULL;
    ll.size = 0;
    ListNode* temp;

	int i = 0;

	while (scanf("%d", &i)){
		if (ll.head == NULL){
			ll.head = (ListNode*) malloc(sizeof(ListNode));
			temp = ll.head;
		}
		else{
			temp->next = (ListNode*) malloc(sizeof(ListNode));
			temp = temp->next;
		}
		temp->item = i;
		ll.size++; //indicator of size
	}
	temp->next = NULL;

	ll=rearrange(ll);

	printList(ll);
    deleteList(&ll);
	return 0;
}

void printList(LinkedList ll){
    ListNode* temp = ll.head;

    while(temp !=NULL){
        printf("%d ",temp->item);
        temp = temp->next;
    }
    printf("\n");
}
void deleteList(LinkedList* llptr){
    ListNode *cur = llptr->head;
    ListNode *temp;
    while (cur!= NULL) {
		temp=cur->next;
		free(cur);
		cur=temp;
	}
	llptr->head=NULL;
	llptr->size =0;
}

LinkedList rearrange (LinkedList ll){
// Write your code here
ListNode *headreal, *head1 = NULL, *head2 = NULL, *tail1=NULL, *tail2=NULL, *cur, *prev, *center, *tail1next = NULL, *tail2next = NULL;

int i = ll.size;
int j = 0;

if(ll.head==NULL || ll.size==1) return ll;

head1 = ll.head;
center = ll.head;
tail1 = ll.head;
tail1next = ll.head;

while(j<i/2){
    prev=center;
    center = center->next;
    j++;
} //prev will be at 5, center will be at 6

headreal = center;
head2 = center;
cur = center;
tail2= center;
tail2next = center;

while(j<i-1){
    cur = cur->next;
    j++;
} //cur will be at 10

j = 0;
i = ll.size;

while(j<i/2){
    tail2next = tail2->next; // shift to 7
    tail2->next = tail1; // 6 to 1
    tail2 = tail2next; // tail2 move to 7

    tail1next = tail1->next; // shift to 2
    tail1->next = tail2; //1 to 7
    tail1 = tail1next; //tail1 move to 2

    j++;
}
ll.head = headreal;

//return ll;
// first segment

ListNode *headreal2, *head12 = NULL, *head22 = NULL, *tail12=NULL, *tail22=NULL, *cur2, *prev2, *center2, *tail1next2 = NULL, *tail2next2 = NULL;

i = ll.size;
j = 0;

head12 = ll.head;
center2 = ll.head;
tail12 = ll.head;
tail1next2 = ll.head;
headreal2 = ll.head;

while(j<i/2){
    prev2=center2;
    center2 = center2->next;
    j++;
} //prev will be at 5, center will be at 6

head22 = center2;
cur2 = center2;
tail22= center2;
tail2next2 = center2;

while(j<i-1){
    cur2 = cur2->next;
    j++;
} //cur will be at 10

j = 0;
i = ll.size;

while(j<i/2){

    tail1next2 = tail12->next; // shift to 2
    tail12->next = tail22; //1 to 7
    tail12 = tail1next2; //tail1 move to 2
if(j==(i/2-1))break;
    tail2next2 = tail22->next; // shift to 7
    tail22->next = tail12; // 6 to 1
    tail22 = tail2next2; // tail2 move to 7

    j++;
}
ll.head = headreal2;
return ll;
}
