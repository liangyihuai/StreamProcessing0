#pragma once



// ThreadOfInputStreamPrint

class ThreadOfInputStreamPrint : public CWinThread
{
	DECLARE_DYNCREATE(ThreadOfInputStreamPrint)

protected:
	ThreadOfInputStreamPrint();           // protected constructor used by dynamic creation
	virtual ~ThreadOfInputStreamPrint();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	static UINT runThread(LPVOID param);
protected:
	DECLARE_MESSAGE_MAP()
};


