#pragma once

#include <glm/glm.hpp>
namespace Drifter {
	class Camera
	{
	public:
		virtual glm::vec3 GetPosition() const = 0;
		virtual void SetPosition(const glm::vec3& position) = 0;
		
		virtual float GetWidth() const = 0;
		virtual float GetHeight() const = 0;
		
		virtual void SetWidth(float width) = 0;
		virtual void SetHeight(float height) = 0;

		virtual void SetLookVector(const glm::vec3& lookVector) = 0;
		virtual void LookAt(const glm::vec3& target) = 0;


		virtual glm::mat4 GetViewMatrix() const = 0;
		virtual glm::mat4 GetProjectionMatrix() const = 0;


		virtual float GetNearClipDistance() const= 0;
		virtual void SetNearClipDistance(float distance) = 0;

		virtual float GetFarClipDistance() const = 0;
		virtual void SetFarClipDistance(float distance) = 0;

		virtual void RecalculateTransforms() = 0;
	};

	class PerspectiveCamera : virtual public Camera
	{
	public:
		static PerspectiveCamera* Create(const glm::vec3& position, const glm::vec3& lookDirection, float fovDegrees);

		virtual float GetFOVDegrees() const = 0;
		virtual void SetFOVDegrees(float value) = 0;

		virtual float GetFOVRadians() const = 0;
		virtual void SetFOVRadians(float value) = 0;
	};

	class OrthographicCamera : virtual public Camera
	{
	public:
		static OrthographicCamera* Create(const glm::vec3& position, const glm::vec3& lookDirection);

	};
}
