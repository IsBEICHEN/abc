

```



void TopSort(AdjGraph *G)       //���������㷨
{
    int i,j;
    int St[MAXV].top=-1;        //ջSt��ָ��Ϊtop
    ArcNode *p;
    for(i=0;i<G->n;i++)         //����ó�ֵ0
        G->adjlist[i].count=0;
    for(i=0;i<G->n;i++)         //����ж�������
    {
        p=G->adjlist[i].firstarc;
        while(p!=NULL)
        {
            G->adjlist[p->adjvex].count++;
            p=p->nextarc;
        }
    }

    for(i=0;i<G->n;i++)         //�����Ϊ0�Ķ����ջ
        if(G->adjlist[i].count==0)
        {
            top++;
            St[top]=i;
        }
    while(top>-1)               //ջ�ղ�ѭ��
    {
        i=St[top];top==;        //��ջһ������i
        printf("%d",i);         //����ö���
        p=G->adjlist[i].count;  //�ҵ�һ���ڽӵ�
        while(p!=NULL)          //������i�ĳ����ڽӵ����ȼ�1
        {
            j=p->adjvex;
            G->adjlist[j].count--;
            if(G->adjlist[j].count==0)      // �����Ϊ0���ڽӵ��ջ
            {
                top++;
                St[top]=j;
            }
            p=p->nextarc;        //����һ���ڽӵ�
        }
    }

}
```
