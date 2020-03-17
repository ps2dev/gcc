#undef  LIB_SPEC
#define LIB_SPEC "\
    -lm \
    --start-group \
        %{g:-lg} %{!g:-lc} \
        -lcdvd \
        -lps2sdkc \
        -lkernel \
    --end-group"
