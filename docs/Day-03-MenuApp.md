# Day 03 — UEFI Menu Application

## Goal

Build and run `MenuApp`, a UEFI text menu controlled by the keyboard.

## Concepts

- `EFI_INPUT_KEY` provides a scan code for special keys and a Unicode character for ordinary keys.
- `SCAN_UP` and `SCAN_DOWN` detect the arrow keys.
- Enter selects the highlighted menu item.
- Escape exits the application.
- `gBS->WaitForEvent()` waits for keyboard input without repeatedly polling.
- `gST->ConOut->ClearScreen()` clears the console before redrawing the menu.
- The selection wraps around when moving past the first or last item.

## Build

The learning repository is separate from the EDK II source tree. Activate the virtual environment for the build, then build from EDK II:

    cd ~/src/edk2
    source ~/src/edk2/.venv/bin/activate
    source edksetup.sh
    export PACKAGES_PATH="$HOME/uefi-learning-labs"
    build -p "$HOME/uefi-learning-labs/MyUefiPkg/MyUefiPkg.dsc" -a X64 -t GCC

The built application is at
`Build/MyUefiPkg/DEBUG_GCC/X64/MenuApp.efi`.

## Run with QEMU and OVMF

QEMU doesn’t need the Python virtual environment. Exit it with `deactivate` if it is active.

Prepare a temporary FAT directory:

    MENU_TEST_DIR=$(mktemp -d)
    mkdir -p "$MENU_TEST_DIR/EFI/BOOT"
    cp ~/src/edk2/Build/MyUefiPkg/DEBUG_GCC/X64/MenuApp.efi "$MENU_TEST_DIR/EFI/BOOT/BOOTX64.EFI"
    cp /usr/share/OVMF/OVMF_VARS_4M.fd "$MENU_TEST_DIR/OVMF_VARS_4M.fd"

Launch QEMU:

    qemu-system-x86_64 -drive if=pflash,format=raw,readonly=on,file=/usr/share/OVMF/OVMF_CODE_4M.fd -drive if=pflash,format=raw,file="$MENU_TEST_DIR/OVMF_VARS_4M.fd" -drive format=raw,file=fat:rw:"$MENU_TEST_DIR" -m 256M -net none

## Test results

- Arrow keys moved the selection through About, Devices, and Exit.
- Enter on About and Devices displayed the matching selection message.
- Enter on Exit returned to the UEFI boot menu.
- Escape also exited to the UEFI boot menu.
