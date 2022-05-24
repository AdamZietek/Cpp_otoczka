#pragma once
#include "wx/wx.h"
#include <fstream>
#include <wx/graphics.h>
#include <wx/combobox.h>
#include <wx/valnum.h>
#include <wx/wfstream.h>
#include <wx/txtstrm.h>
#include <ctime>
#include <cstdlib>
#include "cCanvas.h"

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

public:
	//frame
	wxBoxSizer* fs_1 = nullptr;

	//panels
	wxBoxSizer* ps_2 = nullptr;
	wxPanel* ps_3 = nullptr;
	wxBoxSizer* ps_4 = nullptr;
	//panel_1
	wxBoxSizer* p1s_5 = nullptr;
	wxPanel* p1s_6 = nullptr;
	wxBoxSizer* p1s_7 = nullptr;
	//----------//
	wxButton* w_pol = nullptr;
	wxButton* w_pkt = nullptr;
	wxButton* u_alg = nullptr;
	//wxChoice* kol_pol = nullptr;
	//wxChoice* kol_pkt = nullptr;

	//panel_2
	wxBoxSizer* p2s_5 = nullptr;
	wxPanel* p2s_6 = nullptr;
	wxGridSizer* p2s_7 = nullptr;
	//----------//
	wxStaticText* kol_pkt = nullptr;
	wxChoice* kol_pkt_ch = nullptr;
	wxStaticText* kol_linii = nullptr;
	wxChoice* kol_linii_ch = nullptr;
	wxStaticText* gr_linii = nullptr;
	wxChoice* gr_linii_ch = nullptr;
	wxStaticText* styl_linii = nullptr;
	wxChoice* styl_linii_ch = nullptr;
	//panel_3
	wxBoxSizer* p3s_5 = nullptr;
	wxPanel* p3s_6 = nullptr;
	wxBoxSizer* p3s_7 = nullptr;
	//----------//
	wxButton* r_pkt = nullptr;
	wxButton* zap_pkt = nullptr;
	wxButton* zamknij = nullptr;//235

	//window
	wxBoxSizer* ws_2 = nullptr;
	wxPanel* ws_3 = nullptr;
	wxBoxSizer* ws_4 = nullptr;
	wxBoxSizer* ws_5 = nullptr;
	wxWindow* ws_6 = nullptr;
	wxBoxSizer* ws_7 = nullptr;

	//drawing
	wxPanel* bdp_panel = nullptr;
	wxStatusBar* m_StatusBar = nullptr;
	wxSlider* m_ZoomSlider = nullptr;
	wxClientDC* bdp_client = nullptr;


	wxDouble* w = nullptr;
	wxDouble* h = nullptr;
	wxString color[4] = { "Czerwony", "Zielony", "Niebieski", "Czarny" };
	wxString weight[4] = { "1", "2", "3", "4" };
	wxString style[4] = { "Linia ci¹g³a", "Linia przerywana 1", "Linia przerywana 2", "Kropki" };
	wxPen* pen = nullptr;
	wxBrush* brush = nullptr;

	//data
	wxDouble m_value = 0;
	std::vector<wxPoint2DDouble> points;
	std::vector<wxPoint2DDouble> points2;
	std::vector<wxPoint2DDouble> points3;
	std::vector<wxPoint2DDouble> sort;
	std::vector<wxPoint2DDouble> otoczka;
public:
	//events
	wxDECLARE_EVENT_TABLE();
	void pick_points(wxCommandEvent& evt_1);
	void file_points(wxCommandEvent& evt_2);
	void alg(wxCommandEvent& evt_3);
	void color_pts(wxCommandEvent& evt_4);
	void color_line(wxCommandEvent& evt_5);
	void thicc_line(wxCommandEvent& evt_6);
	void style_line(wxCommandEvent& evt_7);
	void save_points(wxCommandEvent& evt_8);
	void close(wxCommandEvent& evt_9);
};

