# Flappy Bird DS - OOP Refactored Edition

A complete refactoring of a Flappy Bird recreation for the Nintendo DS, transformed from a single 730-line monolithic file into a clean, object-oriented architecture.

## Why This Project Exists

I found this Flappy Bird recreation for the DS and decided to refactor the code to learn something and to just make something cool. The original code was written by **fawnity** (thanks G!) in a single `main.cpp` file - functional but hard to maintain and extend.

This project takes that original code and splits it up into different scripts using an **Object-Oriented Programming (OOP) approach**. I hope this might be informative for people who want to up their coding skills and learn how to potentially refactor code.

The original `main.cpp` is included in this repository for reference, so you can see the before and after.

---

## Screenshots

**On emulator**

<img src="https://github.com/Fewnity/Flappy-Bird-Nintendo-DS/blob/main/GitImages/Flap2.PNG" width="350"><img src="https://github.com/Fewnity/Flappy-Bird-Nintendo-DS/blob/main/GitImages/FlapGif.gif" width="470">

**On a real Nintendo DS**

<img src="https://github.com/Fewnity/Flappy-Bird-Nintendo-DS/blob/main/GitImages/FlapReal.jpg" width="500">

---

## Project Structure

```
source/
├── fb_main.cpp                 # Entry point (just 7 lines!)
├── game/
│   ├── flappybird.cpp/hpp      # Main game controller & state machine
│   ├── bird.cpp/hpp            # Bird entity (physics, animation)
│   ├── pipe.cpp/hpp            # Pipe obstacles (spawning, collision)
│   ├── ui.cpp/hpp              # All UI elements (scores, menus, medals)
│   ├── background.cpp/hpp      # Background scrolling & day/night cycle
│   ├── state.hpp               # Game state enum
│   ├── assets.hpp              # Asset definitions (paths, IDs, dimensions)
│   └── constants.hpp           # Shared game constants
├── engine/
│   ├── graphics/
│   │   └── nf_handler.cpp/hpp  # NightFox library wrapper
│   ├── audio/
│   │   └── sfx_handler.cpp/hpp # Maxmod audio wrapper
│   └── io/
│       └── io_handler.cpp/hpp  # Save/load system
└── nds/
    └── input.cpp/hpp           # DS input handling wrapper
```

---

## How The Code Works

### The Entry Point (`fb_main.cpp`)

The new entry point is beautifully simple:

```cpp
int main(int argc, char **argv){
    FB_GAME fb;
    fb.gameLoop();
    return 0;
}
```

Compare this to the original 730-line `main.cpp` where everything was crammed together!

---

### The Game Controller (`flappybird.cpp`)

This is the heart of the refactored code. It manages:

- **Initialization**: Sets up all subsystems (graphics, audio, sprites)
- **Game Loop**: The main `while(true)` loop that runs every frame
- **State Machine**: Handles transitions between MENU, GET_READY, PLAYING, and DEAD states
- **State Change Callbacks**: UI updates only happen on state transitions, not every frame

**Key Pattern - State Transition Handling:**

```cpp
// Instead of updating UI every frame, we detect state changes
if (gs != prevState){
    onGameStateChanged(prevState, gs);
    prevState = gs;
}
```

This is cleaner than the original where UI code was scattered throughout the game loop.

**Original approach (messy):**
```cpp
// UI updates sprinkled everywhere in the loop
if (WaitToStart) {
    // ... game logic ...
    NF_ShowSprite(GameScreen, UiGfxOffset + 5, false);  // Random UI call
    ShowTitle(0);  // Another UI call
    // ... more game logic ...
}
```

**Refactored approach (clean):**
```cpp
void FB_GAME::onGameStateChanged(GAME_STATE from, GAME_STATE to){
    if (to == GET_READY){
        ui.hidePlayButton();
        ui.showTitleWithFlag(0);
        ui.getReadyScreen(true);
        // All UI changes in one place!
    }
    // ... other states ...
}
```

---

### The Bird Class (`bird.cpp`)

Encapsulates everything about the bird:

| Method | Purpose |
|--------|---------|
| `init()` | Loads sprite, palette, creates the bird on screen |
| `animate()` | Handles wing flapping animation (3 frames, ping-pong) |
| `idleBob()` | Sine wave bobbing motion on menu screen |
| `jump(force)` | Applies upward velocity |
| `gravity()` | Pulls bird down each frame |
| `update(do_gravity)` | Main update - applies physics and draws |
| `checkTopAndBottomCollision()` | Ground and ceiling detection |
| `reset()` | Returns bird to starting position |

