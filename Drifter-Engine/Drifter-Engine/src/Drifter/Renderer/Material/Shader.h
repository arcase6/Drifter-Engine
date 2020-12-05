#pragma once

namespace Drifter {

	class Shader
	{
	public:
		static Shader* Create(const char* vert, const char* frag);
		virtual ~Shader() = default;

		virtual void Bind() = 0;
		virtual void UnBind() = 0;

		virtual uint32_t GetID() = 0;
	protected:
		uint32_t m_RendererID;
	};
}

