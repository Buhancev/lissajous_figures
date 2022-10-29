#pragma once
#include <Windows.h>
#include <cmath>

/*

16.	Разработать программу, демонстрирующую на графике фигуры Лиссажу. График строится по следующему закону:

x(t) = Ax * sin( Wx*t + Dx);
y(t) = Ay * sin( Wy*t + Dy);

(x,y) – координаты точки в момент времени t
Ax, Wx, Dx – параметры X канала
Ay, Wy, Dy – параметры Y канала

Непрерывное вычисление значений x(t) и y(t) необходимо сделать в отдельных дополнительных потоках. 
Основной поток, каждый момент времени, должен запрашивать у дополнительных потоков текущее значение 
вычисленных координат X и Y и ставить точку на графике. 
Предусмотреть на форме кнопки запуска / остановки, 
изменение параметров (A, W, D), 
для каждого из дочерних потоков независимо, непосредственно во время их работы.

*/


class RMutexLocker
{
	HANDLE hMutex;
public:
	RMutexLocker(HANDLE mutex):hMutex(mutex)
	{
		WaitForSingleObject(hMutex, INFINITE);
	}
	~RMutexLocker()
	{
		ReleaseMutex(hMutex);
	}
};


class Lissajous
{
private:

	double timeX;
	double timeY;
	double x;
	double y;

	HANDLE hThread[2];
	HANDLE hMutex;  //защита данных

	//событие "конец работы"
	HANDLE hStopEvt;   

	double Ax, Wx, Dx;
	double Ay, Wy, Dy;

	void CalcX();
	void CalcY();

	static DWORD WINAPI ThreadFuncX(LPVOID ptr);
	static DWORD WINAPI ThreadFuncY(LPVOID ptr);

public:
	Lissajous();
	~Lissajous();


	void start();
	void stop();
	
	//Основной поток, каждый момент времени, должен запрашивать 
	//у дополнительных потоков текущее значение 

	//возвращаем значения x, y в момент времени t
	double getX() const;
	double getY() const;

	void resetTime();

	double getTimeX();
	double getTimeY();

	double getAx();
	double getWx();
	double getDx();

	double getAy();
	double getWy();
	double getDy();

	void setAx(double A);
	void setWx(double W);
	void setDx(double D);

	void setAy(double A);
	void setWy(double W);
	void setDy(double D);

	bool isWorking();

};

