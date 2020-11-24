#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

struct Vector3f
{
	float x;
	float y;
	float z;

	Vector3f()
		: x(0), y(0), z(0)
	{
	}

	Vector3f(float x, float y, float z)
		: x(x), y(y), z(z)
	{
	}
};

class Planet
{
private:
	Vector3f m_Position;
	Vector3f m_Velocity;
	Vector3f m_Force;
	float m_Radius;
	float m_Mass;
	float m_Distance;
	float m_Angle;
	float m_OrbitSpeed;
	std::vector<Planet> m_ChildPlanets;

public:
	// rendering in 2d for now
	Planet();
	Planet(float x, float y, float distance, uint32_t angle, float orbitSpeed, float z = 0);
	~Planet();

	void SpawnMoons(const uint16_t& number);
	void Draw(sf::RenderWindow& window);

	void Orbit();

};

