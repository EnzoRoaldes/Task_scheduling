# Task_scheduling

For this project we are assuming that we are given a number of different tasks that have depen-
dencies between each other (in the sense that some tasks need to be finished before others can
be started). The only guarantee that we have is that there are no circular dependencies (these
would otherwise imply that not all tasks can be completed).
In a first step you should formalize this problem in terms of a graph data structure with
certain properties, and then describe and code an algorithm that will provide one among the
possible sequential tasks scheduling. Your guiding keyword is topological sorting of acyclic
directed graph.
In a second step you will consider the case where each task also has a known duration, and
the tasks can now be performed in parallel (with an unlimited number workers) with the only
condition that a task cannot be started before all of its prerequisites have finished. Describe
and code an algorithm that will schedule them so that the total completion time is (as close as
possible to being) minimal.
