#include "lepch.h"
#include "application.h"
namespace LrssnEngine
{
    Application::Application(){
    }

    Application::~Application(){
    }

    void Application::run(){
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			LE_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			LE_TRACE(e);
		}
        while(true);
    }   
} // namespace LrssnEngine