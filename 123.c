#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>


#define closegr closegraph
#define N 30


void main_a(); //����Ա����
void main_v(); //ͶƱ���߽���
void addcandidate(); // ������ѡ��
void addUser();//����ͶƱ��
void search(); //��ѯ��ѡ����Ϣ
void scan();//�����ѡ����Ϣ
void vote();  //ͶƱ��ͶƱ
void read();//��ȡ��ѡ����Ϣ
void save();//�洢��ѡ����Ϣ
void sort();//��������ͶƱ
void effectivevoting();//��ЧͶƱ��
void empty();//��պ�ѡ��

void Votexiugai();//Ʊ���޸�

int total=0;
int c_total=0;
int i=0;



typedef struct candidate//��ѡ�����ݽṹ��
{
    long number;//��ѡ�˱��
    char name[20];//��ѡ������
    char intro[400];//��ѡ�˼��
    int vote;//��ѡ�˵�Ʊ��
}candidate;



typedef struct user//ͶƱ�����ݽṹ��
{
  char name[20];//ͶƱ������
  char ps[8];//��Ӧ����
  int power;//Ȩ��
}user;



candidate c_man[N];
user total_user[N];




void main_v()//ͶƱ���߽���
{


    int key;
    do
    {
        printf("*************************************************************\n");
        printf("********************��ӭ����ͶƱԱ����***********************\n");
        printf("*************************************************************\n");
        printf("**  1.������к�ѡ��              2.��ѯ��ѡ����Ϣ         **\n");
        printf("**  3.ͶƱ                        4.�˳�                   **\n");
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

void vote()  //ͶƱ��ͶƱ
{


    long candidatenum;//������в���ʱ����ʱ�ṹ�����
    int i,flag;
    char DataFile[20]="DataFile.txt",next;// DataFile�洢��ѡ����Ϣ���ļ�����nextΪ�Ƿ������һ��Ͷ�������ѡ��
    candidate TempS;
    FILE *fp;

begin:

    flag=0;//flag������־�Ƿ��Ҷ�Ӧ��ţ���ͶƱ�Ƿ�ɹ�
    read();
    printf("��������ҪͶƱ�ĺ�ѡ�˵ĺ���:");
    scanf("%ld",&candidatenum);
    printf("����ͶƱ�ĺ�ѡ�˺�����:%ld\n",candidatenum);
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
        printf("ͶƱ�ɹ�\n");


        fp=fopen(DataFile,"wb");

        if(fp==NULL)//�����ǰ�ļ������ڣ���ʾ���ļ�ʧ��
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
        printf("ͶƱʧ�ܣ���ҪͶƱ�ĺ��벻����\n");
        printf("�������������ҳ��             \n");
        getch();
        return;
    }
    fp=fopen(DataFile,"rb");// ��ʾͶƱ������


    if(fp==NULL)
    {
        printf("\nOpen file %s fail! End With any key \n",DataFile);
        perror("Open file fail");
        getch();
        exit(1);
    }

        printf("����������ͶƱ���:\n");
        printf("\n��ѡ�˺���     \t��ѡ������      \tƱ��\n");//"\t"  ����������һ�Ʊ��λ��

    while(fread(&TempS,sizeof(candidate),1,fp)!=(int)NULL)
    {
        if(TempS.number!=0)

        printf("\n%ld            \t%s              \t%d \n",TempS.number,TempS.name,TempS.vote);
    }

    fclose(fp);

    printf("\n������?��(Y)/��(N): ");

    fflush(stdin);

    next=getchar();

    putchar('\n');

    if(next=='y'||next=='Y')goto begin;

}

void main_a()//����Ա����
{

    int key;
    do
    {
        printf("*************************************************************\n");
        printf("********************��ӭ�������Ա����***********************\n");
        printf("*************************************************************\n");
        printf("**  1.�����º�ѡ��                    2.�������û�         **\n");
        printf("**  3.��ѯ��ѡ����Ϣ                  4.������к�ѡ��     **\n");
        printf("**  5.��������ͶƱ                    6.��ЧͶƱ��         **\n");
        printf("**  7.��պ�ѡ����Ϣ                  8.Ʊ������           **\n");
        printf("**                   0.�˳�                                **\n");
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

void addcandidate()//������ѡ��
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
      printf("                 *****************�����º�ѡ��*****************\n");
      printf("������:");

      printf("��ѡ�˺���:");scanf("%ld",&TempS.number);
        for(i=0;i<c_total;i++)//����������Ƿ����ظ�
        {
            if(TempS.number==c_man[i].number)
            {
                printf("�ú����Ѵ���.�������������к�ѡ��...");
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
        printf("        ����:");scanf("%s",&TempS.name);

        TempS.name[19]='\0';

        for(i=0;i<c_total;i++)
        {
            if(strcmp(TempS.name,c_man[i].name)==0)
            {
                printf("�������Ѵ��ڣ���������һ�Σ������������...");
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
        printf("        ���:");
        fflush(stdin);
        gets(TempS.intro);
        TempS.intro[399]='\0';
        TempS.vote=0;
        c_man[c_total]=TempS;//�����ݼ���ԭʼ����,������һ������Ƚ�
        c_total++;
        if(fwrite(&TempS,sizeof(candidate),1,fp)!=1)
        {
            printf("\nwrite file is fail! End with any key\n",DataFile);
            perror("write file fail");
            getch();
            exit(1);
        }
        printf("Ҫ���������µĺ�ѡ����?��(Y)/��(N): ");

        fflush(stdin);

        c=getchar();

    }while(c=='Y'||c=='y');


    fclose(fp);
    printf("��ѡ�����ϣ�\n");    // ����Ļ����ʾ�ļ�����
    printf("*****************************************************************");
    fp=fopen(DataFile,"rb");
    if(fp==NULL)
    {
        printf("\nOpen file %s fail! ��������� \n",DataFile);
        perror("Open file fail");
        getch();
        exit(1);
    }
    while(fread(&TempS,sizeof(candidate),1,fp)!=(int)NULL)
    {
        printf("\n����:%-15ld����:%-15s���:%s",TempS.number,TempS.name,TempS.intro);
    }
    fclose(fp);
    printf("\n*****************************************************************");
    printf("\n�������������ҳ��\n");
    getch();
}

void read()//��ȡ��ѡ����Ϣ
{


    char DataFile[20]="DataFile.txt";
    FILE * fp=NULL;
    c_total=0;
    fp=fopen(DataFile,"rb");
    if(fp==NULL)
    {
        printf("\nOpen file %s fail! ��������� \n",DataFile);
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

void addUser()//�����û�
{

    FILE *fp=NULL;
    char DataFile[20]="�û�.txt";//�洢ͶƱ����Ϣ���ļ���
    user TempS;
    int over_flag=0;
    char c;
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
    fp=fopen(DataFile,"ab+");
    do
    {
        printf("                *****************�������û�*****************                   ");
        printf("������:");
        printf("�û���:");scanf("%s",&TempS.name);
        TempS.name[19]='\0';
        for(i=0;i<total;i++)//������������Ƿ����ظ�
        {
            if(strcmp(TempS.name,total_user[i].name)==0)
            {
                printf("���û����Ѵ��ڣ����������������û�...");
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
        printf("  ����:");

        scanf("%s",&TempS.ps);

        TempS.ps[7]='\0';

        printf("  Ȩ��:");

        scanf("%d",&TempS.power);

        if(TempS.power!=1)
        {
            TempS.power=0;
        }
        total_user[total]=TempS;//�����ݼ���ԭʼ����

        total++;

        if(fwrite(&TempS,sizeof(user),1,fp)!=1)
        {
            printf("\nwrite file is fail! ���������\n",DataFile);

            perror("write file fail");

            getch();

            exit(1);
        }
        printf("Ҫ�����������û���?��(Y)/��(N):");
        getchar();

        c=getchar();

    }while(c=='Y'||c=='y');

    fclose(fp);

    printf("�û��������ݴ������.\n",DataFile);//����Ļ����ʾ�ļ�����

    printf("�����û������������:\n");

    fp=fopen(DataFile,"rb");

    printf("************************************************************");
    if(fp==NULL)
    {
        printf("\nOpen file is fail! End With any key \n",DataFile);

        perror("Open file fail");//��������Ϣ���

        getch();

        exit(1);
    }
    printf("\n����\t\t����\t\tȨ��\n");

    while(fread(&TempS,sizeof(user),1,fp)!=(int)NULL)
    {
        printf("\n%s\t\t%-8s\t\t%d\n",TempS.name,TempS.ps,TempS.power);
    }
    fclose(fp);

    printf("************************************************************");

    printf("\n�������������ҳ��\n");

    getch();

}

void scan()//�����ѡ����Ϣ
{

    read();

    printf("��ѡ�����ϣ�\n");

    printf("***************************************************************\n");

    for(i=0;i<c_total;i++)
    {
        printf("����:%-15ld",c_man[i].number);
        printf("����:%-19s",c_man[i].name);
        printf("���:%s\n",c_man[i].intro);
    }
    printf("***************************************************************");
    printf("\n�������������ҳ��");
    getch();
}

void search() //��ѯ��ѡ����Ϣ
{

    char c;

    long number;

    int flag=0;

    read();

    do
    {
        printf("\n\t������Ҫ��ѯ�ĺ�ѡ�˺���:");
        scanf("%ld",&number);
        for(i=0;i<c_total;i++)
        {
            if(number==c_man[i].number)
            {
                printf("\t��Ҫ��ѯ�ĺ�ѡ����Ϣ����:\n\n");
                printf("\t����:%ld \n",c_man[i].number);
                printf("\t����:%s \n",c_man[i].name);
                printf("\t���:%s \n",c_man[i].intro);
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
            printf("\t�Բ���û����Ҫ��ѯ�ĺ�ѡ��\n");
        }
            printf("\tҪ������ѯ��ѡ����?��(Y)/��(N): ");
        getchar();
        c=getchar();
    }while((c=='Y')||(c=='y'));
}

void sort()//��������ͶƱ
{

    int i,k,j;

    candidate c_man2[N]/*������������� */,   temp;
    read();
    for(i=0;i<c_total;i++)
       c_man2[i]=c_man[i];
    for(i=0;i<c_total-1;i++)//��ѡ������
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
    } //�������
    printf("Ʊ���Ӹߵ�����������:\n");
    printf("***********************************************\n");
    printf("*����           ��ѡ��           Ʊ��         *\n");
    printf("***********************************************\n");
    for(i=0;i<c_total;i++)       //��������Ľ��
    {
       printf("* %-13ld %-13s    %-6d       *\n",c_man2[i].number,c_man2[i].name,c_man2[i].vote);
    }
    printf("***********************************************\n");
    printf("�������������ҳ��\n");
    fflush(stdin);
    getch();
}
void effectivevoting()//��ЧͶƱ��--
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
  printf("��ЧͶƱ��Ϊ��%ld\n",sum);
}


void empty()//��պ�ѡ��
{
     FILE * fp;
    fp = fopen("DataFile.txt", "w");//��ֻд��ʽ���ļ�ʱ ��ʵ���Ǵ�����һ�����ļ�(�յ�)�� ������������ļ���Ҳͬ���ᱻ����
    if(fp == NULL)
        printf("do empty file %s failed\n", fp);
    else fclose(fp);
     printf("����������\n");


}
void main()
{

    FILE * fp=NULL;
    char DataFile[20]="�û�.txt";
    char relogin;//�Ƿ����µ�¼�ı�־
    int success=0;
    user input_user,temp_user;
    printf("����Ա�˺ţ�����  ���붼Ϊ123456\n");
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

     if(strcmp(input_user.name,"����")==0 && (strcmp(input_user.ps,"123456")==0))//У���û���������,���ǹ���Ա,�����ù���Ա����
     {
            printf("\nlogin successful!");
            success=1;
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

void read1()
{
    char DataFile[20]="DataFile.txt";
    FILE * fp=NULL;
    c_total=0;
    fp=fopen(DataFile,"rb");
    if(fp==NULL)
    {
        printf("\nOpen file %s fail! ��������� \n",DataFile);
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

void Votexiugai()//Ʊ���޸�
{
    long candidatenum;//������в���ʱ����ʱ�ṹ�����
    int i,flag;
    char DataFile[20]="DataFile.txt",next;// DataFile�洢��ѡ����Ϣ���ļ�����nextΪ�Ƿ������һ��Ͷ�������ѡ��
    candidate TempS;
    FILE *fp;


begin:

    flag=0;//flag������־�Ƿ��Ҷ�Ӧ���
    read();



    for(i=0;i<c_total;i++)
    {


            flag=1;
            c_man[i].vote=0;

    }
    if(flag)
    {
        printf("�޸ĳɹ�\n");


        fp=fopen(DataFile,"wb");

        if(fp==NULL)//�����ǰ�ļ������ڣ���ʾ���ļ�ʧ��
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

    fp=fopen(DataFile,"rb");// ��ʾͶƱ������


    if(fp==NULL)
    {
        printf("\nOpen file %s fail! End With any key \n",DataFile);
        perror("Open file fail");
        getch();
        exit(1);
    }

    printf("����������ͶƱ���:\n");
        printf("\n��ѡ�˺���     \t��ѡ������      \tƱ��\n");//"\t"  ����������һ�Ʊ��λ��
    while(fread(&TempS,sizeof(candidate),1,fp)!=(int)NULL)
    {
        if(TempS.number!=0)
        printf("\n%ld            \t%s              \t%d \n",TempS.number,TempS.name,TempS.vote);
    }
    fclose(fp);
    printf("\n������?��(Y)/��(N): ");
    fflush(stdin);
    next=getchar();
    putchar('\n');
    if(next=='y'||next=='Y')goto begin;
}
