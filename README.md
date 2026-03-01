# Philosophers

*This project has been created as a part of the 42 curriculum by alicigar.*

## **Description**

The Dining Philosophers Problem is an example often used in computer science and so well known that it has even been referenced is series such as _Pantheon_.

Several philosophers sit around a table and alternate between thinking, eating, and sleeping. In order to eat, each philosopher (represented by a **thread**) must take two shared forks, whose access is protected using mutexes. The challenge lies in coordinating these actions so that all philosophers can eat when needed, without any of them starving and without the system falling into situations of deadlock or data race; in other words, blocking or conflicting behaviours.

The main objectives of the project are to correctly manage:

-Thread synchronization.

-Exclusive access to shared resources.

-Precise time control.

-Ordered and coherent log output.

-Prevention of data races and deadlocks.

-Clean termination of the simulation.


## Instructions

First of all, git clone the repository and enter.
Then, you will find the folder "philo", enter again.

**Compilation**

	make

**Execution**

Philosophers can be executed with 5 or 6 arguments.

| Argument | Description |
|----------|-------------|
| `argv[1]` `number_of_philosophers` | Number of philosophers and forks |
| `argv[2]` `time_to_die` | Time in ms before a philosopher dies |
| `argv[3]` `time_to_eat` | Time in ms a philosopher spends eating |
| `argv[4]` `time_to_sleep` | Time in ms a philosopher spends sleeping |
| `argv[5]` `must_eat` *(optional)* | Simulation stops when all ate this many times |

An example of compilation:

	./philo 5 800 200 200 7

**Debugging and memory checking**

It is recommended to use Valgrind to detect memory leaks, race conditions and threading issues.
_For checking memory leaks_:

	valgrind --leak-check=full ./philo 5 800 200 200 7

_For checking synchronization problems and deadlocks_:

	valgrind --tool=helgrind ./philo 5 800 200 200

_To detect data races_:

	valgrind --tool=drd ./philo 1 800 200 200


## Resources

The subject provided by 42 was used as a primary resource throughout the development process.

Additional external resources (such as tutorials and technical articles) were consulted to reinforce understanding and will be listed in this section:
https://42-cursus.gitbook.io/guide/3-rank-03/philosophers

https://en.wikipedia.org/wiki/Dining_philosophers_problem


During the development of this project, AI was used as a learning support tool, mainly to:

-Clarify theoretical concepts related to concurrency, synchronization, and thread management.

-Assist in writing and improving the project documentation.

-Help formulate questions and compare design approaches, without generating o copying code directly.

All AI-assisted content was reviewed, fully understood and validated, and all final design and implementation decisions were made consciously and responsibly. The project's code was entirely written and tested by me.
