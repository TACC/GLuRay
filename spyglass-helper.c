#include <stdio.h>
#include "spyglass.h"

int main(int argc, char* argv[])
{
    const symbol_info_st * symbol_info;
    int i;

    symbol_info = sgGetSymbolTable();

    for(i=0; symbol_info[i].name; ++i)
    {
        printf("%s\n", symbol_info[i].name);
    }

    return 0;
}
