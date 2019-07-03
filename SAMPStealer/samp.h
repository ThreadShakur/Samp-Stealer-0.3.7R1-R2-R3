enum
{
	DIALOG_STYLE_MSGBOX = 0,
	DIALOG_STYLE_INPUT = 1,
	DIALOG_STYLE_LIST = 2,
	DIALOG_STYLE_PASSWORD = 3,
};

#pragma pack( push, 1 )
struct stDialogInfo
{
	void				*pVTBL;
	int					iTextPoxX;
	int					iTextPoxY;
	int					iTextSizeX;
	int					iTextSizeY;
	int					iBtnOffsetX;
	int					iBtnOffsetY;
	class _CDXUTDialog	*pDialog;
	class _CDXUTListBox *pList;
	class _CDXUTEditBox *pEditBox;
	int					iIsActive;
	int					iType;
	DWORD				DialogID;
	char				*pText;
	DWORD				font;
	DWORD				font2;
	char				szCaption[64];
	uint8_t				byteUnknown;
	bool				bServerside;
};
#pragma pack( pop )


class CSAMP
{
	DWORD dwSAMPAddr;
	DWORD dwSampInfo;

	DWORD dwIPOffset;
	DWORD dwHostnameOffset;
	DWORD dwPortOffset;
	DWORD dwNameOffset;

	stDialogInfo *pDialogInfo;
public:
	DWORD dwCloseDialogHook;
	int version;

	CSAMP( void ) : dwSAMPAddr( NULL ) {};
	bool Initialize( void );
	bool IsInitialized( void );
	DWORD GetBase( void ) { return dwSAMPAddr; }


	char* GetIP(void) { return (char*)(dwSampInfo + dwIPOffset); }
	char* GetHostname( void ) { return (char*)(dwSampInfo + dwHostnameOffset); }
	int GetPort(void) { return *(int *)(dwSampInfo + dwPortOffset); }
	char* GetNickName( void ) { return (char*)(dwSAMPAddr + dwNameOffset); }

	stDialogInfo *GetDialogInfo( void ) { return pDialogInfo; }

};

extern CSAMP *SAMP;