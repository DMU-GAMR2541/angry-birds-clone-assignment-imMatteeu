#include "BirdProfiles.h"
#include "Bird.h"

// Data Profiles for each Bird Type

static EntityData RedBird = {
	"../assets/Ang_Birds/redbird.png",
	50.0f,
	50.0f,
	1.0f,
	0.7f,
	0.3f,
	true
};

static EntityData YellowBird = {
	"../assets/Ang_Birds/yellowbird.png",
	50.0f,
	50.0f,
	0.8f,
	0.7f,
	0.3f,
	true
};

static EntityData BlackBird = {
	"../assets/Ang_Birds/blackbird.png",
	50.0f,
	50.0f,
	1.2f,
	0.7f,
	0.3f,
	true
};

// Function to retrieve the EntityData profile for a given BirdType

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