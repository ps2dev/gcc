#undef  LIB_SPEC
#define LIB_SPEC "--start-group -lc -lg -lm -lps2sdkc -lkernel --end-group"

#undef STARTFILE_SPEC
#define STARTFILE_SPEC "crt0.o%s crti.o%s crtbegin.o%s"

#undef ENDFILE_SPEC
#define ENDFILE_SPEC "crtend.o%s crtn.o%s"
