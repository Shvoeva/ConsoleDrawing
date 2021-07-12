#include <iostream>
#include <conio.h>
using namespace std;

const int Width = 64;
const int Height = 64;

const char Light = 32;
const char Cursor = 176;
const char Dark = 178;

const int Space = 32;
const int AKey = 97;
const int CKey = 99;
const int SKey = 115;
const int Arrows = -32;

const int ArrowUp = 72;
const int ArrowDown = 80;
const int ArrowRight = 77;
const int ArrowLeft = 75;


struct Coordinates
{
	int X = 0;
	int Y = 0;
};


void DeleteArray(bool** image)
{
	for (int i = 0; i < Height; i++)
	{
		delete[] image[i];
	}
	delete[] image;
}

bool** ClearAll(bool** image)
{
	for (int i = 0; i < Height; i++)
	{
		for (int j = 0; j < Width; j++)
		{
			image[i][j] = 0;
		}
	}
	return image;
}

bool** DeletePoint(bool** image, Coordinates &pointer)
{
	image[pointer.Y][pointer.X] = 0;
	return image;
}

bool** PaintOver(bool** image, Coordinates &pointer)
{
	image[pointer.Y][pointer.X] = 1;
	return image;
}

Coordinates MovePointer(Coordinates &pointer, int key)
{
	switch (key)
	{
		case ArrowUp:
			if (pointer.Y != 0)
			{
				pointer.Y--;
			};
			break;
		case ArrowDown:
			if (pointer.Y != Height - 1)
			{
				pointer.Y++;
			};
			break;
		case ArrowRight:
			if (pointer.X != Width - 1)
			{
				pointer.X++;
			};
			break;
		case ArrowLeft:
			if (pointer.X != 0)
			{
				pointer.X--;
			};
			break;
	}

	return pointer;
}

void OutputCanvas(bool** image, Coordinates &pointer)
{
	for (int j = 0; j < Width; j++)
	{
		cout << "__";
	}
	cout << endl;

	for (int i = 0; i < Height; i++)
	{
		cout << "\t|";

		for (int j = 0; j < Width; j++)
		{
			if (i == pointer.Y && j == pointer.X)
			{
				cout << Cursor;
				cout << Cursor;
			}
			else
			{
				if (image[i][j] == 1)
				{
					cout << Dark;
					cout << Dark;
				}
				else
				{
					cout << Light;
					cout << Light;
				}
			}
		}

		cout << '|' << endl;
	}

	cout << "\t|";
	for (int j = 0; j < Width; j++)
	{
		cout << "__";
	}
	cout << '|' << endl << endl;
}

void DisplayText()
{
	cout << endl << "\t\t\t\t\t\t\t\t__CONSOLE DRAW__" << endl;
	cout << "\t\t\t\tCOMMANDS:" << endl;
	cout << "\t\t\t\t\t pen move - up key, down key, left key, right key;" << endl;
	cout << "\t\t\t\t\t painting - space key;" << endl;
	cout << "\t\t\t\t\t deleting - \"C\" kay;" << endl << endl;
	cout << "\t\t\t\t\t cleaning the canvas - \"A\" kay;" << endl;
	cout << "\t\t\t\t\t save picture in bmp format - \"S\" kay." << endl << "\t ";
}

void RedrawMenu(bool** image, Coordinates &pointer)
{
	system("cls");
	DisplayText();
	OutputCanvas(image, pointer);
}

int main()
{
	Coordinates pointer;
	bool flag = 0;
	bool** image = new bool* [Height];
	for (int i = 0; i < Height; i++)
	{
		image[i] = new bool[Width];
	}
	image = ClearAll(image);

	do
	{
		RedrawMenu(image, pointer);

		char c1;
		char c2;
		do
		{
			c1 = _getch();
			if (c1 == Arrows)
			{
				c2 = _getch();
			}
		} while (c1 != AKey && c1 != SKey && c1 != CKey && c1 != Space && c1 != Arrows);

		switch (c1)
		{
		case Arrows:
			pointer = MovePointer(pointer, c2);
			break;
		case Space:
			image = PaintOver(image, pointer);
			break;
		case AKey:
			image = ClearAll(image);
			break;
		case CKey:
			image = DeletePoint(image, pointer);
			break;
			//case SKey: break;
		}
	} while (flag == 0);

	DeleteArray(image);
	
	return 0;
}