**Animation System Explained:**

The bird has 3 animation frames per color (9 total for 3 colors). The animation ping-pongs:

```cpp
void Bird::animate(){
    birdAnimationTimer++;
    if (birdAnimationTimer >= BIRD_ANIMATION_TIMER_COUNT){
        birdAnimationTimer = 0;

        if (reverseAnimation)
            currentBirdAnimation++;
        else
            currentBirdAnimation--;

        NF_HANDLER::spriteFrame(Constants::GAME_SCREEN, gfx_b.id,
                                currentBirdAnimation + model * 3);

        if ((currentBirdAnimation >= BIRD_ANIMATION_COUNT - 1) ||
            (currentBirdAnimation <= 0))
            reverseAnimation = !reverseAnimation;
    }
}
```

**Physics:**
- Gravity adds `0.14f` to Y velocity each frame (capped at 4.0)
- Jump sets Y velocity to `-3.1f` (negative = upward)
- Rotation is tied to velocity: `rot = y_speed * 31.5f`

---

### The Pipe Class (`pipe.cpp`)

Each pipe is actually a **pair** - top and bottom sprites forming a gap.

**Key Insight from Original Code:**

The original used `yPos` as the **bottom pipe's Y position**, with the top pipe at `yPos - 120`. This 120-pixel offset includes:
- Top pipe height (64 pixels)
- Gap size (~56 pixels)

```cpp
void Pipe::updatePosition(){
    int top_y = gap_y - 120;  // Top pipe sprite
    int btm_y = gap_y;        // Bottom pipe sprite

    NF_HANDLER::moveSprite(Constants::GAME_SCREEN, sprite_id_top, x_pos, top_y);
    NF_HANDLER::moveSprite(Constants::GAME_SCREEN, sprite_id_btm, x_pos, btm_y);
}
```

**Collision Detection:**

The original's collision formula (which took me a while to understand!):

```cpp
bool Pipe::checkCollision(int bird_x, int bird_y, int bird_w, int bird_h){
    // Is bird horizontally overlapping with pipe?
    if (x_pos - 11 <= bird_x && x_pos + 26 >= bird_x){
        // Is bird OUTSIDE the safe gap zone?
        if (gap_y <= bird_y + 16 || gap_y >= bird_y + 57){
            return true;  // Collision!
        }
    }
    return false;
}
```

The magic numbers (11, 26, 16, 57) account for sprite sizes and hitbox tweaking.

**Respawn System:**

When a pipe goes off-screen left, it teleports to the right:

```cpp
void Pipe::respawn(){
    x_pos += (PIPE_WIDTH + 68) * Constants::PIPE_COUNT;  // Jump right
    gap_y = randomGapY();  // New random gap position
    scored = false;        // Can score again
}
```

---

### The UI Class (`ui.cpp`)

Handles all user interface elements:

- Title screen ("Flappy Bird" logo)
- "Get Ready!" screen with tap indicator
- "Game Over" screen
- Score display (1-3 digits)
- Score board with current score and high score
- Medal display (bronze/silver/gold/platinum based on score)
- Play button

**Sprite Frame System:**

The UI sprites use a frame-based system where different frames show different graphics:
- Frames 2-3: "Get Ready!" text
- Frames 4-5: "Game Over" text
- Frames 6-7: "Flappy Bird" title
- Frame 8: Tap indicator
- Frame 9: Play button
- Frames 0-3: Medal types

---

### The Background Class (`background.cpp`)

Manages the parallax scrolling backgrounds:

```cpp
void BG::scrollBackground(){
    x_pos++;
    if (x_pos >= 255)
        x_pos = 0;  // Seamless loop

    NF_HANDLER::scrollBackground(Constants::GAME_SCREEN, sb.layer, x_pos, y_pos);
}
```

Also handles day/night background switching with weighted randomness (75% day, 25% night).

---

### The Engine Layer

#### NF_HANDLER (Graphics)

Wraps the NightFox library, which itself wraps low-level DS graphics:

```cpp
// Instead of calling NightFox directly:
NF_CreateSprite(GameScreen, 0, 0, 0, BirdxPos, BirdyPos);

// We use our wrapper:
NF_HANDLER::createSprite(Constants::GAME_SCREEN, gfx_b.id, gfx_b.offset, gfx_b.id, x_pos, y_pos);
```

This abstraction means if we ever switch graphics libraries, we only change one file.

