static inline int DIntr()
{
    int eie, res;

    asm volatile("mfc0\t%0, $12"
                 : "=r"(eie));
    eie &= 0x10000;
    res = eie != 0;

    if (!eie)
        return 0;

    asm(".p2align 3");
    do {
        asm volatile("di");
        asm volatile("sync.p");
        asm volatile("mfc0\t%0, $12"
                     : "=r"(eie));
        eie &= 0x10000;
    } while (eie);

    return res;
}

static inline int EIntr()
{
    int eie;

    asm volatile("mfc0\t%0, $12"
                 : "=r"(eie));
    eie &= 0x10000;
    asm volatile("ei");

    return eie != 0;
}

static inline UWORD
protect_start (void *ptr)
{
  return (UWORD)DIntr();
}

static inline void
protect_end (void *ptr, UWORD isr_level)
{
	if (isr_level)
		EIntr();
}

#include_next <host-config.h>
