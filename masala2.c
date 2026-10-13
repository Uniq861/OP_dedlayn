/* 1-topshiriq, B qism, 6-variant, 2-masala (pointerlar):
 * Satrni indekssiz, char *p bilan '\0' gacha yurib hisoblash;
 * hisoblagichlar funksiyadan pointerlar orqali qaytadi.
 * Kompilyatsiya: gcc -Wall -Wextra masala2.c -o masala2 */
#include <stdio.h>
#include <string.h>

#define MAX 100

/* Natijalar *unli, *undosh, *raqam, *bosh pointerlari orqali qaytariladi */
static void sanash(const char *s, int *unli, int *undosh, int *raqam, int *bosh) {
    const char *p;                       /* satr bo'ylab yuruvchi pointer */
    *unli = *undosh = *raqam = *bosh = 0;
    for (p = s; *p != '\0'; p++) {       /* '\0' gacha, indekssiz */
        char c = *p;
        if (c >= 'A' && c <= 'Z') c = (char)(c + 'a' - 'A');   /* kichikka o'tkazish */
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
            (*unli)++;
        else if (c >= 'a' && c <= 'z')
            (*undosh)++;
        else if (c >= '0' && c <= '9')
            (*raqam)++;
        else if (c == ' ')
            (*bosh)++;
    }
}

static int oqi(char *s) {
    size_t n;
    printf("Satr kiriting (<= %d belgi): ", MAX - 1);
    if (fgets(s, MAX, stdin) == NULL) {
        printf("Xato: kiritish o'qilmadi.\n");
        return 0;
    }
    n = strlen(s);
    if (n > 0 && *(s + n - 1) == '\n') {
        *(s + n - 1) = '\0';
    } else if (n == MAX - 1) {
        printf("Xato: satr juda uzun (<= %d belgi bo'lishi kerak).\n", MAX - 1);
        return 0;
    }
    if (*s == '\0') {
        printf("Xato: bo'sh satr kiritildi.\n");
        return 0;
    }
    return 1;
}

int main(void) {
    char s[MAX];
    int unli, undosh, raqam, bosh;
    if (!oqi(s)) return 1;
    sanash(s, &unli, &undosh, &raqam, &bosh);
    printf("Unli harflar : %d\n", unli);
    printf("Undosh harflar: %d\n", undosh);
    printf("Raqamlar     : %d\n", raqam);
    printf("Bo'shliqlar  : %d\n", bosh);
    /* manzillar: s massiv boshi, unli o'zgaruvchisi (pointer orqali yoziladi) */
    printf("s massivining manzili      : %p\n", (void *)s);
    printf("'unli' o'zgaruvchi manzili : %p\n", (void *)&unli);
    printf("'undosh' o'zgaruvchi manzili: %p\n", (void *)&undosh);
    return 0;
}
