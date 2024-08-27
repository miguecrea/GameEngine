#include "AIComponent.h"
#include "GameObject.h"
#include"SceneManager.h"
#include "Renderer.h"
#include"Map.h"

#include <iostream>
#include <vector>
#include <queue>
#include <array>
#include"staticHeader.h"


#include"iostream"
#include <cmath>
#include<set>
#include <stack>


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

	m_Speed = 15.f;
	auto vectorValidIndexes = Map::GetInstance().ReturnValidIndexes();   //vector with a tuple of ramdom indexes 


	switch (m_TypeOfGhost)
	{
	case dae::GhostType::Blue:
		m_copy = m_Speed;
 
		m_GridpositionsToPatrol.push_back(std::make_tuple(26,20));
		m_GridpositionsToPatrol.push_back(std::make_tuple(30,26));
		m_GridpositionsToPatrol.push_back(std::make_tuple(32,15));

  

		break;
	case dae::GhostType::Red:
		m_GridpositionsToPatrol.push_back(std::make_tuple(8,6));
		m_GridpositionsToPatrol.push_back(std::make_tuple(20,13));
		m_GridpositionsToPatrol.push_back(std::make_tuple(8,18));
		m_copy = m_Speed;


		break;
	case dae::GhostType::Pink:
		m_copy = m_Speed;

		m_GridpositionsToPatrol.push_back(std::make_tuple(11, 1));
		m_GridpositionsToPatrol.push_back(std::make_tuple(4,15));
		m_GridpositionsToPatrol.push_back(std::make_tuple(4, 12));
		m_GridpositionsToPatrol.push_back(std::make_tuple(8,26));
		m_GridpositionsToPatrol.push_back(std::make_tuple(17,18));
  
		break;
	case dae::GhostType::Orange:
		m_copy = m_Speed;

		m_GridpositionsToPatrol.push_back(std::make_tuple(26,10));
		m_GridpositionsToPatrol.push_back(std::make_tuple(23, 1));
		m_GridpositionsToPatrol.push_back(std::make_tuple(23, 12));
		m_GridpositionsToPatrol.push_back(std::make_tuple(26, 9));

		break;
	default:
		break;
	}


	

}//puede tomar un game object 


void dae::AIComponent::Render()
{
	

	for (int index = 0; index < path.size(); index++)
	{



		switch (m_TypeOfGhost)
		{
		case dae::GhostType::Blue:
	   Renderer::GetInstance().FillSquare(float(path[index].x * X_STEP * 2),float(path[index].y * Y_STEP*2), 16, 16, SDL_Color{0,0,255,100});
			break;
		case dae::GhostType::Red:
	   Renderer::GetInstance().FillSquare(float(path[index].x * X_STEP * 2),float(path[index].y * Y_STEP*2), 16, 16, SDL_Color{255,0,0,100});
			break;
		case dae::GhostType::Pink:
	   Renderer::GetInstance().FillSquare(float(path[index].x * X_STEP * 2),float(path[index].y * Y_STEP*2), 16, 16, SDL_Color{255,0,255,100});
			break;
		case dae::GhostType::Orange:
	   Renderer::GetInstance().FillSquare(float(path[index].x * X_STEP * 2),float(path[index].y * Y_STEP*2), 16, 16, SDL_Color{255,255,0,100});
			break;
		default:
			break;
		}
	

	}
		

	


}

