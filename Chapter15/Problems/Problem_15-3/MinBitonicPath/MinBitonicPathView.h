#pragma once


// CMinBitonicPathView

class CMinBitonicPathView : public CWnd
{
	DECLARE_DYNAMIC(CMinBitonicPathView)

public:
	CMinBitonicPathView();
	virtual ~CMinBitonicPathView();

protected:
	DECLARE_MESSAGE_MAP()

private:
	void Paint(const CPoint sortedPoint[], const int pointChain[], int n);

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPaint();
};


