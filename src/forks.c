#include "philo.h"

_Bool get_forks(t_philo *philo)
{
    _Bool can_take_forks;

    can_take_forks = philo->right_fork->last_user != philo->id;
    can_take_forks &= philo->left_fork->last_user != philo->id;
    can_take_forks &= (philo->status == LIVE && !*philo->simulation_terminated);
    if (can_take_forks)
    {
        // printf(TRY_TAKE_FORK_MSG, get_timestamp() ,philo->id);
        pthread_mutex_lock(&philo->right_fork->lock);
        printf(FORK_TAKEN_MSG, get_timestamp() ,philo->id);
        philo->right_fork->last_user = philo->id;
        // printf(TRY_TAKE_FORK_MSG, get_timestamp(), philo->id);
        pthread_mutex_lock(&philo->left_fork->lock);
        printf(FORK_TAKEN_MSG, get_timestamp(), philo->id);
        philo->left_fork->last_user = philo->id;
    }
    return (can_take_forks);
}

// _Bool get_forks(t_philo *philo)
// {
//     _Bool cant_take_forks;

//     cant_take_forks = philo->right_fork->last_user == philo->id;
//     cant_take_forks |= philo->left_fork->last_user == philo->id;
//     if (!cant_take_forks && philo->status == LIVE && !*philo->simulation_terminated)
//     {
//         pthread_mutex_lock(&philo->right_fork->lock);

//         pthread_mutex_lock(&philo->check_death_lock);
//         if (philo->status == LIVE)
//         {
//             printf(FORK_TAKEN_MSG, get_timestamp() ,philo->id);
//             philo->right_fork->last_user = philo->id;
//         }
//         pthread_mutex_unlock(&philo->check_death_lock);

//         pthread_mutex_lock(&philo->left_fork->lock);

//         pthread_mutex_lock(&philo->check_death_lock);
//         if (philo->status == LIVE)
//         {
//             printf(FORK_TAKEN_MSG, get_timestamp(), philo->id);
//             philo->left_fork->last_user = philo->id;
//         }
//         pthread_mutex_unlock(&philo->check_death_lock);
//     }
//     return (!cant_take_forks);
// }

void drop_forks(t_philo *philo)
{
    pthread_mutex_unlock(&philo->left_fork->lock);
    pthread_mutex_unlock(&philo->right_fork->lock);
    printf(FORK_FRIED_MSG, get_timestamp(), philo->id);
    printf(FORK_FRIED_MSG, get_timestamp(), philo->id);
}