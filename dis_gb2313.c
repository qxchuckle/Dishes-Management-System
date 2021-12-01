//coding:GB2313
//There will be bugs if you don't use gb2313
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define SIZE1 100 //���ƣ��۸������
#define SIZE2 200 //������������

typedef struct _node//����Ľڵ�ṹ��
{
    char name[SIZE1];       //��Ʒ����
    char restaurant[SIZE1]; //��������
    float price;            //�˵ļ۸�
    int fraction;           //�˵�����
    char comment[SIZE2];    //��Ʒ����
    struct _node *next;
} Node;
typedef struct _list//������������
{
    Node *head;
    Node *pa;
    Node *pb;
    Node *pc;
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
void inquire_all(List *list);           //�������ȫ���ڵ�
void inquire_one(List *list);           //�������ָ�������ڵ�
void inquire_restaurant(List *list);    //�������ָ������ڵ�
void inquire_part_price(List *list);    //���һ���۸����µĲ�Ʒ(�⹦�ܡ���ƶ��)
void inquire_part_fraction(List *list); //���һ���������ϵĲ�Ʒ
void output(Node *p);                   //�������
//�ļ�����
void save(List *list);     //����
void read_txt(List *list); //��ȡ�ļ�_��ʼ����
//�����������
void sort_ascending(List *list);  //��Ʒ���۸�ӵ͵�������
void sort_descending(List *list); //��Ʒ���۸�Ӹߵ�������
void sort_score(List *list);      //��Ʒ�����ִӸߵ�������
int calculate(List *list);        //�����������Ľڵ����
void swap1(List *list, List *list_swap);//������ð��������㷨��1
void swap2(List *list, List *list_swap);//������ð��������㷨��2
//______________________________________________________
//------------------------------------------------------
int main() //������
{
    //system("chcp 65001");//GB2313
    //system("chcp 936");//UTF8
    //system("cls");
    menu(); //������ܲ˵�
    //���濪����bug
    return 0;
}
//�˵�
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
        options = get_int();
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
    printf("|-----------------------------------------------------------------\n");
    printf("|ʹ�ð�����\n");
    printf("|1������Ʒ��Ϣϵͳ�ɹ��û������޸�����\n");
    printf("|2����Ϊ���ǵ���ͬ������ͬ�����ƵĲ�Ʒ����ϵͳ�����Ʒ�������ظ�\n");
    printf("|3���������������Ϣ��������ɳ������\n");
    printf("|4���ر�ϵͳǰ�ǵñ��棡�������ݻᶪʧ\n");
    printf("|5����bug��ϵ1934009145@qq.com\n");
    printf("|6����Դ��ַ:github.com/qxchuckle/Dishes-Management-System\n");
    printf("|-----------------------------------------------------------------\n");
    printf("\n");
    system("pause");
}
void menu_inquire(List *list) //�����˵�_���Ҳ˵�
{
    int options, z = 1;
    List *p = list;
    if (list->head == NULL)
    {
        printf("��δ�����κβ�Ʒ���޷���ѯ��\n");
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
        printf("|3����ѯ�����ʳ�õ�ȫ����Ʒ��Ϣ\n");
        printf("|4����ѯĳ�۸����µ�ȫ����Ʒ\n");
        printf("|5����ѯĳ�������ϵ�ȫ����Ʒ\n");
        printf("|0������\n");
        printf("|-----------------------------------------------------\n");
        printf("�����빦����ţ�");
        options = get_int();
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
        case 4:
            menu_sort(p);
            inquire_part_price(p);
            return;
        case 5:
            menu_sort(p);
            inquire_part_fraction(p);
            return;
        default:
            printf("�޸ù��ܣ�����������:\n");
            system("pause");
        }
    }
}
void menu_sort(List *list) //�����˵�_���򷽷�
{
    int options, z = 1;
    List *p = list;
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
        options = get_int();
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
//�Խڵ����
void add(List *list) //��ӽڵ�
{
    int n = 0, i = 0;
    Node *last = list->head;
    Node *p1 = (Node *)malloc(sizeof(Node));
    p1->next = NULL;
    system("cls");
    puts("��ʼ¼���Ʒ��\n----------------\n");
    puts("�������Ʒ���ƣ�");
    s_gets(p1->name, SIZE1);
    puts("�������Ʒ��������orʳ�����ƣ�");
    s_gets(p1->restaurant, SIZE1);
    puts("�������Ʒ�ļ۸�");
    p1->price = get_int();
    puts("������0-10�������Բ�Ʒ�������֣�");
    do
    {
        n = get_int();
        if (n >= 0 && n <= 10)
        {
            p1->fraction = n;
            i = 1;
        }
        else
        {
            puts("���ֲ��ڹ涨��Χ�ڣ������룺");
        }
    } while (!i);
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
        list->head = p1; //���lastΪNULL����Ҫ��headָ���һ���ڵ�
    }
    puts("¼��ɹ���");
    system("pause");
}
void delete (List *list) //ɾ���ڵ�
{
    int n = 0;
    char a[SIZE1];
    char b[SIZE1];
    Node *p, *q;
    if (list->head == NULL)
    {
        printf("��δ�����κβ�Ʒ��ɾ��ʧ�ܣ�\n");
        system("pause");
        return;
    }
    system("cls");
    printf("��������Ҫɾ���Ĳ�Ʒ���ƣ�");
    s_gets(a, SIZE1);
    printf("�������Ʒ�����������ƣ�");
    s_gets(b, SIZE1);
    for (q = NULL, p = list->head; p; q = p, p = p->next)
    {
        if (!(strcmp(a, p->name) || strcmp(b, p->restaurant)))
        {
            n++;
            if (q)
            {
                q->next = p->next;
            }
            else
            {
                list->head = p->next;
            }
        }
    }
    if (!n)
    {
        printf("\nû������ˣ�\n");
    }
    else
    {
        printf("\nɾ���ɹ�%d���ˡ�\n", n);
    }
    system("pause");
}
void revise(List *list) //�޸Ľڵ�
{
    int n = 0, m = 0, i = 0;
    char a[SIZE1];
    char b[SIZE1];
    Node *p, *q;
    if (list->head == NULL)
    {
        printf("��δ�����κβ�Ʒ���޷��޸ģ�\n");
        system("pause");
        return;
    }
    system("cls");
    printf("������Ҫ�޸ĵĲ�Ʒ�����ƣ�");
    s_gets(a, SIZE1);
    printf("�������Ʒ�����������ƣ�");
    s_gets(b, SIZE1);
    for (q = NULL, p = list->head; p; q = p, p = p->next)
    {
        if (!(strcmp(a, p->name) || strcmp(b, p->restaurant)))
        {
            n++;
            printf("\nԭ���Ĳ�Ʒ��Ϣ:\n");
            printf("|����:%s\n", p->name);
            printf("|����:%s\n", p->restaurant);
            printf("|�۸�:%.2f\n", p->price);
            printf("|����:%d\n", p->fraction);
            printf("|����:%s\n", p->comment);
            printf("\n");
            puts("���޸Ĳ�Ʒ�ļ۸�");
            p->price = get_int();
            puts("������0-10���������޸Ĳ�Ʒ�����֣�");
            do
            {
                m = get_int();
                if (m >= 0 && m <= 10)
                {
                    p->fraction = m;
                    i = 1;
                }
                else
                {
                    puts("���ֲ��ڹ涨��Χ�ڣ������룺");
                }
            } while (!i);
            puts("��Բ�Ʒ�������ۣ�");
            puts("���޸ĶԲ�Ʒ�����ۣ�");
            s_gets(p->comment, SIZE2);
        }
    }
    if (n)
    {
        printf("\n�޸���ɡ�\n");
    }
    else
    {
        printf("\nû������ˣ�\n");
    }
    system("pause");
}
//��ȫ����
char *s_gets(char *m, int n) //��ȫ�����ַ�
{
    char *p;
    char *find;
    p = fgets(m, n, stdin);
    if (p)
    {
        find = strchr(m, '\n'); //���һ��з�
        if (find)               //�����ַ����NULL
            *find = '\0';       //�ڴ˴�����һ�����ַ�
        else
            while (getchar() != '\n')
                continue;
    }
    return p;
}
int get_int() //��ȫ����int��
{
    int n;
    char ch;
    while (scanf("%d%*c", &n) != 1)
    {
        while ((ch = getchar()) != '\n')
            putchar(ch);
        printf(" ����һ����������\n�����������룺\n");
    }
    return n;
}
double get_double() //��ȫ����double��
{
    double n;
    char ch;

    while (scanf("%lf%*c", &n) != 1)
    {
        while ((ch = getchar()) != '\n')
            putchar(ch);
        printf(" ����һ��������\n�����������룺\n");
    }
    return n;
}
//��������
void inquire_all(List *list) //�������ȫ���ڵ�
{
    Node *p;
    int n = 1;
    system("cls");
    for (p = list->head; p; p = p->next)
    {
        printf("\n��%d����\n", n);
        output(p);
        n++;
    }
    printf("\n���в�Ʒ��ѯ���\n");
    system("pause");
}
void inquire_one(List *list) //���ָ������
{
    int n = 0;
    char a[SIZE1];
    Node *p;
    system("cls");
    printf("��������Ҫ�ҵĲ�Ʒ���ƣ�");
    s_gets(a, SIZE1);
    for (p = list->head; p; p = p->next)
    {
        if (!strcmp(a, p->name))
        {
            output(p);
            n++;
        }
    }
    printf("\n�����ҵ�%d����\n", n);
    system("pause");
}
void inquire_restaurant(List *list) //���ָ���������в�Ʒ
{
    int n = 0;
    char a[SIZE1];
    Node *p;
    system("cls");
    printf("��������Ҫ�ҵķ����ʳ�ã�");
    s_gets(a, SIZE1);
    for (p = list->head; p; p = p->next)
    {
        if (!strcmp(a, p->restaurant))
        {
            output(p);
            n++;
        }
    }
    printf("\n�����ҵ�%d����\n", n);
    system("pause");
}
void inquire_part_price(List *list) //���һ���۸����µĲ�Ʒ(�⹦�ܡ���ƶ��)
{
    int n = 0;
    double money;
    char a[SIZE1];
    Node *p;
    system("cls");
    printf("������ⶥ�۸�");
    money = get_double();
    for (p = list->head; p; p = p->next)
    {
        if (p->price <= money)
        {
            output(p);
            n++;
        }
    }
    printf("\n�����ҵ�%d����\n", n);
    system("pause");
}
void inquire_part_fraction(List *list) //���һ���������ϵĲ�Ʒ
{
    int n = 0;
    int score;
    char a[SIZE1];
    Node *p;
    system("cls");
    printf("������������֣�");
    score = get_int();
    for (p = list->head; p; p = p->next)
    {
        if (p->fraction >= score)
        {
            output(p);
            n++;
        }
    }
    printf("\n�����ҵ�%d����\n", n);
    system("pause");
}
void output(Node *p) //�������
{
    printf("\n|����:%s\n", p->name);
    printf("|����:%s\n", p->restaurant);
    printf("|�۸�:%.2f\n", p->price);
    printf("|����:%d\n", p->fraction);
    printf("|����:%s\n", p->comment);
}
//�ļ�����
void save(List *list) //����
{
    if (list->head == NULL)
    {
        printf("��δ�����κβ�Ʒ������Ϊ�գ�\n");
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
//�����������
void sort_ascending(List *list) //��Ʒ���۸�ӵ͵�������
{
    int n = 0, i, k, num;
    List *p = list;
    Node *p1 = list->head, *p2, *p3;
    List list_swap;
    n = calculate(p);
    list_swap.pa = p1;
    list_swap.pb = p2;
    list_swap.pc = p3;
    //�������ð��������ָ��ָȥ������һ����д�굽�����ģ������ע���ˣ�Ӧ�û��и��õ��㷨�����������Ժ��Ż�
    for (i = 0; i < n; i++)
    {
        list_swap.pa = list->head;         //��ǰ
        list_swap.pb = NULL;               //ǰһ��
        list_swap.pc = list_swap.pa->next; //��һ��
        for (k = 0; k < n - i; k++)
        {
            if (list_swap.pa->price > list_swap.pc->price)
            {
                swap1(p, &list_swap);
            }
            else
            {
                swap2(p, &list_swap);
            }
        }
    }
}
void sort_descending(List *list) //��Ʒ���۸�Ӹߵ�������
{
    int n = 0, i, k, num;
    List *p = list;
    Node *p1 = list->head, *p2, *p3;
    List list_swap;
    n = calculate(p);
    list_swap.pa = p1;
    list_swap.pb = p2;
    list_swap.pc = p3;
    //�������ð��������ָ��ָȥ������һ����д�굽�����ģ������ע���ˣ�Ӧ�û��и��õ��㷨�����������Ժ��Ż�
    for (i = 0; i < n; i++)
    {
        list_swap.pa = list->head;         //��ǰ
        list_swap.pb = NULL;               //ǰһ��
        list_swap.pc = list_swap.pa->next; //��һ��
        for (k = 0; k < n - i; k++)
        {
            if (list_swap.pa->price < list_swap.pc->price)
            {
                swap1(p, &list_swap);
            }
            else
            {
                swap2(p, &list_swap);
            }
        }
    }
}
void sort_score(List *list) //��Ʒ�����ִӸߵ�������
{
    int n = 0, i, k, num;
    List *p = list;
    Node *p1 = list->head, *p2, *p3;
    List list_swap;
    n = calculate(p);
    list_swap.pa = p1;
    list_swap.pb = p2;
    list_swap.pc = p3;
    //�������ð��������ָ��ָȥ������һ����д�굽�����ģ������ע���ˣ�Ӧ�û��и��õ��㷨�����������Ժ��Ż�
    for (i = 0; i < n; i++)
    {
        list_swap.pa = list->head;         //��ǰ
        list_swap.pb = NULL;               //ǰһ��
        list_swap.pc = list_swap.pa->next; //��һ��
        for (k = 0; k < n - i; k++)
        {
            if (list_swap.pa->fraction < list_swap.pc->fraction)
            {
                swap1(p, &list_swap);
            }
            else
            {
                swap2(p, &list_swap);
            }
        }
    }
}
int calculate(List *list) //�����������Ľڵ����
{
    int n = 0;
    Node *p = list->head;
    while (p->next != NULL)
    {
        n++;
        p = p->next;
    }
    return n;
}
void swap1(List *list, List *list_swap)//������ð��������㷨��1
{
    Node *p1 = list_swap->pa, *p2 = list_swap->pb, *p3 = list_swap->pc;
    if (list_swap->pb)
    {
        list_swap->pb->next = list_swap->pa->next;
        list_swap->pa->next = list_swap->pc->next;
        list_swap->pc->next = list_swap->pa;
    }
    else
    {
        list->head = list_swap->pa->next;
        list_swap->pa->next = p3->next;
        list_swap->pc->next = list_swap->pa;
    }
    list_swap->pb = list_swap->pc;
    list_swap->pc = list_swap->pa->next;
}
void swap2(List *list, List *list_swap)//������ð��������㷨��2
{
    Node *p1 = list_swap->pa, *p2 = list_swap->pb, *p3 = list_swap->pc;
    if (list_swap->pb)
    {
        list_swap->pa = list_swap->pa->next;
        list_swap->pc = list_swap->pa->next;
        list_swap->pb = p2->next;
    }
    else
    {
        list_swap->pa = list_swap->pa->next;
        list_swap->pc = list_swap->pa->next;
        list_swap->pb = list->head;
    }
}