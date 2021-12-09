//coding:GB2313
//There will be bugs if you don't use gb2313
//Author:Chuckle
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define SIZE1 100 //���ƣ��۸������
#define SIZE2 200 //������������

typedef struct _node //����Ľڵ�ṹ��
{
    char name[SIZE1];       //��Ʒ����
    char restaurant[SIZE1]; //��������
    float price;            //�˵ļ۸�
    int fraction;           //�˵�����
    char comment[SIZE2];    //��Ʒ����
    struct _node *next;
} Node;
typedef struct _list //������������
{
    Node *head;
    Node *pa;
    Node *pb;
    Node *pc;
} List;
//�˵�
void menu(void);               //һ���˵�
void menu_inquire(List *list); //�����˵�_��ѯ�˵�
void help(void);               //�����˵�_�����˵�
int menu_sort(List *list);     //�����˵�_���򷽷�
//�Խڵ����
void add(List *list);     //��ӽڵ�
void delete (List *list); //ɾ���ڵ�
void revise(List *list);  //�޸Ľڵ�
//��ȫ����
char *s_gets(char *st, int n); //��ȫ�����ַ�
int get_int(void);             //��ȫ����int��
float get_float(void);         //��ȫ����double��
//���������Ͳ���
void inquire_all(List *list);           //�������ȫ���ڵ�
void inquire_one(List *list);           //�������ָ�������ڵ�
void inquire_restaurant(List *list);    //�������ָ������ڵ�
void inquire_part_price(List *list);    //���һ���۸����µĲ�Ʒ(�⹦�ܡ���ƶ��)
void inquire_part_fraction(List *list); //���һ���������ϵĲ�Ʒ
void average_percentage(List *list);    //��ѯĳ�����ʳ�õ�ƽ���۸������
void output(Node *p);                   //�������
void random_menu(List *list);           //������һ����
//�ļ�����
void save(List *list);     //����
void read_txt(List *list); //��ȡ�ļ�_��ʼ����
//�����������
void sort_ascending(List *list);         //��Ʒ���۸�ӵ͵�������
void sort_descending(List *list);        //��Ʒ���۸�Ӹߵ�������
void sort_score(List *list);             //��Ʒ�����ִӸߵ�������
int calculate(List *list);               //�����������Ľڵ����
void swap1(List *list, List *list_swap); //������ð��������㷨��1
void swap2(List *list, List *list_swap); //������ð��������㷨��2
//����
int random_number(List *list); //������ɲ����ڽڵ���������
void color(int a);             //����̨�ı���ɫ
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
    list.head = NULL;                  //headָ��գ���������
    FILE *fp = fopen("Menu.txt", "a"); //����Menu.txt�ļ����򴴽�һ��
    fclose(fp);
    read_txt(&list); //����txt�е����ݣ���ʼ������
    while (z)
    {
        system("cls");
        printf("\n");
        color(2);
        printf("|-----------------------------------------------------\n");
        color(14);
        printf("|          �㶫�����ѧ������У������Ʒ��Ϣϵͳ             \n");
        color(2);
        printf("|-----------------------------------------------------\n");
        color(11);
        printf("|********************ϵͳ���ܲ˵�*********************\n");
        color(2);
        printf("|-----------------------------------------------------\n");
        color(15);
        printf("|*******************|1��ʹ�ð���|                       \n");
        printf("|*******************|2����Ӳ�Ʒ��Ϣ|                    \n");
        printf("|*******************|3��ɾ����Ʒ��Ϣ|                    \n");
        printf("|*******************|4����ѯ��Ʒ��Ϣ|                    \n");
        printf("|*******************|5���޸Ĳ�Ʒ��Ϣ|                    \n");
        printf("|*******************|6�������ʲô|                     \n");
        printf("|*******************|7������|\n");
        color(2);
        printf("|-----------------------------------------------------\n");
        color(15);
        printf("|*******************|0���˳�ϵͳ|                       \n");
        color(12);
        printf("|!!!ǰ���ȱ������˳�ϵͳ,�������ݻᶪʧ!!!\n");
        color(2);
        printf("|-----------------------------------------------------\n");
        color(11);
        printf("�����빦����ţ�");
        color(15);
        options = get_int();
        switch (options)
        {
        case 0:
            z = 0; //����ѭ��
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
            random_menu(&list);
            break;
        case 7:
            save(&list);
            break;
        default:
            color(12);
            printf("�޸ù��ܣ�����������\n");
            color(11);
            system("pause");
            color(15);
        }
    }
    system("pause");
}
void help() //�����˵�_�����˵�
{
    system("cls");
    printf("\n");
    color(2);
    printf("|-----------------------------------------------------------------\n");
    color(15);
    printf("|ʹ�ð�����\n");
    printf("|1������Ʒ��Ϣϵͳ�ɹ��û������޸�����\n");
    printf("|2����Ϊ���ǵ���ͬ������ͬ�����ƵĲ�Ʒ����ϵͳ�����Ʒ�������ظ�\n");
    printf("|3���������������Ϣ��������ɳ������\n");
    printf("|4���ر�ϵͳǰ�ǵñ��棡�������ݻᶪʧ\n");
    printf("|5����bug��ϵ1934009145@qq.com\n");
    printf("|6����Դ��ַ:github.com/qxchuckle/Dishes-Management-System\n");
    color(2);
    printf("|-----------------------------------------------------------------\n");
    printf("\n");
    color(11);
    system("pause");
}
void menu_inquire(List *list) //�����˵�_��ѯ�˵�
{
    int options, z = 1;
    List *p = list;         //���㴫�ṹ��ָ��
    if (list->head == NULL) //�ж������Ƿ�Ϊ��
    {
        color(12);
        printf("��δ�����κβ�Ʒ���޷���ѯ��\n");
        color(11);
        system("pause");
        return; //Ϊ�ս�������
    }
    while (z)
    {
        system("cls");
        printf("\n");
        color(2);
        printf("|-----------------------------------------------------\n");
        color(15);
        printf("|1����ѯȫ����Ʒ��Ϣ\n");
        printf("|2����������ѯ��Ʒ��Ϣ\n");
        printf("|3����ѯ�����ʳ�õ�ȫ����Ʒ��Ϣ\n");
        printf("|4����ѯĳ�۸����µ�ȫ����Ʒ\n");
        printf("|5����ѯĳ�������ϵ�ȫ����Ʒ\n");
        printf("|6����ѯĳ�����ʳ�õ�ƽ���۸����ֺͼ۸�����ռ��\n");
        printf("|0���������˵�\n");
        color(2);
        printf("|-----------------------------------------------------\n");
        color(11);
        printf("�����빦����ţ�");
        color(15);
        options = get_int();
        switch (options)
        {
        case 0:
            z = 0;
            break;
        case 1:
            if (menu_sort(p))
                inquire_all(p);
            return;
        case 2:
            inquire_one(p);
            return;
        case 3:
            if (menu_sort(p))
                inquire_restaurant(p);
            return;
        case 4:
            if (menu_sort(p))
                inquire_part_price(p);
            return;
        case 5:
            if (menu_sort(p))
                inquire_part_fraction(p);
            return;
        case 6:
            average_percentage(p);
            return;
        default:
            color(12);
            printf("�޸ù��ܣ�����������\n");
            color(11);
            system("pause");
        }
    }
}
int menu_sort(List *list) //�����˵�_���򷽷�
{
    int options, z = 1, n = 1;
    List *p = list;
    while (z)
    {
        system("cls");
        printf("\n");
        color(2);
        printf("|-----------------------------------------------------\n");
        color(15);
        printf("|1�����۸�ӵ͵�������\n");
        printf("|2�����۸�Ӹߵ�������\n");
        printf("|3�������ִӸߵ�������\n");
        printf("|4��������\n");
        printf("|0���������˵�\n");
        color(2);
        printf("|-----------------------------------------------------\n");
        color(11);
        printf("�����빦����ţ�");
        color(15);
        options = get_int();
        switch (options)
        {
        case 0:
            z = 0;
            return z;
        case 1:
            sort_ascending(p);
            return n;
        case 2:
            sort_descending(p);
            return n;
        case 3:
            sort_score(p);
            return n;
        case 4:
            return n;
        default:
            color(12);
            printf("�޸ù��ܣ�����������\n");
            color(11);
            system("pause");
            color(15);
        }
    }
}
//�Խڵ����
void add(List *list) //��ӽڵ�
{
    float k = 1;
    int n = 0, i = 0;
    Node *last = list->head;
    Node *p1 = (Node *)malloc(sizeof(Node)); //���ڵ����ռ�
    p1->next = NULL;
    system("cls");
    puts("��ʼ¼���Ʒ��\n----------------\n");
    puts("�������Ʒ���ƣ�");
    s_gets(p1->name, SIZE1);
    puts("�������Ʒ��������orʳ�����ƣ�");
    s_gets(p1->restaurant, SIZE1);
    puts("�������Ʒ�ļ۸�");
    p1->price = get_float();
    puts("������0-10�������Բ�Ʒ�������֣�");
    do
    {
        n = get_int();
        if (n >= 0 && n <= 10) //�ж������Ƿ���0-10
        {
            p1->fraction = n;
            i = 1;
        }
        else
        {
            color(12);
            puts("���ֲ��ڹ涨��Χ�ڣ����������룺");
            color(15);
        }
    } while (!i);
    puts("��Բ�Ʒ�������ۣ�");
    s_gets(p1->comment, SIZE2);
    if (last) //���last��ֵ����˵��head��ָ�������һ���ڵ�
    {
        while (last->next)
        {
            last = last->next; //lastʼ��ָ�����һ���ڵ�
        }
        last->next = p1; //�����һ���ڵ�����ټ�һ���ڵ�
    }
    else
    {
        list->head = p1; //���lastΪNULL����Ҫ��headָ���һ���ڵ�
    }
    color(11);
    puts("¼��ɹ���");
    system("pause");
}
void delete (List *list) //ɾ���ڵ�
{
    int n = 0;
    char a[SIZE1];
    char b[SIZE1];
    Node *p, *q;
    if (list->head == NULL) //�ж������Ƿ�Ϊ��
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
    for (q = NULL, p = list->head; p; q = p, p = p->next) //��������
    {
        if (!(strcmp(a, p->name) || strcmp(b, p->restaurant))) //�ж��Ƿ��ҵ�Ҫ�޸ĵĽڵ�
        {
            n++;   //��¼�ҵ���
            if (q) //�ж��ҵ����ǲ��ǵ�һ���ڵ�
            {
                q->next = p->next; //�øýڵ��ǰһ���ڵ㶼nextָ���һ���ڵ�
            }
            else
            {
                list->head = p->next; //��head��nextָ���һ���ڵ�
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
    color(11);
    system("pause");
}
void revise(List *list) //�޸Ľڵ�
{
    float k = 1;
    int n = 0, m = 0, i = 0;
    char a[SIZE1];
    char b[SIZE1];
    Node *p, *q;
    if (list->head == NULL) //�ж������Ƿ�Ϊ��
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
    for (q = NULL, p = list->head; p; q = p, p = p->next) //��������
    {
        if (!(strcmp(a, p->name) || strcmp(b, p->restaurant))) //�ж��Ƿ��ҵ�Ҫɾ���Ľڵ�
        {
            n++; //��¼�ҵ�
            printf("\nԭ���Ĳ�Ʒ��Ϣ:\n");
            printf("|����:%s\n", p->name);
            printf("|����:%s\n", p->restaurant);
            printf("|�۸�:%.2f\n", p->price);
            printf("|����:%d\n", p->fraction);
            printf("|����:%s\n", p->comment);
            printf("\n");
            puts("���޸Ĳ�Ʒ�ļ۸�");
            p->price = get_float();
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
                    color(12);
                    puts("���ֲ��ڹ涨��Χ�ڣ������룺");
                    color(15);
                }
            } while (!i);
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
    color(11);
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
            *find = '\0';       //�ڴ˴���һ�����ַ�
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
        color(4);
        printf(" ����һ����������\n�����������룺\n");
        color(15);
    }
    return n;
}
float get_float() //��ȫ����double��
{
    float n = 1;
    char ch;
    do
    {
        if (n <= 0) //�û����벻�����������ʾ
        {
            color(12);
            puts("����������һ��������");
            color(15);
        }
        while (scanf("%f%*c", &n) != 1)
        {
            while ((ch = getchar()) != '\n')
                putchar(ch);
            color(12);
            printf(" ����һ��������\n�����������룺\n");
            color(15);
        }
    } while (n <= 0);
    return n;
}
//���������Ͳ���
void inquire_all(List *list) //�������ȫ���ڵ�
{
    Node *p;
    int n = 1;
    system("cls");
    for (p = list->head; p; p = p->next) //��������
    {
        printf("\n��%d����:", n);
        output(p);
        n++;
    }
    color(11);
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
    for (p = list->head; p; p = p->next) //��������
    {
        if (!strcmp(a, p->name)) //�ж��Ƿ��ҵ�
        {
            output(p); //���ú�������ڵ���Ϣ
            n++;       //��¼�ҵ����ٽڵ�
        }
    }
    color(11);
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
    for (p = list->head; p; p = p->next) //��������
    {
        if (!strcmp(a, p->restaurant)) //�ж��Ƿ��ҵ�
        {
            output(p); //���ú�������ڵ���Ϣ
            n++;       //��¼�ҵ����ٽڵ�
        }
    }
    color(11);
    printf("\n�����ҵ�%d����\n", n);
    system("pause");
}
void inquire_part_price(List *list) //���һ���۸����µĲ�Ʒ(�⹦�ܡ���ƶ��)
{
    int n = 0;
    float money, k = 1;
    char a[SIZE1];
    Node *p;
    system("cls");
    printf("������ⶥ�۸�");
    money = get_float();
    for (p = list->head; p; p = p->next) //��������
    {
        if (p->price <= money) //�ж��Ƿ����Ҫ��
        {
            output(p); //���ú�������ڵ���Ϣ
            n++;       //��¼�ҵ����ٽڵ�
        }
    }
    color(11);
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
    for (p = list->head; p; p = p->next) //��������
    {
        if (p->fraction >= score) //�ж��Ƿ����Ҫ��
        {
            output(p); //���ú�������ڵ���Ϣ
            n++;       //��¼�ҵ����ٽڵ�
        }
    }
    printf("\n�����ҵ�%d����\n", n);
    color(11);
    system("pause");
}
void average_percentage(List *list) //��ѯĳ�����ʳ�õ�ƽ���۸������
{
    int n = 0;
    float sum1 = 0, sum2 = 0, b[5] = {0};
    char a[SIZE1];
    Node *p;
    system("cls");
    printf("��������Ҫ��ķ����ʳ�ã�");
    s_gets(a, SIZE1);
    for (p = list->head; p; p = p->next) //��������
    {
        if (!strcmp(a, p->restaurant)) //�ж��Ƿ��ҵ�
        {
            sum1 += p->price;    //�ۼӼ۸�
            sum2 += p->fraction; //�ۼ�����
            if (p->price <= 5)
            {
                b[0]++;
            }
            else
            {
                if (p->price <= 10)
                {
                    b[1]++;
                }
                else
                {
                    if (p->price <= 15)
                    {
                        b[2]++;
                    }
                    else
                    {
                        if (p->price < 20)
                        {
                            b[3]++;
                        }
                        else
                        {
                            b[4]++;
                        }
                    }
                }
            }
            n++; //��¼�ҵ����ٽڵ�
        }
    }
    color(11);
    if (n)
    {
        printf("�÷���/ʳ�õ�ƽ���۸��ǣ�%.2f\tƽ�������ǣ�%.2f\n", sum1 / n, sum2 / n);
        printf("���У�\n0~5Ԫռ:%.1f%%\n5~10Ԫռ:%.1f%%\n10~15Ԫռ:%.1f%%\n", b[0] / n * 100, b[1] / n * 100, b[2] / n * 100);
        printf("15~20Ԫռ:%.1f%%\n20Ԫ����ռ:%.1f%%\n\n", b[3] / n * 100, b[4] / n * 100);
    }
    else
    {
        color(12);
        printf("�޸÷����ʳ�ã�\n\n");
    }
    color(11);
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
void random_menu(List *list) //������һ����
{
    system("cls");
    if (list->head == NULL) //�ж������Ƿ�Ϊ��
    {
        color(12);
        printf("��δ�����κβ�Ʒ��ɾ��ʧ�ܣ�\n");
        color(11);
        system("pause");
        return;
    }
    List *q = list;
    Node *p = list->head;
    int n = random_number(q), i = 1; //�����������������n������ʼi���ڵ�һ���ˣ��ж������Ƿ���ȣ������ҵ��Ǹ���������Ĳ�
    while (p != NULL)
    {

        if (i == n) //�������������������
        {
            output(p);
            color(11);
            system("pause");
            return;
        }
        i++;
        p = p->next;
    }
}
//�ļ�����
void save(List *list) //����
{
    if (list->head == NULL)
    {
        color(12);
        printf("��δ�����κβ�Ʒ������Ϊ�գ�\n");
        color(11);
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
        color(11);
        printf("\n����ɹ�\n");
        system("pause");
    }
    else
    {
        color(12);
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
    fgets(f, 10, fp); //��ȡ��һ�У���������һ�У���ֹbug
    while (!feof(fp)) //����ȡ���ļ�����������ѭ��������ȡ
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
//�������ð��������ָ��ָȥ������һ����д�굽�����ģ������ע���ˣ�Ӧ�û��и��õ��㷨�����������Ժ��Ż�
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
    for (i = 0; i < n - 1; i++)
    {
        list_swap.pa = list->head;         //��ǰ
        list_swap.pb = NULL;               //ǰһ��
        list_swap.pc = list_swap.pa->next; //��һ��
        for (k = 0; k < n - i - 1; k++)
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
    for (i = 0; i < n - 1; i++)
    {
        list_swap.pa = list->head;         //��ǰ
        list_swap.pb = NULL;               //ǰһ��
        list_swap.pc = list_swap.pa->next; //��һ��
        for (k = 0; k < n - i - 1; k++)
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
    for (i = 0; i < n - 1; i++)
    {
        list_swap.pa = list->head;         //��ǰ
        list_swap.pb = NULL;               //ǰһ��
        list_swap.pc = list_swap.pa->next; //��һ��
        for (k = 0; k < n - i - 1; k++)
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
    return n + 1;
}
void swap1(List *list, List *list_swap) //������ð��������㷨��1
{
    if (list_swap->pb)
    {
        list_swap->pb->next = list_swap->pa->next;
        list_swap->pa->next = list_swap->pc->next;
        list_swap->pc->next = list_swap->pa;
    }
    else
    {
        list->head = list_swap->pa->next;
        list_swap->pa->next = list_swap->pc->next;
        list_swap->pc->next = list_swap->pa;
    }
    list_swap->pb = list_swap->pc;
    list_swap->pc = list_swap->pa->next;
}
void swap2(List *list, List *list_swap) //������ð��������㷨��2
{
    if (list_swap->pb)
    {
        list_swap->pa = list_swap->pa->next;
        list_swap->pc = list_swap->pa->next;
        list_swap->pb = list_swap->pb->next;
    }
    else
    {
        list_swap->pa = list_swap->pa->next;
        list_swap->pc = list_swap->pa->next;
        list_swap->pb = list->head;
    }
}
//����
int random_number(List *list) //������ɲ����ڽڵ���������
{
    int n = 0, m = 0, sum = 1, i = 0;
    List *q = list;
    srand((unsigned)time(NULL) * 12);
    m = calculate(q);
    i = m;
    while (m > 0)
    {
        sum = sum * 10;
        m = m / 10;
    }
    while (1)
    {
        n = rand() % sum;
        if (n <= i && n > 0)
        {
            i = n;
            break;
        }
    }
    return i;
}
void color(int a) //����̨�ı���ɫ
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a); //���Ŀ���̨������ɫ
}