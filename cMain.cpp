#pragma once
#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	EVT_BUTTON(10001, pick_points)
	EVT_BUTTON(10002, file_points)
	EVT_BUTTON(10003, alg)
	EVT_CHOICE(10004, color_pts)
	EVT_CHOICE(10005, color_line)
	EVT_CHOICE(10006, thicc_line)
	EVT_CHOICE(10007, style_line)
	EVT_BUTTON(10008, save_points)
	EVT_BUTTON(10009, close)
wxEND_EVENT_TABLE()

//look
const wxFont _12()
{
	return wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
}
const wxFont _9()
{
	return wxFont(9, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
}
void theme(wxFrame* t, wxPanel* pnl1, wxPanel* pnl2, wxPanel* st, wxPanel* nd, wxPanel* rd, wxWindow* wnd)
{
	t->SetBackgroundColour(wxColor(*wxBLACK));
	pnl1->SetBackgroundColour(wxColor(108, 122, 137));
	pnl2->SetBackgroundColour(wxColor(108, 122, 137));
	st->SetBackgroundColour(wxColor(224, 224, 224));
	nd->SetBackgroundColour(wxColor(224, 224, 224));
	rd->SetBackgroundColour(wxColor(224, 224, 224));
	wnd->SetBackgroundColour(wxColor(224, 224, 224));
	st->SetFont(_9());
	nd->SetFont(_9());
	rd->SetFont(_9());
};
void but_to_box(wxBoxSizer* box, wxButton* but)
{
	box->Add(but, 1, wxEXPAND | wxALL, 5);
};
void pnl_to_sz(wxBoxSizer* bs, wxPanel* p)
{
	bs->Add(p, 1, wxEXPAND | wxALL, 5);
}

//coords math
wxDouble min_x(const std::vector<wxPoint2DDouble>& i)
{
	wxDouble m(0.0);
	if (i.size() != 0)
		m = i[0].m_x;
	for (const auto& c : i)
		if (c.m_x < m)
			m = c.m_x;
	return m;
}
wxDouble max_x(const std::vector<wxPoint2DDouble>& i)
{
	wxDouble m(0.0);
	if (i.size() != 0)
		m = i[0].m_x;
	for (const auto& c : i)
		if (c.m_x > m)
			m = c.m_x;
	return m;
}
wxDouble min_y(const std::vector<wxPoint2DDouble>& i)
{
	wxDouble m(0.0);
	if (i.size() != 0)
		m = i[0].m_y;
	for (const auto& c : i)
		if (c.m_y < m)
			m = c.m_y;
	return m;
}
wxDouble max_y(const std::vector<wxPoint2DDouble>& i)
{
	wxDouble m(0.0);
	if (i.size() != 0)
		m = i[0].m_y;
	for (const auto& c : i)
		if (c.m_y > m)
			m = c.m_y;
	return m;
}
wxDouble s(const std::vector<wxPoint2DDouble>& i)
{
	const wxDouble ma_x = max_x(i), ma_y = max_y(i), mi_x = min_x(i), mi_y = min_y(i);

	wxDouble sx(ma_x / (ma_y - mi_y));
	wxDouble sy(ma_y / (ma_x - mi_x));
	wxDouble s(sx);

	if (sy > sx)
		s = sy;

	return s;
}

//input
std::vector<wxPoint2DDouble> randy() //20 random points
{
	srand(time(NULL));

	wxDouble x = 0, y = 0;
	std::vector<wxPoint2DDouble> re;

	while (re.size() < 20)
	{
		x = rand() % 301;
		y = rand() % 301;

		x += 50;
		y += 50;

		re.push_back(wxPoint2DDouble(x, y));
	}
	return re;
}
std::vector<wxPoint2DDouble> u1(wxFileInputStream& str)
{
	int num = 0;
	wxDouble x = 0, y = 0;
	std::vector<wxPoint2DDouble> pts;

	while (str.CanRead())
	{
		wxTextInputStream store(str);
		store >> num >> x >> y;
		pts.push_back(wxPoint2DDouble(x, y));
	}

	return pts;
}
std::vector<wxPoint2DDouble> u2(std::vector<wxPoint2DDouble> i)
{
	const wxDouble mi_y = min_y(i);
	const wxDouble mi_x = min_x(i);
	const wxDouble max_ = max_y(i);
	const wxDouble s_ = s(i);

	std::vector<wxPoint2DDouble> u2;
	for (decltype(i.size()) j = 0; j < i.size(); ++j)
		u2.push_back(wxPoint2DDouble((s_ * (i[j].m_y - mi_y)), (max_ - s_ * (i[j].m_x - mi_x))));
	return u2;
}
//move to the centre of window
std::vector<wxPoint2DDouble> transform(std::vector<wxPoint2DDouble> i, const wxDouble& w_width, const wxDouble& w_height)
{
	std::vector<wxPoint2DDouble> i_t;
	const wxDouble ma_x = max_x(i), ma_y = max_y(i), mi_x = min_x(i), mi_y = min_y(i);
	const wxDouble width = w_width / 2 - (ma_x + mi_x) / 2;
	const wxDouble height = (w_height - 34) / 2 - (ma_y + mi_y) / 2;
	for (const auto& c : i)
		i_t.push_back(wxPoint2DDouble(c.m_x + width, c.m_y + height));
	return i_t;
}

wxGraphicsContext* draw(wxClientDC& d, const wxPen& pen, const wxBrush& brush, std::vector<wxPoint2DDouble> p)
{
	d.Clear();
	wxGraphicsContext* gc1 = wxGraphicsContext::Create(d);
	if (gc1)
	{
		//gc1->SetPen(pen);

		gc1->SetFont(_12(), wxColor(*wxBLACK));
		gc1->SetBrush(brush);

		gc1->DrawText('1', (p)[0].m_x + 10, (p)[0].m_y);
		gc1->DrawRectangle((p)[0].m_x - 3.5, (p)[0].m_y - 3.5, 7.0, 7.0);
		for (decltype(p.size()) i = 1; i < p.size(); ++i)
		{
			gc1->DrawText(wxString::Format(wxT("%i"), i + 1), (p)[i].m_x + 10.0, (p)[i].m_y - 20.0);
			gc1->DrawRectangle((p)[i].m_x - 3.5, (p)[i].m_y - 3.5, 7.0, 7.0);
		}
			
		delete gc1;
	}

	return gc1;
}
wxGraphicsContext* draw_alg(wxClientDC& d, const wxPen& pen, const wxBrush& brush, std::vector<wxPoint2DDouble> p, std::vector<wxPoint2DDouble> l)
{
	d.Clear();
	std::vector<wxPoint2DDouble> last_line{ l[l.size() - 1], l[0] };
	wxGraphicsContext* gc1 = wxGraphicsContext::Create(d);
	if (gc1)
	{
		gc1->SetFont(_12(), wxColor(*wxBLACK));
		gc1->SetBrush(brush);

		gc1->DrawText('1', (p)[0].m_x + 10, (p)[0].m_y);
		gc1->DrawRectangle((p)[0].m_x - 3.5, (p)[0].m_y - 3.5, 7.0, 7.0);
		for (decltype(p.size()) i = 1; i < p.size(); ++i)
		{
			gc1->DrawText(wxString::Format(wxT("%i"), i + 1), (p)[i].m_x + 10.0, (p)[i].m_y - 20.0);
			gc1->DrawRectangle((p)[i].m_x - 3.5, (p)[i].m_y - 3.5, 7.0, 7.0);
		}
		gc1->SetBrush(wxNullBrush);
		gc1->SetPen(pen);
		gc1->DrawLines(l.size(), &(l)[0]);
		gc1->DrawLines(last_line.size(), &last_line[0]);

		delete gc1;
	}

	return gc1;
}

//sorting vector
int partition(std::vector<wxPoint2DDouble>& values, int left, int right, const wxPoint2DDouble d)
{
	int pivotIndex = left + (right - left) / 2;
	wxPoint2DDouble pivotValue = values[pivotIndex];
	int i = left, j = right;
	wxPoint2DDouble temp;
	while (i <= j) {
		while (((d.m_x - values[i].m_x) / sqrt(pow(values[i].m_y - d.m_y, 2) + pow(values[i].m_x - d.m_x, 2))) < ((d.m_x - pivotValue.m_x) / sqrt(pow(pivotValue.m_y - d.m_y, 2) + pow(pivotValue.m_x - d.m_x, 2))))
		{
			i++;
		}
		while (((d.m_x - values[j].m_x) / sqrt(pow(values[j].m_y - d.m_y, 2) + pow(values[j].m_x - d.m_x, 2))) > ((d.m_x - pivotValue.m_x) / sqrt(pow(pivotValue.m_y - d.m_y, 2) + pow(pivotValue.m_x - d.m_x, 2)))) 
		{
			j--;
		}
		if (i <= j) {
			temp = values[i];
			values[i] = values[j];
			values[j] = temp;
			i++;
			j--;
		}
	}
	return i;
}
void quicksort(std::vector<wxPoint2DDouble>& values, int left, int right, const wxPoint2DDouble d) {
	if (left < right) {
		int pivotIndex = partition(values, left, right, d);
		quicksort(values, left, pivotIndex - 1, d);
		quicksort(values, pivotIndex, right, d);
	}
}
int orientation(wxPoint2DDouble p, wxPoint2DDouble q, wxPoint2DDouble r)
{
	int val = (q.m_y - p.m_y) * (r.m_x - q.m_x) -
		(q.m_x - p.m_x) * (r.m_y - q.m_y);

	if (val == 0) return 0;  // colinear 
	return (val > 0) ? 2 : 1; // clock or counterclock wise 
}
std::vector<wxPoint2DDouble> graham(std::vector<wxPoint2DDouble> points, int n)
{
	wxPoint2DDouble p0 = points[0];

	int m = 1;
	for (int i = 1; i < n; i++)
	{
		while (i < n - 1 && orientation(p0, points[i],
			points[i + 1]) == 0)
			i++;

		points[m] = points[i];
		m++; 
	}

	std::vector<wxPoint2DDouble> S;  //wkladam pierwsze trzy
	S.push_back(points[0]);
	S.push_back(points[1]);
	S.push_back(points[2]);

	for (int i = 3; i < m; i++)		 //sprawdzam pozostale
	{
		while (orientation(S[S.size() - 2], S[S.size() - 1], points[i]) != 2)
			S.pop_back();
		S.push_back(points[i]);
	}

	return S;
}

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Geometria Obliczeniowa 4", wxPoint(5, 5), wxSize(1400, 800))
{
	wxFloatingPointValidator<double> val(3, &m_value, wxNUM_VAL_ZERO_AS_BLANK);
	//frame [shell 0]
	//defining top_sizer [shell 1] 
	fs_1 = new wxBoxSizer(wxHORIZONTAL);

	//defining outer sizers [shell 2]
	ps_2 = new wxBoxSizer(wxVERTICAL);
	ws_2 = new wxBoxSizer(wxVERTICAL);

	//defining main panel and window [shell 3]
	ps_3 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(390, 790));
	ws_3 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(1190, 790));

	//defining inner sizer [shell 4]
	ps_4 = new wxBoxSizer(wxVERTICAL);
	ws_4 = new wxBoxSizer(wxVERTICAL);

	//defining outer sizer [shell 5]
	p1s_5 = new wxBoxSizer(wxVERTICAL);
	p2s_5 = new wxBoxSizer(wxVERTICAL);
	p3s_5 = new wxBoxSizer(wxVERTICAL);
	ws_5 = new wxBoxSizer(wxVERTICAL);

	//defining minor panels [shell 6]
	p1s_6 = new wxPanel(ps_3, wxID_ANY, wxDefaultPosition, wxSize(380, 240));
	p2s_6 = new wxPanel(ps_3, wxID_ANY, wxDefaultPosition, wxSize(380, 340));
	p3s_6 = new wxPanel(ps_3, wxID_ANY, wxDefaultPosition, wxSize(380, 200));
	ws_6 = new wxWindow(ws_3, wxID_ANY, wxDefaultPosition, wxSize(980, 780));

	//defining inner sizer [shell 7]
	p1s_7 = new wxBoxSizer(wxVERTICAL);
	p2s_7 = new wxGridSizer(4, 2, 0, 0);
	p3s_7 = new wxBoxSizer(wxVERTICAL);
	ws_7 = new wxBoxSizer(wxVERTICAL);

	//THEME AND COLOR
	theme(this, ps_3, ws_3, p1s_6, p2s_6, p3s_6, ws_6);

	//defining panel 1 [shell 6,7]
	w_pol = new wxButton(p1s_6, 10001, "Losuj punkty");
	w_pkt = new wxButton(p1s_6, 10002, "Wczytaj punkty");
	u_alg = new wxButton(p1s_6, 10003, "Wyznacz otoczkê");
	u_alg->SetBackgroundColour(wxColor(255, 51, 51));
	u_alg->Disable();

	//defining panel 2 [shell 6,7]
	kol_pkt = new wxStaticText(p2s_6, wxID_ANY, "Kolor punktów: ");
	kol_pkt_ch = new wxChoice(p2s_6, 10004, wxDefaultPosition, wxDefaultSize, 4, color, wxCB_SORT | wxTE_CENTRE);
	kol_linii = new wxStaticText(p2s_6, wxID_ANY, "Kolor lini: ");
	kol_linii_ch = new wxChoice(p2s_6, 10005, wxDefaultPosition, wxDefaultSize, 4, color, wxCB_SORT | wxTE_CENTRE);
	gr_linii = new wxStaticText(p2s_6, wxID_ANY, "Gruboœæ linii: ");
	gr_linii_ch = new wxChoice(p2s_6, 10006, wxDefaultPosition, wxDefaultSize, 4, weight, wxCB_SORT | wxTE_CENTRE);
	styl_linii = new wxStaticText(p2s_6, wxID_ANY, "Styl linii: ");
	styl_linii_ch = new wxChoice(p2s_6, 10007, wxDefaultPosition, wxDefaultSize, 4, style, wxCB_SORT | wxTE_CENTRE);
	kol_linii_ch->Disable();
	gr_linii_ch->Disable();
	styl_linii_ch->Disable();
	//defining panel 3 [shell 6,7]
	zap_pkt = new wxButton(p3s_6, 10008, "Zapisz punkty otoczki do pliku .txt");
	zamknij = new wxButton(p3s_6, 10009, "Zamknij");

	//defining thigs inside WINDOW [shell 6,7]
	bdp_panel = new wxPanel(ws_6);

	//----------//

	//controls ADD to sizer panel 1 [shell ->7]
	but_to_box(p1s_7, w_pol);
	but_to_box(p1s_7, w_pkt);
	but_to_box(p1s_7, u_alg);

	//controls ADD to sizer panel 2 [shell ->7]
	p2s_7->Add(kol_pkt, 1, wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxALL, 15);
	p2s_7->Add(kol_pkt_ch, 1, wxEXPAND | wxALL, 15);
	p2s_7->Add(kol_linii, 1, wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxALL, 15);
	p2s_7->Add(kol_linii_ch, 1, wxEXPAND | wxALL, 15);
	p2s_7->Add(gr_linii, 1, wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxALL, 15);
	p2s_7->Add(gr_linii_ch, 1, wxEXPAND | wxALL, 15);
	p2s_7->Add(styl_linii, 1, wxALIGN_CENTER_VERTICAL | wxALIGN_LEFT | wxALL, 15);
	p2s_7->Add(styl_linii_ch, 1, wxEXPAND | wxALL, 15);

	//controls ADD to sizer panel 3 [shell ->7]
	but_to_box(p3s_7, zap_pkt);
	but_to_box(p3s_7, zamknij);

	//BDP ADD to sizer [shell ->7]
	ws_7->Add(bdp_panel, 1, wxEXPAND | wxALL, 0);

	//inner sizer SETSIZER panel [shell 7->6]
	p1s_6->SetSizer(p1s_7);
	p2s_6->SetSizer(p2s_7);
	p3s_6->SetSizer(p3s_7);
	ws_6->SetSizer(ws_7);

	//panel ADD to outer sizer [shell 6->5]
	p1s_5->Add(p1s_6, 1, wxEXPAND | wxALL, 5);
	p2s_5->Add(p2s_6, 1, wxEXPAND | wxALL, 5);
	p3s_5->Add(p3s_6, 1, wxEXPAND | wxALL, 5);
	ws_5->Add(ws_6, 1, wxEXPAND | wxALL, 5);

	//outer sizer ADD to inner sizer [shell 5->4]
	ps_4->Add(p1s_5);
	ps_4->Add(p2s_5);
	ps_4->Add(p3s_5);
	ws_4->Add(ws_5);

	//inner sizer SETSIZER panel [shell 4->3]
	ps_3->SetSizer(ps_4);
	ws_3->SetSizer(ws_4);

	//panel ADD to outer sizer [shell 3->2]
	pnl_to_sz(ps_2, ps_3);
	pnl_to_sz(ws_2, ws_3);

	//outer sizer ADD to inner sizer [shell 2->1]
	fs_1->Add(ps_2);
	fs_1->Add(ws_2);

	//wxFrame SETSIZER top_sizer [shell 1->0]
	SetSizer(fs_1);

	//drawing
	bdp_client = new wxClientDC(bdp_panel);
	pen = new wxPen(*wxBLACK_PEN);
	brush = new wxBrush(*wxBLACK_BRUSH);
	w = new wxDouble((ws_6->GetSize()).GetWidth());
	h = new wxDouble((ws_6->GetSize()).GetHeight());
	//data
}

