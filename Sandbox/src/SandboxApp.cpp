#include <TrEngine.h>
class Sandbox : public TrEngine::Application
{
public:
	Sandbox()
	{}
	~Sandbox()
	{}



};

TrEngine::Application* TrEngine::CreateApplication()
{
	return new Sandbox();
}