# AbstractFilePathSystem - Update a file path based on a directory change command

# Problem to solve
   Write a function that provides change directory (cd) function for an
   abstract file system.

   Notes:

   1. Root path is '/'.
   2. Path separator is '/'.
   3. Parent directory is addressable as "..".
   4. Directory names consist only of English alphabet letters (A-Z and a-z).

   For example, Path("/a/b/c/d").cd("../x").getPath() should return "/a/b/c/x".

   Note: Do not use built-in path-related functions.
   
# Solution

Treat each cd (change directory) command as a series of atomic command and handle
them one at a time. Many test cases are provided in the code.

The code does not handle '.' (current directory) and windows file separator ('\\').

## Solution 1

Use an iterative solution

# Solution 2

this function use recursive algorithm to parse a cd path command and create 
the result path at each step

