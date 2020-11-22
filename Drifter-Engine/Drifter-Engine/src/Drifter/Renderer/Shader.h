#pragma once

namespace Drifter {

	class Shader
	{
	public:
		Shader(const char* vert, const char* frag);
		virtual ~Shader();

		void Bind();
		void UnBind();

	private:
		unsigned int m_RendererID;
	};
}

