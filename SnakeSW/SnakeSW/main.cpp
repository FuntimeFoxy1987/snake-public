#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;
using namespace sf;

enum Menu
{
	launching,
	info,
	control,
	close,
	disabled,
};

enum Direction
{
	up,
	down,
	left,
	rigth,
	nothing
};

//string Str_GameOver = "";
//string Puth_File_Record = "resources/F01_Ir0nK.r";
string puth_File_Font = "resources/CustomFontTtf12H10.ttf";

void writeMenu(Menu menu_) {
	if (menu_ == Menu::launching) {
		cout << "[>] launching the program of snake" << endl;
	}
	else {
		cout << "[ ] launching the program of snake" << endl;
	}
	if (menu_ == Menu::info) {
		cout << "[>] info" << endl;
	}
	else {
		cout << "[ ] info" << endl;
	}
	if (menu_ == Menu::control) {
		cout << "[>] control" << endl;
	}
	else {
		cout << "[ ] control" << endl;
	}
	if (menu_ == Menu::close) {
		cout << "[>] close" << endl;
	}
	else {
		cout << "[ ] close" << endl;
	}

	cout << endl << "press \"Enter\" for select  field of menu." << endl;
}


/*void GameOver_setText(int points_lizing, int record, bool GameOver) {
	if (!GameOver) {
		ostringstream os_point_text, os_record;
		os_point_text << points_lizing;
		os_record << record;

		if (points_lizing > record) {
			Str_GameOver = "[ New Record ]\nNew record : " + os_point_text.str() + "\nOld record : " + os_record.str();
		}
		else {
			Str_GameOver = "[ Game stat ]\nPoint : " + os_point_text.str() + "\nRecord : " + os_record.str();
		}
	}
}*/

int main()
{
#pragma region Меню_программы
	Menu menu_ = Menu::launching;
	writeMenu(menu_);
	while (menu_ != Menu::disabled)
	{
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			system("cls");
			switch (menu_)
			{
			case launching:
				menu_ = Menu::info;
				break;
			case info:
				menu_ = Menu::control;
				break;
			case control:
				menu_ = Menu::close;
				break;
			case close:
				menu_ = Menu::launching;
				break;
			}
			writeMenu(menu_);
			Sleep(100);
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			system("cls");
			switch (menu_)
			{
			case launching:
				menu_ = Menu::close;
				break;
			case info:
				menu_ = Menu::launching;
				break;
			case control:
				menu_ = Menu::info;
				break;
			case close:
				menu_ = Menu::control;
				break;
			}
			writeMenu(menu_);
			Sleep(100);
		}

		if (Keyboard::isKeyPressed(Keyboard::Enter)) {
			if (menu_ == Menu::launching) {
				menu_ = Menu::disabled;
			}
			if (menu_ == Menu::info) {
				system("cls");
				cout << "It's program creates to show a popular game \"snake\". the program is written in c++." << endl;
				cout << endl << "press \"Enter\" for exit." << endl;

				Sleep(100);

				while (true)
				{
					if (Keyboard::isKeyPressed(Keyboard::Enter)) {
						system("cls");
						writeMenu(menu_);
						break;
					}
				}

				Sleep(100);
			}
			if (menu_ == Menu::control) {
				system("cls");
				cout << "Control of the game :" << endl;
				cout << "W - up" << endl;
				cout << "A - left" << endl;
				cout << "S - down" << endl;
				cout << "D - rigth" << endl;
				cout << endl << "press \"Enter\" for exit." << endl;

				Sleep(100);

				while (true)
				{
					if (Keyboard::isKeyPressed(Keyboard::Enter)) {
						system("cls");
						writeMenu(menu_);
						break;
					}
				}

				Sleep(100);
			}
			if (menu_ == Menu::close) {
				return 0;
			}
		}
	}
#pragma endregion
#pragma region Переменные
	Image image_map;
	image_map.loadFromFile("resources/map.png");
	Texture texture_map;
	texture_map.loadFromImage(image_map);
	Sprite sprite_map;
	sprite_map.setTexture(texture_map);

	Font font;
	font.loadFromFile(puth_File_Font);

	Text text(" ", font, 20);
	text.setFillColor(Color::White);
	text.setPosition(0, 0);

	int x_map = 21, y_map = 21;

	bool BoPointGenerated = false;

	int Point_number = 0;
	int record = 0;

	bool GameOver = false;

	Direction direction = Direction::nothing;

	char** map = new char* [y_map];
