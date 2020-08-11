#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#define _GNU_SOURCE         /* See feature_test_macros(7) */
#define number_of_iterations 1000000
#define len_array_collisions 23
#include <math.h>
#define hash_function(X) _Generic((X), \
    int: hash_function_int, \
    char *: hash_function_char \
)(X)

//хеш функция для char
size_t hash_function_char(const char *str)
{
    int hash = 1184142133;
    int i = 0;
    for(; *str; ++str)
    {
        hash = hash ^ ((int)str[i]) << (8  * (i % sizeof(int)));
        i ++;
    }
    return hash % (size_t)99999; //для тестирования хэш функции замените 
                                 //(size_t)99999 на len_array_collisions
}


//хеш функция для int
int hash_function_int(int key)
{
    return key;
}

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
void append_records(node_t *head, char *key, char *value)
{
    node_t *current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }

    current->next = malloc(sizeof(node_t));

    current->next->datas.key2 = key;
    current->next->datas.value2 = value;
    current->next->next=NULL;
}

void add_record(char *key, char *value, node_t *hash_array[])
{
    // пример использования этой функции
    node_t *head = NULL;
    head = malloc(sizeof(node_t));
    append_records(head, key, value);

    hash_array[hash_function(key)] = head;
}

//выдача value по ключу
int print_record(char *key, node_t *hash_array[])
{
    node_t *current = hash_array[hash_function(key)];
    if (current == NULL)
    {
        return 0;
    }

    while (current->next != NULL)
    {
        if (current->next->datas.key2 == key)
        {
            printf("%s\n", current->next->datas.value2);
            break;
        }
        else
        {
            current = current->next;
        }  
    }
    return 0;
}

//удаление элемента по ключу
int delete_record(char *key, node_t *hash_array[])
{
    node_t *head = hash_array[hash_function(key)];
    //указатель на первый элемент
    node_t *current = head;

    if (head->datas.key2 == NULL)
    {
        return 0;
    }

    node_t *node;
    node_t *prev_node;

    while (current->next != NULL)
    {
        if (current->next->datas.key2 == key)
        {
            break;
        }
        else
        {
            current = current->next;
        }
    }

    node = current->next;
    prev_node = current;
    prev_node->next=node->next;
    free(node);
    
    return 0;
}

//обнавление value по ключу 
int update_record(char *key, char *value, node_t *hash_array[])
{
    node_t *head = hash_array[hash_function(key)];
    if (head->datas.key2 == NULL)
    {
        return 0;
    }
    else
    {
        //указатель на первый элемент
        node_t * current = head;
        while (current->next != NULL)
        {
            if (current->next->datas.key2 == key)
                break;
            else
                current = current->next;
        }
        current->next->datas.value2 = value;
    }
    return 0;
}

int main()
{
    node_t *hash_array[100000];

    printf("fuzzing hash_funxion_char\n");
    //fuzzing hash_funxion_char 
    uint64_t collisions[len_array_collisions] = {0};

    for (int i = 0; i < number_of_iterations; ++i)
    {
        int len_word = rand() % 20;
        char word[len_word];
        for (int j = 0; j < len_word; ++j)
        {
            int letter = rand() % 255;
            word[j] = (char)letter;
        }
        word[len_word-1] = '\0';
        
        collisions[hash_function(word)] += 1;
    }

    for (int i = 0; i < len_array_collisions; ++i)
    {
        printf("%ld\n", collisions[i]);
    }

    printf("\nfuzzing hash_table\n");
    //fuzzing hash_table

    char keys[50000][100];
    int index_keys = 0;

    for (int i = 0; i < 1000; ++i)
    {
        int operation = rand()%4;
        //printf("%d\n", operation);
        int quantity = rand()%100;

        for (int d = 0; d < quantity; ++d)
        {
            //key
            int len_key = rand() % 20;
            char key[len_key];
            for (int j = 0; j < len_key; ++j)
            {
                int letter = rand() % 255;
                key[j] = (char)letter;
            }
            key[len_key-1] = '\0';
            
            //value
            int len_value = rand() % 20;
            char value[len_value];
            for (int j = 0; j < len_value; ++j)
            {
                int letter = rand() % 255;
                value[j] = (char)letter;
            }
            value[len_key-1] = '\0';

            //create
            if (operation == 0)
            {
                int i = 0;
                char *k = key;
                for (; *k != 0; ++k)
                {
                    keys[index_keys][i] = *k;
                    i ++;
                }
                keys[index_keys][i+1] = '\0';

                add_record(keys[index_keys], value, hash_array);
                index_keys += 1;
            }

            //update
            if (operation == 1)
            {
                if (index_keys > 0)
                {
                    int index = rand() % index_keys;
                    update_record(keys[index], value, hash_array);
                }
            }

            //read
            if (operation == 2)
                if (index_keys > 0)
                {
                    int index = rand() % index_keys;
                    print_record(keys[index], hash_array);
                }

            //delete
            if (operation == 3)
                if (index_keys > 0)
                {
                    int index = rand() % index_keys;
                    delete_record(keys[index], hash_array);
                }
        }
    }

    return 0;
}
