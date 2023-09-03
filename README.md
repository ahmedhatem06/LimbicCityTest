Documentation.
The class MyHUD contains a reference to a UI widget and adds it to the viewport.

The class MyNewWidget is responsible for managing UI elements such as placement buttons, a list view for buildings, and a customize list. It handles the visibility of these elements and binds click event handlers in its constructor.

The class C_Building serves as the base class for all buildings. It sets up a static mesh component and overlap functions in its constructor. It also includes functions for customizing the building, such as changing color, rotating right/left, and removing the building.

The class BuildingManager is responsible for calling the customize functions on the selected building.C_Building notifies BuildingManager when it's clicked in the game, then BuildingManager holds a reference to the selected building and receives calls from MyNewWidget. It then invokes the appropriate function on the building instance.

A blueprint is created from BuildingManager, which serves as the parent for all building blueprints. Each building blueprint is derived from this parent blueprint.

The class PlayerPawn represents the camera in the game. It contains modifiable values and handles input actions/mappings. It adds a spring arm component and a camera component in its constructor. The class also includes methods for camera movement and rotation.

When a building is clicked, it invokes a function in Actor_BuildingGenerator with a parameter that maps to the corresponding building. The function spawns the building in the game. The player can then move the building on the ground using GetHitResultUnderCursor. The building's location is set based on the hit location until the user clicks on the ground to place it.

In summary, these classes and their interactions facilitate UI management, building customization, camera control, and building placement within the game environment.