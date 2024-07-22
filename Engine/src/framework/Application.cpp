#include "framework/Application.h"
#include "framework/Core.h"
#include "framework/World.h"
#include "framework/AssetManager.h"
#include "framework/PhysicsSystem.h"
#include "framework/TimerManager.h"
#include <windows.h>
#include <iostream>

namespace ly
{
	float Application::GetMonitorRefreshRate()
	{
		DEVMODE devMode;
		if (EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &devMode))
		{
			return static_cast<float>(devMode.dmDisplayFrequency);
		}
		return 60.0f; // Fallback to 60 Hz if unable to get the refresh rate
	}

	Application::Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, sf::Uint32 style)
		: mWindow{ sf::VideoMode(windowWidth, windowHeight),  title, style },
		mTargetFrameRate{ GetMonitorRefreshRate() },
		mTickClock{},
		mCurrentWorld{ nullptr },
		mCleanCycleClock{},
		mCleanCycleIterval{ 2.f }
	{
		std::cout << "Target Frame Rate: " << mTargetFrameRate << " Hz" << std::endl; // Debugging output
	}

	void Application::Run()
	{
		mTickClock.restart();
		float accumulatedTime = 0.f;
		float targetDeltaTime = 1.f / mTargetFrameRate;
		while (mWindow.isOpen())
		{
			sf::Event windowEvent;
			while (mWindow.pollEvent(windowEvent))
			{
				if (windowEvent.type == sf::Event::EventType::Closed)
				{
					QuitApplication();
				}
				else
				{
					DispathEvent(windowEvent);
				}
			}
			float frameDeltaTime = mTickClock.restart().asSeconds();
			accumulatedTime += frameDeltaTime;
			while (accumulatedTime > targetDeltaTime)
			{
				accumulatedTime -= targetDeltaTime;
				TickInternal(targetDeltaTime);
				RenderInternal();
			}
		}
	}

	sf::Vector2u Application::GetWindowSize() const
	{
		return mWindow.getSize();
	}

	bool Application::DispathEvent(const sf::Event& event)
	{
		if (mCurrentWorld)
		{
			return mCurrentWorld->DispathEvent(event);
		}
		return false;
	}

	void Application::TickInternal(float deltaTime)
	{
		Tick(deltaTime);

		if (mCurrentWorld)
		{
			mCurrentWorld->TickInternal(deltaTime);
		}

		TimerManager::Get().UpdateTimer(deltaTime);

		PhysicsSystem::Get().Step(deltaTime);

		if (mCleanCycleClock.getElapsedTime().asSeconds() >= mCleanCycleIterval)
		{
			mCleanCycleClock.restart();
			AssetManager::Get().CleanCycle();
			if (mCurrentWorld)
			{
				mCurrentWorld->CleanCycle();
			}
		}

		if (mPendingWorld && mPendingWorld != mCurrentWorld)
		{
			mCurrentWorld = mPendingWorld;

			PhysicsSystem::Get().Cleanup();
			mCurrentWorld->BeginPlayInternal();
		}
	}

	void Application::RenderInternal()
	{
		mWindow.clear();

		Render();

		mWindow.display();
	}

	void Application::Render()
	{
		if (mCurrentWorld)
		{
			mCurrentWorld->Render(mWindow);
		}
	}

	void Application::Tick(float deltaTime)
	{

	}

	void Application::QuitApplication()
	{
		mWindow.close();
	}
}
