
// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclude rarely-used stuff from Windows headers
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions


#include <afxdisp.h>        // MFC Automation classes



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // MFC support for ribbons and control bars



#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif



#include "Result.h"
#include "EnhanceEventResult.h"
#include "DoubleResult.h"
#include "LongResult.h"
#include "BoolResult.h"
#include "RadarEvent.h"

#include "Event.h"
#include "Utils.h"
#include "EventGenerator.h"
#include "FileReaderUtils.h"
#include <exception>

#include <iostream>
#include <string>

#include "QueueWriter.h"

#include "QueueReader.h"

#include "Process.h"

#include "GreaterEqualThanInt.h"
#include "GreaterThanFloat.h"
#include "EqualString.h"
#include "And.h"
#include "LessThanFloat.h"
#include "TruePredicate.h"

#include "EventFilterSpecParser.h"
#include "EventCaptureSpecParser.h"
#include "CQSpecParser.h"
#include "CEPSpecParser.h"

#include "glog/logging.h"

#include "SinkType.h"
#include <afxcontrolbars.h>
#include <afxwin.h>

#include "Consts.h"
