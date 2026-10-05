# Quick Reference

## Table of Contents

- [AI Tooling Policy]
- [Input Handling - Keys]
  - [Once when a key is pressed or released]
  - [As long as a key is pressed]
- [Input Handling - Mouse]
    - [Mouse buttons - `OnMouseDownEvent` / `OnMouseUpEvent`]
    - [Mouse Position]
- [Game Functions - Overview]

# AI Tooling Policy
Modern AI tools are becoming more powerful, and you will most likely use them throughout your professional career. 
However, before relying on AI, you should first develop your own proper problem-solving and coding skills. Later, AI will become a helpful assistant instead of a replacement.
For now, **your most powerful debugging tool should be the grey matter between your ears.**

> During Programming 1, **you are expected to work without any AI assistance**, unless explicitly asked int the assignment.\
> Please disable any AI tools and focus on developing your own problem-solving and c++ coding skills properly first.

**How to disable GitHub Copilot in Visual Studio 2026:**
1. Go to `Extensions` → `Manage Extensions`.
2. Locate `GitHub Copilot` and click **Disable**.
3. Restart Visual Studio.


---
# Input Handling - Keys
> **Rule of thumb**
>
> - Use `Update()` when something should happen **continuously**.
> - Use `OnKeyDownEvent()` when something should happen **once** when a key is pressed.
> - Use `OnKeyUpEvent()` when something should happen **once** when a key is released.

## Once when a key is pressed or released
Ideal for:
- "Execute this code **once** if this key is pressed."
- "Execute this code on key **down**, and that code on key **release**."
- "Move this object 10px **only once** every time an arrow key is pressed."

>HowTo:
>
> ✅ Check inside `OnKeyDownEvent(SDL_Keycode key)` or `OnKeyUpEvent(SDL_Keycode key)` 
> to make sure it only happens once per keystroke.\
> ❌ **Do not** do this in `Update()`; it would cause continuous updates while key is down, too many checks.

### Respond to a specific key
The `key` parameter can be compared to SDL constants such as `SDLK_SPACE` or `SDLK_a`.\
To find a specific key constant, type `SDLK_` and browse the available options using IntelliSense.
```cpp
void OnKeyDownEvent(SDL_Keycode key)
{
    if (key == SDLK_SPACE)
    {
        // code will be executed once as soon as the spacebar is pressed down
    }
}
```
```cpp
void OnKeyUpEvent(SDL_Keycode key)
{
    if (key == SDLK_SPACE)
    {
        // code will be executed once as soon as the spacebar is released (after pressing down)
    }
}
```
To avoid a long if - else structure, consider using a switch if you have to check several keys:
```cpp
    switch (key)
    {
    case SDLK_LEFT:
        // code connected to left arrow key
        break;
    case SDLK_1:
    case SDLK_KP_1:
        // code connected to both top-row 1 key and numpad 1 key
        break;
    }
```

## As long as a key is pressed
Ideal for:
- "Execute this code **as long as** this key is pressed."
- "Execute this code if this **key combination** is pressed."
- "Keep moving this object 10px **as long as** an arrow key is pressed."

>HowTo:
>
> ✅ Check `SDL_GetKeyboardState` inside `Update(elapsedSec)` for smooth movement every frame.\
> ❌ **Do not** place in `OnKeyDownEvent()` or `OnKeyUpEvent()`, this would cause jittery, single-step movement.

### Check keyboardstate continuously
SDL_GetKeyboardState(nullptr) returns the current **state of every key on the keyboard**.\
To check the state (up or down) of a specific key, type `SDL_SCANCODE_` and browse the available options using IntelliSense.
```cpp
void Update(float elapsedSec)
{
    // get keyboard state collection
    const Uint8* pStates{ SDL_GetKeyboardState(nullptr) };

    if (pStates[SDL_SCANCODE_RIGHT])
    {
        // code to execute as long as right key is down
    }

    if (! pStates[SDL_SCANCODE_RIGHT])
    {
        // code to execute as long as right key is up
    }
}
```
To check for a **key combination**:
```cpp
    if (pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
    {
        // code to execute as long as both left and up key are pressed
    }

```

# Input Handling - Mouse 
## Mouse buttons - `OnMouseDownEvent` / `OnMouseUpEvent`

`e.button` contains information about which button triggered the event. SDL defines it as one of the `SDL_BUTTON_...` constants.

Checking a single button:

```cpp
void OnMouseDownEvent(const SDL_MouseButtonEvent& e)
{
    if (e.button == SDL_BUTTON_LEFT)
    {
        // code related to left mouse button down
    }
}
```

Checking several buttons — same `switch` pattern as with keys:

```cpp
void OnMouseUpEvent(const SDL_MouseButtonEvent& e)
{
    switch (e.button)
    {
    case SDL_BUTTON_LEFT:
        // code related to left mouse button
        break;
    case SDL_BUTTON_MIDDLE:
        // code related to middle mouse button
        break;
    }
}
```

SDL also defines `SDL_BUTTON_X1` and `SDL_BUTTON_X2` for extra side buttons on some mice. Full list in `SDL_mouse.h` or via IntelliSense.

## Mouse position

**All mouse button events** carry `e.x` and `e.y`; the cursor position in window pixels as `int`. \
Cast to `float` to use with the engine's draw functions:

```cpp
void OnMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
    const float mouseX{ static_cast<float>(e.x) };
    const float mouseY{ static_cast<float>(e.y) };
}
```
> ✅ To access the mouse position outside of the mouse events, store it in a global variable that is accessible from the rest of your game code.

# Game Functions - Overview

| Game Function | Purpose | Typical actions | Avoid |
|---------------|---------|-----------------|--------|
| `Start()` | Called **once** when the game starts. Used to prepare everything the game needs before the first frame is shown. | Initialize variables, set starting positions, set colours, create game objects, load resources. | Do **not** draw anything here. Do not put gameplay logic here. |
| `Draw()` | Called **every frame**, over and over, 60 times per second by default. Responsible for **showing the current game state** on the screen. | Draw rectangles, circles, lines, text, sprites later in the course, UI elements, backgrounds. | Do **not** move objects, change health, detect collisions, update timers, etc. **Drawing should only display data.** |
| `Update(float elapsedSec)` | Called **every frame** before drawing. Responsible for **changing the game state** over time. | Move objects, animate values, update timers, process input, detect collisions, change scores, health, mana, XP, etc. | **Do not draw** anything or load resources **here**. |
| `End()` | Called **once** when the game closes. Used to clean up resources that are no longer needed. | Delete dynamically allocated memory, free resources, perform final cleanup. | Do **not** draw anything here. Do **not** place gameplay or animation code here. |