#pragma endregion
#pragma region Заполение_поля_игры
	for (int i = 0; i < y_map; i++)
	{
		map[i] = new char[x_map];
	}
	for (int i = 0; i < y_map; i++)
	{
		for (int j = 0; j < x_map; j++)
		{
			map[j][i] = '0';
		}
	}
#pragma endregion 
#pragma region Змейка_и_начальная_длинна_ее
	vector<Vector2i> snake;

	snake.push_back(Vector2i(8, 10));
	snake.push_back(Vector2i(9, 10));
	snake.push_back(Vector2i(10, 10));
	snake.push_back(Vector2i(11, 10));
#pragma endregion
#pragma region Создание_окна_программы
	RenderWindow window(VideoMode(736, 832), "Snake");
#pragma endregion
	while (window.isOpen())
	{
#pragma region Обработка_событий_окна
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}
#pragma endregion
#pragma region Конец_игры
		if (GameOver)
		{
			for (int i = 0; i < y_map; i++)
			{
				delete[] map[i];
			}
			delete map;

			cout << "Game over ~" << endl;
			return 0;
		}
#pragma endregion
#pragma region Выбор_направления_движения
		if (Keyboard::isKeyPressed(Keyboard::W) && snake[0].y - 1 != snake[1].y)
		{
			direction = Direction::up;
		}
		if (Keyboard::isKeyPressed(Keyboard::A) && snake[0].x - 1 != snake[1].x)
		{
			direction = Direction::left;
		}
		if (Keyboard::isKeyPressed(Keyboard::S) && snake[0].y + 1 != snake[1].y)
		{
			direction = Direction::down;
		}
		if (Keyboard::isKeyPressed(Keyboard::D) && snake[0].x + 1 != snake[1].x)
		{
			direction = Direction::rigth;
		}
#pragma endregion
#pragma region Генерация_вишни_на_карте
		while (!BoPointGenerated)
		{
			Vector2i point;
			point.x = rand() % (x_map - 4) + 2;
			point.y = rand() % (y_map - 4) + 2;
			if (map[point.y][point.x] == '0')
			{
				map[point.y][point.x] = '3';
				BoPointGenerated = true;
			}
		}

		bool boPointCheck = false;

		for (int i = 0; i < y_map; i++)
		{
			for (int j = 0; j < x_map; j++)
			{
				if (map[i][j] == '3')
				{
					boPointCheck = true;
					break;
				}
			}
		}

		if (!boPointCheck)
		{
			BoPointGenerated = false;
		}
