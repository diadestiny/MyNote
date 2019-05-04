

void CreateListHead(LinkList *L,int n){
    LinkList p,r;
    int il
    srand(time(0));
    *L = (LinkList) malloc(sizeof(Node));
    r = *L;
    for(i=0;i<n;i++){
        p = (LinkList) malloc(sizeof(Node));
        p->data = rand()%100+1;
        r->next = p;
        r=p;
    }
    r->next = NULL:
}
