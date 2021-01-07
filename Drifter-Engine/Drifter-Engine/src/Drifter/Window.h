#pragma once
#include "dfpch.h"

#include <Core.h>
#include <Drifter/Events/Event.h>
#include <Drifter/Graphics/GraphicsContext.h>


namespace Drifter {
	struct WindowProps
	{
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Drifter Engine",
					unsigned int width = 1280,
					unsigned int height = 720)
		:Title(title), Width(width), Height(height){}
	};

	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;
		
		virtual ~Window() {}
		
		virtual void OnFrameBegin() = 0;
		virtual void OnFrameEnd() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
		virtual float GetAspectRatio() const = 0;

		virtual void* GetNativeWindow() const = 0;

		//Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void SetCaptureMouseFlag(bool flag) = 0;
		virtual bool GetCaptureMouseFlag() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}