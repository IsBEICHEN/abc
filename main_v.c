#include"a.c"
void main_v()//投票者者界面
{
    system("color B");

    int key;
    do
    {
        system("cls");
        printf("*************************************************************\n");
        printf("********************欢迎进入投票员界面***********************\n");
        printf("*************************************************************\n");
        printf("**  1.浏览所有候选人              2.查询候选人信息         **\n");
        printf("**  3.投票                        4.退出                   **\n");
        scanf("%d",&key);

        switch(key)
        {
         case 1:scan();break;
         case 2:search();break;
         case 3:vote();break;
         case 4:break;
         default:break;
         }

     }while(key!=4);
}

void vote()  //投票者投票
{

    int a;
    long candidatenum;//定义进行操作时的临时结构体变量
    int i,flag;
    char DataFile[20]="DataFile.txt",next;// DataFile存储候选人信息的文件名，next为是否进行下一次投标操作的选项
    candidate TempS;
    FILE *fp;

begin:
    system("cls");
    flag=0;//flag用来标志是否找对应编号，即投票是否成功
    read();
    printf("请输入您要投票的候选人的号码:");
    scanf("%ld",&candidatenum);
    printf("您所投票的候选人号码是:%ld\n",candidatenum);
    for(i=0;i<c_total;i++)
    {
        if(c_man[i].number==candidatenum)
        {
            flag=1;
            a=i;
            c_man[i].vote++;
        }
    }
    if(flag)
    {
        if(total_user[a].power>0)
        {

            printf("投票成功\n");
            total_user[a].power--;
            system("cls");
            fp=fopen(DataFile,"wb");

            if(fp==NULL)//如果当前文件不存在，提示打开文件失败
            {
                printf("\nOpen file is fail!End with any key.\n",DataFile);
                perror("Open file fail");
                getch();
                exit(1);
            }
            for(i=0;i<c_total;i++)
            {

                fwrite(&c_man[i],sizeof(candidate),1,fp);

            }
            fclose(fp);
        }

        else
        {
            printf("您没有足够的票数！");
            printf("按任意键返回首页！             \n");
            getch();
            system("cls");
            return;
        }
    }
    else
    {
        system("cls");
        printf("投票失败！您要投票的号码不存在\n");
        printf("按任意键返回首页！             \n");
        getch();
        system("cls");
        return;
    }
    fp=fopen(DataFile,"rb");// 显示投票后的情况


    if(fp==NULL)
    {
        printf("\nOpen file %s fail! End With any key \n",DataFile);
        perror("Open file fail");
        getch();
        exit(1);
    }

        printf("整理后的最新投票情况:\n");
        printf("\n候选人号码     \t候选人姓名      \t票数\n");//"\t"  横向跳到下一制表符位置

    while(fread(&TempS,sizeof(candidate),1,fp)!=(int)NULL)
    {
        if(TempS.number!=0)

        printf("\n%ld            \t%s              \t%d \n",TempS.number,TempS.name,TempS.vote);
    }

    fclose(fp);

    printf("\n继续吗?是(Y)/否(N): ");

    fflush(stdin);

    next=getchar();

    putchar('\n');

    if(next=='y'||next=='Y')goto begin;

}
void scan()//浏览候选人信息
{
    system("cls");

    read();

    printf("候选人资料：\n");

    printf("***************************************************************\n");

    for(i=0;i<c_total;i++)
    {
        printf("号码:%-15ld",c_man[i].number);
        printf("姓名:%-19s",c_man[i].name);
        printf("简介:%s\n",c_man[i].intro);
    }
    printf("***************************************************************");
    printf("\n按任意键返回首页！");
    getch();
}

void search() //查询候选人信息
{
    system("cls");

    char c;

    long number;

    int flag=0;

    read();

    do
    {
        printf("\n\t请输入要查询的候选人号码:");
        scanf("%ld",&number);
        for(i=0;i<c_total;i++)
        {
            if(number==c_man[i].number)
            {
                printf("\t您要查询的候选人信息如下:\n\n");
                printf("\t号码:%ld \n",c_man[i].number);
                printf("\t姓名:%s \n",c_man[i].name);
                printf("\t简介:%s \n",c_man[i].intro);
                flag=1;
                break;
            }
        }
        if (flag)
        {
            flag=0;
        }
        else
        {
            printf("\t对不起，没有您要查询的候选人\n");
        }
            printf("\t要继续查询候选人吗?是(Y)/否(N): ");
        getchar();
        c=getchar();
    }while((c=='Y')||(c=='y'));
}
void read()//读取候选人信息
{

    system("cls");
    char DataFile[20]="DataFile.txt";
    FILE * fp=NULL;
    c_total=0;
    fp=fopen(DataFile,"rb");
    if(fp==NULL)
    {
        printf("\nOpen file %s fail! 任意键结束 \n",DataFile);
        perror("Open file fail");
        getch();
        exit(1);
    }
    while(fread(&c_man[c_total],sizeof(candidate),1,fp)!=(int)NULL)
    {
        c_total++;
    }
    fclose(fp);
}

