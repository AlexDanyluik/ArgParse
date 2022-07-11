/*
 * flags short_form long_form
 * */

#include <string.h>

enum DataType {
    T_CHAR = 1,
    T_UCHAR = 2,
    T_SHORT = 3,
    T_USHORT = 4,
    T_INT = 5,
    T_UINT = 6,
    T_LONG = 7,
    T_ULONG = 8,
    T_FLOAT = 9,
    T_DOUBLE = 10,
    T_STRING = 11,
};

union DataValue {
    char dv_char;
    unsigned char dv_uchar;
    short dv_short;
    unsigned short dv_ushort;
    int dv_int;
    unsigned int dv_uint;
    long dv_long;
    unsigned long dv_ulong;
    float dv_float;
    double dv_double;
    char* dv_string;
};

typedef struct {
    char* short_form;
    char* long_form;
    enum DataType dtype;
    int nargs;
    union DataValue* args;
} Flag;

typedef struct {
    Flag* flags;
    int* is_flag_set;
    char* title;
    int nflags;
    int cflags;
}ArgParse;

ArgParse newArgParse(int nflags, char* title);
void delArgParse(ArgParse apar);

void add_flag(ArgParse* apar, char* short_form, char* long_form, enum DataType dtype, int args);

void display(const ArgParse* apar);
Flag* args_parse(ArgParse* apar, int nargs, char* const argv[]);
