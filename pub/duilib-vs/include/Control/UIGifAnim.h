#ifndef GifAnimUI_h__
#define GifAnimUI_h__

#pragma once

namespace DuiLib
{
	class CControl;

#define EVENT_TIEM_ID	100

	class DUILIB_API CGifAnimUI : public CControlUI
	{
	public:
		CGifAnimUI(void);
		~CGifAnimUI(void);

		LPCTSTR	GetClass() const;
		LPVOID	GetInterface(LPCTSTR pstrName);
		LRESULT	DoInit() override;
		LRESULT	DoPaint(HDC hDC, const RECT& rcPaint, CControlUI* pStopControl);
		LRESULT	DoEvent(TEventUI& event);
		void	SetVisible(BOOL bVisible = TRUE );
		void	SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
		void	SetBkImage(LPCTSTR pStrImage);
		LPCTSTR GetBkImage();

		void	SetAutoPlay(BOOL bIsAuto = TRUE );
		BOOL	IsAutoPlay() const;
		void	SetAutoSize(BOOL bIsAuto = TRUE );
		BOOL	IsAutoSize() const;
		LRESULT	PlayGif ();
		LRESULT	PauseGif ();
		LRESULT	StopGif ();

	private:
		LRESULT	InitGifImage();
		LRESULT	DeleteGif();
		LRESULT OnTimer(UINT_PTR idEvent);
		LRESULT	DrawFrame(HDC hDC);		// 绘制GIF每帧
		Gdiplus::Image*	LoadGifFromFile(LPCTSTR pstrGifPath);
		Gdiplus::Image* LoadGifFromMemory( LPVOID pBuf,size_t dwSize );
	private:
		Gdiplus::Image	*m_pGifImage;
		UINT			m_nFrameCount;				// gif图片总帧数
		UINT			m_nFramePosition;			// 当前放到第几帧
		Gdiplus::PropertyItem*	m_pPropertyItem;	// 帧与帧之间间隔时间

		CDuiString		m_sBkImage;
		BOOL			m_bIsAutoPlay;				// 是否自动播放gif
		BOOL			m_bIsAutoSize;				// 是否自动根据图片设置大小
		BOOL			m_bIsPlaying;

	};
}

#endif // GifAnimUI_h__
