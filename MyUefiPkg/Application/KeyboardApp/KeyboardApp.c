#include <Uefi.h>

#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>

EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_INPUT_KEY  Key;
  EFI_STATUS     Status;
  UINTN          EventIndex;

  Print (L"UEFI Keyboard Application\n");
  Print (L"Press Enter to confirm, Escape to exit, or another key for details.\n\n");

  while (TRUE) {
    //
    // Wait until the console input protocol signals that a key is available.
    //
    Status = gBS->WaitForEvent (
                    1,
                    &gST->ConIn->WaitForKey,
                    &EventIndex
                    );
    if (EFI_ERROR (Status)) {
      Print (L"Error while waiting for keyboard input: %r\n", Status);
      return Status;
    }

    Status = gST->ConIn->ReadKeyStroke (gST->ConIn, &Key);
    if (EFI_ERROR (Status)) {
      Print (L"Could not read the key: %r\n", Status);
      continue;
    }

    if (Key.ScanCode == SCAN_ESC) {
      Print (L"Escape detected. Exiting.\n");
      break;
    }

    if (Key.UnicodeChar == CHAR_CARRIAGE_RETURN) {
      Print (L"Enter detected. Confirmation received.\n");
      continue;
    }

    if (Key.UnicodeChar != 0) {
      Print (L"Character: '%c' (Unicode: 0x%04x)\n",
             (UINTN)Key.UnicodeChar,
             (UINTN)Key.UnicodeChar);
    } else {
      Print (L"Special key detected (scan code: 0x%04x)\n",
             (UINTN)Key.ScanCode);
    }
  }

  return EFI_SUCCESS;
}
