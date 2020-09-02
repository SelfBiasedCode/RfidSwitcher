# RfidSwitcher

## Summary
RfidSwitcher is a wrapper for the Arduino RFID library. It allows the registration of up to 128 RFID tag UIDs along with a callback function pointer.

## Technical Details
Execution is synchronous through a poll() function. Class instantiation can be done statically, saving the need for dynamic memory allocation.

## Usage
See also the included example.

### Setup
1. Construct a class instance.
2. Initialize the RFID module with **init()**.
3. Register tags using **registerTags()**.
 
### Loop
1. Call poll(). If a tag was read, its ID (zero to 127) is returned. If not, an error code is returned (negative number).

## Known Issues
For performance reasons, no sanitation (e.g. number of tags to be registered) or error checking is performed.