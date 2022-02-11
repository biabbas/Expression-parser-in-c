#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
typedef struct node{
    char data;
    struct node *lp;
    struct node *rp;
}* Node;
int ip(char x);
Node Tree(char pf[]);
int answer(Node root);
int main() {
    char in[20];
    Node ExpTree = NULL;    
    int ans;
    printf("Enter the valid expression:\n");
    scanf("%s",in);
    ExpTree = Tree(in);
    ans = answer(ExpTree);
    printf("\nThe answer is %d\n",ans);
}
int ip(char x){
    switch (x) {
        case '#' :
        case '(' : return 0;break;
        case '+' :
        case '-' : return 1;break;
        case '*' :
        case '/' : return 2;break;
        case '$' :
        case '^' : return 3;break;
        default: printf("%c was to be tested",x);
        exit(0);
    }
}
Node Tree(char in[]){
Node DigStk[10],OpStk[10];
int j=0,topD=-1,topO= 0;
OpStk[0] = (Node)malloc(sizeof(struct node));
OpStk[0]->data = '#';
while(in[j]!='\0'){
Node temp = NULL;
temp = (Node)malloc(sizeof(struct node));
temp->data = in[j++];
temp->lp = NULL;
temp->rp = NULL;
if(isdigit(temp->data)){
    DigStk[++topD] = temp; 
}
else{
     if (temp->data=='(')
          OpStk[++topO]=temp;
        else if (temp->data==')'){
            while (OpStk[topO]->data!='(') {
            OpStk[topO]->rp = DigStk[topD--];
            OpStk[topO]->lp = DigStk[topD--];
            DigStk[++topD] = OpStk[topO--];
            }
            free(temp);
            free(OpStk[topO--]);
        }
        else{
            if(ip(OpStk[topO]->data) < ip(temp->data))
                OpStk[++topO] = temp;
            else{
                while (ip(OpStk[topO]->data) >= ip(temp->data)) {
            OpStk[topO]->rp = DigStk[topD--];
            OpStk[topO]->lp = DigStk[topD--];
            DigStk[++topD] = OpStk[topO--];
                }
            OpStk[++topO] = temp;  
            }
        }
    }
}
while (OpStk[topO]->data!='#')
{
            OpStk[topO]->rp = DigStk[topD--];
            OpStk[topO]->lp = DigStk[topD--];
            DigStk[++topD] = OpStk[topO--];
      }
return DigStk[topD];
}
int answer(Node root){
if(isalnum(root->data)){
return ((int)root->data - 48);
}
else 
   switch(root->data)     
   {
      case '+': return (answer(root->lp)+answer(root->rp));
      case '-': return (answer(root->lp)-answer(root->rp));
      case '*': return (answer(root->lp)*answer(root->rp));
      case '/': return (answer(root->lp)/answer(root->rp));
      case '^':     
      case '$': return ((int)pow((double)answer(root->lp),(double)answer(root->rp)));
      default:  return 0;
   }
}

