xhost +local:docker

if [[ "$(docker images -q pacman 2> /dev/null)" == "" ]]; then
  docker build -t pacman .
fi

docker run -d --rm --env="DISPLAY" --net=host pacman

