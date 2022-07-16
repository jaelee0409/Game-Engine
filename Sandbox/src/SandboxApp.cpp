#include "pch.h"
#include <Terran.h>

class ExampleLayer : public Terran::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{

	}

	void OnUpdate() override
	{
		TR_INFO("ExampleLayer::Update");
	}

	void OnEvent(Terran::Event& event) override
	{
		TR_TRACE("{0}", event);
	}
};

class Sandbox : public Terran::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Terran::Application* Terran::CreateApplication()
{
	return new Sandbox();
}