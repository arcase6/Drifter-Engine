#pragma once

namespace Drifter {

	class Shader
	{
	public:
		Shader(const char* vert, const char* frag);
		virtual ~Shader();

		void Bind();
		void UnBind();

		inline uint32_t GetID()
		{
			return m_RendererID;
		}
	private:
		uint32_t m_RendererID;
	};
}

