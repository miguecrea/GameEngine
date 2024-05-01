#include "AIComponent.h"
#include "GameObject.h"
#include"SceneManager.h"
#include "Renderer.h"
#include"iostream"
#include"Map.h"

#include <vector>
#include <queue>
#include <cmath>
#include<set>
#include <stack>
#include <array>


#define X_MAX 288
#define X_STEP 8
#define Y_MAX 224
#define Y_STEP 8

struct Node
{
	int y;
	int x;
	int parentX;
	int parentY;
	float gCost;
	float hCost;
	float fCost;
};
std::vector<Node> makePath(std::vector<std::vector<Node>> map, Node dest);
bool isValid(int x, int y);

inline bool operator < (const Node& lhs, const Node& rhs)
{//We need to overload "<" to put our struct into a set
	return lhs.fCost < rhs.fCost;
}

bool isDestination(int x, int y, Node dest) {
	if (x == dest.x && y == dest.y) {
		return true;
	}
	return false;
}

//raycast para saltar 

double calculateH(int x, int y, Node dest) {
	double H = (sqrt((x - dest.x) * (x - dest.x)
		+ (y - dest.y) * (y - dest.y)));
	return H;
}

std::vector<Node> aStar(Node player, Node dest) {
	std::vector<Node> empty;
	if (!isValid(dest.x, dest.y)) {
		//std::cout << "Destination is an obstacle" << std::endl;
		return empty;
	}
	if (isDestination(player.x, player.y, dest)) {
		//std::cout << "You are the destination" << std::endl;
		return empty;
	}

	// Dynamically allocate memory for the closedList
	bool** closedList = new bool* [X_MAX / X_STEP];
	for (int i = 0; i < X_MAX / X_STEP; ++i) {
		closedList[i] = new bool[Y_MAX / Y_STEP];
		std::fill_n(closedList[i], Y_MAX / Y_STEP, false);
	}

	// Dynamically allocate memory for the allMap
	std::vector<std::vector<Node>> allMap(X_MAX / X_STEP,
		std::vector<Node>(Y_MAX / Y_STEP));

	// Initialize whole map
	for (int x = 0; x < X_MAX / X_STEP; x++) {
		for (int y = 0; y < Y_MAX / Y_STEP; y++) {
			allMap[x][y].fCost = FLT_MAX;
			allMap[x][y].gCost = FLT_MAX;
			allMap[x][y].hCost = FLT_MAX;
			allMap[x][y].parentX = -1;
			allMap[x][y].parentY = -1;
			allMap[x][y].x = x;
			allMap[x][y].y = y;

			closedList[x][y] = false;
		}
	}

	// Initialize starting point
	int x = player.x;
	int y = player.y;
	allMap[x][y].fCost = 0.0;
	allMap[x][y].gCost = 0.0;
	allMap[x][y].hCost = 0.0;
	allMap[x][y].parentX = x;
	allMap[x][y].parentY = y;

	std::vector<Node> openList;
	openList.emplace_back(allMap[x][y]);
	bool destinationFound = false;

	while (!openList.empty() && openList.size() < (X_MAX / X_STEP) * (Y_MAX / Y_STEP)) {
		Node node;
		do {
			float temp = FLT_MAX;
			std::vector<Node>::iterator itNode;
			for (std::vector<Node>::iterator it = openList.begin();
				it != openList.end(); it = next(it)) {
				Node n = *it;
				if (n.fCost < temp) {
					temp = n.fCost;
					itNode = it;
				}
			}
			node = *itNode;
			openList.erase(itNode);
		} while (!isValid(node.x, node.y));

		x = node.x;
		y = node.y;
		closedList[x][y] = true;

		for (int newX = -1; newX <= 1; newX++) {
			for (int newY = -1; newY <= 1; newY++) {
				double gNew, hNew, fNew;
				if (isValid(x + newX, y + newY)) {
					if (isDestination(x + newX, y + newY, dest)) {
						allMap[x + newX][y + newY].parentX = x;
						allMap[x + newX][y + newY].parentY = y;
						destinationFound = true;

						// Clean up dynamically allocated memory
						for (int i = 0; i < X_MAX / X_STEP; ++i) {
							delete[] closedList[i];
						}
						delete[] closedList;

						return makePath(allMap, dest);
					}
					else if (!closedList[x + newX][y + newY]) {
						gNew = node.gCost + 1.0;
						hNew = calculateH(x + newX, y + newY, dest);
						fNew = gNew + hNew;
						if (allMap[x + newX][y + newY].fCost == FLT_MAX ||
							allMap[x + newX][y + newY].fCost > fNew) {
							allMap[x + newX][y + newY].fCost = float(fNew);
							allMap[x + newX][y + newY].gCost = float(gNew);
							allMap[x + newX][y + newY].hCost = float(hNew);
							allMap[x + newX][y + newY].parentX = x;
							allMap[x + newX][y + newY].parentY = y;
							openList.emplace_back(allMap[x + newX][y + newY]);
						}
					}
				}
			}
		}
	}
	if (!destinationFound) {
		//std::cout << "Destination not found" << std::endl;
		for (int i = 0; i < X_MAX / X_STEP; ++i) {
			delete[] closedList[i];
		}
		delete[] closedList;
		return empty;
	}
	return empty;
}

bool isValid(int x, int y)
{
	//If our Node is an obstacle it is not valid
	// int id = x + y * (X_MAX / X_STEP);

	if (dae::Map::GetInstance().MapArray[y / Y_MAX / Y_STEP][x / X_MAX / X_STEP] != 1)
	{
		if (x < 0 || y < 0 || x >= (X_MAX / X_STEP) || y >= (Y_MAX / Y_STEP)) {
			return false;
		}
		return true;
	}
	return false;
}

