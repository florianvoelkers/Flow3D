#include "Application.hpp"

#include "Input.hpp"
#include "Rendering/RenderingEngine.hpp"
#include "Log.hpp"

// basic file operations
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>

// metastuff testing
#include <MetaStuff/include/Meta.h>
#include "Person.hpp"
#include <json/json.hpp>
#include <MetaStuff/include/JsonCast.h>

namespace Flow {

	using json = nlohmann::json;

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		// missing assert for making sure there is only one instance
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(FLOW_BIND_EVENT_FUNCTION(Application::OnEvent));
		
		m_Input = std::make_unique<Input>();
		m_RenderingEngine = std::make_unique<RenderingEngine>(*m_Window);

		m_NextObjectID = -1;

		m_ResourceManager = std::make_unique<ResourceManager>();

		m_CurrentScene = std::make_unique<Scene>("TestScene", *m_Window);
		m_CurrentScene->OnAttach();

		m_ImGui = std::make_unique<ImGuiLayer>();
		m_ImGui->OnAttach();		

		std::ofstream myfile;
		myfile.open("example.json");
		myfile << "Writing something different to a file.\n";
		myfile.close();

		Person person;
		person.age = 25;
		person.salary = 3.50f;
		person.name = "Alex"; // I'm a person!

		person.favouriteMovies["Nostalgia Critic"] = { MovieInfo{ "The Room", 8.5f } };
		person.favouriteMovies["John Tron"] = { MovieInfo{ "Goosebumps", 10.0f },
			MovieInfo{ "Talking Cat", 9.0f } };

		// printing members of different classes
		std::cout << "Members of class Person:\n";
		meta::doForAllMembers<Person>(
			[](const auto& member)
		{
			std::cout << "* " << member.getName() << '\n';
		}
		);

		std::cout << "Members of class MovieInfo:\n";
		meta::doForAllMembers<MovieInfo>(
			[](const auto& member)
		{
			std::cout << "* " << member.getName() << '\n';
		}
		);

		std::cout << "========================\n";

		// checking if classes are registered
		if (meta::isRegistered<Person>()) {
			std::cout << "Person class is registered\n";
			std::cout << "It has " << meta::getMemberCount<Person>() << " members registered.\n";
		}

		// meta::isRegistered is constexpr, so can be used in enable_if and static_assert!
		static_assert(meta::isRegistered<Person>(), "Person class is not registered!");
		static_assert(meta::getMemberCount<Person>() == 4, "Person does not have 4 members registered?");

		// checking if class has a member
		if (meta::hasMember<Person>("age")) {
			std::cout << "Person has member named 'age'\n";
		}

		// getting members
		auto age = meta::getMemberValue<int>(person, "age");
		std::cout << "Got person's age: " << age << '\n';

		auto name = meta::getMemberValue<std::string>(person, "name");
		std::cout << "Got person's name: " << name << '\n';

		// setting members
		meta::setMemberValue<std::string>(person, "name", "Ron Burgundy");
		name = meta::getMemberValue<std::string>(person, "name");
		std::cout << "Changed person's name to " << name << '\n';

		std::cout << "========================\n";

		// And here's how you can serialize/deserialize
		// (if you write a function for your type)
		std::cout << "Serializing person:" << '\n';
		json root = person;
		std::cout << root << std::endl;

		myfile.open("person.json");
		myfile << std::setw(4) << root;
		myfile.close();

		//Unregistered y;
		//json root2 = y; // this will fail at compile time

		std::cout << "========================\n";

		std::cout << "Serializing Person 2 from JSON:\n";

		auto person2 = root.get<Person>();
		std::cout << "Person 2 name is " << person2.getName() << " too!" << '\n';
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		// application loop: at the moment it runs as fast as it can
		// TODO: setting the frame rate / constant frame rate
		double lastTime = glfwGetTime();

		// for counting frames, but GLFW limits the fps to 60 because of VSYNC to avoid screen tearing
		unsigned int numberOfFrames = 0;
		double lastSecond = lastTime;
		while (m_Running)
		{
			double current = glfwGetTime();
			double elapsed = current - lastTime;
			lastTime = current;

			numberOfFrames++;
			if (current - lastSecond >= 1.0)
			{
				m_ImGui->GetLogger().AddLog("fps: %d\n", numberOfFrames);
				numberOfFrames = 0;
				lastSecond += 1.0f;
			}

			m_Input->OnUpdate(elapsed);
			m_CurrentScene->OnUpdate(elapsed);
			m_RenderingEngine->Render(m_CurrentScene->GetRoot(), m_CurrentScene->GetMainCamera(), m_CurrentScene->GetSkybox());
			m_ImGui->OnUpdate(elapsed);
			m_Window->OnUpdate();
		}
	}

	void Application::Quit()
	{
		m_Running = false;
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(FLOW_BIND_EVENT_FUNCTION(Application::OnWindowClose));
		dispatcher.Dispatch<KeyPressedEvent>(FLOW_BIND_EVENT_FUNCTION(Application::OnKeyPressed));

		m_ImGui->OnEvent(e);
		m_Input->OnEvent(e);		
		m_CurrentScene->OnEvent(e);
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnKeyPressed(KeyPressedEvent& e)
	{
		if (e.GetKeyCode() == (int)Keycode::Escape)
			m_Running = false;

		if (e.GetKeyCode() == (int)Keycode::F10)
		{
			bool receiveEvents = m_ImGui->GetReceiveEvents();
			m_Window->ShowMouse(!receiveEvents);
			m_ImGui->ToggleReceiveEvents();
		}			

		return false; // returns false because other functions should be able to receive those events as well
 	}

	int Application::GetNextObjectID()
	{
		m_NextObjectID++;
		return m_NextObjectID;
	}
}
