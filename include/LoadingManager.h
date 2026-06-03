#pragma once

#include <thread>
#include <mutex>
#include <future>
#include <chrono>


class LoadingManager
{
public:

	LoadingManager();
	~LoadingManager();
	
	void startLoading();

	void loadSprites();
	void loadPhysics();

	float getProgress();
	bool isFinished();

private:

	std::thread spriteThread;
	std::thread physicsThread;

	std::future<void> watch;

	std::mutex progressMutex;

	float progress = 0.f;
	bool finished = false;

	void addProgress(float val);
	void watchComplete();
};
