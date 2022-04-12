#include <stdio.h>
#include <stdlib.h>

struct _listNode{
    float item;
    struct _listNode* next;
};
typedef struct _listNode ListNode;

void printList(ListNode *head);
void deleteList(ListNode **ptrHead);

int size = 0;

ListNode *reverseSegment(ListNode* head, int start, int end); //task at hand
// start and end indicate the range of numbers which order will be reversed

int main()
{
    ListNode *head = NULL, *temp;
	float f = 0.0;
	int S, E;

	scanf("%d %d",&S, &E); //start and end defined here

	while (scanf("%f", &f)){ //input of values to form list
		if (head == NULL){
			head = (ListNode*) malloc(sizeof(ListNode));
			temp = head;
		}
		else{
			temp->next = (ListNode*) malloc(sizeof(ListNode));
			temp = temp->next;
		}
		temp->item = f;
		size++;
	}
	temp->next = NULL;
	if(size == 0) return;
	else if(size==1){
		printList(head);
		deleteList(&head);
	}

	else{
		head = reverseSegment(head,S,E);
		printList(head);
		deleteList(&head);
	}

	return 0;

}

void printList(ListNode *head){
    while(head !=NULL){
        printf("%.2f ",head->item);
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

ListNode *reverseSegment(ListNode* head, int start, int end)
{
// Write your code here
	int num = (end-start);
	if(head == NULL || start<0 || end<0 || start>=end || end>=size || start>=size) return head;
    else if( num ==1){
        int i = 0;
		ListNode *cur = head;
		ListNode *tempLast, *tempPoint, *temp, *tempPrev, *prev, *prev1, *next;

		while (i< start){
			prev = cur; // prev will be the start point of the reversing after the while loop
			tempLast = cur->next;
			cur = tempLast; // tempLast will be the last point of the reversing, needs to connect to the un-reversed
			i++;
		}

    	    temp = cur->next; //temp->next will be pointing to the untouched 1.7 at the end of while loop
        	cur = temp;

        prev->next = temp;
        tempLast->next = temp->next;
        temp->next = tempLast;


		return head;
    }

	else if(start==0 && end<size-1){
        int i = 0;
        ListNode *cur = head;
        ListNode *temp, *next1, *next, *prev;
        temp = head;


        while(i<end){
            next1 = cur->next; //next1 will be 1.3
            cur = next1;
            i++;
        }

        int j = 0;
        cur = head;
        next = cur->next;
        cur->next = next1->next;
        prev = cur;
        cur = next;
        j++;

        while(j<=end){
            next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
            j++;
        }
        return prev;
    }
	else if(start>0 && end<size-1){
		int i = 0;
		ListNode *cur = head;
		ListNode *tempLast, *tempPoint, *temp, *tempPrev, *prev, *prev1, *next;

		while (i< start){
			prev = cur; // prev will be the start point of the reversing after the while loop
			tempLast = cur->next;
			cur = tempLast; // tempLast will be the last point of the reversing, needs to connect to the un-reversed
			i++;
		}

		while (i< end-1){
    	    temp = cur->next; //temp->next will be pointing to the untouched 1.7 at the end of while loop
        	cur = temp;
        	i++;
		}
		prev->next = temp->next;

		int j = start;

		cur = tempLast;
		next = cur->next;
		cur->next = temp->next->next;
		prev1 = cur;
		cur = next;
		j++;

		while(j<=end){
        	next = cur->next;
			cur->next = prev1;
			prev1 = cur;
			cur = next;
			j++;
		}
		return head;
    }
	else if(start>0 && end==size-1){
		int i = 0;
		ListNode *cur = head;
		ListNode *temp, *prev, *prev1, *next;

		while(i<start){
			prev = cur; //prev @ 1.2 eventually
			next = cur->next;
			cur = next;
			i++;
		}

		next = cur->next;
		cur->next=NULL;
		prev1 = cur;
		cur = next;
		i++;
		while(i<=end){
			next = cur->next;
			cur->next = prev1;
			prev1 = cur;
			cur = next;
			i++;
		}
		prev->next = prev1;
		return head;
	}
	else if(start==0 && end==size-1){
		int i = 0;
		int j = 0;
		ListNode *cur = head;
		ListNode *temp, *prev, *prev1, *next;

		temp = head;
		while(j<end){
			next = temp->next;
			temp = next;
			j++;
		}

		next = cur->next;
		cur->next = NULL;
		prev = cur;
		cur = next;
		i++;

		while(i<=end){
			next = cur->next;
			cur->next = prev;
			prev = cur;
			cur = next;
			i++;
		}
		return temp;
	}
}
