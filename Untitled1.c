#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

#define N 30



/*
����Ա�û���123  ����123
*/


/*
�������ļ�������
    r 	ֻ�������ļ������ڷ��ؿ�ָ��
    w 	ֻд�����ļ����ڣ���ɾ�������ݣ����򴴽�һ�����ļ�
    a 	׷�ӡ����ļ������ڣ��򴴽�һ�����ļ�
    r+ 	��д��ָ�����ļ������Ѵ��ڣ����򷵻�NULL
    w+ 	��д����ָ�����ļ��Ѵ��ڣ������е����ݱ�ɾȥ
    a+  ��д��׷��д��
*/

void main_guan();           //����Ա����
void main_tou();            //ͶƱ�˽���
void scan();                //�����ѡ����Ϣ
void search();              //��ѯ��ѡ����Ϣ
void addcandidate();        //�����µĺ�ѡ��
void addUser();             //�������û�
void sort();                //����ͶƱ���
void effectivevoting();     //��ѯ��ЧͶƱ��
void empty();               //������к�ѡ����Ϣ
void Votexiugai();          //Ʊ������
void read();                //��ȡ��ѡ����Ϣ


int c_total = 0;
int i = 0;
int User = 0;


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
    int username;//ͶƱ���˺�
    int password;
}user;


candidate c_man[N];
user total_user[N];



