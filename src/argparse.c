#include "../include/argparse.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

union DataValue* alloc_fargs(enum DataType dtype, int nargs) {
    size_t size = 0;
    switch(dtype) {
        case t__int:
            size = sizeof(int);
            break;
    }
    union DataValue* args = malloc(size * nargs);
    return args;
}

ArgParse newArgParse(int nflags, char* title) {
    Flag* flags = (Flag* ) malloc(sizeof(Flag) * nflags);
    char* p_title = (char* ) malloc(sizeof(char) * strlen(title));
    strcpy_s(p_title, strlen(p_title), title);
    int* is_flag_set = (int* ) malloc(sizeof(int) * nflags);
    for(int i=0; i<nflags; ++i)
        is_flag_set[i] = 0;
    ArgParse apar = {
        .flags = flags,
        .is_flag_set = is_flag_set,
        .nflags = nflags,
        .title = title,
        .cflags = 0,
    };

    return apar;
}



void delArgParse(ArgParse apar) {
    for(int i=0; i<apar.nflags; ++i) {
        free(apar.flags[i].short_form);
        free(apar.flags[i].long_form);
        free(apar.flags[i].args);
    }
    free(apar.flags);
    free(apar.title);
    free(apar.is_flag_set);
}

void add_flag(ArgParse* apar, char* short_form, char* long_form, enum DataType dtype, int nargs) {
    char* f_short_form = NULL;
    char* f_long_form = NULL;
    if(short_form != NULL) {
        f_short_form = (char*) malloc(sizeof(char) * strlen(short_form));
        strcpy(f_short_form, short_form);
    }
    if(long_form != NULL) {
        f_long_form = (char*) malloc(sizeof(char) * strlen(long_form));
        strcpy(f_long_form, long_form);
    }
    if(apar->cflags >= apar->nflags) {
        return;
    }
    union DataValue* args = alloc_fargs(dtype, nargs);
    apar->flags[apar->cflags].nargs = nargs;
    apar->flags[apar->cflags].dtype = dtype;
    apar->flags[apar->cflags].args = args;
    apar->flags[apar->cflags].long_form = f_long_form;
    apar->flags[apar->cflags].short_form = f_short_form;
    apar->cflags++;
    return;
}

void display(const ArgParse *apar) {
    printf("%s\n\n", apar->title);
    printf("Flags: \n\n");
    for(int i=0; i<apar->cflags; ++i) {
        printf("%d. %s, %s [%d args]\n", i, apar->flags[i].short_form,
                apar->flags[i].long_form, apar->flags[i].nargs);
    }
}

int match_up_flag(const Flag* flags, int nflags, char* s) {
    for(int i=0; i<nflags; ++i) {
        if(strcmp(flags[i].long_form, s) == 0 || strcmp(flags[i].short_form, s) == 0) {
            return i;
        }
    }
    return -1;
}

void set_flag(Flag* flag, char* const args[]) {
    for(int i=0; i<flag->nargs; ++i) {
        int x = atoi(args[i]);
        flag->args[i].x = x;
    }
    return;
}

Flag* args_parse(ArgParse* apar, int nargs, char* const argv[]) {
    for(int i=1; i<nargs; i++) {
        int fi = match_up_flag(apar->flags, apar->cflags, argv[i]);
        if(fi < -1)
            return NULL;
        set_flag(&apar->flags[fi], &argv[i+1]);
        apar->is_flag_set[fi] = 1;
        i += apar->flags[fi].nargs;
        return &apar->flags[fi];
    }
    return NULL;
}


