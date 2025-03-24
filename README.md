# CLI Media Browser and Player Application

## Table of Contents
1. [Introduction](#introduction)
2. [Features](#features)
   - [Basic Features](#basic-features)
   - [External Device Connection](#external-device-connection)
3. [Technologies Used](#technologies-used)
   
## Introduction

This project is a command-line interface (CLI) application for Linux that serves as a basic media (audio and video) browser and player with advanced features. It supports browsing media files, managing playlists, editing metadata, and playing video and music. Additionally, it integrates with the FRDM-KL46Z board for external device control. The goal of this project is to apply C++ knowledge and design patterns learned to build a software application for managing and playing media files from both local and external sources. Additionally, the application interacts with a hardware board to control the software, while also implementing unit tests to ensure code quality at the O0 (statement coverage) level.

## Features

### Basic Features

1. **Application Behavior:**
   - The application can run from any directory on your computer.
   - It can also be run from an external USB device (requires mounting the USB and parsing files).
2. **Available Options:**
   - **Media File Browsing:** View a list of media files (audio and video) in the current folder and all subfolders. Includes pagination (25 files per page).
   - **Playlist Management:** 
     - List existing playlists.
     - View a specific playlist.
     - Create, update, or delete playlists.
   - **Metadata Handling (using Taglib):**
     - Accessible from either the media list or a playlist.
     - Display metadata of a media file (Audio: Track name, Album, Artist, Duration, Genre, Publisher, Publish Year; Video: Name, Size, Duration, Bitrate, Codec, etc.).
     - Edit metadata (Modify existing values, Add new metadata keys).
   - **Music Playback (using SDL2 Library):**
     - Basic controls: Play/Pause, Next/Previous.
     - Automatically moves to the next song when the current song finishes.
     - Displays the current playback time and total duration.
   - **Device Volume Control:** Change the volume of the device directly from the application.
     
## External Device Connection

### 1. Integration with S32K144 Board:
- **Volume Control via ADC:** The volume is controlled via ADC on the board.
- **Playback Control Using Buttons:** Play, pause, stop, next, and previous music via the board's buttons.
- **Display Song Information:** The currently playing song’s information is displayed on the board’s screen.

### 2. Deliverables:
- **Software Requirement Specification:**
  - Use case descriptions.
  - Detailed workflows.

- **Design Document:**
  - **Architecture Design:** Implementation of the MVC pattern.
  - **Detailed Design:** Modules and component-level descriptions.

- **Code & Unit Tests:**
  - Implementation of the core application.
  - Unit tests for individual components.

## Technologies Used

- **C++17**: The core programming language used to develop the application.
- **FTXUI**: A C++ library used for creating text-based user interfaces.
- **TagLib**: A library for reading and editing metadata of audio and video files.
- **SDL2**: A cross-platform library used for multimedia applications, such as playing audio and video.
- **S32K144**: A microcontroller board used for hardware integration, including controlling volume and playback with buttons and displaying information on the screen.
- **Unit Testing Framework**: Used to write and run unit tests for individual components of the application to ensure code quality and functionality at the O0 level.
- **Design Patterns**: Implementation of design patterns such as the **MVC (Model-View-Controller)** pattern for structuring the application.


