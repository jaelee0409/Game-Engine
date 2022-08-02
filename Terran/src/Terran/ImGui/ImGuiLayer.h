#pragma once

#include "Terran/Core/Layer.h"

#include "Terran/Events/ApplicationEvent.h"
#include "Terran/Events/KeyEvent.h"
#include "Terran/Events/MouseEvent.h"

namespace Terran {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}