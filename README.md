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



Format of your node_file :

1) first line is the number of nodes
2) always separate your nodes with spaceline as done in the example "nodes.txt"
3) a node is :  - the number of dependancies of the node, followed by its execution time on the 
                  first line
                - the nodes it depends of on the lines bellow 
                

Be careful when creating your node_file that there are no circular dependencies !





CS6 p21/22 -> graphe orienté
CS8        -> structure de priorité
CS9 p12    -> liste/matrice d'adjacence
C10        -> parcours profondeur/largeur 




Faire une structure avec 2 tableaux : 

val1 : nb_node le nombre total de noeuds
val2 : nb_parent le nombre total de dépendances

tab1 : liste de taille nbr de sommets
        avec dans chaque case un tuple
        -> val1 = position du premier élement dont le sommet
        dépend (pour savoir combien faire "suivant - actuel")
        -> val2 = nbr de gens dépendants
        pas besoin de savoir qui ! juste le nbr

tab2 : liste de dépendances triées dans l'ordre
ie les premières valeurs sont les dépendances du sommet0
puis du sommet1 etc...


dans node:
val1 : status : 0 if not yet discovered
                1 if discovered
                2 if visited





TO_DO : - pour trier : jouer avec le nb_child et exe_time
                (dans find_no_dep et new_dep)
        - pb test nb_child == 0 -> nodes 1 et 2 pas ajoutés