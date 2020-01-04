/***********************************************************
* 版权所有 (C)2020, LiuChenHao
*
* 文件名称： main.c
* 文件标识：无
* 内容摘要：该代码为登陆界面
* 其它说明：无
* 当前版本： V1.0
* 作   者：刘辰昊
* 完成日期： 2020 1 3
*
* 修改记录1：
* 修改日期： 2020 1 3
* 版本号： V1.0
* 修改人： LiuChenHao
* 修改内容：创建
**********************************************************/


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



/*********************************************************
* 功能描述：投票者界面
* 输入参数： 无
* 输出参数： 无
* 返回值：   无
* 其它说明：用于转向投票者其他操作的界面
************************************************************/

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

/*********************************************************
* 功能描述：投票者投票
* 输入参数： 无
* 输出参数： TempS.number  被投票的候选人号码
              TempS.name    被投票的候选人姓名
              TempS.vote    被投票的候选人当前得票数
* 返回值： 无
* 其它说明：消息字段之间用分号(;)分隔
************************************************************/

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
/*********************************************************
* 功能描述：管理员界面
* 输入参数： 无
* 输出参数： 无
* 返回值：   无
* 其它说明： 用于转向管理员系统的各种功能的界面
************************************************************/

void main_a()//管理员界面
{
    system("color B");
    int key;
    do
    {
        system("cls");
        printf("*************************************************************\n");
        printf("********************欢迎进入管理员界面***********************\n");
        printf("*************************************************************\n");
        printf("**  1.创建新候选人                    2.创建新用户         **\n");
        printf("**  3.查询候选人信息                  4.浏览所有候选人     **\n");
        printf("**  5.整理所有投票                    6.清空候选人信息     **\n");
        printf("**  7.票数清零                                             **\n");
        printf("**                   0.退出                                **\n");
        scanf("%d",&key);
        switch(key)
        {
         case 1:addcandidate();break;
         case 2:addUser();break;
         case 3:search();break;
         case 4:scan();break;
         case 5:sort(); break;
         case 6:empty(); break;
         case 7:Votexiugai(); break;
         case 0:break;
         default:break;

        }
   }while(key!=0);
}
/*********************************************************
* 功能描述：创建候选人
* 输入参数： 无
* 输出参数： TempS.name  新候选人姓名
              TempS.intro 新候选人简介
              TempS.vote  用于记录新候选人得票数，初始化为0

* 返回值：   无
* 其它说明： 创建一个新的候选人；将新候选人信息存储到文件中
************************************************************/
void addcandidate()//创建候选人
{
    system("cls");
    char DataFile[20]="DataFile.txt";
    FILE * fp=NULL;
    char c;
    int over_flag=0;
    candidate TempS;
    read();
    fp=fopen(DataFile,"ab+");

    do
    {
      system("cls");
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
/*********************************************************
* 功能描述：读取候选人信息
* 输入参数： 无
* 输出参数： 无
* 返回值：    无
* 其它说明：将读取候选人文件DataFile中的信息到缓冲区以便进行下一步操作；
            包含于其他函数中作调用；
************************************************************/

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
/*********************************************************
* 功能描述：创建新用户
* 输入参数： TempS.name  新用户的姓名
             TempS.ps    新用户的密码
             TempS.power 新用户的权限
* 输出参数： 无
* 返回值： 无
* 其它说明：创建一个新用户并赋予他权限；
            将新用户的信息存储到 用户.txt文件中
************************************************************/

void addUser()//创建用户
{
    system("cls");
    FILE *fp=NULL;
    char DataFile[20]="用户.txt";//存储投票人信息的文件名
    user TempS;
    int over_flag=0;
    char c;
    fp=fopen("用户.txt","ab+");//读入原始数据,用于检查输入是否有重复

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
/*********************************************************
* 功能描述：浏览候选人信息
* 输入参数： 无
* 输出参数： c_man[i].number  候选人号码
              c_man[i].name     候选人姓名
              c_man[i].intro    候选人简介
* 返回值： 无
* 其它说明：将存储到结构体数组中的候选人信息全部输出到屏幕上
************************************************************/
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
/*********************************************************
* 功能描述：查询候选人信息
* 输入参数： number  想查询的候选人的号码
* 输出参数：     c_man[i].number     查询的候选人的号码
                 c_man[i].name        查询的候选人的姓名
                 c_man[i].intro       查询的候选人的简介

* 返回值： 无
* 其它说明：输入查询的候选人的号码，将所查询的候选人的信息输出到屏幕上
************************************************************/

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
/*********************************************************
* 功能描述：整理所有投票
* 输入参数： 无
* 输出参数： c_man2[i].number    候选人号码
             c_man2[i].name       候选人姓名
             c_man2[i].vote       候选人当前票数
* 返回值： 无
* 其它说明：将所有候选人的信息整理；
            按照候选人票数从高到低排序；
            将所有整理后的候选人新的输出到屏幕上；
************************************************************/

void sort()//整理所有投票
{

    int i,k,j;

    candidate c_man2[N]/*存放排序后的数据 */,   temp;
    read();
    for(i=0;i<c_total;i++)
       c_man2[i]=c_man[i];
    for(i=0;i<c_total-1;i++)
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
/*********************************************************
* 功能描述：清空候选人
* 输入参数： 无
* 输出参数： 无
* 返回值： 无
* 其它说明：将存储候选人信息的文件 DataFile.txt 清空
************************************************************/


void empty()//清空候选人
{
     FILE * fp;
    fp = fopen("DataFile.txt", "w");//以只写方式打开文件时 其实就是创建了一个新文件(空的)。 如果本来存在文件，也同样会被覆盖
    if(fp == NULL)
        printf("do empty file %s failed\n", fp);
    else fclose(fp);
     printf("数据清空完成\n");


}


/*********************************************************
* 功能描述：登陆界面
* 输入参数： input_user.name     用户名
              input_user.ps       密码
* 输出参数： 无
* 返回值： 无
* 其它说明：输入用户名和密码；
            根据不同的用户名密码跳转到管理员系统或投票者系统；
************************************************************/

void main()
{

    FILE * fp=NULL;
    char DataFile[20]="用户.txt";
    char relogin;//是否重新登录的标志
    int success=0;
    user input_user,temp_user;
    system("color 1");
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

     if(strcmp(input_user.name,"123")==0 && (strcmp(input_user.ps,"123456")==0))//校验用户名和密码,若是管理员,并调用管理员界面
     {
            printf("\nlogin successful!");
            success=1;
            system("cls");
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
            system("cls");
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
        system("cls");
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

/*********************************************************
* 功能描述：票数修改
* 输入参数： 无
* 输出参数： TempS.number    候选者号码
              TempS.name      候选人姓名
              TempS.vote      候选人当前票数
* 返回值： 无
* 其它说明：将指定候选人的票数进行修改
************************************************************/


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
