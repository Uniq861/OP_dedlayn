/* 1-topshiriq, B qism, 6-variant, 1-masala (C asoslari):
 * Satrdagi unli, undosh harflar, raqamlar va bo'shliqlar sonini aniqlash.
 * Indeks (s[i]) bilan ishlaydi. Kompilyatsiya: gcc -Wall -Wextra masala1.c -o masala1 */
#include <stdio.h>
#include <string.h>

#define MAX 100   /* satrning eng katta uzunligi (statik massiv) */

/* Belgi lotin harfi ekanini tekshiradi (<ctype.h> ishlatilmaydi) */
static int harfmi(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

/* Belgi unli harf ekanini tekshiradi (a, e, i, o, u; katta-kichik farqsiz) */
static int unlimi(char c) {
    char k = (c >= 'A' && c <= 'Z') ? (char)(c + 'a' - 'A') : c;
    return k == 'a' || k == 'e' || k == 'i' || k == 'o' || k == 'u';
}

/* Hisoblash: natijalar struct o'rniga 4 ta qiymat sifatida massivga yoziladi */
static void sanash(const char *s, int natija[4]) {
    int i;
    natija[0] = natija[1] = natija[2] = natija[3] = 0;
    for (i = 0; s[i] != '\0'; i++) {
        if (harfmi(s[i])) {
            if (unlimi(s[i])) natija[0]++;   /* unli */
            else              natija[1]++;   /* undosh */
        } else if (s[i] >= '0' && s[i] <= '9') {
            natija[2]++;                     /* raqam */
        } else if (s[i] == ' ') {
            natija[3]++;                     /* bo'shliq */
        }
        /* o' va g' dagi apostrof va boshqa belgilar hisobga olinmaydi */
    }
}

/* Kiritishni tekshirish: bo'sh yoki juda uzun satr rad etiladi. 1 - to'g'ri */
static int oqi(char *s) {
    size_t n;
    printf("Satr kiriting (<= %d belgi): ", MAX - 1);
    if (fgets(s, MAX, stdin) == NULL) {
        printf("Xato: kiritish o'qilmadi.\n");
        return 0;
    }
    n = strlen(s);
    if (n > 0 && s[n - 1] == '\n') {
        s[n - 1] = '\0';                 /* oxiridagi '\n' ni olib tashlash */
    } else if (n == MAX - 1) {
        printf("Xato: satr juda uzun (<= %d belgi bo'lishi kerak).\n", MAX - 1);
        return 0;
    }
    if (s[0] == '\0') {
        printf("Xato: bo'sh satr kiritildi.\n");
        return 0;
    }
    return 1;
}

int main(void) {
    char s[MAX];
    int r[4];
    if (!oqi(s)) return 1;
    sanash(s, r);
    printf("Unli harflar : %d\n", r[0]);
    printf("Undosh harflar: %d\n", r[1]);
    printf("Raqamlar     : %d\n", r[2]);
    printf("Bo'shliqlar  : %d\n", r[3]);
    return 0;
}