void read()//��ȡ��ѡ����Ϣ
{


    char DataFile[20] = "DataFile.txt";
    FILE* fp = NULL;
    c_total = 0;
    fp = fopen(DataFile, "rb");
    if (fp == NULL)
    {
        printf("\nOpen file %s fail! ��������� \n", DataFile);
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


void scan()//�����ѡ����Ϣ
{

    read();
    int i;
    printf("��ѡ�����ϣ�\n");

    printf("***************************************************************\n");

    for (i = 0; i < c_total; i++)
    {
        printf("����:%-15ld", c_man[i].number);
        printf("����:%-19s", c_man[i].name);
        printf("���:%s\n", c_man[i].intro);
    }
    printf("***************************************************************");
    printf("\n�������������ҳ��");
    getch();
}


void search() //��ѯ��ѡ����Ϣ
{

    char c;

    long number;

    int flag = 0;

    read();

    do
    {
        printf("\n\t������Ҫ��ѯ�ĺ�ѡ�˺���:");
        scanf("%ld", &number);
        for (i = 0; i < c_total; i++)
        {
            if (number == c_man[i].number)
            {
                printf("\t��Ҫ��ѯ�ĺ�ѡ����Ϣ����:\n\n");
                printf("\t����:%ld \n", c_man[i].number);
                printf("\t����:%s \n", c_man[i].name);
                printf("\t���:%s \n", c_man[i].intro);
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
            printf("\t�Բ���û����Ҫ��ѯ�ĺ�ѡ��\n");
        }
        printf("\tҪ������ѯ��ѡ����?��(Y)/��(N): ");
        getchar();
        c = getchar();
    } while ((c == 'Y') || (c == 'y'));
}


void vote() //ͶƱ��ͶƱ
{
    int flag = 0;//��������Ƿ�ͶƱ�ɹ�
    long candidatenum;//������в���ʱ����ʱ�ṹ�����
    char DataFile[20] = "DataFile.txt";// DataFile�洢��ѡ����Ϣ���ļ���
    FILE* fp;

    read();
    printf("��������ҪͶƱ�ĺ�ѡ�˵ĺ���:");
    scanf("%ld", &candidatenum);
    printf("����ͶƱ�ĺ�ѡ�˺�����:%ld\n", candidatenum);
    for (i = 0; i < c_total; i++)
    {
        if (c_man[i].number == candidatenum)
            flag = 1;
    }
    if (flag)
    {
        printf("ͶƱ�ɹ�\n");


        fp = fopen(DataFile, "wb");

        if (fp == NULL)//�����ǰ�ļ������ڣ���ʾ���ļ�ʧ��
        {
            printf("\nOpen file is fail!End with any key.\n", DataFile);
            perror("Open file fail");   //������ԭ���������Ļ��
            getch();
            exit(1);
        }
        for (i = 0; i < c_total; i++)          //�޸ĺ�ѡ�˵�Ʊ������
        {

            fwrite(&c_man[i], sizeof(candidate), 1, fp);
            /*
            {
            �˴���һ��fwrite�������÷�
            fwrite(const void*buffer,size_t size,size_t count,FILE*stream);
            ��1��buffer����һ��ָ�룬��fwrite��˵����Ҫ������ݵĵ�ַ��
            ��2��size��Ҫд����ֽ�����
            ��3��count:Ҫ����д��size�ֽڵ�������ĸ�����
            ��4��stream:Ŀ���ļ�ָ�롣
            }
            */
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

    fp = fopen(DataFile, "rb");// ��ͶƱ��������ʾ����Ļ��

    fclose(fp); //�ر��ļ�


}

void main_tou() //ͶƱ�߽���
{
    int key;
    do
    {
        printf("*************************************************************\n");
        printf("**********************��ӭ����ͶƱ����***********************\n");
        printf("**********************��ѡ�����Ĳ�����***********************\n");
        printf("*************************************************************\n");
        printf("****   1.�����ѡ����Ϣ               2.��ѯ��ѡ����Ϣ   ****\n");
        printf("*************************************************************\n");
        printf("****   3.ͶƱ                         4.�˳�             ****\n");
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


void addUser()//�������û�


{
    FILE* fp = NULL;
    user TempS;
    char DataFile[20] = "�û�.txt";
    fp = fopen("�û�.txt", "rb");//����ԭʼ����,���ڼ�������Ƿ����ظ�

    if (fp == NULL)
    {
        printf("\nOpen file %s fail! ��������� \n", DataFile);
        perror("Open file fail");
        getch();
        exit(1);
    }

    fclose(fp);
    fopen("�û�.txt", "ab+");
    printf("**************************������û�***************************\n");
    printf("������ͶƱ���û�����");
    scanf("%s", &TempS.username);
    if (User != 0)
    {
        for (i = 0; i < User; i++)
        {
            if (strcmp(TempS.username, total_user[i].username) == 0)
            {
                printf("���û����Ѵ��ڣ����������������û�...");
                getch();
                break;
            }
        }
    }
    printf("������ͶƱ�˵�������");
    scanf("%d", &TempS.name);
    total_user[User] = TempS;//�����ݼ���ԭʼ����
    User++;

    if (fwrite(&TempS, sizeof(user), 1, fp) != 1)
    {
        printf("\nwrite file is fail! ���������\n", DataFile);

        perror("write file fail");

        getch();

        exit(1);
    }
    fclose(fp);

    printf("�û��������ݴ������.\n");//����Ļ����ʾ�ļ�����

    fclose(fp);



    printf("\n�������������ҳ��\n");

    getch();
}


void addcandidate()//�����º�ѡ��
{
    FILE* fp;
    char DataFile[20] = "DataFIle.txt";
    candidate TempS;

    read();
    fp = fopen(DataFile, "ab+");

    printf("**************************�����µĺ�ѡ��**************************\n");
    printf("****�������ѡ������:");
    scanf("%s",&TempS.name);
    printf("\n��ӳɹ�");
    printf("****�������ѡ�˱��:");
    scanf("%ld",&TempS.number);
    printf("\n��ӳɹ�");
    for (i = 0; i < c_total; i++)
    {
        if (TempS.number == c_man[i].number)
        {
            printf("����ظ�");
            getch();
            break;
        }

    }

    printf("        ���:");
    fflush(stdin);
    gets(TempS.intro);
    TempS.intro[399] = '\0';
    TempS.vote = 0;
    c_man[c_total] = TempS;//�����ݼ���ԭʼ����,������һ������Ƚ�
    c_total++;
    if (fwrite(&TempS, sizeof(candidate), 1, fp) != 1)
    {
        printf("\nwrite file is fail! End with any key\n", DataFile);
        perror("write file fail");
        getch();
        exit(1);
    }


}


void main_guan()//����Ա����
{

    int key;
    do
    {
        printf("*************************************************************\n");
        printf("********************��ӭ�������Ա����***********************\n");
        printf("*************************************************************\n");
        printf("**  1.�����º�ѡ��                    2.�������û�         **\n");
        printf("**  3.��ѯ��ѡ����Ϣ                  4.������к�ѡ��     **\n");
        printf("**  5.��������ͶƱ                    6.��պ�ѡ��          **\n");
        printf("**                   0.�˳�                                **\n");
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
    char DataFile[20]="�û�.txt";
    char relogin;//�Ƿ����µ�¼�ı�־
    int success=0;
    user input_user,temp_user;
    printf("\n");
    printf("*************************************************************\n");
    printf("********************��ӭ��¼����ͶƱϵͳ*********************\n");
    printf("*************************************************************\n");
    printf("*                                                           *\n");
again:
        printf("                �������û���:            &&");
        scanf("%s",input_user.name);
        printf("                  ����������:            &&");
        scanf("%s",input_user.password);
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

    while(fread(&total_user[User],sizeof(user),1,fp)!=(int)NULL)
    {
        User++;
    }


    fclose(fp);

     if(strcmp(input_user.name,"123")==0 && (strcmp(input_user.password,"123456")==0))//У���û���������,���ǹ���Ա,�����ù���Ա����
     {
            printf("\nlogin successful!");
            success=1;
            printf("\n\n\n\n\n\n\n         ���ǹ���Ա!��ӭ����¼ϵͳ!���ڽ������Ա����...\n");
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
            printf("\n\n\n\n\n\n\n         ����ͶƱ��!��ӭ����¼ϵͳ!���ڽ���ͶƱ�߽���...\n");
            main_tou();
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




