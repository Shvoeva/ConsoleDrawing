#pragma warning(disable:4996)
#include <iostream>
#include <conio.h>
using namespace std;

const char* namef = "image.bmp";

const int Width = 64;
const int Height = 64;

const char Light = 32;
const char Cursor = 176;
const char Dark = 178;

const int Space = 32;
const int AKey = 97;
const int CKey = 99;
const int SKey = 115;
const int EnterKey = 13;
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


bool SaveInBMPFormat(bool** image)
{
	FILE* f;
	
	unsigned char *bmp = NULL;
	bmp = (unsigned char*) malloc (3 * Width * Height);
	memset(bmp, 0, sizeof(bmp));
	for (int i = 0; i < Width; i++)
	{
		for (int j = 0; j < Height; j++)
		{
			unsigned char w = image[i][j] * 255;
			bmp[(j + i * Width) * 3 + 2] = (w);
			bmp[(j + i * Width) * 3 + 1] = (w);
			bmp[(j + i * Width) * 3 + 0] = (w);
		}
	}

	unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
	unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
	unsigned char bmppad[3] = {0,0,0};
	int filesize = 54 + 3 * Width * Height;
	
	bmpfileheader[2] = (unsigned char)(filesize);
	bmpfileheader[3] = (unsigned char)(filesize >> 8);
	bmpfileheader[4] = (unsigned char)(filesize >> 16);
	bmpfileheader[5] = (unsigned char)(filesize >> 24);

	bmpinfoheader[4] = (unsigned char)(Width);
	bmpinfoheader[5] = (unsigned char)(Width >> 8);
	bmpinfoheader[6] = (unsigned char)(Width >> 16);
	bmpinfoheader[7] = (unsigned char)(Width >> 24);
	bmpinfoheader[8] = (unsigned char)(Height);
	bmpinfoheader[9] = (unsigned char)(Height >> 8);
	bmpinfoheader[10] = (unsigned char)(Height >> 16);
	bmpinfoheader[11] = (unsigned char)(Height >> 24);

	f = fopen(namef, "wb");
	fwrite(bmpfileheader, 1, 14, f);
	fwrite(bmpinfoheader, 1, 40, f);
	for (int i = 0; i < Height; i++)
	{
		fwrite(bmp + (Width * (Height - i - 1) * 3), 3, Width, f);
		fwrite(bmppad, 1, (4 - (Width * 3) % 4) % 4, f);
	}
	
	fclose(f);
	return 1;
}

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
			}
			break;
		case ArrowDown:
			if (pointer.Y != Height - 1)
			{
				pointer.Y++;
			}
			break;
		case ArrowRight:
			if (pointer.X != Width - 1)
			{
				pointer.X++;
			}
			break;
		case ArrowLeft:
			if (pointer.X != 0)
			{
				pointer.X--;
			}
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
	cout << "\t\t\t\t\t deleting - \"C\" kay;" << endl;
	cout << "\t\t\t\t\t cleaning the canvas - \"A\" kay;" << endl << endl;
	cout << "\t\t\t\t\t exit the program and save the image in bmp format - \"S\" kay." << endl;
	cout << "\t\t\t\t\t exit the program - \"Enter\" kay." << endl << endl << endl;
	cout << "\t\t\t\tIn order to draw more conveniently, make the font smaller." << endl << "\t ";
}

void RedrawMenu(bool** image, Coordinates &pointer)
{
	system("cls");
	DisplayText();
	OutputCanvas(image, pointer);
}

int main()
{
	bool flag = 0;
	Coordinates pointer;
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
		} while (c1 != AKey && c1 != CKey && c1 != SKey && c1 != Space && c1 != Arrows && c1 != EnterKey);

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
			case SKey:
				flag = SaveInBMPFormat(image);
				break;
			case EnterKey:
				flag = 1;
				break;
			default: break;
		}
	} while (flag == 0);

	DeleteArray(image);
	
	return 0;
}