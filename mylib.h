#ifndef MYLIB_H_
#define MYLIB_H_

extern void     *emalloc(size_t);
extern void     *erealloc(void *, size_t);
extern double    sigmoid(double x);
extern int      *get_labels(char *file);
extern double   *get_inputs(char *file, int position);

#endif
