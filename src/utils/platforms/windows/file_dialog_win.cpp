// src/filedialog_win.cpp
#include <windows.h>
#include <commdlg.h>
#include <string>

// Function to show file dialog and get selected file path
std::string showFileDialog()
{
    OPENFILENAME ofn; // common dialog box structure
    char szFile[260]; // buffer for file name

    // Initialize OPENFILENAME
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = "All\0*.*\0Text\0*.TXT\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    // Displays the Open dialog box
    if (GetOpenFileName(&ofn) == TRUE)
    {
        return ofn.lpstrFile;
    }

    return "";
}
