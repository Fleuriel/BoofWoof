#include "EngineCore.h"

std::shared_ptr<GraphicsSystem> mGraphicsSys;
std::shared_ptr<LogicSystem> mLogicSys;

void EngineCore::OnInit()
{
	// if need to deserialize anything
	
	// initialize window stuff, set window height n width n wtv
	// tempo b4 serialization
	g_WindowX = 1920;
	g_WindowY = 1080;
	g_Window = new Window(g_WindowX, g_WindowY, "Boof Woof");
	g_Window->SetWindowWidth(g_WindowX);
	g_Window->SetWindowHeight(g_WindowY);

	g_Window->OnInitialize();

	// register components here
	g_Coordinator.Init();
	g_Coordinator.RegisterComponent<MetadataComponent>();
	g_Coordinator.RegisterComponent<TransformComponent>();
	g_Coordinator.RegisterComponent<GraphicsComponent>();

	g_Coordinator.RegisterComponent<BehaviourComponent>();

	// setting global pointer
	g_Core = this;

	// Set up your global managers
	g_SceneManager;

	// register system & signatures

	mLogicSys = g_Coordinator.RegisterSystem<LogicSystem>();
	{
		Signature signature;
		signature.set(g_Coordinator.GetComponentType<BehaviourComponent>());
		g_Coordinator.SetSystemSignature<LogicSystem>(signature);
	}


	mGraphicsSys = g_Coordinator.RegisterSystem<GraphicsSystem>();
	{
		Signature signature;
		signature.set(g_Coordinator.GetComponentType<TransformComponent>());
		signature.set(g_Coordinator.GetComponentType<GraphicsComponent>());
		g_Coordinator.SetSystemSignature<GraphicsSystem>(signature);
	}

	// Create entities
	{
		Entity entity = g_Coordinator.CreateEntity();
		g_Coordinator.AddComponent(entity, TransformComponent());
		g_Coordinator.AddComponent(entity, GraphicsComponent());
		g_Coordinator.AddComponent(entity, BehaviourComponent("Movement", entity));
		g_Coordinator.AddComponent(entity, MetadataComponent("Player", entity));
	}
	

	// init system
	mLogicSys->Init();
	mGraphicsSys->initGraphicsPipeline();
	
	

	

	// Just leave this part at the most bottom
	m_AccumulatedTime = 0.0;		// elapsed time
	m_CurrNumSteps = 0;
}

void EngineCore::OnUpdate()
{
	m_CurrNumSteps = 0;
	m_DeltaTime = m_EndTime - m_StartTime;	// start at 0
	m_StartTime = g_Timer.GetCurrentTime();
	m_AccumulatedTime += m_DeltaTime;

	while (m_AccumulatedTime >= m_FixedDT)
	{
		m_AccumulatedTime -= m_FixedDT;
		m_CurrNumSteps++;
	}

	// Cap at 4 to avoid performance hit due to too many steps in single frame
	if (m_CurrNumSteps >= 4)
	{
		m_CurrNumSteps = 4;
	}

	// window update
	g_Window->OnUpdate();

	// input update
	g_Input.UpdateStatesForNextFrame();

	//Transition
	g_SceneManager.Update(m_DeltaTime);

	// system updates
	{
		// Logic
		mLogicSys->Update();
		// Graphics
		mGraphicsSys->UpdateLoop();
		m_GraphicsDT = g_Timer.GetElapsedTime();
		
	}


	/*
	//Test serialization
	if (g_Input.GetKeyState(GLFW_KEY_P) == 1) {  // Save engine state
		std::cout << "P key pressed, saving engine state..." << std::endl;
		g_SceneManager.SaveScene("Saves/engine_state.json");
		std::cout << "Engine state saved to Saves/engine_state.json" << std::endl;
	}

	if (g_Input.GetKeyState(GLFW_KEY_O) == 1) {  // Reset entities
		std::cout << "O key pressed, resetting entities..." << std::endl;
		g_Coordinator.ResetEntities();
		std::cout << "Entities reset!" << std::endl;
	}

	if (g_Input.GetKeyState(GLFW_KEY_L) == 1) {  // Load engine state
		std::cout << "L key pressed, loading engine state..." << std::endl;
		g_SceneManager.SaveScene("Saves/engine_state.json");
		std::cout << "Engine state loaded from Saves/engine_state.json" << std::endl;
	}
	*/
	





	// keep this at the end
	m_ElapsedDT = m_GraphicsDT; // to add more DT when more systems comes up
	m_EndTime = g_Timer.GetCurrentTime();
}

void EngineCore::OnShutdown()
{
	// Shutdown window and other systems
	g_Window->OnShutdown();
}