#include<SFML/Window.hpp> //iostream : º–¿Y¿…(header)
#include<SFML/Graphics.hpp>
#include<iostream>
#include<string>


int main() {
	sf::Vector2i fieldSize(20, 15);
			
	// Draw the content of Block.png on screen.
	sf::Texture blockTexture;
	if (!blockTexture.loadFromFile("block.png")) {
		std::cout << "block.png is not found!" << std::endl;
		return EXIT_FAILURE;
	}
	
	sf::Text scoreText;

	std::vector<sf::Vector2i> snake = { sf::Vector2i(3, 4) };
	sf::Vector2i food(rand() % fieldSize.x, rand() % fieldSize.y);

	sf::Sprite block(blockTexture);
	sf::Vector2f blockSize(
		block.getLocalBounds().width,
		block.getLocalBounds().height
	);

	
	sf::VideoMode mode(
		unsigned int (fieldSize.x * blockSize.x),
		unsigned int (fieldSize.y * blockSize.y));

	sf::RenderWindow w(mode , L"≥g¶Y≥D");

	enum class Direction {UP, DOWN, LEFT, RIGHT};
	Direction direction = Direction::RIGHT;


	sf::Clock clock;
	bool isDead = false;

	while (w.isOpen()) {
		// Detection and Process of User Interactive events
		sf::Event evt;
		if (w.pollEvent(evt)) {
			if (evt.type == sf::Event::Closed) {
				w.close();
			}
			if (evt.type == sf::Event::KeyPressed) {
				if (evt.key.code == sf::Keyboard::Up) {
					direction = Direction::UP;
				}
				if (evt.key.code == sf::Keyboard::Down) {
					direction = Direction::DOWN;
				}
				if (evt.key.code == sf::Keyboard::Right) {
					direction = Direction::RIGHT;
				}
				if (evt.key.code == sf::Keyboard::Left) {
					direction = Direction::LEFT;
				}

			}
		}
		
		
		if (clock.getElapsedTime().asSeconds() >= 0.4f) {
			sf::Vector2i head = snake[0];
			// object motion
			if (direction == Direction::UP) {
				head.y--;
			}
			if (direction == Direction::DOWN) {
				head.y++;
			}
			if (direction == Direction::LEFT) {
				head.x--;
			}
			if (direction == Direction::RIGHT) {
				head.x++;
			}
			// head = (4, 4)
			snake.insert(snake.begin(), head);
			// snake = {(4, 4), (3,4)}

			if (head.x < 0 || head.x >= fieldSize.x ||
				head.y < 0 || head.y >= fieldSize.y) {
				isDead = true;
			}
			
			if (!isDead) {
				// Check if the food was bitten by the snake.	
				
				if (food == head) {
					
					std::cout << "Eaten"<< " " << snake.size() - 1 << std::endl;
					sf::Vector2i NewFoodPos(rand() % fieldSize.x, rand() % fieldSize.y);
					food = NewFoodPos;
					
					
					// Draw Score
					std::string s = std::to_string(snake.size() - 1);
					scoreText.setString(s);
					scoreText.setCharacterSize(200);
					scoreText.setFillColor(sf::Color(255, 0, 0));
					w.draw(scoreText);
					w.display();
					
				}
				else {
					snake.pop_back();
				}
			}

			clock.restart();

		}
		


		// Draw graphics
		// Clear Picture
		if (isDead) {
			w.clear(sf::Color(255, 0, 0));
			// Restart the game if any key pressed.
			if (evt.type == sf::Event::KeyPressed) {
				snake = { sf::Vector2i(3, 4) };
				isDead = false;
				clock.restart();
				
			}
			
			
		}
		else {
			w.clear();
		}
		

		// Draw food
		sf::Vector2f foodPos(
			food.x * blockSize.x,
			food.y * blockSize.y);
		block.setPosition(foodPos);
		w.draw(block);

		// Draw a snake
		for (const sf::Vector2i& body : snake) {
			sf::Vector2f bodyPos(
				body.x* blockSize.x,
				body.y* blockSize.y);
			block.setPosition(bodyPos);
			w.draw(block);
		}

		// Draw Score
		w.draw(scoreText);
		
		w.display();

	}

	return EXIT_SUCCESS;

}