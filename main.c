/* 2-topshiriq, 6-variant: bir bog'lamli ro'yxat (singly linked list).
 * Amallar: boshiga qo'shish, oxiriga qo'shish, qiymat bo'yicha o'chirish,
 * chiqarish, butun ro'yxatni bo'shatish.
 * Kompilyatsiya: gcc -Wall -Wextra main.c -o main */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int val;
    struct Node *next;
} Node;

/* Yangi tugun ajratadi; malloc natijasi NULL ga tekshiriladi */
static Node *yangi_tugun(int val) {
    Node *n = (Node *)malloc(sizeof(Node));
    if (n == NULL) {
        fprintf(stderr, "Xato: xotira ajratib bo'lmadi.\n");
        return NULL;
    }
    n->val = val;
    n->next = NULL;
    return n;
}

/* Boshiga qo'shish. head ni o'zgartirish uchun Node ** (pointerga pointer) olinadi */
static int boshiga(Node **head, int val) {
    Node *n = yangi_tugun(val);
    if (n == NULL) return 0;
    n->next = *head;
    *head = n;
    return 1;
}

/* Oxiriga qo'shish */
static int oxiriga(Node **head, int val) {
    Node *n = yangi_tugun(val);
    Node *p;
    if (n == NULL) return 0;
    if (*head == NULL) {
        *head = n;
        return 1;
    }
    for (p = *head; p->next != NULL; p = p->next)
        ;
    p->next = n;
    return 1;
}

/* Qiymat bo'yicha birinchi uchragan tugunni o'chiradi. 1 - o'chirildi, 0 - topilmadi */
static int ochir(Node **head, int val) {
    Node **pp = head;                    /* oldingi tugunning next maydoniga pointer */
    while (*pp != NULL && (*pp)->val != val)
        pp = &(*pp)->next;
    if (*pp == NULL) return 0;
    Node *del = *pp;
    *pp = del->next;                     /* ro'yxatdan uzish */
    free(del);
    return 1;
}

static void chiqar(const Node *head) {
    if (head == NULL) {
        printf("Ro'yxat bo'sh.\n");
        return;
    }
    for (; head != NULL; head = head->next)
        printf("%d -> ", head->val);
    printf("NULL\n");
}

/* Butun ro'yxatni bo'shatish; oxirida *head = NULL */
static void bosh_qil(Node **head) {
    Node *p = *head;
    while (p != NULL) {
        Node *keyingi = p->next;
        free(p);
        p = keyingi;
    }
    *head = NULL;
}

/* Butun son o'qish; harf va h.k. rad etiladi. 1 - muvaffaqiyatli */
static int son_oqi(const char *taklif, int *out) {
    char buf[64], *end;
    long v;
    printf("%s", taklif);
    if (fgets(buf, sizeof buf, stdin) == NULL) return -1;   /* EOF */
    v = strtol(buf, &end, 10);
    while (*end == ' ' || *end == '\n') end++;
    if (end == buf || *end != '\0' || v < -1000000000L || v > 1000000000L) {
        printf("Xato: butun son kiriting.\n");
        return 0;
    }
    *out = (int)v;
    return 1;
}

int main(void) {
    Node *head = NULL;
    int tanlov, val, r;
    for (;;) {
        printf("\n1) Boshiga qo'shish  2) Oxiriga qo'shish  3) Qiymat bo'yicha o'chirish\n"
               "4) Chiqarish  0) Chiqish\n");
        r = son_oqi("Tanlov: ", &tanlov);
        if (r < 0) break;
        if (r == 0) continue;
        if (tanlov == 0) break;
        if (tanlov < 1 || tanlov > 4) {
            printf("Xato: 0..4 oralig'ida tanlang.\n");
            continue;
        }
        if (tanlov == 4) { chiqar(head); continue; }
        r = son_oqi("Qiymat: ", &val);
        if (r < 0) break;
        if (r == 0) continue;
        if (tanlov == 1) {
            if (!boshiga(&head, val)) break;
            printf("%d boshiga qo'shildi.\n", val);
        } else if (tanlov == 2) {
            if (!oxiriga(&head, val)) break;
            printf("%d oxiriga qo'shildi.\n", val);
        } else {
            if (ochir(&head, val)) printf("%d o'chirildi.\n", val);
            else printf("%d ro'yxatda topilmadi.\n", val);
        }
    }
    bosh_qil(&head);
    printf("Ro'yxat bo'shatildi. Dastur tugadi.\n");
    return 0;
}
