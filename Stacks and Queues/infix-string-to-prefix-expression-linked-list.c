#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000 //The size of the array

enum ExpType {OPT,OPERAND};

typedef struct _stackNode{
    char item;
    struct _stackNode *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

void push(Stack *sPtr, char item);
int pop(Stack *sPtr);
char peek(Stack s);
int isEmptyStack(Stack s);

typedef struct _listnode
{
    int  item;
    enum ExpType type;
	struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
   int size;
   ListNode *head;
} LinkedList;

void insertNode(LinkedList *llPtr, int item,enum ExpType type);
int deleteNode(LinkedList *llPtr);
void removeAllNodes(LinkedList *llPtr);
int isEmptyLinkedList (LinkedList ll);


void in2PreLL(char* infix, LinkedList *inExpLL);

void printExpLL(LinkedList inExp);

int main()
{
    char infix[SIZE];

    //printf("Enter an infix expression:\n");
    scanf("%[^\n]%*c",infix);

    LinkedList inExpLL;
    inExpLL.head = NULL;
    inExpLL.size = 0;

    in2PreLL(infix, &inExpLL);

    printExpLL(inExpLL);

    removeAllNodes(&inExpLL);
    return 0;
}

void printExpLL(LinkedList inExpLL)
{
    ListNode* temp = NULL;
    temp = inExpLL.head;
    while(temp!= NULL){
        if(temp->type == OPERAND)
            printf(" %d ",temp->item);
        else
            printf(" %c ",(char)(temp->item));
        temp = temp->next;
    }
    printf("\n");
}

void insertNode(LinkedList *LLPtr, int item, enum ExpType type) {
    ListNode *newNode;
    newNode = malloc(sizeof(ListNode));
    if(newNode==NULL) exit(0);

    newNode->item = item;
    newNode->type = type;
    newNode->next = LLPtr->head;
    LLPtr->head=newNode;
    LLPtr->size++;
}

int deleteNode(LinkedList *LLPtr) {
    if(LLPtr==NULL || LLPtr->size==0){
        return 0;
    }
    else{
       ListNode *temp = LLPtr->head;
       LLPtr->head = LLPtr->head->next;

       free(temp);
       LLPtr->size--;
       return 1;
    }
}

int isEmptyLinkedList (LinkedList ll) {
    if(ll.size==0) return 1;
    else return 0;
}

void removeAllNodes(LinkedList *LLPtr)
{
	while(deleteNode(LLPtr));
}

void push(Stack *sPtr, char item){
    StackNode *newNode;
    newNode = malloc(sizeof(StackNode));
    newNode->item = item;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr){
    if(sPtr == NULL || sPtr->head == NULL){
        return 0;
    }
    else{
       StackNode *temp = sPtr->head;
       sPtr->head = sPtr->head->next;
       free(temp);
       sPtr->size--;
       return 1;
    }
}

char peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}


void in2PreLL(char* infix, LinkedList *inExpLL)
{
  //Write your code here
  char inFix[SIZE];
   Stack s;
   s.head = NULL;
   s.size = 0;
   int a = 0;
   int b = 0;
int precedence(char);
   while(a<strlen(infix)){
       if(infix[a] != '+' && infix[a] != '-' && infix[a] != '*' && infix[a] != '/' && infix[a] != '(' && infix[a] != ')'){
          inFix[b] = infix[a];
          b++;
      }
      else{
          inFix[b] = ' ';
          b++;
          inFix[b] = infix[a];
          b++;
          inFix[b] = ' ';
          b++;
      }
      a++;
   }
   inFix[b] = '\0';

   char revInfix[SIZE];
   char revPrefix[SIZE];
   int i=0;
   int j = 0;
   char c;
   int count =0;

   //reverse the string
   while(inFix[count]!='\0')count++;
   for(i=count-1;i>=0;i--)
    revInfix[count-1-i] = inFix[i];
   revInfix[count]='\0';

   i=0;
   while(i<SIZE && revInfix[i]!='\0')
    {
        c = revInfix[i++];
        switch(c)
        {
        case '*': //operators
        case '/':
        case '+':
        case '-':
            while(isEmptyStack(s)==0 && peek(s) != ')' && precedence(peek(s)) > precedence(c) ) //note the precedence comparison
            {
                revPrefix[j++] = peek(s);
                pop(&s);
            }
            push(&s,c);
            break;
        case ')':            
            if(revInfix[i]=='('){
                revPrefix[j++] = '*';
            }
            push(&s,c);
            break;
        case '(':


            while(isEmptyStack(s)==0)
            {
                if(peek(s)!=')')
                {
                    revPrefix[j++]=peek(s);
                    pop(&s);
                }
                else
                {
                    pop(&s);
                    break;
                }
            }
            break;
        default: //operand
            revPrefix[j++] = c;
        }
    }

    while(isEmptyStack(s)==0)
    {
        revPrefix[j++] = peek(s);
        pop(&s);
    }
    revPrefix[j] = '\0';

   //reverse the string
  count=0;
  char prefix[strlen(infix)];

  while(revPrefix[count]!='\0')count++;
    for(i=count-1;i>=0;i--)
    {
        prefix[count-1-i] = revPrefix[i];
    }
    prefix[count]='\0';

i = count-1;
int y;
    while(i>=0){
        if(prefix[i] == '/' || prefix[i] == '*' || prefix[i] == '+' || prefix[i] == '-' )
        {
            insertNode(inExpLL, (int)prefix[i], 0);
            i--;
        }
    
    else if(prefix[i] == '1' || prefix[i] == '2' || prefix[i] == '3' || prefix[i] == '4' || prefix[i] == '5' || prefix[i] == '6' || prefix[i] == '7' || prefix[i] == '8' || prefix[i] == '9' || prefix[i] == '0' ){ 
        
        y = (int)prefix[i]-48;
        i--;
        j=10;

        while(prefix[i] == '1' || prefix[i] == '2' || prefix[i] == '3' || prefix[i] == '4' || prefix[i] == '5' || prefix[i] == '6' || prefix[i] == '7' || prefix[i] == '8' || prefix[i] == '9' || prefix[i] == '0' ){
            y += j*(((int)prefix[i])-48);
            i--;
            j*=10;
        }
        insertNode(inExpLL, y, 1);
        }
    else i--;
    }
}
int precedence(char op)
{
    if(op == '*' || op == '/')
        return 1;
    else return 0;
}