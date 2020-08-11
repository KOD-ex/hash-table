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
#include "hash_table.h"
 
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