std::vector<Node> makePath(std::vector<std::vector<Node>> map, Node dest) {
	try {
		//std::cout << "Found a path" << std::endl;
		int x = dest.x;
		int y = dest.y;
		std::stack<Node> path;
		std::vector<Node> usablePath;

		while (!(map[x][y].parentX == x && map[x][y].parentY == y)
			&& map[x][y].x != -1 && map[x][y].y != -1)
		{
			path.push(map[x][y]);
			int tempX = map[x][y].parentX;
			int tempY = map[x][y].parentY;
			x = tempX;
			y = tempY;

		}
		path.push(map[x][y]);

		while (!path.empty()) {
			Node top = path.top();
			path.pop();
			usablePath.emplace_back(top);
		}
		return usablePath;
	}
	catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
		return std::vector<Node>();
	}
}

dae::AIComponent::AIComponent(std::shared_ptr<GameObject> SelfGameObject, std::shared_ptr<GameObject> pTargetGameObejct) :
	m_Self{ SelfGameObject },
	m_Target{ pTargetGameObejct },
	m_OldPosition(SelfGameObject->GetLocalPosition()),
	m_pSceneManager(&SceneManager::GetInstance()),//pointer needs addresss 
	m_Direction{ 0 }
{

}//puede tomar un game object 


void dae::AIComponent::Render()

{
	//Point2f Grid = pos(27,35);    
	// Renderer::GetInstance().FillSquare(float(Grid.x),float(Grid.y), 16, SDL_Color{255,0,0,255});

	//Renderer::GetInstance().FillSquare(m_OldPosition.x, m_OldPosition.y, 16, SDL_Color{ 255,0,0,255 });

}

void dae::AIComponent::Update()
{
	//Node player;
	//player.x = X / X_STEP;
	//player.y = Y / Y_STEP;

	//Node destination;
	//destination.x = e->X / X_STEP;
	//destination.y = e->Y / Y_STEP;

	//for (Node node : AIComponent::aStar(player, destination)) {
	//    //Your code here
	//}

	//TODO: algo aqui no funciona

	Node currentPos;
	currentPos.x = int(m_Self->GetLocalPosition().x / X_STEP);
	currentPos.y = int(m_Self->GetLocalPosition().y / Y_STEP);

	Node targetPos;
	targetPos.x = int((m_Target->GetLocalPosition().x) / X_STEP);
	targetPos.y = int((m_Target->GetLocalPosition().y) / Y_STEP);

	auto path = aStar(currentPos, targetPos);
	if (path.size() > 0)
	{
		float x = float(path[0].x * X_STEP);
		float y = float(path[0].y * Y_STEP);
		float deltaX = (x - m_Self->GetLocalPosition().x) * .1f;
		float deltaY = (y - m_Self->GetLocalPosition().y) * .1f;
		m_Self->SetPosition(m_Self->GetLocalPosition().x + deltaX, m_Self->GetLocalPosition().y + deltaY);
	}
}

//m_OldPosition = m_Self->GetLocalPosition();
//glm::vec3 newPosition = m_OldPosition + glm::vec3{10,0,0} * m_pSceneManager->GetDeltaTime();
//m_Self->SetPosition(newPosition.x, newPosition.y);



/////////////////////////////////////////////////////////////////////////////////////////////////


//const float targetX = 20.0f;
//const float targetY = 200.0f;

//m_OldPosition = m_Self->GetLocalPosition();

//// Calculate direction vector towards the target position (200, 200)
//glm::vec3 targetPosition(targetX, targetY, 0.0f); // Assuming z-coordinate is 0
//glm::vec3 direction = glm::normalize(targetPosition - m_OldPosition);

//// Define movement speed
//float moveSpeed = 10.f; // Adjust as needed

//// Calculate movement for this frame
//glm::vec3 movement = direction * moveSpeed * m_pSceneManager->GetDeltaTime();

//// Calculate new position by adding movement to the old position
//glm::vec3 newPosition = m_OldPosition + movement;

//// Check if the character is close enough to the target position
//float distanceToTarget = glm::distance(newPosition, targetPosition);
//if (distanceToTarget <= moveSpeed * m_pSceneManager->GetDeltaTime()) {
//    // If close enough, directly set the position to the target position
//    m_Self->SetPosition(targetX, targetY);
//}
//else {
//    // Otherwise, set the position to the new calculated position
//    m_Self->SetPosition(newPosition.x, newPosition.y);
//}

//


/////////////////////
//Go to target 

// m_OldPosition = m_Self->GetLocalPosition();

// // Assuming playerPosition represents the position of the player object
// glm::vec3 playerPosition = m_Target->GetLocalPosition(); // Assuming m_Player is a pointer to the player object

// // Calculate direction vector towards the player's position
// glm::vec3 direction = glm::normalize(playerPosition - m_OldPosition);

// // Define movement speed
// float moveSpeed = 10.0f; // Adjust as needed

// // Calculate movement for this frame
// glm::vec3 movement = direction * moveSpeed * m_pSceneManager->GetDeltaTime();

// // Calculate new position by adding movement to the old position
// glm::vec3 newPositions = m_OldPosition + movement;

// // Set the position to the new calculated position
//m_Self->SetPosition(newPositions.x, newPositions.y);


 ///////////////



/*  m_OldPosition = m_Self->GetLocalPosition();
  glm::vec3 newPosition = m_OldPosition + glm::vec3{10,0,0} * m_pSceneManager->GetDeltaTime();
  m_Self->SetPosition(newPosition.x, newPosition.y);
*/