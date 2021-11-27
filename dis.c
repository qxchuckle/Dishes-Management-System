//coding:GB2313
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>
#define SIZE1 100 //���ƣ��۸������
#define SIZE2 200 //������������

typedef struct _node
{
    char name[SIZE1];       //��Ʒ����
    char restaurant[SIZE1]; //��������
    float price;            //�˵ļ۸�
    int fraction;           //�˵�����
    char comment[SIZE2];    //��Ʒ����
    struct _node *next;
} Node;
typedef struct _list
{
    Node *head;
} List;
//�˵�
void menu(void);               //һ���˵�
void menu_inquire(List *list); //�����˵�_���Ҳ˵�
void help(void);               //�����˵�_�����˵�
void menu_sort(List *list);    //�����˵�_���򷽷�
//�Խڵ����
void add(List *list);     //��ӽڵ�
void delete (List *list); //ɾ���ڵ�
void revise(List *list);  //�޸Ľڵ�
//��ȫ����
char *s_gets(char *st, int n); //��ȫ�����ַ�
int get_int(void);             //��ȫ����int��
double get_double(void);       //��ȫ����double��
//��������
void inquire_all(List *list);        //�������ȫ���ڵ�
void inquire_one(List *list);        //�������ָ�������ڵ�
void inquire_restaurant(List *list); //�������ָ������ڵ�
//�ļ�����
void save(List *list);     //����
void read_txt(List *list); //��ȡ�ļ�_��ʼ����
//�����������
void sort_ascending(List *list);  //��Ʒ���۸�ӵ͵�������
void sort_descending(List *list); //��Ʒ���۸�Ӹߵ�������
void sort_score(List *list);      //��Ʒ�����ִӸߵ�������

