#pragma once

#include "Lrssnengine.h"

class Sandbox2D : public LrssnEngine::Layer {
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(LrssnEngine::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(LrssnEngine::Event& e) override;
private:
	LrssnEngine::OrthographicCameraController mCameraController;

	// Temp
	LrssnEngine::Ref<LrssnEngine::VertexArray> mSquareVA;
	LrssnEngine::Ref<LrssnEngine::Shader> mFlatColorShader;
	LrssnEngine::Ref<LrssnEngine::Texture2D> mTex;
	glm::vec4 mSquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};