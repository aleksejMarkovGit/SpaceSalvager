# Windows Third-Party Dependencies

This directory is reserved for local third-party dependencies required to build **Space Salvager on Windows**.

Third-party libraries are intentionally **not stored in the repository**.

## SFML

The Windows build requires:

- **SFML 2.5.1**
- a build compatible with the selected MSVC toolset
- static SFML libraries

Space Salvager was originally developed using:

- Windows 7
- Visual Studio 2015
- MSVC v140
- SFML 2.5.1
- static linking

## Expected Directory Structure

Place the Windows SFML distribution inside this directory:

```text
third_party_for_windows/
├── README.md
└── SFML-2.5.1/
    ├── include/
    ├── lib/
    │   └── cmake/
    │       └── SFML/
    └── ...
```

The exact SFML package must match the compiler toolset and target architecture used for the build.

## CMake Configuration

The main `CMakeLists.txt` enables static SFML linking automatically on Windows:

```cmake
if(WIN32)
    set(SFML_STATIC_LIBRARIES ON)
endif()
```

When configuring the project, provide the location of the SFML CMake package if CMake cannot find it automatically.

Example:

```powershell
cmake -S . -B build `
    -DSFML_DIR="third_party_for_windows/SFML-2.5.1/lib/cmake/SFML"
```

Then build the generated project:

```powershell
cmake --build build --config Release
```

## Notes

- SFML binaries and libraries inside this directory are ignored by Git.
- Only this `README.md` is stored in the repository.
- Do not mix SFML builds compiled for different MSVC versions or architectures.
- The Linux build does not use this directory; SFML is obtained from the system package manager instead.
