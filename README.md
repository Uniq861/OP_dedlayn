# OS_T1_V06_Familiya — 1-topshiriq, 6-variant

Fan: Operatsion tizimlar | Topshiriq: 1 | Variant: 6

## Tarkib
- `A_qism/` — hello.c, hello.i, hello.s, hello.o, hello (bajariluvchi fayl)
- `masala1.c` — 1-masala (C asoslari): satrdagi unli/undosh/raqam/bo'shliqlar soni
- `masala2.c` — 2-masala (pointerlar): `char *p` bilan hisoblash, natijalar pointer orqali, `%p`

## A qism (4 bosqich)
```bash
cd A_qism
gcc -E hello.c -o hello.i      # preprocessing
gcc -S hello.i -o hello.s      # kompilyatsiya (assembler kodi)
gcc -c hello.s -o hello.o      # assembling (obyekt fayl)
gcc hello.o -o hello           # linking
./hello
```

## B qism
```bash
gcc -Wall -Wextra masala1.c -o masala1 && ./masala1
gcc -Wall -Wextra masala2.c -o masala2 && ./masala2
```
