Design Choice:
Game objects are the fundamental entities in your game engine. They represent anything that can appear in the game world, such as characters, enemies, items, or even abstract concepts like triggers and waypoints.

Implementation:

Class Hierarchy: Create a base GameObject class that contains properties and methods common to all game objects, such as position, rotation, and update methods.
Inheritance: Derive specific types of game objects from the base class, e.g


Comands Pattern
The command pattern is used to encapsulate requests as objects, allowing for parameterization of clients with queues, requests, and operations. This is especially useful for handling user inputs, AI actions, and other commands that need to be executed.

Implementation:

Command Base Class: Create an abstract Command class with an execute() method.
 
Componenets
Design Choice:
The component-based architecture allows for flexible and reusable game object behaviors. Instead of using deep inheritance hierarchies, game objects can be composed of various components that define their behavior and characteristics.

Implementation:

Component Base Class: Create an abstract Component class with an update() method and other necessary interfaces.
Specific Components: Implement various components such as TransformComponent, RenderComponent, PhysicsComponent, and AIComponent.
Composition: Each GameObject holds a collection of components. Methods within the GameObject class can delegate tasks to these components.

