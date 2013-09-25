#ifndef _SPYGLASS_H_
#define _SPYGLASS_H_

typedef struct
{
    int n;
    const char *e;
}
enum_index_st;

typedef struct
{
    void **doit;
    char *name;
}
symbol_info_st;

/*
 * Returns a null terminated (that is, doit == name == NULL) array which
 * constains the names of all the functions overloaded by the spyglass
 * library.
 */
const symbol_info_st * const sgGetSymbolTable();

#endif /* _SPYGLASS_H_ */
