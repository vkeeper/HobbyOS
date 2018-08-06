 #pragma pack(1)
typedef struct{
    u_int64_t base;
    u_int64_t limit;
    u_int32_t type;
} ARDSItem;

typedef struct{
    u_int32_t len;
    ARDSItem items[0];
} BootParam;
