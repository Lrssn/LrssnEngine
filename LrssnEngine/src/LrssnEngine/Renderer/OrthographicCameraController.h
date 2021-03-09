#pragma once

#include "LrssnEngine/Renderer/OrthographicCamera.h"
#include "LrssnEngine/Core/Timestep.h"

#include "LrssnEngine/Events/ApplicationEvent.h"
#include "LrssnEngine/Events/MouseEvent.h"

namespace LrssnEngine {

	class OrthographicCameraController 	{
	public:
		OrthographicCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		OrthographicCamera& GetCamera() { return mCamera; }
		const OrthographicCamera& GetCamera() const { return mCamera; }
		float GetZoomLevel() const { return mZoomLevel; }
		void SetZoomLevel(float level) { mZoomLevel = level; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
		float mAspectRatio;
		float mZoomLevel = 1.0f;
		OrthographicCamera mCamera;

		bool m_Rotation = 0.0f;

		glm::vec3 mCameraPosition = { 0.0f, 0.0f, 0.0f };
		float mCameraRotation = 0.0f;//In degrees, in the anti-clockwise direction
		float mCameraTranslationSpeed = 5.0f, mCameraRotationSpeed = 180.0f;
	};

}