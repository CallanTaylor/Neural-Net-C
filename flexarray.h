#ifndef FLEXARRAY_H_
#define FLEXARRAY_H_

typedef struct flexarrayrec *flexarray;


extern flexarray   flexarray_new();
extern void        flexarray_free(flexarray f);
extern void        flexarray_append(flexarray f, char c);
extern void        flexarray_print(flexarray f);
extern int         flexarray_get_key(flexarray f);
extern void        flexarray_refresh(flexarray f);


#endif
