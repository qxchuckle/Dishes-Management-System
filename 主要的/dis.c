#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
// #include <windows.h>
#define SIZE1 100 //名称，价格等字数
#define SIZE2 200 //限制评价字数

typedef struct _node
{
    char name[SIZE1];       //菜品名称
    char restaurant[SIZE1]; //饭店名字
    float price;            //菜的价格
    int fraction;           //菜的评分
    char comment[SIZE2];    //菜品评价
    struct _node *next;
} Node;
typedef struct _list
{
    Node *head;
} List;
//菜单
void menu(void);               //一级菜单
void menu_inquire(List *list); //二级菜单_查找菜单
void help(void);               //二级菜单_帮助菜单
void menu_sort(List *list);    //三级菜单_排序方法
//对节点操作
void add(List *list);     //添加节点
void delete (List *list); //删除节点
void revise(List *list);  //修改节点
//安全输入
char *s_gets(char *st, int n); //安全输入字符
int get_int(void);             //安全输入int型
double get_double(void);       //安全输入double型
//链表的输出
void inquire_all(List *list);           //输出链表全部节点
void inquire_one(List *list);           //输出链表指定菜名节点
void inquire_restaurant(List *list);    //输出链表指定饭店节点
void inquire_part_price(List *list);    //输出一定价格以下的菜品(这功能。。贫穷)
void inquire_part_fraction(List *list); //输出一定评分以上的菜品
//文件操作
void save(List *list);     //保存
void read_txt(List *list); //读取文件_初始链表
//单链表的排序
void sort_ascending(List *list);  //菜品按价格从低到高排序
void sort_descending(List *list); //菜品按价格从高到低排序
void sort_score(List *list);      //菜品按评分从高到低排序
//______________________________________________________
//------------------------------------------------------
int main() //主函数
{
    system("chcp 65001");
    system("cls");
    //若中文乱码则删除上面两句
    menu(); //输出功能菜单
    //佛祖开光无bug
    return 0;
}
//菜单
void menu() //一级菜单
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
        printf("|             广东海洋大学*阳江校区菜品信息系统             \n");
        printf("|-----------------------------------------------------\n");
        printf("|********************系统功能菜单*********************\n");
        printf("|-----------------------------------------------------\n");
        printf("|*******************|1、使用帮助|                       \n");
        printf("|*******************|2、添加菜品信息|                    \n");
        printf("|*******************|3、删除菜品信息|                    \n");
        printf("|*******************|4、查询菜品信息|                    \n");
        printf("|*******************|5、修改菜品信息|                    \n");
        printf("|*******************|6、保存|\n");
        printf("|-----------------------------------------------------\n");
        printf("|*******************|0、退出系统|                       \n");
        printf("|!若有2,3,5的操作,前请先保存再退出系统,否则数据会丢失!\n");
        printf("|-----------------------------------------------------\n");
        printf("请输入功能序号：");
        options = get_int();
        switch (options)
        {
        case 0:
            z = 0;
            printf("即将退出系统。\n");
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
            printf("无该功能，请重新输入:\n");
            system("pause");
        }
    }
    system("pause");
}
void help() //二级菜单_帮助菜单
{
    system("cls");
    printf("\n");
    printf("|-----------------------------------------------------------------\n");
    printf("|使用帮助：\n");
    printf("|1、本菜品信息系统可供用户自行修改内容\n");
    printf("|2、因为考虑到不同饭店有同样名称的菜品，本系统允许菜品名称有重复\n");
    printf("|3、请勿输入错误信息，以免造成程序出错\n");
    printf("|4、关闭系统前记得保存！否则数据会丢失\n");
    printf("|5、有bug联系1934009145@qq.com\n");
    printf("|6、开源地址:github.com/qxchuckle/Dishes-Management-System\n");
    printf("|-----------------------------------------------------------------\n");
    printf("\n");
    system("pause");
}
void menu_inquire(List *list) //二级菜单_查找菜单
{
    int options, z = 1;
    List *p = list;
    if (list->head == NULL)
    {
        printf("还未存入任何菜品！无法查询！\n");
        system("pause");
        return;
    }
    while (z)
    {
        system("cls");
        printf("\n");
        printf("|-----------------------------------------------------\n");
        printf("|1、查询全部菜品信息\n");
        printf("|2、按菜名查询菜品信息\n");
        printf("|3、查询饭店或食堂的全部菜品信息\n");
        printf("|4、查询某价格以下的全部菜品\n");
        printf("|5、查询某评分以上的全部菜品\n");
        printf("|0、返回\n");
        printf("|-----------------------------------------------------\n");
        printf("请输入功能序号：");
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
            printf("无该功能，请重新输入:\n");
            system("pause");
        }
    }
}
void menu_sort(List *list) //三级菜单_排序方法
{
    int options, z = 1;
    List *p = list;
    while (z)
    {
        system("cls");
        printf("\n");
        printf("|-----------------------------------------------------\n");
        printf("|1、按价格从低到高排序\n");
        printf("|2、按价格从高到低排序\n");
        printf("|3、按评分从高到低排序\n");
        printf("|4、不排序\n");
        printf("|0、返回\n");
        printf("|-----------------------------------------------------\n");
        printf("请输入功能序号：");
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
            printf("无该功能，请重新输入:\n");
            system("pause");
        }
    }
}
//对节点操作
void add(List *list) //添加节点
{
    int n = 0, i = 0;
    Node *last = list->head;
    Node *p1 = (Node *)malloc(sizeof(Node));
    ;
    p1->next = NULL;
    system("cls");
    puts("开始录入菜品：\n----------------\n");
    puts("请输入菜品名称：");
    s_gets(p1->name, SIZE1);
    puts("请输入菜品所属饭店or食堂名称：");
    s_gets(p1->restaurant, SIZE1);
    puts("请输入菜品的价格：");
    p1->price = get_int();
    puts("请输入0-10的整数对菜品进行评分：");
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
            puts("评分不在规定范围内，请输入：");
        }
    } while (!i);
    puts("请对菜品进行评价：");
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
        list->head = p1; //如果last为NULL，则要将head指向第一个节点
    }
    puts("录入成功！");
    system("pause");
}
void delete (List *list) //删除节点
{
    int n = 0;
    char a[SIZE1];
    char b[SIZE1];
    Node *p, *q;
    if (list->head == NULL)
    {
        printf("还未存入任何菜品！删除失败！\n");
        system("pause");
        return;
    }
    system("cls");
    printf("请输入你要删除的菜品名称：");
    s_gets(a, SIZE1);
    printf("请输入菜品所属饭店名称：");
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
        printf("\n没有这道菜！\n");
    }
    else
    {
        printf("\n删除成功%d道菜。\n", n);
    }
    system("pause");
}
void revise(List *list) //修改节点
{
    int n = 0, m = 0, i = 0;
    char a[SIZE1];
    char b[SIZE1];
    Node *p, *q;
    if (list->head == NULL)
    {
        printf("还未存入任何菜品！无法修改！\n");
        system("pause");
        return;
    }
    system("cls");
    printf("请输入要修改的菜品的名称：");
    s_gets(a, SIZE1);
    printf("请输入菜品所属饭店名称：");
    s_gets(b, SIZE1);
    for (q = NULL, p = list->head; p; q = p, p = p->next)
    {
        if (!(strcmp(a, p->name) || strcmp(b, p->restaurant)))
        {
            n++;
            printf("\n原来的菜品信息:\n");
            printf("|菜名:%s\n", p->name);
            printf("|所属:%s\n", p->restaurant);
            printf("|价格:%.2f\n", p->price);
            printf("|评分:%d\n", p->fraction);
            printf("|评价:%s\n", p->comment);
            printf("\n");
            puts("请修改菜品的价格：");
            p->price = get_int();
            puts("请输入0-10的整数以修改菜品的评分：");
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
                    puts("评分不在规定范围内，请输入：");
                }
            } while (!i);
            puts("请对菜品进行评价：");
            puts("请修改对菜品的评价：");
            s_gets(p->comment, SIZE2);
        }
    }
    if (n)
    {
        printf("\n修改完成。\n");
    }
    else
    {
        printf("\n没有这道菜！\n");
    }
    system("pause");
}
//安全输入
char *s_gets(char *m, int n) //安全输入字符
{
    char *p;
    char *find;
    p = fgets(m, n, stdin);
    if (p)
    {
        find = strchr(m, '\n'); //查找换行符
        if (find)               //如果地址不是NULL
            *find = '\0';       //在此处放置一个空字符
        else
            while (getchar() != '\n')
                continue;
    }
    return p;
}
int get_int() //安全输入int型
{
    int n;
    char ch;
    while (scanf("%d%*c", &n) != 1)
    {
        while ((ch = getchar()) != '\n')
            putchar(ch);
        printf(" 不是一个正整数！\n请您重新输入：\n");
    }
    return n;
}
double get_double() //安全输入double型
{
    double n;
    char ch;

    while (scanf("%lf%*c", &n) != 1)
    {
        while ((ch = getchar()) != '\n')
            putchar(ch);
        printf(" 不是一个正数！\n请您重新输入：\n");
    }
    return n;
}
//链表的输出
void inquire_all(List *list) //输出链表全部节点
{
    Node *p;
    int n = 1;
    system("cls");
    for (p = list->head; p; p = p->next)
    {
        printf("\n第%d道菜\n", n);
        printf("|菜名:%s\n", p->name);
        printf("|所属:%s\n", p->restaurant);
        printf("|价格:%.2f\n", p->price);
        printf("|评分:%d\n", p->fraction);
        printf("|评价:%s\n", p->comment);
        n++;
    }
    printf("\n所有菜品查询完毕\n");
    system("pause");
}
void inquire_one(List *list) //输出指定菜名
{
    int n = 0;
    char a[SIZE1];
    Node *p;
    system("cls");
    printf("请输入你要找的菜品名称：");
    s_gets(a, SIZE1);
    for (p = list->head; p; p = p->next)
    {
        if (!strcmp(a, p->name))
        {
            printf("\n|菜名:%s\n", p->name);
            printf("|所属:%s\n", p->restaurant);
            printf("|价格:%.2f\n", p->price);
            printf("|评分:%d\n", p->fraction);
            printf("|评价:%s\n", p->comment);
            n++;
        }
    }
    printf("\n共查找到%d道菜\n", n);
    system("pause");
}
void inquire_restaurant(List *list) //输出指定饭店所有菜品
{
    int n = 0;
    char a[SIZE1];
    Node *p;
    system("cls");
    printf("请输入你要找的饭店或食堂：");
    s_gets(a, SIZE1);
    for (p = list->head; p; p = p->next)
    {
        if (!strcmp(a, p->restaurant))
        {
            printf("\n");
            printf("|菜名:%s\n", p->name);
            printf("|所属:%s\n", p->restaurant);
            printf("|价格:%.2f\n", p->price);
            printf("|评分:%d\n", p->fraction);
            printf("|评价:%s\n", p->comment);
            n++;
        }
    }
    printf("\n共查找到%d道菜\n", n);
    system("pause");
}
void inquire_part_price(List *list) //输出一定价格以下的菜品(这功能。。贫穷)
{
    int n = 0;
    double money;
    char a[SIZE1];
    Node *p;
    system("cls");
    printf("请输入封顶价格：");
    money = get_double();
    for (p = list->head; p; p = p->next)
    {
        if (p->price <= money)
        {
            printf("\n|菜名:%s\n", p->name);
            printf("|所属:%s\n", p->restaurant);
            printf("|价格:%.2f\n", p->price);
            printf("|评分:%d\n", p->fraction);
            printf("|评价:%s\n", p->comment);
            n++;
        }
    }
    printf("\n共查找到%d道菜\n", n);
    system("pause");
}
void inquire_part_fraction(List *list) //输出一定评分以上的菜品
{
    int n = 0;
    int score;
    char a[SIZE1];
    Node *p;
    system("cls");
    printf("请输入最低评分：");
    score = get_int();
    for (p = list->head; p; p = p->next)
    {
        if (p->fraction >= score)
        {
            printf("\n|菜名:%s\n", p->name);
            printf("|所属:%s\n", p->restaurant);
            printf("|价格:%.2f\n", p->price);
            printf("|评分:%d\n", p->fraction);
            printf("|评价:%s\n", p->comment);
            n++;
        }
    }
    printf("\n共查找到%d道菜\n", n);
    system("pause");
}
//文件操作
void save(List *list) //保存
{
    if (list->head == NULL)
    {
        printf("还未存入任何菜品！保存为空！\n");
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
        printf("\n保存成功\n");
        system("pause");
    }
    else
    {
        printf("保存失败，请自查或联系作者");
    }
}
void read_txt(List *list) //读取文件_初始链表
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
//单链表的排序
void sort_ascending(List *list) //菜品按价格从低到高排序
{
    int n = 0, i, k, num;
    Node *p1 = list->head;
    Node *p2, *p3, *p4;
    while (p1->next != NULL) //计算出节点的个数
    {
        n++;
        p1 = p1->next;
    }
    //单链表的冒泡排序，这指来指去，作者一口气写完到断气的，不想加注释了，应该会有更好的算法，咕咕咕，以后优化
    for (i = 0; i < n; i++)
    {
        p1 = list->head; //当前
        p2 = NULL;       //前一个
        p3 = p1->next;   //下一个
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
void sort_descending(List *list) //菜品按价格从高到低排序
{
    int n = 0, i, k, num;
    Node *p1 = list->head;
    Node *p2, *p3, *p4;
    while (p1->next != NULL) //计算出节点的个数
    {
        n++;
        p1 = p1->next;
    }
    //单链表的冒泡排序，这指来指去，作者一口气写完到断气的，不想加注释了，应该会有更好的算法，咕咕咕，以后优化
    for (i = 0; i < n; i++)
    {
        p1 = list->head; //当前
        p2 = NULL;       //前一个
        p3 = p1->next;   //下一个
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
void sort_score(List *list) //菜品按评分从高到低排序
{
    int n = 0, i, k, num;
    Node *p1 = list->head;
    Node *p2, *p3, *p4;
    while (p1->next != NULL) //计算出节点的个数
    {
        n++;
        p1 = p1->next;
    }
    //单链表的冒泡排序，这指来指去，作者一口气写完到断气的，不想加注释了，应该会有更好的算法，咕咕咕，以后优化
    for (i = 0; i < n; i++)
    {
        p1 = list->head; //当前
        p2 = NULL;       //前一个
        p3 = p1->next;   //下一个
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
