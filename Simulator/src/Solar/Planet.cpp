#include "Planet.h"

#include <iostream>
#include <random>
#include <cmath>

Planet::Planet()
	: m_Position(Vector3f()), m_Velocity(Vector3f()), m_Force(Vector3f()), m_Radius(0), m_Mass(0), m_Distance(0), m_Angle(0), m_OrbitSpeed(0)
{
	m_Texture = new sf::Texture();
}

Planet::Planet(float x, float y, float distance, uint32_t angle, float orbitSpeed, float radius, float z)
	: m_Position(x, y, z), m_Distance(distance), m_Angle(angle), m_Velocity(Vector3f()), m_Force(Vector3f()), m_Radius(radius), m_Mass(0), m_OrbitSpeed(orbitSpeed)
{
	m_Texture = new sf::Texture();
}

Planet::~Planet()
{
}
void Planet::SpawnMoons(const uint16_t& number)
{
	int lowBounds = 150, highBounds = 250;
	int lowAngle = 0, highAngle = 180;
	int lowDirs = 0, highDirs = 1;
	float lowOrbitSpeed = 0.05, highOrbitSpeed = 0.2;

	int directions[2] = { 1, -1 };

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrDistance(lowBounds, highBounds);
	std::uniform_int_distribution<> distrAngle(lowAngle, highAngle);
	std::uniform_int_distribution<> distrDirections(lowDirs, highDirs);
	std::uniform_real_distribution<float> distrOrbitSpeed(lowOrbitSpeed, highOrbitSpeed);

	for (int i = 0; i < number; i++)
	{
		int randomDistance = distrDistance(gen); // Random distance of the moons from planet.
		int randomAngle = distrAngle(gen);
		int randomDirectionX = distrDirections(gen);
		int randomDirectionY = distrDirections(gen);
		float randomOrbitSpeed = distrOrbitSpeed(gen);

		std::cout << "random angle " << randomAngle << ", random distance " << randomDistance << " random dir x : " << directions[randomDirectionX] << " random dir y : " << directions[randomDirectionY] << "random orbit speed " << randomOrbitSpeed << std::endl;

		//int posX = m_Position.x + (directions[randomDirectionX] * randomDistance);
		//int posY = m_Position.y + (directions[randomDirectionY] * randomDistance);
		//std::cout << "pos x " << posX << ", pos y " << posY << std::endl;
		//m_ChildPlanets.push_back(Planet(posX, posY, randomDistance, randomAngle, randomOrbitSpeed));
		m_ChildPlanets.push_back(Planet(m_Position.x + 100.f, m_Position.y + 100.f, 10, 0, randomOrbitSpeed, 30.0f));
	}
}

void Planet::Draw(sf::RenderWindow &window)
{
	sf::CircleShape planet(m_Radius);
	planet.setOrigin(m_Distance + (m_Radius / 3), m_Distance + (m_Radius / 3));
	planet.setPosition(m_Position.x, m_Position.y);
	planet.setTexture(m_Texture, true);
	//planet.setOrigin(m_Distance, m_Distance);
	planet.rotate(m_Angle);
	window.draw(planet);

	//DrawChildPlanets(window, m_ChildPlanets);
}

void Planet::Orbit()
{
	float& angle = m_Angle;
	float orbitSpeed = m_OrbitSpeed;
	angle -= orbitSpeed; // + for clockwise, - for anti clockwise

}

void Planet::Orbit(const Planet& planet)
{
	float& angle = m_Angle;
	float orbitSpeed = m_OrbitSpeed;
	angle -= orbitSpeed;
}

void Planet::SetTexture(std::string filepath)
{
//if (!m_Texture->loadFromFile("Simulator/res/assets/img/sunmap.jpg"))
	if (!m_Texture->loadFromFile(filepath))
		std::cout << "[Error] : Could not load background texture" << std::endl;
}
