#include "lepch.h"
#include "LrssnEngine/Renderer/Shader.h"

#include "LrssnEngine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace LrssnEngine {
	Ref<Shader> Shader::Create(const std::string& filepath) {
		switch (Renderer::GetAPI()) {
			case RendererAPI::API::None:    LE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLShader>(filepath);
		}

		LE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) {
		switch (Renderer::GetAPI()){
			case RendererAPI::API::None:    LE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:	return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
		}
		LE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader) {
		LE_CORE_ASSERT(!Exists(name), "Shader already exists!");
		mShaders[name] = shader;
	}

	void ShaderLibrary::Add(const Ref<Shader>& shader) {
		auto& name = shader->GetName();
		Add(name, shader);
	}

	Ref<LrssnEngine::Shader> ShaderLibrary::Load(const std::string& filepath) {
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Ref<LrssnEngine::Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath) {
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	Ref<LrssnEngine::Shader> ShaderLibrary::Get(const std::string& name) {
		LE_CORE_ASSERT(Exists(name), "Shader not found!");
		return mShaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const {
		return mShaders.find(name) != mShaders.end();
	}
}