#include"a.c"
void main()
{

    FILE * fp=NULL;
    char DataFile[20]="�û�.txt";
    char relogin;//�Ƿ����µ�¼�ı�־
    int success=0;
    user input_user,temp_user;
    system("color 1");
    printf("\n");
    printf("*************************************************************\n");
    printf("********************��ӭ��¼����ͶƱϵͳ*********************\n");
    printf("*************************************************************\n");
    printf("*                                                           *\n");
again:
        printf("                �������û���:            &&");
        scanf("%s",input_user.name);
        printf("                  ����������:            &&");
        scanf("%s",input_user.ps);
        printf("*************************************************************\n");

    fflush(stdin);

     fp=fopen("�û�.txt","rb");//����ԭʼ����,���ڼ�������Ƿ����ظ�

    if(fp==NULL)
    {
        printf("\nOpen file %s fail! ��������� \n",DataFile);
        perror("Open file fail");
        getch();
        exit(1);
    }

    while(fread(&total_user[total],sizeof(user),1,fp)!=(int)NULL)
    {
        total++;
    }


    fclose(fp);

     if(strcmp(input_user.name,"123")==0 && (strcmp(input_user.ps,"123456")==0))//У���û���������,���ǹ���Ա,�����ù���Ա����
     {
            printf("\nlogin successful!");
            success=1;
            system("cls");
            printf("\n\n\n\n\n\n\n         ���ǹ���Ա!��ӭ����¼ϵͳ!���ڽ������Ա����...\n");
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
            printf("\n\n\n\n\n\n\n         ����ͶƱ��!��ӭ����¼ϵͳ!���ڽ���ͶƱ�߽���...\n");
            main_v();
        }

       }

    }
    fclose(fp);
    if(success==0)
    {
        printf("%d",c_total);
        fflush(stdin);//�ļ����ݸ���
        printf("%d",c_total);
        system("cls");
        printf("\n�û�����������󣡼�����������(Y)/��(N): ");
        fflush(stdin);

        relogin=getchar();
        if((relogin=='Y')||(relogin=='y'))
        {
            goto again;
        }
        else
        {
            printf("����\n");
            exit(0);
        }
    }


}