#pragma endregion
#pragma region Обработка_движения_змейки
		if (direction == Direction::up)
		{
			if (snake[0].y != 0)
			{
				if (map[snake[0].y - 1][snake[0].x] == '2')
				{
					GameOver = true;
				}
				vector <Vector2i> new_snake;
				new_snake.push_back(Vector2i(snake[0].x, snake[0].y));

				bool BoPointDetect = false;

				if (snake[0].y > 3)
				{
					if (map[snake[0].y - 1][snake[0].x] == '3')
					{
						BoPointDetect = true;
						BoPointGenerated = false;
						Point_number++;
					}
				}

				if (!BoPointDetect)
				{
					for (int i = 0; i < snake.size() - 1; i++)
					{
						new_snake.push_back(Vector2i(snake[i].x, snake[i].y));
					}
					map[snake[snake.size() - 1].y][snake[snake.size() - 1].x] = '0';
				}
				else
				{
					for (int i = 0; i < snake.size(); i++)
					{
						new_snake.push_back(Vector2i(snake[i].x, snake[i].y));
					}
				}

				new_snake[0] = Vector2i(new_snake[0].x, new_snake[0].y - 1);

				snake = new_snake;
			}
			else
			{
				GameOver = true;
			}

			Sleep(100);
		}

		if (direction == Direction::left)
		{
			if (snake[0].x != 0)
			{
				if (map[snake[0].y][snake[0].x - 1] == '2')
				{
					GameOver = true;
				}
				vector <Vector2i> new_snake;
				new_snake.push_back(Vector2i(snake[0].x, snake[0].y));

				bool BoPointDetect = false;

				if (snake[0].x > 3)
				{
					if (map[snake[0].y][snake[0].x - 1] == '3')
					{
						BoPointDetect = true;
						BoPointGenerated = false;
						Point_number++;
					}
				}

				if (!BoPointDetect)
				{
					for (int i = 0; i < snake.size() - 1; i++)
					{
						new_snake.push_back(Vector2i(snake[i].x, snake[i].y));
					}
					map[snake[snake.size() - 1].y][snake[snake.size() - 1].x] = '0';
				}
				else
				{
					for (int i = 0; i < snake.size(); i++)
					{
						new_snake.push_back(Vector2i(snake[i].x, snake[i].y));
					}
				}

				new_snake[0] = Vector2i(new_snake[0].x - 1, new_snake[0].y);

				snake = new_snake;
			}
			else
			{
				GameOver = true;
			}

			Sleep(100);
		}

		if (direction == Direction::down)
		{
			if (snake[0].y != y_map - 1)
			{
				if (map[snake[0].y + 1][snake[0].x] == '2')
				{
					GameOver = true;
				}
				vector <Vector2i> new_snake;
				new_snake.push_back(Vector2i(snake[0].x, snake[0].y));

				bool BoPointDetect = false;

				if (snake[0].y < 18)
				{
					if (map[snake[0].y + 1][snake[0].x] == '3')
					{
						BoPointDetect = true;
						BoPointGenerated = false;
						Point_number++;
					}
				}

				if (!BoPointDetect)
				{
					for (int i = 0; i < snake.size() - 1; i++)
					{
						new_snake.push_back(Vector2i(snake[i].x, snake[i].y));
					}
					map[snake[snake.size() - 1].y][snake[snake.size() - 1].x] = '0';
				}
				else
				{
					for (int i = 0; i < snake.size(); i++)
					{
						new_snake.push_back(Vector2i(snake[i].x, snake[i].y));
					}
				}

				new_snake[0] = Vector2i(new_snake[0].x, new_snake[0].y + 1);

				snake = new_snake;
			}
			else
			{
				GameOver = true;
			}

			Sleep(100);
		}

		if (direction == Direction::rigth)
		{
			if (snake[0].x != x_map - 1)
			{
				if (map[snake[0].y][snake[0].x + 1] == '2')
				{
					GameOver = true;
				}
				vector <Vector2i> new_snake;
				new_snake.push_back(Vector2i(snake[0].x, snake[0].y));

				bool BoPointDetect = false;

				if (snake[0].x < 18)
				{
					if (map[snake[0].y][snake[0].x + 1] == '3')
					{
						BoPointDetect = true;
						BoPointGenerated = false;
						Point_number++;
					}
				}

				if (!BoPointDetect)
				{
					for (int i = 0; i < snake.size() - 1; i++)
					{
						new_snake.push_back(Vector2i(snake[i].x, snake[i].y));
					}
					map[snake[snake.size() - 1].y][snake[snake.size() - 1].x] = '0';
				}
				else
				{
					for (int i = 0; i < snake.size(); i++)
					{
						new_snake.push_back(Vector2i(snake[i].x, snake[i].y));
					}
				}

				new_snake[0] = Vector2i(new_snake[0].x + 1, new_snake[0].y);

				snake = new_snake;
			}
			else
			{
				GameOver = true;
			}

			Sleep(100);
		}
#pragma endregion
#pragma region Вывод_координат_элементов_змейки_на_карту_игры
		for (int i = 0; i < snake.size(); i++)
		{
			if (i == 0)
			{
				map[snake[i].y][snake[i].x] = '1';
			}
			else
			{
				map[snake[i].y][snake[i].x] = '2';
			}
		}
#pragma endregion
		window.clear();
