#include "tankAI.h"
#define MAXLIFES 3;
#define MAXAMMO 5;
//#define COMPASS [NORTH, WEST, SOUTH, EAST];

TankAI::TankAI(){
	AI.base = new Object("tankbase.obj", 50, btVector3(0, 0, 0), btVector3(0, .5, 0), 0, 0, 0, 1);
	//adjust so that it lied on top of the base
	AI.head = new Object("turret.obj", 50, btVector3(0, 0, 0), btVector3(0, 10, 0), 0, 0, 0, 1);
	SetOrientation();

	AI.lives = MAXLIFES;
	AI.ammo = MAXAMMO;
	AI.initialTime = 0;
	AI.compassPosition = 0; 
	// left, right, forwards, backward, stop
	
	// in seconds
	AI.timeLeft = rand() % 100;
}

TankAI::~TankAI(){

}

void TankAI::Render(GLint modelMatrix, Uniform scalar, Uniform spec, Uniform spot, Uniform height){

  glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, glm::value_ptr(AI.base->GetModel()));
  AI.base->Render(scalar, spec, spot, height);

  glUniformMatrix4fv(modelMatrix, 1, GL_FALSE, glm::value_ptr(AI.head->GetModel()));
  AI.head->Render(scalar, spec, spot, height);
}

void TankAI::Update(unsigned int dt){
	
	//no action given yet
	if (dt-AI.initialTime >= AI.timeLeft){
		AI.timeLeft = (rand() % 2000)+2000;
		AI.direction = rand() % 5;
		switch (AI.direction){
			case 1:
				AI.compassPosition --;
				if (AI.compassPosition < 0)
					AI.compassPosition = 4;
			break;
			case 2:
				AI.compassPosition ++;
				if (AI.compassPosition > 4)
					AI.compassPosition = 0;
			break;
		}
		AI.initialTime = dt;
		AI.base->GetRigidBody()->setLinearVelocity(btVector3(0.0f, 0.0f, 0.0f));
		AI.base->GetRigidBody()->setAngularVelocity(btVector3(0.0f, 0.0f, 0.0f));
	}

	//action given
	switch (AI.direction){
		// Left
		case 1:
			AI.base->rotate(glm::vec3 (0.0f, -1.0, 0.0f));
		break;
		//Right
		case 2:
			AI.base->rotate(glm::vec3 (0.0f, 1.0, 0.0f));
		break;
		//Forward
		case 3:
			switch (AI.compassPosition){
				//North
				case 1:
					AI.base->translate(glm::vec3 (0.0f, 0.0, 1.0f));
				break;
				//West
				case 2:
					AI.base->translate(glm::vec3 (0.0f, 0.0, -1.0f));
				break;
				//East
				case 3:
					AI.base->translate(glm::vec3 (1.0f, 0.0, 0.0f));
				break;
				//South
				case 4:
					AI.base->translate(glm::vec3 (-1.0f, 0.0, 0.0f));
				break;
			}
		break;
		//Backwards
		case 4:
			AI.base->translate(glm::vec3 (0.0f, 0.0, -1.0f));
		break; 
		//Nothing
		case 5:
		break;
	}
	SetOrientation();
	std:: cout << AI.compassPosition << " " << AI.direction << std:: endl; 
}

Object* TankAI::GetAIBase(){
	return AI.base;
}

Object* TankAI::GetAIHead(){
	return AI.head;
}

void TankAI::SetOrientation(){
	AI.base->setOrientation();
	AI.head->setOrientation();
}