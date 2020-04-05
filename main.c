#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define START 65
#define END 90
#define DASH 45

char *get_text(const char *, unsigned int);

int main(int argc, char **argv) {

    __uint8_t dash_length = 0; //max 2^8
    __uint8_t max_length = 0;

    for (int i = 0; i < strlen(*(argv+1)); ++i) {
        if(((int)  *(*(argv+1)+i ) ) == DASH ){
            dash_length = (__uint8_t) i;
        }
        max_length++;
    }

    __uint8_t len_max = (__uint8_t) ((max_length-1) - dash_length);

    char *letters = malloc(sizeof(char) * dash_length);
    char *num_str = malloc(sizeof(char) * len_max);

    strncpy(letters, *(argv+1), dash_length);
    strncpy(num_str, (*(argv+1)+dash_length+1), len_max+1);

//    char *letters = malloc(sizeof(strlen(*(argv+1))));
//    char *num_str = malloc(sizeof(strlen(*(argv+2))));
//
    char *temp;
//
//    strcpy(letters, *(argv+1));
//    strcpy(num_str, *(argv+2));
//
    long numbers;
    numbers = strtol(num_str, &temp, 10);

    int in_num = (int) numbers;

    //handle > 0 s and insert hyp in to the out  put inside main function , 22:14 / 2020,03,30

    char *addr = get_text(letters, in_num);

    printf("%s \n", addr);

    free(addr);
    free(letters);
    free(num_str);

    return 0;

}

char *get_text(const char *str, unsigned int cur_value){

    char *str_copy = (char *) malloc(strlen(str));

    strcpy(str_copy, str);

    char *start_from = (char *) malloc(sizeof(char) * 1 + 5);

    if (!(*str)){

        *(start_from+0) = (char) START;
        *(start_from+1) = '0';
        *(start_from+2) = '0';
        *(start_from+3) = '0';
        *(start_from+4) = '1';
        *(start_from+5) = '\0';

    } else{

        size_t str_lv = strlen(str);
        char ch_num[str_lv+5];
        start_from = realloc(start_from, strlen(str) + 5);
        unsigned int tmp_val = 0;

        if(cur_value == 9999){

            for (int k = (int) str_lv - 1; k > -1; --k) {
                if(((int) *(str_copy+k)) == END ){

                    *(str_copy+k) = (char) START;

                    if(k == 0){
                        str_copy = realloc(str_copy, str_lv+1);
                        *(str_copy+str_lv) = (char) START;
                    }

                } else{
                    *(str_copy+k) = (char)  (*(str_copy+k)+1);
                    break;
                }
            }

            tmp_val = 1;

        } else{
            tmp_val = cur_value + 1;
        }

        sprintf(ch_num, "%04u", tmp_val);

        strcpy(start_from, str_copy);
        strcat(start_from, "-");
        strcat(start_from, ch_num);
        strcat(start_from, "");

        free(str_copy);

    }

    return start_from;

}