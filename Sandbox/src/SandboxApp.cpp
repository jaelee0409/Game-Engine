#include "pch.h"
#include <Terran.h>

class Sandbox : public Terran::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Terran::Application* Terran::CreateApplication()
{
	return new Sandbox();
}