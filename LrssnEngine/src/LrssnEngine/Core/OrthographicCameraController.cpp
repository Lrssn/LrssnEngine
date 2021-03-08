#include "lepch.h"
#include "OrthographicCameraController.h"

#include "LrssnEngine/Core/Input.h"
#include "LrssnEngine/Core/KeyCodes.h"

namespace LrssnEngine {

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: mAspectRatio(aspectRatio), mCamera(-mAspectRatio * mZoomLevel, mAspectRatio* mZoomLevel, -mZoomLevel, mZoomLevel), mCameraRotation(rotation) 	{
	}

	void OrthographicCameraController::OnUpdate(Timestep ts) 	{
		if (Input::IsKeyPressed(LE_KEY_A))
			mCameraPosition.x -= mCameraTranslationSpeed * ts;
		else if (Input::IsKeyPressed(LE_KEY_D))
			mCameraPosition.x += mCameraTranslationSpeed * ts;

		if (Input::IsKeyPressed(LE_KEY_W))
			mCameraPosition.y += mCameraTranslationSpeed * ts;
		else if (Input::IsKeyPressed(LE_KEY_S))
			mCameraPosition.y -= mCameraTranslationSpeed * ts;

		if (m_Rotation) 		{
			if (Input::IsKeyPressed(LE_KEY_Q))
				mCameraRotation += mCameraRotationSpeed * ts;
			if (Input::IsKeyPressed(LE_KEY_E))
				mCameraRotation -= mCameraRotationSpeed * ts;

			mCamera.SetRotation(mCameraRotation);
		}

		mCamera.SetPosition(mCameraPosition);

		mCameraTranslationSpeed = mZoomLevel;
	}

	void OrthographicCameraController::OnEvent(Event& e) 	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(LE_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(LE_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e) 	{
		mZoomLevel -= e.GetYOffset() * 0.25f;
		mZoomLevel = std::max(mZoomLevel, 0.25f);
		mCamera.SetProjection(-mAspectRatio * mZoomLevel, mAspectRatio * mZoomLevel, -mZoomLevel, mZoomLevel);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e) 	{
		mAspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		mCamera.SetProjection(-mAspectRatio * mZoomLevel, mAspectRatio * mZoomLevel, -mZoomLevel, mZoomLevel);
		return false;
	}

}