#include"a.c"
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
