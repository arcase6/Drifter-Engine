#pragma once
#include "Drifter/Renderer/Material/Shader.h"
namespace Drifter {
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const char* vert, const char* frag);
		virtual ~OpenGLShader() = default;
		virtual void Bind() override;
		virtual void UnBind() override;

		virtual inline uint32_t GetID() override {
			return m_RendererID;
		}
	protected:
		uint32_t m_RendererID;
	};
}
