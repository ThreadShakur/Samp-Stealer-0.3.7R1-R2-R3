/*
* PROJECT: WH
* COPYRIGHT: FYP, urShadow
* FILE: samp.cpp
*/

#include "main.h"
#include <iostream>


bool CSAMP::IsInitialized(void)
{
	return dwSAMPAddr != NULL;
}

bool CSAMP::Initialize(void)
{
	if (dwSAMPAddr == NULL) dwSAMPAddr = (DWORD)GetModuleHandle("samp.dll");
	if (dwSAMPAddr == NULL) return false;



	else if (*(DWORD*)(dwSAMPAddr + 0x6C04D) == 0xA164) //R1
	{
		version = 1;

		dwCloseDialogHook = 0x6C04D;

		dwNameOffset = 0x219A6F;
		dwIPOffset = 0x20;
		dwPortOffset = 0x225;
		dwHostnameOffset = 0x121;

		dwSampInfo = *(DWORD*)(dwSAMPAddr + 0x21A0F8);
		pDialogInfo = *(stDialogInfo * *)(dwSAMPAddr + 0x21A0B8);
	}
	if (*(DWORD*)(dwSAMPAddr + 0x6C0FD) == 0xA164) //R2
	{
		version = 2;

		dwCloseDialogHook = 0x6C0FD;

		dwNameOffset = 0x219A77;
		dwIPOffset = 0x1C;
		dwPortOffset = 0x221;
		dwHostnameOffset = 0x11D;

		dwSampInfo = *(DWORD*)(dwSAMPAddr + 0x21A100);
		pDialogInfo = *(stDialogInfo * *)(dwSAMPAddr + 0x21A0C0);
	}
	else if (*(DWORD*)(dwSAMPAddr + 0x6FF4D) == 0xA164) //R3
	{
		version = 3;

		dwCloseDialogHook = 0x6FF4D;

		dwNameOffset = 0x26E03F;
		dwIPOffset = 0x30;
		dwPortOffset = 0x235;
		dwHostnameOffset = 0x131;

		dwSampInfo = *(DWORD *)(dwSAMPAddr + 0x26E8DC);
		pDialogInfo = *(stDialogInfo * *)(dwSAMPAddr + 0x26E898);
	}



	return pDialogInfo != nullptr;
}