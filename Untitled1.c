#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

#define N 30



/*
管理员用户名123  密码123
*/


/*
帮助（文件操作）
    r 	只读。若文件不存在返回空指针
    w 	只写。若文件存在，则删除其内容，否则创建一个新文件
    a 	追加。若文件不存在，则创建一个新文件
    r+ 	读写。指定的文件必须已存在，否则返回NULL
    w+ 	读写。若指定的文件已存在，则其中的内容被删去
    a+  读写，追加写。
*/

void main_guan();           //管理员界面
void main_tou();            //投票人界面
void scan();                //浏览候选人信息
void search();              //查询候选人信息
void addcandidate();        //创建新的候选人
void addUser();             //创建新用户
void sort();                //整理投票结果
void effectivevoting();     //查询有效投票数
void empty();               //清空所有候选人信息
void Votexiugai();          //票数清零
void read();                //读取候选人信息


int c_total = 0;
int i = 0;
int User = 0;


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
    int username;//投票者账号
    int password;
}user;


candidate c_man[N];
user total_user[N];



void read()//读取候选人信息
{


    char DataFile[20] = "DataFile.txt";
    FILE* fp = NULL;
    c_total = 0;
    fp = fopen(DataFile, "rb");
    if (fp == NULL)
    {
        printf("\nOpen file %s fail! 任意键结束 \n", DataFile);
        perror("Open file fail");
        getch();
        exit(1);
    }
    while (fread(&c_man[c_total], sizeof(candidate), 1, fp) != (int)NULL)
    {
        c_total++;
    }
    fclose(fp);
}


void scan()//浏览候选人信息
{

    read();
    int i;
    printf("候选人资料：\n");

    printf("***************************************************************\n");

    for (i = 0; i < c_total; i++)
    {
        printf("号码:%-15ld", c_man[i].number);
        printf("姓名:%-19s", c_man[i].name);
        printf("简介:%s\n", c_man[i].intro);
    }
    printf("***************************************************************");
    printf("\n按任意键返回首页！");
    getch();
}


void search() //查询候选人信息
{

    char c;

    long number;

    int flag = 0;

    read();

    do
    {
        printf("\n\t请输入要查询的候选人号码:");
        scanf("%ld", &number);
        for (i = 0; i < c_total; i++)
        {
            if (number == c_man[i].number)
            {
                printf("\t您要查询的候选人信息如下:\n\n");
                printf("\t号码:%ld \n", c_man[i].number);
                printf("\t姓名:%s \n", c_man[i].name);
                printf("\t简介:%s \n", c_man[i].intro);
                flag = 1;
                break;
            }
        }
        if (flag)
        {
            flag = 0;
        }
        else
        {
            printf("\t对不起，没有您要查询的候选人\n");
        }
        printf("\t要继续查询候选人吗?是(Y)/否(N): ");
        getchar();
        c = getchar();
    } while ((c == 'Y') || (c == 'y'));
}


