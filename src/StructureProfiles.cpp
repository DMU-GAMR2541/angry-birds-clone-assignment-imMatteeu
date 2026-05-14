#pragma once

#include "StructureProfiles.h"

// Data Profiles for each Structure Material

static EntityData WoodStructure = {
	"../assets/Ang_Birds/woodenwall.png",
	60.0f,
	10.0f,
	2.0f,
	0.5f,
	0.3f,
	false
};

static EntityData StoneStructure = {
	"../assets/Ang_Birds/stonewall.png",
	60.0f,
	10.0f,
	12.0f,
	0.5f,
	0.1f,
	false
};

static EntityData IceStructure = {
	"../assets/Ang_Birds/icewall.png",
	60.0f,
	10.0f,
	1.0f,
	0.5f,
	0.3f,
	false
};

// Function to retrieve the EntityData profile for a given StructMaterial

const EntityData& getStructureProfile(StructMaterial material)
{
	switch (material)
	{
	case StructMaterial::Wood: return WoodStructure;
	case StructMaterial::Stone: return StoneStructure;
	case StructMaterial::Ice: return IceStructure;
	}
	return WoodStructure;
}