#pragma region Отрисовка_эментов_игры_на_экране
		for (int i = 0; i < y_map; i++)
		{
			for (int j = 0; j < x_map; j++)
			{
				sprite_map.setPosition(32 * j + 32, 32 * i + 64);
				if (map[i][j] == '0')
				{
					sprite_map.setTextureRect(IntRect(0, 0, 32, 32));
					window.draw(sprite_map);
				}
				if (map[i][j] == '1')
				{
					sprite_map.setTextureRect(IntRect(32, 0, 32, 32));
					window.draw(sprite_map);
				}
				if (map[i][j] == '2')
				{
					sprite_map.setTextureRect(IntRect(64, 0, 32, 32));
					window.draw(sprite_map);
				}
				if (map[i][j] == '3')
				{
					sprite_map.setTextureRect(IntRect(96, 0, 32, 32));
					window.draw(sprite_map);
				}
			}
		}

		ostringstream os_point_text, os_record;
		os_point_text << Point_number;
		os_record << record;
		text.setString("Points : " + os_point_text.str() + "\nRecord : " + os_record.str());
		window.draw(text);

		window.display();
#pragma endregion
	}

	/*
#pragma region Меню_программы
	Menu menu_ = Menu::launching;
	while (menu_ != Menu::disabled)
	{
		if (menu_ == Menu::launching) {
			cout << "[>] launching the program of snake" << endl;
		}
		else {
			cout << "[ ] launching the program of snake" << endl;
		}
		if (menu_ == Menu::info) {
			cout << "[>] info" << endl;
		}
		else {
			cout << "[ ] info" << endl;
		}
		if (menu_ == Menu::reference) {
			cout << "[>] reference" << endl;
		}
		else {
			cout << "[ ] reference" << endl;
		}
		if (menu_ == Menu::close) {
			cout << "[>] close" << endl;
		}
		else {
			cout << "[ ] close" << endl;
		}

		cout << endl << "press \"Enter\" for select  field of menu." << endl;

		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			switch (menu_)
			{
			case launching:
				menu_ = Menu::info;
				break;
			case info:
				menu_ = Menu::reference;
				break;
			case reference:
				menu_ = Menu::close;
				break;
			case close:
				menu_ = Menu::launching;
				break;
			}
			Sleep(100);
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			switch (menu_)
			{
			case launching:
				menu_ = Menu::close;
				break;
			case info:
				menu_ = Menu::launching;
				break;
			case reference:
				menu_ = Menu::info;
				break;
			case close:
				menu_ = Menu::reference;
				break;
			}
			Sleep(100);
		}

		if (Keyboard::isKeyPressed(Keyboard::Enter)) {
			if (menu_ == Menu::launching) {
				menu_ = Menu::disabled;
			}
			if (menu_ == Menu::info) {
				system("cls");
				cout << "It's program creates to show a popular game \"snake\". the program is written in c++." << endl;
				cout << endl << "press \"Enter\" for exit." << endl;

				Sleep(100);

				while (true)
				{
					if (Keyboard::isKeyPressed(Keyboard::Enter)) {
						break;
					}
				}

				Sleep(100);
			}
			if (menu_ == Menu::reference) {
				system("cls");
				cout << "Control of the game :" << endl;
				cout << "W - up" << endl;
				cout << "A - up" << endl;
				cout << "S - up" << endl;
				cout << "D - up" << endl;
				cout << endl << "press \"Enter\" for exit." << endl;

				Sleep(100);

				while (true)
				{
					if (Keyboard::isKeyPressed(Keyboard::Enter)) {
						break;
					}
				}

				Sleep(100);
			}
			if (menu_ == Menu::close) {
				return 0;
			}
		}
		system("cls");
	}
#pragma endregion
	srand(time(NULL));
	setlocale(LC_ALL, "rus");
#pragma region Переменные_программы
	//Размер поля
	int x_map = 21, y_map = 21;

	int dx = 0, dy = 0;
	int temp_x = 0, temp_y = 0;
	int size_lizing;
	//Направление движения
	int Nap = -1;

	int points_p = 1;
	int points_lizing = 0;
	int Time_operation = 0;
	int Time_reset = 500;
	int lizing_xvost = 0;
	float speed = 31.25;
	bool GameOver = false;
	bool Bo_point = true;
	bool Bo_point2 = true;
	int record = 0;
	bool pause = false;
#pragma endregion

	//инициализация карты игры
	char** map = new char* [y_map];
	for (int i = 0; i < y_map; i++)
	{
		map[i] = new char[x_map];
	}
	for (int i = 0; i < y_map; i++)
	{
		for (int j = 0; j < x_map; j++)
		{
			map[j][i] = '0';
		}
	}
	//инициализация змейки
	size_lizing = x_map * y_map - 4;
	point * lizing = new point[size_lizing];
	for (int i = 4; i < size_lizing - 2; i++)
	{
		lizing[i].h = '0';
		lizing[i].x = -128;
		lizing[i].y = -128;
	}
	lizing[0].h = '1';
	lizing[0].x = 1;
	lizing[0].y = 1;
	lizing[1].h = '2';
	lizing[1].x = 2;
	lizing[1].y = 1;
	lizing[2].h = '2';
	lizing[2].x = 3;
	lizing[2].y = 1;
	lizing[3].h = '2';
	lizing[3].x = 3;
	lizing[3].y = 2;

	//создание спрайта для карты игры
	Image image_map;
	image_map.loadFromFile("resources/map.png");
	Texture texture_map;
	texture_map.loadFromImage(image_map);
	Sprite strite_map;
	strite_map.setTexture(texture_map);

	//инициализация окна игры
	RenderWindow window(VideoMode(736, 832), "Lizing");

	//загрузка шрифта
	Font font;
	font.loadFromFile("resources/CustomFontTtf12H10.ttf");
	
	//инициализация пременных текста игры
	Text text(" ", font, 20);
	text.setFillColor(Color::White);
	text.setPosition(0, 0);
	Text text2(" ", font, 20);
	text2.setFillColor(Color::Green);
	text2.setPosition(0, 732);

	//цикл игры
	while (window.isOpen())
	{
		//открытие файла рекорда
		ifstream ifr;
		ifr.open(Puth_File_Record);
		if (!ifr.is_open())
		{
			ofstream ofr;
			ofr.open(Puth_File_Record);
			ofr << 0;
			ofr.close();
		}
		else
		{
			string str;
			while (!ifr.eof())
			{
				str = "";
				ifr >> str;
			}
			istringstream ss(str);
			ss >> record;
		}

		point points;
		
		//события окна
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}
		while (pause == true)
		{
			Font font0;
			font0.loadFromFile("resources/CustomFontTtf12H10.ttf");
			Text text0("", font0, 20);
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
				{
					window.close();
				}
			}
			text0.setPosition(10, 10);
			text0.setString("[Pause] : Press \"Enter\" for continue.");
			window.clear();
			window.draw(text0);
			for (int i = 0; i < y_map; i++)
			{
				for (int j = 0; j < x_map; j++)
				{
					strite_map.setPosition(32 * j + 32, 32 * i + 64);
					if (map[j][i] == '0')
					{
						strite_map.setTextureRect(IntRect(0, 0, 32, 32));
						window.draw(strite_map);
					}
					if (map[j][i] == '1')
					{
						strite_map.setTextureRect(IntRect(32, 0, 32, 32));
						window.draw(strite_map);
					}
					if (map[j][i] == '2')
					{
						strite_map.setTextureRect(IntRect(64, 0, 32, 32));
						window.draw(strite_map);
					}
					if (map[j][i] == '3')
					{
						strite_map.setTextureRect(IntRect(96, 0, 32, 32));
						window.draw(strite_map);
					}
				}
			}
			window.display();
			if (Keyboard::isKeyPressed(Keyboard::Return))
			{
				pause = false;
			}
		}
		for (int i = 0; i < size_lizing; i++)
		{
			int x = lizing[i].x, y = lizing[i].y;
			if (lizing[i].h == '1')
			{
				map[x][y] = '1';
			}
			if (lizing[i].h == '2')
			{
				map[x][y] = '2';
			}
		}
		while (Bo_point)
		{
			if (Bo_point == true)
			{
				points.x = random(x_map, 0, 2);
				points.y = random(y_map, 0, 2);
				if (map[points.x][points.y] == '0')
				{
					map[points.x][points.y] = '3';

					Bo_point = false;
					Bo_point2 = true;
				}
			}
		}
		Time_operation++;
		if (lizing[0].x == 0 && Nap == 0)
		{
			GameOver_setText(points_lizing, record, GameOver);
			GameOver = true;
		}
		if (lizing[0].y == 0 && Nap == 1)
		{
			GameOver_setText(points_lizing, record, GameOver);
			GameOver = true;
		}
		if (lizing[0].x == x_map -1 && Nap == 2)
		{
			GameOver_setText(points_lizing, record, GameOver);
			GameOver = true;
		}
		if (lizing[0].y == y_map -1 && Nap == 3)
		{
			GameOver_setText(points_lizing, record, GameOver);
			GameOver = true;
		}
		if (Keyboard::isKeyPressed(Keyboard::A) && !(Nap == 2))
		{
			Nap = 0;
		}
		if (Keyboard::isKeyPressed(Keyboard::W) && !(Nap == 3))
		{
			Nap = 1;
		}
		if (Keyboard::isKeyPressed(Keyboard::D) && !(Nap == 0))
		{
			Nap = 2;
		}
		if (Keyboard::isKeyPressed(Keyboard::S) && !(Nap == 1))
		{
			Nap = 3;
		}
		for (int i = 1; i < size_lizing; i++)
		{
			switch (Nap)
			{
			case 0:
			{
				if (lizing[0].x - 1 == lizing[i].x && lizing[0].y == lizing[i].y)
				{
					GameOver_setText(points_lizing, record, GameOver);
					GameOver = true;
					i = size_lizing;
				}
				break;
			}

			case 1:
			{
				if (lizing[0].y - 1 == lizing[i].y && lizing[0].x == lizing[i].x)
				{
					GameOver_setText(points_lizing, record, GameOver);
					GameOver = true;
					i = size_lizing;
				}
				break;
			}
			case 2:
			{
				if (lizing[0].x + 1 == lizing[i].x && lizing[0].y == lizing[i].y)
				{
					GameOver_setText(points_lizing, record, GameOver);
					GameOver = true;
					i = size_lizing;
				}
				break;
			}

			case 3:
			{
				if (lizing[0].y + 1 == lizing[i].y && lizing[0].x == lizing[i].x)
				{
					GameOver_setText(points_lizing, record, GameOver);
					GameOver = true;
					i = size_lizing;
				}
				break;
			}

			default:
				break;
			}
		}
		for (int i = 0; i < size_lizing; i++)
		{
			if (!(lizing[i].x == -128))
			{
				lizing_xvost++;
			}
		}
		for (int i = 0; i < x_map; i++)
		{
			for (int j = 0; j < y_map; j++)
			{
				if (!(map[i][j] == '3'))
				{
					Bo_point = true;
				}
				else
				{
					Bo_point = false;
					i = x_map;
					j = y_map;
				}
			}
		}
		if (Nap == 3 && (lizing[0].y < y_map - 1 || lizing[0].x < x_map - 1) && GameOver == false)
		{
			{
				int x_point = lizing[0].x, y_point = lizing[0].y;
				if (map[x_point][y_point + 1] == '3' && lizing[0].y < y_map - 1 && Bo_point2 == true)
				{
					points_lizing++;
					Bo_point2 = false;
					for (int i = 0; i < size_lizing; i++)
					{
						if (lizing[i].x == -128)
						{
							int x_lizing = lizing[i - 1].x, y_lizing = lizing[i - 1].y;
							if ((lizing[i - 1].y - 1) > -1)
							{
								lizing[i].y = y_lizing - 1;
								lizing[i].x = x_lizing;
								lizing[i].h = '2';
								i = size_lizing;
							}
						}
					}
				}
			}
			if (dy < 1000 / speed + 1)
			{
				dy++;
			}
			else
			{
				dy = 0;
				int k = 0;
				for (int i = 0; i < size_lizing; i++)
				{
					if (lizing[0].y < y_map - 1)
					{
						if (lizing[i].h == '1')
						{
							temp_x = lizing[i].x;
							temp_y = lizing[i].y;
							map[temp_x][temp_y] = '0';
							lizing[i].y++;
						}
						if (lizing[i].h == '2')
						{
							int x2 = 0, y2 = 0;
							x2 = lizing[i].x;
							y2 = lizing[i].y;
							map[lizing[i].x][lizing[i].y] = '0';
							lizing[i].x = temp_x;
							lizing[i].y = temp_y;
							temp_x = x2;
							temp_y = y2;
						}
					}
					else
					{
						if (lizing[i].h == '2')
						{
							lizing[i].y++;
							int x2 = lizing[i].x;
							map[x2][size_lizing] = '1';
						}
					}
				}
			}
		}
		if (Nap == 2 && (lizing[0].x < x_map - 1 || lizing[0].y < y_map - 1) && GameOver == false)
		{
			{
				int x_point = lizing[0].x, y_point = lizing[0].y;
				if (map[x_point + 1][y_point] == '3' && lizing[0].x < x_map - 1 && Bo_point2 == true)
				{
					points_lizing++;
					Bo_point2 = false;
					for (int i = 0; i < size_lizing; i++)
					{
						if (lizing[i].x == -128)
						{
							int x_lizing = lizing[i - 1].x, y_lizing = lizing[i - 1].y;
							if ((lizing[i - 1].x - 1) > -1)
							{
								lizing[i].x = x_lizing - 1;
								lizing[i].y = y_lizing;
								lizing[i].h = '2';
								i = size_lizing;
							}
						}
					}
				}
			}
			if (dy < 1000 / speed + 1)
			{
				dy++;
			}
			else
			{
				dy = 0;
				int k = 0;
				for (int i = 0; i < size_lizing; i++)
				{
					if (lizing[0].y < y_map - 1)
					{
						if (lizing[i].h == '1')
						{
							temp_x = lizing[i].x;
							temp_y = lizing[i].y;
							map[temp_x][temp_y] = '0';
							lizing[i].x++;
						}
						if (lizing[i].h == '2')
						{
							int x2 = 0, y2 = 0;
							x2 = lizing[i].x;
							y2 = lizing[i].y;
							map[lizing[i].x][lizing[i].y] = '0';
							lizing[i].x = temp_x;
							lizing[i].y = temp_y;
							temp_x = x2;
							temp_y = y2;
						}
					}
				}
			}
		}
		if (Nap == 0 && (!(lizing[0].x == -1) || !(lizing[0].y == -1)) && GameOver == false)
		{
			{
				int x_point = lizing[0].x, y_point = lizing[0].y;
				if (map[x_point - 1][y_point] == '3' && lizing[0].x > -1 && Bo_point2 == true)
				{
					points_lizing++;
					Bo_point2 = false;
					for (int i = 0; i < size_lizing; i++)
					{
						if (lizing[i].x == -128)
						{
							int x_lizing = lizing[i - 1].x, y_lizing = lizing[i - 1].y;
							if ((lizing[i - 1].x + 1) < x_map + 1)
							{
								lizing[i].x = x_lizing + 1;
								lizing[i].y = y_lizing;
								lizing[i].h = '2';
								i = size_lizing;
							}
						}
					}
				}
			}
			if (dy < 1000 / speed + 1)
			{
				dy++;
			}
			else
			{
				dy = 0;
				int k = 0;
				for (int i = 0; i < size_lizing; i++)
				{
					if (lizing[0].y < y_map - 1)
					{
						if (lizing[i].h == '1')
						{
							temp_x = lizing[i].x;
							temp_y = lizing[i].y;
							map[temp_x][temp_y] = '0';
							lizing[i].x--;
						}
						if (lizing[i].h == '2')
						{
							int x2 = 0, y2 = 0;
							x2 = lizing[i].x;
							y2 = lizing[i].y;
							map[lizing[i].x][lizing[i].y] = '0';
							lizing[i].x = temp_x;
							lizing[i].y = temp_y;
							temp_x = x2;
							temp_y = y2;
						}
					}
				}
			}
		}
		if (Nap == 1 && (!(lizing[0].x == -1) || !(lizing[0].y == -1)) && GameOver == false)
		{
			{
				int x_point = lizing[0].x, y_point = lizing[0].y;
				if (map[x_point][y_point - 1] == '3' && lizing[0].y > -1 && Bo_point2 == true)
				{
					points_lizing++;
					Bo_point2 = false;
					for (int i = 0; i < size_lizing; i++)
					{
						if (lizing[i].x == -128)
						{
							int x_lizing = lizing[i - 1].x, y_lizing = lizing[i - 1].y;
							if ((lizing[i - 1].y + 1) < y_map + 1)
							{
								lizing[i].y = y_lizing + 1;
								lizing[i].x = x_lizing;
								lizing[i].h = '2';
								i = size_lizing;
							}
						}
					}
				}
			}
			if (dy < 1000 / speed + 1)
			{
				dy++;
			}
			else
			{
				dy = 0;
				int k = 0;
				for (int i = 0; i < size_lizing; i++)
				{
					if (lizing[0].y < y_map - 1)
					{
						if (lizing[i].h == '1')
						{
							temp_x = lizing[i].x;
							temp_y = lizing[i].y;
							map[temp_x][temp_y] = '0';
							lizing[i].y--;
						}
						if (lizing[i].h == '2')
						{
							int x2 = 0, y2 = 0;
							x2 = lizing[i].x;
							y2 = lizing[i].y;
							map[lizing[i].x][lizing[i].y] = '0';
							lizing[i].x = temp_x;
							lizing[i].y = temp_y;
							temp_x = x2;
							temp_y = y2;
						}
					}
					else
					{
						if (lizing[i].h == '2')
						{
							lizing[i].y++;
							int x2 = lizing[i].x;
							map[x2][size_lizing] = '1';
						}
					}
				}
			}
		}
		ostringstream os_point_text, os_record;
		os_point_text << points_lizing;
		os_record << record;
		text.setString("Points : " + os_point_text.str() + "\nRecord : " + os_record.str());
		window.clear();
		window.draw(text);
		for (int i = 0; i < y_map; i++)
		{
			for (int j = 0; j < x_map; j++)
			{
				strite_map.setPosition(32 * j + 32, 32 * i + 64);
				if (map[j][i] == '0')
				{
					strite_map.setTextureRect(IntRect(0, 0, 32, 32));
					window.draw(strite_map);
				}
				if (map[j][i] == '1')
				{
					strite_map.setTextureRect(IntRect(32, 0, 32, 32));
					window.draw(strite_map);
				}
				if (map[j][i] == '2')
				{
					strite_map.setTextureRect(IntRect(64, 0, 32, 32));
					window.draw(strite_map);
				}
				if (map[j][i] == '3')
				{
					strite_map.setTextureRect(IntRect(96, 0, 32, 32));
					window.draw(strite_map);
				}
			}
		}
		if (Nap == -1)
		{
			window.draw(text2);
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			pause = true;
		}

		if (GameOver == true)
		{
			window.clear();
			if (points_lizing > record)
			{
				record = points_lizing;
			}

			text.setString(Str_GameOver);
			window.draw(text);

			ofstream osf;
			osf.open("resources/F01_Ir0nK.r");
			if (!osf.is_open())
			{

			}
			else
			{
				osf << record;
			}
			osf.close();
			text2.setPosition(0, 60);
			text2.setString("Press \"Enter\" for reset.");
			if (Keyboard::isKeyPressed(Keyboard::Return))
			{
				for (int i = 0; i < y_map; i++)
				{
					for (int j = 0; j < x_map; j++)
					{
						map[j][i] = '0';
					}
				}
				for (int i = 4; i < size_lizing - 2; i++)
				{
					lizing[i].h = '0';
					lizing[i].x = -128;
					lizing[i].y = -128;
				}
				lizing[0].h = '1';
				lizing[0].x = 1;
				lizing[0].y = 1;
				lizing[1].h = '2';
				lizing[1].x = 2;
				lizing[1].y = 1;
				lizing[2].h = '2';
				lizing[2].x = 3;
				lizing[2].y = 1;
				lizing[3].h = '2';
				lizing[3].x = 3;
				lizing[3].y = 2;
				Nap = -1;
				text2.setString(" ");
				points_lizing = 0;
				GameOver = false;
			}
			window.draw(text2);
			text2.setPosition(0, 732);
		}
		window.display();
	}*/
	
}