#include "singleton.h"
#include "Engine.h"

class Timer : public Singleton<Timer>
{
public:
	bool Initalize(Engine* engine);
	void Shutdown();
	void Update();

	float DeltaTime() const { return m_dt * m_timeScale; }
	float UnscaledDeltaTime() const { return m_dt; }

	void SetTimeScale(float timeScale) { m_timeScale = timeScale; }
	float GetTimeScale() const { return m_timeScale; }
	void Pause() { m_paused = true; }
	void UnPause() { m_paused = false; }
	bool IsPaused() const{ return m_paused; }

	friend Singleton<Timer>;

protected:
	Timer();
	~Timer();

private:
	Engine * m_engine;
	float m_dt;
	float m_timeScale;
	Uint32 m_prevTicks;
	bool m_paused;
};



