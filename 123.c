#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>


#define closegr closegraph
#define N 30


void main_a(); //管理员界面
void main_v(); //投票者者界面
void addcandidate(); // 创建候选人
void addUser();//创建投票者
void search(); //查询候选人信息
void scan();//浏览候选人信息
void vote();  //投票者投票
void read();//读取候选人信息
void save();//存储候选人信息
void sort();//整理所有投票
void effectivevoting();//有效投票数
void empty();//清空候选人

void Votexiugai();//票数修改

int total=0;
int c_total=0;
int i=0;



typedef struct candidate//候选人数据结构体
{
    long number;//候选人编号
    char name[20];//候选人姓名
    char intro[400];//候选人简介
    int vote;//候选人得票数
}candidate;



typedef struct user//投票者数据结构体
{
  char name[20];//投票者姓名
  char ps[8];//对应密码
  int power;//权限
}user;



candidate c_man[N];
user total_user[N];




void main_v()//投票者者界面
{


    int key;
    do
    {
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


    long candidatenum;//定义进行操作时的临时结构体变量
    int i,flag;
    char DataFile[20]="DataFile.txt",next;// DataFile存储候选人信息的文件名，next为是否进行下一次投标操作的选项
    candidate TempS;
    FILE *fp;

begin:

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
            c_man[i].vote++;
        }
    }
    if(flag)
    {
        printf("投票成功\n");


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
        printf("投票失败！您要投票的号码不存在\n");
        printf("按任意键返回首页！             \n");
        getch();
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

void main_a()//管理员界面
{

    int key;
    do
    {
        printf("*************************************************************\n");
        printf("********************欢迎进入管理员界面***********************\n");
        printf("*************************************************************\n");
        printf("**  1.创建新候选人                    2.创建新用户         **\n");
        printf("**  3.查询候选人信息                  4.浏览所有候选人     **\n");
        printf("**  5.整理所有投票                    6.有效投票数         **\n");
        printf("**  7.清空候选人信息                  8.票数清零           **\n");
        printf("**                   0.退出                                **\n");
        scanf("%d",&key);
        switch(key)
        {
         case 1:addcandidate();break;
         case 2:addUser();break;
         case 3:search();break;
         case 4:scan();break;
         case 5:sort(); break;
         case 6:effectivevoting(); break;
         case 7:empty(); break;
         case 8:Votexiugai(); break;
         case 0:break;
         default:break;

        }
   }while(key!=0);
}

void addcandidate()//创建候选人
{

    char DataFile[20]="DataFile.txt";
    FILE * fp=NULL;
    char c;
    int over_flag=0;
    candidate TempS;
    read();
    fp=fopen(DataFile,"ab+");

    do
    {
      printf("                 *****************创建新候选人*****************\n");
      printf("请输入:");

      printf("候选人号码:");scanf("%ld",&TempS.number);
        for(i=0;i<c_total;i++)//检查输入编号是否有重复
        {
            if(TempS.number==c_man[i].number)
            {
                printf("该号码已存在.按任意键浏览所有候选人...");
                getch();
                over_flag=1;
                break;
            }
        }
        if (over_flag)
        {
            over_flag=0;
            continue;
        }
        printf("        姓名:");scanf("%s",&TempS.name);

        TempS.name[19]='\0';

        for(i=0;i<c_total;i++)
        {
            if(strcmp(TempS.name,c_man[i].name)==0)
            {
                printf("该姓名已存在！请再输入一次！按任意键继续...");
                getch();
                over_flag=1;
                break;
            }
        }
        if (over_flag)
        {
            over_flag=0;
            continue;
        }
        printf("        简介:");
        fflush(stdin);
        gets(TempS.intro);
        TempS.intro[399]='\0';
        TempS.vote=0;
        c_man[c_total]=TempS;//将数据加入原始数据,用于下一次输入比较
        c_total++;
        if(fwrite(&TempS,sizeof(candidate),1,fp)!=1)
        {
            printf("\nwrite file is fail! End with any key\n",DataFile);
            perror("write file fail");
            getch();
            exit(1);
        }
        printf("要继续创建新的候选人吗?是(Y)/否(N): ");

        fflush(stdin);

        c=getchar();

    }while(c=='Y'||c=='y');


    fclose(fp);
    printf("候选人资料：\n");    // 在屏幕上显示文件内容
    printf("*****************************************************************");
    fp=fopen(DataFile,"rb");
    if(fp==NULL)
    {
        printf("\nOpen file %s fail! 任意键结束 \n",DataFile);
        perror("Open file fail");
        getch();
        exit(1);
    }
    while(fread(&TempS,sizeof(candidate),1,fp)!=(int)NULL)
    {
        printf("\n号码:%-15ld姓名:%-15s简介:%s",TempS.number,TempS.name,TempS.intro);
    }
    fclose(fp);
    printf("\n*****************************************************************");
    printf("\n按任意键返回首页！\n");
    getch();
}

void read()//读取候选人信息
{


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

void addUser()//创建用户
{

    FILE *fp=NULL;
    char DataFile[20]="用户.txt";//存储投票人信息的文件名
    user TempS;
    int over_flag=0;
    char c;
    fp=fopen("用户.txt","rb");//读入原始数据,用于检查输入是否有重复

    if(fp==NULL)
    {
        printf("\nOpen file %s fail! 任意键结束 \n",DataFile);
        perror("Open file fail");
        getch();
        exit(1);
    }

    while(fread(&total_user[total],sizeof(user),1,fp)!=(int)NULL)
    {
        total++;
    }


    fclose(fp);
    fp=fopen(DataFile,"ab+");
    do
    {
        printf("                *****************创建新用户*****************                   ");
        printf("请输入:");
        printf("用户名:");scanf("%s",&TempS.name);
        TempS.name[19]='\0';
        for(i=0;i<total;i++)//检查输入姓名是否有重复
        {
            if(strcmp(TempS.name,total_user[i].name)==0)
            {
                printf("该用户名已存在！按任意键浏览所有用户...");
                getch();
                over_flag=1;
                break;
            }
        }
        if (over_flag)
        {
            over_flag=0;
            continue;
        }
        printf("  密码:");

        scanf("%s",&TempS.ps);

        TempS.ps[7]='\0';

        printf("  权限:");

        scanf("%d",&TempS.power);

        if(TempS.power!=1)
        {
            TempS.power=0;
        }
        total_user[total]=TempS;//将数据加入原始数据

        total++;

        if(fwrite(&TempS,sizeof(user),1,fp)!=1)
        {
            printf("\nwrite file is fail! 任意键结束\n",DataFile);

            perror("write file fail");

            getch();

            exit(1);
        }
        printf("要继续创建新用户吗?是(Y)/否(N):");
        getchar();

        c=getchar();

    }while(c=='Y'||c=='y');

    fclose(fp);

    printf("用户资料数据处理完毕.\n",DataFile);//在屏幕上显示文件内容

    printf("所有用户具体情况如下:\n");

    fp=fopen(DataFile,"rb");

    printf("************************************************************");
    if(fp==NULL)
    {
        printf("\nOpen file is fail! End With any key \n",DataFile);

        perror("Open file fail");//将错误信息输出

        getch();

        exit(1);
    }
    printf("\n姓名\t\t密码\t\t权限\n");

    while(fread(&TempS,sizeof(user),1,fp)!=(int)NULL)
    {
        printf("\n%s\t\t%-8s\t\t%d\n",TempS.name,TempS.ps,TempS.power);
    }
    fclose(fp);

    printf("************************************************************");

    printf("\n按任意键返回首页！\n");

    getch();

}

void scan()//浏览候选人信息
{

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

void sort()//整理所有投票
{

    int i,k,j;

    candidate c_man2[N]/*存放排序后的数据 */,   temp;
    read();
    for(i=0;i<c_total;i++)
       c_man2[i]=c_man[i];
    for(i=0;i<c_total-1;i++)//用选择法排序
    {
       k=i;
       for(j=i+1;j<c_total;j++)
       {
          if(c_man2[k].vote<c_man2[j].vote)
              k=j;
       }
       if(k!=i)
       {
         temp=c_man2[i];
         c_man2[i]=c_man2[k];
         c_man2[k]=temp;
       }
    } //排序结束
    printf("票数从高到低排列如下:\n");
    printf("***********************************************\n");
    printf("*号码           候选人           票数         *\n");
    printf("***********************************************\n");
    for(i=0;i<c_total;i++)       //输出排序后的结果
    {
       printf("* %-13ld %-13s    %-6d       *\n",c_man2[i].number,c_man2[i].name,c_man2[i].vote);
    }
    printf("***********************************************\n");
    printf("按任意键返回首页！\n");
    fflush(stdin);
    getch();
}
void effectivevoting()//有效投票数--
{
    read();
    int sum=0;
    int i;
    for(i=0;i<c_total;i++)
    {
        if(c_man[i].vote !=0)
        {

            sum=sum+c_man[i].vote;
        }
    }
  printf("有效投票数为：%ld\n",sum);
}


void empty()//清空候选人
{
     FILE * fp;
    fp = fopen("DataFile.txt", "w");//以只写方式打开文件时 其实就是创建了一个新文件(空的)。 如果本来存在文件，也同样会被覆盖
    if(fp == NULL)
        printf("do empty file %s failed\n", fp);
    else fclose(fp);
     printf("数据清空完成\n");


}
void main()
{

    FILE * fp=NULL;
    char DataFile[20]="用户.txt";
    char relogin;//是否重新登录的标志
    int success=0;
    user input_user,temp_user;
    printf("管理员账号：滕健  密码都为123456\n");
    printf("\n");
    printf("*************************************************************\n");
    printf("********************欢迎登录电子投票系统*********************\n");
    printf("*************************************************************\n");
    printf("*                                                           *\n");
again:
        printf("                请输入用户名:            &&");
        scanf("%s",input_user.name);
        printf("                  请输入密码:            &&");
        scanf("%s",input_user.ps);
        printf("*************************************************************\n");
    fflush(stdin);

     fp=fopen("用户.txt","rb");//读入原始数据,用于检查输入是否有重复

    if(fp==NULL)
    {
        printf("\nOpen file %s fail! 任意键结束 \n",DataFile);
        perror("Open file fail");
        getch();
        exit(1);
    }

    while(fread(&total_user[total],sizeof(user),1,fp)!=(int)NULL)
    {
        total++;
    }


    fclose(fp);

     if(strcmp(input_user.name,"滕健")==0 && (strcmp(input_user.ps,"123456")==0))//校验用户名和密码,若是管理员,并调用管理员界面
     {
            printf("\nlogin successful!");
            success=1;
            printf("\n\n\n\n\n\n\n         您是管理员!欢迎您登录系统!正在进入管理员界面...\n");
            main_a();
        }
    else
    {

       for(i=0;i<30;i++)
       {



            if(strcmp(input_user.name,total_user[i].name)==0 && (strcmp(input_user.ps,total_user[i].ps)==0))
        {
            printf("\nlogin successful!");
            success=1;
            printf("\n\n\n\n\n\n\n         您是投票者!欢迎您登录系统!正在进入投票者界面...\n");
            main_v();
        }

       }

    }
    fclose(fp);
    if(success==0)
    {
        printf("%d",c_total);
        fflush(stdin);//文件数据更新
        printf("%d",c_total);
        printf("\n用户名或密码错误！继续输入吗？是(Y)/否(N): ");
        fflush(stdin);

        relogin=getchar();
        if((relogin=='Y')||(relogin=='y'))
        {
            goto again;
        }
        else
        {
            printf("结束\n");
            exit(0);
        }
    }


}

void read1()
{
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

void Votexiugai()//票数修改
{
    long candidatenum;//定义进行操作时的临时结构体变量
    int i,flag;
    char DataFile[20]="DataFile.txt",next;// DataFile存储候选人信息的文件名，next为是否进行下一次投标操作的选项
    candidate TempS;
    FILE *fp;


begin:

    flag=0;//flag用来标志是否找对应编号
    read();



    for(i=0;i<c_total;i++)
    {


            flag=1;
            c_man[i].vote=0;

    }
    if(flag)
    {
        printf("修改成功\n");


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
