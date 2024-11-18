//
// Keyboard.h
// Author: Antoine Bastide
// Date: 16/11/2024
//

#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "Common/RenderingHeaders.h"

#include "Common/Event.h"

namespace Engine2D {
  class Game2D;
}

namespace Engine::Input {
  /**
   * The KeyboardContext struct provides a snapshot of the state of primary keyboard keys
   * (pressed, help and release states) and common modifier keys (shift, control, alt, super, etc.).
   * This struct can be used to manage keyboard input and determine which keys or modifiers
   * are active, as well as the state of lock keys like caps lock and num lock.
   */
  struct KeyboardContext {
    /** Set to true when a key is initially pressed. */
    bool pressed : 1;
    /** Set to true if a key is actively pressed down, remaining true as long as the key is held. */
    bool held : 1;
    /** Set to true when a key is released after being pressed. */
    bool released : 1;
    /** Set to true if the left shift key is currently held down. */
    bool leftShiftPressed : 1;
    /** Set to true if the right shift key is currently held down. */
    bool rightShiftPressed : 1;
    /** Set to true if the left control key is currently held down. */
    bool leftControlPressed : 1;
    /** Set to true if the right control key is currently held down. */
    bool rightControlPressed : 1;
    /** Set to true if the left alt/option key is currently held down. */
    bool leftAltPressed : 1;
    /** Set to true if the right alt/option key is currently held down. */
    bool rightAltPressed : 1;
    /**
     * Set to true if the left Super key is currently held down.
     * - On Windows and Linux, this represents the Windows key (❖).
     * - On macOS, this represents the Command key (⌘).
     */
    bool leftSuperPressed : 1;
    /**
     * Set to true if the right Super key is currently held down.
     * - On Windows and Linux, this represents the Windows key (❖).
     * - On macOS, this represents the Command key (⌘).
     */
    bool rightSuperPressed : 1;
    /** Set to true if Caps Lock is currently held down. */
    bool capsLockPressed : 1;
    /** Set to true if Num Lock is currently held down. */
    bool numLockPressed : 1;
  };

  class KeyboardEvent : public Event<KeyboardContext> {
    friend class Keyboard;
  };

  /**
   * The Keyboard class manages keyboard events, such as key presses and releases,
   * and provides a system for registering callbacks to respond to these events.
   * It includes static methods for initializing keyboard events and processing
   * input from the user. Each key has an associated `KeyboardEvent` that can be
   * used to trigger actions when that key is pressed, held, or released.
   */
  class Keyboard {
    public:
      static KeyboardEvent A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, NUM0, NUM1, NUM2,
          NUM3, NUM4, NUM5, NUM6, NUM7, NUM8, NUM9, SPACE, APOSTROPHE, COMMA, MINUS, PERIOD, SLASH, SEMICOLON, EQUAL,
          LEFT_BRACKET, BACKSLASH, RIGHT_BRACKET, GRAVE_ACCENT, ESCAPE, ENTER, TAB, BACKSPACE, INSERT, DELETE, RIGHT, LEFT,
          DOWN, UP, PAGE_UP, PAGE_DOWN, HOME, END, CAPS_LOCK, SCROLL_LOCK, NUM_LOCK, PRINT_SCREEN, PAUSE, F1, F2, F3, F4, F5,
          F6, F7, F8, F9, F10, F11, F12, F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24, F25, KP_NUM0, KP_NUM1,
          KP_NUM2, KP_NUM3, KP_NUM4, KP_NUM5, KP_NUM6, KP_NUM7, KP_NUM8, KP_NUM9, KP_DECIMAL, KP_DIVIDE, KP_MULTIPLY,
          KP_SUBTRACT, KP_ADD, KP_ENTER, KP_EQUAL, LEFT_SHIFT, LEFT_CONTROL, LEFT_ALT, LEFT_SUPER, RIGHT_SHIFT, RIGHT_CONTROL
          , RIGHT_ALT, RIGHT_SUPER, MENU;

      friend class Engine2D::Game2D;
    private:
      /** If any of the keys were pressed last frame */
      static bool previousKeyStates[GLFW_KEY_LAST + 1];
      /** The window pointer required for querying key states. */
      static GLFWwindow *window;
      Keyboard() = default;
      /**
       * This method sets up the internal map of key codes to `KeyboardEvent`
       * instances, enabling each key's events to be tracked and managed.
       */
      static void initialize(GLFWwindow *window);
      /** Processes all the inputs of the current frame of the game and calls the corresponding key events. */
      static void processInput();
  };
}

#endif //KEYBOARD_H
