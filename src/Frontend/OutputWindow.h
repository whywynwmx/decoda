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

#ifndef OUTPUT_WINDOW_H
#define OUTPUT_WINDOW_H

#include <wx/wx.h>

//
// Forward declarations.
//

class MainFrame;
class FontColorSettings;
class OutputTextbox;

class OutputWindow : public wxPanel {

public:

    /**
     * Constructor.
     */
    OutputWindow(MainFrame* mainFrame, wxWindowID winid);

    /**
     * Sets the font and color settings used in the output window.
     */
    void SetFontColorSettings(const FontColorSettings& settings);

    /**
     * Adds a message to the end of the log.
     */
    void OutputMessage(const wxString& message);

    /**
     * Adds a warning message to the end of the log.
     */
    void OutputWarning(const wxString& message);

    /**
     * Adds an error message to the end of the log.
     */
    void OutputError(const wxString& message);

    /**
     * Returns the line that the cursor is positioned on.
     */
    int GetCurrentLine() const;

    void Clear();
    
    wxString GetLineText(int row);

private:

    /**
     * Outputs text using the passed in text attribute. This method will only
     * cause the output window to scroll down if the insertion point is already
     * at the bottom of the text.
     */
    void SharedOutput(const wxString& message, const wxTextAttr& textAttr);

    MainFrame*     m_mainFrame;
    OutputTextbox* m_textbox;

    wxTextAttr  m_messageAttr;
    wxTextAttr  m_warningAttr;
    wxTextAttr  m_errorAttr;
};

/**
 *
 */
class OutputTextbox : public wxTextCtrl
{

public:
    /**
     * Constructor.
     */
    OutputTextbox(OutputWindow* parent, MainFrame*  m_mainFrame, wxWindowID winid);
    
    /**
     * Sets the font and color settings used in the output window.
     */
    void SetFontColorSettings(const FontColorSettings& settings);

    /**
     * Called when the user double clicks in the window.
     */
    void OnDoubleClick(wxMouseEvent& event);

    /**
     * Called when the user presses a key in the window.
     */
    void OnKeyDown(wxKeyEvent& event);

    /**
     * Adds a message to the end of the log.
     */
    void OutputMessage(const wxString& message);

    /**
     * Adds a warning message to the end of the log.
     */
    void OutputWarning(const wxString& message);

    /**
     * Adds an error message to the end of the log.
     */
    void OutputError(const wxString& message);

    /**
     * Returns the line that the cursor is positioned on.
     */
    int GetCurrentLine() const;

    DECLARE_EVENT_TABLE()

private:
    friend OutputWindow;
    /**
     * Outputs text using the passed in text attribute. This method will only
     * cause the output window to scroll down if the insertion point is already
     * at the bottom of the text.
     */
    void SharedOutput(const wxString& message, const wxTextAttr& textAttr);

    MainFrame*  m_mainFrame;

};

DECLARE_LOCAL_EVENT_TYPE(wxEVT_OUTPUT_KEY_DOWN, -1)

typedef void (wxEvtHandler::*wxOutputKeyDownEventFunction)(wxKeyEvent&);

#define EVT_OUTPUT_KEY_DOWN(id, fn) \
    DECLARE_EVENT_TABLE_ENTRY( wxEVT_OUTPUT_KEY_DOWN, id, -1, \
    (wxObjectEventFunction) (wxEventFunction) (wxCommandEventFunction) (wxNotifyEventFunction) \
    wxStaticCastEvent( wxOutputKeyDownEventFunction, & fn ), (wxObject *) NULL ),

#endif
