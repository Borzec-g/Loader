# Loader
Loader Start Exe + Exe

# App Launcher

A lightweight utility for launching applications in a secure, temporary environment.

## Features

- Launches a main application (e.g., Zoom) from embedded resources.
- Runs a background service alongside the main app.
- Self-cleaning: removes all temporary files after the main app closes.
- Single-file executable with no external dependencies.

## Building

1. Open the solution in Visual Studio 2022.
2. Set configuration to `Release` and platform to `x64`.
3. Build the project. The output is a single `Loader.exe`.

## Usage

Place the compiled `Loader.exe` in any folder and run it. It will automatically:
- Extract and launch the main application (requires the main app's EXE to be embedded as a resource).
- Extract and run the background service (requires the service's EXE to be embedded as a resource).
- Wait for the main app to close, then perform cleanup.

## Author
**KOSTIANTYN CHUDINOV** (GitHub: Borzec-g)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
