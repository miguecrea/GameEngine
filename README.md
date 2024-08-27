
 # Combined AI behavior in Pacman Game
This is my reseach project for the course "Gameplay Programming" at Howest University of Applied Sciences.
The whole project is written in c++ and is made using the my own game engine which I developed for the course programming 4 . 
# Files where to find behavior 
AiComponent.h
AiComponent.cpp

## What is this project about?
In my research I'm figuring out how to make a combined Ai behavior for the well known pacman game  where multiple paths within the A * algorithm
are evaluated and every ghost should be able to pick a both unique  and best path in order to corner Pacman. 
My goal was to create a rather simple but engaging AI system that is fun to play and fits the scope of what we have
larned throughout the semester in the course gameplay programming 
## Description of the Topic
 ### Introduction to A*
A* is a popular pathfinding and graph traversal algorithm used in many games and applications. It aims to find the shortest path from a start node to a goal node by combining the advantages of Dijkstra’s Algorithm and Greedy Best-First-Search. The algorithm uses a heuristic to estimate the cost to reach the goal, making it both complete and optimal.

![a_-search-algorithm-1](https://github.com/user-attachments/assets/7113c452-3157-490b-b493-59c3b6664fc6)

### Relevance to Pacman
In the context of the Pacman game, A* is used to navigate the ghosts intelligently around the maze, chasing Pacman or fleeing to their home base. This makes the game more challenging and enjoyable by creating dynamic and unpredictable ghost behavior.

### Design and Implementation
Problem Definition
The goal is to implement the A* algorithm in a custom game engine to control the ghost's movement in a Pacman game. The ghosts should be able to find the shortest path to Pacman considering the layout of the maze.
but that is only the first step we want to calculate multiple paths so I modified the algorithm to get a vector of possible paths based on a sample 
# # # 1. Generating Multiple Paths

![image](https://github.com/user-attachments/assets/4d32ce7c-45be-4897-92c2-a57727347714)

this function In a Nutshell will get all possible paths based on the sample we provided 

# 2. Evaluating ,comparing Paths and Determining Path Direction
Once the paths are generated, the AI needs to evaluate them to decide which one to follow. The goal is to choose a path that not only leads to the target but also moves in a direction that is distinct from the paths chosen by other AI components
 now we need to select the best path based on specific criteria, particularly how it relates to the AI's current direction and previously chosen paths. 
For each path, the code calculates the direction of the path based on the second-to-last node in the path (the parent node of the last node): 
getting the relative direction 

![image](https://github.com/user-attachments/assets/5c14de16-deb6-4407-be91-96d269691fd7)


# 3. Choosing a Default Path
If the calculated direction matches the current path direction of the AI component (m_CurrentPathDirection), and no default path has been chosen yet, this path is marked as the default:
![image](https://github.com/user-attachments/assets/1affe1b3-3c46-4a8c-97ec-3a075756310d)

# 4. Avoiding Similar Directions
The code then checks whether the calculated direction for the current path has already been chosen by another AI component:

![image](https://github.com/user-attachments/assets/8200f5d8-54e4-4f7a-a68d-fdf7c69c5ea3)

## What are the results?
I'm really happy with the results, you can view them below!

https://github.com/user-attachments/assets/9c1e4d52-2ac1-4d12-94d2-337097b5ddb5

## Next research topics
1. Interactive Environment: Make the environment more complex by adding traps, teleporters, or doors that open and close. Your algorithm will need to account for these interactions.
2 .Dynamic Pathfinding: Investigate algorithms that adapt to changing environments in real-time. For instance, explore how AI components can dynamically re-route if new obstacles are introduced or if the target position changes.
 3. Multi-Agent Pathfinding (MAPF): Research how to optimize pathfinding for multiple AI components simultaneously, minimizing conflicts and collisions between them. This could involve developing or refining MAPF algorithms like Cooperative A*, prioritized planning, or conflict-based search..

# Sources
https://www.geeksforgeeks.org/a-search-algorithm/
https://www.youtube.com/watch?v=-L-WgKMFuhE&t=226s
https://www.codecademy.com/resources/docs/ai/search-algorithms/a-star-search
