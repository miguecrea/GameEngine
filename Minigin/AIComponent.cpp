#include "AIComponent.h"
#include "GameObject.h"
#include"SceneManager.h"
#include "Renderer.h"
#include"Map.h"

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include<set>
#include <stack>
#include <array>
#include"staticHeader.h"



#define X_MAX 224
#define X_STEP 8
#define Y_MAX 288
#define Y_STEP 8


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

std::vector<Node> aStar(Node agent, Node dest) {
	std::vector<Node> empty;
	if (!isValid(dest.x, dest.y)) {
		//std::cout << "Destination is an obstacle" << std::endl;
		return empty;
	}
	if (isDestination(agent.x, agent.y, dest)) {
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
	int x = agent.x;
	int y = agent.y;
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
		//it = next(it)
		do {
			float temp = FLT_MAX;
			std::vector<Node>::iterator itNode;
			for (std::vector<Node>::iterator it = openList.begin();
				it != openList.end(); ++it) {
				Node n = *it;
				if (n.fCost < temp)
				{
					temp = n.fCost;
					itNode = it;
				}
			}
			node = *itNode;
			openList.erase(itNode);
		} while (!isValid(node.x, node.y) && !openList.empty());

		x = node.x;
		y = node.y;
		closedList[x][y] = true;

		for (int newX = -1; newX <= 1; newX++)
		{
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
							allMap[x + newX][y + newY].fCost > fNew)
						{
							if (newX != 0 && newY != 0) {
								fNew = FLT_MAX;
								gNew = FLT_MAX;
								hNew = FLT_MAX;
							}
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

	if (x < 0 || y < 0 || x >= (X_MAX / X_STEP) || y >= (Y_MAX / Y_STEP))
	{
		return false;
	}
	if (dae::Map::GetInstance().MapArray[y][x] == 1)
	{
		return false;
	}
	return true;
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
		//std::cout << "Path full, " << usablePath.size() << std::endl;
		return usablePath;
	}
	catch (const std::exception& e) {
		std::cout << "Path empty, error " << e.what() << std::endl;
		return std::vector<Node>();
	}
}

dae::AIComponent::AIComponent(std::shared_ptr<GameObject> SelfGameObject, std::shared_ptr<GameObject> pTargetGameObejct, dae::GhostType Type) :
	m_Self{ SelfGameObject },
	m_Target{ pTargetGameObejct },
	m_OldPosition(SelfGameObject->GetLocalPosition()),
	m_pSceneManager(&SceneManager::GetInstance()),//pointer needs addresss 
	m_Direction{ 0 },
	m_TypeOfGhost{Type}
{

	m_OrangeGhosts.push_back(std::make_tuple(10,20));
	m_OrangeGhosts.push_back(std::make_tuple(20,34));
	m_OrangeGhosts.push_back(std::make_tuple(2,4));
	m_OrangeGhosts.push_back(std::make_tuple(4,4));
	
	switch (m_TypeOfGhost)
	{
	case dae::GhostType::Blue:
		m_Speed = 25.f;

		break;
	case dae::GhostType::Red:
		m_Speed = 30.f;

		break;
	case dae::GhostType::Pink:

		m_Speed = 15.f;
		break;
	case dae::GhostType::Orange:
		m_Speed = 23.f;

		break;
	default:
		break;
	}


	

}//puede tomar un game object 


void dae::AIComponent::Render()

{



	//auto test = Map::GetInstance().GridToPos(rowTest, Column);

	//int roww = std::get<0>(test);
	//int column = std::get<0>(test);

	//Renderer::GetInstance().FillSquare(float(roww) * 2, float(column) * 2, 16, 16, SDL_Color{ 0,0,0,255 });
	//Renderer::GetInstance().FillSquare(0,0, 16, 16, SDL_Color{ 0,0,0,255 });



	

}

void dae::AIComponent::Update()
{


	Node currentPos;
	currentPos.x = int(m_Self->GetLocalPosition().x + 3) / X_STEP;
	currentPos.y = int(m_Self->GetLocalPosition().y + 3) / Y_STEP;

	//std::cout << "Ghost is at " << currentPos.x << ", " << currentPos.y << "\n";

	Node targetPos;

	

	if (m_GhostState ==int(GhostState::Normal))
	{

		targetPos.x = int(m_Target->GetLocalPosition().x + 3) / X_STEP;
		targetPos.y = int(m_Target->GetLocalPosition().y + 3) / Y_STEP;


	//	 CheckGhost(m_TypeOfGhost);  //can take Taget Pos by refrence 
	}
	else
	{

		RunAway(currentPos.x, currentPos.y,targetPos); 

	}



	//std::cout << "Playeraaaaaa is at " << targetPos.x << ", " << targetPos.y << "\n";


	auto path = aStar(currentPos, targetPos);
	if (path.size() > 1)
	{
		float x = float(path[1].x * X_STEP);
		float y = float(path[1].y * Y_STEP);
		float deltaX = (x - m_Self->GetLocalPosition().x) /*((currentPos.x != path[1].x) ? 1.f : 1.f)*/;
		if (deltaX < 0) deltaX = -1;
		else if (deltaX > 0) deltaX = 1;
		float deltaY = (y - m_Self->GetLocalPosition().y) /*((currentPos.y != path[1].y) ? 1.f : 1.f)*/;
		if (deltaY < 0) deltaY = -1;
		else if (deltaY > 0) deltaY = 1;

		// Define a threshold for snapping
		const float snapThreshold = 0.1f; // Adjust as needed

		
			// Check if the X coordinate needs to be adjusted
			if (fabs(deltaX) > snapThreshold) {
				// Adjust the X coordinate
				float moveX = (deltaX > 0 ? 1 : -1) * m_Speed * m_pSceneManager->GetDeltaTime();
				m_Self->SetPosition(
					m_Self->GetLocalPosition().x + moveX,
					m_Self->GetLocalPosition().y
				);
			}
		
			// Check if the Y coordinate needs to be adjusted
			if (fabs(deltaY) > snapThreshold) {
				// Adjust the Y coordinate
				float moveY = (deltaY > 0 ? 1 : -1) * m_Speed * m_pSceneManager->GetDeltaTime();
				m_Self->SetPosition(
					m_Self->GetLocalPosition().x,
					m_Self->GetLocalPosition().y + moveY
				);
			}
	
	}
}

void dae::AIComponent::CheckGhost(GhostType WhichGhost)
{

	rowTest = 11;
	Column = 10;


	switch (WhichGhost)
	{
	case dae::GhostType::Blue:

		CheckState();      // can have  mutiple functions since they all ahd different 

		//checkSttae() // al paramteres timepo de espera ,,etc 
		break;
	case dae::GhostType::Red:

		break;
	case dae::GhostType::Pink:

		break;
	case dae::GhostType::Orange:

		break;
	default:
		break;
	}




}

void dae::AIComponent::CheckState()
{



	switch (m_GhotsAiState)
	{
	case dae::GhostAiState::Waiting:

		//between to cells   //can be parameter 



		// 
		// add timer and Call function that checks if it should patrol or chase 




		break;
	case dae::GhostAiState::Patrolling:

		//parameter the array with the points



		 
		break;
	case dae::GhostAiState::Chasing:   //difrents type of chasing 

		// if

		//chase the target 


		break;
	default:
		break;
	}



}

void dae::AIComponent::RunAway(const int& ghotsPosX, const int& ghotsPosY, Node & TargetNode)
{

	
	// set to run away 
  auto vectorValidIndexes = Map::GetInstance().ReturnValidIndexes();   //vector with a tuple of ramdom indexes 

//int first_value = std::get<0>(vectorValidIndexes[rand]);  //10        //row           //vector of valid indexes 
//int second_value = std::get<1>(vectorValidIndexes[rand]);  //1      //colummnb         //vector of valid indexes 

    

  int row{20};          //solo se mueve si es valida la casilla 
  int column{21};

  
auto  Pos = Map::GetInstance().GridToPos(column,row);   //primero column y luego row 


TargetNode.x = (std::get<0>(Pos)) / X_STEP;
TargetNode.y = (std::get<1>(Pos)) /  Y_STEP;




//Node destiantion{};
//destiantion.x = targetPosX = (std::get<0>(Pos)) / X_STEP;     //cualqier pos / step 
//destiantion .y = TargetPosY = (std::get<1>(Pos)) /  Y_STEP;   //opne this here 




if(isDestination(ghotsPosX, ghotsPosY,TargetNode))
{


	auto  Pos2 = Map::GetInstance().GridToPos(1,4);   //primero column y luego row 


	TargetNode.x = (std::get<0>(Pos2)) / X_STEP;
	TargetNode.y = (std::get<1>(Pos2)) / Y_STEP;



}

	//std::cout << TargetNode.x << " " << TargetNode.y<<"\n";










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




	//char mapVisualized[X_MAX / X_STEP][Y_MAX / Y_STEP];

	// for (int y{ 0 }; y < Y_MAX / Y_STEP; y++) {
	// 	for (int x{ 0 }; x < X_MAX / X_STEP; x++) {
	// 		mapVisualized[x][y] = '.';

	// 		for (const auto& node : path) {
	// 			if (node.x == x && node.y == y) {
	// 				mapVisualized[x][y] = 'x';
	// 				break;
	// 			}
	// 		}
	// 		if (currentPos.x == x && currentPos.y == y) {
	// 			mapVisualized[x][y] = 'C';
	// 		}
	// 		if (targetPos.x == x && targetPos.y == y) {
	// 			mapVisualized[x][y] = 'T';
	// 		}
	// 		std::cout << mapVisualized[x][y];
	// 	}
	// 	std::cout << "\n";
	// }