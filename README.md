
 # Combined AI behavior in Pacman Game
This is my reseach project for the course "Gameplay Programming" at Howest University of Applied Sciences.
The whole project is written in c++ and is made using the my own game engine which I developed for the course programming 4 . 
## What is this project about?
In my research I'm figuring out how to make a combined Ai behavior for the well known pacman game . 
My goal was to create a rather simple but engaging AI system that is fun to play and fits the scope of what we have
larned throughout the semester in the course gameplay programming 

![FormationSwitching](https://user-images.githubusercontent.com/114002276/211860516-a65eda0d-d20f-4483-99b8-906b2ac22f74.gif)

## How is this implemented?
I started with a little setup creating the grid-based world and made an algorithm choice I went for the A *  which is a well known algoritm
## Description of the Topic
###  AI Behavior Overview
The AI system controls ghost characters with different behavior patterns based on their type and state. The core components of the system are:
![image](https://github.com/user-attachments/assets/53c0b4d7-ba65-447d-bd25-10e5fd19b8f1)
 ### Introduction to A*
A* is a popular pathfinding and graph traversal algorithm used in many games and applications. It aims to find the shortest path from a start node to a goal node by combining the advantages of Dijkstra’s Algorithm and Greedy Best-First-Search. The algorithm uses a heuristic to estimate the cost to reach the goal, making it both complete and optimal.

![a_-search-algorithm-1](https://github.com/user-attachments/assets/7113c452-3157-490b-b493-59c3b6664fc6)


### Relevance to Pacman
In the context of the Pacman game, A* is used to navigate the ghosts intelligently around the maze, chasing Pacman or fleeing to their home base. This makes the game more challenging and enjoyable by creating dynamic and unpredictable ghost behavior.

### Design and Implementation
Problem Definition
The goal is to implement the A* algorithm in a custom game engine to control the ghost's movement in a Pacman game. The ghosts should be able to find the shortest path to Pacman considering the layout of the maze.
but that is only the first step we ant to create an engaging Ai system that makes the ghost share information and work together in order to catch pacman 

## How is this implemented?




## What are the results?
I'm really happy with the results, you can view them below!

![FinalResult](https://user-images.githubusercontent.com/114002276/211960929-d0a7d5a7-d0a8-4c7d-9967-1125ca6055a5.gif)
![FinalResultArrow](https://user-images.githubusercontent.com/114002276/211961935-77390449-14b0-4cda-86ac-f304d3d73a55.gif)

My conclusion is that this system is fun to play with and after some polishing it could be used in a real game. While making the project I found out that dot and cross products are very usefull and finally understood how to use them correctly. 

## Next research topics
If you want, you can do a follow up project based on my work. I would recommend to work on the things where I did not have time to finish:
1. Correct offset when moving next to obstacles. (The path finder self could also take the formation width into account)
2. Subgroups of the formation should always keep a relative position to eachother.
Other also interesting features would be:
1. Creating more basic shapes, for example by means of bezier-curves.
2. The formations could rotate to match the moving direction.

# Sources
https://www.geeksforgeeks.org/a-search-algorithm/
https://www.youtube.com/watch?v=-L-WgKMFuhE&t=226s
https://www.codecademy.com/resources/docs/ai/search-algorithms/a-star-search
