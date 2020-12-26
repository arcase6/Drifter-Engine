#pragma once

#include <Drifter/Layer.h>
#include <Drifter/Window.h>


namespace Drifter::EditorUI {
	class ImguiLayer : public Drifter::Layer
	{
	public:
		ImguiLayer(const std::string& name = "IMGUI Layer");
		~ImguiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnImgui() override;
		virtual void OnEvent(Drifter::Event& e) override;
	
		void NewFrameGLFW();
		void EndFrameGLFW();
	private:
		Window& m_window;
	};
}

