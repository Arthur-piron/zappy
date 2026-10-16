# Zappy

![C](https://img.shields.io/badge/C-A8B9CC?logo=c&logoColor=black)
![C++](https://img.shields.io/badge/C++17-00599C?logo=cplusplus&logoColor=white)
![Python](https://img.shields.io/badge/Python-3776AB?logo=python&logoColor=white)
![raylib](https://img.shields.io/badge/raylib-3D-black)

A networked multiplayer game played by AIs. A C server simulates a small world on a torus grid;
autonomous Python bots connect to it, gather resources, survive, and cooperate to perform
"incantation" rituals that raise their level. The first team to get six players to level 8 wins.
A 3D client written in C++ with raylib lets you watch the game live.

Team project, Epitech 2nd year (June 2026).

```
                 TCP                         TCP
 zappy_ai ×N  ◄────────►  zappy_server  ◄────────►  zappy_gui
 (Python bots)            (C, poll loop,            (C++ / raylib,
                           game clock)               3D spectator)
```

## My part: the AI

I wrote the Python AI (`AI/`), about 1,100 lines with no dependency outside the standard library.
Each bot is a separate process with no shared memory: everything is coordinated through the
server's `Broadcast` command, which only tells a bot *which direction* a message came from.

- **State machine**: `DEFAULT`, `SURVIVAL`, `LEADER`, `RALLIED`, `ARRIVED`, with food tracking
  that preempts every other goal when a bot is about to starve.
- **Leader election**: bots announce a random id; the lowest id becomes leader, without a
  central coordinator.
- **Roles**: the leader farms stones and calls the others; followers feed themselves, gather,
  and lay eggs (`Fork`) so the team grows.
- **Rallying**: followers walk toward the leader by following the direction of its broadcasts
  until they stand on its tile, then the leader starts the ritual.
- **Vision and pathfinding**: parsing of the `Look` cone into tiles and shortest moves to the
  nearest needed resource.
- **Team-tagged messages** so that bots ignore (and are not fooled by) the other team's broadcasts.

The result reaches **level 8**. The design is documented in [AI/Docs/Zappy_AI.md](AI/Docs/Zappy_AI.md).

## Features

| Part | What it does |
|---|---|
| **Server** (`NET/`, C) | Single-threaded `poll()` loop, per-client command queues, time unit scheduling, resource respawn, eggs, incantations, broadcast direction on a torus, GUI protocol. Unit tests with Criterion. |
| **GUI** (`GUI/`, C++17) | 3D scene with animated characters, resources and eggs, player list, tile inspector, broadcast log, settings menu. |
| **AI** (`AI/`, Python) | Autonomous bots described above. |

## Stack

C (server) · C++17, CMake, raylib (GUI) · Python 3.10+ (AI) · Criterion and gcov (tests)

## Build and run

Prerequisites: `gcc`, `make`, `cmake` ≥ 3.16, [raylib](https://github.com/raysan5/raylib) (GUI only), Python ≥ 3.10.

```bash
git clone https://github.com/Arthur-piron/zappy.git
cd zappy
make CC=gcc            # builds zappy_server, zappy_gui and zappy_ai
```

`CC=gcc` replaces `epiclang`, the compiler wrapper used at Epitech.

Start a server, a few bots and the GUI, each in its own terminal:

```bash
./zappy_server -p 4242 -x 10 -y 10 -n red blue -c 6 -f 100
./zappy_ai -h 127.0.0.1 -p 4242 -n red        # repeat to add players
./zappy_gui -h 127.0.0.1 -p 4242
```

| Server flag | Meaning |
|---|---|
| `-p` | port |
| `-x` / `-y` | map size |
| `-n` | team names |
| `-c` | players allowed per team at start |
| `-f` | time frequency (higher is faster) |
| `-v` | verbose log |

Server tests: `make tests_run`.

> The music tracks used by the GUI are not included (copyright). The GUI runs without them.

## Documentation

- [docs/DOCUMENTATION.md](docs/DOCUMENTATION.md): architecture, full protocol, AI strategy, server internals, known pitfalls.
- [AI/Docs/Zappy_AI.md](AI/Docs/Zappy_AI.md): the AI client in detail.
- [GUI/Docs/](GUI/Docs/): the graphical client.
