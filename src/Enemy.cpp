#include "Enemy.h"

EnemyData Enemy::getEnemyData(EnemyData enemyData) {
	switch (enemyData.size) {
	case EnemySize::Small:
		enemyData.health = 50;
		break;
	case EnemySize::Medium:
		enemyData.health = 100;
		break;
	case EnemySize::Large:
		enemyData.health = 150;
		break;
	}
	return enemyData;
}