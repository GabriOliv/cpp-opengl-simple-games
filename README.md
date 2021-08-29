# [Simple Games (C++ Opengl)](https://github.com/GabriOliv/cpp-opengl-simple-games)

Developed on Linux-like OS

---

## Installation 

#### Dependencies

```sh
sudo apt-get update
sudo apt install freeglut3-dev
```

#### Download Project

* Use Git Clone:
	```sh
	git clone https://github.com/GabriOliv/cpp-opengl-simple-games.git
	```
* Or [Download .zip](https://github.com/GabriOliv/cpp-opengl-simple-games/archive/refs/heads/main.zip)

#### Compilation

```sh
cd cpp-opengl-simple-games/
g++ -o rush_hour_game.exe rush_hour_game.cpp -lglut -lGL -lGLU
g++ -o pong_game.exe pong_game.cpp -lglut -lGL -lGLU
```
#### Run
* Pong Game
	```sh
	./pong_game.exe
	```
* Rush Hour Game
	```sh
	./rush_hour_game.exe
	```


## Games

| Game | Control |
| ------ | ------ |
| Pong Game | **W S** - [Left Side] <br/>**⬆️ ⬇️** - [Right Side] <br/> **ESC** - Exit |
| Rush Hour | **⬆️ ⬇️** - [Select Brick] <br/>**⬅️ ➡️** - [Move Brick] <br/> **ESC** - Exit |

&nbsp;

---

&nbsp;

#### Pong Game
<div align="center">
	<a href="https://github.com/GabriOliv/cpp-opengl-simple-games/blob/main/pong_game.cpp">
		<img src="https://raw.githubusercontent.com/GabriOliv/cpp-opengl-simple-games/main/img_pong_game.png" width="500"  alt="Pong_Game"/>
	</a>
	</p>
</div>

#### Rush Hour
<div align="center">
	<a href="https://github.com/GabriOliv/cpp-opengl-simple-games/blob/main/rush_hour_game.cpp">
		<img src="https://raw.githubusercontent.com/GabriOliv/cpp-opengl-simple-games/main/img_rush_hour_game.png" width="500"  alt="Rush_Hour_Game"/>
	</a>
	</p>
</div>




