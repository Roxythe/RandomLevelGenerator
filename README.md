# Random Level Generator

This project is a Random Level Generator designed to procedurally generate dungeon-like maps with various features such as rooms, corridors, biomes, decorations, and interactable elements. It includes a visualizer for rendering the levels and a settings menu for customizing generation parameters.
Features

    Random Level Generation: Procedurally generates levels with rooms and corridors.
    Biomes: Supports multiple biome types:
        Forest
        Cave
        Water
        Desert

    Decorations: Places traps, enemies, and treasure chests within rooms.
    Start and End Points: Randomly generates a starting point and an exit point in the level.
    Visualization:
        Renders the level grid using SFML.
        Displays rooms, corridors, and decorations with distinct colors.
        Includes a legend explaining tile meanings.

    Settings Menu:
        Customize room count and enemy density using sliders.
        Regenerate the level dynamically with a key press (R).
    Key Bindings:
        S: Toggle the settings menu.
        R: Regenerate the level.

## Legend

The visualizer includes a legend that explains what each color in the grid represents:

    White: Spawn Point
    Magenta: End Point
    Blue: Room
    Green: Corridor
    Yellow: Treasure Chest
    Cyan: Trap
    Red: Enemy
    Forest Green: Grassland Biome
    Gray: Cave Biome
    Steel Blue: Water Biome
    Sandy Yellow: Desert Biome
    Transparent: "Press R to regenerate level" (keybinding legend)
    Transparent: "Press S to Open/Close settings" (keybinding legend)

## How to Run

    Clone the repository:

    git clone (https://github.com/Roxythe/RandomLevelGenerator.git)

    Ensure you have the SFML library installed and linked to your project.
    Compile and run the project in your IDE.
    Interact with the application:
        Use the visualizer to view generated levels.
        Press S to open the settings menu.
        Adjust settings like room count and enemy density using sliders.
        Press R to regenerate levels dynamically.

## Controls

    S: Open/close the settings menu.
    R: Regenerate the level.

## Development Details
## Files and Code Structure

    LevelGenerator:
        Responsible for generating rooms, corridors, biomes, and decorations.
    Visualizer:
        Renders the grid and decorations using SFML.
        Provides a settings menu for customization.
    Settings Menu:
        Adjustable sliders for room count and enemy density.
    Event Handling:
        Manages user interactions for key presses and mouse clicks.

## Dependencies

    SFML: Used for rendering and event handling.

## Known Issues

    Interactions with sliders can sometimes require precise mouse clicks.
    If the font file (arial.ttf) is missing, the application may not render text properly.

## Future Enhancements

    Add more biomes and decorations.
    Support saving and loading levels.
    Improve user interface with more interactable elements (e.g., buttons).
    Add music and sound effects for an immersive experience.

## Credits

    Developed by Rocky Harding.
