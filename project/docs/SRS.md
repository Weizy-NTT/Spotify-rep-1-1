# 🎵 **Media Player Application**

---

## **Use Case 1: View Media Files**
**Description:**  
The user can browse media files (audio and video) in the current directory or external USB storage.

### **Features:**
1. **Select Directory/USB Device:**  
   The user selects the directory or USB device to scan for media files.

2. **List Media Files:**  
   The system lists all media files in the selected directory and its subdirectories.

3. **Pagination:**  
   The user navigates through the list of media files using pagination (**25 files per page**).

---

## **Use Case 2: Manage Playlists**
**Description:**  
The user can manage playlists to organize media files.

### **Features:**
- **List Playlists:**  
  The system displays all existing playlists.

- **View Playlist:**  
  The user selects a playlist, and the system displays the media files in it.

- **Create Playlist:**  
  The user provides a name and adds media files to create a new playlist.

- **Update Playlist:**  
  The user adds or removes media files from an existing playlist.

- **Delete Playlist:**  
  The user selects a playlist to delete.

---

## **Use Case 3: View and Edit Metadata**
**Description:**  
The user can view and modify metadata of media files.

### **Features:**
- **View Metadata:**  
  The user selects a media file, and the system displays metadata such as:  
  - Track Name  
  - Album  
  - Artist  
  - Duration  
  - Genre  
  - ...and more.

- **Edit Metadata:**  
  The user modifies existing metadata fields or adds new ones.

---

## **Use Case 4: Playback Media**
**Description:**  
The user can play media files with basic playback functionalities.

### **Features:**
- **Play/Pause:**  
  The user starts or pauses playback of a selected media file.

- **Stop:**  
  The user stops playback.

- **Next/Previous:**  
  The user navigates to the next or previous media file.

- **Automatic Transition:**  
  The system automatically transitions to the next song when the current one finishes.

---

## **Use Case 5: Control Volume**
**Description:**  
The user adjusts the playback volume using both software and hardware.

### **Features:**
- **Increase/Decrease Volume:**  
  The user adjusts the volume through keyboard commands:  
  - `i` to **increase**  
  - `d` to **decrease**

- **Hardware Volume Control:**  
  The user adjusts the volume using the **ADC on the S32K144 board**.

---

## **Use Case 6: Display Information on S32K144**
**Description:**  
The system communicates with the **S32K144** board to display song information and control playback.

### **Features:**
- **Display Song Information:**  
  When a song is playing, its name, duration, and playback status are displayed on the S32K144 screen.

- **Hardware Control:**  
  The user uses buttons on the S32K144 board to:  
  - Play/Pause  
  - Stop  
  - Next  
  - Previous
