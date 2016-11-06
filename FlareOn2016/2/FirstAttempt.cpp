#include <tchar.h>
#include <stdio.h>
#include <Windows.h>
#include <wincrypt.h>
#include <conio.h>

#pragma comment (lib, "advapi32")

void HandleError(LPTSTR psz, int nErrorNumber)
{
	_ftprintf(stderr, TEXT("An error occurred in the program. \n"));
	_ftprintf(stderr, TEXT("%s\n"), psz);
	_ftprintf(stderr, TEXT("Error number %x.\n"), nErrorNumber);
}



bool FireDecryptFile(LPTSTR pszSourceFile, LPTSTR pszDestinationFile, LPTSTR pszPassword)
{
	bool fReturn = false;
	HANDLE hSourceFile = INVALID_HANDLE_VALUE;
	HANDLE hDestinationFile = INVALID_HANDLE_VALUE;
	HCRYPTKEY hKey = NULL;
	HCRYPTHASH hHash1 = NULL;
	HCRYPTHASH hHash2 = NULL;
	HCRYPTPROV hCryptProv = NULL;
	DWORD dwCount;
	DWORD dwMode;
	DWORD dwHashLen;
	DWORD dwHashLenSize = sizeof(DWORD);
	PBYTE pbBuffer = NULL;
	PBYTE pbHash = NULL;
	BYTE iv[32] = { 'c', '6', '1', '0', '6', '3', '2', '0', '4', '1', 'a', '0', '6', '0',
		'9', '1', 'b', 'e', '3', 'f', '2', '6', '4', '9', 'f', '2', 'b', '8', '4', '1', '9', 'b' };
	DWORD dwBlockLen;
	DWORD dwBufferLen;

	hSourceFile = CreateFile(pszSourceFile, FILE_READ_DATA,
		FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (INVALID_HANDLE_VALUE != hSourceFile)
	{
		_tprintf(TEXT("The source encrypted file, %s, is open.\n"), pszSourceFile);
	}
	else
	{
		HandleError(TEXT("Error opening source encrypted file!\n"), GetLastError());
		goto Exit_FireDecryptFile;
	}

	hDestinationFile = CreateFile(pszDestinationFile, FILE_WRITE_DATA,
		FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (INVALID_HANDLE_VALUE != hDestinationFile)
	{
		_tprintf(TEXT("The destination file, %s, is open.\n"), pszDestinationFile);

	}
	else
	{
		HandleError(TEXT("Error opening destination file!\n"), GetLastError());
		goto Exit_FireDecryptFile;
	}

	// Get the handle to the CSP
	if (CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_AES, 0 )) {
		_tprintf(TEXT("The cryptographic provider has been acquired.\n"));
	}
	else
	{
		HandleError(TEXT("Error during CryptAcquireContext!\n"), GetLastError());
		goto Exit_FireDecryptFile;
	}

	// Decrypt the file with a session key derived from a password.

	// Create a hash object
	if (!CryptCreateHash(hCryptProv, CALG_SHA1, 0, 0, &hHash1))
	{
		HandleError(TEXT("Error during CryptCreateHash!\n"), GetLastError());
		goto Exit_FireDecryptFile;
	}

	// Hash in the password data
	if (!CryptHashData(hHash1, (BYTE *)pszPassword,
		lstrlen(pszPassword), 0))
	{
		HandleError(TEXT("Error during CryptHashData!\n"), GetLastError());
		goto Exit_FireDecryptFile;
	}

	// Derive a session key from the hash object.
	if (!CryptDeriveKey(hCryptProv, CALG_AES_256, hHash1, CRYPT_EXPORTABLE, &hKey))
	{
		HandleError(TEXT("Error during CryptDeriveKey!\n"), GetLastError());
		goto Exit_FireDecryptFile;
	}

	dwMode = CRYPT_MODE_CBC;
	if (!CryptSetKeyParam(hKey, KP_MODE, (BYTE *)&dwMode, 0))
	{
		HandleError(TEXT("Error during CryptSetKeyParam!\n"), GetLastError());
		goto Exit_FireDecryptFile;
	}

	
	if (!CryptGetKeyParam(hKey, KP_BLOCKLEN, (BYTE *)&dwBlockLen, &dwBufferLen, 0))
	{
		HandleError(TEXT("Error during CryptGetKeyParam!\n"), GetLastError());
		goto Exit_FireDecryptFile;
	}

	// Create a hash object
	if (!CryptCreateHash(hCryptProv, CALG_MD5, 0, 0, &hHash2))
	{
		HandleError(TEXT("Error during CryptCreateHash!\n"), GetLastError());
		goto Exit_FireDecryptFile;
	}

	if (!CryptHashData(hHash2, (BYTE *)pszSourceFile,
		lstrlen(pszSourceFile), 0))
	{
		HandleError(TEXT("Error during CryptHashData!\n"), GetLastError());
		goto Exit_FireDecryptFile;
	}

	if (!CryptGetHashParam(hHash2, HP_HASHSIZE, (BYTE *)&dwHashLen, &dwHashLenSize, 0))
	{
		HandleError(TEXT("Error during CryptGetHashParam!\n"), GetLastError());
		goto Exit_FireDecryptFile;
	}

	if (! (pbHash = (BYTE *)malloc(dwHashLen)))
	{
		HandleError(TEXT("Allocation failed!\n"), GetLastError());
		goto Exit_FireDecryptFile;
	}

	if (!CryptGetHashParam(hHash2, HP_HASHVAL, pbHash, &dwHashLen, 0))
	{
		HandleError(TEXT("Error during CryptGetHashParam!\n"), GetLastError());
		goto Exit_FireDecryptFile;
	}

	if (!CryptSetKeyParam(hKey, KP_IV, iv, 0))
	{
		HandleError(TEXT("Error during CryptSetKeyParam!\n"), GetLastError());
		goto Exit_FireDecryptFile;
	}

	// Allocate memory for the file read buffer. 
	if (!(pbBuffer = (PBYTE)malloc(dwBlockLen*5)))
	{
		HandleError(TEXT("Out of memory!\n"), E_OUTOFMEMORY);
		goto Exit_FireDecryptFile;
	}


	bool fEOF = false;
	do
	{
		if (!ReadFile(hSourceFile, pbBuffer, dwBlockLen, &dwCount, NULL))
		{
			HandleError(TEXT("Error reading from source file!\n"), GetLastError());
			goto Exit_FireDecryptFile;
		}

		if (dwCount <= dwBlockLen)
		{
			fEOF = TRUE;
		}

		if (!CryptDecrypt(hKey, 0, fEOF, 0, pbBuffer, &dwCount))
		{
			HandleError(TEXT("Error during CryptDecrypt!\n"), GetLastError());
			goto Exit_FireDecryptFile;
		}

		if (!WriteFile(hDestinationFile, pbBuffer, dwCount, &dwCount, NULL))
		{
			HandleError(TEXT("Error writing ciphertext.\n"),
				GetLastError());
			goto Exit_FireDecryptFile;
		}
	} while (!fEOF);

	fReturn = true;

Exit_FireDecryptFile:

	if (pbBuffer)
	{
		free(pbBuffer);
	}

	if (hSourceFile)
	{
		CloseHandle(hSourceFile);
	}

	if (hDestinationFile)
	{
		CloseHandle(hDestinationFile);
	}

	if (hHash1)
	{
		if (!(CryptDestroyHash(hHash1)))
		{
			HandleError(TEXT("Error during CryptDestroyHash!\n"), GetLastError());
		}
		hHash1 = NULL;
	}

	if (hHash2)
	{
		if (!(CryptDestroyHash(hHash2)))
		{
			HandleError(TEXT("Error during CryptDestroyHash!\n"), GetLastError());
		}
		hHash2 = NULL;
	}

	if (hKey)
	{
		if (!(CryptDestroyKey(hKey)))
		{
			HandleError(TEXT("Error during CryptDestroyKey!\n"), GetLastError());
		}
	}

	if (hCryptProv)
	{
		if (!(CryptReleaseContext(hCryptProv, 0)))
		{
			HandleError(TEXT("Error during CryptReleaseContext!\n"), GetLastError());
		}
	}

	return fReturn;
}

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc < 4)
	{
		_tprintf(TEXT("Usage: <FireEyeChal2Decrypt.exe> <source> <dest> <pass>\n"));
		_tprintf(TEXT("Press any key to exit."));
		_gettch();
		return 1;
	}

	LPTSTR pszSource = argv[1];
	LPTSTR pszDestination = argv[2];
	LPTSTR pszPassword = argv[3];

	if (FireDecryptFile(pszSource, pszDestination, pszPassword))
	{
		_tprintf(TEXT("Decryption of the file %s was successful. \n"), pszSource);
		_tprintf(TEXT("The decrypted data is in file %s.\n"), pszDestination);
	}
	else
	{
		HandleError(TEXT("Error decrypting file!\n"), GetLastError());
	}
	return 0;
}
