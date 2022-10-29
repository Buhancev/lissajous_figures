#pragma once
#include <Windows.h>
#include <cmath>

/*

16.	����������� ���������, ��������������� �� ������� ������ �������. ������ �������� �� ���������� ������:

x(t) = Ax * sin( Wx*t + Dx);
y(t) = Ay * sin( Wy*t + Dy);

(x,y) � ���������� ����� � ������ ������� t
Ax, Wx, Dx � ��������� X ������
Ay, Wy, Dy � ��������� Y ������

����������� ���������� �������� x(t) � y(t) ���������� ������� � ��������� �������������� �������. 
�������� �����, ������ ������ �������, ������ ����������� � �������������� ������� ������� �������� 
����������� ��������� X � Y � ������� ����� �� �������. 
������������� �� ����� ������ ������� / ���������, 
��������� ���������� (A, W, D), 
��� ������� �� �������� ������� ����������, ��������������� �� ����� �� ������.

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
	HANDLE hMutex;  //������ ������

	//������� "����� ������"
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
	
	//�������� �����, ������ ������ �������, ������ ����������� 
	//� �������������� ������� ������� �������� 

	//���������� �������� x, y � ������ ������� t
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

