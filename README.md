
 Combined AI behavior in Pacman Game
This is my reseach project for the course "Gameplay Programming" at Howest University of Applied Sciences.
The whole project is written in c++ and is made using the Elite-Engine. The list of the files added by me can be found at the bottom of this readme.
## What is this project about?
In my research I'm figuring out how to make different formations using flocking and steering behaviours. 
My goal was to create shapes without having to offset the position by fixed values, I wanted a system for more organic shapes.

![FormationSwitching](https://user-images.githubusercontent.com/114002276/211860516-a65eda0d-d20f-4483-99b8-906b2ac22f74.gif)

The second part of my project was finding a way to make the units traverse the world together. I did this by calculating only one common path for the formation.

![FormationSplittingFixv2](https://user-images.githubusercontent.com/114002276/211861652-6ae09756-0175-4813-bd74-539276038716.gif)

## How is this implemented?
I started with a little setup: Every RTS-like game needs a way of selecting units and the location where the units should go. 
When you hold the left mouse button, you can move your mouse in any direction to create a selection rectangle. The units are assigned to the formation after releasing the button. I did this by checking if the middle position of any of my agents is inside the currently selected rectangle.

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





# Sources
https://www.geeksforgeeks.org/a-search-algorithm/
https://www.youtube.com/watch?v=-L-WgKMFuhE&t=226s
https://www.codecademy.com/resources/docs/ai/search-algorithms/a-star-search
