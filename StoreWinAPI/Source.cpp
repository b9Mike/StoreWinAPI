#include <windows.h>
#include "resource.h"


BOOL CALLBACK fVentanaLogin(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK fVentanaMain(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrev, PSTR cmdline, int nCmdShow) {
    // Crear la ventana de login
    HWND hVentanaLogin = CreateDialog(hInstance, MAKEINTRESOURCE(DLG_LOGIN), NULL, fVentanaLogin);

    ShowWindow(hVentanaLogin, SW_SHOW);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

BOOL CALLBACK fVentanaLogin(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_COMMAND: {
        if (LOWORD(wParam) == BTN_LOGIN_OK) {
            // Obtener el texto del usuario y la contraseña
            char usuario[100];
            char contrasenia[100];

            GetDlgItemText(hwnd, TXT_LOGIN_USUARIO, usuario, sizeof(usuario));
            GetDlgItemText(hwnd, TXT_LOGIN_CONTRA, contrasenia, sizeof(contrasenia));

            // Verificar las credenciales
            if (strcmp(usuario, "mike") == 0 && strcmp(contrasenia, "123") == 0) {
                // Si las credenciales son correctas, mostrar la ventana principal
                EndDialog(hwnd, 0); // Cierra el diálogo de login
                HWND hVentanaMain = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(DLG_MAIN), NULL, fVentanaMain);
                ShowWindow(hVentanaMain, SW_SHOW); // Muestra la ventana principal
            }
            else {
                MessageBox(hwnd, "Usuario o contraseña incorrectos.", "Error", MB_OK | MB_ICONERROR);
            }
        }
    } break;

    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return FALSE;
}

BOOL CALLBACK fVentanaMain(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return FALSE;
}
