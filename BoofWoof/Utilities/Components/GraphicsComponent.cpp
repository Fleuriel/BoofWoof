//#include "GraphicsComponent.h"
#include "../Core/Graphics/GraphicsSystem.h"
#include "../Core/AssetManager/AssetManager.h"

//#include "../Core/Graphics/Object.h"


void GraphicsComponent::addModel(std::string const& path)
{
	Model model;
	model.loadModel(path, GL_TRIANGLES);
	g_AssetManager.Models.push_back(model);
}

void GraphicsComponent::addObject(glm::vec3 position, glm::vec3 scale, glm::vec3 rotation, glm::vec3 color, Model* model)
{
	Object object;
	object.model = model;
	object.position = position;
	object.scale = scale;
	object.rotation = rotation;
	object.color = color;
	g_AssetManager.Objects.push_back(object);
}




GraphicsComponent::GraphicsComponent()
 {}


//GraphicsComponent::GraphicsComponent(const OpenGLModel& model, int id)
//    : model_To_NDC_xform(1.0f), Position(0.0f), ScaleModel(0.5f),
//    setColor(1.0f), setColorLeft(1.0f), setColorRight(1.0f),
//    PositionLeft(0.0f), PositionRight(0.0f),
//    AngleLeft(0.0f), AngleRight(0.0f),
//    angleX(0.0f), angleY(0.0f), angleZ(0.0f),
//    angleSpeed(0.0f), TagID(id), model_to_create(model), size(1.0f) {}

//
//void GraphicsSystem::Update() {
//    for (auto& entity : mEntities) {
//        // Assuming you have a way to get the component data
//        GraphicsComponent& graphicObject = gCoordinator.GetComponent<GraphicsComponent>(entity);
//
//        // Use shader
//        assetManager.shdrpgms[graphicObject.shd_ref].Use();
//
//        // Bind vertex array to VAOID
//        glBindVertexArray(models[graphicObject.mdl_ref].vaoid); // Bind object's VAO handle
//
//        // Similar draw logic using graphicObject...
//        // Your draw logic here (same as your Draw function)
//
//        // Unbind VAO and shader
//        glBindVertexArray(0);
//        assetManager.shdrpgms[graphicObject.shd_ref].UnUse();
//    }
//}

