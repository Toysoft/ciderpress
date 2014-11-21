/*
 * CiderPress
 * Copyright (C) 2007 by faddenSoft, LLC.  All Rights Reserved.
 * See the file LICENSE for distribution terms.
 */
/*
 * Support for the sub-volume selection dialog.
 *
 * This just picks a sub-volume.  Image format overrides and blocks vs.
 * sectors should be chosen elsewhere.
 */
#include "stdafx.h"
#include "SubVolumeDialog.h"
#include "resource.h"


BEGIN_MESSAGE_MAP(SubVolumeDialog, CDialog)
    ON_LBN_DBLCLK(IDC_SUBV_LIST, OnItemDoubleClicked)
END_MESSAGE_MAP()


/*
 * Set up the control.
 */
BOOL
SubVolumeDialog::OnInitDialog(void)
{
    ASSERT(fpDiskFS != NULL);

    CListBox* pListBox = (CListBox*) GetDlgItem(IDC_SUBV_LIST);
    ASSERT(pListBox != NULL);

//  if (pListBox->SetTabStops(12) != TRUE) {
//      ASSERT(false);
//  }

    DiskFS::SubVolume* pSubVol = fpDiskFS->GetNextSubVolume(NULL);
    ASSERT(pSubVol != NULL);     // shouldn't be here otherwise
    while (pSubVol != NULL) {
        CString volumeIdW(pSubVol->GetDiskFS()->GetVolumeID());
        pListBox->AddString(volumeIdW); // makes a copy of the string

        pSubVol = fpDiskFS->GetNextSubVolume(pSubVol);
    }

    return CDialog::OnInitDialog();
}

/*
 * Do the DDX thang.
 */
void
SubVolumeDialog::DoDataExchange(CDataExchange* pDX)
{
    DDX_LBIndex(pDX, IDC_SUBV_LIST, fListBoxIndex);
}

/*
 * Accept a double-click as an "OK".
 */
void
SubVolumeDialog::OnItemDoubleClicked(void)
{
    OnOK();
}