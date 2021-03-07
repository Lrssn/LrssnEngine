/*
#if defined(_WIN32) || defined(_WIN64) || defined(__WINDOWS__)
	#error Windows_OS
#elif defined(__linux__)
	#error Linux_OS
#elif defined(__APPLE__) && defined(__MACH__)
	#error Mac_OS
#elif defined(unix) || defined(__unix__) || defined(__unix)
	#error Unix_OS
#else
	#error Unknown_OS
#endif
*/

#include <iostream>
#include <imgui/imgui.h>
#include <Lrssnengine.h>


class ExampleLayer : public LrssnEngine::Layer {
public:
	ExampleLayer()
		: Layer("Example") 	{
	}

	void OnUpdate() override 	{
		//LE_INFO("ExampleLayer::Update");
		if (LrssnEngine::Input::IsKeyPressed(LE_KEY_TAB))
			LE_TRACE("Tab key is pressed (poll)!");
	}

	virtual void OnImGuiRender() override 	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(LrssnEngine::Event& event) override 	{
		//LE_TRACE("{0}", event);
		if (event.GetEventType() == LrssnEngine::EventType::KeyPressed) 		{
			LrssnEngine::KeyPressedEvent& e = (LrssnEngine::KeyPressedEvent&)event;
			if (e.GetKeyCode() == LE_KEY_TAB)
				LE_TRACE("Tab key is pressed (event)!");
			LE_TRACE("{0}", e.GetKeyCode());
		}
	}

};

class Sandbox : public LrssnEngine::Application{
public:
	Sandbox(){
		PushLayer(new ExampleLayer());
	};
	~Sandbox(){};

};

LrssnEngine::Application* LrssnEngine::createApplication(){
	return new Sandbox();
}
/*
int main() {

	Sandbox s;
	s.run();
	
	
	return 0;
	const char* name = "Lrssn Engine";
	LRSSNENGINE::Engine e = LRSSNENGINE::Engine(name);

	glm::vec3 newColor = glm::vec3(0.3f, 0.5f, 0.8f);
	float b = 0.0f;
	bool brise = true;
	//e.createObject("res/models/nanosuit.obj");
	e.createObject(trianglePrimitive);
	
	while (!e.shouldEnd()) {
		newColor = glm::vec3(1.0f, 0.6f, b);
		e.getObjects()->at(0).getModels()->at(0).getMeshes()->at(0).getMaterial()->setColor(newColor);
		e.update();
		
		//change color
		if(b<0.0f){
			brise = true;
		}else if(b > 1.0f){
			brise = false;
		}
		(brise) ? b += 0.01f : b -= 0.01f;

	}


	//system("pause");
	return 0;
}
*/