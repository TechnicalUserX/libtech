#ifndef TECH_THREAD_H
#define TECH_THREAD_H

#include "../config/tech_features.h"
#include "../shared/tech_include.h"
#include "../shared/tech_types.h"

#include "tech_tool.h"
#include "tech_error.h"

#ifdef __cplusplus
    extern "C" {
#endif

#define TECH_THREAD_SAFE_BLOCK_GLOBAL_LOCK_IDENTIFIER_MAX_SIZE 64

enum tech_thread_safe_block_exit_status_enum_t {
    TECH_THREAD_SAFE_BLOCK_EXIT_SUCCESS = 0,
    TECH_THREAD_SAFE_BLOCK_EXIT_RECALL,
    TECH_THREAD_SAFE_BLOCK_EXIT_UNKNOWN
};

enum tech_thread_safe_block_exit_status_directive_enum_t {
    TECH_THREAD_SAFE_BLOCK_EXIT_STATUS_DIRECTIVE_INIT = 0,
    TECH_THREAD_SAFE_BLOCK_EXIT_STATUS_DIRECTIVE_GET,
};

enum tech_thread_safe_block_global_directive_enum_t{
    TECH_THREAD_SAFE_BLOCK_GLOBAL_DIRECTIVE_LOCK,
    TECH_THREAD_SAFE_BLOCK_GLOBAL_DIRECTIVE_UNLOCK
};


typedef enum tech_thread_safe_block_exit_status_enum_t tech_thread_safe_block_exit_status_t;

typedef enum tech_thread_safe_block_exit_status_directive_enum_t tech_thread_safe_block_exit_status_directive_t;

typedef enum tech_thread_safe_block_global_directive_enum_t tech_thread_safe_block_global_directive_t;



// Initializes exit status variable pointer for a specific thread-safe block
// Later used for getting exit status
tech_return_t tech_thread_safe_block_exit_status_control(tech_thread_safe_block_exit_status_directive_t directive,tech_thread_safe_block_exit_status_t* exit_status_ptr);


tech_return_t tech_thread_safe_block_global_control(tech_thread_safe_block_global_directive_t directive, const char* lock_identifier,pthread_mutex_t* local_mutex);


// Thread-safe block
// Do not ever let code_block terminate with return,throw,pthread_exit() and similar expressions
// If the caller dies, block could be recurred by another thread but if it doesn't, it is a deadlock until original caller unlocks it
#define TECH_THREAD_SAFE_BLOCK_LOCAL_START \
    { \
    tech_thread_local_t static tech_thread_safe_block_exit_status_t tech_thread_safe_block_exit_status; \
    tech_thread_safe_block_exit_status_control(TECH_THREAD_SAFE_BLOCK_EXIT_STATUS_DIRECTIVE_INIT,&tech_thread_safe_block_exit_status); \
    static atomic_bool          tech_thread_safe_block_mutex_initialized                       = ATOMIC_VAR_INIT(false); \
    static atomic_bool          tech_thread_safe_block_mutex_initialized_further               = ATOMIC_VAR_INIT(false); \
    atomic_bool                 tech_thread_safe_block_mutex_initialized_expected_value        = ATOMIC_VAR_INIT(false); \
    atomic_bool                 tech_thread_safe_block_mutex_initialized_desired_value         = ATOMIC_VAR_INIT(true); \
    static pthread_mutex_t*     tech_thread_safe_block_mutex                                   = NULL; \
    static pthread_mutexattr_t* tech_thread_safe_block_mutex_attribute                         = NULL; \
    static pthread_cond_t*      tech_thread_safe_block_mutex_condition                         = NULL; \
    static atomic_bool          tech_thread_safe_block_mutex_unexpected_exit                   = ATOMIC_VAR_INIT(false); \
    atomic_int                  tech_thread_safe_block_mutex_lock_ret; \
    tech_thread_safe_block_exit_status = TECH_THREAD_SAFE_BLOCK_EXIT_UNKNOWN; \
    if(__atomic_compare_exchange(&tech_thread_safe_block_mutex_initialized, &tech_thread_safe_block_mutex_initialized_expected_value,&tech_thread_safe_block_mutex_initialized_desired_value,0, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)){ \
        if(!tech_thread_safe_block_mutex) \
            tech_thread_safe_block_mutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t)); \
        if(!tech_thread_safe_block_mutex_attribute) \
            tech_thread_safe_block_mutex_attribute = (pthread_mutexattr_t*)malloc(sizeof(pthread_mutexattr_t)); \
        if(!tech_thread_safe_block_mutex_condition) \
            tech_thread_safe_block_mutex_condition = (pthread_cond_t*)malloc(sizeof(pthread_cond_t)); \
        pthread_mutexattr_init(tech_thread_safe_block_mutex_attribute); \
        pthread_mutexattr_setrobust(tech_thread_safe_block_mutex_attribute, PTHREAD_MUTEX_ROBUST); \
        pthread_mutex_init(tech_thread_safe_block_mutex, tech_thread_safe_block_mutex_attribute); \
        pthread_cond_init(tech_thread_safe_block_mutex_condition, NULL); \
        tech_thread_safe_block_mutex_initialized_further = true; \
    } \
    while(!tech_thread_safe_block_mutex_initialized_further){ \
        usleep(100); /*Busy-waiting is the only option*/ \
    } \
    int tech_thread_safe_block_mutex_trylock_ret = pthread_mutex_trylock(tech_thread_safe_block_mutex); \
    if(tech_thread_safe_block_mutex_unexpected_exit && tech_thread_safe_block_mutex_trylock_ret == EOWNERDEAD){ \
        tech_thread_safe_block_mutex_unexpected_exit = false; \
        pthread_mutex_consistent(tech_thread_safe_block_mutex); \
        pthread_mutex_unlock(tech_thread_safe_block_mutex); \
    }else if(tech_thread_safe_block_mutex_unexpected_exit && tech_thread_safe_block_mutex_trylock_ret == ENOTRECOVERABLE){ \
        pthread_mutex_destroy(tech_thread_safe_block_mutex); \
        pthread_mutexattr_destroy(tech_thread_safe_block_mutex_attribute); \
        pthread_cond_destroy(tech_thread_safe_block_mutex_condition); \
        free(tech_thread_safe_block_mutex_condition); \
        free(tech_thread_safe_block_mutex_attribute); \
        free(tech_thread_safe_block_mutex); \
        tech_thread_safe_block_mutex_condition = NULL; \
        tech_thread_safe_block_mutex_attribute = NULL; \
        tech_thread_safe_block_mutex = NULL; \
        tech_thread_safe_block_mutex_initialized = false; \
        tech_thread_safe_block_mutex_initialized_further = false; \
        tech_thread_safe_block_mutex_unexpected_exit = false; \
        tech_thread_safe_block_exit_status = TECH_THREAD_SAFE_BLOCK_EXIT_RECALL; \
    }else if(tech_thread_safe_block_mutex_trylock_ret == 0){ \
        pthread_mutex_unlock(tech_thread_safe_block_mutex); \
    } \
    if(tech_thread_safe_block_mutex_initialized_further){ \
        tech_thread_safe_block_mutex_lock_ret = pthread_mutex_lock(tech_thread_safe_block_mutex); \
        if(tech_thread_safe_block_mutex_lock_ret == 0){ \
            tech_thread_safe_block_mutex_unexpected_exit = true; \
            {
            
#define TECH_THREAD_SAFE_BLOCK_LOCAL_END }; \
            pthread_mutex_unlock(tech_thread_safe_block_mutex); \
            tech_thread_safe_block_exit_status = TECH_THREAD_SAFE_BLOCK_EXIT_SUCCESS; \
            tech_thread_safe_block_mutex_unexpected_exit = false; \
        }else if(tech_thread_safe_block_mutex_lock_ret == EOWNERDEAD){ \
            pthread_mutex_consistent(tech_thread_safe_block_mutex); \
            pthread_mutex_unlock(tech_thread_safe_block_mutex); \
            tech_thread_safe_block_exit_status = TECH_THREAD_SAFE_BLOCK_EXIT_RECALL; \
        }else if(tech_thread_safe_block_mutex_lock_ret == ENOTRECOVERABLE){ \
            pthread_mutex_destroy(tech_thread_safe_block_mutex); \
            pthread_mutexattr_destroy(tech_thread_safe_block_mutex_attribute); \
            tech_thread_safe_block_mutex_initialized = false; \
            tech_thread_safe_block_mutex_initialized_further = false; \
            tech_thread_safe_block_exit_status = TECH_THREAD_SAFE_BLOCK_EXIT_RECALL; \
        }else{ \
            tech_thread_safe_block_exit_status = TECH_THREAD_SAFE_BLOCK_EXIT_UNKNOWN; \
        } \
    } \
} 


