#include<SFML/Window.hpp>
#include<SFML/Graphics.hpp>
#include<random>
#include<vector>
//это никакой ни кох!!
const float h = 600;
const float w = 600;//float будет использоваться, тк нужен тип с плавающей точкой - это занимает меньше места(4б)
const std::vector<sf::Vector2f> vertices{ sf::Vector2f(300, 0), sf::Vector2f(0, 600), sf::Vector2f(600, 600) };// vertices - вершины, то есть задаём координаты вершин , получается квадрат
static std::random_device rd;// стартовое значение генератора с. ч.
static std::mt19937 generator(rd());//сам генератор(так и называется), то есть внутри находится "семя" последовательности
sf::Color color(sf::Color::Red); //задаём начальный цвет, использоваться не будет, просто семя
sf::Vector2f buildp(sf::Vector2f v)//даем вектор на вход
{
	std::uniform_int_distribution<int> distribution(0, 2);//используем класс, который делает равномерное распределение,int, границы чисел 0 и 2 
    int rand = distribution(generator);//создаем сами числа
    if(rand == 0|| rand == 1|| rand == 2) color = sf::Color::Red;//создаем сами числа
    float vectx = 0.5 * (v.x + vertices[rand].x);//делим на 2 сумму координаты исходного вектора и "случайного" - попадаем в один из "больших" треугольников
    float vecty = 0.5 * (v.y + vertices[rand].y);
    return sf::Vector2f(vectx, vecty);//в итоге оплучаем вектор с новыми координатами
}

int main()
{//обычное построение, взятое с сайта
	sf::RenderWindow window(sf::VideoMode(w, h), "Треугольник Серпинского", sf::Style::Default);
	window.setPosition(sf::Vector2i(700, 50));
	sf::Vector2f position(1, 450);//даём начальный вектор
	window.clear();
	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				window.close();
		}
		//отрисовка точек
		sf::CircleShape point(0.2);//Поскольку видеокарта не может привлечь идеальные круги, мы должны подделывать их из нескольких треугольников, соединенных друг с другом. Свойстве “количество точек” sf::CircleShape определяет, сколько из этих треугольников в использовании, и, следовательно, определяет качество круга.
		point.setPosition(position);//задаем позицию точки относительного верхнего левого угла окна
		point.setFillColor(color);
		window.draw(point);
		window.display();
		position = buildp(position);//рекурсируем
	}
}