# Task_scheduling

## Guideline

For this project we are assuming that we are given a number of different tasks that have dependencies between each other (in the sense that some tasks need to be finished before others can be started).  
The only guarantee that we have is that there are no circular dependencies (these would otherwise imply that not all tasks can be completed).

In a first step you should formalize this problem in terms of a graph data structure with certain properties, and then describe and code an algorithm that will provide one among the possible sequential tasks scheduling.  
Your guiding keyword is topological sorting of acyclic directed graph.

In a second step you will consider the case where each task also has a known duration, and the tasks can now be performed in parallel (with an unlimited number workers) with the only condition that a task cannot be started before all of its prerequisites have finished.  
Describe and code an algorithm that will schedule them so that the total completion time is (as close as possible to being) minimal.


## Format of your task file :

1) first line is the number of tasks followed by the total number of dependencies
2) always separate your tasks with a spaceline as done in the example  "tasks_5.txt"
3) a task is : 
   - the number of dependancies of the task followed by its execution time on the first line
   - the tasks it depends of on the lines bellow (1 task per line)
                
4) Be careful when creating your task_file that there are no circular dependencies !


## Run the algorithm

To run our algorithm you need to :
- create your text file *"example.txt"*
- compile our code with ```make```
- call the function with your file ```./main "example.txt"```
- the result will be printed on your terminal as a list

If you want to see our code executed on an example you only need to call *./main* and follow the instructions.