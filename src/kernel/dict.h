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