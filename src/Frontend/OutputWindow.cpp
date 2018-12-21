/*

Decoda
Copyright (C) 2007-2013 Unknown Worlds Entertainment, Inc. 

This file is part of Decoda.

Decoda is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Decoda is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Decoda.  If not, see <http://www.gnu.org/licenses/>.

*/

#include "OutputWindow.h"
#include "MainFrame.h"
#include "FontColorSettings.h"

DEFINE_EVENT_TYPE(wxEVT_OUTPUT_KEY_DOWN)

BEGIN_EVENT_TABLE(OutputTextbox, wxTextCtrl)
    EVT_LEFT_DCLICK(        OutputTextbox::OnDoubleClick)
    EVT_KEY_DOWN(           OutputTextbox::OnKeyDown)
END_EVENT_TABLE()


OutputWindow::OutputWindow(MainFrame* mainFrame, wxWindowID winid)
    : wxPanel(mainFrame)
{
    m_mainFrame = mainFrame;
    m_textbox = new OutputTextbox(this, mainFrame, winid);

    wxBoxSizer* bSizer = new wxBoxSizer(wxVERTICAL);

    bSizer->Add(m_textbox, 1, wxEXPAND);
    SetSizer(bSizer);
    Layout();
}

void OutputWindow::OutputMessage(const wxString& message)
{
    m_textbox->SharedOutput(message, m_messageAttr);
}

void OutputWindow::OutputWarning(const wxString& message)
{
    m_textbox->SharedOutput(message, m_warningAttr);
}

void OutputWindow::OutputError(const wxString& message)
{
    m_textbox->SharedOutput(message, m_errorAttr);
}


void OutputWindow::Clear()
{
    m_textbox->Clear();
}

wxString OutputWindow::GetLineText(int row)
{
    return m_textbox->GetLineText(row);
}

int OutputWindow::GetCurrentLine() const
{

    long pos = m_textbox->GetInsertionPoint();

    long x, y;
    m_textbox->PositionToXY(pos, &x, &y);

    return y;

}

void OutputWindow::SetFontColorSettings(const FontColorSettings& settings)
{

    // Since we don't save enough information to reapply styles to the existing text,
    // clear everything. This is lame, but changing font settings isn't something that
    // happens often enough for it to really make much difference.
    m_textbox->Clear();

    m_textbox->SetBackgroundColour(settings.GetColors(FontColorSettings::DisplayItem_Window).backColor);

    m_messageAttr.SetTextColour(settings.GetColors(FontColorSettings::DisplayItem_Window).foreColor);
    m_messageAttr.SetBackgroundColour(settings.GetColors(FontColorSettings::DisplayItem_Window).backColor);
    m_messageAttr.SetFont(settings.GetFont(FontColorSettings::DisplayItem_Window));

    m_warningAttr.SetTextColour(settings.GetColors(FontColorSettings::DisplayItem_Warning).foreColor);
    m_warningAttr.SetBackgroundColour(settings.GetColors(FontColorSettings::DisplayItem_Window).backColor);
    m_warningAttr.SetFont(settings.GetFont(FontColorSettings::DisplayItem_Warning));

    m_errorAttr.SetTextColour(settings.GetColors(FontColorSettings::DisplayItem_Error).foreColor);
    m_errorAttr.SetBackgroundColour(settings.GetColors(FontColorSettings::DisplayItem_Window).backColor);
    m_errorAttr.SetFont(settings.GetFont(FontColorSettings::DisplayItem_Error));

}

OutputTextbox::OutputTextbox(OutputWindow* parent, MainFrame*  mainFrame, wxWindowID winid)
    : wxTextCtrl(parent, winid, _(""), wxDefaultPosition, wxSize(200, 150), wxTE_MULTILINE | wxTE_READONLY | wxTE_DONTWRAP | wxTE_RICH)
{
    m_mainFrame = mainFrame;
}

void OutputTextbox::OnDoubleClick(wxMouseEvent& event)
{
    
    wxTextCoord col, row;
    HitTest(event.GetPosition(), &col, &row);

    wxString line = GetLineText(row);
    m_mainFrame->GotoError(line);

}

void OutputTextbox::OnKeyDown(wxKeyEvent& event)
{

    // Send the key event to our parent.

    wxKeyEvent event2(event);
    event2.SetEventType(wxEVT_OUTPUT_KEY_DOWN);

    if (GetParent() != NULL)
    {

        GetParent()->GetEventHandler()->ProcessEvent(event2);

        if (event2.GetSkipped())
        {
            event.Skip();
        }
    
    }

}

void OutputTextbox::SharedOutput(const wxString& message, const wxTextAttr& textAttr)
{
    int beforeAppendPosition = GetInsertionPoint();
    int beforeAppendLastPosition = GetLastPosition();
    Freeze();
    SetDefaultStyle(textAttr);
    AppendText(message + "\n");
    Thaw();
    SetInsertionPoint(beforeAppendPosition);
    if (beforeAppendPosition == beforeAppendLastPosition)
    {
        SetInsertionPoint(GetLastPosition());
        ShowPosition(GetLastPosition());
        ScrollLines(-1);
    }
}