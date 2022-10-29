#include "Lissajous.h"

Lissajous::Lissajous()
{
	timeX = 0;
	timeY = 0;

	x = 0;
	y = 0;

	hThread[0] = INVALID_HANDLE_VALUE;
	hThread[1] = INVALID_HANDLE_VALUE;

	hMutex = CreateMutex(NULL, FALSE, NULL);

	hStopEvt = CreateEvent(NULL, TRUE, FALSE, NULL);
	

	Ax = 5, Wx = 1, Dx = 1;
	Ay = 4, Wy = 1; Dy = 2;
}

Lissajous::~Lissajous()
{
	stop();
	CloseHandle(hStopEvt);
}

void Lissajous::CalcX()
{
	RMutexLocker guard(hMutex);
	
	x = Ax * sin(Wx * timeX + Dx);
	
	timeX += 0.5;
}

void Lissajous::CalcY()
{
	RMutexLocker guard(hMutex);

	y = Ay * sin(Wy * timeY + Dy);

	timeY += 0.5;
}

DWORD WINAPI Lissajous::ThreadFuncX(LPVOID ptr)
{
	Lissajous* _this = (Lissajous*)ptr;
	if (!_this) 
		return 1;

	
	for (;;)
	{
		_this->CalcX();
		if (WaitForSingleObject(_this->hStopEvt, 100) != WAIT_TIMEOUT)
			break;
	}
}

DWORD WINAPI Lissajous::ThreadFuncY(LPVOID ptr)
{
	Lissajous* _this = (Lissajous*)ptr;
	if (!_this) 
		return 1;

	for (;;)
	{
		_this->CalcY();
		if (WaitForSingleObject(_this->hStopEvt, 100) != WAIT_TIMEOUT)
			break;
	}
}

void Lissajous::start()
{
	if (hThread[0] != INVALID_HANDLE_VALUE || hThread[1] != INVALID_HANDLE_VALUE)
		return;

	ResetEvent(hStopEvt);

	hThread[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadFuncX, this, 0, NULL);
	hThread[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadFuncY, this, 0, NULL);
}

void Lissajous::stop()
{
	if (hThread[0] == INVALID_HANDLE_VALUE || hThread[1] == INVALID_HANDLE_VALUE)
		return;

	SetEvent(hStopEvt);

	if (WaitForMultipleObjects(2, hThread, TRUE, 1000))
	{
		TerminateThread(hThread[0], 1);
		TerminateThread(hThread[1], 1);
	}

	CloseHandle(hThread[0]);
	CloseHandle(hThread[1]);

	hThread[0] = INVALID_HANDLE_VALUE;
	hThread[1] = INVALID_HANDLE_VALUE;
}

double Lissajous::getX() const
{
	return x;
}

double Lissajous::getY() const
{
	return y;
}

double Lissajous::getTimeX()
{
	return timeX;
}
double Lissajous::getTimeY()
{
	return timeY;
}


double Lissajous::getAx()
{
	return Ax;
}

double Lissajous::getWx()
{
	return Wx;

}

double Lissajous::getDx()
{
	return Dx;
}

double Lissajous::getAy()
{
	return Ay;
}

double Lissajous::getWy()
{
	return Wy;
}

double Lissajous::getDy()
{
	return Dy;
}


void Lissajous::setAx(double A)
{
	RMutexLocker guard(hMutex);
	Ax = A;
}
void Lissajous::setWx(double W)
{
	RMutexLocker guard(hMutex);
	Wx = W;
}
void Lissajous::setDx(double D)
{
	RMutexLocker guard(hMutex);
	Dx = D;
}

void Lissajous::setAy(double A)
{
	RMutexLocker guard(hMutex);
	Ay = A;
}
void Lissajous::setWy(double W)
{
	RMutexLocker guard(hMutex);
	Wy = W;
}
void Lissajous::setDy(double D)
{
	RMutexLocker guard(hMutex);
	Dy = D;
}

void Lissajous::resetTime()
{
	RMutexLocker guard(hMutex);
	timeX = 0;
	timeY = 0;
}

bool Lissajous::isWorking()
{
	return (hThread[0] != INVALID_HANDLE_VALUE && hThread[1] != INVALID_HANDLE_VALUE) ? true : false;
}