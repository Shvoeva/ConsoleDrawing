#include <iostream>
#include <conio.h>
using namespace std;

const int width = 64;
const int height = 64;

const int emp = 32;
const int cur = 176;
const int pai = 178;

const int space = 32;
const int akey = 97;
const int ckey = 99;
const int skey = 115;
const int arrows = -32;

const int ArrowUp = 72;
const int ArrowDown = 80;
const int ArrowRight = 77;
const int ArrowLeft = 75;


struct Coordinates
{
	int x = 0;
	int y = 0;
};


bool** ClearAll(bool** image, Coordinates pointer)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			image[i][j] = 0;
		}
	}
	return image;
}

bool** DeletePoint(bool** image, Coordinates pointer)
{
	image[pointer.y][pointer.x] = 0;
	return image;
}

bool** PaintOver(bool** image, Coordinates pointer)
{
	image[pointer.y][pointer.x] = 1;
	return image;
}

Coordinates MovePointer(Coordinates pointer, int key)
{
	switch (key)
	{
	case ArrowUp:
		if (pointer.y != 0)
		{
			pointer.y--;
		}
		break;
	case ArrowDown:
		if (pointer.y != height - 1)
		{
			pointer.y++;
		}
		break;
	case ArrowRight:
		if (pointer.x != width - 1)
		{
			pointer.x++;
		}
		break;
	case ArrowLeft:
		if (pointer.x != 0)
		{
			pointer.x--;
		}
		break;
	}

	return pointer;
}

void RedrawMenu(bool** image, Coordinates pointer)
{
	system("cls");

	cout << endl << "\t\t\t\t\t\t\t\t__CONSOLE DRAW__" << endl;
	cout << "\t\t\t\tCOMMANDS:" << endl;
	cout << "\t\t\t\t\t pen move - up key, down key, left key, right key;" << endl;
	cout << "\t\t\t\t\t painting - space key;" << endl;
	cout << "\t\t\t\t\t deleting - \"C\" kay;" << endl << endl;
	cout << "\t\t\t\t\t cleaning the canvas - \"A\" kay;" << endl;
	cout << "\t\t\t\t\t save picture in bmp format - \"S\" kay." << endl << "\t ";

	for (int j = 0; j < width; j++)
	{
		cout << "__";
	}
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		cout << "\t|";

		for (int j = 0; j < width; j++)
		{
			if (i == pointer.y && j == pointer.x)
			{
				cout << (char)cur;
				cout << (char)cur;
			}
			else
			{
				if (image[i][j] == 1)
				{
					cout << (char)pai;
					cout << (char)pai;
				}
				else
				{
					cout << (char)emp;
					cout << (char)emp;
				}
			}
		}

		cout << '|' << endl;
	}

	cout << "\t|";
	for (int j = 0; j < width; j++)
	{
		cout << "__";
	}
	cout << '|' << endl << endl;
}

int main()
{
	Coordinates pointer;
	bool flag = 0;
	bool** image = new bool* [height];
	for (int i = 0; i < height; i++)
	{
		image[i] = new bool[width];
		for (int j = 0; j < width; j++)
		{
			image[i][j] = 0;
		}
	}

	do
	{
		RedrawMenu(image, pointer);

		char c1, c2;
		do
		{
			c1 = _getch();
			if (c1 == arrows)
			{
				c2 = _getch();
			}
		} while (c1 != akey && c1 != skey && c1 != ckey && c1 != space && c1 != arrows);

		switch (c1)
		{
		case arrows:
			pointer = MovePointer(pointer, c2);
			break;
		case space:
			image = PaintOver(image, pointer);
			break;
		case akey:
			image = ClearAll(image, pointer);
			break;
		case ckey:
			image = DeletePoint(image, pointer);
			break;
			//case skey: break;
		}
	} while (flag == 0);

	for (int i = 0; i < height; i++)
	{
		delete[] image[i];
	}

	return 0;
}