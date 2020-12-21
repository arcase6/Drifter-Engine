#pragma once
#include "Core.h"
#include <unordered_map>
namespace Drifter {

	class Shader
	{
	public:
		static Ref<Shader> Create(const std::string& filepath);
		static Ref<Shader> Create(const std::string& name, const std::string& vert, const std::string& frag);
		virtual ~Shader() = default;
		
		virtual const std::string& GetName() const = 0;
		virtual void Bind() = 0;
		virtual void UnBind() = 0;

		virtual uint32_t GetID() = 0;
	protected:
		uint32_t m_RendererID;
	};

	class ShaderLibrary
	{
	public:
		void RegisterExistingShader(const Ref<Shader> shader);
		void LoadNewShader(const std::string & filepath);
		Ref<Shader> FindShader(const std::string& name);

		bool Exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, Ref<Shader>> m_shaders;
	};
}

