#include "EditorLayer.h"
#include <imgui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "LrssnEngine/Scene/SceneSerializer.h"
#include "LrssnEngine/Utils/PlatformUtils.h"
#include "LrssnEngine/Math/Math.h"
#include "ImGuizmo.h"



namespace LrssnEngine {

	EditorLayer::EditorLayer()
		: Layer("EditorLayer"), mCameraController(1280.0f / 720.0f), mSquareColor({ 0.2f, 0.3f, 0.8f, 1.0f }) {
	}

	void EditorLayer::OnAttach() {
		LE_PROFILE_FUNCTION();

		mTex = Texture2D::Create("assets/textures/a.png");

		FramebufferSpecification fbSpec;
		fbSpec.Attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::RED_INTEGER, FramebufferTextureFormat::Depth };
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		mFramebuffer = Framebuffer::Create(fbSpec);

		mActiveScene = CreateRef<Scene>();
		mEditorCamera = EditorCamera(30.0f, 1.778f, 0.1f, 1000.0f);
#if 0
		// Entity
		auto square = mActiveScene->CreateEntity("Green Square");
		square.AddComponent<SpriteRendererComponent>(glm::vec4{ 0.0f, 1.0f, 0.0f, 1.0f });

		mSquareEntity = square;
		mCameraEntity = mActiveScene->CreateEntity("Camera A");
		mCameraEntity.AddComponent<CameraComponent>();

		auto redSquare = mActiveScene->CreateEntity("Red Square");
		redSquare.AddComponent<SpriteRendererComponent>(glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f });

		mSecondCamera = mActiveScene->CreateEntity("Camera B");
		auto& cc = mSecondCamera.AddComponent<CameraComponent>();
		cc.Primary = false;

		class CameraController : public ScriptableEntity {
		public:
			virtual void OnCreate() override {
				auto& translation = GetComponent<TransformComponent>().Translation;
				translation.x = rand() % 10 - 5.0f;
			}

			virtual void OnDestroy() override {
			}

			virtual void OnUpdate(Timestep ts) override {
				auto& translation = GetComponent<TransformComponent>().Translation;
				float speed = 5.0f;

				if (Input::IsKeyPressed(Key::A))
					translation.x -= speed * ts;
				if (Input::IsKeyPressed(Key::D))
					translation.x += speed * ts;
				if (Input::IsKeyPressed(Key::W))
					translation.y += speed * ts;
				if (Input::IsKeyPressed(Key::S))
					translation.y -= speed * ts;
			}
		};

		mCameraEntity.AddComponent<NativeScriptComponent>().Bind<CameraController>();
		mSecondCamera.AddComponent<NativeScriptComponent>().Bind<CameraController>();