// If this block is called before any initialization to the exit status variable, this block never executes.
// Executes when the original caller locked the mutex and died
#define TECH_THREAD_SAFE_BLOCK_FAIL_START \
    { \
        tech_thread_safe_block_exit_status_t TECH_THREAD_SAFE_BLOCK_EXIT_STATUS; \
        tech_return_t status = tech_thread_safe_block_exit_status_control(TECH_THREAD_SAFE_BLOCK_EXIT_STATUS_DIRECTIVE_GET,&TECH_THREAD_SAFE_BLOCK_EXIT_STATUS); \
        if(!status){ \
            if(TECH_THREAD_SAFE_BLOCK_EXIT_STATUS){ \
                {
                
#define TECH_THREAD_SAFE_BLOCK_FAIL_END }; \
            } \
        } \
    } 




#define TECH_THREAD_SAFE_BLOCK_GLOBAL_START(lock_identifier) \
    { \
    tech_thread_local_t static tech_thread_safe_block_exit_status_t tech_thread_safe_block_exit_status; \
    tech_thread_safe_block_exit_status_control(TECH_THREAD_SAFE_BLOCK_EXIT_STATUS_DIRECTIVE_INIT,&tech_thread_safe_block_exit_status); \
    static atomic_bool          tech_thread_safe_block_mutex_initialized                       = ATOMIC_VAR_INIT(false); \
    static atomic_bool          tech_thread_safe_block_mutex_initialized_further               = ATOMIC_VAR_INIT(false); \
    atomic_bool                 tech_thread_safe_block_mutex_initialized_expected_value        = ATOMIC_VAR_INIT(false); \
    atomic_bool                 tech_thread_safe_block_mutex_initialized_desired_value         = ATOMIC_VAR_INIT(true); \
    static pthread_mutex_t*     tech_thread_safe_block_mutex                                   = NULL; \
    static pthread_mutexattr_t* tech_thread_safe_block_mutex_attribute                         = NULL; \
    static pthread_cond_t*      tech_thread_safe_block_mutex_condition                         = NULL; \
    static atomic_bool          tech_thread_safe_block_mutex_unexpected_exit                   = ATOMIC_VAR_INIT(false); \
    atomic_int                  tech_thread_safe_block_mutex_lock_ret; \
    tech_thread_safe_block_exit_status = TECH_THREAD_SAFE_BLOCK_EXIT_UNKNOWN; \
    if(__atomic_compare_exchange(&tech_thread_safe_block_mutex_initialized, &tech_thread_safe_block_mutex_initialized_expected_value,&tech_thread_safe_block_mutex_initialized_desired_value,0, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)){ \
        if(!tech_thread_safe_block_mutex) \
            tech_thread_safe_block_mutex = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t)); \
        if(!tech_thread_safe_block_mutex_attribute) \
            tech_thread_safe_block_mutex_attribute = (pthread_mutexattr_t*)malloc(sizeof(pthread_mutexattr_t)); \
        if(!tech_thread_safe_block_mutex_condition) \
            tech_thread_safe_block_mutex_condition = (pthread_cond_t*)malloc(sizeof(pthread_cond_t)); \
        pthread_mutexattr_init(tech_thread_safe_block_mutex_attribute); \
        pthread_mutexattr_setrobust(tech_thread_safe_block_mutex_attribute, PTHREAD_MUTEX_ROBUST); \
        pthread_mutex_init(tech_thread_safe_block_mutex, tech_thread_safe_block_mutex_attribute); \
        pthread_cond_init(tech_thread_safe_block_mutex_condition, NULL); \
        tech_thread_safe_block_mutex_initialized_further = true; \
    } \
    while(!tech_thread_safe_block_mutex_initialized_further){ \
        usleep(100); /*Busy-waiting is the only option*/ \
    } \
    int tech_thread_safe_block_mutex_trylock_ret = pthread_mutex_trylock(tech_thread_safe_block_mutex); \
    if(tech_thread_safe_block_mutex_unexpected_exit && tech_thread_safe_block_mutex_trylock_ret == EOWNERDEAD){ \
        tech_thread_safe_block_mutex_unexpected_exit = false; \
        pthread_mutex_consistent(tech_thread_safe_block_mutex); \
        pthread_mutex_unlock(tech_thread_safe_block_mutex); \
    }else if(tech_thread_safe_block_mutex_unexpected_exit && tech_thread_safe_block_mutex_trylock_ret == ENOTRECOVERABLE){ \
        pthread_mutex_destroy(tech_thread_safe_block_mutex); \
        pthread_mutexattr_destroy(tech_thread_safe_block_mutex_attribute); \
        pthread_cond_destroy(tech_thread_safe_block_mutex_condition); \
        free(tech_thread_safe_block_mutex_condition); \
        free(tech_thread_safe_block_mutex_attribute); \
        free(tech_thread_safe_block_mutex); \
        tech_thread_safe_block_mutex_condition = NULL; \
        tech_thread_safe_block_mutex_attribute = NULL; \
        tech_thread_safe_block_mutex = NULL; \
        tech_thread_safe_block_mutex_initialized = false; \
        tech_thread_safe_block_mutex_initialized_further = false; \
        tech_thread_safe_block_mutex_unexpected_exit = false; \
        tech_thread_safe_block_exit_status = TECH_THREAD_SAFE_BLOCK_EXIT_RECALL; \
    }else if(tech_thread_safe_block_mutex_trylock_ret == 0){ \
        pthread_mutex_unlock(tech_thread_safe_block_mutex); \
    } \
    if(tech_thread_safe_block_mutex_initialized_further){ \
        tech_thread_safe_block_mutex_lock_ret = pthread_mutex_lock(tech_thread_safe_block_mutex); \
        if(tech_thread_safe_block_mutex_lock_ret == 0){ \
            tech_thread_safe_block_mutex_unexpected_exit = true; \
            if(tech_thread_safe_block_global_control(TECH_THREAD_SAFE_BLOCK_GLOBAL_DIRECTIVE_LOCK,TECH_TOOL_STRINGIZE(lock_identifier),tech_thread_safe_block_mutex) == TECH_RETURN_SUCCESS){ \
                { \


#define TECH_THREAD_SAFE_BLOCK_GLOBAL_END(lock_identifier) \
                } \
                tech_thread_safe_block_global_control(TECH_THREAD_SAFE_BLOCK_GLOBAL_DIRECTIVE_UNLOCK,TECH_TOOL_STRINGIZE(lock_identifier),tech_thread_safe_block_mutex); \
                tech_error_number = TECH_SUCCESS; \
            }else{ \
                tech_thread_safe_block_exit_status = TECH_ERROR_THREAD_SAFE_BLOCK_GLOBAL_CANNOT_LOCK; \
            } \
            pthread_mutex_unlock(tech_thread_safe_block_mutex); \
            tech_thread_safe_block_mutex_unexpected_exit = false; \
        }else if(tech_thread_safe_block_mutex_lock_ret == EOWNERDEAD){ \
            pthread_mutex_consistent(tech_thread_safe_block_mutex); \
            pthread_mutex_unlock(tech_thread_safe_block_mutex); \
            tech_thread_safe_block_exit_status = TECH_THREAD_SAFE_BLOCK_EXIT_RECALL; \
        }else if(tech_thread_safe_block_mutex_lock_ret == ENOTRECOVERABLE){ \
            pthread_mutex_destroy(tech_thread_safe_block_mutex); \
            pthread_mutexattr_destroy(tech_thread_safe_block_mutex_attribute); \
            tech_thread_safe_block_mutex_initialized = false; \
            tech_thread_safe_block_mutex_initialized_further = false; \
            tech_thread_safe_block_exit_status = TECH_THREAD_SAFE_BLOCK_EXIT_RECALL; \
        }else{ \
            tech_thread_safe_block_exit_status = TECH_THREAD_SAFE_BLOCK_EXIT_UNKNOWN; \
        } \
    } \
} 






#ifdef __cplusplus
    }
#endif

#endif // TECH_THREAD_H