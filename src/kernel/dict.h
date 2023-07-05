/*
struct nlist { // table entry: 
    struct nlist *next; // next entry in chain 
    char *name; // defined name 
    char *defn; // replacement text 
};
#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE]; // pointer table
// hash: form hash value for string s
unsigned hash(char *s)
{
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
      hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}
// lookup: look for s in hashtab
struct nlist *lookup(char *s)
{
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
          return np; // found
    return NULL; // not found
}
char *strdup(char *);
// install: put (name, defn) in hashtab
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;
    if ((np = lookup(name)) == NULL) { // not found
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
          return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else // already there
        free((void *) np->defn); //free previous defn
    if ((np->defn = strdup(defn)) == NULL)
       return NULL;
    return np;
}
char *strdup(char *s) // make a duplicate of s
{
    char *p;
    p = (char *) malloc(strlen(s)+1); // +1 for ’\0’
    if (p != NULL)
       strcpy(p, s);
    return p;
}
*/

typedef struct dict_t_struct {
    char *key;
    void *value;
    struct dict_t_struct *next;
} dict_t;

dict_t **dictAlloc(void) {
    return __std__malloc(sizeof(dict_t));
}

void *getItem(dict_t *dict, char *key) {
    dict_t *ptr;
    for (ptr = dict; ptr != NULL; ptr = ptr->next) {
        if (__std__strcmp(ptr->key, key) == 0) {
            return ptr->value;
        }
    }
    
    return NULL;
}

void delItem(dict_t **dict, char *key) {
    dict_t *ptr, *prev;
    for (ptr = *dict, prev = NULL; ptr != NULL; prev = ptr, ptr = ptr->next) {
        if (__std__strcmp(ptr->key, key) == 0) {
            if (ptr->next != NULL) {
                if (prev == NULL) {
                    *dict = ptr->next;
                } else {
                    prev->next = ptr->next;
                }
            } else if (prev != NULL) {
                prev->next = NULL;
            } else {
                *dict = NULL;
            }
            
            __std__free(&ptr->key);
            __std__free(&ptr);
            
            return;
        }
    }
}

void addItem(dict_t **dict, char *key, void *value) {
    delItem(dict, key);
    dict_t *d = __std__malloc(sizeof(struct dict_t_struct));
    d->key = __std__malloc(__std__strlen(key)+1);
    __std__strcpy(d->key, key);
    d->value = value;
    d->next = *dict;
    *dict = d;
}