# FileOS

FileOS is a small command-line operating system simulation created for learning purposes.

The project focuses mainly on file-related commands, which is why it is called FileOS. It provides basic virtual file and directory management, including creating, deleting, reading, writing, renaming, and navigating through directories.

FileOS runs on Windows, Linux, and macOS. Colored and plain-text versions are available, allowing users to choose their preferred terminal style.

The virtual filesystem is stored in memory while the program runs and is saved to a local data file for later use.

More commands and features will be added in future updates.

## Structure

```text
FileOS/
├── .github/
│   ├── .gitkeep
│   └── workflows/
│       └── build.yml
├── droc/
│   ├── command.json
│   └── command.txt (Command types)
├── include/
│   ├── directory.h
│   ├── file.h
│   ├── storage.h
│   ├── system.h
│   └── utility.h
├── src/
│   ├── directory.c (Directory commands)
│   ├── file.c (File commands)
│   ├── main.c
│   ├── storage.c (Save and load)
│   ├── system.c (User input handling)
│   └── utility.c (Utility commands)
└── README.md
```
