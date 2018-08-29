#include "formation.h"
#include "enemy.h"
#include "timer.h"

void Formation::Create()
{
	//m_enterPaths[0] = { Vector2D(200.0f, 400.0f), Vector2D(300.0f, 300.0f), Vector2D(200.0f, 200.0f), Vector2D(100.0f, 300.0f), Vector2D(200.0f, 400.0f) };
	//m_enterPaths[1] = { Vector2D(600.0f, 400.0f), Vector2D(500.0f, 300.0f), Vector2D(600.0f, 200.0f), Vector2D(700.0f, 300.0f), Vector2D(600.0f, 400.0f) };

	m_enterPaths[0] = { Vector2D(500.0f, -64.0f), Vector2D(100.0f, 300.0f), Vector2D(200.0f, 400.0f), Vector2D(300.0f, 300.0f) };
	m_enterPaths[1] = { Vector2D(300.0f, -64.0f), Vector2D(700.0f, 300.0f), Vector2D(600.0f, 400.0f), Vector2D(500.0f, 300.0f) };

	m_attackPaths.push_back({ Vector2D(400.0f, 300.0f), Vector2D(500.0f, 500.0f), Vector2D(600.0f, 600.0f), Vector2D(550.0f, 650.0f) });
	m_attackPaths.push_back({ Vector2D(300.0f, 400.0f), Vector2D(500.0f, 500.0f), Vector2D(600.0f, 600.0f), Vector2D(650.0f, 550.0f) });
	m_attackPaths.push_back({ Vector2D(200.0f, 300.0f), Vector2D(400.0f, 400.0f), Vector2D(350.0f, 350.0f), Vector2D(100.0f, 550.0f) });
	m_attackPaths.push_back({ Vector2D(400.0f, 300.0f), Vector2D(200.0f, 200.0f), Vector2D(350.0f, 350.0f), Vector2D(50.0f, 550.0f) });
	m_attackPaths.push_back({ Vector2D(50.0f, 400.0f), Vector2D(500.0f, 500.0f), Vector2D(350.0f, 350.0f), Vector2D(550.0f, 650.0f) });

	m_formation =
		//sec row
	{ { { Enemy::BEE, Enemy::LEFT, 300.0f,200.0, Vector2D(400.0f, 100.0f), this }, 0.0f, false },
	{ { Enemy::BEE, Enemy::LEFT, 300.0f,200.0, Vector2D(440.0f, 100.0f), this }, 0.35f,false },
	{ { Enemy::BEE, Enemy::LEFT, 300.0f,200.0, Vector2D(480.0f, 100.0f), this }, 0.7f,false },
	{ { Enemy::BEE, Enemy::LEFT, 300.0f,200.0, Vector2D(360.0f, 100.0f), this }, 1.05f,false },
	{ { Enemy::BEE, Enemy::LEFT, 300.0f,200.0, Vector2D(320.0f, 100.0f), this }, 1.35f,false },

	{ { Enemy::BEE, Enemy::RIGHT, 300.0f,200.0, Vector2D(280.0f, 100.0f), this }, 2.0f,false },
	{ { Enemy::BEE, Enemy::RIGHT, 300.0f,200.0, Vector2D(240.0f, 100.0f), this }, 2.05f,false },
	{ { Enemy::BEE, Enemy::RIGHT, 300.0f,200.0, Vector2D(200.0f, 100.0f), this }, 2.35f,false },
		//thrid row
	{ { Enemy::BUG, Enemy::LEFT, 300.0f,200.0, Vector2D(400.0f, 140.0f), this }, 1.70f, false },
	{ { Enemy::BUG, Enemy::LEFT, 300.0f,200.0, Vector2D(480.0f, 140.0f), this }, 2.05f, false },
	{ { Enemy::BUG, Enemy::LEFT, 300.0f,200.0, Vector2D(440.0f, 140.0f), this }, 2.35f, false },

		//bosses top row
	{ { Enemy::BOSS, Enemy::RIGHT, 300.0f,400.0, Vector2D(400.0f, 65.0f), this }, 0.0f, false },
	{ { Enemy::BOSS, Enemy::RIGHT, 300.0f,400.0, Vector2D(440.0f, 65.0f), this }, 0.35f, false },
	{ { Enemy::BOSS, Enemy::RIGHT, 300.0f,400.0, Vector2D(360.0f, 65.0f), this }, 0.7f, false },
	{ { Enemy::BOSS, Enemy::RIGHT, 300.0f,400.0, Vector2D(320.0f, 65.0f), this }, 1.05f, false },
	{ { Enemy::BOSS, Enemy::RIGHT, 300.0f,400.0, Vector2D(280.0f, 65.0f), this }, 1.35f, false },
	{ { Enemy::BOSS, Enemy::RIGHT, 300.0f,400.0, Vector2D(240.0f, 65.0f), this }, 1.70f, false },
		//thrid row
	{ {Enemy::BUG2, Enemy::LEFT, 300.0f,50.0, Vector2D(360.0f, 140.0f), this }, 2.70f, false },
	{ { Enemy::BUG2, Enemy::LEFT, 300.0f,50.0, Vector2D(320.0f, 140.0f), this }, 3.0f, false },

	{ { Enemy::BUG2, Enemy::RIGHT, 300.0f,50.0, Vector2D(280.0f, 140.0f), this }, 2.70f, false },
	{ { Enemy::BUG, Enemy::RIGHT, 300.0f,50.0, Vector2D(240.0f, 140.0f), this }, 3.0f, false },
	{ { Enemy::BUG, Enemy::RIGHT, 300.0f,50.0, Vector2D(200.0f, 140.0f), this }, 3.05f, false },
	};
	m_timer = 0.0f;

}

void Formation::Destroy()
{
}

void Formation::Update()
{
	m_timer = m_timer + Timer::Instance()->DeltaTime();
	for (Info& info : m_formation)
	{
		if (info.isActive == false && m_timer > info.enterTime)
		{
			info.isActive = true;
			Enemy * enemy = m_scene->AddEntity<Enemy>();
			enemy->Create(info.enemyInfo);
		}
	}
}

const Formation::Path& Formation::GetRandomAttackPath()
{
	size_t index = rand() % m_attackPaths.size();
	return m_attackPaths[index];
}
