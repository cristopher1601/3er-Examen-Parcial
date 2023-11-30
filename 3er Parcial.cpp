#include <Windows.h>
#include "resource.h"
#include <libloaderapi.h>
#include <iostream>
#include <set>
#include <list>
#include <commctrl.h>
#include <sstream>
using namespace std;
struct usuario
{
	char nombre[50];
	char password[50];
	usuario* sig, * ant;
};
usuario* inicio, * auxant, * auxsig,* aux, *who = nullptr;
struct ventas
{
	int N_boletos;
	int precio;
	char Evento[1000];
	ventas* v_sig, * v_ant;
};
ventas* inicio_v, * auxant_v, * auxsig_v, * aux_v = nullptr;

LRESULT CALLBACK Login(HWND hwndLogin, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Menu(HWND hwndMenu, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK N_Cuenta(HWND hwndN_Cuenta, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Eventos(HWND hwndEventos, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Venta(HWND hwndVenta, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Compras(HWND hwndCompras, UINT msg, WPARAM wParam, LPARAM lParam);


HINSTANCE hInst;
HWND hwndVenta = NULL;
HWND hwndEventos = NULL;
HWND hwndLogin = NULL;
HWND hwndMenu = NULL;
HWND hwndN_Cuenta = NULL;
HWND hwndCompras = NULL;

void AgregarUsuario(usuario* nuevo);
void Agregar_Ventas(ventas* nuevo, int boletos,int p_final);

char ag_usu[10];
char ag_contraseña[10];
int contador, nameint, presEx = 0;
int compras = 0;


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, PSTR cmdLine, int cShow)
{
	hwndLogin = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG1), NULL, Login);
	ShowWindow(hwndLogin, SW_SHOWDEFAULT);

	MSG msg;
	ZeroMemory(&msg, NULL, NULL, NULL);
	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}
LRESULT CALLBACK Login(HWND hwndLogin, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		return TRUE;
	}break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			GetDlgItemText(hwndLogin, IDC_EDIT1, ag_usu, 50);
			GetDlgItemText(hwndLogin, IDC_EDIT2, ag_contraseña, 50);
			if (inicio == NULL)
			{
				MessageBox(hwndLogin, "No hay ususarios registrados.", "AVISO", MB_OK | MB_ICONINFORMATION);
				hwndN_Cuenta = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG2), hwndN_Cuenta, N_Cuenta);
				ShowWindow(hwndLogin, SW_HIDE);
				ShowWindow(hwndN_Cuenta, SW_SHOWDEFAULT);
			}
			else
			{
				aux = inicio;
				while (aux != NULL && strcmp(ag_usu, aux->nombre) != 0)
				{
					aux = aux->sig;
				}
				if (aux == NULL)
				{
					MessageBox(hwndLogin, "Usuario no encontrado", "AVISO", MB_OK | MB_ICONINFORMATION);
				}
				else
				{
					if (strcmp(ag_contraseña, aux->password) == 0)
					{
						EndDialog(hwndLogin, 0);
						who = aux;
						hwndMenu = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG3), hwndMenu, Menu);
						ShowWindow(hwndLogin, SW_HIDE);
						ShowWindow(hwndMenu, SW_SHOWDEFAULT);

					}
					else
					{
						MessageBox(hwndLogin, "Contraseña incorrecta", "AVISO", MB_OK | MB_ICONINFORMATION);
					}
				}
			}
		}

		}break;
		

	}break;
	case WM_CLOSE:
	{
		int opc = MessageBox(hwndLogin, "¿Seguro que quiere salir?", "AVISO", MB_YESNO | MB_ICONQUESTION);
		switch (opc)
		{
		case IDYES:
		{
			DestroyWindow(hwndLogin);
			
		}break;
		}break;

	}break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}break;

	}return 0;


}
LRESULT CALLBACK Menu(HWND hwndMenu, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		aux = inicio;
		while (aux->sig != nullptr && strcmp(ag_usu, aux->nombre))
		{
			aux = aux->sig;
		}

		SetDlgItemText(hwndMenu, IDC_NOMBRE, aux->nombre);
		return TRUE;
	}break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case ID_EVENTOS:
		{
			hwndEventos = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG4), hwndEventos, Eventos);
			ShowWindow(hwndMenu, SW_HIDE);
			ShowWindow(hwndEventos, SW_SHOWDEFAULT);
		}break;
		case ID_SALIR:
		{
			int opc = MessageBox(hwndMenu, "¿Seguro que quieres salir?", "AVISO", MB_YESNO | MB_ICONQUESTION);
			switch (opc)
			{
			case IDYES:
			{
				DestroyWindow(hwndMenu);
			}break;


			}
		}break;
		case ID_VENTA:
		{
			hwndVenta = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG5), hwndVenta, Venta);
			ShowWindow(hwndMenu, SW_HIDE);
			ShowWindow(hwndVenta, SW_SHOWDEFAULT);
		}break;
		case ID_MIS_COMPRAS:
		{
			hwndCompras = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG6), hwndCompras, Compras);
			ShowWindow(hwndMenu, SW_HIDE);
			ShowWindow(hwndCompras, SW_SHOWDEFAULT);
		}break;
		}break;
	}break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}break;

	}return 0;
	
	
}
LRESULT CALLBACK N_Cuenta(HWND hwndN_Cuenta, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		return TRUE;

	}break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK3:
		{
			int lengthUsu = GetWindowTextLength(GetDlgItem(hwndN_Cuenta, IDC_EDIT1));
			int lengthcontra = GetWindowTextLength(GetDlgItem(hwndN_Cuenta, IDC_EDIT2));
			if (lengthUsu > 0 && lengthcontra > 0)
			{
				usuario* temp = new usuario;
				GetDlgItemText(hwndN_Cuenta, IDC_EDIT1, temp->nombre, 50);
				GetDlgItemText(hwndN_Cuenta, IDC_EDIT2, temp->password, 50);
				AgregarUsuario(temp);
				nameint = 1;
			}
			else
			{
				MessageBox(hwndN_Cuenta, "Favor de no dejar espacios en blanco", "AVISO", MB_OK | MB_ICONINFORMATION);
			}
			if (lengthUsu > 0 && lengthcontra > 0 && nameint > 0)
			{
				if (contador == 0)
				{
					contador = 1;
					ShowWindow(hwndN_Cuenta, SW_HIDE);
					ShowWindow(hwndLogin, SW_SHOW);
				}
				else
				{
					ShowWindow(hwndN_Cuenta, SW_HIDE);
					ShowWindow(hwndMenu, SW_SHOW);
				}
			}
		}break;
		}


	}break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}break;

	}return 0;
}
LRESULT CALLBACK Eventos(HWND hwndEventos, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		return TRUE;
	}break;
	case WM_COMMAND:
	{
		HWND lista = GetDlgItem(hwndEventos, IDC_LIST1);
		if (SendMessage(lista, LB_GETCOUNT, 0, 0) == 0)
		{
			
			SendMessage(lista, LB_ADDSTRING, 0, (LPARAM)"Los Claxons, Arena Monterrey, Monterrey, Mexico");
			SendMessage(lista, LB_ADDSTRING, 0, (LPARAM)"Tom & Collins, Nuevo Leon - Gimnasio Factores Mutuos, Monterrey, Mexico");
		}
		switch (LOWORD(wParam))
		{
		case BOTON_REGRESAR:
		{
			ShowWindow(hwndEventos, SW_HIDE);
			ShowWindow(hwndMenu, SW_SHOWDEFAULT);

		}break;
		}
	}break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}break;
	}return 0;
}
LRESULT CALLBACK Venta(HWND hwndVenta, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		SendMessage(GetDlgItem(hwndVenta, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"Los Claxons, Arena Monterrey, Monterrey, Mexico");
		SendMessage(GetDlgItem(hwndVenta, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"Tom & Collins, Nuevo Leon - Gimnasio Factores Mutuos, Monterrey, Mexico");
		return TRUE;
	}break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON1:
		{
			
			int boletos = GetDlgItemInt(hwndVenta, IDC_EDIT1, NULL, FALSE);
			int precio = 500 * boletos;
			int precio_final = precio - (precio * .10) + (precio * 0.16);
			std::string strValue = std::to_string(precio_final);
			SetDlgItemInt(hwndVenta, STATIC_TOTAL, precio_final, FALSE);
			ShowWindow(GetDlgItem(hwndVenta, STATIC_TOTAL), SW_SHOW);

		}break;
		case IDCANCEL:
		{
			ventas* temp = new ventas;

			int boletos = GetDlgItemInt(hwndVenta, IDC_EDIT1, NULL, FALSE);
			int precio_final = (500 * boletos) - ((500 * boletos) * .10);
			GetDlgItemText(hwndVenta, IDC_COMBO1, temp->Evento, 1000);
			Agregar_Ventas(temp,boletos,precio_final);
			
			ShowWindow(hwndVenta, SW_HIDE);
			ShowWindow(hwndMenu, SW_SHOWDEFAULT);

		}break;
		case IDOK:
		{
			ShowWindow(hwndVenta, SW_HIDE);
			ShowWindow(hwndMenu, SW_SHOWDEFAULT);
		}break; 
		}
		
	}break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}break;
	}return 0;
}
LRESULT CALLBACK Compras(HWND hwndCompras, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_INITDIALOG:
	{
		aux_v = inicio_v;
		while (aux_v != nullptr)
		{
			SendMessage(GetDlgItem(hwndCompras, IDC_LIST1), LB_ADDSTRING, (WPARAM)0, (LPARAM)aux_v->Evento);
			aux_v = aux_v->v_sig;
		}

		return TRUE;
	}break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			ShowWindow(hwndCompras, SW_HIDE);
			ShowWindow(hwndMenu, SW_SHOWDEFAULT);
		}break;
		}
	}break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);

	}break;
	}return 0;

}

