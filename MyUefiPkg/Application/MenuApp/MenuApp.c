#include <Uefi.h>

#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>

STATIC
VOID
DrawMenu (
  IN UINTN Selected
  )
{
  gST->ConOut->ClearScreen (gST->ConOut);

  Print (L"UEFI Menu Application\n\n");
  Print (L"Use Up/Down arrows, Enter to select, Escape to exit.\n\n");

  Print (L"%s  About\n",   Selected == 0 ? L">" : L" ");
  Print (L"%s  Devices\n", Selected == 1 ? L">" : L" ");
  Print (L"%s  Exit\n",    Selected == 2 ? L">" : L" ");
}

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
  UINTN          Selected;

  Selected = 0;

  while (TRUE) {
    DrawMenu (Selected);

    Status = gBS->WaitForEvent (
                    1,
                    &gST->ConIn->WaitForKey,
                    &EventIndex
                    );
    if (EFI_ERROR (Status)) {
      return Status;
    }

    Status = gST->ConIn->ReadKeyStroke (gST->ConIn, &Key);
    if (EFI_ERROR (Status)) {
      continue;
    }

    if (Key.ScanCode == SCAN_ESC) {
      break;
    }

    if (Key.ScanCode == SCAN_UP) {
      Selected = (Selected == 0) ? 2 : Selected - 1;
    } else if (Key.ScanCode == SCAN_DOWN) {
      Selected = (Selected + 1) % 3;
    } else if (Key.UnicodeChar == CHAR_CARRIAGE_RETURN) {
      gST->ConOut->ClearScreen (gST->ConOut);

      if (Selected == 0) {
        Print (L"You selected About.\n");
      } else if (Selected == 1) {
        Print (L"You selected Devices.\n");
      } else {
        Print (L"Exit selected. Leaving the menu.\n");
        break;
      }

      gBS->Stall (1000000);
    }
  }

  gST->ConOut->ClearScreen (gST->ConOut);
  Print (L"MenuApp is exiting.\n");

  return EFI_SUCCESS;
}
