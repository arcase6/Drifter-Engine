#pragma once

#ifndef GLM_FORCE_SWIZZLE
#define GLM_FORCE_SWIZZLE
#endif
#include <glm/glm.hpp>

namespace Drifter {
	class Camera
	{
	public:
		virtual glm::vec3 GetPosition() const = 0;
		virtual void SetPosition(const glm::vec3& position) = 0;

		virtual void LookAt(const glm::vec3& target) = 0;
		virtual void SetForwardVector(const glm::vec3& forwardVector) = 0;
		virtual void SetRotationEuler(float yaw, float pitch, float roll) = 0;

		virtual glm::vec3 GetForwardVector() const = 0;
		virtual glm::vec3 GetUpVector() const = 0;
		virtual glm::vec3 GetRightVector() const const = 0;

		virtual glm::mat4 GetViewMatrix() const = 0;
		virtual glm::mat4 GetProjectionMatrix() const = 0;

		virtual float GetNearClipDistance() const = 0;
		virtual void SetNearClipDistance(float distance) = 0;

		virtual float GetFarClipDistance() const = 0;
		virtual void SetFarClipDistance(float distance) = 0;

		virtual void RecalculateTransforms() = 0;
	};

	class PerspectiveCamera : public Camera
	{
	public:
		static Ref<PerspectiveCamera> Create(const glm::vec3& position, const glm::vec3& lookDirection, float fovDegrees = 60.0f, float aspectRatio = 0.0f);

		virtual float GetAspectRatio() const = 0;
		virtual void SetAspectRatio(float aspectRatio) = 0;

		virtual float GetFOVDegrees() const = 0;
		virtual void SetFOVDegrees(float value) = 0;

		virtual float GetFOVRadians() const = 0;
		virtual void SetFOVRadians(float value) = 0;
	};

	class OrthographicCamera : public Camera
	{
	public:
		static Ref<OrthographicCamera> CreateByAspectRatio(const glm::vec3& position, const glm::vec3& lookDirection, float zoomLevel = 1.0f, float aspectRatio = 0.0f);
		static Ref<OrthographicCamera> CreateByWidthAndHeight(const glm::vec3& position, const glm::vec3& lookDirection, float width, float height);

		virtual void SetDimensions(float width, float height) = 0;
		virtual void SetZoomAndAspectRatio(float zoomLevel, float aspectRatio) = 0;

		virtual float GetWidth() const = 0;
		virtual float GetHeight() const = 0;

		virtual float GetZoomLevel() const = 0;
		virtual float GetAspectRatio() const = 0;

	};
}