#### SFX_HANDLER (Audio)

Uses a `Clip` struct pattern for clean audio management:

```cpp
struct Clip{
    int id;
    bool loaded;

    void load_clip(){
        if (!loaded){
            mmLoadEffect(id);
            loaded = true;
        }
    }

    void play_clip(){
        if (loaded)
            mmEffect(id);
    }
};
```

Usage is clean:
```cpp
SFX_HANDLER::Clip sfx_wing{SFX_WING};
sfx_wing.load_clip();
sfx_wing.play_clip();
```

#### IO_HANDLER (Save/Load)

Simple binary file save system:

```cpp
struct SaveData {
    int highScore;
};

int loadHighscore(const char* path){
    SaveData data = {0};
    FILE* file = fopen(path, "rb");
    if (file){
        fread(&data, sizeof(SaveData), 1, file);
        fclose(file);
    }
    return data.highScore;
}
```

---

### DS Input Handling (`input.cpp`)

Wraps the DS input system:

```cpp
bool anyKeyPressed(int key){
    return key != 0 && (key & KEY_TOUCH) == 0;  // Any button except touch
}

bool touchDown(int key){
    return (key & KEY_TOUCH) != 0;  // Touch screen tap (not hold!)
}
```

**Important:** `touchDown()` uses `keysDown()` which only fires on the **first frame** of touch, preventing the "hold to fly" bug.

---

### The Assets System (`assets.hpp`)

All asset definitions in one place using `constexpr` structs:

```cpp
struct gfx_bird{
    static constexpr const char* SPRITE = "sprites/Birds";
    static constexpr const char* PALETTE = "palettes/Birds";
    static constexpr int id = 0;
    static constexpr int offset = 0;
    static constexpr int w = 16;
    static constexpr int h = 16;
    static constexpr int layer = 0;
};
```

This keeps magic numbers out of code and makes assets easy to modify.

---

## DS-Specific Concepts

### VRAM and OAM

The DS has limited Video RAM. Sprites must be:
1. **Loaded** from filesystem to RAM (`loadSprite`)
2. **Copied** to VRAM (`vramSprite`)
3. **Created** as OAM entries (`createSprite`)
4. **Updated** each frame (`setSpriteOam`, `updateOAM`)

### Sprite Frames

A single sprite can have multiple frames (like a sprite sheet). The pipe sprite has:
- Frame 0: Bottom pipe segment
- Frame 3: Top pipe segment (flipped)

### Palettes

Each sprite needs a color palette. The DS supports limited palette slots, so we carefully assign:
- Slot 0: Bird
- Slot 1: Pipes
- Slot 2: Number UI
- Slot 3: Score UI
- Slot 4: Medal/Little UI

---

## What I Learned

1. **Separation of Concerns**: Each class handles one thing well
2. **State Machines**: Clean way to handle game states
3. **Encapsulation**: Hide implementation details, expose clean interfaces
4. **Handler Patterns**: Wrap external libraries for flexibility
5. **Static Initialization**: Use `static bool` flags to load assets only once
6. **DS Hardware**: VRAM management, OAM system, palette slots

---

## How to Run the Game

Download `FlappyBirdDs.nds` and run it on an emulator like [melonDS](http://melonds.kuribo64.net/downloads.php).

**For a real Nintendo DS**, you will need a R4 flashcart (may not work on other flashcarts like M3DS REAL - flashcart needs nitrofs support).

For R4, you will need [this firmware](http://old.r4wood.com/pages/Wood-R4-Kernel.html) (Wood R4 V1.62).

For other flashcarts, try [HBMenu](https://github.com/devkitPro/nds-hb-menu/releases/) if you can't launch the game.

---

## Setup for Programming

1. Download an IDE like [Visual Studio Code](https://code.visualstudio.com/)
2. Download [devkitPro](https://github.com/devkitPro/installer/releases)
3. Put all project files in the devkitPro examples folder (e.g., `C:\devkitPro\examples\Flappy_Bird_DS`)

### Compile the Game

Open the IDE console and run:
```bash
make
```

The Nintendo DS game file will be created as `FlappyBirdDs.nds`

---

## Credits

- **Original Code**: [fawnity](https://github.com/Fewnity/Flappy-Bird-Nintendo-DS)
- **Refactoring**: This project
- **NightFox Library**: For making DS 2D graphics manageable
- **Maxmod**: Audio library for DS

---

## License

Educational project - feel free to learn from it!
