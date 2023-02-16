#include <windows.h>
#include <dlgs.h>

#include <time.h>

HINSTANCE g_hInstance;

int getrand(int ubound)
{
    return (int)((rand() / ((double)RAND_MAX + 1.0f)) * ubound);
}

int compare(const void *x, const void *y)
{
    const int *a = (const int *)x;
    const int *b = (const int *)y;
    return *a - *b;
}

VOID DoIt(HWND hDlg)
{
    int i, j;
    int a[5];

    a[0] = 1 + getrand(31);
    for(i = 1; i < 5; i++)
    {
        a[i] = 1 + getrand(31 - i);
        for(j = 0; j < i; j++)
        {
            if (a[j] <= a[i])
                a[i]++;
        }
        qsort(a, i + 1, sizeof(int), compare);
    }

    SetDlgItemInt(hDlg, edt1, a[0], FALSE);
    SetDlgItemInt(hDlg, edt2, a[1], FALSE);
    SetDlgItemInt(hDlg, edt3, a[2], FALSE);
    SetDlgItemInt(hDlg, edt4, a[3], FALSE);
    SetDlgItemInt(hDlg, edt5, a[4], FALSE);
}

BOOL CALLBACK
DialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HICON hIcon;
    HBITMAP hbm;

    switch(uMsg)
    {
    case WM_INITDIALOG:
        hIcon = LoadIcon(g_hInstance, MAKEINTRESOURCE(1));
        SendMessage(hDlg, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
        SendMessage(hDlg, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
        hbm = LoadBitmap(g_hInstance, MAKEINTRESOURCE(1));
        SendDlgItemMessage(hDlg, stc1, STM_SETIMAGE, IMAGE_BITMAP, 
                           (LPARAM)hbm);
        DoIt(hDlg);
        return TRUE;

    case WM_COMMAND:
        switch(LOWORD(wParam))
        {
        case IDOK:
        case IDCANCEL:
            break;

        case psh1:
            DoIt(hDlg);
            break;
        }
        break;

    case WM_SYSCOMMAND:
        if (wParam == SC_CLOSE)
        {
            EndDialog(hDlg, IDCLOSE);
        }
        break;
    }
    return FALSE;
}

INT WINAPI WinMain(
    HINSTANCE   hInstance,
    HINSTANCE   hPrevInstance,
    LPSTR       pszCmdLine,
    INT         nCmdShow)
{
    srand((unsigned int)time(NULL));
    g_hInstance = hInstance;
    DialogBox(hInstance, MAKEINTRESOURCE(1), NULL, DialogProc);
    return 0;
}
