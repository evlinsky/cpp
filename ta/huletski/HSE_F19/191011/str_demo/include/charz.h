#ifndef CHARZ_H
#define CHARZ_H

// opaque 'pointer'; charz internals are 'hidden'
struct charz;
typedef struct charz charz_t;

charz_t* charz_create(); // NB: not charz_init
void charz_destroy(charz_t **);
void charz_append_cstr(charz_t *, const char *);
void charz_remove_all(charz_t *);

#endif
