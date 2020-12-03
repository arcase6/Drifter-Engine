#pragma once
#include "Uniform.h"

#include <string>
#include <unordered_map>
namespace Drifter {

	class Material
	{
	public:
		void SetUniformFloat(std::string name, float value);

	private:
		std::unordered_map<std::string, Uniform> m_Uniforms;
	};

}

