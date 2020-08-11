//хеш функция для char
size_t hash_function_char(const char *str);

//хеш функция для int
int hash_function_int(int key);

//создание связного списка
typedef struct node{
    struct data
    {
        int key;
        char *key2;
        int value;
        char *value2;
    }datas;
    struct node *next;
} node_t;

//добавление элемента в конец списка
void append_records(node_t *head, char *key, char *value);

void add_record(char *key, char *value, node_t *hash_array[]);

//выдача value по ключу
int print_record(char *key, node_t *hash_array[]);

//удаление элемента по ключу
int delete_record(char *key, node_t *hash_array[]);

//обнавление value по ключу 
int update_record(char *key, char *value, node_t *hash_array[]);