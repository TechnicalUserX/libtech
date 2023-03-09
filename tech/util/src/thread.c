#include <tech/util/include/thread.h>
#include <tech/util/include/error.h>

tech_return_t tech_thread_safe_block_exit_status_control(tech_thread_safe_block_exit_status_directive_t directive, tech_thread_safe_block_exit_status_t *exit_status_ptr)
{

    tech_thread_local_t static tech_thread_safe_block_exit_status_t *exit_status_stored_ptr = NULL;

    switch (directive)
    {

        case TECH_THREAD_SAFE_BLOCK_EXIT_STATUS_DIRECTIVE_GET:
        {
            if (exit_status_stored_ptr != NULL)
            {
                *exit_status_ptr = *exit_status_stored_ptr;
                tech_error_number = TECH_SUCCESS;
                return TECH_RETURN_SUCCESS;
            }
            else
            {
                return TECH_RETURN_FAILURE;
            }
        }
        break;

        case TECH_THREAD_SAFE_BLOCK_EXIT_STATUS_DIRECTIVE_INIT:
        {

            if (exit_status_ptr != NULL)
            {
                exit_status_stored_ptr = exit_status_ptr;
                tech_error_number = TECH_SUCCESS;
                return TECH_RETURN_SUCCESS;
            }
            else
            {
                return TECH_RETURN_FAILURE;
            }
        }
        break;
        default:{
            return TECH_RETURN_FAILURE;
        }
    }
}

tech_return_t tech_thread_safe_block_global_control(tech_thread_safe_block_global_directive_t directive, const char *lock_identifier, pthread_mutex_t *local_mutex)
{

    static struct lock_memory_t
    {
        char lock_identifier[TECH_THREAD_SAFE_BLOCK_GLOBAL_LOCK_IDENTIFIER_MAX_SIZE];
        sem_t semaphore;
        pthread_mutex_t *active_mutex;
        struct lock_memory_t *next;
    } *lock_memory = NULL;






    struct lock_memory_t *detected_lock_memory = NULL;

    if(directive != TECH_THREAD_SAFE_BLOCK_GLOBAL_DIRECTIVE_FREE){
    TECH_THREAD_SAFE_BLOCK_LOCAL_START
    // This is the place for initialization or configuration

    if (!lock_memory)
    {
        // The memory is empty, create a new instance
        struct lock_memory_t *new_memory = (struct lock_memory_t *)malloc(sizeof(struct lock_memory_t));
        sem_init(&new_memory->semaphore, false, 1);
        memset(new_memory->lock_identifier, 0x0, sizeof(new_memory->lock_identifier));
        strncpy(new_memory->lock_identifier, lock_identifier, TECH_THREAD_SAFE_BLOCK_GLOBAL_LOCK_IDENTIFIER_MAX_SIZE);
        new_memory->active_mutex = NULL; // For now, there is no active mutex
        new_memory->next = NULL;
        lock_memory = new_memory;
        detected_lock_memory = new_memory;
    }
    else
    {
        struct lock_memory_t *memory_iterator;

        for (memory_iterator = lock_memory; memory_iterator != NULL; memory_iterator = memory_iterator->next)
        {
            if (strncmp(memory_iterator->lock_identifier, lock_identifier, TECH_THREAD_SAFE_BLOCK_GLOBAL_LOCK_IDENTIFIER_MAX_SIZE) == 0)
            {
                detected_lock_memory = memory_iterator; // Active mutex is the previous mutex
                break;
            }

            if (memory_iterator->next == NULL)
            {

                struct lock_memory_t *new_memory = (struct lock_memory_t *)malloc(sizeof(struct lock_memory_t));
                sem_init(&new_memory->semaphore, false, 1);
                memset(new_memory->lock_identifier, 0x0, sizeof(new_memory->lock_identifier));
                strncpy(new_memory->lock_identifier, lock_identifier, TECH_THREAD_SAFE_BLOCK_GLOBAL_LOCK_IDENTIFIER_MAX_SIZE);
                new_memory->active_mutex = NULL; // For now, there is no active mutex
                new_memory->next = NULL;
                memory_iterator->next = new_memory;
                detected_lock_memory = new_memory;
                break;
            }
        }
    }

    if (detected_lock_memory->active_mutex != NULL)
    {

        int active_mutex_trylock_ret = pthread_mutex_trylock(detected_lock_memory->active_mutex); // Check the previous/active mutex

        // The active mutex is not going to be destroyed here, it is the responsibility of the local block
        if (active_mutex_trylock_ret == EOWNERDEAD)
        {
            sem_post(&detected_lock_memory->semaphore); // Semaphore is restored
        }
        else if (active_mutex_trylock_ret == ENOTRECOVERABLE)
        {
            sem_post(&detected_lock_memory->semaphore); // Semaphore is restored
        }
        else if (active_mutex_trylock_ret == 0)
        {
            pthread_mutex_unlock(detected_lock_memory->active_mutex);
        }
    }
    TECH_THREAD_SAFE_BLOCK_LOCAL_END

    TECH_THREAD_SAFE_BLOCK_FAIL_START
        tech_error_number = TECH_ERROR_THREAD_SAFE_BLOCK_UNEXPECTED_EXIT;
        return TECH_RETURN_FAILURE;
    TECH_THREAD_SAFE_BLOCK_FAIL_END
    }


    switch (directive)
    {

        case TECH_THREAD_SAFE_BLOCK_GLOBAL_DIRECTIVE_LOCK:
        {
            if (sem_wait(&detected_lock_memory->semaphore) == 0)
            {
                // printf("Locked %s\r\n",detected_lock_memory->lock_identifier);
                // fflush(stdout);
                detected_lock_memory->active_mutex = local_mutex; // Set the active mutex before locking
                tech_error_number = TECH_SUCCESS;
            }
        }
        break;

        case TECH_THREAD_SAFE_BLOCK_GLOBAL_DIRECTIVE_UNLOCK:
        {
            // printf("Unlocked %s\r\n",detected_lock_memory->lock_identifier);
            // fflush(stdout);
            sem_post(&detected_lock_memory->semaphore);
            tech_error_number = TECH_SUCCESS;
        }
        break;
        

        case TECH_THREAD_SAFE_BLOCK_GLOBAL_DIRECTIVE_FREE:
        {
            struct lock_memory_t* memory_iterator = lock_memory;

            while(memory_iterator != NULL){

                struct lock_memory_t* memory_iterator_next = memory_iterator->next;
                free(memory_iterator);
                memory_iterator = memory_iterator_next;
            }
        }
        break;
    }
    tech_error_number = TECH_SUCCESS;
    return TECH_RETURN_SUCCESS;
}