#include <Lrssnengine.h>
#include <LrssnEngine/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace LrssnEngine {
	class Sandbox : public Application {
	public:
		Sandbox(ApplicationCommandLineArgs args) : Application("Editor", args) {
			PushLayer(new EditorLayer());
		};
		~Sandbox() {};

	};

	Application* createApplication(ApplicationCommandLineArgs args) {
		return new Sandbox(args);
	}
}