void dae::AIComponent::Update()
{


	if (s_PauseGame == 1) return;




//////////////////////// SHARED AI 


	m_GhostWaitingTime += SceneManager::GetInstance().GetDeltaTime();

	Node currentPos;
	currentPos.x = int(m_Self->GetLocalPosition().x + 3) / X_STEP;
	currentPos.y = int(m_Self->GetLocalPosition().y + 3) / Y_STEP;

	//std::cout << "Ghost is at " << currentPos.x << ", " << currentPos.y << "\n";

	Node targetPos;


	if (m_GhostState != int(GhostState::Normal))
	{
		m_Speed = 11.f	;
	}
	else
	{
		m_Speed = m_copy;
	}

///////////////////// change the velocity based on speed 

	if (m_GhostState ==int(GhostState::Normal))
	{
		m_timertest += SceneManager::GetInstance().GetDeltaTime();


		CheckGhost(currentPos, targetPos);

	}
	else
	{

		//when is blue it it reset 
		m_timertest = 0;
		RunAway(targetPos); 

	}





	 path = aStar(currentPos, targetPos);


	if (path.size() > 1)
	{
		float x = float(path[1].x * X_STEP);
		float y = float(path[1].y * Y_STEP);
		float deltaX = (x - m_Self->GetLocalPosition().x) ;
		if (deltaX < 0) deltaX = -1;
		else if (deltaX > 0) deltaX = 1;
		float deltaY = (y - m_Self->GetLocalPosition().y) ;
		if (deltaY < 0) deltaY = -1;
		else if (deltaY > 0) deltaY = 1;

		// Define a threshold for snapping
		const float snapThreshold = 0.1f; // Adjust as needed

		
			// Check if the X coordinate needs to be adjusted
			if (fabs(deltaX) > snapThreshold) {
				// Adjust the X coordinate
				float moveX = (deltaX > 0 ? 1 : -1) * m_Speed  * m_pSceneManager->GetDeltaTime();
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


void dae::AIComponent::CheckGhost(Node & ghotsPos,Node & targetpos)
{


	switch (m_TypeOfGhost)  
	{
	case dae::GhostType::Blue:
		
		Patrol(m_GridpositionsToPatrol, ghotsPos, targetpos);


		if (m_timertest >= 10.f)
		{

			Chase(targetpos);

			

		}





	

		break;
	case dae::GhostType::Red:

			Patrol(m_GridpositionsToPatrol, ghotsPos, targetpos);
		
		if (m_timertest >= 10.f)     
		{
			Chase(targetpos);

		}	

		break;
	case dae::GhostType::Pink:


		Patrol(m_GridpositionsToPatrol, ghotsPos, targetpos);

		if (m_timertest >= 10.f)
		{
			Chase(targetpos);

		}

		

		break;
	case dae::GhostType::Orange:


		//aptrol for 10 seodcd chase for 20 
		Patrol(m_GridpositionsToPatrol, ghotsPos, targetpos);

		if (m_timertest >= 10.f)
		{
			Chase(targetpos);

		}

		
		break;
	default:
		break;
	}




}



void dae::AIComponent::RunAway(Node & TargetNode)
{

	
	 
  auto vectorValidIndexes = Map::GetInstance().ReturnValidIndexes();   //vector with a tuple of ramdom indexes 
  
int first_value = std::get<0>(vectorValidIndexes[17]);  //10        //row          
int second_value = std::get<1>(vectorValidIndexes[14]);  //1      //colummnb      


GoTo(first_value,second_value, TargetNode);
    

}

void dae::AIComponent::Patrol(const std::vector<std::tuple<int, int>> & patrolPoints, Node & currentPos,Node& targetPos)
{
	//int index //the problem is that here its gets reseted evertframe

	
	m_rowTest = std::get<0>(patrolPoints[m_index]);
	m_Column = std::get<1>(patrolPoints[m_index]);


	GoTo(m_rowTest, m_Column, targetPos);
	if (HasArrived(currentPos, targetPos))
	{
		
		m_index = (m_index + 1) % m_GridpositionsToPatrol.size();
		
	}

}

void dae::AIComponent::Chase(Node& target)
{
	
	target.x = int(m_Target->GetLocalPosition().x + 3) / X_STEP;
	target.y = int(m_Target->GetLocalPosition().y + 3) / Y_STEP;


}

void dae::AIComponent::GoTo(int  row, int  column, Node& TargetNode)
{


	auto  Pos = Map::GetInstance().GridToPos(column, row);   //primero column y luego row 


	TargetNode.x = (std::get<0>(Pos)) / X_STEP;
	TargetNode.y = (std::get<1>(Pos)) / Y_STEP;


}

bool dae::AIComponent::HasArrived(Node& ghosts, Node& TargetNode)
{
	
	return ghosts.x == TargetNode.x && ghosts.y == ghosts.y;
	
}

float dae::AIComponent::distanceBetweenPoints()
{
	float targetX = m_Target->GetWorldPosition().x;
	float targetY = m_Target->GetWorldPosition().y;
	float selfX = m_Self->GetWorldPosition().x;
	float selfY = m_Self->GetWorldPosition().y;

	// Convert coordinates to float for accurate calculations
	float dx = targetX * 2 - selfX * 2; // Assuming you want to scale the x-coordinate by 2
	float dy = targetY - selfY;

	// Calculate the sum of squares
	float sumOfSquares = dx * dx + dy * dy;

	// Calculate the square root of the sum to get the distance
	float distance = std::sqrt(sumOfSquares);

	return distance;
}











//void dae::AIComponent::Update()
//{
//
//
//	if (s_PauseGame == 1) return;
//
//
//
//
//	//////////////////////// SHARED AI 
//
//
//	m_GhostWaitingTime += SceneManager::GetInstance().GetDeltaTime();
//
//	Node currentPos;
//	currentPos.x = int(m_Self->GetLocalPosition().x + 3) / X_STEP;
//	currentPos.y = int(m_Self->GetLocalPosition().y + 3) / Y_STEP;
//
//	//std::cout << "Ghost is at " << currentPos.x << ", " << currentPos.y << "\n";
//
//	Node targetPos;
//
//
//	if (m_GhostState != int(GhostState::Normal))
//	{
//		m_Speed = 11.f;
//	}
//	else
//	{
//		m_Speed = m_copy;
//	}
//
//	///////////////////// change the velocity based on speed 
//
//	if (m_GhostState == int(GhostState::Normal))
//	{
//		m_timertest += SceneManager::GetInstance().GetDeltaTime();
//
//
//		CheckGhost(currentPos, targetPos);
//
//	}
//	else
//	{
//		m_timertest = 0;
//		RunAway(targetPos);
//
//	}
//
//
//
//
//
//	path = aStar(currentPos, targetPos);
//
//
//	if (path.size() > 1)
//	{
//		float x = float(path[1].x * X_STEP);
//		float y = float(path[1].y * Y_STEP);
//		float deltaX = (x - m_Self->GetLocalPosition().x);
//		if (deltaX < 0) deltaX = -1;
//		else if (deltaX > 0) deltaX = 1;
//		float deltaY = (y - m_Self->GetLocalPosition().y);
//		if (deltaY < 0) deltaY = -1;
//		else if (deltaY > 0) deltaY = 1;
//
//		// Define a threshold for snapping
//		const float snapThreshold = 0.1f; // Adjust as needed
//
//
//		// Check if the X coordinate needs to be adjusted
//		if (fabs(deltaX) > snapThreshold) {
//			// Adjust the X coordinate
//			float moveX = (deltaX > 0 ? 1 : -1) * m_Speed * m_pSceneManager->GetDeltaTime();
//			m_Self->SetPosition(
//				m_Self->GetLocalPosition().x + moveX,
//				m_Self->GetLocalPosition().y
//			);
//		}
//		// Check if the Y coordinate needs to be adjusted
//		if (fabs(deltaY) > snapThreshold) {
//			// Adjust the Y coordinate
//			float moveY = (deltaY > 0 ? 1 : -1) * m_Speed * m_pSceneManager->GetDeltaTime();
//			m_Self->SetPosition(
//				m_Self->GetLocalPosition().x,
//				m_Self->GetLocalPosition().y + moveY
//			);
//		}
//	}
//
//
//
//
//
//
//}
//
//void dae::AIComponent::MoveAlongPath(const std::vector<Node>& path)
//{
//}
//
//void dae::AIComponent::AdjustPosition(float deltaX, float deltaY)
//{
//}
//
//
//void dae::AIComponent::CheckGhost(Node& ghotsPos, Node& targetpos)
//{
//
//
//	switch (m_TypeOfGhost)
//	{
//	case dae::GhostType::Blue:
//
//
//		if (m_GhostWaitingTime >= 20.f)
//		{
//
//			Patrol(m_GridpositionsToPatrol, ghotsPos, targetpos);
//
//
//		}
//		break;
//	case dae::GhostType::Red:
//
//		if (m_timertest >= 1.f)   //executing both
//		{
//			Patrol(m_GridpositionsToPatrol, ghotsPos, targetpos);
//
//		}
//		if (m_timertest >= 10.f)
//		{
//			Chase(targetpos);
//
//		}
//
//		break;
//	case dae::GhostType::Pink:
//
//
//		Patrol(m_GridpositionsToPatrol, ghotsPos, targetpos);
//
//
//		break;
//	case dae::GhostType::Orange:
//
//
//		if (distanceBetweenPoints() <= 80.f)
//		{
//			Chase(targetpos);
//		}
//		else
//		{
//			Patrol(m_GridpositionsToPatrol, ghotsPos, targetpos);
//
//		}
//
//
//		break;
//	default:
//		break;
//	}
//
//
//
//
//}
//
//
//
//void dae::AIComponent::RunAway(Node& TargetNode)
//{
//
//
//
//	auto vectorValidIndexes = Map::GetInstance().ReturnValidIndexes();   //vector with a tuple of ramdom indexes 
//
//	int first_value = std::get<0>(vectorValidIndexes[17]);  //10        //row          
//	int second_value = std::get<1>(vectorValidIndexes[14]);  //1      //colummnb      
//
//
//	GoTo(first_value, second_value, TargetNode);
//
//
//}
//
//void dae::AIComponent::Patrol(const std::vector<std::tuple<int, int>>& patrolPoints, Node& currentPos, Node& targetPos)
//{
//	//int index //the problem is that here its gets reseted evertframe
//
//
//	m_rowTest = std::get<0>(patrolPoints[m_index]);
//	m_Column = std::get<1>(patrolPoints[m_index]);
//
//
//	GoTo(m_rowTest, m_Column, targetPos);
//	if (HasArrived(currentPos, targetPos))
//	{
//
//		m_index = (m_index + 1) % m_GridpositionsToPatrol.size();
//
//	}
//
//}
//
//void dae::AIComponent::Chase(Node& target)
//{
//
//	target.x = int(m_Target->GetLocalPosition().x + 3) / X_STEP;
//	target.y = int(m_Target->GetLocalPosition().y + 3) / Y_STEP;
//
//
//}
//
//void dae::AIComponent::GoTo(int  row, int  column, Node& TargetNode)
//{
//
//
//	auto  Pos = Map::GetInstance().GridToPos(column, row);   //primero column y luego row 
//
//
//	TargetNode.x = (std::get<0>(Pos)) / X_STEP;
//	TargetNode.y = (std::get<1>(Pos)) / Y_STEP;
//
//
//}
//
//bool dae::AIComponent::HasArrived(Node& ghosts, Node& TargetNode)
//{
//
//	return ghosts.x == TargetNode.x && ghosts.y == ghosts.y;
//
//}
//
//float dae::AIComponent::distanceBetweenPoints()
//{
//	float targetX = m_Target->GetWorldPosition().x;
//	float targetY = m_Target->GetWorldPosition().y;
//	float selfX = m_Self->GetWorldPosition().x;
//	float selfY = m_Self->GetWorldPosition().y;
//
//	// Convert coordinates to float for accurate calculations
//	float dx = targetX * 2 - selfX * 2; // Assuming you want to scale the x-coordinate by 2
//	float dy = targetY - selfY;
//
//	// Calculate the sum of squares
//	float sumOfSquares = dx * dx + dy * dy;
//
//	// Calculate the square root of the sum to get the distance
//	float distance = std::sqrt(sumOfSquares);
//
//	return distance;
//}
//





















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