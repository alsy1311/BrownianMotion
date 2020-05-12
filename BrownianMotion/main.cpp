#include <SFML/Graphics.hpp>
#include <random>
#include <chrono>
#include <thread>
using namespace sf;
float generator(int a , int b) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(a, b);
	return dis(gen);
}
bool isInside(int i, int j, float x, float y) {
	if (((10 * i) < x) && (x < 10 * (i + 1)) && ((10 * i) < y) && (y < 10 * (i + 1)))
	{
		return true;
	}
	else {
		return false;
	}
}
class Particle
{
public:
	Particle() noexcept = default;
	explicit Particle(const sf::Vector2f position, const float radius, const sf::Vector2f speed) noexcept :
		m_position(position), m_radius(radius), m_speed(speed)
	{}
	~Particle() noexcept = default;
public:
	const auto position() const noexcept
	{
		return m_position;
	}
	const auto radius() const noexcept
	{
		return m_radius;
	}
	void set_x(const float x) noexcept
	{
		m_position.x = x;
	}
	void set_y(const float y) noexcept
	{
		m_position.y = y;
	}
public:
	void draw(sf::RenderWindow* m_window) {

		sf::CircleShape circle(2.0f * m_radius);

		circle.setPosition(m_position);

		circle.setFillColor(sf::Color::Red);

		m_window->draw(circle);

	}
	void move(const unsigned int W, const unsigned int H) {
		m_position.x += generator(- m_speed.x, m_speed.x);
		m_position.y += generator(- m_speed.y, m_speed.y);
		if (m_position.x > W) m_position.x = 0; if (m_position.x < 0) m_position.x = W;
		if (m_position.y > H) m_position.y = 0; if (m_position.y < 0) m_position.y = H;
	}

	//void move(const sf::Vector2f delta) noexcept;

	//void move(const float dt) noexcept;
public:
	sf::Vector2f m_position;
	float m_radius;
	sf::Vector2f m_speed;
};
int main() {
	sf::RenderWindow window{ sf::VideoMode(600U, 600U), "PHYSICS" };
	window.setFramerateLimit(60);
	std::vector < Particle* > particles;
	for (int i = 0; i < 10; i++)
	{
		sf::Vector2f position(generator(0, 600), generator(0, 600));
		sf::Vector2f speed(0.02, 0.02);
		particles.push_back(new Particle(position, 5.0, speed));
	}
	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		window.clear();
		for (auto i = 0U; i < 10; ++i) {
			particles[i]->move(600U, 600U);
			particles[i]->draw(&window);
			window.display();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			window.clear();
		}
		window.display();
	}
	return EXIT_SUCCESS;
}


