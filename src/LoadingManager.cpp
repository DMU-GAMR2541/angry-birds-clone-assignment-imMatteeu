#include "LoadingManager.h"
#include <iostream>

int spriteCount = 0;
int physicsCount = 0;

LoadingManager::LoadingManager()
{
	progress = 0.f;
	finished = false;
}

LoadingManager::~LoadingManager()
{
	if (spriteThread.joinable()) { spriteThread.join(); }
	if (physicsThread.joinable()) { physicsThread.join(); }
}

void LoadingManager::startLoading()
{
	spriteThread = std::thread(&LoadingManager::loadSprites, this);
	physicsThread = std::thread(&LoadingManager::loadPhysics, this);

	watch = std::async(std::launch::async, &LoadingManager::watchComplete, this);
}

void LoadingManager::loadSprites()
{
	for (int i = 0; i < 50; i++)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		addProgress(1.f);

		spriteCount++;
		std::cout << "Sprite Count: " << spriteCount << std::endl;
	}



}void LoadingManager::loadPhysics()
{
	for (int i = 0; i < 50; i++)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(110));
		addProgress(1.f);


		physicsCount++;
		std::cout << "Physics Count: " << physicsCount << std::endl;
	}
}

void LoadingManager::addProgress(float val)
{
	std::lock_guard<std::mutex> lock(progressMutex);

	progress += val;

	if (progress > 100.f) { progress = 100.f; }
}

void LoadingManager::watchComplete()
{
	while (true)
	{
		{
			std::lock_guard<std::mutex> lock(progressMutex);

			if (progress >= 100.f)
			{
				progress = 100.f;

				finished = true;
				break;
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
}

float LoadingManager::getProgress()
{
	std::lock_guard<std::mutex> lock(progressMutex);
	return progress;
}

bool LoadingManager::isFinished()
{
	std::lock_guard<std::mutex> lock(progressMutex);
	return finished;
}

