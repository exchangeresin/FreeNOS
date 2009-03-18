/*
 * Copyright (C) 2009 Niek Linnenbank
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include "StatCommand.h"

int StatCommand::execute(Size nparams, char **params)
{
    struct stat st;
    
    /* Try to stat the file. */
    if ((stat(params[0], &st)) < 0)
    {
	printf("Failed to stat '%s': %s\n",
		params[0], strerror(errno));
	return errno;
    }
    /* Output file statistics. */
    printf("File: %s\n", params[0]);
    printf("Type: ");
    
    /* Print the right file type. */
    if (S_ISREG(st.st_mode))
	printf("Regular File\n");
    
    else if (S_ISDIR(st.st_mode))
	printf("Directory\n");
    
    else if (S_ISCHR(st.st_mode))
    {
	printf("Character Device\n");
	printf("Major ID: %u\n", st.st_dev.major);
	printf("Minor ID: %u\n", st.st_dev.minor);
    }
    else if (S_ISBLK(st.st_mode))
	printf("Block Device\n");

    else
	printf("Unknown\n");
    
    /* Identities. */
    printf("Uid:  %u\n", st.st_uid);
    printf("Gid:  %u\n", st.st_gid);
    
    /* Success. */
    return 0;
}

INITOBJ(StatCommand, statCmd, DEFAULT)
