#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <vector>

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "Botões SFML");

	sf::Texture fundoTextura;
	if (!fundoTextura.loadFromFile("fundo.jpg")){
		return -1;
	}

	sf::Sprite fundoSprite;
	fundoSprite.setTexture(fundoTextura);

	sf::Font fonte;
	if (!fonte.loadFromFile("arial.ttf")){
		return -1; 
	}

	std::vector<sf::RectangleShape> butao;

	sf::Text mainButton("Teste", fonte, 18);
	mainButton.setPosition(35, 20);

	sf::RectangleShape mainButtonRect(sf::Vector2f(100, 50));
	mainButtonRect.setPosition(25, 10);
	mainButtonRect.setFillColor(sf::Color::Blue);

	while (window.isOpen()) {
		sf::Event janela;
		while (window.pollEvent(janela)) {
			if (janela.type == sf::Event::Closed) {
				window.close();
			}

			if (janela.type == sf::Event::MouseButtonReleased) {
				if (janela.mouseButton.button == sf::Mouse::Left) {
					if (mainButtonRect.getGlobalBounds().contains(sf::Vector2f(janela.mouseButton.x, janela.mouseButton.y)) && !butao.empty()){
						butao.clear();
					}
					else if (mainButtonRect.getGlobalBounds().contains(sf::Vector2f(janela.mouseButton.x, janela.mouseButton.y)) && butao.empty()) {

						for (int i = 0; i < 3; i++) {
							sf::RectangleShape button(sf::Vector2f(100, 50));
							button.setFillColor(sf::Color::Blue);
							button.setPosition(25, 80 + i * 70);
							butao.push_back(button);
						}
					}
					else {
						for (size_t i = 0; i < butao.size(); i++) {
							if (butao[i].getGlobalBounds().contains(sf::Vector2f(janela.mouseButton.x, janela.mouseButton.y)) && !butao.empty()) {
								printf("Botão ", i + 1, " clicado!");
							}
						}
					}
				}
			}
		}

		window.clear();
		window.draw(fundoSprite);
		window.draw(mainButtonRect);
		window.draw(mainButton);

		for (const auto& button : butao) {
			window.draw(button);
		}

		window.display();
	}

	return 0;
}
