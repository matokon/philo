#include "philo.h"

int main(int argc, char **argv)
{
    if(argc == 5 || argc == 6)
    {
        t_table table;
        input_parsing(&table, argv);
        data_init(&table);
        dinner_start(&table);
        clean(&table);
    }
    else
    {
        error_exit("Wrong input!\n");
    }
    return (0);
}
