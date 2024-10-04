#include "../Core/Logic/Behaviour.h"
#include "../Core/ECS/Coordinator.hpp"
#include "../Core/Input/Input.h"


namespace Collectables
{
	void Start(Entity entity) {
		std::cout << "Collectables Behaviour Started" << std::endl;
	}

	void Update(Entity entity) {
		// Check if player is colliding with collectable

		// If player is colliding with collectable, destroy collectable

		// Add score to player


	}

	void Destroy(Entity entity) {
		std::cout << "Collectables Behaviour Destroyed" << std::endl;
	}

}