cMain::~cMain()
{
}

void cMain::pick_points(wxCommandEvent& evt_1)
{
	points = randy();
	points2 = u2(points);
	points3 = transform(points2, *w, *h);
	otoczka = {};

	draw(*bdp_client, *pen, *brush, points3);
	u_alg->Enable();
	kol_linii_ch->Disable();
	gr_linii_ch->Disable();
	styl_linii_ch->Disable();
}

void cMain::file_points(wxCommandEvent& evt_2)
{
	kol_linii_ch->Disable();
	gr_linii_ch->Disable();
	styl_linii_ch->Disable();
	wxFileDialog polygon(this, _("Open file containing polygon"), "", "", "*.txt|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (polygon.ShowModal() == wxID_CANCEL)
		return;

	wxFileInputStream input_stream(polygon.GetPath());
	if (!input_stream.IsOk())
	{
		wxLogError("Cannot open file '%s'.", polygon.GetPath());
		return;
	}
	points = u1(input_stream);
	points2 = u2(points);
	points3 = transform(points2, *w, *h);

	draw(*bdp_client, *pen, *brush, points3);
	u_alg->Enable();
}

void cMain::alg(wxCommandEvent& evt_3)
{
	int ix = 0;														//indeks elementu, ktory ma najmniejsza wartosc x i jesli kilka najmniejszych to y
	wxPoint2DDouble low = points3[0];								//element, ktory ma najmniejsza wartosc x i jesli kilka najmniejszych to y
	for (decltype(points3.size()) i = 1; i < points3.size(); ++i)
	{
		if (points3[i].m_y > low.m_y)
		{
			ix = i;
			low = points3[i];
		}
		else if (points3[i].m_y == low.m_y)
			if (points3[i].m_x < low.m_x)
			{
				ix = i;
				low = points3[i];
			}
	}
	sort = points3;													//vector, na ktorym dokonam pierwszego swapa, poszukiwany wyzej element dostaje index = 0
	wxPoint2DDouble zero = points3[0];								//ta zmienna przechowje oryginalna wartosc z indexu = 0
	sort[0] = low;													//najmniejszy pkt w index = 0
	sort[ix] = zero;												//wczesniejsza wartosc z index = 0 w index nalezacym wczesniej do low

	quicksort(sort, 1, sort.size() - 1, low);
	otoczka = graham(sort, sort.size());

	draw_alg(*bdp_client, *pen, *brush, sort, otoczka);
	kol_linii_ch->Enable();
	gr_linii_ch->Enable();
	styl_linii_ch->Enable();
}

void cMain::color_pts(wxCommandEvent& evt_4)
{
	wxString chosen(evt_4.GetString());
	if (chosen == "Czarny")
		*brush = *wxBLACK_BRUSH;
	if (chosen == "Niebieski")
		*brush = *wxBLUE_BRUSH;
	if (chosen == "Zielony")
		*brush = *wxGREEN_BRUSH;
	if (chosen == "Czerwony")
		*brush = *wxRED_BRUSH;

	(otoczka.size() == 0) ? draw(*bdp_client, *pen, *brush, points3) : draw_alg(*bdp_client, *pen, *brush, sort, otoczka);
}

void cMain::color_line(wxCommandEvent& evt_5)
{
	wxString chosen(evt_5.GetString());
	int wid = pen->GetWidth();
	const wxPenStyle styl = pen->GetStyle();
	if (chosen == "Czarny")
		*pen = wxPen(*wxBLACK, wid, styl);
	if (chosen == "Niebieski")
		*pen = wxPen(*wxBLUE, wid, styl);
	if (chosen == "Zielony")
		*pen = wxPen(*wxGREEN, wid, styl);
	if (chosen == "Czerwony")
		*pen = wxPen(*wxRED, wid, styl);

	draw_alg(*bdp_client, *pen, *brush, sort, otoczka);
}

void cMain::thicc_line(wxCommandEvent& evt_6)
{
	wxString chosen(evt_6.GetString());
	const wxColour col = pen->GetColour();
	const wxPenStyle styl = pen->GetStyle();
	if (chosen == "1")
		*pen = wxPen(col, 1, styl);
	if (chosen == "2")
		*pen = wxPen(col, 2, styl);
	if (chosen == "3")
		*pen = wxPen(col, 3, styl);
	if (chosen == "4")
		*pen = wxPen(col, 4, styl);

	draw_alg(*bdp_client, *pen, *brush, sort, otoczka);
}

void cMain::style_line(wxCommandEvent& evt_7)
{
	wxString chosen(evt_7.GetString());
	const wxColour col = pen->GetColour();
	int wid = pen->GetWidth();
	if (chosen == "Linia ci¹g³a")
		*pen = wxPen(col, wid, wxPENSTYLE_SOLID);
	if (chosen == "Linia przerywana 1")
		*pen = wxPen(col, wid, wxPENSTYLE_SHORT_DASH);
	if (chosen == "Linia przerywana 2")
		*pen = wxPen(col, wid, wxPENSTYLE_DOT_DASH);
	if (chosen == "Kropki")
		*pen = wxPen(col, wid, wxPENSTYLE_DOT);

	draw_alg(*bdp_client, *pen, *brush, sort, otoczka);
}

void cMain::save_points(wxCommandEvent& evt_8)
{
	wxFileDialog otp(this, _("Choose file to write points into"), "", "", "*.txt|*.txt", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (otp.ShowModal() == wxID_CANCEL)
		return;

	wxFileOutputStream output_stream(otp.GetPath());
	if (!output_stream.IsOk())
	{
		wxLogError("Cannot open file '%s'.", otp.GetPath());
		return;
	}

	wxTextOutputStream cout(output_stream);
	cout.Flush();
	for (const auto& c : otoczka)
		cout << wxString::Format(wxT("%f"), c.m_x) << " " << wxString::Format(wxT("%f"), c.m_y) << '\n';
	cout << wxString::Format(wxT("%f"), otoczka[0].m_x) << " " << wxString::Format(wxT("%f"), otoczka[0].m_y) << '\n';
}


void cMain::close(wxCommandEvent& evt_9)
{
	Close();
	evt_9.Skip();
}
