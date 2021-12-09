//coding:GB2313
//There will be bugs if you don't use gb2313
//Author:Chuckle
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define SIZE1 100 //名称，价格等字数
#define SIZE2 200 //限制评价字数

typedef struct _node //链表的节点结构体
{
    char name[SIZE1];       //菜品名称
    char restaurant[SIZE1]; //饭店名字
    float price;            //菜的价格
    int fraction;           //菜的评分
    char comment[SIZE2];    //菜品评价
    struct _node *next;
} Node;
typedef struct _list //方便对链表操作
{
    Node *head;
    Node *pa;
    Node *pb;
    Node *pc;
} List;
//菜单
void menu(void);               //一级菜单
void menu_inquire(List *list); //二级菜单_查询菜单
void help(void);               //二级菜单_帮助菜单
int menu_sort(List *list);     //三级菜单_排序方法
//对节点操作
void add(List *list);     //添加节点
void delete (List *list); //删除节点
void revise(List *list);  //修改节点
//安全输入
char *s_gets(char *st, int n); //安全输入字符
int get_int(void);             //安全输入int型
float get_float(void);         //安全输入double型
//链表的输出和操作
void inquire_all(List *list);           //输出链表全部节点
void inquire_one(List *list);           //输出链表指定菜名节点
void inquire_restaurant(List *list);    //输出链表指定饭店节点
void inquire_part_price(List *list);    //输出一定价格以下的菜品(这功能。。贫穷)
void inquire_part_fraction(List *list); //输出一定评分以上的菜品
void average_percentage(List *list);    //查询某饭店或食堂的平均价格和评分
void output(Node *p);                   //方便输出
void random_menu(List *list);           //随机输出一道菜
//文件操作
void save(List *list);     //保存
void read_txt(List *list); //读取文件_初始链表
//单链表的排序
void sort_ascending(List *list);         //菜品按价格从低到高排序
void sort_descending(List *list);        //菜品按价格从高到低排序
void sort_score(List *list);             //菜品按评分从高到低排序
int calculate(List *list);               //计算出单链表的节点个数
void swap1(List *list, List *list_swap); //单链表冒泡排序的算法块1
void swap2(List *list, List *list_swap); //单链表冒泡排序的算法块2
//其他
int random_number(List *list); //随机生成不大于节点数的整数
void color(int a);             //控制台文本颜色
//______________________________________________________
//------------------------------------------------------
int main() //主函数
{
    //system("chcp 65001");//GB2313
    //system("chcp 936");//UTF8
    //system("cls");
    menu(); //输出功能菜单
    //佛祖开光无bug
    return 0;
}
//菜单
void menu() //一级菜单
{
    int options, z = 1;
    List list;
    list.head = NULL;                  //head指向空，链表不存在
    FILE *fp = fopen("Menu.txt", "a"); //若无Menu.txt文件，则创建一个
    fclose(fp);
    read_txt(&list); //读入txt中的数据，初始化链表
    while (z)
    {
        system("cls");
        printf("\n");
        color(2);
        printf("|-----------------------------------------------------\n");
        color(14);
        printf("|          广东海洋大学·阳江校区·菜品信息系统             \n");
        color(2);
        printf("|-----------------------------------------------------\n");
        color(11);
        printf("|********************系统功能菜单*********************\n");
        color(2);
        printf("|-----------------------------------------------------\n");
        color(15);
        printf("|*******************|1、使用帮助|                       \n");
        printf("|*******************|2、添加菜品信息|                    \n");
        printf("|*******************|3、删除菜品信息|                    \n");
        printf("|*******************|4、查询菜品信息|                    \n");
        printf("|*******************|5、修改菜品信息|                    \n");
        printf("|*******************|6、今天吃什么|                     \n");
        printf("|*******************|7、保存|\n");
        color(2);
        printf("|-----------------------------------------------------\n");
        color(15);
        printf("|*******************|0、退出系统|                       \n");
        color(12);
        printf("|!!!前请先保存再退出系统,否则数据会丢失!!!\n");
        color(2);
        printf("|-----------------------------------------------------\n");
        color(11);
        printf("请输入功能序号：");
        color(15);
        options = get_int();
        switch (options)
        {
        case 0:
            z = 0; //跳出循环
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
            random_menu(&list);
            break;
        case 7:
            save(&list);
            break;
        default:
            color(12);
            printf("无该功能，请重新输入\n");
            color(11);
            system("pause");
            color(15);
        }
    }
    system("pause");
}
void help() //二级菜单_帮助菜单
{
    system("cls");
    printf("\n");
    color(2);
    printf("|-----------------------------------------------------------------\n");
    color(15);
    printf("|使用帮助：\n");
    printf("|1、本菜品信息系统可供用户自行修改内容\n");
    printf("|2、因为考虑到不同饭店有同样名称的菜品，本系统允许菜品名称有重复\n");
    printf("|3、请勿输入错误信息，以免造成程序出错\n");
    printf("|4、关闭系统前记得保存！否则数据会丢失\n");
    printf("|5、有bug联系1934009145@qq.com\n");
    printf("|6、开源地址:github.com/qxchuckle/Dishes-Management-System\n");
    color(2);
    printf("|-----------------------------------------------------------------\n");
    printf("\n");
    color(11);
    system("pause");
}
void menu_inquire(List *list) //二级菜单_查询菜单
{
    int options, z = 1;
    List *p = list;         //方便传结构体指针
    if (list->head == NULL) //判断链表是否为空
    {
        color(12);
        printf("还未存入任何菜品！无法查询！\n");
        color(11);
        system("pause");
        return; //为空结束函数
    }
    while (z)
    {
        system("cls");
        printf("\n");
        color(2);
        printf("|-----------------------------------------------------\n");
        color(15);
        printf("|1、查询全部菜品信息\n");
        printf("|2、按菜名查询菜品信息\n");
        printf("|3、查询饭店或食堂的全部菜品信息\n");
        printf("|4、查询某价格以下的全部菜品\n");
        printf("|5、查询某评分以上的全部菜品\n");
        printf("|6、查询某饭店或食堂的平均价格、评分和价格区间占比\n");
        printf("|0、返回主菜单\n");
        color(2);
        printf("|-----------------------------------------------------\n");
        color(11);
        printf("请输入功能序号：");
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
            printf("无该功能，请重新输入\n");
            color(11);
            system("pause");
        }
    }
}
int menu_sort(List *list) //三级菜单_排序方法
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
        printf("|1、按价格从低到高排序\n");
        printf("|2、按价格从高到低排序\n");
        printf("|3、按评分从高到低排序\n");
        printf("|4、不排序\n");
        printf("|0、返回主菜单\n");
        color(2);
        printf("|-----------------------------------------------------\n");
        color(11);
        printf("请输入功能序号：");
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
            printf("无该功能，请重新输入\n");
            color(11);
            system("pause");
            color(15);
        }
    }
}
//对节点操作
void add(List *list) //添加节点
{
    float k = 1;
    int n = 0, i = 0;
    Node *last = list->head;
    Node *p1 = (Node *)malloc(sizeof(Node)); //给节点分配空间
    p1->next = NULL;
    system("cls");
    puts("开始录入菜品：\n----------------\n");
    puts("请输入菜品名称：");
    s_gets(p1->name, SIZE1);
    puts("请输入菜品所属饭店or食堂名称：");
    s_gets(p1->restaurant, SIZE1);
    puts("请输入菜品的价格：");
    p1->price = get_float();
    puts("请输入0-10的整数对菜品进行评分：");
    do
    {
        n = get_int();
        if (n >= 0 && n <= 10) //判断评分是否是0-10
        {
            p1->fraction = n;
            i = 1;
        }
        else
        {
            color(12);
            puts("评分不在规定范围内，请重新输入：");
            color(15);
        }
    } while (!i);
    puts("请对菜品进行评价：");
    s_gets(p1->comment, SIZE2);
    if (last) //如果last有值，则说明head已指向链表第一个节点
    {
        while (last->next)
        {
            last = last->next; //last始终指向最后一个节点
        }
        last->next = p1; //在最后一个节点后面再加一个节点
    }
    else
    {
        list->head = p1; //如果last为NULL，则要将head指向第一个节点
    }
    color(11);
    puts("录入成功！");
    system("pause");
}
void delete (List *list) //删除节点
{
    int n = 0;
    char a[SIZE1];
    char b[SIZE1];
    Node *p, *q;
    if (list->head == NULL) //判断链表是否为空
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
    for (q = NULL, p = list->head; p; q = p, p = p->next) //遍历链表
    {
        if (!(strcmp(a, p->name) || strcmp(b, p->restaurant))) //判断是否找到要修改的节点
        {
            n++;   //记录找到了
            if (q) //判断找到的是不是第一个节点
            {
                q->next = p->next; //让该节点的前一个节点都next指向后一个节点
            }
            else
            {
                list->head = p->next; //让head的next指向后一个节点
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
    color(11);
    system("pause");
}
void revise(List *list) //修改节点
{
    float k = 1;
    int n = 0, m = 0, i = 0;
    char a[SIZE1];
    char b[SIZE1];
    Node *p, *q;
    if (list->head == NULL) //判断链表是否为空
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
    for (q = NULL, p = list->head; p; q = p, p = p->next) //遍历链表
    {
        if (!(strcmp(a, p->name) || strcmp(b, p->restaurant))) //判断是否找到要删除的节点
        {
            n++; //记录找到
            printf("\n原来的菜品信息:\n");
            printf("|菜名:%s\n", p->name);
            printf("|所属:%s\n", p->restaurant);
            printf("|价格:%.2f\n", p->price);
            printf("|评分:%d\n", p->fraction);
            printf("|评价:%s\n", p->comment);
            printf("\n");
            puts("请修改菜品的价格：");
            p->price = get_float();
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
                    color(12);
                    puts("评分不在规定范围内，请输入：");
                    color(15);
                }
            } while (!i);
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
    color(11);
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
            *find = '\0';       //在此处放一个空字符
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
        color(4);
        printf(" 不是一个正整数！\n请您重新输入：\n");
        color(15);
    }
    return n;
}
float get_float() //安全输入double型
{
    float n = 1;
    char ch;
    do
    {
        if (n <= 0) //用户输入不是正数输出提示
        {
            color(12);
            puts("请重新输入一个正数！");
            color(15);
        }
        while (scanf("%f%*c", &n) != 1)
        {
            while ((ch = getchar()) != '\n')
                putchar(ch);
            color(12);
            printf(" 不是一个正数！\n请您重新输入：\n");
            color(15);
        }
    } while (n <= 0);
    return n;
}
//链表的输出和操作
void inquire_all(List *list) //输出链表全部节点
{
    Node *p;
    int n = 1;
    system("cls");
    for (p = list->head; p; p = p->next) //遍历链表
    {
        printf("\n第%d道菜:", n);
        output(p);
        n++;
    }
    color(11);
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
    for (p = list->head; p; p = p->next) //遍历链表
    {
        if (!strcmp(a, p->name)) //判断是否找到
        {
            output(p); //调用函数输出节点信息
            n++;       //记录找到多少节点
        }
    }
    color(11);
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
    for (p = list->head; p; p = p->next) //遍历链表
    {
        if (!strcmp(a, p->restaurant)) //判断是否找到
        {
            output(p); //调用函数输出节点信息
            n++;       //记录找到多少节点
        }
    }
    color(11);
    printf("\n共查找到%d道菜\n", n);
    system("pause");
}
void inquire_part_price(List *list) //输出一定价格以下的菜品(这功能。。贫穷)
{
    int n = 0;
    float money, k = 1;
    char a[SIZE1];
    Node *p;
    system("cls");
    printf("请输入封顶价格：");
    money = get_float();
    for (p = list->head; p; p = p->next) //遍历链表
    {
        if (p->price <= money) //判断是否符合要求
        {
            output(p); //调用函数输出节点信息
            n++;       //记录找到多少节点
        }
    }
    color(11);
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
    for (p = list->head; p; p = p->next) //遍历链表
    {
        if (p->fraction >= score) //判断是否符合要求
        {
            output(p); //调用函数输出节点信息
            n++;       //记录找到多少节点
        }
    }
    printf("\n共查找到%d道菜\n", n);
    color(11);
    system("pause");
}
void average_percentage(List *list) //查询某饭店或食堂的平均价格和评分
{
    int n = 0;
    float sum1 = 0, sum2 = 0, b[5] = {0};
    char a[SIZE1];
    Node *p;
    system("cls");
    printf("请输入你要查的饭店或食堂：");
    s_gets(a, SIZE1);
    for (p = list->head; p; p = p->next) //遍历链表
    {
        if (!strcmp(a, p->restaurant)) //判断是否找到
        {
            sum1 += p->price;    //累加价格
            sum2 += p->fraction; //累加评分
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
            n++; //记录找到多少节点
        }
    }
    color(11);
    if (n)
    {
        printf("该饭店/食堂的平均价格是：%.2f\t平均评分是：%.2f\n", sum1 / n, sum2 / n);
        printf("其中：\n0~5元占:%.1f%%\n5~10元占:%.1f%%\n10~15元占:%.1f%%\n", b[0] / n * 100, b[1] / n * 100, b[2] / n * 100);
        printf("15~20元占:%.1f%%\n20元以上占:%.1f%%\n\n", b[3] / n * 100, b[4] / n * 100);
    }
    else
    {
        color(12);
        printf("无该饭店或食堂！\n\n");
    }
    color(11);
    system("pause");
}
void output(Node *p) //方便输出
{
    printf("\n|菜名:%s\n", p->name);
    printf("|所属:%s\n", p->restaurant);
    printf("|价格:%.2f\n", p->price);
    printf("|评分:%d\n", p->fraction);
    printf("|评价:%s\n", p->comment);
}
void random_menu(List *list) //随机输出一道菜
{
    system("cls");
    if (list->head == NULL) //判断链表是否为空
    {
        color(12);
        printf("还未存入任何菜品！删除失败！\n");
        color(11);
        system("pause");
        return;
    }
    List *q = list;
    Node *p = list->head;
    int n = random_number(q), i = 1; //将随机出来的数赋予n，并初始i等于第一道菜，判断数字是否相等，即可找到那个随机出来的菜
    while (p != NULL)
    {

        if (i == n) //借助随机数来随机输出菜
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
//文件操作
void save(List *list) //保存
{
    if (list->head == NULL)
    {
        color(12);
        printf("还未存入任何菜品！保存为空！\n");
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
        printf("\n保存成功\n");
        system("pause");
    }
    else
    {
        color(12);
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
    fgets(f, 10, fp); //读取第一行，并进入下一行，防止bug
    while (!feof(fp)) //当读取到文件结束符跳出循环结束读取
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
//单链表的冒泡排序，这指来指去，作者一口气写完到断气的，不想加注释了，应该会有更好的算法，咕咕咕，以后优化
void sort_ascending(List *list) //菜品按价格从低到高排序
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
        list_swap.pa = list->head;         //当前
        list_swap.pb = NULL;               //前一个
        list_swap.pc = list_swap.pa->next; //下一个
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
void sort_descending(List *list) //菜品按价格从高到低排序
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
        list_swap.pa = list->head;         //当前
        list_swap.pb = NULL;               //前一个
        list_swap.pc = list_swap.pa->next; //下一个
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
void sort_score(List *list) //菜品按评分从高到低排序
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
        list_swap.pa = list->head;         //当前
        list_swap.pb = NULL;               //前一个
        list_swap.pc = list_swap.pa->next; //下一个
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
int calculate(List *list) //计算出单链表的节点个数
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
void swap1(List *list, List *list_swap) //单链表冒泡排序的算法块1
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
void swap2(List *list, List *list_swap) //单链表冒泡排序的算法块2
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
//其他
int random_number(List *list) //随机生成不大于节点数的整数
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
void color(int a) //控制台文本颜色
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a); //更改控制台文字颜色
}