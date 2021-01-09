#include "dfpch.h"
#include "Shader.h"
#include "Drifter/Renderer/Renderer.h"

#include "Platform/OpenGL/Graphics/OpenGLShader.h"
namespace Drifter {
	Ref<Shader> Shader::Create(const std::string& filepath) {
		Ref<Shader> result;
		switch (Renderer::GetAPI()) {
		case RendererAPI::None:
			DF_LOG_ERROR("RendererAPI::None is not currently implemented!");
			return nullptr;
		case RendererAPI::OpenGL:
			//result.reset(static_cast<Shader *>(new OpenGLShader(filepath)));
			//return result;
			return Ref<Shader>(static_cast<Shader*>(new OpenGLShader(filepath)));
		}
		DF_CORE_ASSERT_UNREACHABLE_LV1("Unsupported RendererAPI received!");
		return nullptr;
	}


	Ref<Shader> Shader::Create(const std::string& name, const std::string& vert, const std::string& frag) {
		Ref<Shader> result;
		switch (Renderer::GetAPI()) {
		case RendererAPI::None:
			DF_CORE_ASSERT_UNREACHABLE_LV1("RendererAPI::None is not currently implemented!");
			return nullptr;
		case RendererAPI::OpenGL:
			return CreateRef<OpenGLShader>(name, vert, frag);
		}
		DF_CORE_ASSERT_UNREACHABLE_LV1("Unsupported RendererAPI received!");
		return nullptr;
	}


	void ShaderLibrary::RegisterExistingShader(const Ref<Shader> shader) {
		DF_CORE_ASSERT_LV2(!Exists(shader->GetName()), "Shader already exists");
		m_shaders[shader->GetName()] = shader;
	}

	void ShaderLibrary::LoadNewShader(const std::string& filepath) {
		Ref<Shader> shader = Shader::Create(filepath);
		m_shaders[shader->GetName()] = shader;
	}

	Ref<Shader>  ShaderLibrary::FindShader(const std::string& name) {
		DF_CORE_ASSERT_LV2(Exists(name), "Shader not found");
		return m_shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const {
		return m_shaders.find(name) != m_shaders.end();
	}

}
