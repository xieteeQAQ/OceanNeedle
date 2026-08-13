cmake --build build
if (( $? == 0 )); then
    print "\ncompiler(zsh): build successed."
    zsh execute.zsh
else
    echo "\ncompiler(zsh): build failed."
fi