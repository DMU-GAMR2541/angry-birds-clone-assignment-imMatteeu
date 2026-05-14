#pragma once

#include "EnemyProfiles.h"

// Data Profiles for each Enemy Type

static EntityData SmallPig = {
	"../assets/Ang_Birds/pig.png",
	40.0f,
	40.0f,
	1.0f,
	0.5f,
	0.3f,
	true
};

static EntityData MediumPig = {
	"../assets/Ang_Birds/helmetpig.png",
	50.0f,
	50.0f,
	2.0f,
	0.5f,
	0.3f,
	true
};

static EntityData BigPig = {
	"../assets/Ang_Birds/kingpig.png",
	60.0f,
	60.0f,
	4.0f,
	0.5f,
	0.3f,
	true
};

// Function to retrieve the EntityData profile for a given EnemySize

const EntityData& getEnemyProfile(EnemySize size)
{
	switch (size)
	{
	case EnemySize::Small: return SmallPig;
	case EnemySize::Medium: return MediumPig;
	case EnemySize::Big: return BigPig;
	}
	return SmallPig;
}