# Day 02 — UEFI Keyboard Input

## Goal

Build and run `KeyboardApp`, a UEFI application that reads keyboard input using
the Simple Text Input Protocol.

## Concepts

- `EFI_INPUT_KEY` contains a `ScanCode` and a `UnicodeChar`.
- `gST->ConIn` is the console input protocol.
- `WaitForEvent()` waits for the input protocol's `WaitForKey` event.
- `ReadKeyStroke()` reads a key into an `EFI_INPUT_KEY`.
- Escape is identified by `Key.ScanCode == SCAN_ESC`.
- Enter is identified by `Key.UnicodeChar == CHAR_CARRIAGE_RETURN`.
- Printable keys provide a `UnicodeChar`; some special keys provide only a scan code.

## Build

The learning repository is separate from the EDK II source tree. Run these
commands to build the application:

    cd ~/src/edk2
    source ~/src/edk2/.venv/bin/activate
    source edksetup.sh
    export PACKAGES_PATH="$HOME/uefi-learning-labs"
    build -p "$HOME/uefi-learning-labs/MyUefiPkg/MyUefiPkg.dsc" -a X64 -t GCC

The absolute DSC path selects the updated platform configuration in this
repository. The `GCC` toolchain tag is used by this EDK II setup.

The built application is at
`Build/MyUefiPkg/DEBUG_GCC/X64/KeyboardApp.efi`.

## Run with QEMU and OVMF

QEMU does not need the Python virtual environment. If it is active, exit it with
`deactivate`.

Prepare a temporary FAT directory with the default x64 UEFI boot filename:

    TEST_DIR=$(mktemp -d)
    mkdir -p "$TEST_DIR/EFI/BOOT"
    cp ~/src/edk2/Build/MyUefiPkg/DEBUG_GCC/X64/KeyboardApp.efi "$TEST_DIR/EFI/BOOT/BOOTX64.EFI"
    cp /usr/share/OVMF/OVMF_VARS_4M.fd "$TEST_DIR/OVMF_VARS_4M.fd"

Start the virtual machine:

    qemu-system-x86_64 -drive if=pflash,format=raw,readonly=on,file=/usr/share/OVMF/OVMF_CODE_4M.fd -drive if=pflash,format=raw,file="$TEST_DIR/OVMF_VARS_4M.fd" -drive format=raw,file=fat:rw:"$TEST_DIR" -m 256M -net none

## Test results

- Pressing `A` displayed the character and Unicode value `0x0061`.
- Pressing Enter displayed the confirmation message.
- Pressing Escape exited KeyboardApp and returned to the UEFI boot menu.
