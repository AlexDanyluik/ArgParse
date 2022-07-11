/*
 * flags short_form long_form
 * */

#include <string.h>

enum DataType {
    t__int = 1,
};

union DataValue {
    int x;
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
