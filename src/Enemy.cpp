#include "Enemy.h"

EnemyData Enemy::getEnemyData(EnemyData enemyData) {
	switch (enemyData.size) {
	case EnemySize::Small:
		enemyData.health = 50;
		enemyData.mass = 1;
		break;
	case EnemySize::Medium:
		enemyData.health = 100;
		enemyData.mass = 2;
		break;
	case EnemySize::Large:
		enemyData.health = 150;
		enemyData.mass = 3;
		break;
	}
	return enemyData;
}