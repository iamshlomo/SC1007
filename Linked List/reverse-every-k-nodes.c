#include <stdio.h>
#include <stdlib.h>

struct _listNode
{
    int item;
    struct _listNode* next;
};
typedef struct _listNode ListNode;

void printList(ListNode *head);
void deleteList(ListNode **ptrHead);

void reverseKNodes(ListNode** head, int K);
int size = 0;

int main()
{
    ListNode *head = NULL, *temp;
    int i = 0;
    int K = 0;

    scanf("%d",&K);

    while (scanf("%d", &i))
    {
        if (head == NULL)
        {
            head = (ListNode*) malloc(sizeof(ListNode));
            temp = head;
        }
        else
        {
            temp->next = (ListNode*) malloc(sizeof(ListNode));
            temp = temp->next;
        }
        temp->item = i;
        size++;
    }
    temp->next = NULL;


    reverseKNodes(&head, K);
    printList(head);
    deleteList(&head);
    return 0;
}

void printList(ListNode *head)
{
    while(head !=NULL)
    {
        printf("%d ",head->item);
        head = head->next;
    }
    printf("\n");
}
void deleteList(ListNode **ptrHead)
{
    ListNode *cur = *ptrHead;
    ListNode *temp;
    while (cur!= NULL)
    {
        temp=cur->next;
        free(cur);
        cur=temp;
    }
    *ptrHead=NULL;
}

void reverseKNodes(ListNode** head, int K)
{
//Write your code here
    if(K<2 || *head == NULL || K>=size) return;

    ListNode *cur = *head, *headreal = *head, *tail = *head, *prev, *next, *nexthead, *finalhead = *head;
    int i = 1;
    int j = K;
    int t = (size/K);
    int count = 1;
    int finder = (size%K);
    int c = 1;

    if(finder!=0){
        finder = (size-finder);
        while(c<=finder){
            finalhead = finalhead->next;
            c++;
        }
    }

    while(i<K)
    {
        headreal = headreal->next; //finding the real head
        i++;
    }
//loop
    while(count<t)
    {
        nexthead = headreal;

        while(i<(K+j))
    {
        nexthead = nexthead->next;
        i++;
    }

    j=j+K;
      i = 0;
      next = cur->next;
      cur->next = nexthead;
      prev = cur;
      cur = next;
      i++;
      while(i<K)
    {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
        i++;
    }
    count++;
    }
   //end loop
   if(size%K==0){
   i = 0;
   next = cur->next;
   cur->next = NULL;
   prev = cur;
   cur = next;
   i++;
   while(i<K)
    {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
        i++;
    }
   }
   else{
    i = 0;
   next = cur->next;
   cur->next = finalhead;
   prev = cur;
   cur = next;
   i++;
   while(i<K)
    {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
        i++;
    }
   }
    *head = headreal;
}
