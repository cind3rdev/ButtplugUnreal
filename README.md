# ButtplugUnreal

ButtplugUnreal is a [Buttplug](https://buttplug.io/) integration plugin for Unreal Engine 5. This project is very much a work in progress, but has basic functionality in place for communicating with connected toys and devices. It has been tested to work through [Intiface Central](https://intiface.com/central/) but should work with any Buttplug server implementing the [Buttplug Protocol](https://buttplug-spec.docs.buttplug.io/docs/spec).

# Installation

Download this repo as a ZIP file and extract the files to a folder called `ButtplugUnreal` in your project's `Plugins` folder. Reload your Unreal Engine project (restart the editor), recompile the module if prompted, and you should be good to go!

# Basic Usage

The base class for ButtplugUnreal is the `ButtplugManager` Actor Component. You can create a Blueprint or C++ class dervied from `ButtplugManager` to begin connecting your game to Buttplug. The `ButtplugManager` class handles a few low to mid-level functionalities for interacing with toys...

- Connection to Buttplug Server & Connection/Disconnection Events
- Maintains a list of connected Devices & Device Added/Removed/Updated Events
- Buttplug Command Invocation, such as `ScalarCmd`, `LinearCmd`, `VibrateCmd`, etc.
- High level interaction (for use in Blueprints) for toy control
