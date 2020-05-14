#include <SFML/Graphics.hpp>
#include <random>
#include <chrono>
#include <thread>
const auto width = 600U;
const auto height = 600U;
auto step = width / 10.0f;
float generator(float a , float b) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> dis(a, b);
	return dis(gen);
}
class Particle
{
public:
	sf::Vector2f m_position;
	float m_radius;
	sf::Vector2f m_speed;
	Particle() noexcept = default;
	explicit Particle(const sf::Vector2f position, const float radius, const sf::Vector2f speed) noexcept :
		m_position(position), m_radius(radius), m_speed(speed)
	{}
	~Particle() noexcept = default;
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
		if (m_position.x > W) m_position.x = 0.f; if (m_position.x < 0) m_position.x = static_cast<float>(W);
		if (m_position.y > H) m_position.y = 0.f; if (m_position.y < 0) m_position.y = static_cast<float>(H);
	}
};
bool isInside(Particle* p, const unsigned int xPos, const unsigned int yPos) {
	return ((p -> m_position.x < xPos) && (p -> m_position.x > (xPos - step)) && (p ->m_position.y < yPos) && (p -> m_position.y > (yPos - step)));
}
int main() {
	sf::RenderWindow window{ sf::VideoMode(600U, 600U), "PHYSICS" };
	window.setFramerateLimit(40);
	std::vector < Particle* > particles;
	int count = 20;
	for (int i = 0; i < count; i++)
	{
		sf::Vector2f position(generator(0, 600), generator(0, 600));
		sf::Vector2f speed(0.02f, 0.02f);
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
		for (auto i = step; i <= width; i += step) {
			for (auto j = step; j <= height; j += step) {
				double counter = 0;
				for (auto p : particles) {
					if (isInside(p, i, j)) {
						++counter;
					}
				}
				sf::RectangleShape rectangle;
				rectangle.setPosition(sf::Vector2f(i - step, j - step));
				rectangle.setSize(sf::Vector2f(step, step));
				rectangle.setFillColor(sf::Color(0, 255 * counter / count * 3.5f, 0));
				window.draw(rectangle);
			}
		}
		for (auto i = 0U; i < count; ++i) {
			particles[i]->move(600U, 600U);
			particles[i]->draw(&window);
			//window.display();
			//window.clear();
		}
		window.display();
	}
	return EXIT_SUCCESS;
}


