// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#pragma once

// Change these values to use different versions
#define WINVER		    0x0600
#define _WIN32_WINNT	0x0600
#define _WIN32_IE	    0x0700
#define _WTL_NO_WTYPES  // WTL shouldn't define CRect/CPoint/CSize

#include <atlbase.h>
#include <atltypes.h>   // shared CRect/CPoint/CSize
#include <atlapp.h>     // base WTL classes
extern CAppModule _Module;
#include <atlwin.h>

#include <atlframe.h>
#include <atlmisc.h>
#include <atlcrack.h>
#include <atltheme.h>
#include <atlctrls.h>
#include <atlctrlx.h>

#include <dwmapi.h>     // DWM APIs

#if defined _M_IX86
  #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
  #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
  #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
  #pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
