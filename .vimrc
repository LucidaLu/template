set tabstop=4
set shiftwidth=4
set autoindent
set cindent
set number
syntax on
colorscheme darkblue
set go=
autocmd BufNewFile *.cpp 0r ~/template.cpp
inoremap { {}<left><return><up><end><return>
inoremap } {}<left>
imap ` <c-n>
inoremap <c-l> <up><end><space>{<down><end><cr>}<up><end>
inoremap <c-k> <up><end><bs><bs><down><down><esc>ddi<up><end>
set timeoutlen=150
set cino=l-s
set filetype=cpp
func CompleteForLoop(...)
	execute printf("normal afor(int %s=%s;%s<=%s;++%s)",a:1,a:2,a:1,a:3,a:1)
	call feedkeys('a')
endfunction
command -nargs=* Rep call CompleteForLoop(<f-args>)
iab rep <esc>:Rep
iab ll long long
iab fropn freopen("input","r",stdin)
iab opn void *operator new(size_t flag) {static *pool=(*)malloc(*sizeof()),*mem;<cr>return flag?mem++:mem=pool
