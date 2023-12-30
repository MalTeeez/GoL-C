set -xe
gcc main.c -lpthread -o main -Wall -Wextra -pedantic

echo "\n Executing main.c \n"

screen -S c ./main