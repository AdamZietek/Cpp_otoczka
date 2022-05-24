#pragma once

#include "wx/wx.h"
#include "wx/vscroll.h"

class cCanvas : public wxHVScrolledWindow
{
public:
	cCanvas(wxWindow* parent);
	~cCanvas();

private:
	int m_nPixelSize = 8;

public:
	void SetPixelSize(int n);

private:
	virtual wxCoord OnGetRowHeight(size_t row) const;
	virtual wxCoord OnGetColumnWidth(size_t row) const;

	void OnDraw(wxDC& dc);
	void OnPaint(wxPaintEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

