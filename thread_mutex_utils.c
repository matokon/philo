#include "philo.h"

void mutex_handle(pthread_mutex_t *mtx, const char *code)
{
    if (ft_strcmp(code, "INIT") == 0)
    {
        if (pthread_mutex_init(mtx, NULL) != 0)
            error_exit("Mutex init error!");
    }
    else if (ft_strcmp(code, "LOCK") == 0)
    {
        if (pthread_mutex_lock(mtx) != 0)
            error_exit("Mutex lock error!");
    }
    else if (ft_strcmp(code, "UNLOCK") == 0)
    {
        if (pthread_mutex_unlock(mtx) != 0)
            error_exit("Mutex unlock error!");
    }
    else if (ft_strcmp(code, "DESTROY") == 0)
    {
        if (pthread_mutex_destroy(mtx) != 0)
            error_exit("Mutex destroy error!");
    }
    else
    {
        error_exit("Unknown mutex operation!");
    }
}

void thread_handle(pthread_t *thread,
                   const char *code,
                   void *(*start_routine)(void *),
                   void *arg)
{
    int status;

    if (ft_strcmp(code, "CREATE") == 0)
    {
        status = pthread_create(thread, NULL, start_routine, arg);
        if (status != 0)
            error_exit("Thread create error!");
    }
    else if (ft_strcmp(code, "JOIN") == 0)
    {
        status = pthread_join(*thread, NULL);
        if (status != 0)
            error_exit("Thread join error!");
    }
    else if (ft_strcmp(code, "DETACH") == 0)
    {
        status = pthread_detach(*thread);
        if (status != 0)
            error_exit("Thread detach error!");
    }
    else
    {
        error_exit("Unknown thread operation!");
    }
}
