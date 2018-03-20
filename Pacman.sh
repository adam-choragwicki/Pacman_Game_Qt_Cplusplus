if [ ! -d "executable_linux" ]; then
    wget https://github.com/adam-choragwicki/Pacman_Game_Qt_Cplusplus/releases/latest/download/executable_linux.zip
    unzip executable_linux.zip && rm executable_linux.zip
    chmod +x executable_linux/Pacman.sh executable_linux/Pacman
fi

./executable_linux/Pacman