void vote() //投票者投票
{
    int flag = 0;//用来标记是否投票成功
    long candidatenum;//定义进行操作时的临时结构体变量
    char DataFile[20] = "DataFile.txt";// DataFile存储候选人信息的文件名
    FILE* fp;

    read();
    printf("请输入您要投票的候选人的号码:");
    scanf("%ld", &candidatenum);
    printf("您所投票的候选人号码是:%ld\n", candidatenum);
    for (i = 0; i < c_total; i++)
    {
        if (c_man[i].number == candidatenum)
            flag = 1;
    }
    if (flag)
    {
        printf("投票成功\n");


        fp = fopen(DataFile, "wb");

        if (fp == NULL)//如果当前文件不存在，提示打开文件失败
        {
            printf("\nOpen file is fail!End with any key.\n", DataFile);
            perror("Open file fail");   //将错误原因输出到屏幕上
            getch();
            exit(1);
        }
        for (i = 0; i < c_total; i++)          //修改候选人的票数数据
        {

            fwrite(&c_man[i], sizeof(candidate), 1, fp);
            /*
            {
            此处加一条fwrite函数的用法
            fwrite(const void*buffer,size_t size,size_t count,FILE*stream);
            （1）buffer：是一个指针，对fwrite来说，是要输出数据的地址。
            （2）size：要写入的字节数；
            （3）count:要进行写入size字节的数据项的个数；
            （4）stream:目标文件指针。
            }
            */
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

    fp = fopen(DataFile, "rb");// 将投票后的情况显示到屏幕上

    fclose(fp); //关闭文件


}

void main_tou() //投票者界面
{
    int key;
    do
    {
        printf("*************************************************************\n");
        printf("**********************欢迎来到投票界面***********************\n");
        printf("**********************请选择您的操作：***********************\n");
        printf("*************************************************************\n");
        printf("****   1.浏览候选人信息               2.查询候选人信息   ****\n");
        printf("*************************************************************\n");
        printf("****   3.投票                         4.退出             ****\n");
        printf("*************************************************************\n");
        scan("%d", &key);
        switch (key)
        {
        case 1:scan(); break;
        case 2:search(); break;
        case 3:vote(); break;
        case 4:break;
        default:break;
        }
    } while (key != 4);

}


void addUser()//创建新用户


{
    FILE* fp = NULL;
    user TempS;
    char DataFile[20] = "用户.txt";
    fp = fopen("用户.txt", "rb");//读入原始数据,用于检查输入是否有重复

    if (fp == NULL)
    {
        printf("\nOpen file %s fail! 任意键结束 \n", DataFile);
        perror("Open file fail");
        getch();
        exit(1);
    }

    fclose(fp);
    fopen("用户.txt", "ab+");
    printf("**************************添加新用户***************************\n");
    printf("请输入投票人用户名：");
    scanf("%s", &TempS.username);
    if (User != 0)
    {
        for (i = 0; i < User; i++)
        {
            if (strcmp(TempS.username, total_user[i].username) == 0)
            {
                printf("该用户名已存在！按任意键浏览所有用户...");
                getch();
                break;
            }
        }
    }
    printf("请输入投票人的姓名：");
    scanf("%d", &TempS.name);
    total_user[User] = TempS;//将数据加入原始数据
    User++;

    if (fwrite(&TempS, sizeof(user), 1, fp) != 1)
    {
        printf("\nwrite file is fail! 任意键结束\n", DataFile);

        perror("write file fail");

        getch();

        exit(1);
    }
    fclose(fp);

    printf("用户资料数据处理完毕.\n");//在屏幕上显示文件内容

    fclose(fp);



    printf("\n按任意键返回首页！\n");

    getch();
}


void addcandidate()//创建新候选人
{
    FILE* fp;
    char DataFile[20] = "DataFIle.txt";
    candidate TempS;

    read();
    fp = fopen(DataFile, "ab+");

    printf("**************************创建新的候选人**************************\n");
    printf("****请输入候选人姓名:");
    scanf("%s",&TempS.name);
    printf("\n添加成功");
    printf("****请输入候选人编号:");
    scanf("%ld",&TempS.number);
    printf("\n添加成功");
    for (i = 0; i < c_total; i++)
    {
        if (TempS.number == c_man[i].number)
        {
            printf("编号重复");
            getch();
            break;
        }

    }

    printf("        简介:");
    fflush(stdin);
    gets(TempS.intro);
    TempS.intro[399] = '\0';
    TempS.vote = 0;
    c_man[c_total] = TempS;//将数据加入原始数据,用于下一次输入比较
    c_total++;
    if (fwrite(&TempS, sizeof(candidate), 1, fp) != 1)
    {
        printf("\nwrite file is fail! End with any key\n", DataFile);
        perror("write file fail");
        getch();
        exit(1);
    }


}


void main_guan()//管理员界面
{

    int key;
    do
    {
        printf("*************************************************************\n");
        printf("********************欢迎进入管理员界面***********************\n");
        printf("*************************************************************\n");
        printf("**  1.创建新候选人                    2.创建新用户         **\n");
        printf("**  3.查询候选人信息                  4.浏览所有候选人     **\n");
        printf("**  5.整理所有投票                    6.清空候选人          **\n");
        printf("**                   0.退出                                **\n");
        scanf("%d", &key);
        switch (key)
        {
        case 1:addcandidate(); break;
        case 2:addUser(); break;
        case 3:search(); break;
        case 4:scan(); break;

        case 0:break;
        default:break;
        }
    } while (key != 0);
}







void main()
{

    FILE * fp=NULL;
    char DataFile[20]="用户.txt";
    char relogin;//是否重新登录的标志
    int success=0;
    user input_user,temp_user;
    printf("\n");
    printf("*************************************************************\n");
    printf("********************欢迎登录电子投票系统*********************\n");
    printf("*************************************************************\n");
    printf("*                                                           *\n");
again:
        printf("                请输入用户名:            &&");
        scanf("%s",input_user.name);
        printf("                  请输入密码:            &&");
        scanf("%s",input_user.password);
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

    while(fread(&total_user[User],sizeof(user),1,fp)!=(int)NULL)
    {
        User++;
    }


    fclose(fp);

     if(strcmp(input_user.name,"123")==0 && (strcmp(input_user.password,"123456")==0))//校验用户名和密码,若是管理员,并调用管理员界面
     {
            printf("\nlogin successful!");
            success=1;
            printf("\n\n\n\n\n\n\n         您是管理员!欢迎您登录系统!正在进入管理员界面...\n");
            main_guan();
        }
    else
    {

       for(i=0;i<30;i++)
       {



            if(strcmp(input_user.name,total_user[i].name)==0 && (strcmp(input_user.password,total_user[i].password)==0))
        {
            printf("\nlogin successful!");
            success=1;
            printf("\n\n\n\n\n\n\n         您是投票者!欢迎您登录系统!正在进入投票者界面...\n");
            main_tou();
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




