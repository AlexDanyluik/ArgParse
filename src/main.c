#include "../include/argparse.h"
#include <stdio.h>
#include <string.h>

int factorial(int x) {
    int fi = 1;
    for(int i=2; i<=x; ++i)
        fi *= i;
    return fi;
}

int main(int argc, char* const argv[]) {
    ArgParse parse = newArgParse(3, "Factorial");
    add_flag(&parse, "-v", "--version", t__int, 0);
    add_flag(&parse, "-n", "--number", t__int, 1);
    add_flag(&parse, "-h", "--help", t__int, 0);
    Flag* flag = args_parse(&parse, argc, argv);
    if(flag == NULL) {
        delArgParse(parse);
        printf("Pass -h or --help flag to get help.");
        return 0;
    }
    if(strcmp("-v", flag->short_form) == 0)
        printf("Version 0.0.1\n");
    else if(strcmp("-h", flag->short_form) == 0)
        display(&parse);
    else
        printf("%d\n", factorial(flag->args[0].x));
    delArgParse(parse);
    return 0;
}
