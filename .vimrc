"indents
set autoindent
set smartindent
"au! FileType python setl nosmartindent "for python files
inoremap # X^H#
set tabstop=4
set shiftwidth=4
setexpandtab "expand tabs to spaces

"display
set scrolloff=2
set cursorline
set nowrap

"hybrid line numbers
set number
set relativenumber
set nu rnu
augroup numbertoggle
  autocmd!
  autocmd BufEnter,FocusGained,InsertLeave,WinEnter * if &nu && mode() != "i" | set rnu   | endif
  autocmd BufLeave,FocusLost,InsertEnter,WinLeave   * if &nu                  | set nornu | endif
augroup END

"formatting
filetype plugin on
syntax on
colorscheme delek

"search
set showmatch
set incsearch
set ignorecase "for searches
set smartcase "automatically switch to case sensitive if any uppercase letters are typed
set wildmenu
set wildignore=*.o,*.obj,*.bak,*.exe,*.pyc,*.swp
nnoremap <silent> <CR> :noh<CR><CR> "clear highlighting of search

"tabs
nnoremap <C-Tab> :tabnext<CR>
nnoremap <C-S-Tab> :tabprevious<CR>
nnoremap <silent> <A-Left> :tabm -1<CR>
nnoremap <silent> <A-Right> :tabm +1<CR>
set switchbuf=usetab

"move lines up and down in each mode
nnoremap <C-j> :m+1<CR>
nnoremap <C-k> :m-2<CR>
inoremap <C-j> <Esc>:m+1<CR>gi
inoremap <C-k> <Esc>:m-2<CR>gi
vnoremap <C-j> :m '>+1<CR>gv
vnoremap <C-k> :m '<-2<CR>gv

"system
set hidden "remember undo after quitting
"output swap files and backup files to tmp dir
set directory=~/.vim/tmp//,.
setbackupdir=~/.vim/tmp//,.
"close buffer without closing pane
nnoremap <C-c> :b#\|bd #<CR>
