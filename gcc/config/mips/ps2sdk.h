#undef  LIB_SPEC
#define LIB_SPEC "\
    -lm \
    --start-group \
        %{g:-lg} %{!g:-lc} \
        -lcdvd \
        -lpthread \
        -lpthreadglue \
        -lcglue \
        -lkernel \
    --end-group"

#undef STARTFILE_SPEC
#define STARTFILE_SPEC "crt0.o%s crti.o%s crtbegin.o%s"

#undef ENDFILE_SPEC
#define ENDFILE_SPEC "crtend.o%s crtn.o%s"

/* The following definitions are for shared object support. */
/* Reference: gcc/config/mips/mips.h, gcc/config/mips/gnu-user.h */

/* If we don't set MASK_ABICALLS, we can't allow usage of PIC.  */
#undef TARGET_DEFAULT
#define TARGET_DEFAULT MASK_ABICALLS

/* -G is incompatible with -mabicalls which is the default, so only allow
   objects in the small data section if the user explicitly asks for it.  */
#undef MIPS_DEFAULT_GVALUE
#define MIPS_DEFAULT_GVALUE 0

/* Conditionally enable PIC depending on the presence of -mplt.  */
#undef SUBTARGET_ASM_SPEC
#define SUBTARGET_ASM_SPEC \
  "%{!mno-abicalls:%{mplt:-call_nonpic;:-KPIC}}"

/* Set some default options for the driver. Mainly, this optimizes default
   options for executables and allows usage of shared objects if requested. */
#define PS2SDK_DRIVER_SELF_SPECS \
  "%{mshared|mno-shared:;:%{" FPIE_OR_FPIC_SPEC ":-mshared;:-mno-shared}}",             \
  "%{mplt|mno-plt:;:-mplt}",             \
  /* -mplt has no effect without -mno-shared.  Simplify later   \
     specs handling by removing a redundant option.  */     \
  "%{!mno-shared:%<mplt}",            \
  /* -mplt likewise has no effect for -mabi=64 without -msym32.  */ \
  "%{mabi=64:%{!msym32:%<mplt}}"

#undef DRIVER_SELF_SPECS
#define DRIVER_SELF_SPECS \
  MIPS_ISA_LEVEL_SPEC,    \
  BASE_DRIVER_SELF_SPECS, \
  PS2SDK_DRIVER_SELF_SPECS
