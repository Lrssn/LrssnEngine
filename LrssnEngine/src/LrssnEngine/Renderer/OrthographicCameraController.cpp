#include "lepch.h"
#include "LrssnEngine/Renderer/OrthographicCameraController.h"

#include "LrssnEngine/Core/Input.h"
#include "LrssnEngine/Core/KeyCodes.h"

namespace LrssnEngine {

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: mAspectRatio(aspectRatio), mCamera(-mAspectRatio * mZoomLevel, mAspectRatio* mZoomLevel, -mZoomLevel, mZoomLevel), mCameraRotation(rotation) 	{
	}

	void OrthographicCameraController::OnUpdate(Timestep ts) 	{
		LE_PROFILE_FUNCTION();
		if (Input::IsKeyPressed(Key::A))		{
			mCameraPosition.x -= cos(glm::radians(mCameraRotation)) * mCameraTranslationSpeed * ts;
			mCameraPosition.y -= sin(glm::radians(mCameraRotation)) * mCameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(Key::D)) {
			mCameraPosition.x += cos(glm::radians(mCameraRotation)) * mCameraTranslationSpeed * ts;
			mCameraPosition.y += sin(glm::radians(mCameraRotation)) * mCameraTranslationSpeed * ts;
		}
		if (Input::IsKeyPressed(Key::W))
		{
			mCameraPosition.x += -sin(glm::radians(mCameraRotation)) * mCameraTranslationSpeed * ts;
			mCameraPosition.y += cos(glm::radians(mCameraRotation)) * mCameraTranslationSpeed * ts;
		}
		else if (Input::IsKeyPressed(Key::S))
		{
			mCameraPosition.x -= -sin(glm::radians(mCameraRotation)) * mCameraTranslationSpeed * ts;
			mCameraPosition.y -= cos(glm::radians(mCameraRotation)) * mCameraTranslationSpeed * ts;
		}

		if (m_Rotation) 		{
			if (Input::IsKeyPressed(Key::Q))
				mCameraRotation += mCameraRotationSpeed * ts;
			if (Input::IsKeyPressed(Key::E))
				mCameraRotation -= mCameraRotationSpeed * ts;

			if (mCameraRotation > 180.0f)
				mCameraRotation -= 360.0f;
			else if (mCameraRotation <= -180.0f)
				mCameraRotation += 360.0f;


			mCamera.SetRotation(mCameraRotation);
		}

		mCamera.SetPosition(mCameraPosition);

		mCameraTranslationSpeed = std::min(std::max(mZoomLevel* mZoomLevel, 1.0f),20.0f);
	}

	void OrthographicCameraController::OnEvent(Event& e) 	{
		LE_PROFILE_FUNCTION();
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(LE_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(LE_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}
	void OrthographicCameraController::OnResize(float width, float height) 	{
		mAspectRatio = width / height;
		mCamera.SetProjection(-mAspectRatio * mZoomLevel, mAspectRatio * mZoomLevel, -mZoomLevel, mZoomLevel);
	}
	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e) 	{
		LE_PROFILE_FUNCTION();
		mZoomLevel -= e.GetYOffset() * 0.25f;
		mZoomLevel = std::max(mZoomLevel, 0.25f);
		mCamera.SetProjection(-mAspectRatio * mZoomLevel, mAspectRatio * mZoomLevel, -mZoomLevel, mZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e) 	{
		LE_PROFILE_FUNCTION();
		OnResize((float)e.GetWidth(), (float)e.GetHeight());
		return false;
	}

}