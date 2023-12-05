#ifndef HEADERS_H_
#define HEADERS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <math.h>

#include "absolute_path.h"
#include "exit.h"
#include "input.h"
#include "linked_list.h"
#include "main.h"
#include "pastevents.h"
#include "peek.h"
#include "proclore.h"
#include "prompt.h"
#include "relative_path.h"
#include "seek.h"
#include "system_calls.h"
#include "warp.h"

#define sz 4097
#define history_sz 15
#define CLOCK_MONOTONIC 1

#define RESET "\x1B[0m"
#define GREEN "\x1B[32m"
#define BLUE "\x1B[34m"
#define WHITE "\x1B[37m"
#define YELLOW "\033[1;33m"

#endif