void AgregarUsuario(usuario* nuevo)
{
	if (inicio == NULL)
	{
		inicio = new usuario;
		aux = inicio;
		nuevo->ant = NULL;
		aux->sig = nullptr;
		strcpy_s(aux->nombre, nuevo->nombre);
		strcpy_s(aux->password, nuevo->password);
        	
	}
	else
	{
		contador = 1;
		aux = inicio;
		while (aux->sig != nullptr)
		{
			auxant = aux;
			aux = aux->sig;
		}
		aux->sig = new usuario;
		aux->sig->sig = nullptr;
		nuevo->ant = auxant;
		aux = aux->sig;
		strcpy_s(aux->nombre, nuevo->nombre);
		strcpy_s(aux->password, nuevo->password);
	}
}
void Agregar_Ventas(ventas* nuevo, int boletos,int p_final)
{
	if (inicio_v == NULL)
	{
		inicio_v = new ventas;
		aux_v = inicio_v;
		nuevo->v_ant = NULL;
		aux_v->v_sig = nullptr;
		aux_v->N_boletos = boletos;
		aux_v->precio = p_final;
		strcpy_s(aux_v->Evento, nuevo->Evento);
	}
	else
	{
		aux_v = inicio_v;
		while (aux_v->v_sig != nullptr)
		{
			auxant_v = aux_v;
			aux_v = aux_v->v_sig;
		}
		aux_v->v_sig = new ventas;
		aux_v->v_sig->v_sig = nullptr;
		nuevo->v_ant = auxant_v;
		aux_v = aux_v->v_sig;
		aux_v->N_boletos = boletos;
		aux_v->precio = p_final;
		strcpy_s(aux_v->Evento, nuevo->Evento);
		
	}
}