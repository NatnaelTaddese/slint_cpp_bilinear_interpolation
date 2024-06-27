// src/filedialog_win.cpp
#include <windows.h>
#include <commdlg.h>
#include <string>
#include <fstream>
#include <shlwapi.h>

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

// Helper function to extract the file name from a path
std::string getFileName(const std::string &filePath)
{
    char fileName[MAX_PATH];
    _splitpath_s(filePath.c_str(), NULL, 0, NULL, 0, fileName, MAX_PATH, NULL, 0);
    return std::string(fileName);
}

// Function to show save file dialog and save the file as PNG
bool saveToFileDialog(const std::string &tempFilePath)
{
    OPENFILENAME ofn; // common dialog box structure
    char szFile[260]; // buffer for file name

    // Extract the file name from the temp file path
    std::string defaultFileName = getFileName(tempFilePath) + ".png";
    strncpy_s(szFile, defaultFileName.c_str(), sizeof(szFile) - 1);

    // Initialize OPENFILENAME
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = "PNG Files\0*.PNG\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.lpstrDefExt = "png"; // Default extension
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;

    // Displays the Save As dialog box
    if (GetSaveFileName(&ofn) == TRUE)
    {
        std::string savePath = ofn.lpstrFile;

        // Copy the contents of the temp file to the selected file path
        std::ifstream src(tempFilePath, std::ios::binary);
        std::ofstream dest(savePath, std::ios::binary);

        dest << src.rdbuf();

        return true;
    }

    return false;
}