#pragma once

#include <Drifter/Layer.h>
#include <Drifter/Window.h>


namespace Drifter::EditorUI {
	class DRIFTER_API ImguiLayer : public Drifter::Layer
	{
	public:
		ImguiLayer(Drifter::Window& window, const std::string& name = "IMGUI Layer");
		~ImguiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnUpdate() override;
		virtual void OnEvent(Drifter::Event& e) override;
	
	private:
		Window& m_window;
		void NewFrameGLFW();
		void EndFrameGLFW();
	};
}

