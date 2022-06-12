#vimtutor

##navigation

   k
   |
h-- --l
   |
   j

can prepend number to skip that many spaces/lines
`Ctrl+G`  --  display file status and current line
`Ctrl+w`  --  jump between windows

###modes
Normal   --  `esc`     --  perform actions
Command  --  `:`       --  save/quit/interact with cmd line
Insert   --  `i`       --  insert text before cursor
             `a`       --  insert text (append) after cursor
             `A`       --  insert text (append) to end of line
             `o`       --  create newline below and insert text
             `O`       --  create newline above and insert text
Replace  --  `Ctrl+r`  --  overwrite text
Visual   --  `v`       --  select text  

###actions
singletons:
`x`  --  delete current character
`r`  --  replace character

work with motion:
`d`  --  delete (`dd` deletes current line)
`c`  --  change selection (e.g., `ce` changes word)

###motions
`w`  --  skip to beginning of next word 
`e`  --  skip to end of current word 
`0`  --  skip to end of line
`$`  --  skip to beginning of line
`G`  --  skip to end of file
`gg` --  skip to beginning of file

may prepend number, as in `5w`

###commands
`help`  --  open help
`q`   --  quit file
`q!`  --  quit without saving
`w`   --  write (save) file
`wq`  --  save and quit
`w <name>`  --  save to named file
`r <name>`  --  read file into cursor
`r !<cmd>`  --  pipe command output into cursor 
`!<cmd>`  --  execute command on command line
`set ic`   --  ignore case when searching
`set is`   --  allow partial matches
`set hls`  --  highlight matches
prepend `no` to unset
`Ctrl+d`  --  show available commands
`Tab`  --  tab autocomplete

###copy and paste
`y`  --  copy (yank) selection 
`p`  --  paste after cursor

###undo and redo
`u`  --  undo previous action
`U`  --  undo all changes on line
`Ctrl+R`  --  revert undo (redo)

###search
`/`  --  search forward
`?`  --  search backward
`n`  --  skip to next match
`N`  --  skip to prior match
`Ctrl+o`  --  check older matches
`Ctrl+i`  --  check newer matches
`%`  --  find matching ()/[]/{}

###substitutions
`:s/old/new`         --  substitute first match in line
`:s/old/new/g`       --  substitute all matches in line
`:#,#s/old/new/g`    --  substitute all matches between line numbers
`:%s/old/new/g`      --  substitute all matches in file
`.../gc`  --  ask for comfirmation before changes
