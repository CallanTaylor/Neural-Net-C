#ifndef MYLIB_H_
#define MYLIB_H_

extern void     *emalloc(size_t s);
extern void     *erealloc(void *p, size_t s);
extern double    sigmoid(double x);
extern int      *get_labels(char *file);
extern int      *get_inputs(char *str);
extern void      print_input(char *str);

#endif
