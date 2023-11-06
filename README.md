# philosophers
Eighth 42 project : Philosophers

## Description
The goal of this propject was to solve the dining philosophers in C with threads and mutexes.

## Installation
To use this project, you need to have a C compiler installed on your computer as well as git.  
To install it you need to clone this repository, then once it's done, go into the folder created and type the command `make`. Once it's done an executable file named `philo` should be here.

## How to use
Once the project is installed, you can run it the following way :  
`./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]`  
where :  
`number_of_philosophers` is the number of philosophers at the table and also the number of forks,  
`time_to_die` is the time in milliseconds in which a philosopher needs to eat,  
`time_to_eat` is the time in milliseconds during which a philosopher eats, during this time, he needs two forks,  
`time_to_sleep` is the time in milliseconds during which a philosopher sleeps,  
`[number_of_times_each_philosopher_must_eat]` is an optional argument that states that if the philosophers ate `number_of_times_each_philosopher_must_eat` times, then the simulation stops. If not specified, the simulation stops stops when a philosopher dies.  
