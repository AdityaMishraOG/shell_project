# SHELL_PROJECT
The repository is an implementation of a Shell - a command-line interface written in C. It emulates a Unix-like shell enviornment.  

This solo project was a part of the CS3.301 - Operating Systems and Networks course .

 The link to the complete project description is [here](https://karthikv1392.github.io/cs3301_osn/mini-projects/mp1).

# Features

- Fully functional shell environment.
- Support for system commands like `cd`, `ls`, `emacs`, etc.
- Process management with foreground and background processes.
- I/O redirection using `<`, `>`, and `>>`.
- Pipe functionality for command chaining.
- Networking capabilities to fetch man pages from the internet.
- User-defined commands.
- Persistent storage of past commands and execution history.
- Error handling for both user-defined and system commands.
- Interactive features like `neonate` to display process IDs at intervals.

# User-defined Commands

The list of user-defined commands are: 

- `warp`
- `peek`
- `pastevents`
- `proclore`
- `seek`
- `activities`
- `ping`
- `fg`
- `bg`
- `neonate`
- `iMan`

# Assumptions
- The shell is exited using the `exit` command
- The target names, path names, etc are entered after the flags are entered for commands `peek` and `seek`.
- The `-` flag can not be used with commands `warp` and `peek` initially as there is no previous directory until the first change of directory happens
- The time taken by the foreground process and the name of the process will be printed in the next prompt if process takes greater than two seconds to run. However, this occurs exclusively for the subsequent prompt and not for those that follow.




