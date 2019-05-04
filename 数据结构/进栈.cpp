

Status Pop(SqStack *S,SElemType e){

   if(S->top == -1)
    return ERROR;
   *e = S->data[S->top];
   S->top--;
   return OK;
}
