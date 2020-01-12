#ifndef _WINDOWGDI_H_
#define WND_CLASSNAME "lunaGui5.0"
#include <vector>
#include <chrono>
#include <iomanip>
#include <functional>

struct SBmpInfo
{
	BITMAPINFO	m_BitmapInfo;
	RGBQUAD		m_bmiColors[3];	// 为BITMAPINFO的m_bmiColors补充两个元素空间
};

struct SGDI
{
	HWND		m_hWnd;
	HDC			m_hMainDC;
	HDC			m_hMemoryDC;
	HBITMAP		m_hMainSurface;
	HBITMAP		m_hOldBitmap;
	int			m_Width;
	int			m_Height;
	UINT* m_pBackBuffer;
	SBmpInfo	m_BmpInfo;
};

class GdiWindow
{
public:
	GdiWindow();

	GdiWindow(HWND p);
	~GdiWindow();
	int  regWindowClass();
	int  createWindow(LPCSTR title);
	void AlphaBlend32(UINT* pDstBmp, int dst_width, UINT* pSrcBmp, int src_width, int blend_width, int blend_height);
	void DrawBmp(UINT* pBmp, int x, int y, int width, int height, int dx, int dy);
	bool Init(HWND hWnd, int width, int height);
	void load_png();
	void End();
	void draw_calll();
	void setTaskbar(bool is);       //是否在任务栏出现
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
public:
	static unsigned char png_data[38965];
	UINT* g_Bmp32 = 0;
	std::vector<unsigned int> _data;
	int _width = 600, _height = 270;
	int i_width = 0, i_height = 0;
private:

	SGDI		g_GDI = {};
	int			g_bmpWidth = 268;
	int			g_bmpHeight = 268;
	HINSTANCE   hInstance = 0;
	HWND        _hWndParent = 0;
	bool        _taskbar = true;
};
class Canvas
{
public:
	Canvas(int w, int h);
	~Canvas();

	void DrawLine(int StartX, int StartY, int EndX, int EndY, UINT* dstIMG, DWORD color);
	int  DrawCircle(int _x, int _y, int n, float R, UINT* dstIMG, DWORD color);

	//对称圆
	void DrawCircle1(int cx, int cy, int r, UINT* dstIMG, DWORD color);

	void Fast_Circle(int xc, int yc, int r, UINT* dstIMG, DWORD color);

	void circleDDA(int cx, int cy, int r, UINT* dstIMG, DWORD color);
private:
	void CirPot(int cx, int cy, int x, int y, UINT* dstIMG, DWORD color);
	void blendcolor(DWORD* dst, DWORD src);
	void SetPixelColor(long x, long y, DWORD c, UINT* pIMG);
	int _width = 0;
	int _height = 0;
private:
	int _type = 4;
};

/*
Timer返回两个时间差
reset函数重置

void fun()
{
cout << ”hello word” << endl;
}
int main()
{
Timer t; //开始计时
fun();
cout << t.elapsed() << endl; //打印fun函数耗时多少毫秒
cout << t.elapsed_micro() << endl; //打印微秒
cout << t.elapsed_nano() << endl; //打印纳秒
cout << t.elapsed_seconds() << endl; //打印秒
cout << t.elapsed_minutes() << endl; //打印分钟
cout << t.elapsed_hours() << endl; //打印小时
}
*/
class Timer
{
public:
	std::time_t getTimeStamp()
	{
		std::chrono::time_point<std::chrono::high_resolution_clock, std::chrono::milliseconds> tp =
			std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now());
		return tp.time_since_epoch().count();
	}
public:
	Timer() : m_begin(std::chrono::high_resolution_clock::now()) {}
	Timer(std::function<void(int64_t ct)> end_func) : m_begin(std::chrono::high_resolution_clock::now())
		, _end_func(end_func)
	{}
	~Timer()
	{
		if (_end_func)
		{
			_end_func(elapsed_micro());
		}
	}
	void reset() { m_begin = std::chrono::high_resolution_clock::now(); }
#if 0
	//默认输出毫秒
	uint64_t elapsed() const
	{
		return (std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now())
			- std::chrono::time_point_cast<std::chrono::milliseconds>(m_begin)).count();
	}
	//微秒
	uint64_t elapsed_micro()const
	{
		return (std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now())
			- std::chrono::time_point_cast<std::chrono::microseconds>(m_begin)).count();
	}
	//纳秒
	uint64_t elapsed_nano()const
	{
		return (std::chrono::time_point_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now())
			- std::chrono::time_point_cast<std::chrono::nanoseconds>(m_begin)).count();
	}
	//秒
	uint64_t elapsed_seconds()const
	{
		return (std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now())
			- std::chrono::time_point_cast<std::chrono::seconds>(m_begin)).count();
	}
	//分
	uint64_t elapsed_minutes()const
	{
		return (std::chrono::time_point_cast<std::chrono::minutes>(std::chrono::high_resolution_clock::now())
			- std::chrono::time_point_cast<std::chrono::minutes>(m_begin)).count();
	}
	//时
	uint64_t elapsed_hours()const
	{
#ifdef _WIN32
		return std::chrono::duration_cast<std::chrono::hours>(std::chrono::high_resolution_clock::now() - m_begin).count();
#else
		return (std::chrono::time_point_cast<std::chrono::hours>(std::chrono::high_resolution_clock::now())
			- std::chrono::time_point_cast<std::chrono::hours>(m_begin)).count();
#endif
	}
#else
	//默认输出毫秒
	uint64_t elapsed() const
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - m_begin).count();
	}
	//微秒
	uint64_t elapsed_micro() const
	{
		return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - m_begin).count();
	}
	//纳秒
	uint64_t elapsed_nano() const
	{
		return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_begin).count();
	}
	//秒
	uint64_t elapsed_seconds() const
	{
		return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - m_begin).count();
	}
	//分
	uint64_t elapsed_minutes() const
	{
		return std::chrono::duration_cast<std::chrono::minutes>(std::chrono::high_resolution_clock::now() - m_begin).count();
	}
	//时
	uint64_t elapsed_hours() const
	{
		return std::chrono::duration_cast<std::chrono::hours>(std::chrono::high_resolution_clock::now() - m_begin).count();
	}

#endif
private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_begin;
	std::function<void(int64_t ct)> _end_func;
};

#endif /*_WINDOWGDI_H_*/
