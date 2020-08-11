#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <math.h>
#include "hash_table.h"
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