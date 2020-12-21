#include "dfpch.h"
#include "Camera.h"

#include "Drifter/Renderer/Renderer.h"
#include "Platform/OpenGL/Renderer/OpenGLPerspectiveCamera.h"
#include "Platform/OpenGL/Renderer/OpenGLOrthographicCamera.h"
namespace Drifter {
    Ref<PerspectiveCamera> PerspectiveCamera::Create(const glm::vec3& position, const glm::vec3& lookDirection, float fovDegrees, float aspectRatio)
    {
		if (aspectRatio == 0) {
			aspectRatio = Application::Get().GetWindow().GetAspectRatio();
		}
		PerspectiveCamera* camera = nullptr;
		switch (Renderer::GetAPI()) {
		case RendererAPI::None:
			DF_LOG_ERROR("RendererAPI::None is not currently implemented!");
			return nullptr;
		case RendererAPI::OpenGL:
			camera = static_cast<PerspectiveCamera*>(new OpenGLPerspectiveCamera(aspectRatio, fovDegrees));
			break;
		}
		DF_ASSERT(camera,"Unsupported RendererAPI received!");
		
		if (camera) {
			camera->SetPosition(position);
			camera->SetForwardVector(lookDirection);
			camera->SetFOVDegrees(fovDegrees);
			camera->RecalculateTransforms();
		}

		return Ref<PerspectiveCamera>(camera);
    }

	Ref<OrthographicCamera> OrthographicCamera::CreateByAspectRatio(const glm::vec3& position, const glm::vec3& lookDirection, float zoomLevel, float aspectRatio)
	{
		if (aspectRatio == 0) {
			aspectRatio = Application::Get().GetWindow().GetAspectRatio();
		}
		OrthographicCamera* camera = nullptr;
		switch (Renderer::GetAPI()) {
		case RendererAPI::None:
			DF_LOG_ERROR("RendererAPI::None is not currently implemented!");
			return nullptr;
		case RendererAPI::OpenGL:
			camera = static_cast<OrthographicCamera*>(new OpenGLOrthographicCamera(aspectRatio * zoomLevel, zoomLevel));
			break;
		}

		if (camera) {
			camera->SetPosition(position);
			camera->SetForwardVector(lookDirection);
			camera->RecalculateTransforms();
		}
		else {
			DF_LOG_ERROR("Unsupported RendererAPI received!");
		}

		return Ref<OrthographicCamera>(camera);
	}


    Ref<OrthographicCamera> OrthographicCamera::CreateByWidthAndHeight(const glm::vec3& position, const glm::vec3& lookDirection, float zoomLevel, float aspectRatio)
    {
		OrthographicCamera* camera;
		switch (Renderer::GetAPI()) {
		case RendererAPI::None:
			DF_LOG_ERROR("RendererAPI::None is not currently implemented!");
			return nullptr;
		case RendererAPI::OpenGL:
			float width = (float)Application::Get().GetWindow().GetWidth();
			float height = (float)Application::Get().GetWindow().GetHeight();
			camera = static_cast<OrthographicCamera*>(new OpenGLOrthographicCamera(width, height));
			break;
		}
		DF_ASSERT(camera, "Unsupported RendererAPI received!");

		if (camera) {
			camera->SetPosition(position);
			camera->SetForwardVector(lookDirection);
			camera->RecalculateTransforms();
		}

		return Ref<OrthographicCamera>(camera);
    }
}