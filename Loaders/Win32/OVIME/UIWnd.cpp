#define OV_DEBUG

#include "OVIME.h"

LRESULT APIENTRY UIWndProc(HWND hWnd,
						   UINT msg,
						   WPARAM wParam,
						   LPARAM lParam)
{
	HIMC			hUICurIMC;
	LPINPUTCONTEXT	lpIMC;
	LONG			lRet = 0L;
	LPMYPRIVATE lpMyPrivate;

	hUICurIMC = (HIMC)GetWindowLong(hWnd, IMMGWL_IMC);

	//
	// Even if there is no current UI. these messages should not be pass to 
	// DefWindowProc().
	//
	if(!hUICurIMC)
	{        
		switch (msg)
		{
		case WM_IME_STARTCOMPOSITION:
		case WM_IME_ENDCOMPOSITION:
		case WM_IME_COMPOSITION:
		case WM_IME_NOTIFY:
		case WM_IME_CONTROL:
		case WM_IME_COMPOSITIONFULL:
		case WM_IME_SELECT:
		case WM_IME_CHAR:
			return 0L;
		default:
			break;
		}
	}

	switch (msg)
	{
		murmur("UIMSG");	

	case WM_WINDOWPOSCHANGING: //The WM_WINDOWPOSCHANGING message is sent to a window whose size, position, or place in the Z order is about to change as a result of a call to the SetWindowPos function or another window-management function.
		murmur("WM_WINDOWPOSCHANGING");
		break;
			
	case WM_MOUSEACTIVATE:
		murmur("WM_MOUSEACTIVATE");
		break;
	case WM_ACTIVATEAPP:
		murmur("WM_ACTIVATEAPP");
		break;
	case WM_CHILDACTIVATE:
		murmur("WM_CHILDACTIVATE");
		break;
	case WM_CREATE:  
		murmur("WM_CREATE");
		CompX = CompY = -1;
		UICreateCompWindow(hWnd);
		UICreateCandWindow(hWnd);
		UICreateNotifyWindow(hWnd);
		break;
		
	case WM_IME_SETCONTEXT:
		murmur("WM_IME_SETCONTEXT");
		murmur("%p",lParam);
		
		//switch(lParam)
		//{
		//case ISC_SHOWUICOMPOSITIONWINDOW:
		//	murmur("ISC_SHOWUICOMPOSITIONWINDOW");
		//	break;
		//	/*case ISC_SHOWUIGUIDWINDOW:
		//	murmur("ISC_SHOWUIGUIDWINDOW");
		//	break;
		//	case ISC_SHOWUISOFTKBD:
		//	murmur("ISC_SHOWUISOFTKBD");
		//	break;*/
		//case ISC_SHOWUICANDIDATEWINDOW:
		//	murmur("ISC_SHOWUICANDIDATEWINDOW");
		//	break;
		//case ISC_SHOWUICANDIDATEWINDOW << 1:
		//	murmur("ISC_SHOWUICANDIDATEWINDOW << 1");
		//	break;
		//case ISC_SHOWUICANDIDATEWINDOW << 2:
		//	murmur("ISC_SHOWUICANDIDATEWINDOW << 2");
		//	break;
		//case ISC_SHOWUICANDIDATEWINDOW << 3:
		//	murmur("ISC_SHOWUICANDIDATEWINDOW << 3");
		//	break;
		//default:
		//	
		//	break;
		//}
		if (wParam) //TRUE if the window is active, and FALSE otherwise.
		{
			murmur("wParm=%p",wParam);
			murmur("hUICurIMC:%p", hUICurIMC);
			if (hUICurIMC)  //hUICurIMC==0 ��ܥX��
			{
				lpIMC = ImmLockIMC(hUICurIMC);
				murmur("lpIMC:%p", lpIMC);
				if (lpIMC)
				{
					//James add
					POINT pt;
					if(CompX < 0)
					{
						pt.x = 15;
						pt.y = 15;
						ClientToScreen(lpIMC->hWnd, &pt);
						CompX = pt.x;
						CompY = pt.y;
					}

					lpMyPrivate = (LPMYPRIVATE)ImmLockIMCC(lpIMC->hPrivate);
					if(lpMyPrivate->PreEditStr)
					{
						if(wcslen(lpMyPrivate->PreEditStr))
						{
							UIMoveCompWindow(hWnd, CompX, CompY, lpMyPrivate->PreEditStr);
							UISetCompStr(lpMyPrivate->PreEditStr);
							UIShowCompWindow();
						}
						else
							UIHideCompWindow();
					}
					else
					{
						UIHideCompWindow();
					}

					if(lpMyPrivate->CandStr)
					{
						if(wcslen(lpMyPrivate->CandStr))
						{
							UIMoveCandWindow(hWnd, CompX,CompY+20,NULL);
							UISetCandStr(lpMyPrivate->CandStr);
							UIShowCandWindow();
						}
						else
							UIHideCandWindow();
					}
					else
					{
						UIHideCandWindow();
					}
					ImmUnlockIMCC(lpIMC->hPrivate);
				}
				else
				{
					murmur("hUICurIMC=NULL");
					UIHideCandWindow();
					UIHideCompWindow();
				}
				ImmUnlockIMC(hUICurIMC);
			}
			else   // it is NULL input context.
			{
				UIHideCandWindow();
				UIHideCompWindow();
			}
		}
		else //�Y��o��else���� �h��������c# form ���|����
		{
			murmur("wParam=NULL");
			UIHideCandWindow();
			UIHideCompWindow();
		}
		break;

	case WM_IME_STARTCOMPOSITION:
		murmur("WM_IME_STARTCOMPOSITION");
		break;

	case WM_IME_COMPOSITION:
		murmur("WM_IME_COMPOSITION");
		//test
		//MyGenerateMessage(hWnd, WM_IME_NOTIFY, IMN_SETCANDIDATEPOS, 0);

		//lRet = NotifyHandle(hUICurIMC, hWnd, WM_IME_NOTIFY, IMN_SETCANDIDATEPOS, NULL);

		lpIMC = ImmLockIMC(hUICurIMC);
		POINT pt;
		if(CompX < 0) {
			pt.x = 15;
			pt.y = 15;
			ClientToScreen(lpIMC->hWnd, &pt);
			CompX = pt.x;
			CompY = pt.y;
		}
		lpMyPrivate = (LPMYPRIVATE)ImmLockIMCC(lpIMC->hPrivate);		

		if(lpMyPrivate->PreEditStr)
		{
			if(wcslen(lpMyPrivate->PreEditStr))
			{
				UIMoveCompWindow(hWnd, CompX, CompY, lpMyPrivate->PreEditStr);
				UISetCompStr(lpMyPrivate->PreEditStr);
				UIShowCompWindow();
			}
			else
				UIHideCompWindow();
		}
		else
		{
			UIHideCompWindow();
		}
		
		if(lpMyPrivate->CandStr)
		{
			if(wcslen(lpMyPrivate->CandStr))
			{
				UIMoveCandWindow(hWnd, CompX,CompY+20,NULL);
				UISetCandStr(lpMyPrivate->CandStr);
				UIShowCandWindow();
			}
			else
				UIHideCandWindow();
		}
		else
		{
			UIHideCandWindow();
		}
		ImmUnlockIMCC(lpIMC->hPrivate);
		ImmUnlockIMC(hUICurIMC);
		break;
		
	case WM_IME_ENDCOMPOSITION:
		murmur("WM_IME_ENDCOMPOSITION");
		UIHideCompWindow();
		UIHideCandWindow();
		break;
		
	case WM_IME_COMPOSITIONFULL:
		murmur("WM_IME_COMPOSITIONFULL");
		break;
		
	case WM_IME_SELECT:
		murmur("WM_IME_SELECT");
		break;
		
	case WM_IME_CONTROL:
		murmur("WM_IME_CONTROL");
		lRet = ControlHandle(hUICurIMC, hWnd, msg, wParam, lParam);
		break;
		
		
	case WM_IME_NOTIFY:
		murmur("WM_IME_NOTIFY: %p",wParam);
		lRet = NotifyHandle(hUICurIMC, hWnd, msg, wParam, lParam);
		break;
		
	case WM_DESTROY:
		murmur("WM_DESTROY");
		loader->closeModule();
		break;

	case WM_IME_RELOADCONFIG:
		murmur("WM_IME_RELOADCONFIG");
		loader = AVLoader::getLoader();
		loader->reloadConfig();
		break;

	default:
		murmur("no this message,%p",msg);
		return DefWindowProc(hWnd,msg,wParam,lParam);
    }
    return lRet;
}
