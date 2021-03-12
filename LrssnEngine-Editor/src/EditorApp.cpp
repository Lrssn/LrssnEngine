#include <Lrssnengine.h>
#include <LrssnEngine/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace LrssnEngine {
	class Sandbox : public Application {
	public:
		Sandbox() : Application("Editor") {
			PushLayer(new EditorLayer());
		};
		~Sandbox() {};

	};

	Application* createApplication() {
		return new Sandbox();
	}
}