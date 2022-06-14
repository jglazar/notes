# Mastering Vim by Ilic

## basics

open file with `vim +NUM file` to skip to line number  
....could specify `+pattern` instead 

`Ctrl+v` can highlight multiple lines to apply operations in parallel   

modes:  
* normal -- stay here when not typing
* insert
* command
* visual -- highlights text
* insert normal -- press `Ctrl+o` to enter one Normal command

commands:  
* ex -- regular commands, like `:help`
* mapped -- mappings/bindings
* editing -- used in Normal and Insert Modes, like `d3w`

can open files in normal mode with `:e file`  
this places file into current buffer  
can also read file into line below cursor with `:r file`  
....specify line to read into with `:NUMr file`  

use `gf` (goto file) if hovering on filename with cursor  

`:x` -- close file and write only if changes were made  

### navigation
use capital `W` or `E` to ignore punctuation  
....defines word using whitespace only  

* `Ctrl+d` -- scroll down half page 
* `Ctrl+u` -- scroll up half page 
* `Ctrl+f` -- scroll down full page 
* `Ctrl+b` -- scroll up full page 
* `H` -- skip to highest line in window
* `L` -- skip to lowest line in window
* `M` -- skip to middle of window

`:NUM` skips to line NUM  

`shift+rightarrow` -- travel right by word 
`shift+leftarrow` -- travel left by word 

### search
hover over word and press:  
* `*` -- search forwards for next occurence of current word
* `#` -- search backwards
* prepend `g` for inexact matches

arrow up/down to scroll through previous searches  
empty pattern repeats last search  
`NUM/pattern` skips to NUMth occurence  

after search is done, press `Ctrl+o` to jump to prior position
or `Ctrl+i` to jump forwards  

### file browsing
`netrw` plugin launched via:  
* `:Ex` -- opens current dir in current window
* `:Ex dir` -- open specified dir in current window
* `:Sex` -- open in horizontal split
* `:Vex` -- open in vertical split
* `:Tex` -- open in new tab

`i` cycles through view types:
* thin
* long
* wide
* tree
set default in `~/.vimrc` with `let g:netrw_liststyle = NUM`

can open directories in vim from cmd line  

`netrw` commands:  
* `Enter` -- open file under cursor
* `D` -- delete file under cursor
* `R` -- rename file under cursor
* `X` -- execute file under cursor
* `%` -- create new file in current directory

file is opened in same window by default  
....can keep `netrw` in split with `:netrw_browse_split`  
....add to `~/.vimrc` using `let g:netrw_browse_split = 4`  
....this opens files in previous window. other options available too  

can set default netrw windowsize % with `let g:netrw_winsize = NUM`  

vim can open remote files via ssh, ftp, and more  

## personalization

add raw cmd to `~/.vimrc`, or  
run cmd in vim command mode (prepend `:`)  
unset with `set noCMD` or `set CMD!`
check setting status with `set CMD?`  

see more in book on page 34  

general:  
* `set nocompatible` -- enable vim over vi
* `set backspace=indent,eol,start` -- allow more backspaces
* `set history=NUM` -- set bigger command history
* `set showcmd` -- show commands as they're typed
* `set autoread` -- re-read files if unmodified
* `set hidden` -- manage many buffers

interface:  
* `set number` -- set line numbers 
* `colorscheme TAB` -- check colorschemes 
  * I like default, delek, desert, pablo, peachpuff, and zellner
  * default is best
* `set laststatus=2` -- always display status bar 
* `set wildmenu` -- display TAB completions as menu
* `set tabpagemax=40` -- set max num of tab pages

indents:  
* `set autoindent` -- new line inherits old line's indent
* `filetype plugin indent on` -- smart indent
* `set tabstop=NUM` -- set TAB to appear as NUM spaces
* `set expandtab` -- TAB = 4 spaces
* `set nowrap` -- don't wrap lines

search:  
* `set incsearch` -- find next match as search is typed
* `set hlsearch` -- turn on search highlighting
* `set ignorecase`
* `set smartcase`

text rendering:  
* `set encoding=utf-8`
* `set linebreak` -- smarter line wrapping
* `set scrolloff=NUM` -- number of lines to pad before/after cursor
* `syntax enable` -- syntax highlighting 

misc:  
* `set confirm` -- confirm before quitting
* `set nolinemode` -- use vimrc rather than file's mode lines
