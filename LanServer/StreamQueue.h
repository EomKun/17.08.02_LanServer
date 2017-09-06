/////////////////////////////////////////////////////////////////////
// www.gamecodi.com						이주행 master@gamecodi.com
//
//
/////////////////////////////////////////////////////////////////////
/*---------------------------------------------------------------

	Aya Library - Stream SingleQueue

	원형 FIFO 스트리밍 큐.


	완성된 패킷을 만들기 위해서 StreamDQ 앞단에 사용을 목적으로 한다.


	- 사용법.

	CAyaStreamSQ	clStreamQ;
	CAyaStreamSQ	clStreamQ(1024);




----------------------------------------------------------------*/
#ifndef __AYA_STREAM_SINGLE_QUEUE__
#define __AYA_STREAM_SINGLE_QUEUE__

class CAyaStreamSQ
{
public:

	/*---------------------------------------------------------------
	AyaStreamSQ Enum.

	----------------------------------------------------------------*/
	enum e_AYA_STREAM_SQ
	{
		eBUFFER_DEFAULT				= 20960,		// 버퍼의 기본 크기.
		eBUFFER_BLANK				= 8			 	// 확실한 구분을 위해 8Byte 의 빈공간.

	};

public:

	/////////////////////////////////////////////////////////////////////////
	// 생성자(임의 크기 지정), 파괴자.
	//
	//
	/////////////////////////////////////////////////////////////////////////
			CAyaStreamSQ(void);
			CAyaStreamSQ(int iBufferSize);

	virtual	~CAyaStreamSQ(void);

	/////////////////////////////////////////////////////////////////////////
	// 버퍼 생성 & 큐의 초기화.
	//
	// Parameters: (int)버퍼용량.
	// Return: 없음.
	/////////////////////////////////////////////////////////////////////////
	void	Initial(int iBufferSize);

	/////////////////////////////////////////////////////////////////////////
	// 버퍼 전체의 용량 얻음.
	//
	// Parameters: 없음.
	// Return: (int)버퍼용량.
	/////////////////////////////////////////////////////////////////////////
	int		GetBufferSize(void);
	/////////////////////////////////////////////////////////////////////////
	// 현재 사용중인 용량 얻기.
	//
	// Parameters: 없음.
	// Return: (int)사용중인 용량.
	/////////////////////////////////////////////////////////////////////////
	int		GetUseSize(void);

	/////////////////////////////////////////////////////////////////////////
	// 현재 버퍼에 남은 용량 얻기.
	//
	// Parameters: 없음.
	// Return: (int)남은용량.
	/////////////////////////////////////////////////////////////////////////
	int		GetFreeSize(void);

	/////////////////////////////////////////////////////////////////////////
	// 버퍼 포인터로 외부에서 한방에 읽고, 쓸 수 있는 길이.
	// (끊기지 않은 길이)
	//
	// Parameters: 없음.
	// Return: (int)사용가능 용량.
	/////////////////////////////////////////////////////////////////////////
	int		GetNotBrokenGetSize(void);
	int		GetNotBrokenPutSize(void);


	/////////////////////////////////////////////////////////////////////////
	// WritePos 에 데이타 넣음.
	//
	// Parameters: (char *)데이타 포인터. (int)크기. 
	// Return: (int)넣은 크기.
	/////////////////////////////////////////////////////////////////////////
	int		Put(char *chpData, int iSize);
	/////////////////////////////////////////////////////////////////////////
	// ReadPos 에서 데이타 가져옴. ReadPos 이동.
	//
	// Parameters: (char *)데이타 포인터. (int)크기.
	// Return: (int)가져온 크기.
	/////////////////////////////////////////////////////////////////////////
	int		Get(char *chpDest, int iSize);

	/////////////////////////////////////////////////////////////////////////
	// ReadPos 에서 데이타 읽어옴. ReadPos 고정.
	//
	// Parameters: (char *)데이타 포인터. (int)크기.
	// Return: (int)가져온 크기.
	/////////////////////////////////////////////////////////////////////////
	int		Peek(char *chpDest, int iSize);

	/////////////////////////////////////////////////////////////////////////
	// Index위치에서 데이타 읽어옴. 
	//
	// Parameters: (char *)데이타 포인터. (int)시작인덱스. (int)크기.
	// Return: (int)가져온 크기.
	/////////////////////////////////////////////////////////////////////////
	int		Peek(char *chpDest, int iIndex, int iSize);



	/////////////////////////////////////////////////////////////////////////
	// 원하는 길이만큼 읽기위치 에서 삭제.
	//
	// Parameters: 없음.
	// Return: 없음.
	/////////////////////////////////////////////////////////////////////////
	void	RemoveData(int iSize);

	/////////////////////////////////////////////////////////////////////////
	// Write 의 위치를 이동하는 함수.
	//
	// Parameters: 없음.
	// Return: (int)Write 이동 사이즈
	/////////////////////////////////////////////////////////////////////////
	int		MoveWritePos(int iSize);


	/////////////////////////////////////////////////////////////////////////
	// 버퍼의 모든 데이타 삭제.
	//
	// Parameters: 없음.
	// Return: 없음.
	/////////////////////////////////////////////////////////////////////////
	void	ClearBuffer(void);
	/////////////////////////////////////////////////////////////////////////
	// 버퍼의 포인터 얻음.
	//
	// Parameters: 없음.
	// Return: (char *) 버퍼 포인터.
	/////////////////////////////////////////////////////////////////////////
	char	*GetBufferPtr(void);

	/////////////////////////////////////////////////////////////////////////
	// 버퍼의 ReadPos 포인터 얻음.
	//
	// Parameters: 없음.
	// Return: (char *) 버퍼 포인터.
	/////////////////////////////////////////////////////////////////////////
	char	*GetReadBufferPtr(void);
	/////////////////////////////////////////////////////////////////////////
	// 버퍼의 WritePos 포인터 얻음.
	//
	// Parameters: 없음.
	// Return: (char *) 버퍼 포인터.
	/////////////////////////////////////////////////////////////////////////
	char	*GetWriteBufferPtr(void);



	/////////////////////////////////////////////////////////////////////////
	// Lock, Unlock.
	// 스레드 환경을 위해 CriticalSection 으로 Lock, Unlock 처리.
	// 
	// Parameters: 없음.
	// Return: 없음.
	/////////////////////////////////////////////////////////////////////////
	void	Lock(void);
	void	Unlock(void);





protected:

	//------------------------------------------------------------
	// 버퍼 포인터.
	//------------------------------------------------------------
	char				*m_chpBuffer;
	//------------------------------------------------------------
	// 버퍼 사이즈.
	//------------------------------------------------------------
	int					m_iBufferSize;

	//------------------------------------------------------------
	// 버퍼의 읽기 위치, 쓰기 위치.
	//------------------------------------------------------------
	int					m_iReadPos;
	int					m_iWritePos;

	//------------------------------------------------------------
	// 스레드 환경을 위해 크리티걸 섹션 사용.
	//------------------------------------------------------------
	CRITICAL_SECTION	m_csQueue;
};


#endif