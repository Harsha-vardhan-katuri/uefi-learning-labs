# Day 01 — UEFI Fundamentals

## Tasks completed
- Set up EDK II in Ubuntu on WSL2.
- Built EDK II BaseTools.
- Built and ran HelloWorld.
- Created a custom platform DSC for MyUefiPkg.
- Built CounterApp and ran it in QEMU with OVMF.

## Concepts learned
- UEFI applications and the UefiMain entry point.
- INF files describe modules and their dependencies.
- DSC files define platform configuration and library mappings.
- Library classes specify services that modules require.
- Library instances provide implementations.
- Boot Services provide firmware services before OS handoff.
- gBS->Stall() introduces a delay.
- ReadKeyStroke() checks for available keyboard input.

## Challenges
- Resolving library dependencies in a custom DSC.
- Keeping C source files separate from INF configuration files.
- Running EFI applications from a virtual FAT filesystem.

## Next session
Build a KeyboardApp that responds to Enter and Escape.
