#pragma once

#include "Lrssnengine.h"
#include "Panels/SceneHierarchyPanel.h"

#include "LrssnEngine/Renderer/EditorCamera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace  LrssnEngine {
	class EditorLayer : public Layer {
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& e) override;
		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);

	private:
		void NewScene();
		void OpenScene();
		void SaveSceneAs();

		OrthographicCameraController mCameraController;
		
		// Temp
		Ref<VertexArray> mSquareVA;
		Ref<Shader> mFlatColorShader;
		Ref<Framebuffer> mFramebuffer;

		Ref<Scene> mActiveScene;
		Entity mSquareEntity;

		Entity mCameraEntity;
		Entity mSecondCamera;

		bool mPrimaryCamera = true;
		EditorCamera mEditorCamera;
		Ref<Texture2D> mTex;
		bool mViewportFocused = false, mViewportHovered = false;
		glm::vec2 mViewportSize = { 0.0f, 0.0f };
		glm::vec2 mViewportBounds[2];
		glm::vec4 mSquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
		int mGizmoType = -1;
		Entity mHoveredEntity;
		// Panels
		SceneHierarchyPanel mSceneHierarchyPanel;
	};
}