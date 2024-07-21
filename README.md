
# A* Pathfinding Algorithm in Pacman Game
## Description of the Topic
 ### Introduction to A*
A* is a popular pathfinding and graph traversal algorithm used in many games and applications. It aims to find the shortest path from a start node to a goal node by combining the advantages of Dijkstra’s Algorithm and Greedy Best-First-Search. The algorithm uses a heuristic to estimate the cost to reach the goal, making it both complete and optimal.

![a_-search-algorithm-1](https://github.com/user-attachments/assets/7113c452-3157-490b-b493-59c3b6664fc6)






### Relevance to Pacman
In the context of the Pacman game, A* is used to navigate the ghosts intelligently around the maze, chasing Pacman or fleeing to their home base. This makes the game more challenging and enjoyable by creating dynamic and unpredictable ghost behavior.

### Design and Implementation
Problem Definition
The goal is to implement the A* algorithm in a custom game engine to control the ghost's movement in a Pacman game. The ghosts should be able to find the shortest path to Pacman considering the layout of the maze.
