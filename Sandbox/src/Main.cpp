#include <Lrssnengine.h>
#include <LrssnEngine/Core/EntryPoint.h>

#include "Sandbox2D.h"
#include "ExampleLayer.h"


class Sandbox : public LrssnEngine::Application{
public:
	Sandbox() : Application("Sandbox") {
		PushLayer(new Sandbox2D());
	};
	~Sandbox(){};

};

LrssnEngine::Application* LrssnEngine::createApplication(){
	return new Sandbox();
}