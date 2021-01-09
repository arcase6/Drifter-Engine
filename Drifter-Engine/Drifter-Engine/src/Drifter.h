#pragma once

// For use by Drifter application
#include "Drifter/Core/Base.h"
#include "Drifter/Application.h"
#include "DebugUtil/Debug.h"
#include "Drifter/Core/Format.h"

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
#include "Drifter/Graphics/Shader.h"
#include "Drifter/Graphics/Uniform.h"
#include "Drifter/Graphics/Texture.h"
#include "Drifter/Camera/Camera.h"
#include "Drifter/Renderer/Renderer.h"