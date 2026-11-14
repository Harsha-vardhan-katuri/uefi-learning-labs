# UEFI Learning Labs

Hands-on UEFI development using EDK II, Embedded C, and QEMU.

## Environment
- Ubuntu on WSL2
- EDK II
- GCC toolchain
- QEMU with OVMF firmware

## Day 01 — UEFI Fundamentals
- Built and ran HelloWorld.
- Created and tested CounterApp.
- Learned about INF files, DSC files, library classes, and Boot Services.

## Day 02 — Keyboard Input
- Built and tested KeyboardApp with QEMU and OVMF.
- Read keyboard input using `EFI_INPUT_KEY` and `ReadKeyStroke()`.
- Handled Enter, Escape, and other keys.
- See [Day 02 — UEFI Keyboard Input](docs/Day-02-Keyboard-Input.md).

## Day 03 — UEFI Menu
- Built and tested MenuApp with QEMU and OVMF.
- Used Up/Down scan codes to move through menu choices.
- Used Enter to select and Escape to exit.
- See [Day 03 — UEFI Menu Application](docs/Day-03-MenuApp.md).
