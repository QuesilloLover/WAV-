# Description 

This code modifies the volume of an audio file in WAV format by increasing or decreasing the sound samples by a given factor in the command line.

## Structure

The WAV header is stored in a struct with every single attribute for the 44 Bytes of the header.

## Notes

This code only works with WAV standard headers. If you want to modify the volume of an audio file with a non-canon header format, like an audio downloaded from YouTube, you need to create an array in order to store the extra data of the header.
