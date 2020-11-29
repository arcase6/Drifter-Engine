#include "Camera.h"

#include "Drifter/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLCamera.h"
namespace Drifter {
    PerspectiveCamera* PerspectiveCamera::Create(const glm::vec3& position, const glm::vec3& lookDirection, float fovDegrees)
    {
		PerspectiveCamera* camera;
		switch (Renderer::GetAPI()) {
		case RendererAPI::None:
			DF_LOG_ERROR("RendererAPI::None is not currently implemented!");
			return nullptr;
		case RendererAPI::OpenGL:
			camera = static_cast<PerspectiveCamera*>(new OpenGLPerspectiveCamera());
			break;
		}
		DF_ASSERT(camera,"Unsupported RendererAPI received!");
		
		if (camera) {
			camera->SetPosition(position);
			camera->SetLookVector(lookDirection);
			camera->SetFOVDegrees(fovDegrees);
			camera->RecalculateTransforms();
		}

		return camera;
    }

    OrthographicCamera* OrthographicCamera::Create(const glm::vec3& position, const glm::vec3& lookDirection)
    {
		OrthographicCamera* camera;
		switch (Renderer::GetAPI()) {
		case RendererAPI::None:
			DF_LOG_ERROR("RendererAPI::None is not currently implemented!");
			return nullptr;
		case RendererAPI::OpenGL:
			camera = static_cast<OrthographicCamera*>(new OpenGLOrthographicCamera());
			break;
		}
		DF_ASSERT(camera, "Unsupported RendererAPI received!");

		if (camera) {
			camera->SetPosition(position);
			camera->SetLookVector(lookDirection);
			camera->RecalculateTransforms();
		}

		return camera;
    }
}