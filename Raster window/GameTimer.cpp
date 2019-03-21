#include "GameTimer.h"



GameTimer::GameTimer() :
	m_active(false)
{
	LARGE_INTEGER frequency;

	QueryPerformanceFrequency(&frequency);

	m_secondsPerCount = 1.0f / static_cast<float>(frequency.QuadPart);

	Reset();
}

GameTimer::~GameTimer()
{
}

float GameTimer::PlayingTime()
{
	if (m_active)
	{
		// The distance m_currentTime - m_baseTime includes paused time,
		// which we do not want to count.  To correct this, we can subtract
		// the paused time from m_currentTime:
		return static_cast<float>(((m_currentTime.QuadPart - m_pausedTime.QuadPart) - m_baseTime.QuadPart)*m_secondsPerCount);
	}
	else
	{
		// The clock is currently not running so don't count the time since
		// the clock was stopped
		return static_cast<float>(((m_stopTime.QuadPart - m_pausedTime.QuadPart) - m_baseTime.QuadPart)*m_secondsPerCount);
	}
}

float GameTimer::DeltaTime()
{
	return m_deltaTime;
}

void GameTimer::PlayingTime(float time)
{
	// Reset the internal state to reflect a PlayingTime of 'time'
	// Offset the baseTime by this 'time'.
	m_active = false;
	m_stopTime = m_currentTime;
	m_pausedTime.QuadPart = 0;

	m_baseTime.QuadPart = m_stopTime.QuadPart - static_cast<__int64>(time / m_secondsPerCount);
}

void GameTimer::Reset()
{
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);

	m_baseTime = currentTime;
	m_previousTime = currentTime;
	m_stopTime = currentTime;
	m_currentTime = currentTime;
	m_pausedTime.QuadPart = 0;
	m_active = false;
}

void GameTimer::Start()
{
	LARGE_INTEGER startTime;
	QueryPerformanceCounter(&startTime);
	if (!m_active)
	{
		// Accumulate the time elapsed between stop and start pairs.
		m_pausedTime.QuadPart += (startTime.QuadPart - m_stopTime.QuadPart);

		m_previousTime = startTime;
		m_stopTime.QuadPart = 0;
		m_active = true;
	}
}


void GameTimer::Stop()
{
	if (m_active)
	{
		// Set the stop time to the time of the last update.
		m_stopTime = m_currentTime;
		m_active = false;
	}
}

void GameTimer::Update()
{
	if (!m_active)
	{
		m_deltaTime = 0.0;
		return;
	}

	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);
	m_currentTime = currentTime;

	m_deltaTime = (m_currentTime.QuadPart - m_previousTime.QuadPart)*m_secondsPerCount;
	m_previousTime = m_currentTime;

	if (m_deltaTime < 0.0)
	{
		m_deltaTime = 0.0;
	}
}