//�������Ⱥ������������ʱ���Ⱥ�
int main() //������
{
    menu(); //������ܲ˵�
    //���濪����bug
    return 0;
}
void menu() //һ���˵�
{
    int options, z = 1;
    List list;
    list.head = NULL;
    FILE *fp = fopen("Menu.txt", "a");
    fclose(fp);
    read_txt(&list);
    while (z)
    {
        system("cls");
        printf("\n");
        printf("|-----------------------------------------------------\n");
        printf("|             �㶫�����ѧ*����У����Ʒ��Ϣϵͳ             \n");
        printf("|-----------------------------------------------------\n");
        printf("|********************ϵͳ���ܲ˵�*********************\n");
        printf("|-----------------------------------------------------\n");
        printf("|*******************|1��ʹ�ð���|                       \n");
        printf("|*******************|2����Ӳ�Ʒ��Ϣ|                    \n");
        printf("|*******************|3��ɾ����Ʒ��Ϣ|                    \n");
        printf("|*******************|4����ѯ��Ʒ��Ϣ|                    \n");
        printf("|*******************|5���޸Ĳ�Ʒ��Ϣ|                    \n");
        printf("|*******************|6������|\n");
        printf("|-----------------------------------------------------\n");
        printf("|*******************|0���˳�ϵͳ|                       \n");
        printf("|!����2,3,5�Ĳ���,ǰ���ȱ������˳�ϵͳ,�������ݻᶪʧ!\n");
        printf("|-----------------------------------------------------\n");
        printf("�����빦����ţ�");
        scanf("%d", &options);
        switch (options)
        {
        case 0:
            z = 0;
            printf("�����˳�ϵͳ��\n");
            break;
        case 1:
            help();
            break;
        case 2:
            add(&list);
            break;
        case 3:
            delete (&list);
            break;
        case 4:
            menu_inquire(&list);
            break;
        case 5:
            revise(&list);
            break;
        case 6:
            save(&list);
            break;
        default:
            printf("�޸ù��ܣ�����������:\n");
            system("pause");
        }
    }
    system("pause");
}
void help() //�����˵�_�����˵�
{
    system("cls");
    printf("\n");
    printf("|-----------------------------------------------------\n");
    printf("|ʹ�ð�����\n");
    printf("|1������Ʒ��Ϣϵͳ�ɹ��û������޸�����\n");
    printf("|2���������������Ϣ��������ɳ������\n");
    printf("|2���ر�ϵͳǰ�ǵñ��棡\n");
    printf("|3����bug��ϵ1934009145@qq.com\n");
    printf("|-----------------------------------------------------\n");
    printf("\n");
    system("pause");
}
void add(List *list) //��ӽڵ�
{
    Node *p1 = (Node *)malloc(sizeof(Node));
    p1->next = NULL;
    Node *last = list->head;
    system("cls");
    puts("��ʼ¼���Ʒ��\n----------------\n");
    getchar();
    puts("�������Ʒ���ƣ�");
    s_gets(p1->name, SIZE1);
    puts("�������Ʒ��������orʳ�����ƣ�");
    s_gets(p1->restaurant, SIZE1);
    puts("�������Ʒ�ļ۸�");
    p1->price = get_int();
    puts("������0-10�������Բ�Ʒ�������֣�");
    p1->fraction = get_int();
    puts("��Բ�Ʒ�������ۣ�");
    s_gets(p1->comment, SIZE2);
    if (last)
    {
        while (last->next)
        {
            last = last->next;
        }
        last->next = p1;
    }
    else
    {
        list->head = p1;//���lastΪNULL����Ҫ��headָ���һ���ڵ�
    }
    puts("¼��ɹ���");
    system("pause");
}
char *s_gets(char *st, int n) //��ȫ�����ַ�
{
    char *ret_val;
    char *find;

    ret_val = fgets(st, n, stdin);
    if (ret_val)
    {
        find = strchr(st, '\n'); //���һ��з�
        if (find)                //�����ַ����NULL
            *find = '\0';        //�ڴ˴�����һ�����ַ�
        else
            while (getchar() != '\n')
                continue;
    }
    return ret_val;
}
int get_int() //��ȫ����int��
{
    int input;
    char ch;

    while (scanf("%d%*c", &input) != 1)
    {
        while ((ch = getchar()) != '\n')
            putchar(ch);
        printf(" ����һ����������\n�����������룺\n");
    }
    return input;
}
void menu_inquire(List *list) //�����˵�_���Ҳ˵�
{
    List *p = list;
    int options, z = 1;
    if(list->head==NULL){
        printf ("��δ�����κβ�Ʒ���޷���ѯ��\n");
        system("pause");
        return;
    }
    while (z)
    {
        system("cls");
        printf("\n");
        printf("|-----------------------------------------------------\n");
        printf("|1����ѯȫ����Ʒ��Ϣ\n");
        printf("|2����������ѯ��Ʒ��Ϣ\n");
        printf("|3����ѯ�����ʳ�õĲ�Ʒ��Ϣ\n");
        printf("|0������\n");
        printf("|-----------------------------------------------------\n");
        printf("�����빦����ţ�");
        scanf("%d", &options);
        switch (options)
        {
        case 0:
            z = 0;
            break;
        case 1:
            menu_sort(p);
            inquire_all(p);
            return;
        case 2:
            inquire_one(p);
            return;
        case 3:
            menu_sort(p);
            inquire_restaurant(p);
            return;
        default:
            printf("�޸ù��ܣ�����������:\n");
            system("pause");
        }
    }
}
void inquire_all(List *list) //�������ȫ���ڵ�
{
    system("cls");
    Node *p;
    int n = 1;
    for (p = list->head; p; p = p->next)
    {
        printf("\n��%d����\n", n);
        printf("|����:%s\n", p->name);
        printf("|����:%s\n", p->restaurant);
        printf("|�۸�:%.2f\n", p->price);
        printf("|����:%d\n", p->fraction);
        printf("|����:%s\n", p->comment);
        n++;
    }
    printf("\n���в�Ʒ��ѯ���\n");
    system("pause");
}
double get_double() //��ȫ����double��
{
    double input;
    char ch;

    while (scanf("%lf%*c", &input) != 1)
    {
        while ((ch = getchar()) != '\n')
            putchar(ch);
        printf(" ����һ��������\n�����������룺\n");
    }
    return input;
}
void save(List *list) //����
{
    if(list->head==NULL){
        printf ("��δ�����κβ�Ʒ������Ϊ�գ�\n");
        system("pause");
        return;
    }
    Node *p = list->head;
    FILE *fp = fopen("Menu.txt", "w");
    if (fp)
    {
        while (p)
        {
            fprintf(fp, "\n%s %s %f %d %s", p->name, p->restaurant, p->price, p->fraction, p->comment);
            p = p->next;
        }
        fclose(fp);
        printf("\n����ɹ�\n");
        system("pause");
    }
    else
    {
        printf("����ʧ�ܣ����Բ����ϵ����");
    }
}
void read_txt(List *list) //��ȡ�ļ�_��ʼ����
{
    int i = 1;
    Node *last;
    Node *p1;
    int a = 1;
    char f[5];
    FILE *fp = fopen("Menu.txt", "r");
    fgets(f, 10, fp);
    while (!feof(fp))
    {
        last = list->head;
        p1 = (Node *)malloc(sizeof(Node));
        p1->next = NULL;
        fscanf(fp, "%s%s%f%d%s", p1->name, p1->restaurant, &p1->price, &p1->fraction, p1->comment);
        if (last)
        {
            while (last->next)
            {
                last = last->next;
            }
            last->next = p1;
        }
        else
        {
            list->head = p1;
        }
    }
    fclose(fp);
}
void inquire_one(List *list) //�������ָ�������ڵ�
{
    int n = 0;
    system("cls");
    printf("��������Ҫ�ҵĲ�Ʒ���ƣ�");
    getchar();
    char temp[SIZE1];
    s_gets(temp, SIZE1);
    Node *p;
    for (p = list->head; p; p = p->next)
    {
        if (!strcmp(temp, p->name))
        {
            printf("\n|����:%s\n", p->name);
            printf("|����:%s\n", p->restaurant);
            printf("|�۸�:%.2f\n", p->price);
            printf("|����:%d\n", p->fraction);
            printf("|����:%s\n", p->comment);
            n++;
        }
    }
    printf("\n�����ҵ�%d����\n", n);
    system("pause");
}
void inquire_restaurant(List *list) //�������ָ������ڵ�
{
    int n = 0;
    system("cls");
    printf("��������Ҫ�ҵķ����ʳ�ã�");
    getchar();
    char temp[SIZE1];
    s_gets(temp, SIZE1);
    Node *p;
    for (p = list->head; p; p = p->next)
    {
        if (!strcmp(temp, p->restaurant))
        {
            printf("\n");
            printf("|����:%s\n", p->name);
            printf("|����:%s\n", p->restaurant);
            printf("|�۸�:%.2f\n", p->price);
            printf("|����:%d\n", p->fraction);
            printf("|����:%s\n", p->comment);
            n++;
        }
    }
    printf("\n�����ҵ�%d����\n", n);
    system("pause");
}
void menu_sort(List *list) //�����˵�_���򷽷�
{
    List *p = list;
    int options, z = 1;
    while (z)
    {
        system("cls");
        printf("\n");
        printf("|-----------------------------------------------------\n");
        printf("|1�����۸�ӵ͵�������\n");
        printf("|2�����۸�Ӹߵ�������\n");
        printf("|3�������ִӸߵ�������\n");
        printf("|4��������\n");
        printf("|0������\n");
        printf("|-----------------------------------------------------\n");
        printf("�����빦����ţ�");
        scanf("%d", &options);
        switch (options)
        {
        case 0:
            z = 0;
            break;
        case 1:
            sort_ascending(p);
            return;
        case 2:
            sort_descending(p);
            return;
        case 3:
            sort_score(p);
            return;
        case 4:
            return;
        default:
            printf("�޸ù��ܣ�����������:\n");
            system("pause");
        }
    }
}
void sort_ascending(List *list) //��Ʒ���۸�ӵ͵�������
{
    int n = 0, i, k, num;
    Node *p1 = list->head;
    Node *p2, *p3, *p4;
    while (p1->next != NULL) //������ڵ�ĸ���
    {
        n++;
        p1 = p1->next;
    }
    //�������ð��������ָ��ָȥ������һ����д�굽�����ģ������ע���ˣ�Ӧ�û��и��õ��㷨�����������Ժ��Ż�
    for (i = 0; i < n; i++)
    {
        p1 = list->head; //��ǰ
        p2 = NULL;       //ǰһ��
        p3 = p1->next;   //��һ��
        for (k = 0; k < n - i; k++)
        {
            if (p1->price > p3->price)
            {
                if (p2)
                {
                    p2->next = p1->next;
                    p1->next = p3->next;
                    p3->next = p1;
                }
                else
                {
                    list->head = p1->next;
                    p1->next = p3->next;
                    p3->next = p1;
                }
                p2 = p3;
                p3 = p1->next;
            }
            else
            {
                if (p2)
                {
                    p1 = p1->next;
                    p3 = p1->next;
                    p2 = p2->next;
                }
                else
                {
                    p1 = p1->next;
                    p3 = p1->next;
                    p2 = list->head;
                }
            }
        }
    }
}
void sort_descending(List *list) //��Ʒ���۸�Ӹߵ�������
{
    int n = 0, i, k, num;
    Node *p1 = list->head;
    Node *p2, *p3, *p4;
    while (p1->next != NULL) //������ڵ�ĸ���
    {
        n++;
        p1 = p1->next;
    }
    //�������ð��������ָ��ָȥ������һ����д�굽�����ģ������ע���ˣ�Ӧ�û��и��õ��㷨�����������Ժ��Ż�
    for (i = 0; i < n; i++)
    {
        p1 = list->head; //��ǰ
        p2 = NULL;       //ǰһ��
        p3 = p1->next;   //��һ��
        for (k = 0; k < n - i; k++)
        {
            if (p1->price < p3->price)
            {
                if (p2)
                {
                    p2->next = p1->next;
                    p1->next = p3->next;
                    p3->next = p1;
                }
                else
                {
                    list->head = p1->next;
                    p1->next = p3->next;
                    p3->next = p1;
                }
                p2 = p3;
                p3 = p1->next;
            }
            else
            {
                if (p2)
                {
                    p1 = p1->next;
                    p3 = p1->next;
                    p2 = p2->next;
                }
                else
                {
                    p1 = p1->next;
                    p3 = p1->next;
                    p2 = list->head;
                }
            }
        }
    }
}
void sort_score(List *list) //��Ʒ�����ִӸߵ�������
{
    int n = 0, i, k, num;
    Node *p1 = list->head;
    Node *p2, *p3, *p4;
    while (p1->next != NULL) //������ڵ�ĸ���
    {
        n++;
        p1 = p1->next;
    }
    //�������ð��������ָ��ָȥ������һ����д�굽�����ģ������ע���ˣ�Ӧ�û��и��õ��㷨�����������Ժ��Ż�
    for (i = 0; i < n; i++)
    {
        p1 = list->head; //��ǰ
        p2 = NULL;       //ǰһ��
        p3 = p1->next;   //��һ��
        for (k = 0; k < n - i; k++)
        {
            if (p1->fraction < p3->fraction)
            {
                if (p2)
                {
                    p2->next = p1->next;
                    p1->next = p3->next;
                    p3->next = p1;
                }
                else
                {
                    list->head = p1->next;
                    p1->next = p3->next;
                    p3->next = p1;
                }
                p2 = p3;
                p3 = p1->next;
            }
            else
            {
                if (p2)
                {
                    p1 = p1->next;
                    p3 = p1->next;
                    p2 = p2->next;
                }
                else
                {
                    p1 = p1->next;
                    p3 = p1->next;
                    p2 = list->head;
                }
            }
        }
    }
}
void delete (List *list) //ɾ���ڵ�
{
    if(list->head==NULL){
        printf ("��δ�����κβ�Ʒ��ɾ��ʧ�ܣ�\n");
        system("pause");
        return;
    }
    system("cls");
    printf("��������Ҫɾ���Ĳ�Ʒ���ƣ�");
    getchar();
    char temp[SIZE1];
    s_gets(temp, SIZE1);
    Node *p, *q;
    for (q = NULL, p = list->head; p; q = p, p = p->next)
    {
        if (!strcmp(temp, p->name))
        {
            if (q)
            {
                q->next = p->next;
            }
            else
            {
                list->head = p->next;
            }
            free(p);
        }
    }
    printf("\nɾ���ɹ�\n");
    system("pause");
}
void revise(List *list) //�޸Ľڵ�
{
    if(list->head==NULL){
        printf ("��δ�����κβ�Ʒ���޷��޸ģ�\n");
        system("pause");
        return;
    }
    system("cls");
    printf("������Ҫ�޸ĵĲ�Ʒ�����ƣ�");
    getchar();
    char temp[SIZE1];
    s_gets(temp, SIZE1);
    Node *p, *q;
    for (q = NULL, p = list->head; p; q = p, p = p->next)
    {
        if (!strcmp(temp, p->name))
        {
            printf("\nԭ���Ĳ�Ʒ��Ϣ:\n");
            printf("|����:%s\n", p->name);
            printf("|����:%s\n", p->restaurant);
            printf("|�۸�:%.2f\n", p->price);
            printf("|����:%d\n", p->fraction);
            printf("|����:%s\n", p->comment);
            printf("\n");
            puts("�������Ʒ��������orʳ�����ƣ�");
            s_gets(p->restaurant, SIZE1);
            puts("�������Ʒ�ļ۸�");
            p->price = get_int();
            puts("������0-10�������Բ�Ʒ�������֣�");
            p->fraction = get_int();
            puts("��Բ�Ʒ�������ۣ�");
            s_gets(p->comment, SIZE2);
        }
    }
    printf("\n�޸����\n");
    system("pause");
}