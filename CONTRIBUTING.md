The ButtplugUnreal project is fully open source and welcomes contributions from the community in the form of pull requests. Generally speaking, the original author of this project has some loosely held convictions on the direction it should take, and as such pull requests that don't fall in line with that vision may not be accepted. You are always welcome to fork this repo and make it something your own, however! 

This guide serves as a high level overview of the project's architecture, and what areas we feel need special attention. Feel free to create an Issue for the project if you have a question about how it works, or would like to suggest an improvement and get community feedback before starting to actually work on the improvement. If you've encountered a bug, please  report it as an Issue, so that we can track it.

# Low Hanging Fruit

Want to dip your toes in and get started with an easy task that would help the project? Here's a list of "quick wins" to look at...

* **Message Implementation** - The minimal goal of this project is to implement all of the commands and messages described in the Buttplug Protocol Spec. We've documented the progress towards this goal on the wiki [here](https://github.com/cind3rdev/ButtplugUnreal/wiki/Implemented-Messages). You can help by testing messages that are implemented but marked as "Not Tested", or by implementing (and ideally testing) messages that aren't currently implemented. Also feel free to update this wiki page if new commands are added to the spec that haven't been written down yet.
* **Documentation** - We are currently working to document this project in the wiki so that users of the plugin can clearly and easily understand how it works. You can help by making modifications to the wiki to improve the docs in any way.

# Higher Level Goals

The list below contains larger goals on the project's radar. We broadly welcome feedback from the community on these goals. Since the goals are large ane nebulous in nature, we encourage you to make Issues to discuss planned work on the goals before starting.

* **High Level API** - The MVP of the project is to implement the low level Buttplug protocol, but to make the project more useful, we'd like to consider various higher level API mechanisms for adding sex toy integration to your Unreal Engine games. Thoughts include "emitters" for toy stimulation, the ability to physically represent toys in the world or on a character's avatar, integration with the Gameplay Ability System, etc.
* **Blueprint Support** - Because of the requirements of the plugin, we have predominantly written the code in C++. However, it is a very important goal for us to be able to primarily use this plugin through Blueprints. To this end, we want to make sure we are properly annotating the underlying classes, structs, etc. so that they can be used effectively within Blueprints, and we would like to enhance the docs to include plenty of examples using Blueprints.
* **Code Optimization** - The original author of this project was *not* fluent in C++, and is used to the cushy world of automatic garbage collection. It's very likely they made mistakes that could cause memory leaks or other general performance problems. Those more experienced with Unreal Engine C++ are encouraged to heavily audit the code and make improvements or suggestions.

# Architecture

### ButtplugManager

The "root level" of the UnrealButtplug project is the [`ButtplugManager`](https://github.com/cind3rdev/ButtplugUnreal/blob/master/Source/ButtplugUnreal/Public/ButtplugManager.h) actor component. This actor component is meant to be subclassed, but contains all of the functionality for interacting with Buttplug at a lower level. Higher level API components will likely reference a `ButtplugManager` instance to do their bidding. Responsibilities of the `ButtplugManager` include...

* Connection to the Buttplug server
* Device list management, and device scanning
* Sending commands to devices
* Pulling sensor data from devices

### Messages

A bulk of the project are subclasses of the [`UButtplugMessage`](https://github.com/cind3rdev/ButtplugUnreal/blob/master/Source/ButtplugUnreal/Public/Messages/ButtplugMessage.h) class. This class essentially acts as an interface allowing messages to define how they are serialized and deserialized to and from JSON. Messages have three main responsibilities:

* Define the name of the message by overriding `GetMessageName()`
* Serialize the message instance into a `FJsonObject` by overriding `Serialize()`
* Deserializing the message from a `FJsonObject` by overriding `Deserialize()`

Messages are generally classified as outbound (commands sent to the server) and inbound (responses or information received from the server). 

Outbound messages can be sent through the `ButtplugManager` either using the `SendMessage` function, or one of the various functions implemented for sending specific commands, such as `ScalarCmd()`.

Inbound messages are mostly handled in the private `HandleIncomingMessage` function within `ButtplugManager`. Currently, messages that aren't handled here are just logged to the console. You can override the `HandleIncomingMessage` function in your `ButtplugManager` subclass to add game-specific support for messages.