#endif
		mSceneHierarchyPanel.SetContext(mActiveScene);
	}

	void EditorLayer::OnDetach() {
		LE_PROFILE_FUNCTION();
	}

	void EditorLayer::OnUpdate(Timestep ts) {
		LE_PROFILE_FUNCTION();
		// Resize
		if (FramebufferSpecification spec = mFramebuffer->GetSpecification();
			mViewportSize.x > 0.0f && mViewportSize.y > 0.0f && // zero sized framebuffer is invalid
			(spec.Width != mViewportSize.x || spec.Height != mViewportSize.y)) {
			mFramebuffer->Resize((uint32_t)mViewportSize.x, (uint32_t)mViewportSize.y);
			mCameraController.OnResize(mViewportSize.x, mViewportSize.y);
			mActiveScene->OnViewportResize((uint32_t)mViewportSize.x, (uint32_t)mViewportSize.y);
			mEditorCamera.SetViewportSize(mViewportSize.x, mViewportSize.y);
		}
		// Update
		if (mViewportFocused)
			mCameraController.OnUpdate(ts);
		mEditorCamera.OnUpdate(ts);
		// Render
		Renderer2D::ResetStats();
		mFramebuffer->Bind();
		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		RenderCommand::Clear();
		// Clear our entity ID attachment to -1
		mFramebuffer->ClearAttachment(1, -1);
		// Update scene
		mActiveScene->OnUpdateEditor(ts, mEditorCamera);

		auto [mx, my] = ImGui::GetMousePos();
		mx -= mViewportBounds[0].x;
		my -= mViewportBounds[0].y;
		glm::vec2 viewportSize = mViewportBounds[1] - mViewportBounds[0];
		my = viewportSize.y - my;
		int mouseX = (int)mx;
		int mouseY = (int)my;

		if (mouseX >= 0 && mouseY >= 0 && mouseX < (int)viewportSize.x && mouseY < (int)viewportSize.y) {
			int pixelData = mFramebuffer->ReadPixel(1, mouseX, mouseY);
			mHoveredEntity = pixelData == -1 ? Entity() : Entity((entt::entity)pixelData, mActiveScene.get());
		}

		mFramebuffer->Unbind();
	}

	void EditorLayer::OnImGuiRender() {
		LE_PROFILE_FUNCTION();

		// Note: Switch this to true to enable dockspace
		static bool dockspaceOpen = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen) {
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();
		float minWinSizeX = style.WindowMinSize.x;
		style.WindowMinSize.x = 370.0f;
		
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}
		style.WindowMinSize.x = minWinSizeX;

		if (ImGui::BeginMenuBar()) {
			if (ImGui::BeginMenu("File")) {
				// Disabling fullscreen would allow the window to be moved to the front of other windows, 
				// which we can't undo at the moment without finer window depth/z control.
				//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);
				if (ImGui::MenuItem("New", "Ctrl+N"))
					NewScene();

				if (ImGui::MenuItem("Open...", "Ctrl+O"))
					OpenScene();
				if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
					SaveSceneAs();
				if (ImGui::MenuItem("Exit")) Application::Get().Close();
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}
		mSceneHierarchyPanel.OnImGuiRender();
		
		//Stats screen
		ImGui::Begin("Stats");

		std::string name = "None";
		if (mHoveredEntity)
			name = mHoveredEntity.GetComponent<TagComponent>().Tag;
		ImGui::Text("Hovered Entity: %s", name.c_str());

		auto stats = Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Viewport");
		auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
		auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
		auto viewportOffset = ImGui::GetWindowPos();
		mViewportBounds[0] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
		mViewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };
		
		mViewportFocused = ImGui::IsWindowFocused();
		mViewportHovered = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->BlockEvents(!mViewportFocused && !mViewportHovered);

		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		mViewportSize = { viewportPanelSize.x, viewportPanelSize.y };
		uint64_t textureID = mFramebuffer->GetColorAttachmentRendererID();
		ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ mViewportSize.x, mViewportSize.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

		// Gizmos
		Entity selectedEntity = mSceneHierarchyPanel.GetSelectedEntity();
		if (selectedEntity && mGizmoType != -1) {
			ImGuizmo::SetOrthographic(false);
			ImGuizmo::SetDrawlist();

			ImGuizmo::SetRect(mViewportBounds[0].x, mViewportBounds[0].y, mViewportBounds[1].x - mViewportBounds[0].x, mViewportBounds[1].y - mViewportBounds[0].y);

			// Camera

			// Runtime camera from entity
			// auto cameraEntity = m_ActiveScene->GetPrimaryCameraEntity();
			// const auto& camera = cameraEntity.GetComponent<CameraComponent>().Camera;
			// const glm::mat4& cameraProjection = camera.GetProjection();
			// glm::mat4 cameraView = glm::inverse(cameraEntity.GetComponent<TransformComponent>().GetTransform());

			// Editor camera
			const glm::mat4& cameraProjection = mEditorCamera.GetProjection();
			glm::mat4 cameraView = mEditorCamera.GetViewMatrix();

			// Entity transform
			auto& tc = selectedEntity.GetComponent<TransformComponent>();
			glm::mat4 transform = tc.GetTransform();

			// Snapping
			bool snap = Input::IsKeyPressed(Key::LeftControl);
			float snapValue = 0.5f; // Snap to 0.5m for translation/scale
			// Snap to 45 degrees for rotation
			if (mGizmoType == ImGuizmo::OPERATION::ROTATE)
				snapValue = 45.0f;

			float snapValues[3] = { snapValue, snapValue, snapValue };

			ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection),
				(ImGuizmo::OPERATION)mGizmoType, ImGuizmo::LOCAL, glm::value_ptr(transform),
				nullptr, snap ? snapValues : nullptr);

			if (ImGuizmo::IsUsing()) {
				glm::vec3 translation, rotation, scale;
				Math::DecomposeTransform(transform, translation, rotation, scale);

				glm::vec3 deltaRotation = rotation - tc.Rotation;
				tc.Translation = translation;
				tc.Rotation += deltaRotation;
				tc.Scale = scale;
			}
		}

		ImGui::End();
		ImGui::PopStyleVar();

		ImGui::End();
	}

	void EditorLayer::OnEvent(Event& e) {
		mCameraController.OnEvent(e);
		mEditorCamera.OnEvent(e);
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressedEvent>(LE_BIND_EVENT_FN(EditorLayer::OnKeyPressed));
		dispatcher.Dispatch<MouseButtonPressedEvent>(LE_BIND_EVENT_FN(EditorLayer::OnMouseButtonPressed));
	}

	bool EditorLayer::OnKeyPressed(KeyPressedEvent& e) {
		// Shortcuts
		if (e.GetRepeatCount() > 0)
			return false;

		bool control = Input::IsKeyPressed(Key::LeftControl) || Input::IsKeyPressed(Key::RightControl);
		bool shift = Input::IsKeyPressed(Key::LeftShift) || Input::IsKeyPressed(Key::RightShift);
		switch (e.GetKeyCode()) {
			case Key::N:{
				if (control)
					NewScene();
				break;
			}
			case Key::O:{
				if (control)
					OpenScene();
				break;
			}
			case Key::S:{
				if (control && shift)
					SaveSceneAs();
				break;
			}
			// Gizmos
			case Key::Q: {
				if (!ImGuizmo::IsUsing())
					mGizmoType = -1;
				break;
			}
			case Key::W: {
				if (!ImGuizmo::IsUsing())
					mGizmoType = ImGuizmo::OPERATION::TRANSLATE;
				break;
			}
			case Key::E:{
				if (!ImGuizmo::IsUsing())
					mGizmoType = ImGuizmo::OPERATION::ROTATE;
				break;
			}
			case Key::R:{
				if (!ImGuizmo::IsUsing())
					mGizmoType = ImGuizmo::OPERATION::SCALE;
				break;
			}
		}
	}
	bool EditorLayer::OnMouseButtonPressed(MouseButtonPressedEvent& e) {

		if (e.GetMouseButton() == Mouse::ButtonLeft) {
			if(mViewportHovered && !ImGuizmo::IsOver() && !Input::IsKeyPressed(Key::LeftAlt))
				mSceneHierarchyPanel.GetSelectedEntity(mHoveredEntity);
		}
		return false;
	}
	void EditorLayer::NewScene() {
		mActiveScene = CreateRef<Scene>();
		mActiveScene->OnViewportResize((uint32_t)mViewportSize.x, (uint32_t)mViewportSize.y);
		mSceneHierarchyPanel.SetContext(mActiveScene);
	}

	void EditorLayer::OpenScene() {
		std::optional<std::string> filepath = FileDialogs::OpenFile("LrssnEngine Scene (*.ls)\0*.ls\0");
		if (filepath){
			mActiveScene = CreateRef<Scene>();
			mActiveScene->OnViewportResize((uint32_t)mViewportSize.x, (uint32_t)mViewportSize.y);
			mSceneHierarchyPanel.SetContext(mActiveScene);

			SceneSerializer serializer(mActiveScene);
			serializer.Deserialize(*filepath);
		}
	}

	void EditorLayer::SaveSceneAs() {
		std::optional<std::string> filepath = FileDialogs::SaveFile("LrssnEngine Scene (*.ls)\0*.ls\0");
		if (filepath) {
			SceneSerializer serializer(mActiveScene);
			serializer.Serialize(*filepath);
		}
	}

}