
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
  UINTN        Counter;
  EFI_INPUT_KEY Key;
  EFI_STATUS   Status;

  Counter = 1;

  Print (L"UEFI Counter Application\n");
  Print (L"Press any key to exit.\n\n");

  while (TRUE) {
    Print (L"Counter: %u\n", Counter);
    Counter++;

    // Wait approximately one second.
    gBS->Stall (1000000);

    // Check whether a key has been pressed.
    Status = gST->ConIn->ReadKeyStroke (gST->ConIn, &Key);

    if (!EFI_ERROR (Status)) {
      break;
    }
  }

  Print (L"\nKey detected. Exiting application.\n");

  return EFI_SUCCESS;
}
