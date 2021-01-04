#pragma once

// For use by Drifter application
#include "Core.h"
#include "Drifter/Application.h"
#include "Debug/Instrumentation.h"

//Layers
#include "Drifter/Layer.h"
#include "Drifter/EditorUI/ImguiLayer.h"

//Input
#include "Drifter/Input/Input.h"
#include "Drifter/Input/KeyCodes.h"
#include "Drifter/Input/MouseCodes.h"

//Time
#include "Drifter/Core/Time.h"

//Math
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtx/string_cast.hpp>

//Rendering
#include "Drifter/Renderer/Shaders/Shader.h"
#include "Drifter/Renderer/Shaders/Uniform.h"
#include "Drifter/Renderer/Shaders/Texture.h"
#include "Drifter/Renderer/Cameras/Camera.h"
#include "Drifter/Renderer/Renderer.h"