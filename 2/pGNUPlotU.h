// A C++ interface to gnuplot. 
#ifndef PGNUPLOT_H
#define PGNUPLOT_H

#include <stdio.h>
#include <windows.h>

class CpGnuplotU
{
public:
	CpGnuplotU(const WCHAR* gnuplotName);
	~CpGnuplotU();

	// send a command to gnuplot
	void cmd(const WCHAR* format, ...);

private:
	// FILE *_pipe;
	HWND _hWndParent;
	HWND _hWndText;
	HWND _hWndGraph;

	friend BOOL CALLBACK cbGetTextWindow(HWND hWnd, LPARAM  lParam);
	friend BOOL CALLBACK cbGetGraphWindow(HWND hWnd, LPARAM  lParam);
};

#endif