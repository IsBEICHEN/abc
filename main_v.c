#include"a.c"
void main_v()//ͶƱ���߽���
{
    system("color B");

    int key;
    do
    {
        system("cls");
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

    int a;
    long candidatenum;//������в���ʱ����ʱ�ṹ�����
    int i,flag;
    char DataFile[20]="DataFile.txt",next;// DataFile�洢��ѡ����Ϣ���ļ�����nextΪ�Ƿ������һ��Ͷ�������ѡ��
    candidate TempS;
    FILE *fp;

begin:
    system("cls");
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
            a=i;
            c_man[i].vote++;
        }
    }
    if(flag)
    {
        if(total_user[a].power>0)
        {

            printf("ͶƱ�ɹ�\n");
            total_user[a].power--;
            system("cls");
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
            printf("��û���㹻��Ʊ����");
            printf("�������������ҳ��             \n");
            getch();
            system("cls");
            return;
        }
    }
    else
    {
        system("cls");
        printf("ͶƱʧ�ܣ���ҪͶƱ�ĺ��벻����\n");
        printf("�������������ҳ��             \n");
        getch();
        system("cls");
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
void scan()//�����ѡ����Ϣ
{
    system("cls");

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
    system("cls");

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
void read()//��ȡ��ѡ����Ϣ
{

    system("cls");
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

