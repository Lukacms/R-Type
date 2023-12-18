#!/usr/bin/python3

import platform
import subprocess
from sys import argv, executable


def install_package(package_name):
    system = platform.system().lower()

    try:
        if system == "linux":
            # Check if Debian-based (e.g., Ubuntu), Arch, or Red Hat-based (e.g., Fedora) system
            if subprocess.call(["which", "apt-get"]) == 0:
                subprocess.call(["sudo", "apt-get", "update"])
                subprocess.call(["sudo", "apt-get", "install", "-y", package_name])
            elif subprocess.call(["which", "pacman"]) == 0:
                subprocess.call(["sudo", "pacman", "-S", "--noconfirm", package_name])
            elif subprocess.call(["which", "dnf"]) == 0:
                subprocess.call(["sudo", "dnf", "install", "-y", package_name])
            else:
                raise NotImplementedError("Unsupported Linux distribution")

        elif system == "darwin":
            # macOS using Homebrew
            if subprocess.call(["which", "brew"]) == 0:
                subprocess.call(["brew", "install", package_name])
            else:
                raise RuntimeError(
                    "Homebrew is not installed. Please install it and try again."
                )

        elif system == "windows":
            # Windows using pip
            subprocess.call([executable, "-m", "pip", "install", package_name])

        else:
            raise NotImplementedError(f"Unsupported operating system: {system}")

        print(f"Package '{package_name}' installed successfully.")

    except Exception as e:
        print(f"Error installing package '{package_name}': {e}")
        exit(1)


if __name__ == "__main__":
    for i in range(1, len(argv)):
        install_package(argv[i])
    exit(0)
