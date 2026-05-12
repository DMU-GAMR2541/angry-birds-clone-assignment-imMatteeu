#include "BirdProfiles.h"
#include "Bird.h"

static EntityData RedBird = {
	"assets/Ang_Birds/redbird.png",
	50.0f,
	50.0f,
	1.0f,
	0.5f,
	0.3f,
	true
};

static EntityData YellowBird = {
	"assets/Ang_Birds/yellowbird.png",
	50.0f,
	50.0f,
	1.0f,
	0.5f,
	0.3f,
	true
};

static EntityData BlackBird = {
	"assets/Ang_Birds/blackbird.png",
	50.0f,
	50.0f,
	1.0f,
	0.5f,
	0.3f,
	true
};

const EntityData& getBirdProfile(BirdType type)
{
	switch (type)
	{
	case BirdType::Red: return RedBird;
	case BirdType::Yellow: return YellowBird;
	case BirdType::Black: return BlackBird;
	}
	return RedBird;
}