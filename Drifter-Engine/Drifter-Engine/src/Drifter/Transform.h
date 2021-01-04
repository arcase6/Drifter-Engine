#pragma once

#include "glm/glm.hpp"
namespace Drifter {
	class Transform
	{
	public:
		virtual ~Transform() = default;
		virtual glm::mat4 GetTransformMatrix() const = 0;
	};

	class RectTransform : public Transform
	{
	public:
		RectTransform(glm::vec3 position, glm::vec2 size, float rotation = 0.0f, glm::vec2 pivot = { 0.5f, 0.5f }):
			m_Position(position), m_Size(size), m_Rotation(rotation), m_Pivot(pivot)
		{
			if (rotation != 0.0f) {
				RecalculateRotationMatrix();
			}
		}

		RectTransform(glm::vec2 position, glm::vec2 size, float rotation = 0.0f, glm::vec2 pivot = { 0.5f, 0.5f }) :
			m_Position({ position.x, position.y, 0.0f }), m_Size(size), m_Rotation(rotation), m_Pivot(pivot)
		{
			if (rotation != 0.0f) {
				RecalculateRotationMatrix();
			}
		}

		void SetSize(const glm::vec2& value)     { m_Size = value;	   }
		void SetPosition(const glm::vec3& value) { m_Position = value; }
		void SetPivot(const glm::vec2& value)    { m_Pivot = value;	   }
		void SetRotationRadians(float value) { m_Rotation = value; RecalculateRotationMatrix(); }
		void SetRotationDegrees(float value)     { m_Rotation = glm::radians(value);  RecalculateRotationMatrix(); }
		
		glm::vec3 GetPosition() const { return m_Position; }
		glm::vec2 GetSize() const { return m_Size; }
		float GetRotationDegrees() const { return glm::degrees(m_Rotation); }
		float GetRotationRadians() const { return m_Rotation; }
		glm::vec2 GetPivot() const { return m_Pivot; }

		//inherited from Transform
		virtual glm::mat4 GetTransformMatrix() const override;
	private:
		void RecalculateRotationMatrix();

		glm::vec3 m_Position;
		glm::vec2 m_Size;

		float m_Rotation;
		glm::mat4 m_RotationMatrix{ 1.0f};
		glm::vec2 m_Pivot;

	};
}

