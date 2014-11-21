/*
 * CiderPress
 * Copyright (C) 2007 by faddenSoft, LLC.  All Rights Reserved.
 * See the file LICENSE for distribution terms.
 */
/*
 * Filename manipulations.  Includes some basic file ops (e.g. tests for
 * file existence) as well.
 */
#ifndef UTIL_PATHNAME_H
#define UTIL_PATHNAME_H

/*
 * Holds a full or partial pathname, manipulating it in various ways.
 *
 * This creates some hefty buffers for _splitpath() to use, so don't use
 * these as storage within other objects.
 *
 * Functions that return CStrings should have their values assigned into
 * CString variables.  Attempting to set a "const char*" to them can cause
 * problems as the CString being returned is in local storage.
 */
class PathName {
public:
    PathName(const WCHAR* pathName = L"", WCHAR fssep = '\\') {
        ASSERT(fssep == '\\');  // not handling other cases yet
        fPathName = pathName;
        fFssep = fssep;
        fSplit = false;
    }
    PathName(const CString& pathName, WCHAR fssep = '\\') {
        ASSERT(fssep == '\\');  // not handling other cases yet
        fPathName = pathName;
        fFssep = fssep;
        fSplit = false;
    }
    ~PathName(void) {}

    /*
     * Name manipulations.
     */
    void SetPathName(const WCHAR* pathName, WCHAR fssep = '\\') {
        ASSERT(fssep == '\\');  // not handling other cases yet
        fPathName = pathName;
        fFssep = fssep;
        fSplit = false;
    }
    void SetPathName(const CString& pathName, WCHAR fssep = '\\') {
        ASSERT(fssep == '\\');  // not handling other cases yet
        fPathName = pathName;
        fFssep = fssep;
        fSplit = false;
    }

    // get the full pathname we have stored
    CString GetPathName(void) const { return fPathName; }

    // create a pathname from a "foreign" OS name
    int ConvertFrom(const char* foreignName, char foreignFssep);

    // return just the filename: "C:\foo\bar.txt" -> "bar.txt"
    CString GetFileName(void);

    // return just the extension: C:\foo\bar.txt --> ".txt"
    CString GetExtension(void);

    // return just the drive component: "C:\foo\bar.txt" --> "C:"
    CString GetDriveOnly(void);

    // return drive and path component: "C:\foo\bar.txt" -> "C:\foo\"
    // (assumes trailing paths end in '\')
    CString GetDriveAndPath(void);
    CString GetPathOnly(void);

    // try to normalize a short name into a long name
    int SFNToLFN(void);

    /*
     * File manipulations.
     */
    // returns the description of the file type (as seen in explorer)
    CString GetDescription(void);

    // determine whether or not the file exists
    bool Exists(void);

    // check the status of a file
    int CheckFileStatus(struct _stat* psb, bool* pExists, bool* pIsReadable,
        bool* pIsDir);

    // get the modification date
    time_t GetModWhen(void);
    // set the modification date
    int SetModWhen(time_t when);

    // create the path, if necessary
    int CreatePathIFN(void);

    static const WCHAR* FindExtension(const WCHAR* pathname, WCHAR fssep);
    static const WCHAR* FilenameOnly(const WCHAR* pathname, WCHAR fssep);
    //int SFNToLFN(const char* sfn, CString* pLfn);

private:
    void SplitIFN(void) {
        if (!fSplit) {
            _wsplitpath(fPathName, fDrive, fDir, fFileName, fExt);
            fSplit = true;
        }
    }
    int Mkdir(const WCHAR* dir);
    int GetFileInfo(const WCHAR* pathname, struct _stat* psb, time_t* pModWhen,
        bool* pExists, bool* pIsReadable, bool* pIsDirectory);
    int CreateSubdirIFN(const WCHAR* pathStart, const WCHAR* pathEnd,
        WCHAR fssep);

    CString     fPathName;
    WCHAR       fFssep;
    bool        fSplit;

    WCHAR       fDrive[_MAX_DRIVE];         // 3
    WCHAR       fDir[_MAX_DIR];             // 256
    WCHAR       fFileName[_MAX_FNAME];      // 256
    WCHAR       fExt[_MAX_EXT];             // 256
};

#endif /*UTIL_PATHNAME_H*/