/******************************************************************************************
*   Visit https://github.com/biabbas/ExpressionTreeRE.c for all files.             *
*                                                                                          *
*                                                                                          *
*                                                                                          *
*                                                                                          *
*                                                                                          *                                                                                         
*   Created by B I                                                                                       *
******************************************************************************************/      

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
typedef struct node{
    int x;
    int value;
    char data;
    struct node *lp;
    struct node *rp;
}* Node;
int ip(char x);
Node Tree(char pf[]);
int answer(Node root);
int Valid(Node root);
int main(void) {

    char in[20];
    Node ExpTree = NULL;    
    int ans;
    printf("Enter the valid expression:\n");
    scanf("%s",in);
    
    ExpTree = Tree(in);
    ans = answer(ExpTree);
    printf("The Answer is %d\n",ans);
    return 0;

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
        
        default: 
        return -1;
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
    temp->x = 1;
    temp->value = (int)temp->data - 48;
    while(isdigit(in[j]))
    temp->value = temp->value*10 + (int)in[j++]-48;
    DigStk[++topD] = temp; 
}
else{
    temp->x = 0;
     if (temp->data=='(')
          OpStk[++topO]=temp;
        else if (temp->data==')'){
            while (OpStk[topO]->data!='(') {
            OpStk[topO]->rp = DigStk[topD--];
            OpStk[topO]->lp = DigStk[topD];
            DigStk[topD] = OpStk[topO--];
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
            OpStk[topO]->lp = DigStk[topD];
            DigStk[topD] = OpStk[topO--];
                }
            OpStk[++topO] = temp;  
            }
        }
    }
}
while (OpStk[topO]->data!='#')
{
                OpStk[topO]->rp = DigStk[topD--];
            OpStk[topO]->lp = DigStk[topD];
            DigStk[topD] = OpStk[topO--];
      }
return DigStk[topD];
}
int answer(Node root){
if(root->x){
return root->value;
}
else 
   switch(root->data)     
   {
      case '+':          //addition
          return (answer(root->lp)+answer(root->rp));
          break;
      case '-':           //subtraction
          return (answer(root->lp)-answer(root->rp));

      case '*':            //multiplication
          return (answer(root->lp)*answer(root->rp));

      case '/':           //division
          return (answer(root->lp)/answer(root->rp));

      case '^':     
      case '$':
return ((int)pow((double)answer(root->lp),(double)answer(root->rp)));
      default:
      return 0;
   }
}
