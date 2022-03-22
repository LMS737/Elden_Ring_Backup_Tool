# Elden_Ring_Backup_Tool

#### A tool written in C++ to make a versioned backup of Elden Ring Saves in Windows.

### What is it?
The use case of this tool is to run the tool after a play session of Elden Ring to make a versioned backup, that's it.

No schedulers, background tasks, GUI, backing up every X seconds, backup restoring.

This tool is supposed to be made for myself for my own convenience. No updates are planned.

### How does it work?
This tool keeps a version history of five saves: Save_1, ..., Save_5. The highest number Save_X is always the most recent Save file.

Every time the tool is run, a new save is backed up inside the folder `<Directory where the tool is run>\Backup_Saves\Save_X`. All the way up to Save_5. 

If Save_5 already exists the following happens: 

- Save_1 is removed which is the oldest Save
- Save_3 is renamed to Save_2
- Save_4 is renamed to Save_3
- Save_5 is renamed to Save_4
- Save_5 is created and is the most recent Save

### How do I run it?
- You can simply download it under Releases and run the .exe file. 
- Or you can compile the program yourself. You need C++17 or later (I used C++20).

### Anti-Virus gets triggered?
Yes that might happen. This occurs when an attempt is made to remove directory `Save_1`. They don't like directory removal by an unknown .exe file , especially if you run the tool from the C:\ drive.  

Unfortunately there is not much you can do, except whitelisting or running the program from a drive other than C:\ .





