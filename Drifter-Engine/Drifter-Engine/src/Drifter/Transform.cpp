#include "dfpch.h"
#include "Transform.h"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/string_cast.hpp"

#include "Debug/Instrumentation.h"
namespace Drifter
{
	glm::mat4 RectTransform::GetTransformMatrix() const{
		PROFILE_RENDERER_FUNCTION();
		using namespace glm;

		mat4 result(1.0);
		//move to pivot
		//result[3].x -= m_Pivot.x;
		//result[3].y -= m_Pivot.y;
		result = translate(glm::mat4(1.0f), { -m_Pivot.x, m_Pivot.y, 0.0f });
		
		//DF_LOG_INFO(glm::to_string(result));
		//scale
		result = scale(glm::mat4(1.0f), { m_Size.x, m_Size.y, 1.0f }) * result;
		//DF_LOG_INFO(glm::to_string(result));

		//rotate
		result = rotate(glm::mat4(1.0f), m_Rotation, { 0.0f, 0.0f, 1.0f }) * result;
		//DF_LOG_INFO(glm::to_string(result));

		//translate
		result = translate(glm::mat4(1.0f), m_Position) * result;
		//DF_LOG_INFO(glm::to_string(result));

		return result;
	}
}