bool Match(char exp[],int n)
{
    int i=0;
    char e;
    bool match = true;
    LinkStNode * st;
    InitStack(st);
     while(i<n&&match)
     {
         if(exp[i]=='(')
                Push(st,exp[i]);
         else if(exp[i]==')')
         {
             if(GetTop(st,e)==True)
             {
                 if(e!='(')
                        match=false;
                 else
                    Pop(st,e);
             }
             else match=false;

         }
         i++;
     }
     if(!StackEmpty(st))
        match=false;
     DestoryStack(st);
     return match;
}

Void CreateMat(TSMatrix &t,ElemType A[M][N])
{

    int i,j;
    r.tows=M;t.cols=N;t.nums=0;
    for(i=0;i<M;i++)
    {
        for(j=0;j<N;j++)
        if(A[i][j]!=0)      //Ö»´æ´¢·ÇÁãÔªËØ
        {
            t.data[t.nums].r=i;t.data[t.nums].c=j;
            t.data[t.nums].d=A[i][j];t.nums++;
        }
    }
}
